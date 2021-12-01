/*7772279 计2班 洪七公*/
#include<iostream>
using namespace std;
int main()
{
	double i,x;
	cout<<"请输入利润值"<<endl;
	cin>>i;
	if(i<=100000){
		x=0.1*i;
		}
	else if(100000<i&&i<=200000){
		x=10000+0.075*(i-100000);
		}
    else if(200000<i&&i<=400000){
		x=17500+0.05*(i-200000);
		}
    else if(400000<i&&i<=600000){
		x=27500+0.03*(i-400000);
		}
    else if(600000<i&&i<=1000000){
		x=33500+0.015*(i-600000);
		}
	else if(i>1000000){
		x=39500+0.01*(i-1000000);
		}
	cout<<"此为对应奖金值"<<'\n'<<x<<endl;
	return 0;
}
