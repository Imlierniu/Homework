//7772310 ������ ����ǿ����
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	double a, c;
	long b, d;
	int a9, a8, a7, a6, a5, a4, a3, a2, a1, a0, f1, f2, e; 

	cout << "��y��ʼ��" ;

	while (getchar() == 'y'){                                    //��ѭ��Ϊ��һ��������Щ���֣�����һ�δο���
        
		cout << endl;
		cout << "����һ�����㵽һ���ڡ�������";
	    cin >> a;
	    b = long(a / 100);
	    d = long(a - (b * 100));
	    c = a - (b * 100) - d;

	    b = b % 100000000;

	    a9 = b / 10000000;
	    b = b % 10000000;

	    a8 = b / 1000000;
	    b = b % 1000000;

	    a7 = b / 100000;
	    b = b % 100000;

	    a6 = b / 10000;
	    b = b % 10000;

	    a5 = b / 1000;
	    b = b % 1000;

	    a4 = b / 100;
	    b = b % 100;

	    a3 = b / 10;
	    b = b % 10;

	    a2 = b;

	    a1 = d / 10;
	    d = d % 10;

	    a0 = d;

	    e = int(c * 1000);
        e = (fabs(c - e) >=0.5) + e;
	    f1 = e / 100;
	    e = e % 100;
	    f2 = e / 10;


	    cout << "ʮ��λ��" << a9 << endl;
	    cout << "��λ��" << a8 << endl;
        cout << "ǧ��λ��" << a7 << endl;
	    cout << "����λ��" << a6 << endl;
	    cout << "ʮ��λ��" << a5 << endl;
	    cout << "��λ��" << a4 << endl;
	    cout << "ǧλ��" << a3 << endl;
	    cout << "��λ��" << a2 << endl;
	    cout << "ʮλ��" << a1 << endl;
		cout << "��λ��" << a0 << endl;
	    cout << "ʮ��λ��" << f1 << endl;
	    cout << "�ٷ�λ��" << f2 << endl << endl;
        cout << "��y������" ;
	     
	    getchar();
	}

	return 0;
}


	

