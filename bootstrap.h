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
            // Vector FN(string ticker);   // returns a vector of 2 - start index and end index
            // this function from Stocks class
            
            void Plot() const; 
            void SetMCN(int N_);
            void SetM(int M_)
            void RunBootstrap(int T); // return
    };
    
    
}