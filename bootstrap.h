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
using namespace std;

class BootStrap
{
    private:
            
            int M = 80, N = 40;                        //number of stocks and iterations
            vector<double> CalAAR;
            vector<double> CalCAAR;
            //result matrix structure
    
    public:
            
            void runBootStrap();                        //matrix generate
            //BootStrap(Group *Group_ptr)
            void PullStocks();                          // private??
            string getdateStart();
            string getdateEnd();
            void AAR();                                //calculate AAR
            void CARR();                               // calculate CAAR
            void plotCARR();                           // plot 
           
    
};