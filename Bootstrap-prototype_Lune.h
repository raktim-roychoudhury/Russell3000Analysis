# pragma once
#include "group-prototype_Lune.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef vector<double> Vector;
typedef vector<vector<double>> Matrix;
typedef vector<vector<string>> Table;

class Bootstrap
{
    private:
        int N = 40;
        int M = 80;
        Group* GroupPtr;
        
        //Saved Output
        Matrix AAR; //group x time
        Matrix CAAR; //group x time
        Matrix AAR_STD; //group x time
        Matrix CAAR_STD //group x time
        
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

void Bootstrap::RunBootstrap(int T //number of timesteps N)
{
    Vector AAR;
    AAR.resize(T);
    for(int n = 0; n < GroupPtr->GetN(); n++) //iterate through each group
    {
        AAR = 0; //overload this
        for(int i = 0;i < N; i++) //iterate through each monte carlo iteration 
        {
            vector<string> sample = PullTickers(n);
            
            AAR = Cal_AAR(sample);
            AAR[n] += AAR;
            AAR_STD[n] += AAR*AAR;
            CAAR[n] += Cal_CAAR(AAR);
            CAAR_STD += CAAR[n]*CAAR[n];
        }
        AAR[n]/=N; //divide by N later to not lose precision
        AAR_STD[n] = AAR_STD[n]/N - AAR[n]*AAR[n];
        CAAR[n]/=N;
        CAAR_STD[n] = CAAR_STD[n]/N - CAAR[n]*CAAR[n]; //std for each timestep???
    }
    
}