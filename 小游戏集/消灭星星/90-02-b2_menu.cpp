#include"90-02-b2.h"

void menu(int &a,int &b)//a:row  b:col
{
	while (1) {
		cct_cls();
		cout << "选择行数(8-10) :";
		cin >> a;
		while (cin.fail()) {        //防止死循环
			cin.clear();
			cin.ignore(100, '\n');
			cct_cls();
			cout << "选择行数(8-10) :";
			cin >> a;
		}
		if (a <= 10 && a >= 8)
			break;
		else
			continue;
	}
	while (1) {
		cct_cls();
		cout << "选择列数(8-10) :";
		cin >> b;
		while (cin.fail()) {        //防止死循环
			cin.clear();
			cin.ignore(100, '\n');
			cct_cls();
			cout << "选择列数(8-10) :";
			cin >> b;
		}
		if (b <= 10 && b >= 8)
			break;
		else
			continue;
	}
	
	
}

void Quit(int a,int b, CONSOLE_GRAPHICS_INFO& MyCGI) {
	cct_gotoxy(0, MyCGI.lines-4);
	cout << "按回车退出" << endl;
	char ch = _getch();
	while (ch != 13) {
		ch = _getch();
	}
}