//7772310 ������ ��ǿ
#include<iostream>
using namespace std;
int main()
{
	double i;
	int bonus, b;
	cout << "�����뱾������";
	cin >> i;
	b = i / 100000;
	switch(b)
	{
	    case 0: 
			bonus = 0.1 * i;
		    cout << "����Ϊ��" << bonus << endl;
			break;

	    case 1: 
			bonus = 10000 + 0.075 * (i - 100000);
		    cout << "����Ϊ��" << bonus << endl;
			break;

	    case 2:
	    case 3: 
		    bonus = 17500 + 0.05 * (i - 200000);
		    cout << "����Ϊ��" << bonus << endl;
	        break;

 	    case 4:
	    case 5:
		    bonus = 27500 + 0.03 * (i - 400000);
		    cout << "����Ϊ��" << bonus << endl;
		    break;

	    case 6:
	    case 7:
	    case 8:
	    case 9:
			bonus = 33500 + 0.015 * (i - 600000);
		    cout << "����Ϊ��" << bonus << endl;
		    break;
		default:
			bonus = 39500 + 0.015 * (i - 1000000);
		    cout << "����Ϊ��" << bonus << endl;
			break;
	}
	return 0;
}

