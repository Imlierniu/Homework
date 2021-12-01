/*计算机1班 黄药师 7772214 */
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
float k;
int i,j;
	cout<<"请输入利润值";
	cin>>i;
	cout<<"元";
	i=i-1;
    j=i/100000;
	i=i+1;
	switch (j)
	{
    	case 0:
			k=0.1*i;
			break;
	    case 1:
			k=10000+0.075*(i-100000);
			break;
	    case 2:
        case 3:
			k=17500+0.05*(i-200000);
			break;
		case 4:
	    case 5:
			k=27500+0.03*(i-400000);
			break;
	    case 6:
	    case 7:
		case 8:
		case 9:
	    case 10:
			k=33500+0.015*(i-600000);
			break;
	    default:
			k=39500+0.01*(i-1000000);
	}
		cout<<"应发奖金数为："<<k<<"元"<<endl;
		return 0;
}
