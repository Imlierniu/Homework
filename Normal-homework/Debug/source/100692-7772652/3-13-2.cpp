//数理强化班 柯镇恶 7772652
#include<iostream>
using namespace std;
int main()
{
	int i,a,b;
	cout<<"输入公司利润"<<endl;
	cin>>i;
	b=i/100000;
	switch(b)
	{
		case 0:
		    a=0.1*i;
			break;
	    case 1:
		    a=0.1*100000+(i-100000)*0.075;
			break;
	    case 2:
	    case 3:
		    a=0.1*100000+100000*0.075+(i-200000)*0.05;
			break;
	    case 4:
	    case 5:
		    a=0.1*100000+100000*0.075+200000*0.05+(i-400000)*0.03;
			break;
	    case 6:
	    case 7:
	    case 8:
	    case 9:
		    a=0.1*100000+100000*0.075+200000*0.05+200000*0.03+(i-600000)*0.015;
			break;
	    case 10:
		    a=0.1*100000+100000*0.075+200000*0.05+200000*0.03+400000*0.015+(i-1000000)*0.01;
			break;
	}
	cout<<"提成为"<<a<<endl;
	return 0;
}