/*7772265 ��һ �𴦻�*/
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	double s;
	int x,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12;
	cin>>s;
	a1=int(s/1e9)%10;
	a2=int(s/1e8)%10;
	a3=int(s/1e7)%10;
	a4=int(s/1e6)%10;
	a5=int(s/1e5)%10;
	a6=int(s/1e4)%10;
	a7=int(s/1e3)%10;
	a8=int(s/1e2)%10;
	a9=int(s/1e1)%10;
	a10=int(s-1e9*a1)%10;
	x=int((s-1e9*a1-1e8*a2-1e7*a3-1e6*a4-1e5*a5-1e4*a6-1e3*a7-1e2*a8-1e1*a9-a10)*1000+2);
	a11=x/100;
	a12=x/10%10;
	cout<<"ʮ��λ��"<<a1<<endl;
	cout<<"��λ��"<<a2<<endl;
	cout<<"ǧ��λ��"<<a3<<endl;
	cout<<"����λ��"<<a4<<endl;
	cout<<"ʮ��λ��"<<a5<<endl;
	cout<<"��λ��"<<a6<<endl;
	cout<<"ǧλ��"<<a7<<endl;
	cout<<"��λ��"<<a8<<endl;
	cout<<"ʮλ��"<<a9<<endl;
	cout<<"��λ��"<<a10<<endl;
	cout<<"ʮ��λ��"<<a11<<endl;
	cout<<"�ٷ�λ��"<<a12<<endl;
	return 0;
}