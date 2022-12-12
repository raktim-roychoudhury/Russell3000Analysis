#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <bits/stdc++.h>
#include <cstring> 
#include <algorithm>

#include "Stocks.h"
#include "ReadLoadData.h"

using namespace std;
using namespace fre;

ostream& operator<<(ostream& out, Vector& V)
    {
        for (Vector::iterator itr = V.begin(); itr != V.end(); itr++)
            out << *itr << "   ";
        out << endl;
        return out;
    }

void SetN(int N, map<string, Stocks> &stock_map, String &DateList)
{
    
    string ticker;
    Stocks curr_stock;
    
    auto itr = stock_map.begin();
    
    for(; itr != stock_map.end(); itr++)
    {
        ticker = itr->first;
        curr_stock = itr->second; 
        //set N, starting date and ending date for each stock
        curr_stock.SetN(N, DateList);
    }
}


int main()
{
    map<string, Stocks> GlobalStockMap;
    Stocks Russel;
    GlobalStockMap["IWV"] = Russel;
    LoadEarnings(GlobalStockMap);
    
    String DateList = GenerateDates();
    SetN(30, GlobalStockMap, DateList);
    
    FetchData(GlobalStockMap);
    write2file(GlobalStockMap);
    return 0;
}
