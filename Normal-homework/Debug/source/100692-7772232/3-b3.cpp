//7772256 托雷 大数据 7772232 梅超风 
#include <iostream>
using namespace std;
int main()
{
	double a,x;
	int b,c1,c2,c3,c;
	cout<<"输入一个[0 .. 100 亿)之间的浮点数"<<endl;
	cin>>a;
	b=a/100,c1=b/10000000;
	cout<<"十亿位:"<<c1<<endl;
	b=b%10000000,c2=b/1000000;
	cout<<"亿位:"<<c2<<endl;
	b=b%1000000,c3=b/100000;
	cout<<"千万位:"<<c3<<endl;
	b=b%100000,c=b/10000;
	cout<<"百万位:"<<c<<endl;
	b=b%10000,c=b/1000;
	cout<<"十万位:"<<c<<endl;
	b=b%1000,c=b/100;
	cout<<"万位:"<<c<<endl;
	b=b%100,c=b/10;
	cout<<"千位:"<<c<<endl;
	b=b%10,c=b/1;
	cout<<"百位:"<<c<<endl;
	x=a+0.001-c1*1000000000-c2*100000000-c3*10000000;
	b=x*100;
	b=b%10000,c=b/1000;
	cout<<"十位:"<<c<<endl;
	b=b%1000;
	c=b/100;
	cout<<"个位:"<<c<<endl;
	b=b%100;
	c=b/10;
	cout<<"十分位:"<<c<<endl;
	b=b%10;
	c=b/1;
	cout<<"百分位:"<<c<<endl;
	return 0;
}