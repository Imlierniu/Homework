//����� 7772652
#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int main()
{
	double a,b,c,f,h,j,l,n,p,r,t,u,w,v,y,x;
	int d,e,g,i,k,m,o,q,s;
	cout<<"����һ����0..100�ڣ�֮��ĸ�����"<<endl;
	cin>>a;
	b=a/1000000000;
	
	d=(int)b;
	cout<<"ʮ��λ "<<d<<endl;
	c=a/100000000-d*10;
	
	e=(int)c;
	cout<<"��λ "<<e<<endl;
	f=a/10000000-e*10-d*100;
	
	g=(int)f;
	cout<<"ǧ��λ "<<g<<endl;
	h=a/1000000-g*10-e*100-d*1000;
	
	i=(int)h;
	cout<<"����λ "<<i<<endl;
	j=a/100000-i*10-g*100-e*1000-d*10000;
	
	k=(int)j;
	cout<<"ʮ��λ "<<k<<endl;
	l=a/10000-k*10-i*100-g*1000-e*10000-d*100000;
	
	m=(int)l;
	cout<<"��λ "<<m<<endl;
	n=a/1000-m*10-k*100-i*1000-g*10000-e*100000-d*1000000;
	
	o=(int)n;
	cout<<"ǧλ "<<o<<endl;
	p=a/100-o*10-m*100-k*1000-i*10000-g*100000-e*1000000-d*10000000;
	
	q=(int)p;
	cout<<"��λ "<<q<<endl;
	r=a/10-q*10-o*100-m*1000-k*10000-i*100000-g*1000000-e*10000000-d*100000000;
	
	s=(int)r;
	cout<<"ʮλ "<<s<<endl;
	t=a-s*10-q*100-o*1000-m*10000-k*100000-i*1000000-g*10000000-e*100000000-d*1000000000;
	cout<<"��λ "<<(int)t<<endl;
	u=t-(int)t;
    v=int(u*10+0.0001);
	w=int(u*100+0.0001);
	x=int(v*10);
	y=int(w-x);
   
	cout<<"ʮ��λ "<<v<<endl;
    cout<<u<<endl;
	cout<<"�ٷ�λ "<<y<<endl;
	return 0;
}