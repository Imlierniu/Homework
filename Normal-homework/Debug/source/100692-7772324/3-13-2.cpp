/*7772324 樵夫 信息类03班*/
#include <iostream>
using namespace std;
int main()
{
	double i;
	int a;
	cin>>i;
	cout<<"应发奖金";
	a=i/100000;
	switch(a)
	{
	    case 0:
			cout<<0.1*i<<endl;
			break;
		case 1:
			cout<<0.075*i+2500<<endl;
			break;
		case 2:
		case 3:
			cout<<0.05*i+7500<<endl;
			break;
		case 4:
		case 5:
			cout<<0.03*i+15500<<endl;
		case 6:
		case 7:
		case 8:
		case 9:
			cout<<0.015*i+24500<<endl;
		default:
			cout<<0.01*i+29500<<endl;
	}
	return 0;
}
//所描述的情况在等号处的含义可能与书中有些出入，但由于等号处的值相同，故不妨碍计算。


