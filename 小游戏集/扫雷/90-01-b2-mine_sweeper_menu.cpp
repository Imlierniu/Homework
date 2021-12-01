
#include"90-01-b2-mine_sweeper.h"
int menu()
{
	int num;
	char c;
	system("cls");
	cout << "-----------------------------------------" << endl;
	cout << "1.选择难度并显示内部数组" << endl;
	cout << "2.输入初始位置并显示被打开的区域" << endl;
	cout << "3.内部数组基础版" << endl;
	cout << "4.内部数组完整版" << endl;
	cout << "5.画出伪图形化框架并显示内部数组" << endl;
	cout << "6.检测鼠标位置和合法性" << endl;
	cout << "7.鼠标选择初始位置并显示被打开的初始区域" << endl;
	cout << "8.伪图形界面基础版" << endl;
	cout << "9.为图形界面完整版" << endl;
	cout << "0.退出" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "[请选择]" << endl;

	c = _getch();
	while (c<'0' || c>'9') {        //防止死循环
		c = _getch();
	}
	num = (int)(c - '0');


	return num;
}
int Select_Level()
{
	system("cls");
	int num;
	char c;
	cout << "请选择难度" << endl;
	cout << "  1.初级（ 9x9   - 10个地雷）" << endl;
	cout << "  2.中级（16x16  - 40个地雷）" << endl;
	cout << "  3.高级（16x30  - 99个地雷）" << endl;
	cout << "请输入1.2.3" << endl;
	c = _getch();
	while (c<'1' || c>'3') {        //防止死循环
		c = _getch();
	}
	num = (int)(c - '0');


	return num;

}
void Quit()
{
	cout << "按回车退出" << endl;
	char ch = _getch();
	while (ch != 13) {
		ch = _getch();
	}
}