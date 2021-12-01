
#pragma once

#include <iostream>
using namespace std;

/* 补全TString类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class TString {
private:
	char* content;
	int   len;
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */
public:
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */
	TString();
	~TString();
	TString(const char*);
	//TString(char*);
	TString(const TString&);
	inline void Delete();

	friend istream& operator >>(istream&,TString&);
	friend ostream& operator <<(ostream&, const TString&);

	const char* c_str()const;

	//TString& operator=(int);
	TString& operator=(const TString&);
	TString& operator=(const char*);

	friend TString operator+(const TString&,const TString&);
	friend TString operator+(const TString&, const char*);
	friend TString operator+(const char*, const TString&);
	friend TString operator+(const TString&, char*);
	friend TString operator+(char*, const TString&);
	friend TString operator+(const TString&, char);
	friend TString operator+(char, const TString&);

	TString& operator+=(const TString&);
	TString& operator+=(const char*);
	TString& operator+=(char*);
	TString& operator+=(char);

	TString operator-(const TString&);
	TString operator-(const char*);
	TString operator-(char*);
	TString operator-(char);

	TString& operator-=(const TString&);
	TString& operator-=(const char*);
	TString& operator-=(char*);
	TString& operator-=(char);

	TString operator*(int);
	TString& operator*=(int);

	TString operator!();

	bool operator<(const TString&);
	bool operator<=(const TString&);
	bool operator>(const TString&);
	bool operator>=(const TString&);
	bool operator==(const TString&);
	bool operator!=(const TString&);

	bool operator<(const char*);
	bool operator<=(const char*);
	bool operator>(const char*);
	bool operator>=(const char*);
	bool operator==(const char*);
	bool operator!=(const char*);

	friend bool operator<(const char*,const TString&);
	friend bool operator<=(const char*, const TString&);
	friend bool operator>(const char*, const TString&);
	friend bool operator>=(const char*, const TString&);
	friend bool operator==(const char*, const TString&);
	friend bool operator!=(const char*, const TString&);

	/*bool operator<(char*);
	bool operator<=(char*);
	bool operator>(char*);
	bool operator>=(char*);
	bool operator==(char*);
	bool operator!=(char*);

	friend bool operator<(char*,const TString&);
	friend bool operator<=(char*, const TString&);
	friend bool operator>(char*, const TString&);
	friend bool operator>=(char*, const TString&);
	friend bool operator==(char*, const TString&);
	friend bool operator!=(char*, const TString&);*/

	int length()const;

	char& operator[](int n);
	
};

/* 如果有其它全局函数需要声明，写于此处 */
int TStringLen(const TString&);
void Strrev(char*&);
/* 如果有需要的宏定义、只读全局变量等，写于此处 */
#pragma once
