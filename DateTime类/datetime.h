#pragma once
#include"date.h"
#include"time.h"
using namespace std;
#define MaxDateTime (long long)86400*73049LL
class DateTime :public Date,public Time
{

public:
	DateTime();
	DateTime(int, int, int,int,int,int);
	void set(int year, int month , int day ,int hour,int minute,int second);
	void show();

	//转换构造
	DateTime(long long);
	//类型转换
	operator long long()const;
	//+
	friend DateTime operator+(const DateTime&, long long);
	friend DateTime operator+(long long, const DateTime&);
	friend DateTime operator-(const DateTime&, long long);
	friend long long operator-(const DateTime&, const DateTime&);
	//++
	DateTime operator++(int);
	DateTime& operator++();
	//--
	DateTime operator--(int);
	DateTime& operator--();

	//<<、>>
	friend ostream& operator<<(ostream&, const DateTime&);
	friend istream& operator>>(istream&, DateTime&);

	//比较运算符
	bool operator >(const DateTime&);
	bool operator <(const DateTime&);
	bool operator >=(const DateTime&);
	bool operator <=(const DateTime&);
	bool operator ==(const DateTime&);
	bool operator !=(const DateTime&);

};

