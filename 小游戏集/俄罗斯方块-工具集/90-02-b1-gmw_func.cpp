#include"90-02-b1-gmw.h"

void Show_Map(CONSOLE_GRAPHICS_INFO& MyCGI,int row, int col)
{
	gmw_draw_frame(&MyCGI);	
}

int get_next_num(const bool new_seed, const unsigned int seed)
{
	if (new_seed)
		srand(seed);

	return rand() % 10;
}

void Print_Digital(CONSOLE_GRAPHICS_INFO& MyCGI,int n, int L, int X, int Y, int D[40][5][5])  //在指定位置画处数字，以5*5矩阵中线点为坐标基准
{    //以大方块作为坐标细，在后续函数中转换成实际画图坐标系

	const BLOCK_DISPLAY_INFO bdi[] = {
				{BDI_VALUE_BLANK, -1, -1, "  "},						//0不显示，用空格填充即可
				{1,  COLOR_HBLACK, -1, "〇"},				//如果给出数字1，则显示空心球
				{2,  COLOR_HGREEN, COLOR_HBLACK, "◎"},	//如果给出数字2，则显示双线空心球
				{3,  COLOR_HGREEN,COLOR_HBLACK, "★"},		//如果给出数字3，则显示星
				{4,  COLOR_HRED, -1, NULL},				//如果给出数字4，则直接显示4（NULL表示直接显示数字）
				{BDI_VALUE_END, -1, -1, NULL}			//以BDI_VALUE_END结束，一定要有!!!
	};
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_BLOCK, 0);		//无延时
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (D[(n * 4 + L)][i][j] == 1) {
				gmw_draw_block(&MyCGI, X+i-2, Y+j-2, 3, bdi);
			}
		}
	}
}

void Erase_Digital(CONSOLE_GRAPHICS_INFO& MyCGI, int n, int L, int X, int Y, int D[40][5][5])
{
	const BLOCK_DISPLAY_INFO bdi[] = {
				{BDI_VALUE_BLANK, COLOR_WHITE, -1, "  "},						//0不显示，用空格填充即可
				{1,  COLOR_HBLACK, -1, "〇"},				//如果给出数字1，则显示空心球
				{2,  COLOR_HGREEN, COLOR_HBLACK, "◎"},	//如果给出数字2，则显示双线空心球
				{3,  COLOR_HGREEN,COLOR_HBLACK, "★"},		//如果给出数字3，则显示星
				{4,  COLOR_HRED, -1, NULL},				//如果给出数字4，则直接显示4（NULL表示直接显示数字）
				{BDI_VALUE_END, -1, -1, NULL}			//以BDI_VALUE_END结束，一定要有!!!
	};
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (D[(n * 4 + L)][i][j] == 1) {
				if (((X + i) * 3 - 6) >= 0)
					gmw_draw_block(&MyCGI, X + i - 2, Y + j - 2, 0, bdi);
			}
		}
	}
	cct_gotoxy(0, 100);
}

void Init_6(CONSOLE_GRAPHICS_INFO& MyCGI, int& a, int& b, int D[40][5][5])
{
	
	//申请一个Map二维数组，大小为a * b，保存已经到底得方块矩阵，又得给画图和移动函数加一个Map参数了。。
	int** Map = new int* [a];   //申请a个指向一维数组的指针
	for (int i = 0; i < a; i++) {
		Map[i] = new int[b];            //a个数组，每个数组长度为b
		for (int j = 0; j < b; j++) {
			Map[i][j] = 0;            //初始化置0
		}
	}

	int score = 0;
	int level = 0;//加速等级,用于定时器判断
	int x;   //当前数字
	
	
	x=get_next_num(true, 1);

	int list[30] = { 1 ,7, 4, 0, 9, 4, 8, 8, 2, 4, 5, 5, 1, 7, 1, 1, 5, 2, 7, 6, 1, 4, 2, 3, 2, 2, 1, 6, 8, 5 };
	int count = 1;//下落序列号
	int Next_Number = list[count + 1];//下一个落下的数字
	int time = 1000;//初始时间间隔

	int bottom = 0;

	//cct_showstr(0, a * 3 + 3, "下一个数字：", 0, 4, 1);
	
	//cout << Next_Number;
	cct_showstr(MyCGI.col_num * MyCGI.CFI.block_width + 2,2, "分数：", 0, 4, 1);
	cout << score;
	cct_setcolor(0, 7);
	char c0 = 0, c = 0;
	//int A = 0, B = 0, C = 0, D = 0, E = 0;

	int X = 2;  //受限于gmw工具集的，此处不能为-2，即不能实现原来的从屏幕外下落，否则会乱。因为gmw并没有考虑画在屏幕外的部分
	int Y = b / 2;
	int L = 0;
	MSG   msg;
	UINT timer_id = SetTimer(NULL, level, time, NULL);//上次提交时定时器没有关闭，这次可以了

	while (1) {
		X = 2;//
		Y = b / 2;
		L = 0;
		
		x = get_next_num();

		Next_Number = list[++count];
		cct_showstr(MyCGI.col_num*MyCGI.CFI.block_width+2, 4, "下一个数字：", 0, 4, 1);
		cout << Next_Number;
		cct_gotoxy(MyCGI.col_num * MyCGI.CFI.block_width + 2, 10);

		cout << MyCGI.lines << " " << MyCGI.cols;
		//if (god)
			//cout << 1;
		//else
			
		cct_showstr(MyCGI.col_num * MyCGI.CFI.block_width + 2, 2, "分数：", 0, 4, 1);
		cout << score;
		cct_setcolor(0, 7);
		//x = 1;
		Print_Digital(MyCGI,x, L, X, Y, D);
		cct_gotoxy(0, a * 3 + 3);
		while (1) {

			if((score / 15) > level && time > 300) {
				KillTimer(NULL, timer_id);
				level = score / 15;
				time -= 100;
				timer_id = SetTimer(NULL, level, time, NULL);//重置计时器的时间间隔
			}

			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_TIMER)
				{
					DispatchMessage(&msg);
					//一定时间的下落
					if (Can_Move_Dy(x, L % 4, X + 1, Y, D, a, b, Map) == 1)
						Down_Move(MyCGI,x, L % 4, X, Y, D);
					else {                            //退出当前循环，开始下落第二个数字
						if (Map_Record_score(MyCGI,Map, a, b, D, x, L % 4, X, Y, score))      //在数组里做标记
							bottom = 1;
						else
							return;//Game Over
					}
				}
			}
			if (bottom) {
				bottom = 0;
				break;
			}//落下一个数字
			cct_gotoxy(0, a * 3 + 3);
			//X++;
			cct_setcolor(0, 7);

			if (_kbhit()) {
				c0 = _getch();
				if (c0 == 27)
					return;

				if (c0 == KB_ARROW_UP) {
					if (Can_Move_Dy(x, (L + 1) % 4, X, Y, D, a, b, Map)) {
						L++;
						Roll_Move(MyCGI, x, L, X, Y, D);
					}
				}
				if (c0 == KB_ARROW_LEFT) {
					if (Can_Move_Dy(x, L % 4, X, Y - 1, D, a, b, Map)) {
						//Y--;
						Left_Move(MyCGI, x, L % 4, X, Y, D);
					}
				}
				if (c0 == KB_ARROW_RIGHT) {
					if (Can_Move_Dy(x, L % 4, X, Y + 1, D, a, b, Map)) {
						//Y++;
						Right_Move(MyCGI, x, L % 4, X, Y, D);
					}
				}
				if (c0 == KB_ARROW_DOWN) {
					if (Can_Move_Dy(x, L % 4, X + 1, Y, D, a, b, Map))
						Down_Move(MyCGI, x, L % 4, X, Y, D);
				}
			}
			Sleep(0.1);            //游戏循环周期1ms，如果设得和下落周期一样，会导致键盘输入响应很慢
		}
	}
}

bool Can_Move_Dy(int n, int L, int X, int Y, int D[40][5][5], int a, int b, int** M)//新增加了地图判断
{
	//判断Y
	if (Y < 0 || Y >= b || X >= a)
		return 0;
	if (Y == 0) {
		for (int i = 0; i < 5; i++) {
			if (D[4 * n + L][i][0] == 1) {
				return 0;
			}
		}
		for (int i = 0; i < 5; i++) {
			if (D[4 * n + L][i][1] == 1) {
				return 0;
			}
		}
	}
	else if (Y == 1) {
		for (int i = 0; i < 5; i++) {
			if (D[4 * n + L][i][0] == 1) {
				return 0;
			}
		}
		
	}
	else if (Y == b - 1) {
		for (int i = 0; i < 5; i++) {
			if (D[4 * n + L][i][4] == 1) {
				return 0;
			}
		}
		for (int i = 0; i < 5; i++) {
			if (D[4 * n + L][i][3] == 1) {
				return 0;
			}
		}
	}
	else if (Y == b - 2) {
		for (int i = 0; i < 5; i++) {
			if (D[4 * n + L][i][4] == 1) {
				return 0;
			}
		}

	}
	//判断X
	if (X == a - 1) {
		for (int i = 0; i < 5; i++) {
			if (D[4 * n + L][4][i] == 1) {
				return 0;
			}
		}
		for (int i = 0; i < 5; i++) {
			if (D[4 * n + L][3][i] == 1) {
				return 0;
			}
		}
	}
	else if (X == a - 2) {
		for (int i = 0; i < 5; i++) {
			if (D[4 * n + L][4][i] == 1) {
				return 0;
			}
		}
	}
	//判断Map
	int x0, y0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			x0 = X - 2 + i;
			y0 = Y - 2 + j;
			if ((x0 >= 0) && (y0 >= 0) && (x0 < a) && (y0 < b))   //一开始坐标为负数
				if ((D[n * 4 + L][i][j] == 1) && M[x0][y0] == 1)
					return 0;
		}
	}


	return 1;
}

bool Left_Move(CONSOLE_GRAPHICS_INFO& MyCGI,int n, int L, int& X, int& Y, int D[40][5][5])
{
	Erase_Digital(MyCGI, n, L, X, Y, D);
	Print_Digital(MyCGI,n, L, X, --Y, D);
	return 1;
}

bool Right_Move(CONSOLE_GRAPHICS_INFO& MyCGI,int n, int L, int& X, int& Y, int D[40][5][5])
{
	Erase_Digital(MyCGI, n, L, X, Y, D);
	Print_Digital(MyCGI, n, L, X, ++Y, D);
	return 1;
}

bool Down_Move(CONSOLE_GRAPHICS_INFO& MyCGI,int n, int L, int& X, int& Y, int D[40][5][5])
{
	Erase_Digital(MyCGI, n, L, X, Y, D);
	Print_Digital(MyCGI,n, L, ++X, Y, D);
	return 1;
}

bool Roll_Move(CONSOLE_GRAPHICS_INFO& MyCGI,int n, int L, int& X, int& Y, int D[40][5][5])
{
	Erase_Digital(MyCGI, n, (L - 1) % 4, X, Y, D);
	Print_Digital(MyCGI,n, L % 4, X, Y, D);
	return 1;
}

bool Map_Record_score(CONSOLE_GRAPHICS_INFO& MyCGI,int** M, int a, int b, int D[40][5][5], int x, int L, int X, int Y, int& score)
{
	int H = 0;
	int x0 = 0, y0 = 0;              //记录
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {//X,Y是数字中心点坐标
			x0 = (X - 2 + i);
			y0 = Y - 2 + j;
			if (x0 <= 0)
				return 0;
			if (D[x * 4 + L][i][j] == 1) {
				M[x0][y0] = 1;
			}
		}
	}
	//检测有没有可以消除的行
	for (int i = a - 1; i > 0; i--) {
		int tag = 1;
		for (int j = 0; j < b; j++) {
			if (M[i][j] == 0) {
				tag = 0;
				break;
			}
		}
		if (tag == 1) {
			Map_Clear(MyCGI,a, b, M, i);
			H++;
			i++;//消除一行后回退
		}
	}
	switch (H)
	{
	case 1:
		score += 1;
		break;
	case 2:
		score += 3;
		break;
	case 3:
		score += 6;
		break;
	case 4:
		score += 10;
		break;
	case 5:
		score += 15;
		break;
	}
	for (int i = 0; i < b; i++) {     //Game Over
		if (M[0][i] == 1)
			return 0;
	}
	return 1;
}

void Map_Clear(CONSOLE_GRAPHICS_INFO& MyCGI,int a, int b, int** M, int I) //消除一行,改完数组直接刷新生成
{
	for (int i = I; i > 0; i--) {
		for (int j = 0; j < b; j++) {
			M[i][j] = M[i - 1][j];
		}
	}
	for (int j = 0; j < b; j++) {
		M[0][j] = 0;
	}
	Map_Print(MyCGI,a, b, M);
}
void Map_Print(CONSOLE_GRAPHICS_INFO& MyCGI,int a, int b, int** M)
{
	const BLOCK_DISPLAY_INFO bdi[] = {
				{BDI_VALUE_BLANK, -1, -1, "  "},						//0不显示，用空格填充即可
				{1,  COLOR_HBLACK, -1, "〇"},				//如果给出数字1，则显示空心球
				{2,  COLOR_HGREEN, COLOR_HBLACK, "◎"},	//如果给出数字2，则显示双线空心球
				{3,  COLOR_HGREEN,COLOR_HBLACK, "★"},		//如果给出数字3，则显示星
				{4,  COLOR_HRED, -1, NULL},				//如果给出数字4，则直接显示4（NULL表示直接显示数字）
				{BDI_VALUE_END, -1, -1, NULL}			//以BDI_VALUE_END结束，一定要有!!!
	};
	//cct_cls();
	Show_Map(MyCGI,a, b);
	cct_setcolor(0, 0);
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if (M[i][j] == 1)
				gmw_draw_block(&MyCGI, i, j, 3, bdi);
			cct_setcolor(0, 0);
		}

	}	

}