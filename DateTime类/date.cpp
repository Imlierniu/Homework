#include "date.h"

Date::Date()
{
	year = 1900;
	month = 1;
	day = 1;
}

Date::Date(int y, int m, int d)
{
	if (y > 2099 || y < 1900)
		y = 1900;
	this->year = y;

	if (m < 1 || m>12)
		m = 1;
	this->month = m;

	if (is_run(y)) {
		if (d<1 || d>mon2[m - 1])
			d = 1;
	}
	else {
		if (d<1 || d>mon1[m - 1])
			d = 1;
	}
	this->day = d;
}

Date::Date(int x)//转换构造
{
	int y = 1900, m = 1, d = 1;
	
	if (x <= 1||x>73049) {
		year = 1900;
		month = 1;
		day = 1;
		return;
	}
	else if (x > 73049) {//非法值默认都为1900.1.1？？
		year = 2099;
		month = 12;
		day = 31;
		return;
	}
	else {
		while (x > 366) {
			if (is_run(y))
				x -= 366;
			else
				x -= 365;
			y++;
		}
		if (x <= 0) {
			year = y;
			month = m;
			day = d;
			return;
		}
		if ((x == 366 && !is_run(y))) {
			y++;
			x = 1;
		}
		else {
			if (is_run(y)) {
				while (x > mon2[m - 1]) {
					x -= mon2[m - 1];
					m++;
				}
			}
			else {
				while (x > mon1[m - 1]) {
					x -= mon1[m - 1];
					m++;
				}
			}
		}
	}
	year = y;
	month = m;
	day = x;
}


void Date::set(int y, int m, int d)
{
	if (!y) {
		y = 1900;
		this->year = 1900;
	}
	else if (y) {
		if ((y > 2099 || y < 1900))
			y = 1900;
		this->year = y;
	}

	if (!m) {
		m = 1;
		this->month = 1;
	}
	else if (m) {
		if (m > 12)
			m = 1;
		this->month = m;
	}

	if (is_run(y)) {
		if (!d||d > mon2[m - 1])
			d = 1;
		this->day = d;
	}
	else {
		if (!d||d > mon1[m - 1])
			d = 1;
		this->day = d;

	}

}

void Date::get(int& a, int& b, int& c)
{
	a = year;
	b = month;
	c = day;
}

void Date::show()
{
	cout << year << "年" << month << "月" << day << "日" << endl;
}

//类型转换
Date:: operator int()const
{
	int days = day;
	for (int m = month - 1; m >= 1; m--) {
		if (is_run(year))
			days += mon2[m - 1];
		else
			days += mon1[m - 1];

	}
	for (int y = year - 1; y >= 1900; y--) {
		if (is_run(y))
			days += 366;
		else
			days += 365;
	}
	return days;
}
//+
Date operator+(const Date& a, int x)
{
	int days;
	Date ans, a1 = a;
	days = (int)a1 + x;
	if (days < 0)
		days = 73049 - days;
	if(days>73049)
		days %= 73049;
	ans = Date(days);
	return ans;
}

Date operator+(int x, const Date& a)
{
	int days;
	Date ans, a1 = a;
	days = (int)a1 + x;
	if (days < 0)
		days = 73049 - days;
	if (days > 73049)
		days %= 73049;
	ans = Date(days);
	return ans;
}

Date operator-(const Date& a, int x)
{
	int days;
	Date ans, a1 = a;
	days = (int)a1 - x;
	if (days <= 0)//由Date+int获得的0代表2099.12.31 而构造函数中0代表1900.1.1
		days += 73049;
	if (days > 73049)
		days %= 73049;
	ans = Date(days);
	return ans;
}

int operator-(const Date& a, const Date& b)
{
	Date a1 = a, b1 = b;
	return int(a) - int(b1);
}

//++
Date Date:: operator++(int)
{
	Date ans = *this;
	if (int(*this) >= 73049)
		return ans;
	*this = Date(int(ans) + 1);
	return ans;
}

Date& Date::operator++()
{
	if (int(*this) >= 73049)
		return *this;
	*this = Date(int(*this) + 1);
	return *this;
}
//--
Date Date:: operator--(int)
{
	Date ans = *this;
	if (int(*this) <= 1)
		return ans;
	*this = Date(int(ans) - 1);
	return ans;
}

Date& Date:: operator--()
{
	if (int(*this) <= 1)
		return *this;
	*this = Date(int(*this) - 1);
	return *this;
}


//<<、>>
ostream& operator<<(ostream& out, const Date& d)
{
	out << d.year << "年" << d.month << "月" << d.day << "日" << endl;
	return out;
}

istream& operator>>(istream& in, Date& date)
{
	int y, m, d;
	in >> y >> m >> d;
	date.set(y, m, d);

	return in;
}

//比较运算符
bool Date::operator >(const Date& a)
{
	Date a1 = a;
	return int(*this) > int(a1) ? 1 : 0;
}

bool Date::operator <(const Date& a)
{
	Date a1 = a;
	return int(*this) < int(a1) ? 1 : 0;
}

bool Date::operator >=(const Date& a)
{
	Date a1 = a;
	return int(*this) >= int(a1) ? 1 : 0;
}

bool Date::operator <=(const Date& a)
{
	Date a1 = a;
	return int(*this) <= int(a1) ? 1 : 0;
}

bool Date::operator ==(const Date& a)
{
	Date a1 = a;
	return int(*this) == int(a1) ? 1 : 0;
}

bool Date::operator !=(const Date& a)
{
	Date a1 = a;
	return int(*this) != int(a1) ? 1 : 0;
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */
bool is_run(int year)
{
	if (!year)
		return 0;
	if (year % 400 == 0 || ((year % 4) == 0 && year % 100))
		return 1;
	return 0;
}
