//7772232 大数据 7772232
#include <iostream>
using namespace std;
int main()
{
	int i,x;
	cout<<"请输入当月利润i"<<endl;
	cin>>i;
	if (i>=0)
	{
		if (i<=1e5)
		    x=i*0.1;
	    else if (i>1e5 && i<=2e5)
		    x=1e4+(i-1e5)*0.075;
	    else if (i>2e5 && i<=4e5)
		    x=1e4+0.75e4+(i-2e5)*0.05;
	    else if (i>4e5 && i<=6e5)
		    x=1e4+0.75e4+1e4+(i-4e5)*0.03;
	    else if (i>6e4 && i<=1e6)
		    x=1e4+0.75e4+1e4+0.6e4+(i-6e5)*0.015;
	    else 
		    x=1e4+0.75e4+1e4+0.6e4+0.6e4+(i-1e6)*0.01;
	    cout<<"应发奖金数量为"<< x <<"元"<<endl;
	}
	else 
		cout<<"输入错误"<<endl;

	return 0;
}