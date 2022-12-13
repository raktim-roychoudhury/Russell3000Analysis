#pragma once
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include "Stocks.h"
using namespace std;
using namespace fre;

typedef vector<double> Vector;
typedef vector<vector<double>> Matrix;
typedef vector<vector<string>> Table;
typedef map<string,Stocks> Map;

class Group
{
    protected:
        //data members
        Table Group_Mapping; //table of tickers
        Map* stockMapPtr;
        int N_group;
        vector<string> Group_Names;
        
        //constructor
        Group(Map* data_);
        
        //pure virtual compare function to sort stocks by attribute
        virtual bool compare(Stocks& a,Stocks& b) = 0;
        
        //destructor
        virtual ~Group() = 0;
        
    public:
        //get, set number of groups
        void SetN(int n);
        int GetN() const;
        
        //get, set group names
        void SetGroupNames(vector<string>& names);
        vector<string> GetGroupNames() const;
        
        //get, set stock map
        Map* GetStockMap() const;
        void UpdateStockMap(Map* stockMapPtr_);
        
        //get Group Vector Pointer
        Table* GetGroup_Mapping();
        
        //create Groups
        void CreateGroups();
        void CreateGroups(int n);
        void CreateGroups(Map* stockMapPtr_, int n);
        
        //overloaded subscript operator to return by group name
        vector<string>& operator[] (const string& groupname);
};

class Groupby_Surprise: public Group
{
    //comparator to sort stocks by attribute
    protected:
        bool compare(Stocks& a,Stocks& b);
        
    public:
        //constructor
        Groupby_Surprise(Map* stockMapPtr_);
        
        //destructor
        ~Groupby_Surprise();
};