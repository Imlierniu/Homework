/*7772265 ��һ �𴦻�*/
#include<iostream>
using namespace std;
int main()
{
	unsigned int i;
	double a,b,c,d,e,f;
	cout<<"����������i(Բ):";
	cin>>i;

	if(i<=100000){													//��if�����㽱��
		a=i*0.1;
		cout<<"��������Ϊ"<<a<<"Բ"<<endl;
		}
	else{
		if(i<=200000){
			b=10000+(i-100000)*0.075;
			cout<<"��������Ϊ"<<b<<"Բ"<<endl;
			}
		else{
			if(i<=400000){
				c=17500+(i-200000)*0.05;
				cout<<"��������Ϊ"<<c<<"Բ"<<endl;
				}
			else{
				if(i<=600000){
					d=27500+(i-400000)*0.03;
					cout<<"��������Ϊ"<<d<<"Բ"<<endl;
					}
				else{
					if(i<=1000000){
						e=33500+(i-600000)*0.015;
						cout<<"��������Ϊ"<<e<<"Բ"<<endl;
						}
					else{
						f=39500+(i-1000000)*0.01;
						cout<<"��������Ϊ"<<f<<"Բ"<<endl;
						}
					}
				}
			}
		}
	return 0;
}