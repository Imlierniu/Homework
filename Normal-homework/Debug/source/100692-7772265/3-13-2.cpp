
	/*	7772265 	  ��һ  		�𴦻�*/
		
#include<iostream>
using namespace std;
int main()
{
	unsigned int i,s;
	double a,b,c,d,e,f;
	cout<<"����������i(Բ):";
	cin>>i;
	s=(i-1)/100000;

	switch(s){													//��switch�����㽱��
		case 0:
			a=i*0.1;
			cout<<"��������Ϊ"<<a<<"Բ"<<endl;
			break;
		case 1:
			b=10000+(i-100000)*0.075;
			cout<<"��������Ϊ"<<b<<"Բ"<<endl;
			break;
		case 2:
		case 3:
			c=17500+(i-200000)*0.05;
			cout<<"��������Ϊ"<<c<<"Բ"<<endl;
			break;
		case 4:
		case 5:
			d=27500+(i-400000)*0.03;
			cout<<"��������Ϊ"<<d<<"Բ"<<endl;
			break;
		case 6:
		case 7:
		case 8:
		case 9:
			e=33500+(i-600000)*0.015;
			cout<<"��������Ϊ"<<e<<"Բ"<<endl;
			break;
		default:
			f=39500+(i-1000000)*0.01;
			cout<<"��������Ϊ"<<f<<"Բ"<<endl;
			break;
			}

	return 0;
}