
	7772214 ��ҩʦ �����һ��

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double a,b,c;
	cout<<"������һ��С��һ���ڵĸ�������С���������λ����"<<endl;
	cin>>a;
    b=a-floor(a);    
    c=int(a/1000000000);
    cout<<"ʮ��λ��"<<c<<endl;  
	a=a-c*1000000000; 

	c=floor(a/100000000);
    cout<<"��λ��"<<c<<endl;
	a=a-c*100000000;

    c=int(a/10000000);
    cout<<"ǧ��λ��"<<c<<endl;
	a=a-c*10000000;

    c=int(a/1000000);
    cout<<"����λ��"<<c<<endl;
	a=a-c*1000000;

    c=int(a/100000);
    cout<<"ʮ��λ��"<<c<<endl;
	a=a-c*100000;

	c=int(a/10000);
    cout<<"��λ��"<<c<<endl;
	a=a-c*10000;

	c=int(a/1000);
    cout<<"ǧλ��"<<c<<endl;
	a=a-c*1000;

	c=int(a/100);
    cout<<"��λ��"<<c<<endl;
    a=a-c*100;

	c=int(a/10);
    cout<<"ʮλ��"<<c<<endl;
	a=a-c*10;

    cout<<"��λ��"<<int(a)<<endl;

	cout<<"ʮ��λ��"<<int(b*10+0.001)<<endl;
	b=b*10-int(b*10+0.001);  

	cout<<"�ٷ�λ��"<<int(b*10+0.001)<<endl;
	
	return 0;
}