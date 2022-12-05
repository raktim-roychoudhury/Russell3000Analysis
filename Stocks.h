#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace fre
{
	typedef vector<double> Vector;
	typedef vector<Vector> Matrix;
	
	class Stocks
	{
	  protected:
		Vector Date;
		Vector Open_price;
		Vector High_price;
		Vector Low_price;
		Vector Close_price;
		Vector Adjusted_close;
		Vector volume;
		Matrix Stock_info;
		
		double reported_earnings;
		double estimated_earnings;
		double surprise_earnings;
		double surprise_perecent;
		string earnings_date;
		string ticker;
		
		int N;
		
	  public:
		Stocks(){}
		Stocks(Vector d_, Vector op_, Vector hp_, Vector lp_, Vector cp_, Vector acp_, Vector v_ ):Date(d_), Open_price(op_), High_price(hp_), Low_price(lp_), Close_price(cp_), Adjusted_close(acp_), volume(v_) {}
		Vector GetDate() const { return Date; }
        Vector GetOpen_price() const { return Open_price; }
		Vector GetHigh_price() const { return High_price; }
		Vector GetLow_price() const { return Low_price; }
		Vector GetClose_price() const { return Close_price; }
		Vector GetAdjusted_close() const { return Adjusted_close; }
		Vector Getvolume() const { return volume; }
		
		void SetOP(const Vector & OP) { Open_price = OP; }
        void SetHP(const Vector& HP) { High_price = HP; }
        void SetLP(const Vector& LP) { Low_price = LP; }
        void SetCP(const Vector& CP) { Close_price = CP; }
        void SetACP(const Vector& ACP) { Adjusted_close = ACP; }
        void SetVol(const Vector& Vol) { volume = Vol; }
        
        void SetReportedEarnings(const double& re) { reported_earnings = re;}
        void SetEstimatedEarnings(const double& ee) { estimated_earnings = ee;}
        void SetSurpriseEarnings(const double& se) { surprise_earnings = se;}
        void SetSurprisePerecent(const double& sp) { surprise_perecent = sp;}
        void SetTicker(const string& ticker_) { ticker = ticker_}
        void SetEarningsDate(const string& earnings_date_) { earnings_date = earnings_date_;}
	};


}
