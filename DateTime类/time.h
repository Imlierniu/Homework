#pragma once
#include <iostream>
#include<iomanip>
using namespace std;
#define MaxSecond 86400
class Time
{
protected:
	int hour;
	int minute;
	int second;
public:
	Time();
	Time(int, int, int);
	void set(int y, int m=0 , int d=0 );
	//void get(int&, int&, int&);
	void show();

	//转换构造
	Time(int);
	//类型转换
	operator int()const;
	//+
	friend Time operator+(const Time&, int);
	friend Time operator+(int, const Time&);
	friend Time operator-(const Time&, int);
	friend int operator-(const Time&, const Time&);
	//++
	Time operator++(int);
	Time& operator++();
	//--
	Time operator--(int);
	Time& operator--();

	//<<、>>
	friend ostream& operator<<(ostream&, const Time&);
	friend istream& operator>>(istream&, Time&);

	//比较运算符
	bool operator >(const Time&);
	bool operator <(const Time&);
	bool operator >=(const Time&);
	bool operator <=(const Time&);
	bool operator ==(const Time&);
	bool operator !=(const Time&);
};

