
	7772214 黄药师 计算机一班

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double a,b,c;
	cout<<"请输入一个小于一百亿的浮点数（小数点后保留两位）："<<endl;
	cin>>a;
    b=a-floor(a);    
    c=int(a/1000000000);
    cout<<"十亿位："<<c<<endl;  
	a=a-c*1000000000; 

	c=floor(a/100000000);
    cout<<"亿位："<<c<<endl;
	a=a-c*100000000;

    c=int(a/10000000);
    cout<<"千万位："<<c<<endl;
	a=a-c*10000000;

    c=int(a/1000000);
    cout<<"百万位："<<c<<endl;
	a=a-c*1000000;

    c=int(a/100000);
    cout<<"十万位："<<c<<endl;
	a=a-c*100000;

	c=int(a/10000);
    cout<<"万位："<<c<<endl;
	a=a-c*10000;

	c=int(a/1000);
    cout<<"千位："<<c<<endl;
	a=a-c*1000;

	c=int(a/100);
    cout<<"百位："<<c<<endl;
    a=a-c*100;

	c=int(a/10);
    cout<<"十位："<<c<<endl;
	a=a-c*10;

    cout<<"个位："<<int(a)<<endl;

	cout<<"十分位："<<int(b*10+0.001)<<endl;
	b=b*10-int(b*10+0.001);  

	cout<<"百分位："<<int(b*10+0.001)<<endl;
	
	return 0;
}