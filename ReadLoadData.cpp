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
using namespace std;

namespace fre
{

	const char* cIWB3000SymbolFile = "Russell3000EarningsAnnouncements.csv"; 

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
			temp.SetEarningsDate(earnings_date);
			temp.SetEstimatedEarnings(stod(estimated_earnings));
			temp.SetReportedEarnings(stod(reported_earnings));
			temp.SetSurpriseEarnings(stod(surprise_earnings));
			temp.SetSurprisePerecent(stod(surprise_perecent));
			
			//store the stock object in the map
			data[ticker] = temp;
		}
	}	

	int write_data(void* ptr, int size, int nmemb, void* data)
	{
		//the amount of data which libcurl passed to the function
		size_t realsize = size * nmemb;
		
		//change the data type of the "data" variable passed to the function
		Stocks* stock = (Stocks*)data;
		char* stream = (char*)ptr;
		
		String Date;
		Vector Open_price;
		Vector High_price;
		Vector Low_price;
		Vector Close_price;
		Vector Adjusted_close;
		Vector volume;
		
		stringstream sData;
		sData.str(stream);
		
		string sDate, sOpen, sHigh, sLow, sClose, sAdjClose, sVolume;
	
		string line;
		
		while (getline(sData, line)) {
			size_t found = line.find('-');
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
		
		//return the size of data which libcurl passed to not cause any error
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
			string start_date = "2022-11-01";
			string end_date = "2022-11-30";
			string api_token = "638d6a442c56c0.76328612";  // You must replace this API token with yours
	
			
			struct MemoryStruct data;
			data.memory = NULL;
			data.size = 0;
	
			auto itr = stock_map.begin();
			
			for(; itr != stock_map.end(); itr++)
			{
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
				curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
				curl_easy_setopt(handle, CURLOPT_WRITEDATA, ticker);
		
				result = curl_easy_perform(handle);	
				if (result != CURLE_OK)
				{
					// if errors have occured, tell us what is wrong with result
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				}
			}
			
		}	
	
		
		else
		{
			fprintf(stderr, "Curl init failed!\n");
		}
	
		// cleanup since you've used curl_easy_init  
		curl_easy_cleanup(handle);
	
		// release resources acquired by curl_global_init() 
		curl_global_cleanup();
	}

}