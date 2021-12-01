	
	
/*7772198 信18 陆冠英*/
#include<iostream>
using namespace std;
int main()
{
	int i;
	cout<<"请输入当月利润:"<<endl;
	cin>>i;
	cout<<"应发奖金总数为:";
	if(i<=100000)
		cout<<0.1*i<<endl;
	else if(i<=200000)
		cout<<2500+0.075*i<<endl;
	else if(i<=400000)
		cout<<7500+0.05*i<<endl;
	else if(i<=600000)
		cout<<15500+0.03*i<<endl;
	else if(i<=1000000)
		cout<<24500+0.015*i<<endl;
	else 
		cout<<29500+0.01*i<<endl;
	return 0;
}