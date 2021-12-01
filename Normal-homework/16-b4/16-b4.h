/* 1752846 边泽轩 车辆工程（汽车）*/
#pragma once

#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */
bool is_run(int year);
/* 如果有需要的宏定义、只读全局变量等，写于此处 */
const int mon1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const int mon2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };

/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date {
private:
	int year;
	int month;
	int day;
	/* 不允许添加数据成员 */
public:
	/* 根据需要定义所需的成员函数、友元函数等(不允许添加数据成员) */
	Date();
	Date(int, int, int);
	void set(int y,int m=1,int d=1);
	void get(int&, int&, int&);
	void show();

	//转换构造
	Date(int);
	//类型转换
	operator int()const;
	//+
	friend Date operator+(const Date&,int);
	friend Date operator+(int, const Date&);
	friend Date operator-(const Date&, int);
	friend int operator-(const Date&, const Date&);
	//++
	Date operator++(int);
	Date& operator++();
	//--
	Date operator--(int);
	Date& operator--();

	//<<、>>
	friend ostream& operator<<(ostream&, const Date&);
	friend istream& operator>>(istream&,  Date&);

	//比较运算符
	bool operator >(const Date&);
	bool operator <(const Date&);
	bool operator >=(const Date&);
	bool operator <=(const Date&);
	bool operator ==(const Date&);
	bool operator !=(const Date&);

};

