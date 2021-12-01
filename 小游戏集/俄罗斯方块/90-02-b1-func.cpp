#include"90-02-b1.h"

int Init(int &a,int&b)//选择尺寸
{
	while (1) {
		cct_cls();
		cout << "选择高度（18-26） :";
		cin >> a;
		while (cin.fail()) {        //防止死循环
			cin.clear();
			cin.ignore(100, '\n');
			cct_cls();
			cout << "选择高度（18-26） :";
			cin >> a;
		}
		if (a <= 26 && a >= 18)
			break;
		else
			continue;
	}
	while (1) {
		cct_cls();
		cout << "选择宽度(4-7)*3 :";
		cin >> b;
		while (cin.fail()) {        //防止死循环
			cin.clear();
			cin.ignore(100, '\n');
			cct_cls();
			cout << "选择宽度(4-7)*3 :";
			cin >> b;
		}
		if (b <= 21 && b >= 12 && b % 3 == 0)
			break;
		else
			continue;
	}
	Show_Map(a, b);
	return 1;
}

void Init_2(int a,int b,int D[40][5][5])  //显示数字4种状态
{
	int x;//序号
	while (1) {
		cct_cls();
		cct_setfontsize("新宋体", 20);
		cout << "选择0-9: " << endl;
		cin >> x;
		while (cin.fail()) {        //防止死循环
			cin.clear();
			cin.ignore(100, '\n');
			cct_cls();
			cct_setfontsize("新宋体", 20);
			cout << "选择0-9: " << endl;
			cin >> x;
		}
		if (x <= 9 && x >= 0)
			break;
		else
			continue;
	}
	cct_setfontsize("新宋体", 10);
	Show_Map(18, 18);
	Show_Block(x,18,18,D);

}

void Init_3(int a, int b, int Di[40][5][5])//体验旋转
{
	int x;//序号
	while (1) {
		cct_cls();
		cct_setfontsize("新宋体", 20);
		cout << "选择0-9: " << endl;
		cin >> x;
		while (cin.fail()) {        //防止死循环
			cin.clear();
			cin.ignore(100, '\n');
			cct_cls();
			cct_setfontsize("新宋体", 20);
			cout << "选择0-9: " << endl;
			cin >> x;
		}
		if (x <= 9 && x >= 0)
			break;
		else
			continue;
	}
	cct_setfontsize("新宋体", 10);
	Show_Map(a, b);
	Show_Roll_Block(x, a, b,Di);
}

void Init_4(int a, int b, int Di[40][5][5])//单个数字下落过程
{
	int x;//序号
	while (1) {
		cct_cls();
		cct_setfontsize("新宋体", 20);
		cout << "选择0-9: " << endl;
		cin >> x;
		while (cin.fail()) {        //防止死循环
			cin.clear();
			cin.ignore(100, '\n');
			cct_cls();
			cct_setfontsize("新宋体", 20);
			cout << "选择0-9: " << endl;
			cin >> x;
		}
		if (x <= 9 && x >= 0)
			break;
		else
			continue;
	}
	cct_setfontsize("新宋体", 10);
	Show_Map(a, b);
	int time = 0;
	char c0=0,c=0;
	int A=0, B=0, C=0, D=0, E=0;
	
	int X = -2;
	int Y = b / 2;
	int L = 0;
	Print_Digital(x,L,X,Y,Di);
	cct_gotoxy(0, a * 3 + 3);
	

	while (1) {       
		if (time > 100) {   //
			time = 0;
			if (Can_Move(x, L%4, X+1, Y, Di, a, b))
				Down_Move(x, L%4,X, Y,Di);
			cct_gotoxy(0, a * 3 + 3);
			//X++;
			cct_setcolor(0, 7);
		}
		if (_kbhit()) {
			c0 = _getch();
			if (c0 == 27)
				return;
			
			if (c0 == KB_ARROW_UP) {
				if (Can_Move(x, (L+1)%4 , X, Y, Di, a, b)) {
					L++;
					Roll_Move(x, L , X, Y, Di);
				}
			}
			if (c0 == KB_ARROW_LEFT) {
				if (Can_Move(x, L % 4, X, Y - 1, Di, a, b)){
					//Y--;
					Left_Move(x, L % 4, X, Y, Di);
					
				}
			}
			if (c0 == KB_ARROW_RIGHT) {
				if (Can_Move(x, L % 4, X, Y + 1, Di, a, b)) {
					//Y++;
					Right_Move(x, L % 4, X, Y, Di);
					
				}
			}
			if (c0 == KB_ARROW_DOWN) {
				if (Can_Move(x, L % 4, X + 1, Y, Di, a, b)) {
					//X++;
					Down_Move(x, L % 4, X, Y, Di);
					
				}
			}
		}
		time++;
		Sleep(1);            //游戏循环周期1ms，如果设得和下落周期一样，会导致键盘输入响应很慢
	}
}

void Init_5(int a, int b, int Di[40][5][5])
{
	//申请一个Map二维数组，大小为a * b，保存已经到底得方块矩阵，又得给画图和移动函数加一个Map参数了。。
	int** Map = new int* [a];   //申请a个指向一维数组的指针
	for (int i = 0; i < a; i++) {
		Map[i] = new int[b];            //a个数组，每个数组长度为b
		for (int j = 0; j < b; j++) {
			Map[i][j] = 0;            //初始化置0
		}
	}
	Show_Map(a, b);

	int x  = get_next_num(true, 123);
	char c0 = 0, c = 0;
	int A = 0, B = 0, C = 0, D = 0, E = 0;
	int bottom = 0;//判断是否到底

	int X = -2;
	int Y = b / 2;
	int L = 0;

	SetTimer(0, 0, 1000, NULL);
	MSG   msg;

	while (1) {
		X = -2;
		Y = b / 2;
		L = 0;
		x = get_next_num();
		//x = 1;
		Print_Digital(x, L, X, Y, Di);
		cct_gotoxy(0, a * 3 + 3);
		while (1) {
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_TIMER)
				{
					DispatchMessage(&msg);
					//一定时间的下落
					if (Can_Move_Dy(x, L % 4, X + 1, Y, Di, a, b, Map) == 1)
						Down_Move(x, L % 4, X, Y, Di);
					else {                            //退出当前循环，开始下落第二个数字
						if (Map_Record(Map, a, b, Di, x, L % 4, X, Y))      //在数组里做标记
							bottom=1;
						else
							return;//Game Over
					}
				}
			}
			if (bottom){
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
					if (Can_Move_Dy(x, (L + 1)%4, X, Y, Di, a, b,Map)) {
						L++;
						Roll_Move(x, L, X, Y, Di);
					}
				}
				if (c0 == KB_ARROW_LEFT) {
					if (Can_Move_Dy(x, L % 4, X, Y - 1, Di, a, b,Map)) {
						//Y--;
						Left_Move(x, L % 4, X, Y, Di);
					}
				}
				if (c0 == KB_ARROW_RIGHT) {
					if (Can_Move_Dy(x, L % 4, X, Y + 1, Di, a, b,Map)) {
						//Y++;
						Right_Move(x, L % 4, X, Y, Di);
					}
				}
				if (c0 == KB_ARROW_DOWN) {
					if (Can_Move_Dy(x, L % 4, X + 1, Y, Di, a, b,Map))
						Down_Move(x, L % 4, X, Y, Di);
				}
			}
			Sleep(1);            //游戏循环周期1ms，如果设得和下落周期一样，会导致键盘输入响应很慢
		}
	}
}

void Init_6(int a, int b, int Di[40][5][5],int god)
{
	//申请一个Map二维数组，大小为a * b，保存已经到底得方块矩阵，又得给画图和移动函数加一个Map参数了。。
	int** Map = new int* [a];   //申请a个指向一维数组的指针
	for (int i = 0; i < a; i++) {
		Map[i] = new int[b];            //a个数组，每个数组长度为b
		for (int j = 0; j < b; j++) {
			Map[i][j] = 0;            //初始化置0
		}
	}

	Show_Map(a, b);
	
	//int time = 0,time_count=100;之前用sleep时的变量
	int score = 0;
	int level = 0;//加速等级,用于定时器判断
	int x;   //当前数字
	if (god)
		x = 1;
	else
		x = get_next_num(true, 1);
	int list[30] = { 1 ,7, 4, 0, 9, 4, 8, 8, 2, 4, 5, 5, 1, 7, 1, 1, 5, 2, 7, 6, 1, 4, 2, 3, 2, 2, 1, 6, 8, 5 };
	int count = 1;//下落序列号
	int Next_Number = list[count + 1];//下一个落下的数字
	int time = 1000;//初始时间间隔
	
	int bottom = 0;

	cct_showstr(0, a*3 + 3, "下一个数字：", 0, 4, 1);
	if (god)
		cout << 1;
	else
		cout << Next_Number;
	cct_showstr(0, a * 3 + 4, "分数：", 0, 4, 1);
	cout << score;
	cct_setcolor(0, 7);
	char c0 = 0, c = 0;
	int A = 0, B = 0, C = 0, D = 0, E = 0;

	int X = -2;
	int Y = b / 2;
	int L = 0;
	MSG   msg;
	UINT timer_id = SetTimer(NULL, level, time, NULL);//上次提交时定时器没有关闭，这次可以了

	while (1) {
		X = -2;
		Y = b / 2;
		L = 0;
		if (god)
			x = 1;
		else
			x = get_next_num();
		
		Next_Number = list[++count ];
		cct_showstr(0, a * 3 + 3, "下一个数字：", 0, 4, 1);
		if (god)
			cout << 1;
		else
			cout << Next_Number;
		cct_showstr(0, a * 3 + 4, "分数：", 0, 4, 1);
		cout << score;
		cct_setcolor(0, 7);
		//x = 1;
		Print_Digital(x, L, X, Y, Di);
		cct_gotoxy(0, a * 3 + 3);
		while (1) {
			
			if ((score / 15) > level && time > 300) {
				KillTimer(NULL, timer_id);
				level = score / 15;
				time -= 100;
				timer_id=SetTimer(NULL, level, time, NULL);//重置计时器的时间间隔
			}
			
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_TIMER)
				{
					DispatchMessage(&msg);
					//一定时间的下落
					if (Can_Move_Dy(x, L % 4, X + 1, Y, Di, a, b, Map) == 1)
						Down_Move(x, L % 4, X, Y, Di);
					else {                            //退出当前循环，开始下落第二个数字
						if (Map_Record_score(Map, a, b, Di, x, L % 4, X, Y,score))      //在数组里做标记
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
					if (Can_Move_Dy(x, (L + 1) % 4, X, Y, Di, a, b, Map)) {
						L++;
						Roll_Move(x, L, X, Y, Di);
					}
				}
				if (c0 == KB_ARROW_LEFT) {
					if (Can_Move_Dy(x, L % 4, X, Y - 1, Di, a, b, Map)) {
						//Y--;
						Left_Move(x, L % 4, X, Y, Di);
					}
				}
				if (c0 == KB_ARROW_RIGHT) {
					if (Can_Move_Dy(x, L % 4, X, Y + 1, Di, a, b, Map)) {
						//Y++;
						Right_Move(x, L % 4, X, Y, Di);
					}
				}
				if (c0 == KB_ARROW_DOWN) {
					if (Can_Move_Dy(x, L % 4, X + 1, Y, Di, a, b, Map))
						Down_Move(x, L % 4, X, Y, Di);
				}
			}
			
			Sleep(0.1);            //游戏循环周期1ms，如果设得和下落周期一样，会导致键盘输入响应很慢
		}
		
	}
}

bool Map_Record(int** M,int a,int b,int D[40][5][5],int x,int L,int X,int Y)
{
	int x0=0, y0=0;              //记录
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {//X,Y是数字中心点坐标
			x0 = (X - 2 + i);
			y0 = Y - 2 + j;
			if (x0 <= 0)
				return 0;
			if (D[x * 4 + L][i][j] == 1) {
				M[x0][y0]= 1;
			}
		}
	}
	                                   //检测有没有可以消除的行
	for (int i = a-1; i > 0; i--) {
		int tag = 1;
		for (int j = 0; j < b; j++) {
			if (M[i][j] == 0) {
				tag = 0;
				break;
			}
		}
		if (tag == 1){
			Map_Clear(a,b,M,i);
			i++;//消除一行后回退
		}
	}

	for (int i = 0; i < b; i++) {     //Game Over
		if (M[0][i] == 1)
			return 0;
	}
	return 1;
}
bool Map_Record_score(int** M, int a, int b, int D[40][5][5], int x, int L, int X, int Y,int& score)
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
			Map_Clear(a, b, M, i);
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
void Map_Clear(int a,int b,int **M,int I) //消除一行,改完数组直接刷新生成
{
	for (int i = I; i > 0; i--) {
		for (int j = 0; j < b; j++) {
			M[i][j] = M[i - 1][j];
		}
	}
	for (int j = 0; j < b; j++) {
		M[0][j] = 0;
	}
	Map_Print(a, b, M);
}

void Map_Print(int a, int b, int** M)
{
	//cct_cls();
	Show_Map(a,b);
	cct_setcolor(0, 0);
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if (M[i][j] == 1)
				Show_Block_Base(i*3, j*6);//坐标系变换
			//else
				//Erase_Block_Base(i*3+1, j*6+2);
			cct_setcolor(0, 0);
		}
		
	}
	
}

bool Can_Move(int n,int L,int X,int Y,int D[40][5][5],int a,int b)//判断能不能移动到这个位置
{
	//判断Y
	if (Y < 0 || Y >= b || X >= a)
		return 0;
	if (Y == 0) {
		for (int i = 0; i < 5; i++) {
			if (D[4 * n + L][i][0]==1) {
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
		/*for (int i = 0; i < 5; i++) {
			if (Digital[4 * n + L][i][1] == 1) {
				return 0;
			}
		}*/
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
	
	return 1;
}

bool Can_Move_Dy(int n, int L, int X, int Y, int D[40][5][5], int a, int b,int** M)//新增加了地图判断
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
		/*for (int i = 0; i < 5; i++) {
			if (Digital[4 * n + L][i][1] == 1) {
				return 0;
			}
		}*/
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
			if((x0>=0)&&(y0>=0)&&(x0<a)&&(y0<b))   //一开始坐标为负数
				if ((D[n * 4 + L][i][j] == 1) && M[x0][y0] == 1)
				return 0;
		}
	}


	return 1;
}

bool Left_Move(int n,int L,int& X, int& Y, int D[40][5][5])
{

	Erase_Digital(n,L,X, Y,D);
	Print_Digital(n,L,X,--Y,D);
	return 1;
}

bool Right_Move(int n, int L, int& X, int& Y, int D[40][5][5])
{
	Erase_Digital(n, L, X, Y, D);
	Print_Digital(n,L,X,++Y,D);
	
	return 1;
}

bool Down_Move(int n, int L, int& X, int& Y, int D[40][5][5])
{
	Erase_Digital(n, L, X, Y, D);
	Print_Digital(n,L,++X,Y,D);
	return 1;
}

bool Roll_Move(int n, int L, int& X, int& Y, int D[40][5][5])
{
	Erase_Digital(n, (L-1)%4, X, Y, D);
	Print_Digital(n,L%4,X,Y,D);
	return 1;
}

void Show_Map(const int x,const int y)
{
	int color = 12;                         //画边框
	cct_setfontsize("新宋体", 10);
	cct_setconsoleborder(y * 6 + 4, x*3+10, y * 6 + 10, x * 3 + 10 );
	cct_cls();
	cct_showstr(0, 0, "■", 0, color, y*3+2, -1);
	for (int i = 1; i < x * 3+1; i++) {
		cct_showstr(0,i , "■", 0, color, 1, -1);
		cct_showstr(y*6+2,i, "■", 0, color, 1, -1);
	}
	cct_showstr(0, x * 3 + 1, "■", 0, color, y * 3 + 2, -1);

	cct_gotoxy(2, 1);
	for (int i = 0; i < x; i++) {
		//int color = 15;
		Draw_Line(y,i);
			/*if (i % 2 == 0) {    //棋盘底色
				if (j % 2 == 1)
					color = 7;
				else
					color = 15;
			}
			else {
				if (j % 2 == 1)
					color = 15;
				else
					color = 7;
			}*/
			
			//cct_showstr(2+j*6, 1+i*3, "      ", color, 0, 1);        //画底纹cct速度太慢了
			//cct_showstr(2+j*6, 2+(i)*3,     "      ", color, 0, 1);
			//cct_showstr(2+j*6, 3+(i)*3, "      ", color, 0, 1);
			/*cct_setcolor(color, 0);
			cct_gotoxy(2 + j * 6, 1 + i * 3);
			cout << "      " ;
			cct_gotoxy(2 + j * 6, 2 + (i) * 3);
			cout << "      ";
			cct_gotoxy(2 + j * 6, 3 + (i) * 3);
			cout << "      ";*/
		
	}
	
	cct_gotoxy(0, x * 3 + 2);
	cct_setcolor(0, 7);
	//cout << endl;
	cout << x<<"×"<<y << endl;
	
}

void Draw_Line(int b,int a)
{
	int color = 7;
	
	for (int j = 0; j < 3; j++) {
		cct_gotoxy(2, 1 + a * 3 + j);
		for (int i = 0; i < b; i++) {
			/*if (i % 2 == 1)           //条纹底色
				color = 7;
			else
				color = 15;*/
			cct_setcolor(color, 0);
			cout << "      ";
		}
		
		
	}
	
}

void Show_Block(int n, int a, int b,int D[40][5][5])
{
	for (int k0 = 0; k0 < 2; k0++) {
		for (int k = 0; k < 2; k++) {     //选择左右中形态
			Print_Digital(n, k0*2+k, 5 + k0 * 8, 5+k*8 ,D);  //以大格为单位
		}
	}
	
	cct_setcolor(0, 7);
	cct_gotoxy(0,a*3+3);
	cout << endl;
	
}

void Show_Block_Base(int X,int Y)
{
	//cct_setcolor(0, 7);
	cct_showstr(Y + 2, X + 1, "┏━┓", 10, 0, 1);
	cct_showstr(Y + 2, X + 2, "┃●┃", 10, 0, 1);
	cct_showstr(Y + 2, X + 3, "┗━┛", 10, 0, 1);
	cct_setcolor(0, 7);
	
}

void Print_Digital(int n,int L,int X,int Y, int D[40][5][5])  //在指定位置画处数字，以5*5矩阵中线点为坐标基准
{                                                             //以大方块作为坐标细，在后续函数中转换成实际画图坐标系
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (D[(n*4+L)][i][j] == 1) {
				//Show_Block_Base(k * 20 + i * 3 + 3, 20 + j * 6);
				if(((X + i) * 3 - 6)>=0)
					Show_Block_Base((X+i)*3-6, (Y+j)*6-12);//把块坐标转换成画图坐标
				//Show_Block_Base(20+i*3, (k)*36+3 + j * 6);
			}
			//else {
				//Erase_Block_Base(X * 3 - 6 + i * 3, Y * 6 - 12 + j * 6);
			//}
			
		}
	}
}

void Erase_Digital(int n,int L,int X, int Y,int D[40][5][5])
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (D[(n * 4 + L)][i][j] == 1) {
				if (((X + i) * 3 - 6) >= 0)
					Erase_Block_Base(X * 3 - 6 + i * 3, Y * 6 - 12 + j * 6);
			}
		}
	}
	cct_gotoxy(0, 100);
}

void Erase_Block_Base(int X, int Y) 
{
	cct_showstr(Y + 2, X + 1, "      ", 7, 0, 1);
	cct_showstr(Y + 2, X + 2,     "      ", 7, 0, 1);
	cct_showstr(Y + 2, X + 3, "      ", 7, 0, 1);
}

void Show_Roll_Block(int n,int a,int b,int Di[40][5][5]) 
{
	int A=0, B=0, C=0, D=0, E=0;
	int L = 0;
	int Esc_tag = 0;
	Print_Digital(n, L%4, a/2, b / 2,Di);  //以大格为单位
	//Print_Digital(n, L%4, 2,1, Di);
	//Show_Block_Base(0,6);
	cct_setcolor(0, 7);
	while (1) {
		while (1) {
			cct_gotoxy(0, a * 3 + 3);
			cct_read_keyboard_and_mouse(A, B, C, D, E);
			if (E==KB_ARROW_UP) {
				break;
			}
			if (D == 27) {
				Esc_tag = 1;
				break;
			}
		}
		if (Esc_tag)
			break;
		
		//system("cls");
		cct_setfontsize("新宋体", 10);
		//Show_Map(a, b);
		Erase_Digital(n, L%4, a/2, b/2, Di);
		L++;
		Print_Digital(n, L % 4, a / 2, b / 2,Di);
		//Print_Digital(n, L%4, 2, 1, Di);//实验用
		cct_setcolor(0, 7);
		cct_gotoxy(0, a * 3 + 3);

	}
	cct_setcolor(0, 7);
	cct_gotoxy(0, a * 3 + 3);
	cout <<endl;

}

int get_next_num(const bool new_seed , const unsigned int seed)
{
	if (new_seed)
		srand(seed);

	return rand() % 10;
}

