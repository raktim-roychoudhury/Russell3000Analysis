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
        Table Group_Mapping; //table of tickers
        int N_Group;
        map<string,Stocks>* stockMapPtr;
        Group(map<string,Stocks>* data_);
        virtual ~Group() = 0;
        
    public:
        void SetN(int n);
        int GetN() const;
        
        map<string,Stocks>* GetStockMap() const
        void UpdateStockMap(map<string, Stocks>* stockMapPtr_);
        
        virtual void CreateGroups = 0;
        virtual void CreateGroups(int n) = 0;
        virtual void CreateGroups(map<string, Stocks>* stockMapPtr_, int n) = 0;
};

class Groupby_Surprise: public Group
{
    protected:
        bool cmp_bysurprise(pair<string, Stocks>& a, pair<string, Stocks>& b) const;
    public:
        Groupby_Surprise(map<string,Stocks>* stockMapPtr_);
        ~Groupby_Surprise();
        void CreateGroups();
        void CreateGroups(int n);
        void CreateGroups(map<string,Stocks>* stockMapPtr_, int n);
}