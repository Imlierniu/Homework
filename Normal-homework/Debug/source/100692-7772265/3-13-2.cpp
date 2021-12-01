
	/*	7772265 	  信一  		丘处机*/
		
#include<iostream>
using namespace std;
int main()
{
	unsigned int i,s;
	double a,b,c,d,e,f;
	cout<<"请输入利润i(圆):";
	cin>>i;
	s=(i-1)/100000;

	switch(s){													//用switch语句计算奖金
		case 0:
			a=i*0.1;
			cout<<"奖金总数为"<<a<<"圆"<<endl;
			break;
		case 1:
			b=10000+(i-100000)*0.075;
			cout<<"奖金总数为"<<b<<"圆"<<endl;
			break;
		case 2:
		case 3:
			c=17500+(i-200000)*0.05;
			cout<<"奖金总数为"<<c<<"圆"<<endl;
			break;
		case 4:
		case 5:
			d=27500+(i-400000)*0.03;
			cout<<"奖金总数为"<<d<<"圆"<<endl;
			break;
		case 6:
		case 7:
		case 8:
		case 9:
			e=33500+(i-600000)*0.015;
			cout<<"奖金总数为"<<e<<"圆"<<endl;
			break;
		default:
			f=39500+(i-1000000)*0.01;
			cout<<"奖金总数为"<<f<<"圆"<<endl;
			break;
			}

	return 0;
}