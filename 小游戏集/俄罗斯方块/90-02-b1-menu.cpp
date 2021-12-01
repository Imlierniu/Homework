#include"90-02-b1.h"

int menu()
{
	int num;
	char c;
	system("cls");
	cout << "-----------------------------------------" << endl;
	cout << "1.选择游戏背景大小" << endl;
	cout << "2.选择一个数字并查看它的四形态" << endl;
	cout << "3.选择一个数字并通过↑旋转它,Esc退出" << endl;
	cout << "4.选择一个数字并眼睁睁看它下落(可通过方向键操作)" << endl;
	cout << "5.游戏基础班" << endl;
	cout << "6.游戏完整版(有加速，计分，预测)" << endl;
	cout << "7.游戏外挂版" << endl;
	cout << "0.退出" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "[请选择]" << endl;

	c = _getch();
	while (c < '0' || c>'9') {        //防止死循环
		c = _getch();
	}
	num = (int)(c - '0');
	return num;
}
void Quit(int a,int b)
{
	cct_gotoxy(0, a*3 + 3);
	cout << "按回车退出" << endl;
	char ch = _getch();
	while (ch != 13) {
		ch = _getch();
	}
}