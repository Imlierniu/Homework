/*7772279 计2班 洪七公*/
#include<iostream>
using namespace std;
int main()
{
	int a,i,x;
	cout<<"请输入利润值"<<endl;
	cin>>i;
	if(i>1000000) a=10;
	else a=i/100000;
	switch(a){
	    case 0:
			x=0.1*i;
			break;
		case 1:
			x=10000+0.075*(i-100000);
			break;
		case 2:
		case 3:
			x=17500+0.05*(i-200000);
			break;
		case 4:
		case 5:
			x=27500+0.03*(i-400000);
			break;
		case 6:
		case 7:
		case 8:
		case 9:
			x=33500+0.015*(i-600000);
			break;
		case 10:
			x=39500+0.01*(i-1000000);
			break;
	    }
		cout<<"此为对应奖金值"<<'\n'<<x<<endl;
		return 0;
}
	
			











			

