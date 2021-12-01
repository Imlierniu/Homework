/*7772324 樵夫 信03*/
#include <iostream>
using namespace std;
int main()
{
	double i;
	cin>>i;
	cout<<"应发奖金";
	if(i<=100000) cout<<0.1*i<<"元"<<endl;
	else if(i>100000&&i<=200000) cout<<0.075*i+2500<<"元"<<endl;
	else if(i>200000&&i<=400000) cout<<0.05*i+7500<<"元"<<endl;
	else if(i>400000&&i<=600000) cout<<0.03*i+15500<<"元"<<endl;
	else if(i>600000&&i<=1000000) cout<<0.015*i+24500<<"元"<<endl;
	else cout<<0.01*i+29500<<"元"<<endl;
	return 0;
}
