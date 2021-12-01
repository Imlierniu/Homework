
#pragma once

#include <iostream>
using namespace std;

/* ��ȫTString��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class TString {
private:
	char* content;
	int   len;
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
public:
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
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

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
int TStringLen(const TString&);
void Strrev(char*&);
/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
#pragma once
