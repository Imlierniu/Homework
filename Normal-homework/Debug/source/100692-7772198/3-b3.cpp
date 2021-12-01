/*7772214 陆冠英 信息类18班*/

#include<iostream>
using namespace std;
int main()
{
	double a,b0,d0;
	int c1=10,c2=100,c3=1000,c4=10000,c5=100000,
		b,b1,b2,b3,b4,b5,b6,d,d1,d2,d3,d4,d5,d6;
	cout<<"请键盘输入一个[0 .. 100 亿)之间的最多两位小数的浮点数"<<endl;
	cin>>a;
	b0=a/10000,b=int(b0);
    b1=(b-b%c5)/c5;
	b2=(b%c5-b%c5%c4)/c4;
	b3=(b%c5%c4-b%c5%c4%c3)/c3;
	b4=(b%c5%c4%c3-b%c5%c4%c3%c2)/c2;
	b5=(b%c5%c4%c3%c2-b%c5%c4%c3%c2%c1)/c1;
	b6=b%c5%c4%c3%c2%c1;
	d0=(a+0.001-10000*b)*100,d=int(d0);
	d1=(d-d%c5)/c5;
	d2=(d%c5-d%c5%c4)/c4;
	d3=(d%c5%c4-d%c5%c4%c3)/c3;
	d4=(d%c5%c4%c3-d%c5%c4%c3%c2)/c2;
	d5=(d%c5%c4%c3%c2-d%c5%c4%c3%c2%c1)/c1;
	d6=d%c5%c4%c3%c2%c1;
    cout<<"十亿位:"<<b1<<endl;
	cout<<"亿位:"<<b2<<endl;
	cout<<"千万位:"<<b3<<endl;
	cout<<"百万位:"<<b4<<endl;
	cout<<"十万位:"<<b5<<endl;
	cout<<"万位:"<<b6<<endl;
	cout<<"千位:"<<d1<<endl;
	cout<<"百位:"<<d2<<endl;
	cout<<"十位:"<<d3<<endl;
	cout<<"个位:"<<d4<<endl;
	cout<<"十分位:"<<d5<<endl;
	cout<<"百分位:"<<d6<<endl;
	return 0;
}