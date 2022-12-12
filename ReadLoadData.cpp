#include <stdio.h>
#include <cstring>
#include <string> 
#include <iostream>
#include <sstream>  
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>
#include <curl/curl.h>
#include <map>
#include "Stocks.h"
#include "ReadLoadData.h"

using namespace std;

namespace fre
{

	const char* cIWB3000SymbolFile = "Russell3000EarningsAnnouncements.csv"; 

	string FormatDate(string Date)
	{
		std::map<string, string> months = { { "JAN", "01" },{ "FEB", "02" },{ "MAR", "03" },{ "APR", "04" }, { "MAY", "05" },{ "JUN", "06" },{ "JUL", "07" },{ "AUG", "08" },
		{ "SEP", "09" },{ "OCT", "10" },{ "NOV", "11" },{ "DEC", "12" } };
	
		string day = Date.substr(0, 2);
		string month = Date.substr(3, 3);
		for (int i = 0; i < 3; i++)
		{
			month[i] = toupper(month[i]);
		}
		month = months[month];
		string year = Date.substr(7, 9);
	
		string result = "20" + year + "-" + month + "-" + day;
		return result;
	}
	
	//Read the symbols from the CSV file to fetch the data
	void LoadEarnings(map<string, Stocks> &data)
	{
		//declare and open fstream object to read from the excel file
		ifstream fin;
		fin.open(cIWB3000SymbolFile, ios::in);
		
		//declare variables to store the data
		string line, ticker, earnings_date, period_ending, estimated_earnings, reported_earnings, surprise_earnings, surprise_perecent;
		
		int c = 0;
		cout<<"reading..."<<endl;
		while (!fin.eof())
		{
			
			getline(fin, line);
			stringstream sin(line);
			getline(sin, ticker, ',');
			getline(sin, earnings_date, ',');
			getline(sin, period_ending, ',');
			getline(sin, estimated_earnings, ',');
			getline(sin, reported_earnings, ',');
			getline(sin, surprise_earnings, ',');
			getline(sin, surprise_perecent);
			
			if (c == 0)
			{
				c++;
				continue;
			}
			
			//create a temporary stock object to store in the maps
			Stocks temp;
			
			temp.SetTicker(ticker);
			temp.SetEarningsDate(FormatDate(earnings_date));
			temp.SetEstimatedEarnings(stod(estimated_earnings));
			temp.SetReportedEarnings(stod(reported_earnings));
			temp.SetSurpriseEarnings(stod(surprise_earnings));
			temp.SetSurprisePerecent(stod(surprise_perecent));
			
			//store the stock object in the map
			data[ticker] = temp;
		}
	}	

	void write_to_stock(stringstream &sData, Stocks* stock)
	{
		//the amount of data which libcurl passed to the function
		
		String Date;
		Vector Open_price;
		Vector High_price;
		Vector Low_price;
		Vector Close_price;
		Vector Adjusted_close;
		Vector volume;
		
		string sDate, sOpen, sHigh, sLow, sClose, sAdjClose, sVolume;
	
		string line;
		
		while (getline(sData, line)) {
			unsigned long long found = line.find('-');
			if (found != std::string::npos)
			{
				//Date,Open,High,Low,Close,Adjusted_close,Volume
				//2022-11-01,139.5,141.35,138.06,140.89,140.89,1182851
				sDate = line.substr(0, line.find_first_of(','));
				Date.push_back(sDate);
				line.erase(line.find_last_of(','));
				
				sOpen = line.substr(line.find_last_of(',') + 1);
				Open_price.push_back(stod(sOpen));
				line.erase(line.find_last_of(','));
				
				sHigh = line.substr(line.find_last_of(',') + 1);
				High_price.push_back(stod(sHigh));
				line.erase(line.find_last_of(','));
				
				sLow = line.substr(line.find_last_of(',') + 1);
				Low_price.push_back(stod(sLow));
				line.erase(line.find_last_of(','));
				
				sClose = line.substr(line.find_last_of(',') + 1);
				Close_price.push_back(stod(sClose));
				line.erase(line.find_last_of(','));
				
				sAdjClose = line.substr(line.find_last_of(',') + 1);
				Adjusted_close.push_back(stod(sAdjClose));
				line.erase(line.find_last_of(','));
				
				sVolume = line.substr(line.find_last_of('\n') + 1);
				volume.push_back(stod(sVolume));
				
			}
		}
		stock->SetDate(Date);
		stock->SetOP(Open_price);
		stock->SetHP(High_price);
		stock->SetLP(Low_price);
		stock->SetCP(Close_price);
		stock->SetACP(Adjusted_close);
		stock->SetVol(volume);
		stock->CalculateReturns();
		
		
	}
	void* myrealloc(void* ptr, size_t size)
	{
		if (ptr)
			return realloc(ptr, size);
		else
			return malloc(size);
	}
	
	int write_data2(void* ptr, size_t size, size_t nmemb, void* data)
	{
		size_t realsize = size * nmemb;
		struct MemoryStruct* mem = (struct MemoryStruct*)data;
		mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);
		if (mem->memory) {
			memcpy(&(mem->memory[mem->size]), ptr, realsize);
			mem->size += realsize;
			mem->memory[mem->size] = 0;
		}
		return realsize;
	}

	void FetchData(map<string, Stocks> &stock_map)
	{
		vector<string> symbolList;
	
	
		// declaration of an object CURL 
		CURL* handle;
	
		CURLcode result;
	
		
		// set up the program environment that libcurl needs 
		curl_global_init(CURL_GLOBAL_ALL);
		
		// curl_easy_init() returns a CURL easy handle 
		handle = curl_easy_init();
		
		// if everything's all right with the easy handle... 
		if (handle)
		{
			string url_common = "https://eodhistoricaldata.com/api/eod/";
			string start_date = "2022-03-01";
			string end_date = "2022-12-01";
			string api_token = "638d6a442c56c0.76328612";  // You must replace this API token with yours
			
			auto itr = stock_map.begin();
			
			for(; itr != stock_map.end(); itr++)
			{
				struct MemoryStruct data;
				data.memory = NULL;
				data.size = 0;
				
				string symbol = itr->first;
				cout<<"loading "<<symbol<<"...\n";
				string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
				
				//set the url to call the data from
				curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
		
				//adding a user agent
				curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
				
				//create a temporary pointer used to access the stock corresponding to the ticker
				Stocks *ticker = &(itr->second);
				
				
				//store the data in the Stock class using write_data function
				curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
				curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
		
				result = curl_easy_perform(handle);	
				if (result != CURLE_OK)
				{
					// if errors have occured, tell us what is wrong with result
					cout<<"\n\n\nError here\n\n\n";
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				}
				
				stringstream sData;
				sData.str(data.memory);
				write_to_stock(sData, ticker);
				free(data.memory);
			}
			
		}	
	
		
		else
		{
			fprintf(stderr, "Curl init failed!\n");
			//return -1;
		}
	
		
		// cleanup since you've used curl_easy_init  
		curl_easy_cleanup(handle);
	
		// release resources acquired by curl_global_init() 
		curl_global_cleanup();
	}
	
	void write2file(map<string, Stocks> &data)
	{
		cout<<"Writinging..."<<endl;
		ofstream fout;
		fout.open("temp.txt");
		
		auto itr = data.begin();
		for (; itr != data.end() ; itr++)
		{
			Stocks temp = itr->second;
			fout<<itr->first<<", "<<temp.GetTicker()<<", " <<temp.GetEarningsDate()<<", "<<temp.GetEstimatedEarnings()<<", "<<temp.GetSurprisePerecent()<<endl;
			fout<<"Data from EOD: \n";
			
			Vector adj = temp.GetAdjusted_close();
			
			fout<<"Adj Close: "<<adj.size()<<endl;
			for(int i = 0; i < adj.size(); i++)
			{
				fout<<adj[i]<<" ";
			}
			
			Vector pct_returns = temp.GetReturns();
			
			fout<<endl<<"Percent returns: "<<pct_returns.size()<<endl;
			for(int i = 0; i < pct_returns.size(); i++)
			{
				fout<<pct_returns[i]<<" ";
			}
			
			fout<<endl<<endl;
		}
	}

}