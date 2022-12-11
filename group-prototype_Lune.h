#pragma once
#include <vector>
#include <string>
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
        map<string,Stocks>* dataPtr;
        
        Group(map<string,Stocks>* data_);
        virtual ~Group() = 0;
        
    public:
        virtual void SetGroup(int n) = 0;
        //string GetGroup(const string& ticker) const; //Do we need this??
        int GetN() const;
};

class Groupby_Surprise: public Group
{
    public:
        Groupby_Surprise(map<string,Stocks>* dataPtr_);
        ~Groupby_Surprise();
        void SetGroup(int n);
        map<string,Stocks>* GetdataPtr() const;
}

Group::Group(map<string,Stocks>* dataPtr_): dataPtr(dataPtr_) {}

Groupby_Surprise::Groupby_Surprise(map<string,Stocks>* dataPtr_): Group(dataPtr_) {}
Groupby_Surprise::~Groupby_Surprise(){}
void Groupby_Surprise::SetGroup(int n)
{
    N_Group = n;
    Group_Mapping.resize(N_Group);
    //Store Tickers in Matrix
}