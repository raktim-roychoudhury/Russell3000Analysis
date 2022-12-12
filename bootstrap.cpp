#include <stdio.h>
#include <cstring>
#include <string> 
#include <iostream>
#include <vector>
#include <locale>
#include <iomanip>
#include <cassert>
#include <map>
#include "Stocks.h"
#include "bootstrap.h"

namespace fre
{

    Vector generateSample(int gr_n)
    {
        int max_size = 1000;
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
    		W[i] = grp_ptr->sample[i];
    	}
    	
	    return W;
    }
    
    Vector Bootstrap :: AbnormRet(string ticker)
    {
        Vector AbnormReturn(T);
        start_index = FN(ticker)[0];
        end_index =FN(ticker)[1];
        int j = 0;
        for(int i=start_index; i<=end_index; i++, j++ )
        {
         AbnormReturn[j] = myMap(ticker).Ret[i] - myMap("IWV").Ret[i];   
        }
        return AbnormReturn
    }
    
    // vector<string> PullTickers(int index) const;
 // we need IWV, we need the earnings announcement date for each stock and returns functions in stock class
    Vector Bootstrap :: Cal_AAR(int gr_n //group number) // return AAR calculation across sample stocks (of 1 sample) for 2N timesteps (2N x 1)
    {
        Vector sample(M);
        Vector Ave = ConstVector(0,T);
        sample = generateSample(n);
        for(int i = 0; i< M; i++)
        {
            Ave += AbnormRet(sample[i]);
            
            
        }
        
        
        
    }
    
    
    Vector Cal_CAAR(const Vector& AAR); // return CAAR calculation across sample stocks (of 1 sample) for 2N timesteps (2N x 1)
            
    
    
    void Bootstrap::RunBootstrap(int T //number of timesteps: 2N)
    {
        Vector AAR_tmp, CAAR_tmp;
        String sample;
        int N_Group = GroupPtr->GetN(); // number of groups. In this case - 3
    
        //initialize result matrices to 0s
        AAR = ConstMatrix(0,N_Group,T);     //group x time 
        CAAR = ConstMatrix(0,N_Group,T);    //group x time 
        AAR_STD = ConstVector(0,N_Group);   //group x 1 
        CAAR_STD = ConstVector(0,N_Group);  //group x 1 
        Avg_AAR = ConstVector(0,N_Group);   //group x 1 
        Avg_CAAR = ConstVector(0,N_Group);  //group x 1 
        
        AAR_tmp.resize(T); // vector of size 2N 
        CAAR_tmp.resize(T); // vector of size 2N 
        
        for(int n = 0; n < N_Group ; n++) //iterate through each group
        {
            for(int i = 0;i < MCN; i++) //iterate through each monte carlo iteration (i.e. Bootstrap iteration) 
            {
                // sample = PullTickers(n); 
                AAR_tmp = Cal_AAR(n);
                AAR[n] += AAR_tmp;      
                AAR_STD[n] += AAR_tmp^AAR_tmp;
                CAAR_tmp = Cal_CAAR(AAR_tmp);
                CAAR[n] += CAAR_tmp;
                CAAR_STD[n] += CAAR_tmp^CAAR_tmp;
            }
            
            AAR[n] = (1/MCN)*AAR[n]; //divide by N later to not lose precision
            CAAR[n] = (1/MCN)*CAAR[n];
            Avg_AAR[n] = (AAR[n]^ConstVector(1,T))/T;
            Avg_CAAR[n] = (CAAR[n]^ContVector(1,T))/T;
            AAR_STD[n] = sqrt((1/(T*MCN)*AAR_STD[n] - Avg_AAR[n]*Avg_AAR[n]));
            CAAR_STD[n] = sqrt((1/(T*MCN))*CAAR_STD[n] - Avg_CAAR[n]*Avg_CAAR[n]); 
        }
        
    }
}

