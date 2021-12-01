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

void Print_Digital(CONSOLE_GRAPHICS_INFO& MyCGI,int n, int L, int X, int Y, int D[40][5][5])  //��ָ��λ�û������֣���5*5�������ߵ�Ϊ�����׼
{    //�Դ󷽿���Ϊ����ϸ���ں���������ת����ʵ�ʻ�ͼ����ϵ

	const BLOCK_DISPLAY_INFO bdi[] = {
				{BDI_VALUE_BLANK, -1, -1, "  "},						//0����ʾ���ÿո���伴��
				{1,  COLOR_HBLACK, -1, "��"},				//�����������1������ʾ������
				{2,  COLOR_HGREEN, COLOR_HBLACK, "��"},	//�����������2������ʾ˫�߿�����
				{3,  COLOR_HGREEN,COLOR_HBLACK, "��"},		//�����������3������ʾ��
				{4,  COLOR_HRED, -1, NULL},				//�����������4����ֱ����ʾ4��NULL��ʾֱ����ʾ���֣�
				{BDI_VALUE_END, -1, -1, NULL}			//��BDI_VALUE_END������һ��Ҫ��!!!
	};
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_BLOCK, 0);		//����ʱ
	
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
				{BDI_VALUE_BLANK, COLOR_WHITE, -1, "  "},						//0����ʾ���ÿո���伴��
				{1,  COLOR_HBLACK, -1, "��"},				//�����������1������ʾ������
				{2,  COLOR_HGREEN, COLOR_HBLACK, "��"},	//�����������2������ʾ˫�߿�����
				{3,  COLOR_HGREEN,COLOR_HBLACK, "��"},		//�����������3������ʾ��
				{4,  COLOR_HRED, -1, NULL},				//�����������4����ֱ����ʾ4��NULL��ʾֱ����ʾ���֣�
				{BDI_VALUE_END, -1, -1, NULL}			//��BDI_VALUE_END������һ��Ҫ��!!!
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
	
	//����һ��Map��ά���飬��СΪa * b�������Ѿ����׵÷�������ֵø���ͼ���ƶ�������һ��Map�����ˡ���
	int** Map = new int* [a];   //����a��ָ��һά�����ָ��
	for (int i = 0; i < a; i++) {
		Map[i] = new int[b];            //a�����飬ÿ�����鳤��Ϊb
		for (int j = 0; j < b; j++) {
			Map[i][j] = 0;            //��ʼ����0
		}
	}

	int score = 0;
	int level = 0;//���ٵȼ�,���ڶ�ʱ���ж�
	int x;   //��ǰ����
	
	
	x=get_next_num(true, 1);

	int list[30] = { 1 ,7, 4, 0, 9, 4, 8, 8, 2, 4, 5, 5, 1, 7, 1, 1, 5, 2, 7, 6, 1, 4, 2, 3, 2, 2, 1, 6, 8, 5 };
	int count = 1;//�������к�
	int Next_Number = list[count + 1];//��һ�����µ�����
	int time = 1000;//��ʼʱ����

	int bottom = 0;

	//cct_showstr(0, a * 3 + 3, "��һ�����֣�", 0, 4, 1);
	
	//cout << Next_Number;
	cct_showstr(MyCGI.col_num * MyCGI.CFI.block_width + 2,2, "������", 0, 4, 1);
	cout << score;
	cct_setcolor(0, 7);
	char c0 = 0, c = 0;
	//int A = 0, B = 0, C = 0, D = 0, E = 0;

	int X = 2;  //������gmw���߼��ģ��˴�����Ϊ-2��������ʵ��ԭ���Ĵ���Ļ�����䣬������ҡ���Ϊgmw��û�п��ǻ�����Ļ��Ĳ���
	int Y = b / 2;
	int L = 0;
	MSG   msg;
	UINT timer_id = SetTimer(NULL, level, time, NULL);//�ϴ��ύʱ��ʱ��û�йرգ���ο�����

	while (1) {
		X = 2;//
		Y = b / 2;
		L = 0;
		
		x = get_next_num();

		Next_Number = list[++count];
		cct_showstr(MyCGI.col_num*MyCGI.CFI.block_width+2, 4, "��һ�����֣�", 0, 4, 1);
		cout << Next_Number;
		cct_gotoxy(MyCGI.col_num * MyCGI.CFI.block_width + 2, 10);

		cout << MyCGI.lines << " " << MyCGI.cols;
		//if (god)
			//cout << 1;
		//else
			
		cct_showstr(MyCGI.col_num * MyCGI.CFI.block_width + 2, 2, "������", 0, 4, 1);
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
				timer_id = SetTimer(NULL, level, time, NULL);//���ü�ʱ����ʱ����
			}

			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_TIMER)
				{
					DispatchMessage(&msg);
					//һ��ʱ�������
					if (Can_Move_Dy(x, L % 4, X + 1, Y, D, a, b, Map) == 1)
						Down_Move(MyCGI,x, L % 4, X, Y, D);
					else {                            //�˳���ǰѭ������ʼ����ڶ�������
						if (Map_Record_score(MyCGI,Map, a, b, D, x, L % 4, X, Y, score))      //�������������
							bottom = 1;
						else
							return;//Game Over
					}
				}
			}
			if (bottom) {
				bottom = 0;
				break;
			}//����һ������
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
			Sleep(0.1);            //��Ϸѭ������1ms�������ú���������һ�����ᵼ�¼���������Ӧ����
		}
	}
}

bool Can_Move_Dy(int n, int L, int X, int Y, int D[40][5][5], int a, int b, int** M)//�������˵�ͼ�ж�
{
	//�ж�Y
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
	//�ж�X
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
	//�ж�Map
	int x0, y0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			x0 = X - 2 + i;
			y0 = Y - 2 + j;
			if ((x0 >= 0) && (y0 >= 0) && (x0 < a) && (y0 < b))   //һ��ʼ����Ϊ����
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
	int x0 = 0, y0 = 0;              //��¼
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {//X,Y���������ĵ�����
			x0 = (X - 2 + i);
			y0 = Y - 2 + j;
			if (x0 <= 0)
				return 0;
			if (D[x * 4 + L][i][j] == 1) {
				M[x0][y0] = 1;
			}
		}
	}
	//�����û�п�����������
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
			i++;//����һ�к����
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

void Map_Clear(CONSOLE_GRAPHICS_INFO& MyCGI,int a, int b, int** M, int I) //����һ��,��������ֱ��ˢ������
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
				{BDI_VALUE_BLANK, -1, -1, "  "},						//0����ʾ���ÿո���伴��
				{1,  COLOR_HBLACK, -1, "��"},				//�����������1������ʾ������
				{2,  COLOR_HGREEN, COLOR_HBLACK, "��"},	//�����������2������ʾ˫�߿�����
				{3,  COLOR_HGREEN,COLOR_HBLACK, "��"},		//�����������3������ʾ��
				{4,  COLOR_HRED, -1, NULL},				//�����������4����ֱ����ʾ4��NULL��ʾֱ����ʾ���֣�
				{BDI_VALUE_END, -1, -1, NULL}			//��BDI_VALUE_END������һ��Ҫ��!!!
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