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
//#include ".h"         //header files 
//#include ".h"
//#include ".h"
#include "ReadLoadData.h"
#include "Stocks.h"
#include "Group.h"
using namespace std;
using namespace std::chrono;
//using namespace 

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


int main() 
{
    
    int temp,x,group, test =0;  // menu option and number of days 
    string tick;
    double N=0;
    
    map<string, Stocks> stockData;
    
    LoadEarnings(&stockData);
    
    Groupby_Surprise group(stockData);
    group.CreateGroups();
    Table* groupTable = group.GetGroup_Mapping();
    
    //temporary vector 
    vector<double> v;
    v.insert(v.begin(),2.0);
    v.push_back(3.0);
    v.push_back(4.0);
    v.push_back(5.0);
    
    // create object of bootstrap or our stock object with our data Bootstrap test;
    
    while(true)
    {
    cout<<"\t \t \t :Menu: "<<endl;
    cout<<"1) Enter N to retrieve 2N+1 historical prices for all stocks."<<endl;
    cout<<"2) Pull information for one stock from one group. "<<endl;
    cout<<"3) Display AAR, AAR-std, CAAR, CAAR-std for one group. "<<endl;
    cout<<"4) Display gnuplot plot for CAAR of all 3 groups.  "<<endl;
    cout<<"5) Exit program "<<endl<<endl;
    cout<<"Please select appropriate option number:  "<<endl;;
    cin>>x;
   
    
    // switch structure for each option
   
    
        switch(x)
        {
            case 1:
            {
                while(test==0)
                {
                    cout<<"Enter N value between 60 and 90: "<<endl;
                    cin>>N;
                    int integer1 = (int) N;
                    if (integer1 != N)
                    {
                        cout<<"Error, please enter an integer value error"<<endl;
                        cin.clear();
                    }
                    else if(N>=60 && N<=90 && !cin.fail())  // n is an int 
                    {
                        cout<<"Check for case working cout "<<endl;
                        // object.load data for stocks
                        auto start = high_resolution_clock::now();
                        // object.operations to return historical data
                        print_v(v);
                        auto stop = high_resolution_clock::now();
                        auto duration = duration_cast<seconds>(stop - start);
                        // object.display
                        cout<<"function execution time in seconds: "<<duration.count()<<endl;
                        test =1;
                        //break;
                    }
                    else
                    {
                        cout<<"Error, Enough data points not found. Please select N above 60 and below 90 "<<endl;
                        cin.clear();
                        //test =1;
                        //cin.ignore(10000,'\n');
                        //break;
                    }
                }
                break;
            }
            case 2:
            {   
                if (N>=60 && N<=90)
                {
                    while(test==0)
                    {
                        cout<<"Please provide ticker of stock: "<<endl;
                        cin>> tick;
                        //check each group
                        // if(object.missgroupcount(tick) == 1) {object.missgroupprint(tick);}
                        // elseif(object.meetgroupcount(tick) == 1) {object.meetgroupprint(tick);}
                        // elseif(object.beatgroupcount(tick) == 1) {object.beatgroupprint(tick);}   
                        // else { cout<< " Error, Ticker not found!. Enter valid ticker <<endl;"}
                        if(!cin.fail())
                        {
                            cout<<"check case 2 working "<<tick<<endl;
                            print_v(v);
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
                if(N>=60 && N<=90)
                {
                    while(test==0)
                    {
                        cout<<"1) Missed \t 2) Beat \t 3) Meet"<<endl;
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
                            cout<<" Missed Estimate Group summary "<<endl;
                            cout<<" Average Abnormal Returns (AAR) "<<endl;
                            //print object.missaar
                            print_v(v);
                        
                            cout<<" Average Abnormal Returns standard deviation (AAR-std) "<<endl;
                            //print object.missaarstd
                            print_v(v);
                
                            cout<<" Cumilative Average Abnormal Returns (CAAR) "<<endl;
                            //print object.misscarr
                            print_v(v);
                
                            cout<<" Cumilative Average Abnormal Returns (CAAR-std) "<<endl;
                            //print object.misscaarstd
                            print_v(v);
                            test = 1;
                        }
                        else if(group == 2)
                        {
                            cout<<" Beat Estimate Group summary "<<endl;
                            cout<<" Average Abnormal Returns (AAR) "<<endl;
                            //print object.missaar
                            print_v(v);
                    
                            cout<<" Average Abnormal Returns standard deviation (AAR-std) "<<endl;
                            //print object.missaarstd
                            print_v(v);
                        
                            cout<<" Cumilative Average Abnormal Returns (CAAR) "<<endl;
                            //print object.misscarr
                            print_v(v);
                        
                            cout<<" Cumilative Average Abnormal Returns (CAAR-std) "<<endl;
                            //print object.misscaarstd
                            print_v(v);
                            test = 1;
                        }
                        else if(group == 3)
                        {
                            cout<<" Meet Estimate Group summary "<<endl;
                            cout<<" Average Abnormal Returns (AAR) "<<endl;
                            //print object.missaar
                            print_v(v);
                
                            cout<<" Average Abnormal Returns standard deviation (AAR-std) "<<endl;
                            //print object.missaarstd
                            print_v(v);
                        
                            cout<<" Cumilative Average Abnormal Returns (CAAR) "<<endl;
                            //print object.misscarr
                            print_v(v);
                        
                            cout<<" Cumilative Average Abnormal Returns (CAAR-std) "<<endl;
                            //print object.misscaarstd
                            print_v(v);
                            test = 1;
                        }
                        else 
                        {
                            cout<<"Error, Please select valid option number"<<endl;
                        }
                    
                    }
                    
                }
                
                else
                {
                    cout<<"Data has not yet been retrieved! Try retrieving data first using Option 1 in Main Menu!"<<endl;
                }
                break;
            }
            case 4:
            {   
                if(N>=60 && N<=90)
                {
                    cout<<"CAAR for all 3 groups "<<endl;
                    //object.plot
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