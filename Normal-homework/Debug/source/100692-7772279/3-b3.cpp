/*7772279 ���߹� ��2��*/
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
	cout<<"ʮ��λ"<<":"<<int(b)<<endl;
    cout<<"��λ"<<":"<<int(c)<<endl;
	cout<<"ǧ��λ"<<":"<<int(d)<<endl;
	cout<<"����λ"<<":"<<int(e)<<endl;
    cout<<"ʮ��λ"<<":"<<int(f)<<endl;
	cout<<"��λ"<<":"<<int(g)<<endl;
	cout<<"ǧλ"<<":"<<int(h)<<endl;
	cout<<"��λ"<<":"<<i<<endl;
	cout<<"ʮλ"<<":"<<int(j)<<endl;
	cout<<"��λ"<<":"<<int(k)<<endl;
	cout<<"ʮ��λ"<<":"<<int(l)<<endl;
	cout<<"�ٷ�λ"<<":"<<int(m)<<endl;
	return 0;
}