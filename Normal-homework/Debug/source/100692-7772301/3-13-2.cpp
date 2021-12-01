/* 7772301 计3班 瑛姑
*/
#include <iostream>
using namespace std;
int main()
{ 
	cout<<"请输入利润"<<endl;
	int i,x;
	cin>>i;
	
	switch (i/100000)  {
		case 0:
			x=i*0.1;
			break;
		case 1:
			x=10000+(i-100000)*0.075;
			break;
		case 2:
		case 3:
			x=17500+(i-200000)*0.05;
			break;
		case 4:
		case 5:
			x=27500+(i-400000)*0.03;
			break;
		case 6:
		case 7:
		case 8:
		case 9:
			x=33500+(i-600000)*0.015;
			break;
		default:
			x=39500+(i-1000000)*0.01;
			break;
	}
	cout<<"奖金为："<<x<<endl;
	return 0;
}
