//7772310 杨铁心 数理强化班
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	double a, c;
	long b, d;
	int a9, a8, a7, a6, a5, a4, a3, a2, a1, a0, f1, f2, e; 

	cout << "按y开始。" ;

	while (getchar() == 'y'){                                    //加循环为了一次输入那些数字，懒得一次次开了
        
		cout << endl;
		cout << "输入一个【零到一百亿】的数：";
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


	    cout << "十亿位：" << a9 << endl;
	    cout << "亿位：" << a8 << endl;
        cout << "千万位：" << a7 << endl;
	    cout << "百万位：" << a6 << endl;
	    cout << "十万位：" << a5 << endl;
	    cout << "万位：" << a4 << endl;
	    cout << "千位：" << a3 << endl;
	    cout << "百位：" << a2 << endl;
	    cout << "十位：" << a1 << endl;
		cout << "各位：" << a0 << endl;
	    cout << "十分位：" << f1 << endl;
	    cout << "百分位：" << f2 << endl << endl;
        cout << "按y继续：" ;
	     
	    getchar();
	}

	return 0;
}


	

