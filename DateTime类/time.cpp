#include "time.h"

Time::Time()
{
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(int h, int m, int s)
{
	if (h >= 24 || h < 0)
		h = 0;
	if (m >= 60 || m < 0)
		m = 0;
	if (s >= 60 || s < 0)
		s = 0;
	this->hour = h;
	this->minute = m;
	this->second = s;
}

void Time::set(int h, int m , int s )
{
	if (h >= 24 || h < 0)
		h = 0;
	if (m >= 60 || m < 0)
		m = 0;
	if (s >= 60 || s < 0)
		s = 0;
	this->hour = h;
	this->minute = m;
	this->second = s;
}

void Time::show()
{
	cout<<setw(2)<<setfill('0')<<hour<< ":" << setw(2) << setfill('0')<< minute << ":" << setw(2) << setfill('0')<<second << endl;
}

//转换构造
Time::Time(int x)
{
	if (x <= 0||x>=MaxSecond) {
		this->hour = 0;
		this->minute = 0;
		this->second= 0;
		return;
	}
	else {
		this->hour = x / 3600;
		x %= 3600;
		this->minute = x / 60;
		x %= 60;
		this->second = x;
	}
	
}
//类型转换
Time::operator int()const
{
	int ans = 0;
	ans += this->hour * 3600 + this->minute * 60 + this->second;
	return ans;
}
//+
Time operator+(const Time&a, int x)
{
	int Second = 0;
	Second = int(a) + x;
	if (Second < 0)
		Second = MaxSecond + Second;
	if (Second >=MaxSecond)
		Second %= MaxSecond;
	Time ans = Time(Second);
	return ans;
}

Time operator+(int x, const Time&a)
{
	int Second = 0;
	Second = int(a) + x;
	if (Second < 0)
		Second = MaxSecond + Second;
	if (Second >=MaxSecond)
		Second %= MaxSecond;
	Time ans = Time(Second);
	return ans;
}

Time operator-(const Time&a, int x)
{
	int Second = 0;
	Second = int(a) - x;
	if (Second < 0)
		Second = MaxSecond + Second;
	if (Second >=MaxSecond)
		Second %= MaxSecond;
	Time ans = Time(Second);
	return ans;
}

int operator-(const Time&a, const Time&b)
{
	Time a1 = a, b1 = b;
	return (int)a1 - (int)b1;
}

//++
Time Time:: operator++(int)//后置
{
	Time ans = *this;
	*this =Time(int(ans) + 1);//在没有动态内存申请的情况下，不需要定义operator=赋值重载了
	return ans;
}

Time& Time::operator++()
{
	*this = Time(int(*this) + 1);
	return *this;
}
//--
Time Time::operator--(int)
{
	Time ans = *this;
	*this = Time(int(ans) - 1);//在没有动态内存申请的情况下，不需要定义operator=赋值重载了
	return ans;
}

Time& Time::operator--()
{
	*this = Time(int(*this) - 1);
	return *this;
}

//<<、>>
ostream& operator<<(ostream&out, const Time&a)
{
	out <<setw(2)<<setfill('0')<< a.hour << ":" << setw(2) << setfill('0') << a.minute << ":" << setw(2) << setfill('0') << a.second  << endl;
	return out;
}

istream& operator>>(istream&in, Time&a)
{
	int h, m, s;
	in >> h >> m >> s;
	a.set(h, m, s);
	return in;
}

//比较运算符
bool Time::operator >(const Time&a)
{
	Time a1 = a;
	return (int)*this > (int)a1;
}

bool Time::operator <(const Time&a)
{
	Time a1 = a;
	return (int)*this < (int)a1;
}

bool Time::operator >=(const Time&a)
{
	Time a1 = a;
	return (int)*this >= (int)a1;
}

bool Time::operator <=(const Time&a)
{
	Time a1 = a;
	return (int)*this <= (int)a1;
}

bool Time::operator ==(const Time& a)
{
	Time a1 = a;
	return (int)*this == (int)a1;
}

bool Time::operator !=(const Time& a)
{
	Time a1 = a;
	return (int)*this != (int)a1;
}