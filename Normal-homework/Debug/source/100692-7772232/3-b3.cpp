//7772256 ���� ������ 7772232 ÷���� 
#include <iostream>
using namespace std;
int main()
{
	double a,x;
	int b,c1,c2,c3,c;
	cout<<"����һ��[0 .. 100 ��)֮��ĸ�����"<<endl;
	cin>>a;
	b=a/100,c1=b/10000000;
	cout<<"ʮ��λ:"<<c1<<endl;
	b=b%10000000,c2=b/1000000;
	cout<<"��λ:"<<c2<<endl;
	b=b%1000000,c3=b/100000;
	cout<<"ǧ��λ:"<<c3<<endl;
	b=b%100000,c=b/10000;
	cout<<"����λ:"<<c<<endl;
	b=b%10000,c=b/1000;
	cout<<"ʮ��λ:"<<c<<endl;
	b=b%1000,c=b/100;
	cout<<"��λ:"<<c<<endl;
	b=b%100,c=b/10;
	cout<<"ǧλ:"<<c<<endl;
	b=b%10,c=b/1;
	cout<<"��λ:"<<c<<endl;
	x=a+0.001-c1*1000000000-c2*100000000-c3*10000000;
	b=x*100;
	b=b%10000,c=b/1000;
	cout<<"ʮλ:"<<c<<endl;
	b=b%1000;
	c=b/100;
	cout<<"��λ:"<<c<<endl;
	b=b%100;
	c=b/10;
	cout<<"ʮ��λ:"<<c<<endl;
	b=b%10;
	c=b/1;
	cout<<"�ٷ�λ:"<<c<<endl;
	return 0;
}