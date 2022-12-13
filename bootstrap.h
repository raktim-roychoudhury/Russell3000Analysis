# pragma once
#include "group-prototype_Lune.h"
#include "Matrix.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
using namespace MatrixOp;
namespace fre
{
    class Bootstrap
    {
        private:
            int MCN = 40;   // no. of bootstrap (monte carlo) iterations 
            int M = 80;     // size of each sample from a group 
            Group* GroupPtr;
            map <string, Stock>* myMap;
            
            //populated as part of output of Bootstrap  
            Matrix Avg_AAR; //group x time  
            Matrix Avg_CAAR; //group x time   
            Matrix AAR_STD; //group x time 
            Matrix CAAR_STD; //group x time
    
        public:
            Bootstrap(const Group* GroupPtr_);
            ~Bootstrap();
            Vector Cal_AAR(const vector<string>& sample); // return AAR calculation across sample stocks (of 1 sample) for 2N timesteps (2N x 1)
            Vector cumsum(const Vector& V); // return CAAR calculation across sample stocks (of 1 sample) for 2N timesteps (2N x 1)
         
            Vector VSQRT(Vector &V);
            Vector AbnormRet(string ticker);
            Vector generateSample(int gr_n);
            
            // void Plot() const; 
            void SetMCN(int N_) {N = N_};
            void SetM(int M_) {M = M_};
            void RunBootstrap(int T); // return
            
    };
    
    
}