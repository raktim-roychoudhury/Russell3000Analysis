#include <stdio.h>
#include <cstring>
#include <string> 
#include <iostream>
#include <vector>
#include <locale>
#include <iomanip>
#include <cassert>
#include <map>
#include <chrono>
#include <time.h>
#include <random>
#include<algorithm>
#include<iterator>
#include "Stocks.h"
#include "bootstrap.h"
#include "Matrix.h"
#include "Group.h"

namespace fre
{
    Bootstrap::Bootstrap(Group* GroupPtr_, map<string, Stocks>* MapPtr_): GroupPtr(GroupPtr_),MapPtr(MapPtr_)
    {
        T = (*MapPtr).begin()->second.GetN()*2;
             
    }

    String Bootstrap :: generateSample(int gr_n) // To be unit tested - with integration 
    {
        int max_size = 1000;
        String grouptickers(max_size); 
        grouptickers = (GroupPtr->GetGroup_Mapping())[gr_n];
        String W(M);
        vector<int> numbers;
        vector<int> sample;
        int num_random_samples = 80;
        for (int i = 0; i < max_size; i++)   
        numbers.push_back(i);
	    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	    std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));
    	for (int i = 0; i < num_random_samples; i++)
    	{
    		sample.push_back(numbers[i]);
    	}
    	for (int i = 0; i < sample.size(); i++)
    	{
    		W[i] = grouptickers[sample[i]];  // operator overloading
    	}
    	
	    return W;
    }
    
    /*
    Vector Bootstrap :: VSQRT(Vector &V)    // unit tested
    {
        int d = (int)V.size();
        Vector U(d);
        for (int j = 0; j < d; j++) U[j] = sqrt(V[j]);
        return U;
    }
    */
    // return CAAR calculation across sample stocks (of 1 sample) for 2N timesteps (2N x 1)
    Vector Bootstrap :: cumsum(const Vector& V) // unit tested
    {
        int d = (int)V.size();
        Vector U(d);
        U[0] = V[0];
        for(int j = 1; j < d; j++)
        {
            U[j] = U[j-1] + V[j];
        }
        return U;
    }
    
    
    Vector Bootstrap :: AbnormRet(string ticker) // To be unit tested - with integration 
    {
        Vector AbnormReturn(T);
        int start, end;
        start = (*MapPtr)[ticker].GetStartIndex();
        end = (*MapPtr)[ticker].GetEndIndex();
        Vector R = (*MapPtr)[ticker].GetReturns();
        Vector Benchmark = (*MapPtr)["IWV"].GetReturns();
        int j = 0;
        for(int i=0; i<=T; i++)
        {
         AbnormReturn[i] = R[start+1+i] - Benchmark[start+1+i];   
        }
        return AbnormReturn;
    }
 
    // return AAR calculation across sample stocks (of 1 sample) for 2N timesteps (2N x 1)
    Vector Bootstrap :: Cal_AAR(int gr_n) // To be unit tested - with integration 
    {
        String sample(M);
        Vector Ave = ConstVector(0,T);
        sample = generateSample(gr_n);
        for(int i = 0; i< M; i++)
        {
            Ave += AbnormRet(sample[i]);    // operator overloading
        }
        
        Ave = (1/M)*Ave;
        return Ave;
        
    }

    //number of timesteps: 2N)
    void Bootstrap :: RunBootstrap()  // To be unit tested - with integration 
    {

        Vector AAR_tmp, CAAR_tmp;
        int N_Group = GroupPtr->GetN(); // number of groups. In this case - 3
        //initialize result matrices to 0s
        Avg_AAR = ConstMatrix(0,N_Group,T);     //group x time 
        Avg_CAAR = ConstMatrix(0,N_Group,T);    //group x time 
        AAR_STD = ConstMatrix(0,N_Group,T);   //group x time 
        CAAR_STD = ConstMatrix(0,N_Group,T); //group x time 
        
        AAR_tmp.resize(T); // vector of size 2N 
        CAAR_tmp.resize(T); // vector of size 2N 
        CAAR_tmp.resize(T); 
        for(int n = 0; n < N_Group ; n++) //iterate through each group
        {
            for(int i = 0;i < MCN; i++) //iterate through each monte carlo iteration (i.e. Bootstrap iteration 1-40) 
            {
                AAR_tmp = Cal_AAR(n);
                Avg_AAR[n] += AAR_tmp;      
                AAR_STD[n] += AAR_tmp*AAR_tmp;
                CAAR_tmp = cumsum(AAR_tmp);
                Avg_CAAR[n] += CAAR_tmp;
                CAAR_STD[n] += CAAR_tmp*CAAR_tmp;
            }
            for(int j=0;j<T;j++)
            {
                Avg_AAR[n][j] = (1/MCN)*Avg_AAR[n][j]; 
                Avg_CAAR[n][j] = (1/MCN)*Avg_CAAR[n][j];
                AAR_STD[n][j] = sqrt((1/(MCN)*AAR_STD[n][j] - Avg_AAR[n][j]*Avg_AAR[n][j]));
                CAAR_STD[n][j] = sqrt((1/(MCN))*CAAR_STD[n][j] - Avg_CAAR[n][j]*Avg_CAAR[n][j]); 
            }
            
            //Avg_AAR[n] = (1/MCN)*Avg_AAR[n]; 
            //Avg_CAAR[n] = (1/MCN)*Avg_CAAR[n];
            //AAR_STD[n] = VSQRT((1/(MCN)*AAR_STD[n] - Avg_AAR[n]*Avg_AAR[n]));
            //CAAR_STD[n] = VSQRT((1/(MCN))*CAAR_STD[n] - Avg_CAAR[n]*Avg_CAAR[n]); 
        }
    }
    
    Vector Bootstrap::GetAAR(int gr_index) const
    {
        return Avg_AAR[gr_index];
    }
    Vector Bootstrap::GetAAR_STD(int gr_index) const
    {
        return AAR_STD[gr_index];
    }
    Vector Bootstrap::GetCAAR(int gr_index) const
    {
        return Avg_CAAR[gr_index];
    }
    Vector Bootstrap::GetCAAR_STD(int gr_index) const
    {
        return CAAR_STD[gr_index];
    }
}

