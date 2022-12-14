#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include "Stocks.h"

namespace fre{

	vector<string> GenerateDates()
    {
    	set<int> day31({1,3,5,7,8,10,12});
    	set<int> day30({4,6,9,11});
    	
    	vector<string> DateList;
    	
    	int days;
    	
    	for (int i = 1; i < 13; i++)
    	{
    		if(day31.find(i) != day31.end())
    			days = 31;
    		else if(day30.find(i) != day30.end())
    			days = 30;
    		else
    			days = 28;
    		
    		for(int j = 1; j < days+1; j++)
    		{
    			string month;
    			string date;
    			
    			if (i < 10)
    				month = "0"	+ to_string(i);
    			else
    				month = to_string(i);
    			
    			if (j < 10)
    				date = "0" + to_string(j);
    			else
    				date = to_string(j);
    			
    			string temp_date = "2022-" + month + "-" + date;
    			
    			DateList.push_back(temp_date);
    		}
    	}
    	return DateList;
    }

    void Stocks::SetDates(String dateslist)
	{
		auto itr = find(Date.begin(), Date.end(), earnings_date);

		int index = std::distance(Date.begin(), itr);
		start_date = Date[index - N];
		end_date = Date[(index + N)];
		start_index = index - N;
		end_index = index + N;
	}
	
	void Stocks::CalculateReturns()
	{
		float daily_return;
		for (int i = 1; i < Adjusted_close.size(); i++)
		{
			daily_return = Adjusted_close[i]/Adjusted_close[i-1] - (float)1.0;
			pct_returns.push_back(daily_return);
		}
	}
	
	void Stocks::SetN(int N_, String &datelist)
	{
		N = N_;
		SetDates(datelist);
	}
	
}