//7772232���ݿ�ѧ������ݼ���÷����
#include <iostream>
using namespace std;
int main()
{
	int i,x;
	cout<<"�����뵱������i"<<endl;
	cin>>i;
	i=i-1;
	if (i>0)
	{
		switch (i/100000)
		{
		    case 0:
		        x=(i+1)*0.1;
			    break;
			case 1:
	            x=1e4+(i+1-1e5)*0.075;
				break;
			case 2:
			case 3:
				x=1e4+0.75e4+(i+1-2e5)*0.05;
				break;
			case 4:
			case 5:
				x=1e4+0.75e4+1e4+(i+1-4e5)*0.03;
				break;
			case 6:
			case 7:
			case 8:
			case 9:
				x=1e4+0.75e4+1e4+0.6e4+(i+1-6e5)*0.015;
				break;
			default:
				x=1e4+0.75e4+1e4+0.6e4+0.6e4+(i+1-1e6)*0.01;
				break;
		}
		cout<<"Ӧ����������Ϊ"<< x <<"Ԫ"<<endl;
	}
	else
	    cout<<"�������"<<endl;
	return 0;
}