#include "Group.h"

using namespace std;


//base Group class
//default no. of groups = 3
Group::Group(map<string, Stocks>* data_): stockMapPtr(data_), N_group(3){
}

Group::~Group(){
}

//set no. of groups
void Group::SetN(int n){
    N_group = n;
}

int Group::GetN() const{
    return N_group;
}

//update Stock Map
void Group::UpdateStockMap(map<string, Stocks>* stockMapPtr_){
    stockMapPtr = stockMapPtr_;
}

//get Stock Map
map<string, Stocks>* Group::GetStockMap() const{
    return stockMapPtr;
}

//Create groups
void Group::CreateGroups(){
    vector<Stocks> stockVector;
    for (auto it = stockMapPtr->begin(); it != stockMapPtr.end(); ++it) stockVector.push_back(it->second);
    sort(stockVector.begin(), stockVector.end(), compare, reverse = true);
    
    int NoOfStocks = (int)(stockVector.size()/N_group);
    
    for (int i = 0; i < N_group; ++i){
        for (int j = i * NoOfStocks; j < min(i + NoOfStocks, stockVector.size()); ++j){
            Group_Mapping[i].push_back(stockVector[j].GetTicker());
        }
    }
}

void Group::CreateGroups(int n){
    SetN(n);
    CreateGroups();
}

void Group::CreateGroups(map<string, Stocks>* stockMapPtr_, int n){
    UpdateStockMap(stockMapPtr_);
    CreateGroups(n);
}

//Groupby_Surprise derived class


Groupby_Surprise::Groupby_Surprise(map<string, Stocks>* stockMapPtr_): Group(map<string, Stocks>* stockMapPtr_){
}

Groupby_Surprise::~Groupby_Surprise(){
}

//to be completed

bool Groupby_surprise::compare(const Stocks& a, const Stocks& b) const{
    return (a.GetSurprisePerecent() < b.GetSurprisePerecent());
}




