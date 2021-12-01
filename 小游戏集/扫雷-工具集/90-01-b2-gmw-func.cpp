#include"90-01-b2-gmw.h"

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
	while (c < '1' || c>'3') {        //防止死循环
		c = _getch();
	}
	num = (int)(c - '0');


	return num;

}
void Quit(CONSOLE_GRAPHICS_INFO MyCGI)
{
	gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "回车 退出");
	
	char ch = _getch();
	while (ch != 13) {
		ch = _getch();
	}
}

void Set_zhadan(int coord[][2], char* zhadan, int a, int b, int x)
{
	for (int i = 0; i < a * b; i++) {   //初始化置‘0’
		zhadan[i] = '0';
	}

	srand((unsigned)time(0));
	int i = x, x0, y0;
	while (i > 0)
	{
		x0 = rand() % a; //行号
		y0 = rand() % b;  //列号
		if (*(zhadan + x0 * b + y0) == '*') {
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

inline void add(char* zhadan, int x, int y, int a, int b)
{
	//利用作用与反作用性计数
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
	
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_BLOCK, 0);		//画色块的延时
	
	gmw_draw_frame(&MyCGI);
	sprintf_s(temp, "Esc退出，空格查看时间，开启第一块后开始计时");
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
			{10, COLOR_YELLOW, COLOR_WHITE, "  "},				//0未知区域
			{11,  COLOR_HYELLOW, COLOR_WHITE, "  "},				//1 鼠标所在块
			{12,  COLOR_RED, COLOR_HYELLOW, "  "},				//2 标记区域

			{0,  COLOR_WHITE, COLOR_WHITE, NULL},				//NULL（0-8），显示内部数组
			{1,  COLOR_WHITE, 1, NULL},				//如果给出数字4，则直接显示4（NULL表示直接显示数字）
			{2,COLOR_WHITE,2,NULL},
			{3,COLOR_WHITE,3,NULL},
			{4,COLOR_WHITE,4,NULL},
			{5,COLOR_WHITE,5,NULL},
			{6,COLOR_WHITE,6,NULL},
			{7,COLOR_WHITE,7,NULL},
			{8,COLOR_WHITE,8,NULL},
			{-6,COLOR_WHITE,0,"* "},//炸弹

			{BDI_VALUE_END, -1, -1, NULL}			//以BDI_VALUE_END结束，一定要有!!!
	};
	gmw_init(&MyCGI);
	int row, col;

	char zhadan1[9][9];
	int coord1[10][2];
	char zhadan2[16][16];
	int coord2[40][2];
	char zhadan3[16][30];
	int coord3[99][2];
	int A[50][50];//标志数组，用于判断能否显示
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

	gmw_set_rowcol(&MyCGI, row, col);					//游戏区域6*7
	gmw_set_ext_rowcol(&MyCGI, 0, 0, 0, 2);				//设置额外行列
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//修改窗口颜色并级联修改游戏区域、上下状态栏
	gmw_set_font(&MyCGI, "Terminal", 14, 0);				//TrueType字体（新宋体）宽度不需要，可任意设置
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//每个色块区域宽度6列*高度3列，要分隔线
	gmw_set_frame_default_linetype(&MyCGI, 1);			//设置框架线型为预置值2（全部为单线）
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK);
	gmw_set_rowno_switch(&MyCGI, true);					//显示行号
	gmw_set_colno_switch(&MyCGI, true);					//显示列标
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_FRAME, 0);		//画边框的延时
	gmw_set_block_border_switch(&MyCGI, false);			//设置色块需要小边框
	Print_Graph_unknow(1, MyCGI, bdi, row, col);


	int maction, old_mrow, old_mcol, mrow = -1, mcol = -1;
	int keycode1, keycode2;
	int ret;
	int n = 0;


	if (level == 1) {
		
		/*由于鼠标移动和点击的操作的识别不是并行的，若在鼠标快速移动过程中点击的话会出现亮色块滞留的现象*/
		while (1) {
			old_mrow = mrow;
			old_mcol = mcol;
			ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) {//鼠标左键任选一块开始游戏，判断是否能打开
				break;
			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				if (old_mrow >= 0 && old_mcol >= 0 && A[old_mrow][old_mcol] == 0)//A数组元素为0是非显示状态
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//原色快显示正常黄色
				gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //鼠标所在块显亮黄色
			}

		}
		while (Is_Begin(zhadan1[0], 9, 9, 1, mrow, mcol) == 0) {
			Set_zhadan(coord1, zhadan1[0], 9, 9, 10);
			continue;
		}
		//到这里一定是能打开的，进行第一次打开操作，保证不会第一次喷到炸弹
		double time1 = GetTickCount(), time2;
		Open_Area_Graph(MyCGI, bdi, A, zhadan1[0], mrow, mcol, 9, 9, n, tag, level);
		//开门红之后进行正式游戏
		while (1) {
			old_mrow = mrow;
			old_mcol = mcol;
			gmw_status_line(&MyCGI, TOP_STATUS_LINE, "剩余雷数 ", NULL);
			cout << 10 - A[49][49];
			ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			if (n == 71) {
				time2 = GetTickCount();
				char win[50];
				sprintf_s(win, "You Win!,共用时 %lf s", (time2 - time1) / 1000);
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
						sprintf_s(lost, "You Lost!,共用时 %lf s", (time2 - time1) / 1000);
						gmw_status_line(&MyCGI, LOWER_STATUS_LINE, lost, NULL);

						break;
					}
				}

			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] == 0) {//A数组元素为0是非显示状态
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//原色快显示正常黄色
					gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //鼠标所在块显亮黄色
				}
				else if (A[mrow][mcol] != 0 && A[old_mrow][old_mcol] == 0) {//当前是已打开，前一个位置未知
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//原色快显示正常黄色
				}
				else if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] != 0)
					gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //鼠标所在块显亮黄色
			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK) {
				if (A[mrow][mcol] == 2) {//已标记就取消
					A[mrow][mcol] = 0;
					A[49][49]--;
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);
					gmw_status_line(&MyCGI, TOP_STATUS_LINE, "剩余雷数 ", NULL);
					if (A[49][49] >= 10)
						cout << 0;
					else
						cout << 10 - A[49][49];
				}
				else if (A[mrow][mcol] == 0) {//只能在未打开处标记
					A[mrow][mcol] = 2;
					A[49][49]++;
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 12, bdi);		//标记
					gmw_status_line(&MyCGI, TOP_STATUS_LINE, "剩余雷数 ", NULL);
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
					cout << "共用时 " << (time2 - time1) / 1000 << "s";

				}

			}
		}

	}
	else if (level == 2){

		 /*由于鼠标移动和点击的操作的识别不是并行的，若在鼠标快速移动过程中点击的话会出现亮色块滞留的现象*/
		 while (1) {
			 old_mrow = mrow;
			 old_mcol = mcol;
			 ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			 if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) {//鼠标左键任选一块开始游戏，判断是否能打开
				 break;
			 }
			 else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				 if (old_mrow >= 0 && old_mcol >= 0 && A[old_mrow][old_mcol] == 0)//A数组元素为0是非显示状态
					 gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//原色快显示正常黄色
				 gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //鼠标所在块显亮黄色
			 }

		 }
		 while (Is_Begin(zhadan2[0], 16, 16, 1, mrow, mcol) == 0) {
			 Set_zhadan(coord2, zhadan2[0], 16, 16, 40);
			 continue;
		 }
		 //到这里一定是能打开的，进行第一次打开操作，保证不会第一次喷到炸弹
		 double time1 = GetTickCount(), time2;
		 Open_Area_Graph(MyCGI, bdi, A, zhadan2[0], mrow, mcol, 16, 16, n, tag, level);
		 //开门红之后进行正式游戏
		 while (1) {
			 old_mrow = mrow;
			 old_mcol = mcol;
			 gmw_status_line(&MyCGI, TOP_STATUS_LINE, "剩余雷数 ", NULL);
			 cout << 40 - A[49][49];
			 ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			 if (n == 216) {
				 time2 = GetTickCount();
				 char win[50];
				 sprintf_s(win, "You Win!,共用时 %lf s", (time2 - time1) / 1000);
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
						 sprintf_s(lost, "You Lost!,共用时 %lf s", (time2 - time1) / 1000);
						 gmw_status_line(&MyCGI, LOWER_STATUS_LINE, lost, NULL);
						 break;
					 }
				 }

			 }
			 else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				 if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] == 0) {//A数组元素为0是非显示状态
					 gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//原色快显示正常黄色
					 gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //鼠标所在块显亮黄色
				 }
				 else if (A[mrow][mcol] != 0 && A[old_mrow][old_mcol] == 0) {//当前是已打开，前一个位置未知
					 gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//原色快显示正常黄色
				 }
				 else if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] != 0)
					 gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //鼠标所在块显亮黄色
			 }
			 else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK) {
				 if (A[mrow][mcol] == 2) {//已标记就取消
					 A[mrow][mcol] = 0;
					 A[49][49]--;
					 gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);
					 gmw_status_line(&MyCGI, TOP_STATUS_LINE, "剩余雷数 ", NULL);
					 if (A[49][49] >= 40)
						 cout << 0;
					 else
						 cout << 40 - A[49][49];
				 }
				 else if (A[mrow][mcol] == 0) {//只能在未打开处标记
					 A[mrow][mcol] = 2;
					 A[49][49]++;
					 gmw_draw_block(&MyCGI, old_mrow, old_mcol, 12, bdi);		//标记
					 gmw_status_line(&MyCGI, TOP_STATUS_LINE, "剩余雷数 ", NULL);
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
					 cout << "共用时 " << (time2 - time1) / 1000 << "s";
				 }
			 }
		 }
	}
	else if (level == 3) {
		/*由于鼠标移动和点击的操作的识别不是并行的，若在鼠标快速移动过程中点击的话会出现亮色块滞留的现象*/
		while (1) {
			old_mrow = mrow;
			old_mcol = mcol;
			ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) {//鼠标左键任选一块开始游戏，判断是否能打开
				break;
			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				if (old_mrow >= 0 && old_mcol >= 0 && A[old_mrow][old_mcol] == 0)//A数组元素为0是非显示状态
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//原色快显示正常黄色
				gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //鼠标所在块显亮黄色
			}

		}
		while (Is_Begin(zhadan3[0], 16, 30, 1, mrow, mcol) == 0) {
			Set_zhadan(coord3, zhadan3[0], 16, 30, 99);
			continue;
		}
		//到这里一定是能打开的，进行第一次打开操作，保证不会第一次喷到炸弹
		double time1 = GetTickCount(), time2;
		Open_Area_Graph(MyCGI, bdi, A, zhadan3[0], mrow, mcol, 16, 30, n, tag, level);
		//开门红之后进行正式游戏
		while (1) {
			old_mrow = mrow;
			old_mcol = mcol;
			gmw_status_line(&MyCGI, TOP_STATUS_LINE, "剩余雷数 ", NULL);
			cout << 99 - A[49][49];
			ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
			if (n == 381) {
				time2 = GetTickCount();
				char win[50];
				sprintf_s(win, "You Win!,共用时 %lf s", (time2 - time1) / 1000);
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
						sprintf_s(lost, "You Lost!,共用时 %lf s", (time2 - time1) / 1000);
						gmw_status_line(&MyCGI, LOWER_STATUS_LINE, lost, NULL);
						break;
					}
				}

			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
				if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] == 0) {//A数组元素为0是非显示状态
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//原色快显示正常黄色
					gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //鼠标所在块显亮黄色
				}
				else if (A[mrow][mcol] != 0 && A[old_mrow][old_mcol] == 0) {//当前是已打开，前一个位置未知
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);		//原色快显示正常黄色
				}
				else if (A[mrow][mcol] == 0 && A[old_mrow][old_mcol] != 0)
					gmw_draw_block(&MyCGI, mrow, mcol, 11, bdi);				 //鼠标所在块显亮黄色
			}
			else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK) {
				if (A[mrow][mcol] == 2) {//已标记就取消
					A[mrow][mcol] = 0;
					A[49][49]--;
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 10, bdi);
					gmw_status_line(&MyCGI, TOP_STATUS_LINE, "剩余雷数 ", NULL);
					if (A[49][49] >= 99)
						cout << 0;
					else
						cout << 99 - A[49][49];
				}
				else if (A[mrow][mcol] == 0) {//只能在未打开处标记
					A[mrow][mcol] = 2;
					A[49][49]++;
					gmw_draw_block(&MyCGI, old_mrow, old_mcol, 12, bdi);		//标记
					gmw_status_line(&MyCGI, TOP_STATUS_LINE, "剩余雷数 ", NULL);
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
					cout << "共用时 " << (time2 - time1) / 1000 << "s";
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
	if (*(zhadan + X * b + Y) <= '8' && *(zhadan + X * b + Y) >= '1') {//内部聚合两种打开方式，0则深度搜索，数字则直接显示
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
	int Row_8[8] = { 1,1,1,0,0,-1,-1,-1 };//顺时针回旋顺序，顺序不影响效率
	int Col_8[8] = { 1,0,-1,1,-1,-1,0,1 };
	//如果没有周围没有雷,继续dfs 
	if ((A[X][Y] != 1) && *(zhadan + X * b + Y) == '0') {
		A[X][Y] = 1;
		n++;
		//向8个方向蔓延
		for (int i = 0; i < 8; ++i) {
			int NextRow = X + Row_8[i];
			int NextCol = Y + Col_8[i];
			if (NextRow >= 0 && NextRow < a && NextCol >= 0 && NextCol < b) {
				if (*(zhadan + NextRow * b + NextCol) == '0') {
					Dfs(zhadan, NextRow, NextCol, a, b, A, n);
				}
				else if (*(zhadan + NextRow * b + NextCol) == '*') {
					;//是炸弹，什么都不做
				}
				else {         //如果不是0，就显示炸弹数量，不再探索他的周围
					if (A[NextRow][NextCol] != 1) {
						A[NextRow][NextCol] = 1;
						n++;
					}
				}
			}
		}
	}

}

