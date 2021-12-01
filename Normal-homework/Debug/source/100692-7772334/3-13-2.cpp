
	//7772334 尹志平 信13


#include <iostream>
using namespace std;
int main()
{
	double a,i;
	cout<<"请输入当月利润：";
	cin>>i;
	switch((int)i/100000){
	case 0:
	case 1:
		a=10000+(i-100000)*0.075;
		break;
	case 2:
	case 3:
		a=10000+100000*0.075+(i-200000)*0.05;
		break;
	case 6:
	case 5:
		a=10000+100000*0.075+200000*0.05+(i-400000)*0.03;
		break;
	case 7:
	case 8:
	case 9:
	case 10:
		a=10000+100000*0.075+200000*0.05+400000*0.03+(i-600000)*0.015;
		break;
	default:
		a=10000+100000*0.075+200000*0.05+400000*0.03+600000*0.015+(i-1000000)*0.01;
	}
	cout <<"应发奖金总额为："<<a<<endl;
	return 0;
}