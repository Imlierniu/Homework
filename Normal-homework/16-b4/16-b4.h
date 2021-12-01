/* 1752846 ������ �������̣�������*/
#pragma once

#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
bool is_run(int year);
/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
const int mon1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const int mon2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };

/* ��ȫDate��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class Date {
private:
	int year;
	int month;
	int day;
	/* ������������ݳ�Ա */
public:
	/* ������Ҫ��������ĳ�Ա��������Ԫ������(������������ݳ�Ա) */
	Date();
	Date(int, int, int);
	void set(int y,int m=1,int d=1);
	void get(int&, int&, int&);
	void show();

	//ת������
	Date(int);
	//����ת��
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

	//<<��>>
	friend ostream& operator<<(ostream&, const Date&);
	friend istream& operator>>(istream&,  Date&);

	//�Ƚ������
	bool operator >(const Date&);
	bool operator <(const Date&);
	bool operator >=(const Date&);
	bool operator <=(const Date&);
	bool operator ==(const Date&);
	bool operator !=(const Date&);

};

