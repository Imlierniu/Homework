/*7772334 ��־ƽ ��13*/
#include <iostream>
#include <cmath>
using namespace std;
int main()
{double a,x;
int c,d,e,f,g,h,i,j,k,l,m,n;
cout<<"������һ��[0,30�ڣ��ĸ�����A=";
cin>>a;
c=a/1000000000;
d=int(a/100000000)%10;
e=int(a/10000000)%10;
f=int(a/1000000)%10;
g=int(a/100000)%10;
h=int(a/10000)%10;
i=int(a/1000)%10;
j=int(a/100)%10;
k=int(a/10)%10;
l=a-int(a/10)*10;
x=a-int(a/10)*10-l+0.005;
m=x*10;
n=int(x*100)%10;
cout<<"ʮ��λ:"<<c<<endl;
cout<<"��λ:"<<d<<endl;
cout<<"ǧ��λ:"<<e<<endl;
cout<<"����λ:"<<f<<endl;
cout<<"ʮ��λ:"<<g<<endl;
cout<<"��λ:"<<h<<endl;
cout<<"ǧλ:"<<i<<endl;
cout<<"��λ:"<<j<<endl;
cout<<"ʮλ:"<<k<<endl;
cout<<"��λ:"<<l<<endl;
cout<<"ʮ��λ"<<m<<endl;
cout<<"�ٷ�λ"<<n<<endl;
return 0;
}