/*7772334 尹志平 信13*/
#include <iostream>
#include <cmath>
using namespace std;
int main()
{double a,x;
int c,d,e,f,g,h,i,j,k,l,m,n;
cout<<"请输入一个[0,30亿）的浮点数A=";
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
cout<<"十亿位:"<<c<<endl;
cout<<"亿位:"<<d<<endl;
cout<<"千万位:"<<e<<endl;
cout<<"百万位:"<<f<<endl;
cout<<"十万位:"<<g<<endl;
cout<<"万位:"<<h<<endl;
cout<<"千位:"<<i<<endl;
cout<<"百位:"<<j<<endl;
cout<<"十位:"<<k<<endl;
cout<<"个位:"<<l<<endl;
cout<<"十分位"<<m<<endl;
cout<<"百分位"<<n<<endl;
return 0;
}