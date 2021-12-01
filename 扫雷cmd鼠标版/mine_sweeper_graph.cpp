#include"90-01-b2-mine_sweeper.h"

void Print_Graph_Base(int level)
{
	system("cls");
	if (level == 1) {
		Graph_1(1);
	}
	else if (level == 2) {
		Graph_2(1);
	}
	else if (level == 3) {
		Graph_3(1);
	}
}
void Print_Graph_unknow(int level)
{
	system("cls");
	if (level == 1) {
		Graph_1(0);
	}
	else if (level == 2) {
		Graph_2(0);
	}
	else if (level == 3) {
		Graph_3(0);
	}
}
void Print_top(int level)
{
	int L;
	if (level == 1)
		L = 8;
	else if (level == 2)
		L = 15;
	else
		L = 29;
	//开始画第一行
	cout << "  ";
	cct_setcolor(15, 0);
	cout << "╔";
	for (int i = 0; i < L; i++) {
		cout << "══╦";
	}
	cout << "══╗";
}
void Print_2(int level,int color)
{
	int L;
	if (level == 1)
		L = 9;
	else if (level == 2)
		L = 16;
	else
		L = 30;
	//第二行
	cct_setcolor(0, 7);
	cout << endl << "  ";
	cct_setcolor(15, 0);
	cout << "║";
	for (int i = 0; i < L; i++) {
		cct_setcolor(color, 0);
		cout << "    ";
		cct_setcolor(15, 0);
		cout << "║";
	}

}
void Print_3(int i,int level,int color)
{
	int L;
	if (level == 1)
		L = 9;
	else if (level == 2)
		L = 16;
	else
		L = 30;
	//第三行，与第二行一样,加一个输出字符即可
	cct_setcolor(0, 7);
	cout << endl << (char)('A'+i)<<" ";
	cct_setcolor(15, 0);
	cout << "║";
	for (int i = 0; i < L; i++) {
		cct_setcolor(color, 0);
		cout << "    ";
		cct_setcolor(15, 0);
		cout << "║";
	}
}
void Print_mid(int level)
{
	int L;
	if (level == 1)
		L = 9;
	else if (level == 2)
		L = 16;
	else
		L = 30;
	//结点处
	cct_setcolor(0, 7);
	cout << endl << "  ";
	cct_setcolor(15, 0);
	cout << "╠";
	for (int i = 0; i < L-1; i++) {
		cout << "══╬";
	}
	cout << "══╣";
}
void Print_bot(int level)
{
	int L;
	if (level == 1)
		L = 9;
	else if (level == 2)
		L = 16;
	else
		L = 30;
	cct_setcolor(0, 7);
	cout << endl;
	cout << "  ";
	cct_setcolor(15, 0);
	cout << "╚";
	for (int i = 0; i < L-1; i++) {
		cout << "══╩";
	}
	cout << "══╝";
}
void Graph_1(int know)            //画表盘
{
	int color;
	if (know == 0)
		color = 6;
	else
		color = 7;
	cct_setconsoleborder(59, 35, 59, 35);
	cct_gotoxy(0, 1);
	cct_setfontsize("点阵字体",14,0);
	for (int i = 0; i < 9; i++) {
		cout << "     ";
		cout << i + 1;
	}
	cout << endl;
	Print_top(1);
	int i = 0;
	for (; i < 8; i++) {
		Print_2(1,color);
		Print_3(i,1,color);
		Print_mid(1);
	}
	Print_2(1,color);
	Print_3(i,1,color);
	Print_bot(1);
	cct_setcolor(0, 7);
	cout << endl<<endl;
	
	
}
void Graph_2(int know)
{
	int color;
	if (know == 0)
		color = 6;
	else
		color = 7;
	cct_setconsoleborder(101, 60, 110, 60);
	cct_gotoxy(0, 1);
	cct_setfontsize("点阵字体",14,0);
	for (int i = 0; i < 16; i++) {
		if (i + 1 > 9)
			cout << "    ";
		else
			cout << "     ";
		cout << i + 1;
	}
	cout << endl;
	Print_top(2);
	int i = 0;
	for (; i < 15; i++) {
		Print_2(2,color);
		Print_3(i,2,color);
		Print_mid(2);
	}
	Print_2(2,color);
	Print_3(i,2,color);
	Print_bot(2);
	cct_setcolor(0, 7);
	cout << endl<<endl;
	int a, b, c, d;
	//cct_getconsoleborder(a, b, c, d);
	//cout << a << " " << b << " " << c << " " << d;
}
void Graph_3(int know)
{
	int color;
	if (know == 0)
		color = 6;
	else
		color = 7;
	cct_setconsoleborder(185, 60, 200, 60);
	cct_gotoxy(0, 1);
	cct_setfontsize("点阵字体", 14, 0);
	for (int i = 0; i < 30; i++) {
		if (i + 1 > 9)
			cout << "    ";
		else
			cout << "     ";
		cout << i + 1;
	}
	cout << endl;
	Print_top(3);
	int i = 0;
	for (; i < 15; i++) {
		Print_2(3,color);
		Print_3(i, 3,color);
		Print_mid(3);
	}
	Print_2(3,color);
	Print_3(i, 3,color);
	Print_bot(3);
	cct_setcolor(0, 7);
	cout << endl << endl;
}
void Graph_1_array(char zhadan[][9])//画出内部数组
{
	int x=1, y=-1;
	char c;
	for (int i = 0; i < 9; i++) {
		x += 3;
		y = -1;
		for (int j = 0; j < 9; j++) {
			y +=6;
			c = zhadan[i][j];
			if (c == '*')
				cct_showch(y, x, c, 7, 0, 1);
			else if (c == '0')
				;
			else
				cct_showch(y, x, c, 7, c-'0', 1);
		}
		
	}
	cct_gotoxy(0, 33);
	cct_setcolor(0, 7);
	//cct_showch(5, 4, '0', 7, 1);
}
	
void Graph_2_array(char zhadan[][16])
{
	int x = 1, y = -1;
	char c;
	for (int i = 0; i < 16; i++) {
		x += 3;
		y = -1;
		for (int j = 0; j < 16; j++) {
			y += 6;
			c = zhadan[i][j];
			if (c == '*')
				cct_showch(y, x, c, 7, 0, 1);
			else if (c == '0')
				;
			else
				cct_showch(y, x, c, 7, c - '0', 1);
		}

	}
	cct_gotoxy(0, 55);
	cct_setcolor(0, 7);
	//cct_showch(5, 4, '0', 7, 1);
}

void Graph_3_array(char zhadan[][30])
{
	int x = 1, y = -1;
	char c;
	for (int i = 0; i < 16; i++) {
		x += 3;
		y = -1;
		for (int j = 0; j < 30; j++) {
			y += 6;
			c = zhadan[i][j];
			if (c == '*')
				cct_showch(y, x, c, 7, 0, 1);
			else if (c == '0')
				;
			else
				cct_showch(y, x, c, 7, c - '0', 1);
		}

	}
	cct_gotoxy(0, 55);
	cct_setcolor(0, 7);
	//cct_showch(5, 4, '0', 7, 1);
}

int Show_Mouse(int level,int num,char* zhandan,int &X,int& Y,int &tag)
{
	cct_enable_mouse();
	int a = 0, b = 0, c = 0, d = 0, e = 0;
	while(1){

		cct_read_keyboard_and_mouse(b, a, c, d, e);//注意！！ab顺序
		if (num == 6 && c == MOUSE_LEFT_BUTTON_CLICK)//退出
			return -1;
		if ((num == 8 ||num==9)&& d == 27)//退出
			return -1;
		if (num == 9 && d == 32) {
			tag = 3;
			return 0;
		}
		//cout << a << " " << b;
		if (level == 1) {
			cct_gotoxy(0, 31);
			cct_showstr(0, 31, "    ", 0, 7, 1);
			cct_gotoxy(0, 31);
			cct_setcolor(0, 7);
			int tag1=0,tag0=0;
			cout << "[当前光标] ";
			if (a < 3 || a>28)
				tag0 = 0;
			else if (a % 3 == 0 || a % 3 == 1)
				tag0 = 1;

			if (b - 1 < 3 || b - 1 > 54)
				tag1 = 0;
			else if ((b - 4) % 6 == 0)
				tag1 = 1;
			else if ((b - 5) % 6 == 0)
				tag1 = 1;
			else if ((b - 6) % 6 == 0)
				tag1 = 1;
			else if ((b - 7) % 6 == 0)
				tag1 = 1;
			if (tag1*tag0 == 1) {
				cout << (char)(a / 3 + 'A'-1 ) << "行 ";
				if (b <= 7 && b >= 4)
					cout << "1列";
				else if ((b - 1) % 6 == 0)
					cout << (char)(b-1) / 6 << "列";
				else
					cout << (b -1)/ 6 +1 << "列";
				if (num == 7 && c == MOUSE_LEFT_BUTTON_CLICK) {//展开，只有合法坐标内才能点击
					X = a / 3 - 1;
					Y = (b - 1) / 6;
					return -1;
				}
				else if (num == 8  ) {//展开，只有合法坐标内才能点击
					if (c == MOUSE_LEFT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 0;
						return 1;
					}
					else if (c == MOUSE_RIGHT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 1;
						return 0;
					}
					
				}
				else if (num == 9) {//展开，只有合法坐标内才能点击
					if (c == MOUSE_LEFT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 0;
						return 1;
					}
					else if (c == MOUSE_RIGHT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 1;
						return 0;
					}

				}
			}
			else {
				cout << "非法坐标";
			}
		}
		else if (level == 2) {
			cct_gotoxy(0, 53);
			cct_showstr(0, 53, "    ", 0, 7, 1);
			cct_gotoxy(0, 53);
			cct_setcolor(0, 7);
			int tag1 = 0, tag0 = 0;
			cout << "[当前光标] ";
			if (a < 3 || a>49)
				tag0 = 0;
			else if (a % 3 == 0 || a % 3 == 1)
				tag0 = 1;

			if (b - 1 < 3 || b - 1 > 96)
				tag1 = 0;
			else if ((b - 4) % 6 == 0)
				tag1 = 1;
			else if ((b - 5) % 6 == 0)
				tag1 = 1;
			else if ((b - 6) % 6 == 0)
				tag1 = 1;
			else if ((b - 7) % 6 == 0)
				tag1 = 1;
			if (tag1*tag0 == 1) {
				cout << (char)(a / 3 + 'A' - 1) << "行 ";
				if (b <= 7 && b >= 4)
					cout << "1列";
				else if ((b - 1) % 6 == 0)
					cout << (b - 1) / 6   << "列";
				else
					cout << (b - 1) / 6 +  1<< "列";
				if (num == 7 && c == MOUSE_LEFT_BUTTON_CLICK) {//展开
					int X = a / 3 - 1;
					int Y = (b - 1) / 6;
					return -1;
				}
				else if (num == 8) {//展开，只有合法坐标内才能点击
					if (c == MOUSE_LEFT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 0;
						return 1;
					}
					else if (c == MOUSE_RIGHT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 1;
						return 0;
					}
				}
				else if (num == 9) {//展开，只有合法坐标内才能点击
					if (c == MOUSE_LEFT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 0;
						return 1;
					}
					else if (c == MOUSE_RIGHT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 1;
						return 0;
					}
				}
			}
			else {
				cout << "非法坐标";
			}
		}
		else {
			cct_gotoxy(0, 53);
			cct_showstr(0, 53, "    ", 0, 7, 1);
			cct_gotoxy(0, 53);
			cct_setcolor(0, 7);
			int tag1 = 0, tag0 = 0;
			cout << "[当前光标] ";
			if (a < 3 || a>49)
				tag0 = 0;
			else if (a % 3 == 0 || a % 3 == 1)
				tag0 = 1;

			if (b - 1 < 3 || b - 1 > 180)
				tag1 = 0;
			else if ((b - 4) % 6 == 0)
				tag1 = 1;
			else if ((b - 5) % 6 == 0)
				tag1 = 1;
			else if ((b - 6) % 6 == 0)
				tag1 = 1;
			else if ((b - 7) % 6 == 0)
				tag1 = 1;
			if (tag1*tag0 == 1) {
				cout << (char)(a / 3 + 'A' - 1) << "行 ";
				if (b <= 7 && b >= 4)
					cout << "1列";
				else if ((b - 1) % 6 == 0)
					cout << (b - 1) / 6  << "列";
				else
					cout << (b - 1) / 6 + 1<< "列";
				if (num == 7 && c == MOUSE_LEFT_BUTTON_CLICK) {//展开
					int X = a / 3 - 1;
					int Y = (b - 1) / 6;
					return -1;
				}
				else if (num == 8) {//展开，只有合法坐标内才能点击
					if (c == MOUSE_LEFT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 0;
						return 1;
					}
					else if (c == MOUSE_RIGHT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 1;
						return 0;
					}
				}
				else if (num == 9) {//展开，只有合法坐标内才能点击
					if (c == MOUSE_LEFT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 0;
						return 1;
					}
					else if (c == MOUSE_RIGHT_BUTTON_CLICK) {
						X = a / 3 - 1;
						Y = (b - 1) / 6;
						tag = 1;
						return 0;
					}
				}
			}
			else {
				cout << "非法坐标";
			}
		}

	}
	
}
/*void Is_Click_Begin(int level, int num, char* zhandan)
{
	while (Is_Begin(zhadan, 16, 30, 3, X, Y) == 0) {
		Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
		//Print_zhadan(zhadan3[0], 16, 30);
		continue;
	}
}*/