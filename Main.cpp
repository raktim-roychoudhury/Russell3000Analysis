#include "Stocks.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <bits/stdc++.h>
#include <cstring> 
#include <algorithm>

using namespace std;
using namespace fre;

ostream& operator<<(ostream& out, Vector& V)
    {
        for (Vector::iterator itr = V.begin(); itr != V.end(); itr++)
            out << *itr << "   ";
        out << endl;
        return out;
    }

int main()
{

    
    string line;
    ifstream myfile ("Results_Dummy.txt");
    if (myfile.is_open())
    {
        map<string, Stocks> sample;
        int count;
        string key = "";
        Vector date_;
        Vector open_;
        Vector high_;
        Vector low_;
        Vector close_;
        Vector adjp_;
        Vector Vol_;
        int newkey;
        while (getline (myfile,line) )
            {
                
                if (line.length() < 5 && line.length() > 0)
                {
                    // cout << key << endl;
                    newkey = 1;
                    key = line;
                    
                }
                
                else if(line.length() == 0)
                {
                    
                    newkey = 0;
                    sample[key] = Stocks(date_,open_,high_,low_,close_,adjp_,Vol_);
                    close_.clear();
                }
                
                else if (line[0] == 'D')
                    continue;
                else
                    {
                        stringstream ss(line);
                        count = 0;
                        while (ss.good()) 
                        {
                            count++;
                            string substr;
                            getline(ss, substr, ',');
                            if(count == 1)
                                date_.push_back(stof(substr));
                            else if(count == 2)
                                open_.push_back(stof(substr));
                            else if(count == 3)
                                high_.push_back(stof(substr));
                            else if(count == 4)
                                low_.push_back(stof(substr));
                            else if(count == 5)
                                close_.push_back(stof(substr));
                                //cout << stof(substr) << endl;
                            else if(count == 6)
                                adjp_.push_back(stof(substr));
                            else if(count == 7)
                                Vol_.push_back(stof(substr));
                        }
                    }
                
            }
            sample[key] = Stocks(date_,open_,high_,low_,close_,adjp_,Vol_);
            for (map<string, Stocks>::iterator itr = sample.begin(); itr != sample.end(); itr++)
            {
                cout << "hello" << endl;
                vector <double> x = itr->second.GetClose_price(); 
                cout << itr->first << ".:" << x <<endl;
            
            }
        myfile.close();
        
    }
    
    else cout << "Unable to open file"; 
    
    
    return 0;
}
