//7772334 ��־ƽ ��13
#include <iostream>
using namespace std;
int main()
{
	double x,y;
	int a,b,c,d,e,f,g,h,i,j,k,l;
	cin>>x;
	x=x+0.005;
	a=x/1000000000;
	b=int(x/100000000)%10;
	c=int(x/10000000)%10;
	d=int(x/1000000)%10;
	e=int(x/100000)%10;
	f=int(x/10000)%10;
	g=int(x/1000)%10;
	h=int(x/100)%10;
	i=int(x/10)%10;
	y=x-a*1000000000-b*100000000-c*10000000;
	j=(int)y%10;
	k=int(y*10)%10;
	l=int(y*100)%10;
	cout<<"ʮ��λ��"<<a<<endl;
	cout<<"��λ��"<<b<<endl;
	cout<<"ǧ��λ��"<<c<<endl;
	cout<<"����λ��"<<d<<endl;
	cout<<"ʮ��λ��"<<e<<endl;
	cout<<"��λ��"<<f<<endl;
	cout<<"ǧλ��"<<g<<endl;
	cout<<"��λ��"<<h<<endl;
	cout<<"ʮλ��"<<i<<endl;
	cout<<"��λ��"<<j<<endl;
	cout<<"ʮ��λ��"<<k<<endl;
	cout<<"�ٷ�λ��"<<l<<endl;
	return 0;
}
