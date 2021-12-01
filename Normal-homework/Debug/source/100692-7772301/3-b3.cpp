/* 7772301	计算机3班 瑛姑*/
#include <iostream>
using namespace std;
int main()
{double x;
int a,b,c,d,e,f,g,h,i,j,k,l;
cin>>x;
x=x+1e-5;
a=x/1e9;
x=x-a*1e9;
b=x/1e8;
x=x-b*1e8;
c=x/1e7;
x=x-c*1e7;
d=x/1e6;
x=x-d*1e6;
e=x/1e5;
x=x-e*1e5;
f=x/1e4;
x=x-f*1e4;
g=x/1e3;
x=x-g*1e3;
h=x/1e2;
x=x-h*1e2;
i=x/1e1;
x=x-i*1e1;
j=x/1e0;
x=x-j*1e0;
k=x/1e-1;
x=x-k*1e-1;
l=x/1e-2;
cout<<"十亿位:"<<a<<endl;
cout<<"亿位:"<<b<<endl;
cout<<"千万位:"<<c<<endl;
cout<<"百万位:"<<d<<endl;
cout<<"十万位:"<<e<<endl; 
cout<<"万位:"<<f<<endl;
cout<<"千位:"<<g<<endl;
cout<<"百位:"<<h<<endl;
cout<<"十位:"<<i<<endl;
cout<<"个位:"<<j<<endl;
cout<<"十分位:"<<k<<endl;
cout<<"百分位:"<<l<<endl;
return 0;
}