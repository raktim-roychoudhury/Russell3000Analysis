# pragma once
#include "group-prototype_Lune.h"
#include "Matrix.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
using namespace MatrixOp;

class Bootstrap
{
    private:
        int MCN = 40;   // no. of bootstrap (monte carlo) iterations 
        int M = 80;     // size of each sample from a group 
        Group* GroupPtr;
        
        //populated as part of output of Bootstrap  
        Matrix AAR; //group x time  
        Matrix CAAR; //group x time   
        Vector AAR_STD; //group x 1 
        Vector CAAR_STD; //group x 1
        Vector Avg_AAR; //group x 1
        Vector Avg_CAAR; //group x 1
        

    public:
        Bootstrap(const Group* GroupPtr_);
        ~Bootstrap();
        vector<string> PullTickers(int index) const; // returns sample of size 80 of beat (0), miss (1), meet)(2) (80 x 1)
        
        // we need IWV, we need the earnings announcement date for each stock and returns functions in stock class
        Vector Cal_AAR(const vector<string>& sample); // return AAR calculation across sample stocks (of 1 sample) for 2N timesteps (2N x 1)
        Vector Cal_CAAR(const Vector& AAR); // return CAAR calculation across sample stocks (of 1 sample) for 2N timesteps (2N x 1)
        
        void Plot() const; 
        void SetMCN(int N_);
        void SetM(int M_)
        void RunBootstrap(int T); // return
};

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
                sample = PullTickers(n); 
                AAR_tmp = Cal_AAR(sample);
                AAR[n] += AAR_tmp;      // need to overload this operator (Shweta to do)
                AAR_STD[n] += AAR_tmp^AAR_tmp;
                CAAR_tmp = Cal_CAAR(AAR);
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