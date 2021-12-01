/*7772279 洪七公 计2班*/
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	double a,b,c,d,e,f,g,h,i,j,k,l,m;
	cin>>a;
	b=a/1000000000;
	c=a-int(b)*1000000000,c=int(c)/100000000;
    d=a-int(b)*1000000000-int(c)*100000000,d=int(d)/10000000;
    e=a-int(b)*1000000000-int(c)*100000000-int(d)*10000000,e=int(e)/1000000;
    f=a-int(b)*1000000000-int(c)*100000000-int(d)*10000000-int(e)*1000000,f=int(f)/100000;
	g=a-int(b)*1000000000-int(c)*100000000-int(d)*10000000-int(e)*1000000-int(f)*100000,g=int(g)/10000;
	h=a-int(b)*1000000000-int(c)*100000000-int(d)*10000000-int(e)*1000000-int(f)*100000-int(g)*10000,h=int(h)/1000;
	i=a-int(b)*1000000000-int(c)*100000000-int(d)*10000000-int(e)*1000000-int(f)*100000-int(g)*10000-int(h)*1000,i=int(i)/100;
    j=a-int(b)*1000000000-int(c)*100000000-int(d)*10000000-int(e)*1000000-int(f)*100000-int(g)*10000-int(h)*1000-int(i)*100,j=int(j)/10;
	k=a-int(b)*1000000000-int(c)*100000000-int(d)*10000000-int(e)*1000000-int(f)*100000-int(g)*10000-int(h)*1000-int(i)*100-int(j)*10,k=int(k)/1;
	l=a-int(a),l=l*100,l=l/10+0.05;
	m=a-int(a),m=m*1000-int(l)*100,m=m/10+0.5;
	cout<<"十亿位"<<":"<<int(b)<<endl;
    cout<<"亿位"<<":"<<int(c)<<endl;
	cout<<"千万位"<<":"<<int(d)<<endl;
	cout<<"百万位"<<":"<<int(e)<<endl;
    cout<<"十万位"<<":"<<int(f)<<endl;
	cout<<"万位"<<":"<<int(g)<<endl;
	cout<<"千位"<<":"<<int(h)<<endl;
	cout<<"百位"<<":"<<i<<endl;
	cout<<"十位"<<":"<<int(j)<<endl;
	cout<<"个位"<<":"<<int(k)<<endl;
	cout<<"十分位"<<":"<<int(l)<<endl;
	cout<<"百分位"<<":"<<int(m)<<endl;
	return 0;
}