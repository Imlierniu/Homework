#include"90-01-b2-mine_sweeper.h"

void Set_zhadan(int coord[][2], char* zhadan,int a, int b,int x)
{
	for (int i = 0; i < a*b; i++) {   //初始化置‘0’
		zhadan[i] = '0';
	}
	
	srand((unsigned)time(0));
	int i = x, x0, y0;
	while (i > 0)
	{
		x0 = rand() % a; //行号
		y0 = rand() % b;  //列号
		if (*(zhadan+x0*b+y0) == '*') {
			continue;
		}
		else {
			*(zhadan + x0 * b + y0) = '*';
			coord[i - 1][0] = x0;//0是行数
			coord[i - 1][1] = y0;//1是列数
			i--;
		}
	}
	Add_zhadan(coord, zhadan, a, b, x);
}

inline void add(char*zhadan,int x, int y,int a,int b)
{
	//利用作用与反作用性计数
	if ((x - 1)>=0 && (y - 1)>=0 && (*(zhadan+(x - 1)*b+(y - 1)) != '*'))
		*(zhadan + (x - 1)*b + (y - 1)) += 1;
	if ((x - 1)>=0 && (*(zhadan + (x - 1)*b + (y )) != '*'))
		*(zhadan + (x - 1)*b + (y )) += 1;
	if ((y - 1)>=0 && (*(zhadan + (x )*b + (y - 1)) != '*'))
		*(zhadan + (x)*b + (y - 1))+=1;
	if (((x - 1)>=0 && (y + 1 < b)) && (*(zhadan + (x - 1)*b + (y + 1)) != '*'))
		*(zhadan + (x - 1)*b + (y + 1))+=1;
	if ((y + 1 < b) && (*(zhadan + (x )*b + (y + 1)) != '*'))
		*(zhadan + (x)*b + (y + 1))+=1;
	if ((x + 1 < a) && (y - 1)>=0 && (*(zhadan + (x + 1)*b + (y - 1)) != '*'))
		*(zhadan + (x + 1)*b + (y - 1))+=1;
	if ((x + 1 < a) && (*(zhadan + (x + 1)*b + (y )) != '*'))
		*(zhadan + (x + 1)*b + (y))+=1;
	if ((x + 1 < a) && (y + 1 < b) && (*(zhadan + (x + 1)*b + (y + 1)) != '*'))
		*(zhadan + (x + 1)*b + (y + 1)) += 1;
}

void Add_zhadan(int coord[][2], char* zhadan, int a, int b, int x)
{
	//cout << a<<b << endl;
	for(int i=0;i<x;i++){
		int x0 = coord[i][0];
		int y0 = coord[i][1];
		
		add(zhadan,x0, y0,a,b);
	}
}
void Print_zhadan(char*zhadan,int a,int b)
{
	char biankuang[2][40];//先左后上
	for (int i = 0; i < 30; i++) {
		biankuang[0][i] = 'A' + i;
		if (i <= 8) 
			biankuang[1][i] = '1' + i;
		else
			biankuang[1][i] = 'a' + i-9;
	}
	system("cls");
	cout << "内部数组" << endl;
	cout << "  |";
	for (int i = 0; i < b; i++) {
		cout << biankuang[1][i] << " ";
	}
	cout << endl;
	cout << "--|-------------------------------------------------------------" << endl;
	for (int i = 0; i < a; i++) {
		cout << biankuang[0][i] << " |";
		for (int j = 0; j < b; j++) {
			cout <<*(zhadan + i * b + j) << " ";
		}
		cout << endl;
	}
}
void Print_unknow(int a,int b)
{
	char biankuang[2][40];//先左后上
	for (int i = 0; i < 30; i++) {
		biankuang[0][i] = 'A' + i;
		if (i <= 8)
			biankuang[1][i] = '1' + i;
		else
			biankuang[1][i] = 'a' + i - 9;
	}
	system("cls");
	cout << "内部数组" << endl;
	cout << "  |";
	for (int i = 0; i < b; i++) {
		cout << biankuang[1][i] << " ";
	}
	cout << endl;
	cout << "--|-------------------------------------------------------------" << endl;
	for (int i = 0; i < a; i++) {
		cout << biankuang[0][i] << " |";
		for (int j = 0; j < b; j++) {
			cout << "X" << " ";
		}
		cout << endl;
	}
}
void Init(int level,int num)
{
	char zhadan1[9][9];
	int coord1[10][2];
	char zhadan2[16][16];
	int coord2[40][2];
	char zhadan3[16][30];
	int coord3[99][2];
	int A[50][50];//标志数组，用于判断能否显示
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			A[i][j] = 0;
		}
	}
	if (level == 1) {
		//
		if (num == 1) {
			Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
			Print_zhadan(zhadan1[0], 9, 9);
		}
		else if (num == 2) {
			int X=-1, Y=-1,tag=0;
			Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
			Print_unknow(9, 9);
			//Print_zhadan(zhadan1[0], 9, 9);
			int i = Is_cin_right(9, 9, 1, X, Y);
			if (i== -1)
				return;
			
			while (Is_Begin(zhadan1[0],9,9,1,X,Y)==0) {
				Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
				//Print_zhadan(zhadan1[0], 9, 9);
				continue;
			}//说明isbegin成功，可以进行打开操作
			int n = 0;
			Open_Area(A,zhadan1[0], X,Y, 9,9,n,tag,num);
			
		}
		else if (num == 3) { //游戏模式
			cout << "游戏开始，青放心选择一个坐标作为你的开局，游戏保证你不会落地成盒，回车确认" << endl;
			getchar();
			int X = -1, Y = -1,tag=0;
			Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
			Print_unknow(9, 9);
			
			//Print_zhadan(zhadan1[0], 9, 9);
			int i = Is_cin_right(9, 9, 1, X, Y);
			if (i == -1)
				return;

			while (Is_Begin(zhadan1[0], 9, 9, 1, X, Y) == 0) {
				Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
				//Print_zhadan(zhadan1[0], 9, 9);
				continue;
			}//说明isbegin成功，可以进行打开操作
			int n = 0;
			Open_Area(A,zhadan1[0], X, Y, 9, 9,n,tag,num);
			while (1) {
				if (n == 71) {
					cout << "\nYou Win!" << endl;
					return;
				}
				int i = Is_cin_right(9, 9, 1, X, Y);
				if (i == -1)
					return;
				if (zhadan1[X][Y] == '*') {
					Open_Area(A, zhadan1[0], X, Y, 9, 9, n, tag, num);
					cout << "You Lost!" << endl;
					return;
				}
				else
					Open_Area(A,zhadan1[0], X, Y, 9, 9,n,tag,num);//聚合了两种打开方式
			}
		}
		else if (num == 4) {//游戏模式完全版
			cout << "游戏开始，青放心选择一个坐标作为你的开局，游戏保证你不会落地成盒，回车确认" << endl;
			getchar();
			int X = -1, Y = -1,tag=0;
			Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
			Print_unknow(9, 9);
			
			//Print_zhadan(zhadan1[0], 9, 9);
			int i = Is_cin_right(9, 9, 1, X, Y);
			if (i == -1)
				return;

			while (Is_Begin(zhadan1[0], 9, 9, 1, X, Y) == 0) {
				Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
				//Print_zhadan(zhadan1[0], 9, 9);
				continue;
			}//说明isbegin成功，可以进行打开操作
			int n = 0;
			Open_Area(A, zhadan1[0], X, Y, 9, 9, n,tag,num);
			while (1) {
				if (n == 71) {
					cout << "\nYou Win!" << endl;
					return;
				}
				tag = 0;
				int i = Is_cin_right_4(9, 9, 1, X, Y,tag);
				if (i == -1)
					return;
				if (zhadan1[X][Y] == '*'&&tag==0) {
					Open_Area(A, zhadan1[0], X, Y, 9, 9, n, tag, num);
					cout << "You Lost!" << endl;
					return;
				}
				else
					Open_Area(A, zhadan1[0], X, Y, 9, 9, n,tag,num);//聚合了两种打开方式
			}
		}
	}
	else if (level == 2) {
		
		if (num == 1) {
			Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
			Print_zhadan(zhadan2[0], 16, 16);
		}
		else if (num == 2) {
			int X = -1, Y = -1,tag=0;
			Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
			Print_unknow(16, 16);
			//Print_zhadan(zhadan2[0], 16, 16);
			int i = Is_cin_right(16, 16, 2, X, Y);
			if (i == -1)
				return;
				
			
			while (Is_Begin(zhadan2[0], 16, 16, 2,X,Y)==0) {
				Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
				//Print_zhadan(zhadan2[0], 16, 16);
				continue;
			}
			int n = 0;
			Open_Area(A,zhadan2[0], X, Y, 16,16,n,tag,num);
		}
		else if (num == 3) {
			cout << "游戏开始，青放心选择一个坐标作为你的开局，游戏保证你不会落地成盒，回车确认" << endl;
			getchar();
			int X = -1, Y = -1,n=0,tag=0;
			Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
			Print_unknow(16, 16);
			//Print_zhadan(zhadan2[0], 16, 16);
			int i = Is_cin_right(16, 16, 2, X, Y);
			if (i == -1)
				return;


			while (Is_Begin(zhadan2[0], 16, 16, 2, X, Y) == 0) {
				Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
				//Print_zhadan(zhadan2[0], 16, 16);
				continue;
			}
			Open_Area(A,zhadan2[0], X, Y, 16, 16,n,tag,num);
			while (1) {
				if (n == 216) {
					cout << "\nYou Win!" << endl;
					return;
				}
				int i = Is_cin_right(16, 16, 2, X, Y);
				if (i == -1)
					return;
				if (zhadan2[X][Y] == '*') {
					Open_Area(A, zhadan2[0], X, Y, 16, 16, n, tag, num);
					cout << "You Lost!" << endl;
					return;
				}
				else
					Open_Area(A,zhadan2[0], X, Y, 16, 16,n,tag,num);//聚合了两种打开方式
			}
		}
		else if (num == 4) {//游戏模式完全版
			cout << "游戏开始，青放心选择一个坐标作为你的开局，游戏保证你不会落地成盒，回车确认" << endl;
			getchar();
			int X = -1, Y = -1, tag = 0;
			Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
			Print_unknow(16, 16);
			//Print_zhadan(zhadan1[0], 9, 9);
			int i = Is_cin_right(16, 16, 2, X, Y);
			if (i == -1)
				return;

			while (Is_Begin(zhadan2[0], 16, 16, 2, X, Y) == 0) {
				Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
				//Print_zhadan(zhadan1[0], 9, 9);
				continue;
			}//说明isbegin成功，可以进行打开操作
			int n = 0;
			Open_Area(A, zhadan2[0], X, Y, 16, 16, n, tag,num);
			while (1) {
				tag = 0;
				if (n == 216) {
					cout << "\nYou Win!" << endl;
					return;
				}
				int i = Is_cin_right_4(16, 16, 2, X, Y, tag);
				if (i == -1)
					return;
				if (zhadan2[X][Y] == '*'&&tag==0) {
					Open_Area(A, zhadan2[0], X, Y, 16, 16, n, tag, num);
					cout << "You Lost!" << endl;
					return;
				}
				else
					Open_Area(A, zhadan2[0], X, Y, 16, 16, n, tag,num);//聚合了两种打开方式
			}
		}
	}
	else if (level == 3) {
		
		if (num == 1) {
			Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
			Print_zhadan(zhadan3[0], 16, 30);
		}
		else if (num == 2) {
			
			int X = -1, Y = -1,tag=0;
			Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
			Print_unknow(16, 30);
			//Print_zhadan(zhadan3[0], 16, 30);
			int i = Is_cin_right(16, 30, 3, X, Y);
			if (i== -1)
				return;
			
			while (Is_Begin(zhadan3[0], 16, 30, 3,X,Y)==0) {
				Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
				//Print_zhadan(zhadan3[0], 16, 30);
				continue;
			}
			int n = 0;
			Open_Area(A,zhadan3[0], X, Y, 16,30,n,tag,num);

		}
		else if (num == 3) {
			cout << "游戏开始，青放心选择一个坐标作为你的开局，游戏保证你不会落地成盒，回车确认" << endl;
			getchar();
			int X = -1, Y = -1,n=0,tag=0;
			Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
			Print_unknow(16, 30);
			//Print_zhadan(zhadan2[0], 16, 16);
			int i = Is_cin_right(16, 30, 3, X, Y);
			if (i == -1)
				return;

			while (Is_Begin(zhadan3[0], 16, 30, 3, X, Y) == 0) {
				Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
				//Print_zhadan(zhadan3[0], 16, 30);
				continue;
			}
			Open_Area(A,zhadan3[0], X, Y, 16, 30,n,tag,num);
			while (1) {
				if (n == 381) {
					cout << "\nYou Win!" << endl;
					return;
				}
				int i = Is_cin_right(16, 30, 3, X, Y);
				if (i == -1)
					return;
				if (zhadan3[X][Y] == '*'&&tag==0) {
					Open_Area(A, zhadan3[0], X, Y, 16, 30, n, tag, num);
					cout << "\nYou Lost!" << endl;
					return;
				}
				else 
					Open_Area(A,zhadan3[0], X, Y, 16, 30,n,tag,num);//聚合了两种打开方式
			}
		}
		else if (num == 4) {//游戏模式完全版
			cout << "游戏开始，青放心选择一个坐标作为你的开局，游戏保证你不会落地成盒，回车确认" << endl;
			getchar();
			int X = -1, Y = -1, tag = 0;
			Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
			Print_unknow(16, 30);
			//Print_zhadan(zhadan1[0], 9, 9);
			int i = Is_cin_right(16, 30, 3, X, Y);
			if (i == -1)
				return;

			while (Is_Begin(zhadan3[0], 16, 30, 3, X, Y) == 0) {
				Set_zhadan(coord3, zhadan3[0], 16, 30, 10);
				//Print_zhadan(zhadan1[0], 9, 9);
				continue;
			}//说明isbegin成功，可以进行打开操作
			int n = 0;
			Open_Area(A, zhadan3[0], X, Y, 16, 30, n, tag,num);
			while (1) {
				tag = 0;
				if (n == 381) {
					cout << "\nYou Win!" << endl;
					return;
				}
				int i = Is_cin_right_4(16, 30, 3, X, Y, tag);
				if (i == -1)
					return;
				if (zhadan3[X][Y] == '*'&&tag==0) {
					Open_Area(A, zhadan3[0], X, Y, 16, 30, n, tag, num);
					cout << "You Lost!" << endl;
					return;
				}
				else
					Open_Area(A, zhadan3[0], X, Y, 16, 30, n, tag,num);//聚合了两种打开方式
			}
		}
	}
}
void Init2(int level, int num)//减轻Init压力，图形部分
{
	char zhadan1[9][9];
	int coord1[10][2];
	char zhadan2[16][16];
	int coord2[40][2];
	char zhadan3[16][30];
	int coord3[99][2];
	int A[50][50];//标志数组，用于判断能否显示
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			A[i][j] = 0;
		}
	}
	if (level == 1) {
		if (num == 5) {
			Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
			Print_Graph_Base(level);
			Graph_1_array(zhadan1);
		}
		else if (num == 6)
		{
			int X = -1, Y = -1,tag=0;
			Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
			Print_Graph_Base(level);
			Graph_1_array(zhadan1);
			Show_Mouse(level, num, zhadan1[0], X, Y,tag);
		}
		else if (num == 7) {  //打开第一步
			int X = -1, Y = -1, tag = 0;
			Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
			Print_Graph_unknow(level);
			//Graph_1_array(zhadan1);
			Show_Mouse(level, num, zhadan1[0], X, Y,tag);
			while (Is_Begin(zhadan1[0], 9, 9, 1, X, Y) == 0) {
				Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
				//Print_zhadan(zhadan1[0], 9, 9);
				continue;
			}//说明isbegin成功，可以进行打开操作
			int n = 0;
			Open_Area_Graph(A, zhadan1[0], X, Y, 9, 9, n, tag, num, level);
			//cout << X << " " << Y;验证点击正确
		}
		else if (num == 8) {
			int X = -1, Y = -1, tag = 0;
			Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
			Print_Graph_unknow(level);
			cct_showstr(0, 0, "Esc退出", 0, 14, 1);
			if(Show_Mouse(level, num, zhadan1[0], X, Y,tag)==-1)
				return;
			while (Is_Begin(zhadan1[0], 9, 9, 1, X, Y) == 0) {
				Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
				continue;
			}
			int n = 0;
			Open_Area_Graph(A, zhadan1[0], X, Y, 9, 9, n, tag, num, level);
			while (1) {
				//cout << n;
				if (n == 71) {
					cout << "\nYou Win!" << endl;
					return;
				}
				int i=Show_Mouse(level, num, zhadan1[0], X, Y,tag);
				
				if (i == -1)
					return;
				if (zhadan1[X][Y] == '*'&&tag==0) {
					Open_Area_Graph(A, zhadan1[0], X, Y, 9, 9, n, tag, num, level);//聚合了两种打开方式
					cout << "You Lost!" << endl;
					return;
				}
				else
					Open_Area_Graph(A, zhadan1[0], X, Y, 9, 9, n, tag, num,level);//聚合了两种打开方式
			}

		}
		else if (num == 9) {
			int X = -1, Y = -1, tag = 0;
			Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
			
			Print_Graph_unknow(level);
			cct_showstr(0, 0, "Esc退出 Space查看时间，开启第一块时开始计时", 0, 14, 1);
			while (1) {
				int mouse = Show_Mouse(level, num, zhadan1[0], X, Y, tag);
				if (mouse == -1)
					return;
				else if (mouse == 1)//只有左键单击在有效区域才进入游戏，要不然开局点了其他键会卡死
					break;
			}
			while (Is_Begin(zhadan1[0], 9, 9, 1, X, Y) == 0) {
				Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
				continue;
			}
			double time1 = GetTickCount(),time2;
			int n = 0;
			cct_showstr(0, 0, "                                                   ", 0, 0, 1);
			Open_Area_Graph(A, zhadan1[0], X, Y, 9, 9, n, tag, num, level);
			while (1) {
				if (A[48][48] == 99) {
					time2 = GetTickCount();
					cct_showstr(0, 33, "游戏已运行 ", 0, 12, 1);
					cout << (time2 - time1) / 1000.0;
				}
				//cout << n;
				if (n == 71) {
					time2 = GetTickCount();
					cct_showstr(0, 33, "You win!共用时 ", 0, 12, 1);
					cout << (time2 - time1) / 1000.0;
					cct_setcolor(0, 7);
					return;
				}
				int i = Show_Mouse(level, num, zhadan1[0], X, Y, tag);

				if (i == -1)
					return;
				if (zhadan1[X][Y] == '*'&&tag == 0) {
					Open_Area_Graph(A, zhadan1[0], X, Y, 9, 9, n, tag, num, level);//聚合了两种打开方式
					//cout << "You Lost!" << endl;
					time2 = GetTickCount();
					cct_showstr(0, 33, "You lost!共用时 ", 0, 12, 1);
					cout << (time2 - time1) / 1000.0;
					cct_setcolor(0, 7);
					return;
				}
				else
					Open_Area_Graph(A, zhadan1[0], X, Y, 9, 9, n, tag, num, level);//聚合了两种打开方式
			}

		}
	}
	else if (level == 2) {
		if (num == 5) {
			Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
			Print_Graph_Base(level);
			Graph_2_array(zhadan2);
		}
		else if (num == 6) {
			int X = -1, Y = -1,tag=0;
			Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
			Print_Graph_Base(level);
			Graph_2_array(zhadan2);
			Show_Mouse(level,num, zhadan2[0],X,Y,tag);
		}
		else if (num == 7) {
			int X = -1, Y = -1,tag=0;
			Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
			Print_Graph_unknow(level);
			//Graph_2_array(zhadan2);
			Show_Mouse(level, num, zhadan2[0],X,Y,tag);
			while (Is_Begin(zhadan2[0], 16, 16, 2, X, Y) == 0) {
				Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
				//Print_zhadan(zhadan2[0], 16, 16);
				continue;
			}
			int n = 0;
			Open_Area_Graph(A, zhadan2[0], X, Y, 16, 16, n, tag, num,level);
		}
		else if (num == 8) {
			int X = -1, Y = -1, tag = 0;
			Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
			Print_Graph_unknow(level);
			cct_showstr(0, 0, "Esc退出", 0,14, 1);
			Show_Mouse(level, num, zhadan2[0], X, Y,tag);
			while (Is_Begin(zhadan2[0], 16, 16, 2, X, Y) == 0) {
				Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
				continue;
			}
			int n = 0;
			Open_Area_Graph(A, zhadan2[0], X, Y, 16, 16, n, tag, num, level);
			while (1) {
				if (n == 216) {
					cout << "\nYou Win!" << endl;
					return;
				}
				int i = Show_Mouse(level, num, zhadan2[0], X, Y,tag);
				if (i == -1)
					return;
				if (zhadan2[X][Y] == '*'&&tag==0) {
					Open_Area_Graph(A, zhadan2[0], X, Y, 16, 16, n, tag, num, level);
					cout << "You Lost!" << endl;
					return;
				}
				else
					Open_Area_Graph(A, zhadan2[0], X, Y, 16, 16, n, tag, num, level);//聚合了两种打开方式
			}

		}
		else if (num == 9) {
			int X = -1, Y = -1, tag = 0;
			Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
			double time1 = GetTickCount(),time2;
			Print_Graph_unknow(level);
			cct_showstr(0, 0, "Esc退出 Space查看时间，开启第一块时开始计时", 0, 14, 1);
			while (1) {
				int mouse = Show_Mouse(level, num, zhadan2[0], X, Y, tag);
				if (mouse == -1)
					return;
				else if (mouse == 1)//只有左键单击在有效区域才进入游戏，要不然开局点了其他键会卡死
					break;
			}
			//Show_Mouse(level, num, zhadan2[0], X, Y, tag);
			while (Is_Begin(zhadan2[0], 16, 16, 2, X, Y) == 0) {
				Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
				continue;
			}
			int n = 0;
			cct_showstr(0, 0, "                                                   ", 0, 0, 1);
			Open_Area_Graph(A, zhadan2[0], X, Y, 16, 16, n, tag, num, level);
			while (1) {
				if (A[48][48] == 99) {
					time2 = GetTickCount();
					cct_showstr(0, 58, "游戏已运行 ", 0, 12, 1);
					cout << (time2 - time1) / 1000.0;
				}
				if (n == 216) {
					time2 = GetTickCount();
					cct_showstr(0, 33, "You win!共用时 ", 0, 12, 1);
					cout << (time2 - time1) / 1000.0;
					cct_setcolor(0, 7);
					return;
				}
				int i = Show_Mouse(level, num, zhadan2[0], X, Y, tag);
				if (i == -1)
					return;
				if (zhadan2[X][Y] == '*'&&tag == 0) {
					Open_Area_Graph(A, zhadan2[0], X, Y, 16, 16, n, tag, num, level);
					time2 = GetTickCount();
					cct_showstr(0, 58, "You lost!共用时 ", 0, 12, 1);
					cout << (time2 - time1) / 1000.0;
					cct_setcolor(0, 7);
					return;
				}
				else
					Open_Area_Graph(A, zhadan2[0], X, Y, 16, 16, n, tag, num, level);//聚合了两种打开方式
			}

		}
	}
	else if (level == 3) {
		if (num == 5) {
			Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
			Print_Graph_Base(level);
			Graph_3_array(zhadan3);
		}
		else if (num == 6) {
			int X = -1, Y = -1,tag=0;
			Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
			Print_Graph_Base(level);
			Graph_3_array(zhadan3);
			
			Show_Mouse(level,num,zhadan3[0],X,Y,tag);
		}
		else if (num == 7) {
			int X = -1, Y = -1,tag=0;
			Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
			Print_Graph_unknow(level);
			//Graph_3_array(zhadan3);
			Show_Mouse(level, num,zhadan3[0],X,Y,tag);
			while (Is_Begin(zhadan3[0], 16, 30, 3, X, Y) == 0) {
				Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
				//Print_zhadan(zhadan3[0], 16, 30);
				continue;
			}
			int n = 0;
			Open_Area_Graph(A, zhadan3[0], X, Y, 16, 30, n, tag, num,level);
		}
		else if (num == 8) {
			int X = -1, Y = -1, tag = 0;
			Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
			Print_Graph_unknow(level);
			cct_showstr(0, 0, "Esc退出", 0, 14, 1);
			Show_Mouse(level, num, zhadan3[0], X, Y,tag);
			while (Is_Begin(zhadan3[0], 16, 30, 3, X, Y) == 0) {
				Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
				continue;
			}
			int n = 0;
			Open_Area_Graph(A, zhadan3[0], X, Y, 16, 30, n, tag, num, level);
			while (1) {
				if (n == 381) {
					cout << "\nYou Win!" << endl;
					return;
				}
				int i = Show_Mouse(level, num, zhadan3[0], X, Y,tag);
				if (i == -1)
					return;
				if (zhadan3[X][Y] == '*'&&tag==0) {
					Open_Area_Graph(A, zhadan3[0], X, Y, 16, 30, n, tag, num, level);
					cout << "You Lost!" << endl;
					return;
				}
				else
					Open_Area_Graph(A, zhadan3[0], X, Y, 16, 30, n, tag, num, level);//聚合了两种打开方式
			}

		}
		else if (num == 9) {
			double time1= GetTickCount(),time2;
			int X = -1, Y = -1, tag = 0;
			Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
			Print_Graph_unknow(level);
			cct_showstr(0, 0, "Esc退出 Space查看时间，开启第一块时开始计时", 0, 14, 1);
			while (1) {
				int mouse = Show_Mouse(level, num, zhadan2[0], X, Y, tag);
				if (mouse == -1)
					return;
				else if (mouse == 1)//只有左键单击在有效区域才进入游戏，要不然开局点了其他键会卡死
					break;
			}
			//Show_Mouse(level, num, zhadan3[0], X, Y, tag);
			while (Is_Begin(zhadan3[0], 16, 30, 3, X, Y) == 0) {
				Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
				continue;
			}
			int n = 0;
			cct_showstr(0, 0, "                                                 ", 0, 0, 1);
			Open_Area_Graph(A, zhadan3[0], X, Y, 16, 30, n, tag, num, level);
			while (1) {
				if (A[48][48] == 99) {
					time2 = GetTickCount();
					cct_showstr(0, 58, "You win!共用时 ", 0, 12, 1);
					cout << (time2 - time1) / 1000.0;
					cct_setcolor(0, 7);
					return;
				}
				if (n == 381) {
					Open_Area_Graph(A, zhadan3[0], X, Y, 16, 30, n, tag, num, level);
					time2 = GetTickCount();
					cct_showstr(0, 58, "You lost!共用时 ", 0, 12, 1);
					cout << (time2 - time1) / 1000.0;
					cct_setcolor(0, 7);
					return;
				}
				int i = Show_Mouse(level, num, zhadan3[0], X, Y, tag);
				if (i == -1)
					return;
				if (zhadan3[X][Y] == '*'&&tag == 0) {
					Open_Area_Graph(A, zhadan3[0], X, Y, 16, 30, n, tag, num, level);
					cout << "You Lost!" << endl;
					return;
				}
				else
					Open_Area_Graph(A, zhadan3[0], X, Y, 16, 30, n, tag, num, level);//聚合了两种打开方式
			}

		}
	}
}
int Is_cin_right(int a, int b, int num,int& X,int& Y)//这里NUM是level的意思
{
	char x0, y0;
	
	if (num == 1) {                 //判断合法输入
		x0 = _getch();
		while (x0<'A' || x0>'I' || x0 == 'Q') {
			if (x0 == 'Q') {
				cout << x0;
				return -1;
			}
			x0 = _getch();

		}
		cout << x0;
		X = x0 - 'A';
		y0 = _getch();
		while (y0<'1' || y0>'9') {
			y0 = _getch();
		}
		cout << y0;
		Y = y0 - '1';
	}
	else if (num == 2) {
		x0 = _getch();
		if (x0 == 'Q') {
			cout << x0;
			return -1;
		}
		while (x0<'A' || x0>'P' || x0 == 'Q') {
			if (x0 == 'Q') {
				cout << x0;
				return -1;
			}
			x0 = _getch();
		}
		cout << x0;
		X = x0 - 'A';
		y0 = _getch();
		while ((y0<'1' || y0>'9') && (y0<'a' || y0>'g')) {
			y0 = _getch();
		}
		cout << y0;
		if (y0 <= '9'&&y0 >= '1')
			Y = y0 - '1';
		else
			Y = y0 - 'a' + 9;
	}
	else if (num == 3) {
		x0 = _getch();
		if (x0 == 'Q') {
			cout << x0;
			return -1;
		}
		while (x0<'A' || x0>'P' || x0 == 'Q') {
			if (x0 == 'Q') {
				cout << x0;
				return -1;
			}
			x0 = _getch();
		}
		cout << x0;
		X = x0 - 'A';
		y0 = _getch();
		while ((y0<'1' || y0>'9') && (y0<'a' || y0>'u')) {
			y0 = _getch();
		}
		cout << y0;
		if (y0 <= '9'&&y0 >= '1')
			Y = y0 - '1';
		else
			Y = y0 - 'a' + 9;
	}
	return 1;
 }

int Is_cin_right_4(int a, int b, int num, int& X, int& Y,int& tag)
{
	char x0, y0;
	
	if (num == 1) {                 //判断合法输入
		x0 = _getch();
		if (x0 == '!' || x0 == '#' ) {
			if (x0 == '!')
				tag = 1;
			else if (x0 == '#')
				tag = 3;
		

			cout << x0;
			x0 = _getch();
			while (x0<'A' || x0>'I' || x0 == 'Q') {
				if (x0 == 'Q') {
					cout << x0;
					return -1;
				}
				x0 = _getch();
			}
			cout << x0;

			X = x0 - 'A';
		}
		else {
			
			while (x0<'A' || x0>'I' || x0 == 'Q') {
				if (x0 == 'Q') {
					cout << x0;
					return -1;
				}
				x0 = _getch();
			}
			cout << x0;


			X = x0 - 'A';
		}
		
		y0 = _getch();
		while (y0<'1' || y0>'9') {
			y0 = _getch();
		}
		cout << y0;
		Y = y0 - '1';
	}
	else if (num == 2) {
		x0 = _getch();
		if (x0 == '!' || x0 == '#' || x0 == '&') {
			if (x0 == '!')
				tag = 1;
			else if (x0 == '#')
				tag = 0;
			else
				tag = 100;
		}
		x0 = _getch();
		if (x0 == 'Q') {
			cout << x0;
			return -1;
		}
		while (x0<'A' || x0>'P' || x0 == 'Q') {
			if (x0 == 'Q') {
				cout << x0;
				return -1;
			}
			x0 = _getch();
		}
		cout << x0;
		X = x0 - 'A';
		y0 = _getch();
		while ((y0<'1' || y0>'9') && (y0<'a' || y0>'g')) {
			y0 = _getch();
		}
		cout << y0;
		if (y0 <= '9'&&y0 >= '1')
			Y = y0 - '1';
		else
			Y = y0 - 'a' + 9;
	}
	else if (num == 3) {
		x0 = _getch();
		if (x0 == '!' || x0 == '#' || x0 == '&') {
			if (x0 == '!')
				tag = 1;
			else if (x0 == '#')
				tag = 0;
			else
				tag = 100;
		}
		x0 = _getch();
		if (x0 == 'Q') {
			cout << x0;
			return -1;
		}
		while (x0<'A' || x0>'P' || x0 == 'Q') {
			if (x0 == 'Q') {
				cout << x0;
				return -1;
			}
			x0 = _getch();
		}
		cout << x0;
		X = x0 - 'A';
		y0 = _getch();
		while ((y0<'1' || y0>'9') && (y0<'a' || y0>'u')) {
			y0 = _getch();
		}
		cout << y0;
		if (y0 <= '9'&&y0 >= '1')
			Y = y0 - '1';
		else
			Y = y0 - 'a' + 9;
	}
	return 1;
}

int Is_Begin(char*zhadan,int a,int b,int num,int&X,int&Y) //
{
	if(*(zhadan+X*b+Y)=='0')
		return 1;
	return 0;
}

bool Open_Area(int A[][50],char* zhadan,int X, int Y,int a,int b,int& n,int tag,int num)
{
	if (tag == 1) {//tag=1进入标记模式，每次循环会重置tag为0，除非使用！进行标记,TAG=3进入摘除标记模式
		if (A[X][Y] == 0 || A[X][Y] == 2) {//允许重复标记，要不然会炸
			A[X][Y] = 2;
			Open_Show(zhadan, a, b, A, n, tag,num);
		}
		else//在已经打开的地方标红，不操作
			Open_Show(zhadan, a, b, A, n, tag,num);
		return 0;
	}
	if (tag == 3) {//解除标记
		if (A[X][Y] == 2||A[X][Y]==0) {//允许对未标记的解除标记
			A[X][Y] = 0;//不会需要设为1，因为1的不会被设为标记，也就不会需要解除标记
			Open_Show(zhadan, a, b, A, n, tag,num);
		}
		else//在已经打开的地方标红，不操作
			;
		return 0;
	}
	
	if (*(zhadan + X * b + Y) == '*') {
		A[X][Y] = 1;
		Open_Show(zhadan, a, b, A, n, tag, num);
		return 0;
	}
	if (*(zhadan + X * b + Y) <= '8'&&*(zhadan + X * b + Y) >= '1') {//内部聚合两种打开方式，0则深度搜索，数字则直接显示
		A[X][Y] = 1;
		n++;
		Open_Show(zhadan,a,b,A,n,tag,num);
	}
	Dfs(zhadan,X,Y,a,b,A,n);
	Open_Show(zhadan, a, b, A,n,tag,num);
}
bool Open_Area_Graph(int A[][50], char* zhadan, int X, int Y, int a, int b, int& n, int tag, int num,int level)
{
	if (tag == 1) {//tag=1进入标记模式，
		if (A[X][Y] == 0 ) {
			A[X][Y] = 2;
			A[49][49]++;//不想再加一个参数了，利用这个数组里的一个元素来记录，反正这个元素也没用
			Open_Show_Graph(zhadan, a, b, A, n, tag, num,level);
		}
		else if (A[X][Y] == 2){//取消标记
			A[X][Y] = 0;
			A[49][49]--;
			Open_Show_Graph(zhadan, a, b, A, n, tag, num, level);
		}
		//else//在已经打开的地方标红，不操作
			//Open_Show_Graph(zhadan, a, b, A, n, tag, num,level);
		return 0;
	}
	if (tag == 3) {//显示时间
		A[48][48]=99;
		Open_Show_Graph(zhadan, a, b, A, n, tag, num, level);
		return 0;
	}
	

	if (*(zhadan + X * b + Y) == '*') {
		A[X][Y] = 1;
		Open_Show_Graph(zhadan, a, b, A, n, tag, num, level);
		return 0;
	}
	if (*(zhadan + X * b + Y) <= '8'&&*(zhadan + X * b + Y) >= '1') {//内部聚合两种打开方式，0则深度搜索，数字则直接显示
		A[X][Y] = 1;
		n++;
		Open_Show_Graph(zhadan, a, b, A, n, tag, num,level);
	}
	Dfs(zhadan, X, Y, a, b, A, n);
	Open_Show_Graph(zhadan, a, b, A, n, tag, num,level);
}
/* dfs(char*zhadan, int X, int Y, int a, int b)
{
	int Row_8[8] = { 1,1,1,0,0,-1,-1,-1 };//顺时针回旋顺序，顺序不影响效率
	int Col_8[8] = { 1,0,-1,1,-1,-1,0,1 };
	int n = 0;//计算该炸弹周围的炸弹数
	for (int i = 0; i < 8; i++) {
		int NextRow = X + Row_8[i];
		int NextCol = Y + Col_8[i];
		if (NextRow >= 0 && NextRow < a && NextCol >= 0 && NextCol < b) {
			if (*(zhadan+NextRow*b+NextCol) == 'M')
				n++;
		}
	}
	//如果没有周围没有雷 设置为标志'#' 继续遍历dfs  否则此位置改为雷的个数
	if (n == 0) {
		*(zhadan+X*b+Y) = '#';
		//向8个方向蔓延
		for (int i = 0; i < 8; ++i) {
			int NextRow = X+ Row_8[i];
			int NextCol = Y + Col_8[i];
			if (NextRow >= 0 && NextRow < a && NextCol >= 0 && NextCol < b) {
				if (*(zhadan+NextRow*b+NextCol) == 'X') {
					dfs(zhadan,NextRow);
				}

			}
		}
	}
	else {
		*(zhadan + X * b + Y) = '0' + n;//如果不是0，就显示炸弹数量，不再探索他的周围
	}
}*/

void Dfs(char*zhadan, int X, int Y, int a, int b,int A[][50],int& n)
{
	int Row_8[8] = { 1,1,1,0,0,-1,-1,-1 };//顺时针回旋顺序，顺序不影响效率
	int Col_8[8] = { 1,0,-1,1,-1,-1,0,1 };
	//如果没有周围没有雷,继续dfs 
	if ((A[X][Y]!=1)&&*(zhadan+X*b+Y) == '0') {
		A[X][Y] = 1;
		n++;
		//向8个方向蔓延
		for (int i = 0; i < 8; ++i) {
			int NextRow = X + Row_8[i];
			int NextCol = Y + Col_8[i];
			if (NextRow >= 0 && NextRow < a && NextCol >= 0 && NextCol < b) {
				if (*(zhadan + NextRow * b + NextCol) == '0') {
					Dfs(zhadan,NextRow,NextCol,a,b,A,n);
				}
				else if (*(zhadan + NextRow * b + NextCol) == '*') {
					;//是炸弹，什么都不做
				}
				else  {         //如果不是0，就显示炸弹数量，不再探索他的周围
					if (A[NextRow][NextCol] != 1) {
						A[NextRow][NextCol] = 1;
						n++;
					}
				}
			}
		}
	}
	
}

void Open_Show(char* zhadan, int a, int b,int A[][50],int n,int tag,int num)
{
	char biankuang[2][40];//先左后上
	for (int i = 0; i < 30; i++) {
		biankuang[0][i] = 'A' + i;
		if (i <= 8)
			biankuang[1][i] = '1' + i;
		else
			biankuang[1][i] = 'a' + i - 9;
	}
	system("cls");
	cout << "内部数组" << endl;
	cout << "  |";
	for (int i = 0; i < b; i++) {
		cout << biankuang[1][i] << " ";
	}
	cout << endl;
	cout << "--|-------------------------------------------------------------" << endl;
	for (int i = 0; i < a; i++) {
		cout << biankuang[0][i] << " |";
		for (int j = 0; j < b; j++) {
			if (A[i][j] == 1) {
				cct_setcolor(3, 14);
				cout << *(zhadan + i * b + j);
				cct_setcolor(0, 7);
				cout<< " ";
			}
			else if(A[i][j]==2){
				cct_setcolor(4, 7);	
				cout << "X";
				cct_setcolor(0, 7);
				cout << " ";
				
			}
			else if (A[i][j]==0) {
				cout << "X";
				cout << " ";
			}

		}
		cout << endl;
	}
	cout << endl;   //检测正确性代码
	/*for (int i = 0; i < a; i++) {
		cout << "  ";
		for (int j = 0; j < b; j++) {
			cout << *(zhadan + i * b + j) << " ";
		}
		cout << endl;
	}*/
	cout << endl;
	cout << "已排除数" << n << endl;
	
	/*for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	*/
	if (num == 4)
		Show_4_info();
}
void Show_4_info()
{
	cout << endl << endl << "游戏4完整版新增功能：！+坐标标记，#+坐标取消标记，&显示已运行时间" << endl;
}
void Open_Show_Graph(char*zhadan, int a, int b, int A[][50], int n, int tag, int num,int level)
{
	//Print_Graph_Base(1);
	int I, J;//打印起始点坐标
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if (A[i][j] == 1) {
				cct_setcolor(0, 7);
				I = (i + 1) * 3;
				J = (2*j + 1) * 3 + 1;
				cct_showstr(J, I, "    ", 7, 0, 1);
				cct_showstr(J, I+1, "    ", 7, 0, 1);
				char c = *(zhadan + i * b + j);
				if (c == '*')
					cct_showch(J+1, I+1, c, 12, 7, 1);
				else if (c == '0')
					;
				else
					cct_showch(J+1, I+1, c, 7, c - '0', 1);
				
				
			}
			else if (A[i][j] == 2) {
				cct_setcolor(0, 7);
				I = (i + 1) * 3;
				J = (2 * j + 1) * 3 + 1;
				cct_showstr(J, I, "    ", 4, 4, 1);
				cct_showstr(J, I + 1, "    ", 4, 4, 1);
			}
			else if (A[i][j] == 0) {
				cct_setcolor(0, 7);
				I = (i + 1) * 3;
				J = (2 * j + 1) * 3 + 1;
				cct_showstr(J, I, "    ", 6, 0, 1);
				cct_showstr(J, I + 1, "    ", 6, 0, 1);
			}

		}
	}
	cct_setcolor(0, 7);
	if (level == 1) {
		if (num == 9) {
			cct_showstr(0, 0, "                                ", 0, 0, 1, -1);
			cct_showstr(0, 0, "剩余雷数 ", 0, 14, 1, -1);
			if (10 - A[49][49] >= 0)
				cout << 10 - A[49][49];
			else
				cout << 0;
			
		}
		cct_showstr(0, 31, "                                ", 0, 0, 1, -1);
		cct_setcolor(0, 7);
		cct_gotoxy(0, 31);
		//cout << "余雷 " << 10 - n;
	}
	else if (level == 2) {
		if (num == 9) {
			cct_showstr(0, 0, "                                ", 0, 0, 1, -1);
			cct_showstr(0, 0, "剩余雷数 ", 0, 14, 1, -1);
			if (40 - A[49][49] >= 0)
				cout << 40 - A[49][49];
			else
				cout << 0;
		}
		cct_showstr(0, 53, "                                ", 0, 0, 1, -1);
		cct_setcolor(0, 7);
		cct_gotoxy(0, 53);
		//cout << "余雷 " << 40 - n;
	}
	else if (level == 3) {
		if (num == 9) {
			cct_showstr(0, 0, "                                 ", 0, 0, 1, -1);
			cct_showstr(0, 0, "剩余雷数 ", 0, 14, 1, -1);
			if (99 - A[49][49] >= 0)
				cout << 99 - A[49][49];
			else
				cout << 0;
		}
		cct_showstr(0, 53, "                                ", 0, 0, 1, -1);
		cct_setcolor(0, 7);
		cct_gotoxy(0, 53);
		//cout << "余雷 "<<99-n;
	}
	

	
	
	//cct_gotoxy()

}


/**void begin()
{
	Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
	Print_Graph_unknow(level);
	//Graph_1_array(zhadan1);
	Show_Mouse(level, num);


	int X = -1, Y = -1, tag = 0;
	Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
	Print_unknow(9, 9);

	//Print_zhadan(zhadan1[0], 9, 9);
	int i = Is_cin_right(9, 9, 1, X, Y);
	if (i == -1)
		return;

	while (Is_Begin(zhadan1[0], 9, 9, 1, X, Y) == 0) {
		Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
		//Print_zhadan(zhadan1[0], 9, 9);
		continue;
	}//说明isbegin成功，可以进行打开操作
	int n = 0;
	Open_Area(A, zhadan1[0], X, Y, 9, 9, n, tag, num);
	while (1) {
		if (n == 71) {
			cout << "\nYou Win!" << endl;
			return;
		}
		int i = Is_cin_right(9, 9, 1, X, Y);
		if (i == -1)
			return;
		if (zhadan1[X][Y] == '*') {
			cout << "You Lost!" << endl;
			return;
		}
		else
			Open_Area(A, zhadan1[0], X, Y, 9, 9, n, tag, num);//聚合了两种打开方式
	}
}*/