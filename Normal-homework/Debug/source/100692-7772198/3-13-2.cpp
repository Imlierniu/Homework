/*7772198 ��18 ½��Ӣ*/
#include<iostream>
using namespace std;
int main()
{
	int i;
	cout<<"�����뵱������:"<<endl;
	cin>>i;
	cout<<"Ӧ����������Ϊ:";
	switch(i/100000)
	{
	case 0:
		cout<<0.1*i<<endl;
		break;
	case 1:
		cout<<2500+0.075*i<<endl;
		break;
	case 2:
	case 3:
		cout<<7500+0.05*i<<endl;
		break;
	case 4:
	case 5:
		cout<<15500+0.03*i<<endl;
		break;
	case 6:
	case 7:
	case 8:
    case 9:
		cout<<24500+0.015*i<<endl;
		break;
	default: 
		cout<<29500+0.01*i<<endl;
		break;
	}
	return 0;
}