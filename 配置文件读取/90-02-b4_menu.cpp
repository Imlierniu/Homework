/* �������̣�������1752856 ������*/
#include"90-02-b4.h"

void menu(int &a,int &b)//a:row  b:col
{
	while (1) {
		cct_cls();
		cout << "ѡ������(5-10) :";
		cin >> a;
		while (cin.fail()) {        //��ֹ��ѭ��
			cin.clear();
			cin.ignore(100, '\n');
			cct_cls();
			cout << "ѡ������(5-10) :";
			cin >> a;
		}
		if (a <= 10 && a >= 5)
			break;
		else
			continue;
	}
	while (1) {
		cct_cls();
		cout << "ѡ������(5-10) :";
		cin >> b;
		while (cin.fail()) {        //��ֹ��ѭ��
			cin.clear();
			cin.ignore(100, '\n');
			cct_cls();
			cout << "ѡ������(5-10) :";
			cin >> b;
		}
		if (b <= 10 && b >= 5)
			break;
		else
			continue;
	}
	
	
}

void Quit(int a,int b, CONSOLE_GRAPHICS_INFO& MyCGI) {
	cct_gotoxy(0, MyCGI.lines-4);
	cout << "���س��˳�" << endl;
	char ch = _getch();
	while (ch != 13) {
		ch = _getch();
	}
}