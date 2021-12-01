/*7772214 黄药师 计算机1班*/ 
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	float i,j;
	cout<<"请输入利润："<<endl;
	cin>>i;
	if(i<=100000)
		j=0.1*i;
	else if(i<=200000)
		j=10000+0.075*(i-100000);
	else if(i<=400000)
		j=17500+0.05*(i-200000);
	else if(i<=600000)
		j=27500+0.03*(i-400000);
	else if(i<=1000000)
	    j=33500+0.015*(i-600000);
	else
		j=45500+0.01*(i-1000000);

    cout<<"应发奖金总数为："<<j<<endl;
    return 0;
}
