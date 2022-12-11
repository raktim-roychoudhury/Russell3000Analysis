# pragma once
#include "group-prototype_Lune.h"
#include "Matrix.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace MatrixOp;

class Bootstrap
{
    private:
        int N = 40;
        int M = 80;
        Group* GroupPtr;
        
        //Saved Output
        Matrix AAR; //group x time
        Matrix CAAR; //group x time
        Vector AAR_STD; //group x 1
        Vector CAAR_STD; //group x 1
        Vector Avg_AAR;
        Vector Avg_CAAR;
        
        vector<string> PullTickers(int index) const;
        Vector Cal_AAR(const vector<string>& sample);
        Vector Cal_CAAR(const Vector& AAR);
        void Plot() const;
        
    public:
        Bootstrap(const Group* GroupPtr_);
        ~Bootstrap();
        void SetN(int N_);s
        void SetM(int M_)
        void RunBootstrap(int T); 
};

void Bootstrap::RunBootstrap(int T //number of timesteps: 2N)
{
    Vector AAR_tmp;
    int N_Group = GroupPtr->GetN();
    
    //initialize result matrices
    AAR = ContMatrix(0,N_Group,T);
    CAAR = ContMatrix(0,N_Group,T);
    AAR_STD = ContVector(0,N_Group);
    CAAR_STD = ContVector(0,N_Group);
    Avg_AAR = ContVector(0,N_Group);
    Avg_CAAR = ContVector(0,N_Group);
    
    for(int n = 0; n < N_Group ; n++) //iterate through each group
    {
        AAR_tmp = ConstVector(0,T); //overload this
        
        for(int i = 0;i < N; i++) //iterate through each monte carlo iteration 
        {
            vector<string> sample = PullTickers(n);
            
            AAR_tmp = Cal_AAR(sample);
            AAR[n] += AAR_tmp;
            AAR_STD[n] += AAR_tmp^AAR_tmp;
            CAAR[n] += Cal_CAAR(AAR);
            CAAR_STD += CAAR[n]^CAAR[n];
        }
        
        AAR[n] = 1/N*AAR[n]; //divide by N later to not lose precision
        CAAR[n] = 1/N*CAAR[n];
        
        Avg_AAR[n] = AAR[n]^ContVector(1,T)/T;
        Avg_CAAR[n] = CAAR[n]^ContVector(1,T)/T;
        AAR_STD[n] = 1/(N*N_Group)*AAR_STD[n] - Avg_AAR[n]*Avg_AAR[n];
        CAAR_STD[n] = 1/(N*N_Group)*CAAR_STD[n] - Avg_CAAR[n]*Avg_CAAR[n]; //std for each timestep???
    }
    
}