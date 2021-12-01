#include"90-01-b2-gmw.h"

int Select_Level()
{
	system("cls");
	int num;
	char c;
	cout << "��ѡ���Ѷ�" << endl;
	cout << "  1.������ 9x9   - 10�����ף�" << endl;
	cout << "  2.�м���16x16  - 40�����ף�" << endl;
	cout << "  3.�߼���16x30  - 99�����ף�" << endl;
	cout << "������1.2.3" << endl;
	c = _getch();
	while (c < '1' || c>'3') {        //��ֹ��ѭ��
		c = _getch();
	}
	num = (int)(c - '0');


	return num;

}
void Quit(CONSOLE_GRAPHICS_INFO MyCGI)
{
	gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "�س� �˳�");
	
	char ch = _getch();
	while (ch != 13) {
		ch = _getch();
	}
}

void Set_zhadan(int coord[][2], char* zhadan, int a, int b, int x)
{
	for (int i = 0; i < a * b; i++) {   //��ʼ���á�0��
		zhadan[i] = '0';
	}

	srand((unsigned)time(0));
	int i = x, x0, y0;
	while (i > 0)
	{
		x0 = rand() % a; //�к�
		y0 = rand() % b;  //�к�
		if (*(zhadan + x0 * b + y0) == '*') {
			continue;
		}
		else {
			*(zhadan + x0 * b + y0) = '*';
			coord[i - 1][0] = x0;//0������
			coord[i - 1][1] = y0;//1������
			i--;
		}
	}
	Add_zhadan(coord, zhadan, a, b, x);
}

inline void add(char* zhadan, int x, int y, int a, int b)
{
	//���������뷴�����Լ���
	if ((x - 1) >= 0 && (y - 1) >= 0 && (*(zhadan + (x - 1) * b + (y - 1)) != '*'))
		*(zhadan + (x - 1) * b + (y - 1)) += 1;
	if ((x - 1) >= 0 && (*(zhadan + (x - 1) * b + (y)) != '*'))
		*(zhadan + (x - 1) * b + (y)) += 1;
	if ((y - 1) >= 0 && (*(zhadan + (x)*b + (y - 1)) != '*'))
		*(zhadan + (x)*b + (y - 1)) += 1;
	if (((x - 1) >= 0 && (y + 1 < b)) && (*(zhadan + (x - 1) * b + (y + 1)) != '*'))
		*(zhadan + (x - 1) * b + (y + 1)) += 1;
	if ((y + 1 < b) && (*(zhadan + (x)*b + (y + 1)) != '*'))
		*(zhadan + (x)*b + (y + 1)) += 1;
	if ((x + 1 < a) && (y - 1) >= 0 && (*(zhadan + (x + 1) * b + (y - 1)) != '*'))
		*(zhadan + (x + 1) * b + (y - 1)) += 1;
	if ((x + 1 < a) && (*(zhadan + (x + 1) * b + (y)) != '*'))
		*(zhadan + (x + 1) * b + (y)) += 1;
	if ((x + 1 < a) && (y + 1 < b) && (*(zhadan + (x + 1) * b + (y + 1)) != '*'))
		*(zhadan + (x + 1) * b + (y + 1)) += 1;
}

void Add_zhadan(int coord[][2], char* zhadan, int a, int b, int x)
{
	//cout << a<<b << endl;
	for (int i = 0; i < x; i++) {
		int x0 = coord[i][0];
		int y0 = coord[i][1];

		add(zhadan, x0, y0, a, b);
	}
}

void Print_Graph_unknow(int level, CONSOLE_GRAPHICS_INFO MyCGI, const BLOCK_DISPLAY_INFO bdi[],int a,int b)
{
	char temp[200];
	cct_cls();
	
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_BLOCK, 0);		//��ɫ�����ʱ
	
	gmw_draw_frame(&MyCGI);
	sprintf_s(temp, "Esc�˳����ո�鿴ʱ�䣬������һ���ʼ��ʱ");
	gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp);
	int i, j;
	for (i = 0; i < a; i++)
		for (j = 0; j < b; j++)
			gmw_draw_block(&MyCGI, i, j, 10, bdi);
	
}

void Init(int level)
{
	CONSOLE_GRAPHICS_INFO MyCGI;
	const BLOCK_DISPLAY_INFO bdi[] = {
			{10, COLOR_YELLOW, COLOR_WHITE, "  "},				//0δ֪����
			{11,  COLOR_HYELLOW, COLOR_WHITE, "  "},				//1 ������ڿ�
			{12,  COLOR_RED, COLOR_HYELLOW, "  "},				//2 �������

			{0,  COLOR_WHITE, COLOR_WHITE, NULL},				//NULL��0-8������ʾ�ڲ�����
			{1,  COLOR_WHITE, 1, NULL},				//�����������4����ֱ����ʾ4��NULL��ʾֱ����ʾ���֣�
			{2,COLOR_WHITE,2,NULL},
			{3,COLOR_WHITE,3,NULL},
			{4,COLOR_WHITE,4,NULL},
			{5,COLOR_WHITE,5,NULL},
			{6,COLOR_WHITE,6,NULL},
			{7,COLOR_WHITE,7,NULL},
			{8,COLOR_WHITE,8,NULL},
			{-6,COLOR_WHITE,0,"* "},//ը��

			{BDI_VALUE_END, -1, -1, NULL}			//��BDI_VALUE_END������һ��Ҫ��!!!
	};
	gmw_init(&MyCGI);
	int row, col;

	char zhadan1[9][9];
	int coord1[10][2];
	char zhadan2[16][16];
	int coord2[40][2];
	char zhadan3[16][30];
	int coord3[99][2];
	int A[50][50];//��־���飬�����ж��ܷ���ʾ
	int tag = 0;
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			A[i][j] = 0;
		}
	}

	if (level == 1) {
		row = 9;
		col = 9;
		Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
	}
	else if (level == 2) {
		row = 16;
		col = 16;
		Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
	}
	else {
		row = 16;
		col = 30;
		Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
	}

	gmw_set_rowcol(&MyCGI, row, col);					//��Ϸ����6*7
	gmw_set_ext_rowcol(&MyCGI, 0, 0, 0, 2);				//���ö�������
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//�޸Ĵ�����ɫ�������޸���Ϸ��������״̬��
	gmw_set_font(&MyCGI, "Terminal", 14, 0);				//TrueType���壨�����壩��Ȳ���Ҫ������������
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//ÿ��ɫ��������6��*�߶�3�У�Ҫ�ָ���
	gmw_set_frame_default_linetype(&MyCGI, 1);			//���ÿ������ΪԤ��ֵ2��ȫ��Ϊ���ߣ�
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK);
	gmw_set_rowno_switch(&MyCGI, true);					//��ʾ�к�
	gmw_set_colno_switch(&MyCGI, true);					//��ʾ�б�
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_FRAME, 0);		//���߿����ʱ
	gmw_set_block_border_switch(&MyCGI, false);			//����ɫ����ҪС�߿�
	Print_Graph_unknow(1, MyCGI, bdi, row, col);


	int maction, old_mrow, old_mcol, mrow = -1, mcol = -1;
	int keycode1, keycode2;
	int ret;
	int n = 0;


	if (level == 1) {
		
		/*��������ƶ��͵���Ĳ�����ʶ���ǲ��еģ������������ƶ������е���Ļ��������ɫ������������*/
		while (1) {
			old_mrow = mrow;
			old_mcol = mcol;
			ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) {//��������ѡһ�鿪ʼ��Ϸ���ж��Ƿ��ܴ�
				break;
			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				if (old_mrow >= 0 && old_mcol >= 0 && A[old_mrow][old_mcol] == 0)//A����Ԫ��Ϊ0�Ƿ���ʾ״̬
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//ԭɫ����ʾ������ɫ
				gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //������ڿ�������ɫ
			}

		}
		while (Is_Begin(zhadan1[0], 9, 9, 1, mrow, mcol) == 0) {
			Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
			continue;
		}
		//������һ�����ܴ򿪵ģ����е�һ�δ򿪲�������֤�����һ���絽ը��
		double time1 = GetTickCount(), time2;
		Open_Area_Graph(MyCGI, bdi, A, zhadan1[0], mrow, mcol, 9, 9, n, tag, level);
		//���ź�֮�������ʽ��Ϸ
		while (1) {
			old_mrow = mrow;
			old_mcol = mcol;
			gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ʣ������ ", NULL);
			cout << 10 - A[49][49];
			ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			if (n == 71) {
				time2 = GetTickCount();
				char win[50];
				sprintf_s(win, "You Win!,����ʱ %lf s", (time2 - time1) / 1000);
				gmw_status_line(&MyCGI, LOWER_STATUS_LINE, win, NULL);

				break;
			}
			if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) {
				//cout << n;
				if (A[mrow][mcol] == 0 || A[mrow][mcol] == 2) {
					Open_Area_Graph(MyCGI, bdi, A, zhadan1[0], mrow, mcol, 9, 9, n, tag, level);
					if (zhadan1[mrow][mcol] == '*') {
						time2 = GetTickCount();
						char lost[50];
						sprintf_s(lost, "You Lost!,����ʱ %lf s", (time2 - time1) / 1000);
						gmw_status_line(&MyCGI, LOWER_STATUS_LINE, lost, NULL);

						break;
					}
				}

			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] == 0) {//A����Ԫ��Ϊ0�Ƿ���ʾ״̬
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//ԭɫ����ʾ������ɫ
					gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //������ڿ�������ɫ
				}
				else if (A[mrow][mcol] != 0 && A[old_mrow][old_mcol] == 0) {//��ǰ���Ѵ򿪣�ǰһ��λ��δ֪
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//ԭɫ����ʾ������ɫ
				}
				else if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] != 0)
					gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //������ڿ�������ɫ
			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK) {
				if (A[mrow][mcol] == 2) {//�ѱ�Ǿ�ȡ��
					A[mrow][mcol] = 0;
					A[49][49]--;
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);
					gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ʣ������ ", NULL);
					if (A[49][49] >= 10)
						cout << 0;
					else
						cout << 10 - A[49][49];
				}
				else if (A[mrow][mcol] == 0) {//ֻ����δ�򿪴����
					A[mrow][mcol] = 2;
					A[49][49]++;
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 12, bdi);		//���
					gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ʣ������ ", NULL);
					if (A[49][49] >= 10)
						cout << 0;
					else
						cout << 10 - A[49][49];
				}
			}
			else if (ret == CCT_KEYBOARD_EVENT) {
				if (keycode1 == 27) {
					break;
				}
				else if (keycode1 == 32) {
					cct_gotoxy(0, MyCGI.lines - 2);
					cout << "                                          ";
					time2 = GetTickCount();
					
					cct_gotoxy(0, MyCGI.lines - 2);
					cout << "����ʱ " << (time2 - time1) / 1000 << "s";

				}

			}
		}

	}
	else if (level == 2){

		 /*��������ƶ��͵���Ĳ�����ʶ���ǲ��еģ������������ƶ������е���Ļ��������ɫ������������*/
		 while (1) {
			 old_mrow = mrow;
			 old_mcol = mcol;
			 ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			 if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) {//��������ѡһ�鿪ʼ��Ϸ���ж��Ƿ��ܴ�
				 break;
			 }
			 else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				 if (old_mrow >= 0 && old_mcol >= 0 && A[old_mrow][old_mcol] == 0)//A����Ԫ��Ϊ0�Ƿ���ʾ״̬
					 gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//ԭɫ����ʾ������ɫ
				 gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //������ڿ�������ɫ
			 }

		 }
		 while (Is_Begin(zhadan2[0], 16, 16, 1, mrow, mcol) == 0) {
			 Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
			 continue;
		 }
		 //������һ�����ܴ򿪵ģ����е�һ�δ򿪲�������֤�����һ���絽ը��
		 double time1 = GetTickCount(), time2;
		 Open_Area_Graph(MyCGI, bdi, A, zhadan2[0], mrow, mcol, 16, 16, n, tag, level);
		 //���ź�֮�������ʽ��Ϸ
		 while (1) {
			 old_mrow = mrow;
			 old_mcol = mcol;
			 gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ʣ������ ", NULL);
			 cout << 40 - A[49][49];
			 ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			 if (n == 216) {
				 time2 = GetTickCount();
				 char win[50];
				 sprintf_s(win, "You Win!,����ʱ %lf s", (time2 - time1) / 1000);
				 gmw_status_line(&MyCGI, LOWER_STATUS_LINE, win, NULL);

				 break;
			 }
			 if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) {
				 //cout << n;
				 if (A[mrow][mcol] == 0 || A[mrow][mcol] == 2) {
					 Open_Area_Graph(MyCGI, bdi, A, zhadan2[0], mrow, mcol, 16, 16, n, tag, level);
					 if (zhadan2[mrow][mcol] == '*') {
						 time2 = GetTickCount();
						 char lost[50];
						 sprintf_s(lost, "You Lost!,����ʱ %lf s", (time2 - time1) / 1000);
						 gmw_status_line(&MyCGI, LOWER_STATUS_LINE, lost, NULL);
						 break;
					 }
				 }

			 }
			 else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				 if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] == 0) {//A����Ԫ��Ϊ0�Ƿ���ʾ״̬
					 gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//ԭɫ����ʾ������ɫ
					 gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //������ڿ�������ɫ
				 }
				 else if (A[mrow][mcol] != 0 && A[old_mrow][old_mcol] == 0) {//��ǰ���Ѵ򿪣�ǰһ��λ��δ֪
					 gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//ԭɫ����ʾ������ɫ
				 }
				 else if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] != 0)
					 gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //������ڿ�������ɫ
			 }
			 else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK) {
				 if (A[mrow][mcol] == 2) {//�ѱ�Ǿ�ȡ��
					 A[mrow][mcol] = 0;
					 A[49][49]--;
					 gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);
					 gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ʣ������ ", NULL);
					 if (A[49][49] >= 40)
						 cout << 0;
					 else
						 cout << 40 - A[49][49];
				 }
				 else if (A[mrow][mcol] == 0) {//ֻ����δ�򿪴����
					 A[mrow][mcol] = 2;
					 A[49][49]++;
					 gmw_draw_block(&MyCGI, old_mrow, old_mcol, 12, bdi);		//���
					 gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ʣ������ ", NULL);
					 if (A[49][49] >= 40)
						 cout << 0;
					 else
						 cout << 40 - A[49][49];
				 }
			 }
			 else if (ret == CCT_KEYBOARD_EVENT) {
				 if (keycode1 == 27) {
					 break;
				 }
				 else if (keycode1 == 32) {
					 cct_gotoxy(0, MyCGI.lines - 2);
					 cout << "                                          ";
					 time2 = GetTickCount();
					
					 cct_gotoxy(0, MyCGI.lines - 2);
					 cout << "����ʱ " << (time2 - time1) / 1000 << "s";
				 }
			 }
		 }
	}
	else if (level == 3) {
		/*��������ƶ��͵���Ĳ�����ʶ���ǲ��еģ������������ƶ������е���Ļ��������ɫ������������*/
		while (1) {
			old_mrow = mrow;
			old_mcol = mcol;
			ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) {//��������ѡһ�鿪ʼ��Ϸ���ж��Ƿ��ܴ�
				break;
			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				if (old_mrow >= 0 && old_mcol >= 0 && A[old_mrow][old_mcol] == 0)//A����Ԫ��Ϊ0�Ƿ���ʾ״̬
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//ԭɫ����ʾ������ɫ
				gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //������ڿ�������ɫ
			}

		}
		while (Is_Begin(zhadan3[0], 16, 30, 1, mrow, mcol) == 0) {
			Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
			continue;
		}
		//������һ�����ܴ򿪵ģ����е�һ�δ򿪲�������֤�����һ���絽ը��
		double time1 = GetTickCount(), time2;
		Open_Area_Graph(MyCGI, bdi, A, zhadan3[0], mrow, mcol, 16, 30, n, tag, level);
		//���ź�֮�������ʽ��Ϸ
		while (1) {
			old_mrow = mrow;
			old_mcol = mcol;
			gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ʣ������ ", NULL);
			cout << 99 - A[49][49];
			ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			if (n == 381) {
				time2 = GetTickCount();
				char win[50];
				sprintf_s(win, "You Win!,����ʱ %lf s", (time2 - time1) / 1000);
				gmw_status_line(&MyCGI, LOWER_STATUS_LINE, win, NULL);

				break;
			}
			if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) {
				//cout << n;
				if (A[mrow][mcol] == 0 || A[mrow][mcol] == 2) {
					Open_Area_Graph(MyCGI, bdi, A, zhadan3[0], mrow, mcol, 16, 30, n, tag, level);
					if (zhadan3[mrow][mcol] == '*') {
						time2 = GetTickCount();
						char lost[50];
						sprintf_s(lost, "You Lost!,����ʱ %lf s", (time2 - time1) / 1000);
						gmw_status_line(&MyCGI, LOWER_STATUS_LINE, lost, NULL);
						break;
					}
				}

			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] == 0) {//A����Ԫ��Ϊ0�Ƿ���ʾ״̬
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//ԭɫ����ʾ������ɫ
					gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //������ڿ�������ɫ
				}
				else if (A[mrow][mcol] != 0 && A[old_mrow][old_mcol] == 0) {//��ǰ���Ѵ򿪣�ǰһ��λ��δ֪
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//ԭɫ����ʾ������ɫ
				}
				else if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] != 0)
					gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //������ڿ�������ɫ
			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK) {
				if (A[mrow][mcol] == 2) {//�ѱ�Ǿ�ȡ��
					A[mrow][mcol] = 0;
					A[49][49]--;
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);
					gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ʣ������ ", NULL);
					if (A[49][49] >= 99)
						cout << 0;
					else
						cout << 99 - A[49][49];
				}
				else if (A[mrow][mcol] == 0) {//ֻ����δ�򿪴����
					A[mrow][mcol] = 2;
					A[49][49]++;
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 12, bdi);		//���
					gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ʣ������ ", NULL);
					if (A[49][49] >= 99)
						cout << 0;
					else
						cout << 99 - A[49][49];
				}
			}
			else if (ret == CCT_KEYBOARD_EVENT) {
				if (keycode1 == 27) {
					break;
				}
				else if (keycode1 == 32) {
					cct_gotoxy(0, MyCGI.lines - 2);
					cout << "                                          ";
					time2 = GetTickCount();

					cct_gotoxy(0, MyCGI.lines - 2);
					cout << "����ʱ " << (time2 - time1) / 1000 << "s";
				}
			}
		}
	}
	
	getchar();
	Quit(MyCGI);
}
		

bool Open_Area_Graph(CONSOLE_GRAPHICS_INFO& MyCGI, const BLOCK_DISPLAY_INFO bdi[],int A[][50], char* zhadan, int X, int Y, int a, int b, int& n, int tag,int level)
{
	if (*(zhadan + X * b + Y) == '*') {
		A[X][Y] = 1;
		gmw_draw_block(&MyCGI, X, Y,*(zhadan+b*X+Y) - '0', bdi);
		return 0;
	}
	if (*(zhadan + X * b + Y) <= '8' && *(zhadan + X * b + Y) >= '1') {//�ڲ��ۺ����ִ򿪷�ʽ��0�����������������ֱ����ʾ
		A[X][Y] = 1;
		n++;
		gmw_draw_block(&MyCGI, X, Y, *(zhadan + b * X + Y) - '0', bdi);
	}
	Dfs(zhadan, X, Y, a, b, A, n);
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if(A[i][j]==1)
			gmw_draw_block(&MyCGI, i, j, *(zhadan + b * i + j) - '0', bdi);
		}
	}
}

int Is_Begin(char* zhadan, int a, int b, int num, int& X, int& Y) //
{
	if (*(zhadan + X * b + Y) == '0')
		return 1;
	return 0;
}

void Dfs(char* zhadan, int X, int Y, int a, int b, int A[][50], int& n)
{
	int Row_8[8] = { 1,1,1,0,0,-1,-1,-1 };//˳ʱ�����˳��˳��Ӱ��Ч��
	int Col_8[8] = { 1,0,-1,1,-1,-1,0,1 };
	//���û����Χû����,����dfs 
	if ((A[X][Y] != 1) && *(zhadan + X * b + Y) == '0') {
		A[X][Y] = 1;
		n++;
		//��8����������
		for (int i = 0; i < 8; ++i) {
			int NextRow = X + Row_8[i];
			int NextCol = Y + Col_8[i];
			if (NextRow >= 0 && NextRow < a && NextCol >= 0 && NextCol < b) {
				if (*(zhadan + NextRow * b + NextCol) == '0') {
					Dfs(zhadan, NextRow, NextCol, a, b, A, n);
				}
				else if (*(zhadan + NextRow * b + NextCol) == '*') {
					;//��ը����ʲô������
				}
				else {         //�������0������ʾը������������̽��������Χ
					if (A[NextRow][NextCol] != 1) {
						A[NextRow][NextCol] = 1;
						n++;
					}
				}
			}
		}
	}

}

