#include "datetime.h"

DateTime::DateTime():Date(),Time()
{
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second):Date(year,month,day),Time(hour,minute,second)
{
}

void DateTime:: set(int year, int month, int day, int hour, int minute, int second)
{
	Date::set(year,month,day);
	Time::set(hour,minute,second);
}

void DateTime::show()
{
	cout << year << "-" << setw(2) << setfill('0') <<month << "-" << setw(2) << setfill('0') <<day << " ";
	cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << ":" << setw(2) << setfill('0') << second << endl;
}

//转换构造
DateTime::DateTime(long long X):Time((int)((X) % MaxSecond)), Date(X / MaxSecond + 1)//(+1)满一天后已经跳到下一天了
{
	if (X <= 0 || X >= MaxDateTime) {
		this->year = 1900;
		this->month = 1;
		this->day = 1;
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
	}
}
//类型转换
DateTime::operator long long()const
{
	long long ans = 0;
	ans += (int)Time(this->hour, this->minute, this->second);
	ans += (long long)(((long long)(int)Date(this->year, this->month, this->day)-1)*(long long)MaxSecond);//（-1）比如1900-01-02在Date中为2，但实际上只过了1天
	return ans;
}
//+
DateTime operator+(const DateTime&a, long long x)
{
	long long s = (long long)a + (long long)x;
	if (s < 0)
		s = (long long)((long long)MaxDateTime + s);
	if (s >= (long long)MaxDateTime)
		s %= (long long)MaxDateTime;
	//cout << s << "??" << endl;
	DateTime ans = DateTime(s);
		return ans;
}

DateTime operator+(long long x, const DateTime&a)
{
	return operator+(a, x);
}

DateTime operator-(const DateTime&a, long long x)
{
	return operator+(a, -x);
}

long long operator-(const DateTime&a, const DateTime&b)
{
	DateTime a1(a), b1(b);
	return(long long)a1 - (long long)b1;
}

//++
DateTime DateTime::operator++(int)
{
	long long s = (long long)*this;
	(*this)=DateTime(s+1);
	DateTime ans(s);
	return ans;
}

DateTime& DateTime::operator++()
{
	long long s = (long long)*this;
	(*this)=DateTime(s+1);
	return *this;
}

//--
DateTime DateTime::operator--(int)
{
	long long s = (long long)*this;
	(*this) = DateTime(s - 1);
	DateTime ans(s);
	return ans;
}

DateTime& DateTime::operator--()
{
	long long s = (long long)*this;
	(*this) = DateTime(s - 1);
	return *this;
}

//<<、>>
ostream& operator<<(ostream&out, const DateTime&a)
{
	out<<a.year<<"-"<<setw(2)<<setfill('0') << a.month << "-" <<setw(2)<<setfill('0') << a.day << " "
		<< setw(2) << setfill('0') << a.hour << ":" << setw(2) << setfill('0') 
		<< a.minute << ":" << setw(2) << setfill('0') << a.second << endl;
	return out;
}

istream& operator>>(istream&in, DateTime&a)
{
	int year, month, day, hour, minute, second;
	in >> year >> month >> day>>hour>>minute>>second;
	a.set(year,month,day,hour,minute,second);
	return in;
}

//比较运算符
bool DateTime::operator >(const DateTime&a)
{
	DateTime a1 = a;
	return (long long)*this > (long long)a1;
}

bool DateTime::operator <(const DateTime&a)
{
	DateTime a1 = a;
	return (long long)*this < (long long)a1;
}

bool DateTime::operator >=(const DateTime&a)
{
	DateTime a1 = a;
	return (long long)*this >= (long long)a1;
}

bool DateTime::operator <=(const DateTime&a)
{
	DateTime a1 = a;
	return (long long)*this <= (long long)a1;
}

bool DateTime::operator ==(const DateTime&a)
{
	DateTime a1 = a;
	return (long long)*this == (long long)a1;
}

bool DateTime::operator !=(const DateTime&a)
{
	DateTime a1 = a;
	return (long long)*this != (long long)a1;
}
