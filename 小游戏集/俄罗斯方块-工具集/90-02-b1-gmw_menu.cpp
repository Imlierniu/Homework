#include"90-02-b1-gmw.h"


int Init(CONSOLE_GRAPHICS_INFO& MyCGI,int& a, int& b,int Di[40][5][5])//选择尺寸
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
	gmw_init(&MyCGI);
	gmw_set_rowcol(&MyCGI,a, b);					//游戏区域row*col
	gmw_set_ext_rowcol(&MyCGI, 0, 0, 0, 16);				//设置额外行列
	gmw_set_color(&MyCGI, COLOR_WHITE, COLOR_HBLACK);		//修改窗口颜色并级联修改游戏区域、上下状态栏
	gmw_set_font(&MyCGI, "新宋体", 10, 0);				//TrueType字体（新宋体）宽度不需要，可任意设置
	gmw_set_frame_style(&MyCGI, 6, 3, false);				//每个色块区域宽度6列*高度3列，要分隔线
	gmw_set_frame_default_linetype(&MyCGI, 2);			//设置框架线型为预置值2（全部为单线）
	gmw_set_rowno_switch(&MyCGI, false);					//显示行号
	gmw_set_colno_switch(&MyCGI, false);					//显示列标
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_FRAME, 0);		//画边框的延时
	gmw_set_block_border_switch(&MyCGI, true);			//设置色块需要小边框
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE, false);//不需要上/下状态栏
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE, true);
	/* 显示框架 */
	//cct_setconsoleborder(93, 61,200,200);
	Show_Map(MyCGI, a, b);
	Init_6(MyCGI, a, b, Di);
	return 1;
}

void Quit(int a, int b)
{
	cct_gotoxy(0, a * 3 + 3);
	cout << "按回车退出" << endl;
	char ch = _getch();
	while (ch != 13) {
		ch = _getch();
	}
}