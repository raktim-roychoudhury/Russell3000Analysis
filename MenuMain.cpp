#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <stdexcept> 
#include <iomanip>
#include <vector>
#include <map>
#include <chrono>
#include <sstream> 
#include <typeinfo>
#include "ReadLoadData.h"
#include "Stocks.h"
#include "Group.h"
#include "bootstrap.h"
#include "Matrix.h"

using namespace std;
using namespace std::chrono;
using namespace fre;
// vector output print function 


void print_v(vector<double> v)
{
    auto itr = v.begin();
    for (;itr != v.end(); itr++)
    {
        cout << *itr << " " << fixed << setprecision(3);
        
    }
    cout <<endl;
}

//map and vector of vector prints?? are they included in header files ?
String SetN(int N, map<string, Stocks> &stock_map)
{
//    cout<<"Printing all tickers: ";
    auto itr2 = stock_map.begin();
    
    String skipped_tickers;
    
    for(;itr2 != stock_map.end(); itr2++)
    {
        //Stocks temp = (itr->second);
        //cout<<itr2->first;
        int flag = (itr2->second).SetN(N);
        if(flag == -1)
        {
            skipped_tickers.push_back(itr2->first);
            
        }
        //cout<<endl;
    }
    
    cout<<"\nsize inside SetN: "<<skipped_tickers.size()<<endl;
    return skipped_tickers;
}

void CalAbnormalReturns(map<string, Stocks> &stock_map)
{
    auto itr = stock_map.begin();
    for(; itr != stock_map.end(); itr++)
    {
        (itr->second).CalculateAbnormalReturns(stock_map);
    }
    cout<<"Finished AAR\n";
}


int main() 
{
    
    int x,group,test =0;  // menu option and number of days 
    string tick;
    int N=0;
    int integer1;

    map<string, Stocks> GlobalStockMap;
    Stocks Russel;
    
    LoadEarnings(GlobalStockMap);
    
    String skipped_tickers;
    
    GlobalStockMap["IWV"] = Russel;
    
    Groupby_Surprise gobj(&GlobalStockMap);
    
    Table groupTable = gobj.GetGroup_Mapping();
    
    Bootstrap GlobalBoot;
    // create object of bootstrap or our stock object with our data Bootstrap test;
    
    int fetched = 0;
    
    while(true)
    {
        cout<<"Menu: "<<endl;
        cout<<"1) Enter N to retrieve 2N+1 historical prices for all stocks (Please allow around 5 mins to fetch)"<<endl;
        cout<<"2) Pull information for one stock from one group. "<<endl;
        cout<<"3) Display AAR, AAR-std, CAAR, CAAR-std for one group. "<<endl;
        cout<<"4) Display gnuplot plot for CAAR of all 3 groups.  "<<endl;
        cout<<"5) Exit program "<<endl<<endl;
        cout<<"Please select appropriate option number:  "<<endl;;
        cin>>x;
   
        switch(x)
        {
            case 1:
            {

                while(test==0)
                {
                    
                    cout<<"Enter N value between 60 and 80: "<<endl;
                    cin>>N;
                    integer1 = (int) N;
                    
                    
                    if (integer1 != N)
                    {
                        cout<<"Error, please enter an integer value error"<<endl;
                        cin.clear();
                    }
                    else if(N>=60 && N<=80 && !cin.fail())  // n is an int 
                    {
                        
                        if (fetched == 0)
                        {
                            cout<<"Loading data, please allow around 5 mins to load...\n";
                        
                            auto start = high_resolution_clock::now();
                            FetchData(GlobalStockMap);
                            auto stop = high_resolution_clock::now();
                            auto duration = duration_cast<seconds>(stop - start);
                            cout<<"Fetched data seconds: "<<duration.count()<<endl;
                            fetched  = 1;
                            CalAbnormalReturns(GlobalStockMap);
                        }
                        
                        
                        
                        skipped_tickers = SetN(N, GlobalStockMap);
                        gobj.CreateGroups(skipped_tickers);
                        test = 1;
                    }
                    else
                    {
                        cout<<"Error, Enough data points not found. Please select N above 60 and below 80 "<<endl;
                        cin.clear();
                    }
                }
                break;
            }
            case 2:
            {   
                if (N>=60 && N<=80)
                {
                    while(test==0)
                    {
                        cout<<"Please provide ticker of stock: "<<endl;
                        cin>> tick;
                        
                        if(GlobalStockMap.find(tick) != GlobalStockMap.end())
                        {
                            GlobalStockMap[tick].DisplayDetails();
                        }
                        else
                        {
                            cout<<"Please enter a valid ticker\n";
                            test = 1;
                        }
                        
                        
                        if(!cin.fail())
                        {
                            test = 1;
                        }
                        else 
                        { 
                            cout<<"Error, Invalid Input field. Example: Try GOOG ";   // try and error c++ 
                        }
                    }
                }
                else
                {
                    cout<<"Data has not yet been retrieved! Try retrieving data first using Option 1 in Main Menu!"<<endl;
                }
                break;
            }
            case 3:
            {
                Bootstrap boot(&gobj, &GlobalStockMap, N);
                boot.RunBootstrap();
                cout << "Bootstrap object created" << endl;
                if(N>=60 && N<=80)
                {
                    while(test==0)
                    {
                        cout<<"1) Beat \t 2) Meet \t 3) Miss"<<endl;
                        cout<< "Please select appropriate group number: "<<endl; 
                        cin>>group;
                        int integer2 = (int) group;
                        
                        if(integer2 != group)
                        {
                            cout<<"Invalid Input field"<<endl;
                            cin.clear();
                            
                        }
                        else if(group == 1)   //switch?
                        {
                            cout<<" Beat Estimate Group summary "<<endl;
                            cout<<" Average Abnormal Returns (AAR) "<<endl;
                            cout << "AAR - Group 1 "<< endl;
                            Vector vec0_mean; 
                            vec0_mean = 100*boot.GetAAR(0);
                            cout << vec0_mean << endl;
                            
                            cout<<" Average Abnormal Returns standard deviation (AAR-std) "<<endl;
                            cout << "AAR_STD - Group 1 "<< endl;
                            Vector vec0_std;
                            vec0_std = 100*boot.GetAAR_STD(0);
                            cout << vec0_std << endl;
                            
                            cout<<" Cumilative Average Abnormal Returns (CAAR) "<<endl;
                            cout << "CAAR - Group 1 "<< endl;
                            Vector vec0_CAAR;
                            vec0_CAAR = 100*boot.GetCAAR(0);
                            cout << vec0_CAAR << endl;
                            
                            cout<<" Cumilative Average Abnormal Returns (CAAR-std) "<<endl;
                            cout << "CAAR_STD - Group 1 "<< endl;
                            Vector vec0_Cstd;
                            vec0_Cstd = 100*boot.GetCAAR_STD(0);
                            cout << vec0_Cstd << endl;

                            test = 1;
                        }
                        else if(group == 2)
                        {
                            
                            

                            cout<<" Beat Estimate Group summary "<<endl;
                            cout<<" Average Abnormal Returns (AAR) "<<endl;
                            cout << "AAR - Group 2 "<< endl;
                            Vector vec1_mean; 
                            vec1_mean = 100*boot.GetAAR(1);
                            cout << vec1_mean << endl;
                    
                            cout<<" Average Abnormal Returns standard deviation (AAR-std) "<<endl;
                            cout << "AAR_STD - Group 2 "<< endl;
                            Vector vec1_std;
                            vec1_std = 100*boot.GetAAR_STD(1);
                            cout << vec1_std << endl;
                        
                            cout<<" Cumilative Average Abnormal Returns (CAAR) "<<endl;
                            cout << "CAAR - Group 2 "<< endl;
                            Vector vec1_cumulative;
                            vec1_cumulative = 100*boot.GetCAAR(1);
                            cout << vec1_cumulative << endl;

                        
                            cout<<" Cumilative Average Abnormal Returns (CAAR-std) "<<endl;
                            cout << "CAAR_STD - Group 2 "<< endl;
                            Vector vec1_cumstd;
                            vec1_cumstd = 100*boot.GetCAAR_STD(1);
                            cout << vec1_cumstd << endl;
                            //print object.misscaarstd
                            
                            test = 1;
                        }
                        else if(group == 3)
                        {
                            
                            cout<<" Meet Estimate Group summary "<<endl;
                            cout<<" Average Abnormal Returns (AAR) "<<endl;
                            cout << "AAR - Group 3 "<< endl;
                            Vector vec2_mean; 
                            vec2_mean = 100*boot.GetAAR(2);
                            cout << vec2_mean << endl;
                            
                
                            cout<<" Average Abnormal Returns standard deviation (AAR-std) "<<endl;
                            cout << "AAR_STD - Group 3 "<< endl;
                            Vector vec2_std;
                            vec2_std = 100*boot.GetAAR_STD(2);
                            cout << vec2_std<<endl;
                            
                        
                            cout<<" Cumilative Average Abnormal Returns (CAAR) "<<endl;
                            cout << "CAAR - Group 3 "<< endl;
                            Vector vec2_CAAR;
                            vec2_CAAR = 100*boot.GetCAAR(2);
                            cout << vec2_CAAR << endl;
                            
                        
                            cout<<" Cumilative Average Abnormal Returns (CAAR-std) "<<endl;
                            cout << "CAAR_STD - Group 3 "<< endl;
                            Vector vec2_Cstd;
                            vec2_Cstd = 100*boot.GetCAAR_STD(2);
                            cout << vec2_Cstd << endl;
                            
                            test = 1;
                        }
                        else 
                        {
                            cout<<"Error, Please select valid option number"<<endl;
                        }
                    
                    }
                    GlobalBoot = boot;
                    
                }
                
                else
                {
                    cout<<"Data has not yet been retrieved! Try retrieving data first using Option 1 in Main Menu!"<<endl;
                }
                break;
            }
            case 4:
            {   
                if(N>=60 && N<=80)
                {
                    
                    cout<<"CAAR for all 3 groups "<<endl;
                    //object.plot
                    
                    Vector g1 = GlobalBoot.GetCAAR(0);
                    Vector g2 = GlobalBoot.GetCAAR(1);
                    Vector g3 = GlobalBoot.GetCAAR(2);
                    
                    int i = 0;
                    int nIntervals = integer1*2;
                    
                    cout<<"Plot size: "<<nIntervals<<endl;

                    
                    double* xData = (double*) malloc((nIntervals+1)*sizeof(double));
                    double* yData = (double*) malloc((nIntervals+1)*sizeof(double));
                    double* yData2 = (double*) malloc((nIntervals+1)*sizeof(double));
                    double* yData3 = (double*) malloc((nIntervals+1)*sizeof(double));
                    
                    for (i = 0; i < nIntervals; i++) {
                        xData[i] = i-integer1;
                    }
                    for (i = 0; i <= nIntervals; i++) {
                        yData[i] = g1[i];
                    }
                    for (i = 0; i <= nIntervals; i++) {
                        yData2[i] = g2[i];
                    }
                    for (i = 0; i <= nIntervals; i++) {
                        yData3[i] = g3[i];
                    }
                    
                    const char *title = "Avg CAAR for 3 groups";
                    const char *yLabel = "Avg CAAR(%)";
                        
                    plotResults(xData, yData, yData2, yData3, nIntervals, title, yLabel);
                    
                    GlobalBoot.plotResults(100*g1, 100*g2, 100*g3, N);
                    
                }
                else
                {
                    cout<<"Data has not yet been retrieved! Try retrieving data first using Option 1 in Main Menu!"<<endl;
                }
                break;
            }
            case 5:
            {
                exit(0);
            }
            default: 
                cout<<"Error, Please select valid option "<< endl;
                cin.clear();
                test = 1;
                break;
            
        }
         
        test = 0;
        
    }
    
    return 0;
     
}