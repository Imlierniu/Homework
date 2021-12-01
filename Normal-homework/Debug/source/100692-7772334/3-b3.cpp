//7772334 尹志平 信13
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
	cout<<"十亿位："<<a<<endl;
	cout<<"亿位："<<b<<endl;
	cout<<"千万位："<<c<<endl;
	cout<<"百万位："<<d<<endl;
	cout<<"十万位："<<e<<endl;
	cout<<"万位："<<f<<endl;
	cout<<"千位："<<g<<endl;
	cout<<"百位："<<h<<endl;
	cout<<"十位："<<i<<endl;
	cout<<"个位："<<j<<endl;
	cout<<"十分位："<<k<<endl;
	cout<<"百分位："<<l<<endl;
	return 0;
}
