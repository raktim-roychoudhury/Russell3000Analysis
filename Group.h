#pragma once
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include "Stocks.h"
using namespace std;

typedef vector<double> Vector;
typedef vector<vector<double>> Matrix;
typedef vector<vector<string>> Table;

class Group
{
    protected:
        //data members
        Table Group_Mapping; //table of tickers
        map<string,Stocks>* stockMapPtr;
        int N_Group;
        
        //constructor
        Group(map<string,Stocks>* data_);
        
        virtual bool compare(const Stocks& a,const Stocks& b) const = 0;
        virtual ~Group() = 0;
        
    public:
        void SetN(int n);
        int GetN() const;
        
        map<string,Stocks>* GetStockMap() const
        void UpdateStockMap(map<string, Stocks>* stockMapPtr_);
        
        void CreateGroups;
        void CreateGroups(int n);
        void CreateGroups(map<string, Stocks>* stockMapPtr_, int n);
};

class Groupby_Surprise: public Group
{
    //comparator to sort stocks by attribute
    protected:
        bool compare(const Stocks& a,const Stocks& b) const;
        
    public:
        Groupby_Surprise(map<string,Stocks>* stockMapPtr_);
        ~Groupby_Surprise();
}