


/* -----------------------------------------

	 本文件功能：
	1、放被 hanoi_main.cpp/hanoi_menu.cpp 中的各函数调用的菜单各项对应的执行函数

	 本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------- */


   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/


#include"90-01-b1-hanoi.h"


int pop(int i)
{
	return stack[i][--top[i]];
}
void push(int x, int i)
{
	stack[i][top[i]] = x;
	top[i]++;
}

void print(int i, int n)
{
	int j = 0;
	while (j < top[i]) {
		cout << stack[i][j++] << " ";
	}

	int k = n - top[i];
	while (k-- > 0) {
		cout << "  ";
	}
}


void set(char& a, int& n)
{
	int i = (int)(a - 'A');
	for (; top[i] < n; top[i]++) {
		stack[i][top[i]] = (n - top[i]);
	}
}
void show_1(int& x, char a, char b, char c)
{
	cout << "# " << x << " " << a << "-->" << c << endl;
}
void show_2(int& x, char a, char b, char c)
{
	cout << "第" << setw(4) << i << "步(#" << x << " " << a << "-->" << c << endl;
}
void show_3(int& n, int& x, char a, char b, char c)
{
	cout << "第" << setw(4) << i << "步(#" << x << "):";
	cout << a << "-->" << c << "  ";
	cout << "A: ";
	print(0, n);
	cout << "|";
	cout << "B: ";
	print(1, n);
	cout << "|";
	cout << "C: ";
	print(2, n);
	cout << "|";
	cout << endl;
}
void show_4(int& x, char a, char b, char c)
{
	if (Time) {
		Sleep(Time);   //速度
	}
	else {             //单步
		while (1)
		{
			char ch = getchar();
			if (ch == '\n')
				break;

		}
	}
	//输出竖向汉诺塔
	system("cls");
	cout << endl;
	for (int i = 14; i >= 0; i--) {
		if (i < top[0])
			cout << setw(12) << stack[0][i];
		else
			cout << "            ";

		if (i < top[1])
			cout << setw(12) << stack[1][i];
		else
			cout << "            ";

		if (i < top[2])
			cout << setw(12) << stack[2][i];
		else
			cout << "            ";
		cout << endl;
	}

	cout << "       " << "=================================" << endl;;
	cout << setw(12) << "A" << setw(12) << "B" << setw(12) << "C" << endl;
	cout << "\n\n\n";

	cout << "第" << setw(4) << i << "步(#" << x << "):";
	cout << a << "-->" << c << "  ";

}
void move_stack(int num, int n, int N, int& x, char a, char b, char c)//把递归函数功能拆分出来
{
	i++;   //用于记步
	x++;   //用于记录当下移动的盘号
	int t_pop=0;
	switch (a) {
	case'A':
		t_pop = pop(0);
		break;
	case'B':
		t_pop = pop(1);
		break;
	case'C':
		t_pop = pop(2);
		break;
	default:
		break;
	}
	switch (c) {
	case'A':
		push(t_pop, 0);
		break;
	case'B':
		push(t_pop, 1);
		break;
	case'C':
		push(t_pop, 2);
		break;
	default:
		break;
	}
	if (num == 4)
		show_4(x, a, b, c);
	else if (num == 3)
		show_3(N, x, a, b, c);
	else if (num == 1)
		show_1(x, a, b, c);
	else if (num == 2)
		show_2(x, a, b, c);
	else if (num == 8) {
		Paint_3(N, top[(int)(a - 'A')], x, a, b, c, x, 0); //第二个x是颜色，颜色和盘子号绑定关系
		if (Time) {
			Sleep(Time);//速度
		}
		else {             //单步
			while (1)
			{
				char ch = getchar();
				if (ch == '\n')
					break;
			}
		}
	}

	return;

}
void move(int& num, int n, int N, int& x, char a, char b, char c)
{
	if (n == 1)
		move_stack(num, n, N, x, a, b, c);
	else {
		x = 0;
		move(num, n - 1, N, x, a, c, b);
		x = n - 1;
		move(num, 1, N, x, a, b, c);
		x = 0;
		move(num, n - 1, N, x, b, a, c);
	}
}
void work(int& num, int& N, int& x, int& mode, char& Begin, char& Temp, char& End)
{
	switch (mode)
	{
	case 1:Time = 1000; break;
	case 2:Time = 800; break;
	case 3:Time = 600; break;
	case 4:Time = 400; break;
	case 5:Time = 200; break;
	}
	if (num == 3) {
		cout << "初始：" << "              ";
		cout << "A: ";
		print(0, N);
		cout << "|";
		cout << "B: ";
		print(1, N);
		cout << "|";
		cout << "C: ";
		print(2, N);
		cout << "|";
		cout << endl;
	}
	move(num, N, N, x, Begin, Temp, End);

}

void Change_speed(int& mode)
{
	while (1) {
		cout << "请输入移动速度(0-5：0-按回车单步演示 1-延时最长 5-延时最短";
		cin >> mode;
		while (cin.fail()) {        //防止死循环
			cin.clear();
			cin.ignore(100, '\n');
			cout << "请输入移动速度(0-5：0-按回车单步演示 1-延时最长 5-延时最短" << endl;
			cin >> mode;
		}
		if (mode <= 5 && mode >= 0)
			break;
		else
			continue;
	}

}
void init(int& n, char& Begin, char& Temp, char& End, int game_top[])
{
	while (1) {                       //输入层数检测
		cout << "请输入层数n(1-10)：" << endl;
		cin >> n;
		while (cin.fail()) {        //防止死循环
			cin.clear();
			cin.ignore(100, '\n');
			cout << "请输入层数n(1-10)：" << endl;
			cin >> n;
		}
		if (n <= 10 && n >= 1)
			break;
		else
			continue;
	}


	int tag[3] = { 0,0,0 };   //推断Temp所用
	while (1) {  //输入起始圆柱检测
		cout << "输入起始圆柱<A-C>";
		cin >> Begin;
		if (Begin <= 'C' && Begin >= 'A' ){	 //保证大小写均可
				tag[(Begin - 'A')] = 1;
			break;
		}
		else if (Begin <= 'c' && Begin >= 'a') {
			Begin -= 32;
			tag[(Begin - 'A')] = 1;
			break;
		}
		else
			continue;
	}
	while (1) {          //输入终止圆柱检测
		cout << "输入终止圆柱<A-C>";
		cin >> End;
		if (Begin == End) {
			cout << "起始终止圆柱不得相同，重新输入" << endl;
			continue;
		}
		if ((End <= 'C') && (End >= 'A')) {
			tag[End - 'A'] = 1;
			break;
		}
		else if (End <= 'c' && End >= 'a') {
			End -= 32;
			tag[End - 'A'] = 1;
			break;
		}
		else
			continue;

	}

	if (!tag[0])
		Temp = 'A';
	else if (!tag[1])
		Temp = 'B';
	else
		Temp = 'C';


	game_top[Begin - 'A'] = 1;
	game_top[Temp - 'A'] = 0;
	game_top[End - 'A'] = 0;



}
void Clear()
{
	i = 0;    //步数
	//int stack[3][15];//三个柱子上的盘子
	top[0] = 0;
	top[1] = 0;
	top[2] = 0;
	Time = 0;
	cout << "按回车退出" << endl;
	char ch = _getch();
	while (ch != 13) {
		ch = _getch();
	}
}

//画图
void Paint_1()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j <= 20; j++) {
			cct_showstr(30 * i + j, 18, " ", 14, 7, 1, -1);
			Sleep(10);
		}
		for (int k = 17; k >= 2; k--) {
			cct_showstr(i * 30 + 10, k, " ", 14, 7, 1, -1);
			Sleep(10);
		}
	}
}
void Paint_2(int n, char& Begin)
{
	int center = (Begin - 'A') * 30 + 10;
	for (int i = 0; i < n; i++) {
		for (int j = center - n + i; j < center + n - i + 1; j++) {
			cct_showstr(j, 17 - i, " ", n - i, 7, 1, -1);
			Sleep(10);
		}
	}
}
void Paint_3(int N, int n, int x, char& Begin, char& Temp, char& End, int color, bool is_static)//x当前盘子号
{
	int center_1 = (Begin - 'A') * 30 + 10;//起始位置
	int center_2;                          //末了位置，不一定是在End处
	cct_gotoxy(0, 0);
	cct_setcolor(0, 7);

	/*if (n % 2) {
		center_2 = (End - 'A') * 30 + 10;
		cout << "从" << Begin << " 盘移动到" << End << "盘，共" << n << "层\n";
	}
	else {
		center_2 = (Temp - 'A') * 30 + 10;
		cout << "从" << Begin << " 盘移动到" << Temp << "盘，共" << n << "层\n";
	}*/
	center_2 = (End - 'A') * 30 + 10;
	cout << "从" << Begin << " 盘移动到" << End << "盘，共" << N << "层\n";


	int x0 = center_1 - x;   //初点横坐标
	int x1 = center_2 - x;   //终点横坐标
	int y1 = 18 - top[(int)(End - 'A')];
	int length = 2 * x + 1;
	int y0 = 17 - top[Begin - 'A'];//移动时栈已经改变了，所以18-1=17
	if (is_static) {                       //选项7直接输出而栈指针未动，手动操作一下
		y0 += 1;
		y1 -= 1;
	}
	for (int j = y0; j > 2; j--) {                        //从第一个杆平移到顶

		for (int i = x0; i < x0 + length; i++) {
			if (i == 10 || i == 40 || i == 70)
				cct_showstr(i, j, " ", 14, 0, 1, -1);
			else
				cct_showstr(i, j, " ", color, 0, 1, -1);

		}
		Sleep(20);
		for (int i = x0; i < x0 + length; i++) {
			if (i == 10 || i == 40 || i == 70)
				cct_showstr(i, j, " ", 14, 0, 1, -1);
			else
				cct_showstr(i, j, " ", 0, 0, 1, -1);

		}

	}
	if (x1 - x0 > 0) {
		for (int i = x0; i < x1; i++) {                     //在顶上左右移动
			for (int j = i; j < i + length; j++) {
				cct_showstr(j, 1, " ", color, 0, 1, -1);
			}
			Sleep(10);
			for (int j = i; j < i + length; j++) {
				cct_showstr(j, 1, " ", 0, 0, 1, -1);
			}
			//Sleep(10);
		}
	}
	else {
		for (int i = x0; i > x1; i--) {                     //在顶上左右移动
			for (int j = i; j < i + length; j++) {
				cct_showstr(j, 1, " ", color, 0, 1, -1);
			}
			Sleep(10);
			for (int j = i; j < i + length; j++) {
				cct_showstr(j, 1, " ", 0, 0, 1, -1);
			}
			//Sleep(10);
		}
	}

	for (int j = 2; j < y1; j++) {                        //在终杆平移到底
		for (int i = x1; i < x1 + length; i++) {
			if (i == 10 || i == 40 || i == 70)
				cct_showstr(i, j, " ", 14, 0, 1, -1);
			else
				cct_showstr(i, j, " ", color, 0, 1, -1);
			//Sleep(10);
		}
		Sleep(20);
		for (int i = x1; i < x1 + length; i++) {
			if (i == 10 || i == 40 || i == 70)
				cct_showstr(i, j, " ", 14, 0, 1, -1);
			else
				cct_showstr(i, j, " ", 0, 0, 1, -1);
			//Sleep(10);
		}
	}
	for (int i = x1; i < x1 + length; i++) {     //终点处
		cct_showstr(i, y1, " ", color, 0, 1, -1);
	}

}

void Game_error_clear()
{
	cct_showstr(0, 26, "                                                       ", 0, 0, 1, -1);
	cct_gotoxy(0, 26);
	cct_setcolor(0, 7);
	cin.clear();
	cin.ignore(100, '\n');
}

void Game(int N, int x, char& Begin, char& Temp, char& End, int game_top[])
{
	i = 0;
	char End1 = End;
	while (1) {

		cct_gotoxy(0, 25);
		cct_setcolor(0, 7);
		cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：" << endl;
		while (1) {  //输入起始圆柱检测
			cct_gotoxy(0, 28);
			Begin = getchar();
			if (Begin <= 'C' && Begin >= 'A' || Begin <= 'c' && Begin >= 'a') {
				if (Begin <= 'c' && Begin >= 'a')   //保证大小写均可
					Begin -= 32;
				if (top[(Begin - 'A')]==0) {
					cct_gotoxy(0, 26);
					cout << "初始柱不能为空！";
					Sleep(1000);
					Game_error_clear();
					continue;
				}
				break;
			}
			else
				continue;
		}
		while (1) {          //输入终止圆柱检测
			cct_gotoxy(0, 28);
			End = getchar();
			if (Begin == End) {
				cct_gotoxy(0, 26);
				cout << "起始终止圆柱不得相同，重新输入";
				Sleep(1000);
				Game_error_clear();
				continue;
			}
			if (End <= 'C' && End >= 'A' || End <= 'c' && End >= 'a') {
				if (End <= 'c' && End >= 'a')
					End -= 32;
				if (top[End - 'A'] && (game_top[Begin - 'A'] > game_top[End - 'A'])) {
					cct_gotoxy(0, 26);
					cout << "大盘不能放在小盘之上！";
					Sleep(1000);
					Game_error_clear();
					continue;
				}
				break;
			}
			else
				continue;

		}


		//cout << Begin << "--->" << End << endl;
		
		
		int t_pop=0;
		switch (Begin) {
		case'A':
			t_pop = pop(0);
			break;
		case'B':
			t_pop = pop(1);
			break;
		case'C':
			t_pop = pop(2);
			break;
		default:
			break;
		}
		switch (End) {
		case'A':
			push(t_pop, 0);
			break;
		case'B':
			push(t_pop, 1);
			break;
		case'C':
			push(t_pop, 2);
			break;
		default:
			break;
		}
		//game_top[End - 'A'] = game_top[Begin - 'A'];
		//game_top[Begin - 'A']=stack[Begin-'A'][top[Begin-'A']-1];
		
		x = game_top[Begin - 'A'];
		Paint_3(N, top[(int)(Begin - 'A')], x, Begin, Temp, End, x, 0);
		i++;

		game_top[Begin - 'A'] = stack[Begin - 'A'][top[Begin - 'A'] - 1];
		game_top[End - 'A'] = stack[End - 'A'][top[End - 'A'] - 1];

		if (top[End1 - 'A'] == N) {
			Game_error_clear();
			cout << "牛啊牛啊！,你一共花了 " << i << " 步完成" << endl;
			break;
		}
	}

}
void Quit()
{
	cct_gotoxy(0, 30);
	cct_setcolor(0, 7);
	Clear();
}