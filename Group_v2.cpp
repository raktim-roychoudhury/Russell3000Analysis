#include "Group.h"

using namespace std;


//base Group class
//default no. of groups = 3
//constructor
Group::Group(map<string, Stocks>* data_): stockMapPtr(data_), N_group(3){
}

//destructor
Group::~Group(){
}

//set no. of groups
void Group::SetN(int n){
    N_group = n;
}

//get no. of groups
int Group::GetN() const{
    return N_group;
}

//get group names as a vector of string
String Group::GetGroupNames() const
{
    return GroupNames;
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

//create groups, no. of groups as parameter
void Group::CreateGroups(int n){
    SetN(n);
    CreateGroups();
    GroupName = {"Beat","Meet","Miss"};
}

//create groups, stockMap and no. of groups as parameter
void Group::CreateGroups(map<string, Stocks>* stockMapPtr_, int n){
    UpdateStockMap(stockMapPtr_);
    CreateGroups(n);
}

//overloaded subscript operator to return by groupname
vector<string>& Group::operator[] (const string& groupname) const{
    if (strcmp(groupname, string("Beat")) == true) return Group_Mapping[0];
    else if (strcmp(groupname, string("Meet")) == true) return GroupMapping[1];
    else if (strcmp(groupname, string("Miss")) == true) return GroupMapping[2];
    return NULL;
}

//overloaded subscript operator to return by group index
vector<string>& Group::operator[] (const int& index) const{
    return GroupMapping[index];
}

//Groupby_Surprise derived class

//constructor
Groupby_Surprise::Groupby_Surprise(map<string, Stocks>* stockMapPtr_): Group(map<string, Stocks>* stockMapPtr_){
}

//destructor
Groupby_Surprise::~Groupby_Surprise(){
}

//compare stocks by surprise percent
bool Groupby_surprise::compare(const Stocks& a, const Stocks& b) const{
    return (a.GetSurprisePerecent() < b.GetSurprisePerecent());
}




