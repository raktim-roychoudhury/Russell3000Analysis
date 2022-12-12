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
typedef vector<string> String;

class Group
{
    protected:
        //data members
        Table Group_Mapping; //table of tickers
        map<string,Stocks>* stockMapPtr;
        int N_Group;
        String GroupNames; //vector of group names {"Beat","Meet","Miss"}
        
        //constructor
        Group(map<string,Stocks>* data_);
        
        //pure virtual compare function to sort stocks by attribute
        virtual bool compare(const Stocks& a,const Stocks& b) const = 0;
        
        //destructor
        virtual ~Group() = 0;
        
    public:
        //get, set number of groups
        void SetN(int n);
        int GetN() const;
        String GetGroupNames() const;
        
        //get, set stock map
        map<string,Stocks>* GetStockMap() const
        void UpdateStockMap(map<string, Stocks>* stockMapPtr_);
        
        //create Groups
        void CreateGroups;
        void CreateGroups(int n);
        void CreateGroups(map<string, Stocks>* stockMapPtr_, int n);
        
        //overloaded subscript operator to return by group name
        vector<string>& operator[] (const string& groupname) const;
        vector<string>& operator[] (const int& index) const;
};

class Groupby_Surprise: public Group
{
    //comparator to sort stocks by attribute
    protected:
        bool compare(const Stocks& a,const Stocks& b) const;
        
    public:
        //constructor
        Groupby_Surprise(map<string,Stocks>* stockMapPtr_);
        
        //destructor
        ~Groupby_Surprise();
}