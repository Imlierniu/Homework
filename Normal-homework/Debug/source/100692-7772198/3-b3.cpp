/*7772214 ½��Ӣ ��Ϣ��18��*/

#include<iostream>
using namespace std;
int main()
{
	double a,b0,d0;
	int c1=10,c2=100,c3=1000,c4=10000,c5=100000,
		b,b1,b2,b3,b4,b5,b6,d,d1,d2,d3,d4,d5,d6;
	cout<<"���������һ��[0 .. 100 ��)֮��������λС���ĸ�����"<<endl;
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
    cout<<"ʮ��λ:"<<b1<<endl;
	cout<<"��λ:"<<b2<<endl;
	cout<<"ǧ��λ:"<<b3<<endl;
	cout<<"����λ:"<<b4<<endl;
	cout<<"ʮ��λ:"<<b5<<endl;
	cout<<"��λ:"<<b6<<endl;
	cout<<"ǧλ:"<<d1<<endl;
	cout<<"��λ:"<<d2<<endl;
	cout<<"ʮλ:"<<d3<<endl;
	cout<<"��λ:"<<d4<<endl;
	cout<<"ʮ��λ:"<<d5<<endl;
	cout<<"�ٷ�λ:"<<d6<<endl;
	return 0;
}