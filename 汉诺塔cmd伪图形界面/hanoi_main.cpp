#include"90-01-b1-hanoi.h"


/* -----------------------------------------

	 本文件功能：
	1、放main函数
	2、初始化屏幕
	3、调用菜单函数（hanoi_menu.cpp中）并返回选项
	4、根据选项调用菜单各项对应的执行函数（hanoi_multiple_solutions.cpp中）

	 本文件要求：
	1、不允许定义全局变量（含外部全局和静态全集，const及#define不在限制范围内）
	2、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	3、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------- */

   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/

   /******题目允许的四个全局变量*******/
int i;    //步数
int stack[3][15];//三个柱子上的盘子
int top[3];
int Time;

int main()
{
	while (1) {
		int x = 0;    //当前移动的盘子号
	//int isshow; //是否显示横
		char Begin, Temp, End;
		int mode;
		int n;
		int num;//10个选项

		int game_top[3] = { 0 };//三个顶盘是几号,游戏用

		/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
		cct_setconsoleborder(120, 40, 120, 9000);
		num = menu();
		switch (num) {
		case 1:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			move(num, n, n, x, Begin, Temp, End);
			Clear();
			break;
		case 2:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			move(num, n, n, x, Begin, Temp, End);
			Clear();
			break;
		case 3:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			work(num, n, x, mode, Begin, Temp, End);
			Clear();
			break;
		case 4:
			init(n, Begin, Temp, End, game_top);
			Change_speed(mode);
			set(Begin, n);
			system("cls");
			work(num, n, x, mode, Begin, Temp, End);
			Clear();
			break;
		case 5:
			system("cls");
			Paint_1();
			Quit();
			break;
		case 6:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			Paint_1();
			Paint_2(n, Begin);
			Quit();
			break;
		case 7:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			Paint_1();
			Paint_2(n, Begin);
			if (n % 2)
				Paint_3(n, top[Begin - 'A'], 1, Begin, End, Temp, 1, 1);
			else
				Paint_3(n, top[Begin - 'A'], 1, Begin, Temp, End, 1, 1);

			Quit();
			break;
		case 8:
			init(n, Begin, Temp, End, game_top);
			Change_speed(mode);
			set(Begin, n);
			system("cls");
			Paint_1();
			Paint_2(n, Begin);
			work(num, n, x, mode, Begin, Temp, End);
			Quit();
			break;
		case 9:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			Paint_1();
			Paint_2(n, Begin);

			x = game_top[Begin - 'A'];
			Game(n, x, Begin, Temp, End, game_top);
			Quit();
			break;
		case 0:
			return 0;
			break;
		}

	}

	return 0;
}
