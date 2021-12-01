#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
#include<Windows.h>
#include<iomanip>
using namespace std;

/* --------------------------------------------------
		此处可以给出需要的静态全局变量（尽可能少，最好没有）、静态全局只读变量/宏定义（个数不限）等
   -------------------------------------------------- */


/* --------------------------------------------------
		此处可以给出需要的内部辅助工具函数
		1、函数名不限，建议为 gmw_inner_* 
		2、个数不限
		3、必须是static函数，确保只在本源文件中使用
   -------------------------------------------------- */
static void move_draw(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi,int direction,int n)
{
	//把原来的在标准地方画色块的函数复制过来，画的时候移动一下位置就可以了
	int bdi_value1 = 0;   //不是画bdi数组中下标为bdi_value的块，而是画bdi数组中value值等于bdi_value的色块，bdi_value1是下标
	while (1) {
		if (bdi[bdi_value1].value == bdi_value)
			break;
		bdi_value1++;
	}
	int bg_color, fg_color;
	int time = pCGI->delay_of_draw_block;
	if (bdi[bdi_value1].bgcolor == -1)
		bg_color = pCGI->CFI.bgcolor;
	else
		bg_color = bdi[bdi_value1].bgcolor;

	if (bdi[bdi_value1].fgcolor == -1)
		fg_color = pCGI->CFI.fgcolor;
	else
		fg_color = bdi[bdi_value1].fgcolor;

	cct_setcolor(bg_color, fg_color);

	if (pCGI->CFI.separator == 1) {
		int X = row_no * (pCGI->CFI.block_high + 1) + pCGI->extern_up_lines + 1;
		if (pCGI->SLI.is_top_status_line == 1)
			X++;//有上状态栏
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//有列标

		int Y = col_no * (pCGI->CFI.block_width + 2) + pCGI->extern_left_cols + 2;
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//有行标

		if (direction == UP_TO_DOWN)
			//X += (pCGI->CFI.block_high)*n;
			X += n;
		else if (direction == DOWN_TO_UP)
			X -= n;
		//X -= (pCGI->CFI.block_high)*n;
		else if (direction == LEFT_TO_RIGHT)
			//Y += (pCGI->CFI.block_width)*n;
			Y += n;
		else if (direction == RIGHT_TO_LEFT)
			Y -= n;
		//Y -= (pCGI->CFI.block_width)*n;
		cct_gotoxy(Y, X);

		if (pCGI->CBI.block_border == 1 && bdi_value1 != 0) {

			cout << pCGI->CBI.top_left;      //第一行

			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;

			}
			cout << pCGI->CBI.top_right;

			cct_gotoxy(Y, X + 1);

			int j;
			for (j = 0; j < pCGI->CFI.block_high - 2; j++) {   //中间的几行，除去色块顶和底行

				if (j == ((pCGI->CFI.block_high - 2) / 2)) {//最中间的那一行，即有内容的行
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//输出数字
						if (bdi[bdi_value1].value < 10) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 1) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 1) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 2) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 2) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 1000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 3) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 3) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 10000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 4) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 4) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 5) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 5) / 2 + 1; i++)
								cout << " ";
						}
						else {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 6) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 6) / 2; i++)
								cout << " ";
						}
						//cout <<setw(2)<< bdi[bdi_value1].value;
					}
					else if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value == 0) {
						for (int i = 0; i < pCGI->CFI.block_width / 2; i++)
							cout << "  ";
					}
					else {
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
						cout << bdi[bdi_value1].content;
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
					}
					cout << pCGI->CBI.v_normal;
				}
				else {
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
						cout << "  ";
						Sleep(time);
					}
					cout << pCGI->CBI.v_normal;
					Sleep(time);
				}

			}

			
			cct_gotoxy(Y, X + pCGI->CFI.block_high - 1);
			cout << pCGI->CBI.lower_left;      //最后一行

			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;

			}
			cout << pCGI->CBI.lower_right;
		}
		else {
			for (int j = 0; j < pCGI->CFI.block_high; j++) {
				cct_gotoxy(Y, X + j);
				if (j == ((pCGI->CFI.block_high) / 2)) {//最中间的那一行，即有内容的行

					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//输出数字
						if (bdi[bdi_value1].value < 10) {
							for (int i = 0; i < (pCGI->CFI.block_width - 1) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 1) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100) {
							for (int i = 0; i < (pCGI->CFI.block_width - 2) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 2) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 1000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 3) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 3) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 10000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 5) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 5) / 2 + 1; i++)
								cout << " ";
						}
						else {
							for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++)
								cout << " ";
						}
					}
					else if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value == 0) {
						for (int i = 0; i < pCGI->CFI.block_width / 2; i++)
							cout << "  ";
					}
					else {
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
						cout << bdi[bdi_value1].content;
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
					}

				}
				else {
					for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
						cout << "  ";
						Sleep(time);
					}
				}

			}
		}
	}
	else {
		int X = row_no * (pCGI->CFI.block_high ) + pCGI->extern_up_lines + 1;
		if (pCGI->SLI.is_top_status_line == 1)
			X++;//有上状态栏
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//有列标

		int Y = col_no * (pCGI->CFI.block_width ) + pCGI->extern_left_cols + 2;
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//有行标

	
		if (direction == UP_TO_DOWN)
			//X += (pCGI->CFI.block_high)*n;
			X += n;
		else if (direction == DOWN_TO_UP)
			X -= n;
		//X -= (pCGI->CFI.block_high)*n;
		else if (direction == LEFT_TO_RIGHT)
			//Y += (pCGI->CFI.block_width)*n;
			Y += n;
		else if (direction == RIGHT_TO_LEFT)
			Y -= n;
		//Y -= (pCGI->CFI.block_width)*n;
		cct_gotoxy(Y, X);

		if (pCGI->CBI.block_border == 1 && bdi_value1 != 0) {

			cout << pCGI->CBI.top_left;      //第一行

			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;

			}
			cout << pCGI->CBI.top_right;

			Sleep(time);
			cct_gotoxy(Y, X + 1);
			int j;
			for (j = 0; j < pCGI->CFI.block_high - 2; j++) {   //中间的几行，除去色块顶和底行

				if (j == ((pCGI->CFI.block_high - 2) / 2)) {//最中间的那一行，即有内容的行
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//输出数字
						if (bdi[bdi_value1].value < 10) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 1) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 1) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 2) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 2) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 1000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 3) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 3) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 10000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 4) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 4) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 5) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 5) / 2 + 1; i++)
								cout << " ";
						}
						else {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 6) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 6) / 2; i++)
								cout << " ";
						}
						//cout <<setw(2)<< bdi[bdi_value1].value;
					}
					else if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value == 0) {
						for (int i = 0; i < pCGI->CFI.block_width / 2; i++)
							cout << "  ";
					}
					else {
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
						cout << bdi[bdi_value1].content;
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
					}
					cout << pCGI->CBI.v_normal;
				}
				else {
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
						cout << "  ";
						Sleep(time);
					}
					cout << pCGI->CBI.v_normal;
					Sleep(time);
				}

			}
			
			cct_gotoxy(Y, X + pCGI->CFI.block_high - 1);
			cout << pCGI->CBI.lower_left;      //最后一行

			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;

			}
			cout << pCGI->CBI.lower_right;
		}
		else {
		for (int j = 0; j < pCGI->CFI.block_high; j++) {
			cct_gotoxy(Y, X + j);
			if (j == ((pCGI->CFI.block_high) / 2)) {//最中间的那一行，即有内容的行

				if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//输出数字
					if (bdi[bdi_value1].value < 10) {
						for (int i = 0; i < (pCGI->CFI.block_width - 1) / 2; i++)
							cout << " ";
						cout << bdi[bdi_value1].value;
						for (int i = 0; i < (pCGI->CFI.block_width - 1) / 2 + 1; i++)
							cout << " ";
					}
					else if (bdi[bdi_value1].value < 100) {
						for (int i = 0; i < (pCGI->CFI.block_width - 2) / 2; i++)
							cout << " ";
						cout << bdi[bdi_value1].value;
						for (int i = 0; i < (pCGI->CFI.block_width - 2) / 2; i++)
							cout << " ";
					}
					else if (bdi[bdi_value1].value < 1000) {
						for (int i = 0; i < (pCGI->CFI.block_width - 3) / 2; i++)
							cout << " ";
						cout << bdi[bdi_value1].value;
						for (int i = 0; i < (pCGI->CFI.block_width - 3) / 2 + 1; i++)
							cout << " ";
					}
					else if (bdi[bdi_value1].value < 10000) {
						for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++)
							cout << " ";
						cout << bdi[bdi_value1].value;
						for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++)
							cout << " ";
					}
					else if (bdi[bdi_value1].value < 100000) {
						for (int i = 0; i < (pCGI->CFI.block_width - 5) / 2; i++)
							cout << " ";
						cout << bdi[bdi_value1].value;
						for (int i = 0; i < (pCGI->CFI.block_width - 5) / 2 + 1; i++)
							cout << " ";
					}
					else {
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++)
							cout << " ";
						cout << bdi[bdi_value1].value;
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++)
							cout << " ";
					}
				}
				else if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value == 0) {
					for (int i = 0; i < pCGI->CFI.block_width / 2; i++)
						cout << "  ";
				}
				else {
					for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
						cout << "  ";
						Sleep(time);
					}
					cout << bdi[bdi_value1].content;
					for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
						cout << "  ";
						Sleep(time);
					}
				}

			}
			else {
				for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
					cout << "  ";
					Sleep(time);
				}
			}

		}

		}
	}
	
	
}
static void move_erase(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value,  const BLOCK_DISPLAY_INFO* const bdi,int direction,int n,int tag)
{
	
	//int bg_color, fg_color;
	cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	if (pCGI->CFI.separator == 1) {
		int X = row_no * (pCGI->CFI.block_high + 1) + pCGI->extern_up_lines + 1;
		if (pCGI->SLI.is_top_status_line == 1)
			X++;//有上状态栏
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//有列标

		int Y = col_no * (pCGI->CFI.block_width + 2) + pCGI->extern_left_cols + 2;
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//有行标
		if (direction == UP_TO_DOWN)
			X += n;
		else if (direction == DOWN_TO_UP)
			X -= n;
		else if (direction == LEFT_TO_RIGHT)
			Y += n;
		else if (direction == RIGHT_TO_LEFT)
			Y -= n;
		cct_gotoxy(Y, X);
		char c[3];
		if (direction == DOWN_TO_UP || direction == UP_TO_DOWN)
			sprintf_s(c, pCGI->CFI.h_normal);
		else
			sprintf_s(c, pCGI->CFI.v_normal);
		if (pCGI->CBI.block_border == 1) {
			for (int j = 0; j < pCGI->CFI.block_high; j++) {
				cct_gotoxy(Y, X + j);
				for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
					if (tag)
						cout << c;
					else
						cout << "  ";
				}
			}

		}
		else {
			for (int j = 0; j < pCGI->CFI.block_high; j++) {
				cct_gotoxy(Y, X + j);
				for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
					if (tag)
						cout << c;
					else
						cout << "  ";
				}
			}

		}
	}
	else {
		int X = row_no * (pCGI->CFI.block_high ) + pCGI->extern_up_lines + 1;
		if (pCGI->SLI.is_top_status_line == 1)
			X++;//有上状态栏
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//有列标

		int Y = col_no * (pCGI->CFI.block_width ) + pCGI->extern_left_cols + 2;
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//有行标
		if (direction == UP_TO_DOWN)
			X += n;
		else if (direction == DOWN_TO_UP)
			X -= n;
		else if (direction == LEFT_TO_RIGHT)
			Y += n;
		else if (direction == RIGHT_TO_LEFT)
			Y -= n;
		cct_gotoxy(Y, X);
		char c[3];
		if (direction == DOWN_TO_UP || direction == UP_TO_DOWN)
			sprintf_s(c, pCGI->CFI.h_normal);
		else
			sprintf_s(c, pCGI->CFI.v_normal);
		if (pCGI->CBI.block_border == 1) {
			for (int j = 0; j < pCGI->CFI.block_high; j++) {
				cct_gotoxy(Y, X + j);
				for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
					if (tag)
						cout << c;
					else
						cout << "  ";
				}
			}

		}
		else {
			for (int j = 0; j < pCGI->CFI.block_high; j++) {
				cct_gotoxy(Y, X + j);
				for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
					if (tag)
						cout << c;
					else
						cout << "  ";
				}
			}

		}
	}
	

}

/* ----------------------------------------------- 
		实现下面给出的函数（函数声明不准动）
   ----------------------------------------------- */
/***************************************************************************
  函数名称：
  功    能：设置游戏主框架的行列数
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int row						：行数(错误则为0，不设上限，人为保证正确性)
			const int col						：列数(错误则为0，不设上限，人为保证正确性)
  返 回 值：
  说    明：1、指消除类游戏的矩形区域的行列值
            2、行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (pCGI->CFI.separator == 1)
		pCGI->lines -= pCGI->row_num * (pCGI->CFI.block_high + 1)+1;       //减去原来的值
	else
		pCGI->lines -= pCGI->row_num * (pCGI->CFI.block_high)+2;
	
	if (pCGI->CFI.separator == 1)
		pCGI->SLI.lower_start_y -= pCGI->row_num * (pCGI->CFI.block_high + 1)+1; //还会影响下状态栏行坐标，所以需要改变
	else
		pCGI->SLI.lower_start_y -= pCGI->row_num * (pCGI->CFI.block_high )+2; //还会影响下状态栏行坐标，所以需要改变
	


	if (row < 0)
		pCGI->row_num = 0;
	else
		pCGI->row_num = row;
	if(pCGI->CFI.separator==1)
		pCGI->lines += pCGI->row_num * (pCGI->CFI.block_high + 1)+1;       //加上新值
	else
		pCGI->lines += pCGI->row_num * (pCGI->CFI.block_high )+2; //+1因为上面减的时候少减一个1，而这里原本应该+2，现1就可以了
	
	if (pCGI->CFI.separator == 1)
		pCGI->SLI.lower_start_y += pCGI->row_num * (pCGI->CFI.block_high + 1) + 1; //还会影响下状态栏行坐标，所以需要改变
	else
		pCGI->SLI.lower_start_y += pCGI->row_num * (pCGI->CFI.block_high) + 2; //还会影响下状态栏行坐标，所以需要改变
	
	/*COL*/
	if (pCGI->CFI.separator == 1)
		pCGI->cols -= pCGI->col_num * (pCGI->CFI.block_width + 2) + 2;       //减去旧值
	else
		pCGI->cols -= pCGI->col_num * (pCGI->CFI.block_width + 2) + 4;
	if (col < 0)
		pCGI->col_num = 0;
	else
		pCGI->col_num = col;
	if (pCGI->CFI.separator == 1)
		pCGI->cols += pCGI->col_num * (pCGI->CFI.block_width + 2)+2;       //加上新值
	else
		pCGI->cols += pCGI->col_num * (pCGI->CFI.block_width+2)+4;

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置整个窗口（含游戏区、附加区在内的整个cmd窗口）的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int bg_color					：前景色（缺省COLOR_BLACK）
		   const int fg_color					：背景色（缺省COLOR_WHITE）
		   const bool cascade					：是否级联（缺省为true-级联）
  返 回 值：
  说    明：1、cascade = true时
				同步修改游戏主区域的颜色
				同步修改上下状态栏的正常文本的背景色和前景色，醒目文本的背景色（前景色不变）
			2、不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15
				    前景色背景色的值一致导致无法看到内容
					前景色正好是状态栏醒目前景色，导致无法看到醒目提示
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (cascade == true) {
		pCGI->area_bgcolor = bgcolor;
		pCGI->area_fgcolor = fgcolor;
		pCGI->CFI.bgcolor = bgcolor;
		pCGI->CFI.fgcolor = fgcolor;

		pCGI->SLI.lower_normal_bgcolor = bgcolor; 
		pCGI->SLI.lower_normal_fgcolor = fgcolor;
		pCGI->SLI.top_normal_bgcolor = bgcolor;
		pCGI->SLI.top_normal_fgcolor = fgcolor;
		pCGI->SLI.lower_catchy_bgcolor = bgcolor;
		pCGI->SLI.top_catchy_bgcolor = bgcolor;
		
		cct_cls();
		char color[10];
		strcpy_s(color, "color ");
		char b[2], f[2];

		sprintf(b, "%X", pCGI->area_bgcolor);
		sprintf(f, "%X", pCGI->area_fgcolor);  //转换成大写16进制数
		strcat_s(color, b);
		strcat_s(color, f);
		system(color); //把整个cmd窗口颜色更改过来

		gmw_set_status_line_color(pCGI, 0);
		gmw_set_status_line_color(pCGI, 1);
	}
	else {
		pCGI->area_bgcolor = bgcolor;
		pCGI->area_fgcolor = fgcolor;
	}
	
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置窗口的字体
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const char *fontname					：字体名称（只能是"Terminal"和"新宋体"两种，错误则返回-1，不改变字体）
		   const int fs_high					：字体高度（缺省及错误为16，不设其它限制，人为保证）
		   const int fs_width					：字体高度（缺省及错误为8，不设其它限制，人为保证）
  返 回 值：
  说    明：1、与cmd_console_tools中的setfontsize相似，目前只支持“点阵字体”和“新宋体”
            2、若设置其它字体则直接返回，保持原字体设置不变
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO *const pCGI, const char *fontname, const int fs_high, const int fs_width)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (strcmp(fontname, "新宋体") == 0 || strcmp(fontname, "Terminal") == 0) {
		strcpy_s(pCGI->CFT.font_type, fontname);
		if (fs_high <= 0)
			pCGI->CFT.font_size_high = 16;
		else
			pCGI->CFT.font_size_high = fs_high;
		if (fs_width <= 0)
			pCGI->CFT.font_size_width = 8;
		else
			pCGI->CFT.font_size_width = fs_width;
	}
	else
		return -1;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置延时
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int type						：延时的类型（目前为3种）
		   const int delay_ms					：以ms为单位的延时
			   画边框的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   画色块的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   色块移动的延时：BLOCK_MOVED_DELAY_MS ~ 不设上限，人为保证正确（ <BLOCK_MOVED_DELAY_MS 则置 BLOCK_MOVED_DELAY_MS）
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int delay_ms)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == DELAY_OF_DRAW_FRAME) {
		if (delay_ms < 0)
			pCGI->delay_of_draw_frame = 0;
		else
			pCGI->delay_of_draw_frame = delay_ms;
	}
	else if (type == DELAY_OF_DRAW_BLOCK) {
		if (delay_ms < 0)
			pCGI->delay_of_draw_block = 0;
		else
			pCGI->delay_of_draw_block = delay_ms;
	}
	else if (type == DELAY_OF_BLOCK_MOVED) {
		if (delay_ms < BLOCK_MOVED_DELAY_MS)
			pCGI->delay_of_block_moved = BLOCK_MOVED_DELAY_MS;
		else
			pCGI->delay_of_block_moved = delay_ms;
	}
	
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  输入参数：设置游戏主框架结构之外需要保留的额外区域
  功    能：CONSOLE_GRAPHICS_INFO *const pCGI	：
		   const int up_lines					：上部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int down_lines				：下部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int left_cols					：左边额外的列（缺省及错误为0，不设上限，人为保证）
		   const int right_cols				：右边额外的列（缺省及错误为0，不设上限，人为保证）
  返 回 值：
  说    明：额外行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->cols -= pCGI->extern_left_cols + pCGI->extern_right_cols;//减去旧值
	pCGI->lines -= pCGI->extern_up_lines + pCGI->extern_down_lines;

	pCGI->start_x -= pCGI->extern_up_lines;//减去旧值?
	pCGI->start_y -= pCGI->extern_left_cols;

	pCGI->SLI.lower_start_y -= pCGI->extern_up_lines; //还会影响下状态栏行坐标，所以需要改变
	pCGI->SLI.top_start_y -= pCGI->extern_up_lines; //还会影响下状态栏行坐标，所以需要改变
	pCGI->SLI.lower_start_x -= pCGI->extern_left_cols;//影响下状态栏列坐标
	pCGI->SLI.top_start_x -= pCGI->extern_left_cols;//影响上状态栏列坐标
	if (up_lines <= 0)
		pCGI->extern_up_lines = 0;
	else
		pCGI->extern_up_lines = up_lines;
	if (down_lines <= 0)
		pCGI->extern_down_lines = 0;
	else
		pCGI->extern_down_lines = down_lines;
	if (left_cols <= 0)
		pCGI->extern_left_cols = 0;
	else
		pCGI->extern_left_cols = left_cols;
	if (right_cols <= 0)
		pCGI->extern_right_cols = 0;
	else
		pCGI->extern_right_cols = right_cols;
	pCGI->cols += pCGI->extern_left_cols + pCGI->extern_right_cols;//加上新值
	pCGI->lines += pCGI->extern_up_lines + pCGI->extern_down_lines;

	pCGI->start_x += pCGI->extern_up_lines;//加新值
	pCGI->start_y += pCGI->extern_left_cols;

	pCGI->SLI.lower_start_y += pCGI->extern_up_lines; //还会影响下状态栏行坐标，所以需要改变
	pCGI->SLI.top_start_y += pCGI->extern_up_lines; //还会影响下状态栏行坐标，所以需要改变
	pCGI->SLI.lower_start_x += pCGI->extern_left_cols;//影响下状态栏列坐标
	pCGI->SLI.top_start_x += pCGI->extern_left_cols;//影响上状态栏列坐标

	

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的11种线型（缺省4种）
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：1 - 全线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 2) {
		strcpy_s(pCGI->CFI.top_left, "┏");
		strcpy_s(pCGI->CFI.lower_left, "┗");
		strcpy_s(pCGI->CFI.top_right, "┓");
		strcpy_s(pCGI->CFI.lower_right, "┛");
		strcpy_s(pCGI->CFI.h_normal, "━");
		strcpy_s(pCGI->CFI.v_normal, "┃");
		strcpy_s(pCGI->CFI.h_top_separator, "┳");
		strcpy_s(pCGI->CFI.h_lower_separator, "┻");
		strcpy_s(pCGI->CFI.v_left_separator, "┣");
		strcpy_s(pCGI->CFI.v_right_separator, "┫");
		strcpy_s(pCGI->CFI.mid_separator, "╋");	
	}
	else if (type == 1) {
		strcpy_s(pCGI->CFI.top_left, "╔");
		strcpy_s(pCGI->CFI.lower_left, "╚");
		strcpy_s(pCGI->CFI.top_right, "╗");
		strcpy_s(pCGI->CFI.lower_right, "╝");
		strcpy_s(pCGI->CFI.h_normal, "═");
		strcpy_s(pCGI->CFI.v_normal, "║");
		strcpy_s(pCGI->CFI.h_top_separator, "╦");
		strcpy_s(pCGI->CFI.h_lower_separator, "╩");
		strcpy_s(pCGI->CFI.v_left_separator, "╠");
		strcpy_s(pCGI->CFI.v_right_separator, "╣");
		strcpy_s(pCGI->CFI.mid_separator, "╬");
	}
	else if (type == 3) {
		strcpy_s(pCGI->CFI.top_left, "╒");
		strcpy_s(pCGI->CFI.lower_left, "╘");
		strcpy_s(pCGI->CFI.top_right, "╕");
		strcpy_s(pCGI->CFI.lower_right, "╛");
		strcpy_s(pCGI->CFI.h_normal, "═");
		strcpy_s(pCGI->CFI.v_normal, "│");
		strcpy_s(pCGI->CFI.h_top_separator, "╤");
		strcpy_s(pCGI->CFI.h_lower_separator, "╧");
		strcpy_s(pCGI->CFI.v_left_separator, "╞");
		strcpy_s(pCGI->CFI.v_right_separator, "╡");
		strcpy_s(pCGI->CFI.mid_separator, "╪");
	}
	else if (type == 4) {
		strcpy_s(pCGI->CFI.top_left, "╓");
		strcpy_s(pCGI->CFI.lower_left, "╙");
		strcpy_s(pCGI->CFI.top_right, "╖");
		strcpy_s(pCGI->CFI.lower_right, "╜");
		strcpy_s(pCGI->CFI.h_normal, "─");
		strcpy_s(pCGI->CFI.v_normal, "║");
		strcpy_s(pCGI->CFI.h_top_separator, "╥");
		strcpy_s(pCGI->CFI.h_lower_separator, "╨");
		strcpy_s(pCGI->CFI.v_left_separator, "╟");
		strcpy_s(pCGI->CFI.v_right_separator, "╢");
		strcpy_s(pCGI->CFI.mid_separator, "╫");
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的11种线型
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const char *...						：共11种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right,
	const char *lower_right, const char *h_normal, const char *v_normal, const char *h_top_separator,
	const char *h_lower_separator, const char *v_left_separator, const char *v_right_separator, const char *mid_separator)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if(top_left==NULL)
		strcpy_s(pCGI->CFI.top_left, "  ");
	else if (sizeof(top_left) == 2) {
		strcpy_s(pCGI->CFI.top_left, top_left);
		strcat_s(pCGI->CFI.top_left, " ");
	}
	else
		strcpy_s(pCGI->CFI.top_left, top_left);

	if(lower_left==NULL)
		strcpy_s(pCGI->CFI.lower_left, "  ");
	else if (sizeof(lower_left) == 2) {
		strcpy_s(pCGI->CFI.lower_left, lower_left);
		strcat_s(pCGI->CFI.lower_left, " ");
	}
	else
		strcpy_s(pCGI->CFI.lower_left, lower_left);

	if(top_right==NULL)
		strcpy_s(pCGI->CFI.top_right, "  ");
	else if (sizeof(top_right) == 2) {
		strcpy_s(pCGI->CFI.top_right, top_right);
		strcat_s(pCGI->CFI.top_right, " ");
	}
	else
		strcpy_s(pCGI->CFI.top_right, top_right);

	if(lower_right==NULL)
		strcpy_s(pCGI->CFI.lower_right, "  ");
	else if (sizeof(lower_right) == 2) {
		strcpy_s(pCGI->CFI.lower_right, lower_right);
		strcat_s(pCGI->CFI.lower_right, " ");
	}
	else 
		strcpy_s(pCGI->CFI.lower_right, lower_right);

	if(h_normal==NULL)
		strcpy_s(pCGI->CFI.h_normal, "  ");
	else if (sizeof(h_normal) == 2) {
		strcpy_s(pCGI->CFI.h_normal, h_normal);
		strcat_s(pCGI->CFI.h_normal, " ");
	}
	else
		strcpy_s(pCGI->CFI.h_normal, h_normal);

	if(v_normal==NULL)
		strcpy_s(pCGI->CFI.v_normal, "  ");
	else if (sizeof(v_normal) == 2) {
		strcpy_s(pCGI->CFI.v_normal, v_normal);
		strcat_s(pCGI->CFI.v_normal, " ");
	}
	else
		strcpy_s(pCGI->CFI.v_normal, v_normal);

	if(h_top_separator==NULL)
		strcpy_s(pCGI->CFI.h_top_separator, "  ");
	else if (sizeof(h_top_separator) == 2) {
		strcpy_s(pCGI->CFI.h_top_separator, h_top_separator);
		strcat_s(pCGI->CFI.h_top_separator, " ");
	}
	else
		strcpy_s(pCGI->CFI.h_top_separator, h_top_separator);

	if(h_lower_separator==NULL)
		strcpy_s(pCGI->CFI.h_lower_separator, "  ");
	else if (sizeof(h_lower_separator) == 2) {
		strcpy_s(pCGI->CFI.h_lower_separator, h_lower_separator);
		strcat_s(pCGI->CFI.h_lower_separator, " ");
	}
	else
		strcpy_s(pCGI->CFI.h_lower_separator, h_lower_separator);

	if(v_left_separator==NULL)
		strcpy_s(pCGI->CFI.v_left_separator, "  ");
	else if (sizeof(v_left_separator) == 2) {
		strcpy_s(pCGI->CFI.v_left_separator , v_left_separator);
		strcat_s(pCGI->CFI.v_left_separator, " ");
	}
	else
		strcpy_s(pCGI->CFI.v_left_separator, v_left_separator);

	if(v_right_separator==NULL)
		strcpy_s(pCGI->CFI.v_right_separator, "  ");
	else if (sizeof(v_right_separator) == 2) {
		strcpy_s(pCGI->CFI.v_right_separator, v_right_separator);
		strcat_s(pCGI->CFI.v_right_separator, " ");
	}
	else
		strcpy_s(pCGI->CFI.v_right_separator, v_right_separator);

	if(mid_separator==NULL)
		strcpy_s(pCGI->CFI.mid_separator, "  ");
	else if (sizeof(mid_separator) == 2) {
		strcpy_s(pCGI->CFI.mid_separator, mid_separator);
		strcat_s(pCGI->CFI.mid_separator, " ");
	}
	else
		strcpy_s(pCGI->CFI.mid_separator, mid_separator);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的色块数量大小、是否需要分隔线等
  输入参数：输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int block_width						：宽度（错误及缺省2，因为约定表格线为中文制表符，如果给出奇数，要+1）
			const int block_high						：高度（错误及缺省1）
			const bool separator						：是否需要分隔线（缺省为true，需要分隔线）
  返 回 值：
  说    明：框架大小/是否需要分隔线等的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO *const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	//列
	if (pCGI->inited != CGI_INITED)
		return -1;
		
	if (pCGI->CFI.separator == 1)
		pCGI->cols -= pCGI->col_num * (pCGI->CFI.block_width + 2)+2;//减去旧值
	else
		pCGI->cols -= pCGI->col_num * (pCGI->CFI.block_width )+4;//这里+2见set_rowcol

	if (block_width <= 0)
		pCGI->CFI.block_width = 2;
	else if((block_width)%2==1)
		pCGI->CFI.block_width = block_width+1;
	else
		pCGI->CFI.block_width = block_width;
	

	//行
	if (pCGI->CFI.separator == 1)
		pCGI->lines -= pCGI->row_num * (pCGI->CFI.block_high + 1)+1;//减去旧值
	else
		pCGI->lines -= pCGI->row_num * (pCGI->CFI.block_high )+2;//这里+1见set_rowcol

	if (pCGI->CFI.separator == 1)
		pCGI->SLI.lower_start_y-= pCGI->row_num * (pCGI->CFI.block_high + 1);//还会影响下状态栏的行坐标
	else
		pCGI->SLI.lower_start_y -= pCGI->row_num * (pCGI->CFI.block_high )+2;

	if (pCGI->CFI.block_high <= 0)
		pCGI->CFI.block_high = 1;
	else
		pCGI->CFI.block_high = block_high;
	
	
	



	pCGI->CFI.separator = separator;//separator之后改变

	if (pCGI->CFI.separator == 1)
		pCGI->SLI.lower_start_y += pCGI->row_num * (pCGI->CFI.block_high + 1);//还会影响下状态栏的行坐标
	else
		pCGI->SLI.lower_start_y += pCGI->row_num * (pCGI->CFI.block_high) + 2;

	if (pCGI->CFI.separator == 1)
		pCGI->lines += pCGI->row_num * (pCGI->CFI.block_high + 1)+1;//加上新值
	else
		pCGI->lines += pCGI->row_num * (pCGI->CFI.block_high)+2;

	if (pCGI->CFI.separator == 1)
		pCGI->cols += pCGI->col_num * (pCGI->CFI.block_width + 2)+2;
	else
		pCGI->cols += pCGI->col_num * (pCGI->CFI.block_width)+4;

	
	

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BORDER_TYPE 结构中的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int bg_color					：背景色（缺省 -1表示用窗口背景色）
			const int fg_color					：前景色（缺省 -1表示用窗口前景色）
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (bgcolor == -1)
		pCGI->CFI.bgcolor = pCGI->area_bgcolor;
	else
		pCGI->CFI.bgcolor = bgcolor;
	if (fgcolor == -1)
		pCGI->CFI.fgcolor = pCGI->area_fgcolor;
	else
		pCGI->CFI.fgcolor = fgcolor;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型（缺省4种）
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：1 - 全双线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 2) {
		strcpy_s(pCGI->CBI.top_left, "┏");
		strcpy_s(pCGI->CBI.lower_left, "┗");
		strcpy_s(pCGI->CBI.top_right, "┓");
		strcpy_s(pCGI->CBI.lower_right, "┛");
		strcpy_s(pCGI->CBI.h_normal, "━");
		strcpy_s(pCGI->CBI.v_normal, "┃");

	}
	else if (type == 1) {
		strcpy_s(pCGI->CBI.top_left, "╔");
		strcpy_s(pCGI->CBI.lower_left, "╚");
		strcpy_s(pCGI->CBI.top_right, "╗");
		strcpy_s(pCGI->CBI.lower_right, "╝");
		strcpy_s(pCGI->CBI.h_normal, "═");
		strcpy_s(pCGI->CBI.v_normal, "║");
	}
	else if (type == 3) {
		strcpy_s(pCGI->CBI.top_left, "╒");
		strcpy_s(pCGI->CBI.lower_left, "╘");
		strcpy_s(pCGI->CBI.top_right, "╕");
		strcpy_s(pCGI->CBI.lower_right, "╛");
		strcpy_s(pCGI->CBI.h_normal, "═");
		strcpy_s(pCGI->CBI.v_normal, "│");
	}
	else if (type == 4) {
		strcpy_s(pCGI->CBI.top_left, "╓");
		strcpy_s(pCGI->CBI.lower_left, "╙");
		strcpy_s(pCGI->CBI.top_right, "╖");
		strcpy_s(pCGI->CBI.lower_right, "╜");
		strcpy_s(pCGI->CBI.h_normal, "─");
		strcpy_s(pCGI->CBI.v_normal, "║");
	}

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const char *...					：共6种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right, const char *lower_right, const char *h_normal, const char *v_normal)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (top_left == NULL)
		strcpy_s(pCGI->CBI.top_left, "  ");
	else if (sizeof(top_left) == 2) {
		strcpy_s(pCGI->CBI.top_left, top_left);
		strcat_s(pCGI->CBI.top_left, " ");
	}
	else
		strcpy_s(pCGI->CBI.top_left, top_left);

	if (lower_left == NULL)
		strcpy_s(pCGI->CBI.lower_left, "  ");
	else if (sizeof(lower_left) == 2) {
		strcpy_s(pCGI->CBI.lower_left, lower_left);
		strcat_s(pCGI->CBI.lower_left, " ");
	}
	else
		strcpy_s(pCGI->CBI.lower_left, lower_left);

	if (top_right == NULL)
		strcpy_s(pCGI->CBI.top_right, "  ");
	else if (sizeof(top_right) == 2) {
		strcpy_s(pCGI->CBI.top_right, top_right);
		strcat_s(pCGI->CBI.top_right, " ");
	}
	else
		strcpy_s(pCGI->CBI.top_right, top_right);

	if (lower_right == NULL)
		strcpy_s(pCGI->CBI.lower_right, "  ");
	else if (sizeof(lower_right) == 2) {
		strcpy_s(pCGI->CBI.lower_right, lower_right);
		strcat_s(pCGI->CBI.lower_right, " ");
	}
	else
		strcpy_s(pCGI->CBI.lower_right, lower_right);

	if (h_normal == NULL)
		strcpy_s(pCGI->CBI.h_normal, "  ");
	else if (sizeof(h_normal) == 2) {
		strcpy_s(pCGI->CBI.h_normal, h_normal);
		strcat_s(pCGI->CBI.h_normal, " ");
	}
	else
		strcpy_s(pCGI->CBI.h_normal, h_normal);

	if (v_normal == NULL)
		strcpy_s(pCGI->CBI.v_normal, "  ");
	else if (sizeof(v_normal) == 2) {
		strcpy_s(pCGI->CBI.v_normal, v_normal);
		strcat_s(pCGI->CBI.v_normal, " ");
	}
	else
		strcpy_s(pCGI->CBI.v_normal, v_normal);

	
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置每个游戏色块(彩球)是否需要小边框
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const bool on_off					：true - 需要 flase - 不需要（缺省false）
  返 回 值：
  说    明：边框约定为中文制表符，双线
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CBI.block_border = on_off;
	gmw_set_block_default_linetype(pCGI, 1);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示上下状态栏
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：状态栏类型（上/下）
			const bool on_off					：true - 需要 flase - 不需要（缺省true）
  返 回 值：
  说    明：1、状态栏的相关约定如下：
			   1.1、上状态栏只能一行，在主区域最上方框线/列标的上面，为主区域的最开始一行（主区域的左上角坐标就是上状态栏的坐标）
			   1.2、下状态栏只能一行，在主区域最下方框线的下面
			   1.3、状态栏的宽度为主区域宽度，如果信息过长则截断
		   2、行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	
	if (type == TOP_STATUS_LINE) {
		pCGI->lines -= pCGI->top_status_line * 1;//减去旧值
		pCGI->SLI.lower_start_y -= pCGI->top_status_line * 1;
		pCGI->top_status_line = on_off;
		pCGI->SLI.is_top_status_line = on_off;
		pCGI->lines += pCGI->top_status_line * 1;//加上新值
		pCGI->SLI.lower_start_y += pCGI->top_status_line * 1;
	}
	else {
		pCGI->lines -= pCGI->lower_status_line * 1;//减去旧值
		pCGI->lower_status_line = on_off;
		pCGI->SLI.is_lower_status_line = on_off;
		pCGI->lines += pCGI->lower_status_line * 1;//加新值
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置上下状态栏的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：状态栏类型（上/下）
			const int normal_bgcolor			：正常文本背景色（缺省 -1表示使用窗口背景色）
			const int normal_fgcolor			：正常文本前景色（缺省 -1表示使用窗口前景色）
			const int catchy_bgcolor			：醒目文本背景色（缺省 -1表示使用窗口背景色）
			const int catchy_fgcolor			：醒目文本前景色（缺省 -1表示使用亮黄色）
  输入参数：
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == TOP_STATUS_LINE) {
		if (normal_bgcolor == -1) 
			pCGI->SLI.top_normal_bgcolor = pCGI->area_bgcolor;
		else 
			pCGI->SLI.top_normal_bgcolor = normal_bgcolor;

		if(normal_fgcolor==-1)
			pCGI->SLI.top_normal_fgcolor = pCGI->area_fgcolor;
		else
			pCGI->SLI.top_normal_fgcolor = normal_fgcolor;

		if (catchy_bgcolor == -1) 
			pCGI->SLI.top_catchy_bgcolor = pCGI->area_bgcolor;
		else 
			pCGI->SLI.top_catchy_bgcolor = catchy_bgcolor;
		
		if (catchy_fgcolor == -1) 
			pCGI->SLI.top_catchy_fgcolor = 14;//亮黄
		else
			pCGI->SLI.top_catchy_fgcolor = catchy_fgcolor;
	}
	else if (type == LOWER_STATUS_LINE) {
		if (normal_bgcolor == -1)
			pCGI->SLI.lower_normal_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.lower_normal_bgcolor = normal_bgcolor;

		if (normal_fgcolor == -1)
			pCGI->SLI.lower_normal_fgcolor = pCGI->area_fgcolor;
		else
			pCGI->SLI.lower_normal_fgcolor = normal_fgcolor;

		if (catchy_bgcolor == -1)
			pCGI->SLI.lower_catchy_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.lower_catchy_bgcolor = catchy_bgcolor;

		if (catchy_fgcolor == -1)
			pCGI->SLI.lower_catchy_fgcolor = 14;//亮黄
		else
			pCGI->SLI.lower_catchy_fgcolor = catchy_fgcolor;
	}

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示行号
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const bool on_off					：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、行号约定为字母A开始连续排列（如果超过26，则从a开始，超过52的统一为*，实际应用不可能）
            2、是否显示行号的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->cols -= pCGI->draw_frame_with_row_no * 2;//减去旧值
	pCGI->draw_frame_with_row_no = on_off;
	pCGI->cols+= pCGI->draw_frame_with_row_no * 2;//加新值
	

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示列标
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const bool on_off					：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、列标约定为数字0开始连续排列（数字0-99，超过99统一为**，实际应用不可能）
            2、是否显示列标的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->lines -= pCGI->draw_frame_with_col_no * 1;//减旧
	pCGI->SLI.lower_start_y-= pCGI->draw_frame_with_col_no * 1;//影响上下状态栏行坐标
	pCGI->SLI.top_start_y-= pCGI->draw_frame_with_col_no * 1;

	pCGI->draw_frame_with_col_no = on_off;

	pCGI->lines += pCGI->draw_frame_with_col_no * 1;//加新
	pCGI->SLI.lower_start_y += pCGI->draw_frame_with_col_no * 1;//影响上下状态栏行坐标
	pCGI->SLI.top_start_y += pCGI->draw_frame_with_col_no * 1;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：打印 CONSOLE_GRAPHICS_INFO 结构体中的各成员值
  输入参数：
  返 回 值：
  说    明：1、仅供调试用，打印格式自定义
            2、本函数测试用例中未调用过，可以不实现
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：将 CONSOLE_GRAPHICS_INFO 结构体用缺省值进行初始化
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI：整体结构指针
		   const int row					：游戏区域色块行数（缺省10）
		   const int col					：游戏区域色块列数（缺省10）
		   const int bgcolor				：整个窗口背景色（缺省 COLOR_BLACK）
		   const int fgcolor				：整个窗口背景色（缺省 COLOR_WHITE）
  返 回 值：
  说    明：窗口背景黑/前景白，点阵16*8，上下左右无额外行列，上下状态栏均有，无行号/列标，框架线型为双线，色块宽度2/高度1/无小边框，颜色略
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* 首先置标记 */
	//gmw_set_ext_rowcol(pCGI, col, row);
	pCGI->inited = CGI_INITED;
	//gmw_set_color(pCGI, bgcolor, fgcolor);
	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	pCGI->col_num = col;
	pCGI->row_num = row;//参数包含部分
	pCGI->start_x = pCGI->extern_up_lines;  
	pCGI->start_y = pCGI->extern_left_cols;

	gmw_set_font(pCGI,"Terminal");//设置字体,高度宽度为默认值?
	gmw_set_delay(pCGI, DELAY_OF_DRAW_BLOCK, 0);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_FRAME, 0);
	gmw_set_delay(pCGI, DELAY_OF_BLOCK_MOVED, 30);//设置时延
	gmw_set_ext_rowcol(pCGI);//设置额外行
	gmw_set_status_line_switch(pCGI, 0, 1);
	gmw_set_status_line_switch(pCGI, 1, 1);//上下状态栏开启
	gmw_set_status_line_color(pCGI, TOP_STATUS_LINE, -1, -1, -1, -1);
	gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE, -1, -1, -1, -1);//状态栏颜色设置
	gmw_set_rowno_switch(pCGI, 0);
	gmw_set_colno_switch(pCGI, 0);//不开启行号列标
	gmw_set_block_border_switch(pCGI, 0);//色块无边框
	gmw_set_frame_style(pCGI, 2,1,1);//色块大小，分割线有
	gmw_set_frame_color(pCGI);
	gmw_set_frame_linetype(pCGI);//默认全双线框

	//pCGI->start_x = ;
	//pCGI->start_y = ;
	//cmd窗口行数
	if(pCGI->CFI.separator==1)
		pCGI->lines = (pCGI->row_num * (pCGI->CFI.block_high + 1) + 1)+pCGI->extern_up_lines+pCGI->extern_down_lines+4;
	else
		pCGI->lines = (pCGI->row_num * (pCGI->CFI.block_high ) + 2) + pCGI->extern_up_lines + pCGI->extern_down_lines + 4;
	if (pCGI->top_status_line)
		pCGI->lines++;
	if (pCGI->lower_status_line)
		pCGI->lines++;
	if (pCGI->draw_frame_with_col_no)
		pCGI->lines++;

	//cnd窗口列数
	if (pCGI->CFI.separator == 1)
		pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + (pCGI->col_num * (pCGI->CFI.block_width + 2) + 2)+1;
	else
		pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + (pCGI->col_num * (pCGI->CFI.block_width) + 4) + 1;


	if (pCGI->draw_frame_with_row_no)
		pCGI->cols += 2;
	//上下状态栏起始位置坐标
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.lower_start_y = pCGI->row_num * (pCGI->CFI.block_high + 1) + 1 + pCGI->extern_up_lines;//为何行列相反?
	if (pCGI->SLI.is_top_status_line == 1)
		pCGI->SLI.lower_start_y++;//有上状态栏+1
	if(pCGI->draw_frame_with_col_no==1)
		pCGI->SLI.lower_start_y++;//有列标+1
	pCGI->SLI.lower_start_x = pCGI->extern_left_cols;
	//cct_gotoxy(1, 30);
	//cout << pCGI->cols;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：画主游戏框架
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
  返 回 值：
  说    明：具体可参考demo的效果
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	cct_setconsoleborder(pCGI->cols,pCGI->lines, pCGI->cols, pCGI->lines);

	int time = pCGI->delay_of_draw_frame;
	cct_setcolor(pCGI->CFI.bgcolor,pCGI->CFI.fgcolor);
	//cout << pCGI->area_bgcolor << pCGI->area_fgcolor;
	
	cct_setfontsize(pCGI->CFT.font_type,pCGI->CFT.font_size_high,pCGI->CFT.font_size_width);
	int X = pCGI->start_x;
	int Y = pCGI->start_y;
	if (pCGI->draw_frame_with_row_no == 1)
		Y+=2;      //显示行号的话右移一列
	//X = pCGI->extern_up_lines + 1;
	//Y = pCGI->extern_left_cols;
	if (pCGI->SLI.is_top_status_line == 1)
		X++;  //有上状态栏，+1
	
	
	
	if (pCGI->CFI.separator == 1) {
		if (pCGI->draw_frame_with_col_no == 1) { //列号
			cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);//行列号颜色与总体颜色一致，与CFI颜色不一定一致
			cct_gotoxy(Y+(pCGI->CFI.block_width+2)/2,X);
			//for (int i = 0; i < pCGI->CFI.block_width - 2; i++)
				//cout << " ";
			cout << 0;
			for (int i = 0; i < pCGI->col_num - 1; i++) {
				for (int j = 0; j < pCGI->CFI.block_width + 1; j++)
					cout << " ";
				cout << i + 1;
			}
			++X;
		}
		cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);//恢复框架颜色
		
		cct_showstr(Y, X, pCGI->CFI.top_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);//第一行
		//cout << pCGI->draw_frame_with_col_no;
		for (int j = 0; j < pCGI->col_num - 1; j++) {//第一行
			for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
				cout << pCGI->CFI.h_normal;
				Sleep(time);
			}
			cout << pCGI->CFI.h_top_separator;
			Sleep(time);
		}
		for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
			cout << pCGI->CFI.h_normal;
			Sleep(time);
		}
		cout << pCGI->CFI.top_right;
		Sleep(time);
		//开始第二小行
		int i0 = 0;
		for (; i0 < pCGI->row_num - 1; i0++) {
			int j = 0;
			for (; j < pCGI->CFI.block_high; j++) {
				if (pCGI->draw_frame_with_row_no == 1 && j == pCGI->CFI.block_high / 2) {//打印行标
					cct_gotoxy(Y - 2, X + 1);
					cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
					cout << (char)(i0 + 'A');
					cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);

				}
				cct_gotoxy(Y, ++X);

				cout << pCGI->CFI.v_normal;
				Sleep(time);
				for (int k = 0; k < pCGI->col_num ; k++) {
					cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					for (int i = 0; i < pCGI->CFI.block_width; i++)
						cout << " ";
					//cct_gotoxy(Y + (pCGI->CFI.block_width + 2) * k, X);


					cout << pCGI->CFI.v_normal;
					//Sleep(time);
				}
				//endl
			}
			cct_gotoxy(Y, ++X);
			cout << pCGI->CFI.v_left_separator;
			Sleep(time);
			for (int j1 = 0; j1 < pCGI->col_num - 1; j1++) {
				for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
					cout << pCGI->CFI.h_normal;
					Sleep(time);
				}
				cout << pCGI->CFI.mid_separator;
				Sleep(time);
			}
			for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
				cout << pCGI->CFI.h_normal;
				Sleep(time);
			}

			cout << pCGI->CFI.v_right_separator;
			Sleep(time);
		}
		//最后一行
		for (int i = 0; i < pCGI->CFI.block_high; i++) {
			if (pCGI->draw_frame_with_row_no == 1 && i == pCGI->CFI.block_high / 2) {//打印行标
				cct_gotoxy(Y - 2, X + 1);
				cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
				cout << (char)(i0 + 'A');
				cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				
			}
			cct_gotoxy(Y, ++X);
			cout << pCGI->CFI.v_normal;
			Sleep(time);
			for (int j = 0; j < pCGI->col_num; j++) {
				for (int i = 0; i < pCGI->CFI.block_width ; i++) {;
					cout << " ";
					//Sleep(time);
				}
				cout << pCGI->CFI.v_normal;
				Sleep(time);
			}

		}
		cct_gotoxy(Y, ++X);
		cout << pCGI->CFI.lower_left;
		for (int j = 0; j < pCGI->col_num - 1; j++) {
			for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
				cout << pCGI->CFI.h_normal;
				Sleep(time);
			}
			cout << pCGI->CFI.h_lower_separator;
			Sleep(time);
		}
		for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
			cout << pCGI->CFI.h_normal;
			Sleep(time);
		}

		cout << pCGI->CFI.lower_right << endl;
		Sleep(time);
	}
	else {//无分割线
	if (pCGI->draw_frame_with_col_no == 1) { //列号
		cct_gotoxy(Y, X);
		cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);//行列号颜色与area一致而不一定与框架一致
		//for (int i = 0; i < pCGI->CFI.block_width - 2; i++)
		cct_gotoxy(Y + (pCGI->CFI.block_width + 2) / 2, X);
		
		cout << 0;
		for (int i = 0; i < pCGI->col_num - 1; i++) {
			//for (int j = 0; j < pCGI->CFI.block_width + 1; j++)
				//cout << " ";
			if (i + 1 < 100)
				cout << setw(2) << i + 1;
			else
				cout << "**";
		}
		X++;
	}
		cct_showstr(Y, X, pCGI->CFI.top_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);//第一行

		for (int j = 0; j < pCGI->col_num * (pCGI->CFI.block_width )/2; j++) {
			cout << pCGI->CFI.h_normal;
		}
		cout << pCGI->CFI.top_right;
		
		Sleep(time);
		//开始第二小行
		int i = 0;
		for (; i < pCGI->row_num * pCGI->CFI.block_high ; i++) {
			int j = i / pCGI->CFI.block_high;
			if (i % pCGI->CFI.block_high == 0&&pCGI->draw_frame_with_row_no==1) {
				cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
				cct_gotoxy(Y - 2, X+1);
				if (j < 26)
					cout << (char)(j + 'A');
				else if (j >= 26 && j < 52)
					cout << (char)(j + 'a' - 26);
				else
					cout << '*';
			}
			cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			cct_gotoxy(Y, ++X);
			cout << pCGI->CFI.v_normal;
			cct_gotoxy(Y+(pCGI->CFI.block_width)*pCGI->col_num+2,X);
			cout << pCGI->CFI.v_normal;
		}
		
		cct_gotoxy(Y, ++X);//末行
		cout << pCGI->CFI.lower_left;
		for (int j = 0; j < pCGI->col_num * (pCGI->CFI.block_width )/2 ; j++) {
			cout << pCGI->CFI.h_normal;
		}
		cout << pCGI->CFI.lower_right;
		Sleep(time);
	}


	
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：在状态栏上显示信息
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int type							：指定是上/下状态栏
		   const char *msg						：正常信息
		   const char *catchy_msg					：需要特别标注的信息（在正常信息前显示）
  返 回 值：
  说    明：1、输出宽度限定为主框架的宽度（含行号列标位置），超出则截去
            2、如果最后一个字符是某汉字的前半个，会导致后面乱码，要处理
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const char *msg, const char *catchy_msg)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if(type == TOP_STATUS_LINE&&pCGI->SLI.is_top_status_line==1){
		int X, Y;
		Y = pCGI->extern_left_cols;
		X = pCGI->extern_up_lines;
		
		
		cct_gotoxy(Y, X);//起始坐标根据额外行列数定
		cct_setcolor(pCGI->area_bgcolor, pCGI->area_bgcolor);
		cout << "                                     ";//清除原来的东西
		cct_gotoxy(Y, X);
		if (catchy_msg != NULL) {
			cct_setcolor(pCGI->SLI.top_catchy_bgcolor,pCGI->SLI.top_catchy_fgcolor);
			cout << catchy_msg;
		}
		cct_setcolor(pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor);
		cout << msg;
	}
	else if (type == LOWER_STATUS_LINE&&pCGI->SLI.is_lower_status_line==1&&pCGI->CFI.separator==1) {
		int X, Y;
		Y = pCGI->extern_left_cols;
		X = pCGI->row_num * (pCGI->CFI.block_high + 1) + 1 + pCGI->extern_up_lines;
		if (pCGI->SLI.is_top_status_line == 1)
			X++;//有上状态栏+1
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//有列标+1
		cct_gotoxy(Y,X);
		//cct_setcolor(0, 0);
		cct_setcolor(pCGI->area_bgcolor, pCGI->area_bgcolor);
		cout << "                                     ";//清除原来的东西
		cct_gotoxy(Y, X);
		if (catchy_msg != NULL) {
			cct_setcolor(pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor);
			cout << catchy_msg;
		}
		cct_setcolor(pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);
		cout << msg;
	}
	else if(type == LOWER_STATUS_LINE && pCGI->SLI.is_lower_status_line == 1 && pCGI->CFI.separator == 0){
		int X, Y;
		Y = pCGI->extern_left_cols;
		X = pCGI->row_num * (pCGI->CFI.block_high ) + 2 + pCGI->extern_up_lines;
		if (pCGI->SLI.is_top_status_line == 1)
			X++;//有上状态栏+1
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//有列标+1
		cct_gotoxy(Y, X);
		if (catchy_msg != NULL) {
			cct_setcolor(pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor);
			cout << catchy_msg;
		}
		cct_setcolor(pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);
		cout << msg;
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：
  显示某一个色块(内容为字符串，坐标为row/col)
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const BLOCK_DISPLAY_INFO *const bdi		：存放该值对应的显示信息的结构体数组
  返 回 值：
  说    明：1、BLOCK_DISPLAY_INFO 的含义见头文件，用法参考测试样例
            2、bdi_value为 BDI_VALUE_BLANK 表示空白块，要特殊处理
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO *const bdi)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/*色块坐标系起始坐标为(0, 0), 转换成cmd坐标系为(extern_col + 1 + 1 + 2, extern_row + 3)
	因此将(i,j)色块转换为cmd坐标系就是(col_no*(block_width+2)+上边的初值,(row_no*(block_high+1)))+上边的初始值) 指 每一个色块的左上角   */
	int bdi_value1=0;   //不是画bdi数组中下标为bdi_value的块，而是画bdi数组中value值等于bdi_value的色块，bdi_value1是下标
	while (1) {
		if (bdi[bdi_value1].value == bdi_value)
			break;
		bdi_value1++;
	}
	int bg_color, fg_color;
	int time = pCGI->delay_of_draw_block;

	if (bdi[bdi_value1].bgcolor == -1)
		bg_color = pCGI->CFI.bgcolor;
	else
		bg_color = bdi[bdi_value1].bgcolor;

	if (bdi[bdi_value1].fgcolor == -1)
		fg_color = pCGI->CFI.fgcolor;
	else
		fg_color = bdi[bdi_value1].fgcolor;

	int X, Y;
	

	if (pCGI->CFI.separator == 1) {//有分割线

		//把棋盘中的坐标转换成画图cmd的坐标XY
		Y = col_no * (pCGI->CFI.block_width + 2) + pCGI->extern_left_cols + 2;//+2是框架的左边框
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//有行标

		X = row_no * (pCGI->CFI.block_high + 1) + pCGI->extern_up_lines + 1;//+1是上框架的边框
		if (pCGI->SLI.is_top_status_line == 1)
			X++;//有上状态栏
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//有列标

		cct_setcolor(bg_color, fg_color);
		cct_gotoxy(Y, X);

		if (pCGI->CBI.block_border == 1 && bdi_value1 != 0) {

			cout << pCGI->CBI.top_left;      //第一行
			Sleep(time);
			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;
				Sleep(time);
			}
			cout << pCGI->CBI.top_right;
			Sleep(time);

			cct_gotoxy(Y, X + 1);
			int j;
			for (j = 0; j < pCGI->CFI.block_high - 2; j++) {    //中间的几行，除去色块顶和底行

				if (j == ((pCGI->CFI.block_high - 2) / 2)) {	//最中间的那一行，即有内容的行
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//输出数字
						if (bdi[bdi_value1].value < 10) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 1) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 1) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 2) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 2) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 1000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 3) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 3) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 10000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 4) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 4) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 5) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 5) / 2 + 1; i++)
								cout << " ";
						}
						else {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 6) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 6) / 2; i++)
								cout << " ";
						}
						//cout <<setw(2)<< bdi[bdi_value1].value;
					}
					else if ( bdi[bdi_value1].value == 0) {
						for (int i = 0; i < (pCGI->CFI.block_width-4) / 2; i++)
							cout << "  ";
					}
					else {
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
						cout << bdi[bdi_value1].content;
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
					}
					cout << pCGI->CBI.v_normal;
				}
				else {
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
						cout << "  ";
						Sleep(time);
					}
					cout << pCGI->CBI.v_normal;
					Sleep(time);
				}

			}
			cct_gotoxy(Y, X + pCGI->CFI.block_high - 1);
			cout << pCGI->CBI.lower_left;      //最后一行
			Sleep(time);
			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;
				Sleep(time);
			}
			cout << pCGI->CBI.lower_right;
			Sleep(time);
		}
		else {//无边框

			for (int j = 0; j < pCGI->CFI.block_high; j++) {
				cct_gotoxy(Y, X + j);
				if (j == ((pCGI->CFI.block_high) / 2)) {//最中间的那一行，即有内容的行
					
					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//输出数字
						if (bdi[bdi_value1].value < 10) {
							for (int i = 0; i < (pCGI->CFI.block_width - 1) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 1) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100) {
							for (int i = 0; i < (pCGI->CFI.block_width - 2) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 2) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 1000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 3) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 3) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 10000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 5) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 5) / 2 + 1; i++)
								cout << " ";
						}
						else {
							for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++)
								cout << " ";
						}
					}
					else if (bdi[bdi_value1].value == 0) {
						for (int i = 0; i < pCGI->CFI.block_width / 2; i++)
							cout << "  ";
					}
					else {
						for (int i = 0; i < (pCGI->CFI.block_width - 2)/2 ; i++) {
							cout << " ";
							Sleep(time);
						}
						cout << bdi[bdi_value1].content;
						for (int i = 0; i < (pCGI->CFI.block_width - 2)/2; i++) {
							cout << " ";
							Sleep(time);
						}
					}
					
				}
				else {
					for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
						cout << "  ";
						Sleep(time);
					}
				}

			}
		}
	}
	else {//无分割线

		//把棋盘中的坐标转换成画图cmd的坐标XY
		Y = col_no * (pCGI->CFI.block_width ) + pCGI->extern_left_cols + 2;//+2是框架的左边框
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//有行标

		X = row_no * (pCGI->CFI.block_high ) + pCGI->extern_up_lines + 1;//+1是上框架的边框
		if (pCGI->SLI.is_top_status_line == 1)
			X++;//有上状态栏
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//有列标

		cct_setcolor(bg_color, fg_color);
		cct_gotoxy(Y,X);

		if (pCGI->CBI.block_border == 1 && bdi_value1 != 0) {//有边框

			cout << pCGI->CBI.top_left;      //第一行
			Sleep(time);
			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;
				Sleep(time);
			}
			cout << pCGI->CBI.top_right;
			Sleep(time);

			
			cct_gotoxy(Y, X + 1);
			int j;
			for (j = 0; j < pCGI->CFI.block_high - 2; j++) {   //中间的几行，除去色块顶和底行

				if (j == ((pCGI->CFI.block_high - 2) / 2)) {//最中间的那一行，即有内容的行
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//输出数字
						if (bdi[bdi_value1].value < 10) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 1) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 1) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 2) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 2) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 1000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 3) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 3) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 10000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 4) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 4) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 5) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 5) / 2 + 1; i++)
								cout << " ";
						}
						else {
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 6) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4 - 6) / 2; i++)
								cout << " ";
						}
						//cout <<setw(2)<< bdi[bdi_value1].value;
					}
					else if (bdi[bdi_value1].value == 0) {
						for (int i = 0; i < (pCGI->CFI.block_width-4) / 2; i++)
							cout << "  ";
					}
					else {
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
						cout << bdi[bdi_value1].content;
						for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
					}
					cout << pCGI->CBI.v_normal;
				}
				else {
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
						cout << "  ";
						Sleep(time);
					}
					cout << pCGI->CBI.v_normal;
					Sleep(time);
				}

			}

			cct_gotoxy(Y, X+ pCGI->CFI.block_high - 1);
			cout << pCGI->CBI.lower_left;      //最后一行
			Sleep(time);
			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;
				Sleep(time);
			}
			cout << pCGI->CBI.lower_right;
			Sleep(time);
		}
		else {//无边框
			for (int j = 0; j < pCGI->CFI.block_high; j++) {
				cct_gotoxy(Y, X + j);
				if (j == ((pCGI->CFI.block_high) / 2)) {//最中间的那一行，即有内容的行

					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//输出数字
						if (bdi[bdi_value1].value < 10) {
							for (int i = 0; i < (pCGI->CFI.block_width - 1) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 1) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100) {
							for (int i = 0; i < (pCGI->CFI.block_width - 2) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 2) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 1000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 3) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 3) / 2 + 1; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 10000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++)
								cout << " ";
						}
						else if (bdi[bdi_value1].value < 100000) {
							for (int i = 0; i < (pCGI->CFI.block_width - 5) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 5) / 2 + 1; i++)
								cout << " ";
						}
						else {
							for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++)
								cout << " ";
							cout << bdi[bdi_value1].value;
							for (int i = 0; i < (pCGI->CFI.block_width - 6) / 2; i++)
								cout << " ";
						}
					}
					else if (bdi[bdi_value1].value == 0) {
						for (int i = 0; i < pCGI->CFI.block_width / 2; i++)
							cout << "  ";
					}
					else {
						for (int i = 0; i < (pCGI->CFI.block_width - 2) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
						cout << bdi[bdi_value1].content;
						for (int i = 0; i < (pCGI->CFI.block_width - 2) / 2; i++) {
							cout << "  ";
							Sleep(time);
						}
					}

				}
				else {
					for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
						cout << "  ";
						Sleep(time);
					}
				}

			}
		}
	}

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：移动某一个色块
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const int blank_bdi_value				：移动过程中用于动画效果显示时用于表示空白的值（一般为0，此处做为参数代入，是考虑到可能出现的特殊情况）
		   const BLOCK_DISPLAY_INFO *const bdi		：存放显示值/空白值对应的显示信息的结构体数组
		   const int direction						：移动方向，一共四种，具体见cmd_gmw_tools.h
		   const int distance						：移动距离（从1开始，人为保证正确性，程序不检查）
  返 回 值：
  说    明：
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO *const bdi, const int direction, const int distance)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//cct_gotoxy(pCGI->SLI.lower_start_x + 2, pCGI->SLI.lower_start_y + 2);
	//cout << pCGI->delay_of_block_moved;
	if (pCGI->CFI.separator == 1) {  //有分割线版
		for (int i = 0; i < distance; i++) {
			if (direction == DOWN_TO_UP) {
				for (int j = 0; j < pCGI->CFI.block_high + 1; j++) {
					//if ((j + i * (pCGI->CFI.block_high + 1)) % (pCGI->CFI.block_high + 1) == 0)//说明在标准框内，因为一开始的坐标一定在框内
						
					if(j==pCGI->CFI.block_high)
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, DOWN_TO_UP, j + i * (pCGI->CFI.block_high + 1), 1);//把线框补上
					else
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, DOWN_TO_UP, j + i * (pCGI->CFI.block_high + 1), 0);
					Sleep(pCGI->delay_of_block_moved);
					move_draw(pCGI, row_no, col_no, bdi_value, bdi, DOWN_TO_UP, j + i * (pCGI->CFI.block_high + 1) + 1);
					Sleep(pCGI->delay_of_block_moved);
				}
			}
			else if (direction == UP_TO_DOWN) {
				for (int j = 0; j < pCGI->CFI.block_high + 1; j++) {
					
					if(j==pCGI->CFI.block_high)
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, UP_TO_DOWN, j + i * (pCGI->CFI.block_high + 1), 1);//最后一步补框
					else
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, UP_TO_DOWN, j + i * (pCGI->CFI.block_high + 1), 0);
					Sleep(pCGI->delay_of_block_moved);
					move_draw(pCGI, row_no, col_no, bdi_value, bdi, UP_TO_DOWN, j + i * (pCGI->CFI.block_high + 1) + 1);
					Sleep(pCGI->delay_of_block_moved);
				}

			}
			else if (direction == LEFT_TO_RIGHT) {
				for (int j = 0; j < pCGI->CFI.block_width + 2; j += 2) {
					if(j ==pCGI->CFI.block_width )
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, LEFT_TO_RIGHT, j + i * (pCGI->CFI.block_width + 2), 1);
					else
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, LEFT_TO_RIGHT, j + i * (pCGI->CFI.block_width + 2), 0);
					Sleep(pCGI->delay_of_block_moved);
					move_draw(pCGI, row_no, col_no, bdi_value, bdi, LEFT_TO_RIGHT, j + i * (pCGI->CFI.block_width + 2) + 2);
					Sleep(pCGI->delay_of_block_moved);
				}
			}
			else if (direction == RIGHT_TO_LEFT) {
				for (int j = 0; j < pCGI->CFI.block_width + 2; j += 2) {
					if(j == pCGI->CFI.block_width )
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, RIGHT_TO_LEFT, j + i * (pCGI->CFI.block_width + 2), 1);
					else
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, RIGHT_TO_LEFT, j + i * (pCGI->CFI.block_width + 2), 0);

					Sleep(pCGI->delay_of_block_moved);
					move_draw(pCGI, row_no, col_no, bdi_value, bdi, RIGHT_TO_LEFT, j + i * (pCGI->CFI.block_width + 2) + 2);
					Sleep(pCGI->delay_of_block_moved);
				}
			}
		}
	}

	else {//无分割线
		for (int i = 0; i < distance; i++) {
			if (direction == DOWN_TO_UP) {
				for (int j = 0; j < pCGI->CFI.block_high ; j++) {
					//if ((j + i * (pCGI->CFI.block_high + 1)) % (pCGI->CFI.block_high + 1) == 0)//说明在标准框内
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, DOWN_TO_UP, j + i * (pCGI->CFI.block_high ), 0);
					//else
						//move_erase(pCGI, row_no, col_no, bdi_value, bdi, DOWN_TO_UP, j + i * (pCGI->CFI.block_high + 1), 1);//把线框补上
					Sleep(pCGI->delay_of_block_moved);
					move_draw(pCGI, row_no, col_no, bdi_value, bdi, DOWN_TO_UP, j + i * (pCGI->CFI.block_high ) + 1);
					Sleep(pCGI->delay_of_block_moved);
				}
			}
			else if (direction == UP_TO_DOWN) {
				for (int j = 0; j < pCGI->CFI.block_high ; j++) {
					//if ((j + i * (pCGI->CFI.block_high + 1)) % (pCGI->CFI.block_high + 1) == 0)//说明在标准框内
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, UP_TO_DOWN, j + i * (pCGI->CFI.block_high ), 0);
					//else
						//move_erase(pCGI, row_no, col_no, bdi_value, bdi, UP_TO_DOWN, j + i * (pCGI->CFI.block_high + 1), 1);
					Sleep(pCGI->delay_of_block_moved);
					move_draw(pCGI, row_no, col_no, bdi_value, bdi, UP_TO_DOWN, j + i * (pCGI->CFI.block_high) + 1);
					Sleep(pCGI->delay_of_block_moved);
				}

			}
			else if (direction == LEFT_TO_RIGHT) {
				for (int j = 0; j < pCGI->CFI.block_width; j += 2) {
					//if ((j + i * (pCGI->CFI.block_width + 2)) % (pCGI->CFI.block_width + 2) == 0)
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, LEFT_TO_RIGHT, j + i * (pCGI->CFI.block_width ), 0);
					//else
						//move_erase(pCGI, row_no, col_no, bdi_value, bdi, LEFT_TO_RIGHT, j + i * (pCGI->CFI.block_width + 2), 1);
					Sleep(pCGI->delay_of_block_moved);
					move_draw(pCGI, row_no, col_no, bdi_value, bdi, LEFT_TO_RIGHT, j + i * (pCGI->CFI.block_width ) + 2);
					Sleep(pCGI->delay_of_block_moved);
				}
			}
			else if (direction == RIGHT_TO_LEFT) {
				for (int j = 0; j < pCGI->CFI.block_width ; j += 2) {
					//if ((j + i * (pCGI->CFI.block_width + 2)) % (pCGI->CFI.block_width + 2) == 0)
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, RIGHT_TO_LEFT, j + i * (pCGI->CFI.block_width ), 0);
					//else
						//move_erase(pCGI, row_no, col_no, bdi_value, bdi, RIGHT_TO_LEFT, j + i * (pCGI->CFI.block_width + 2), 1);
					Sleep(pCGI->delay_of_block_moved);
					move_draw(pCGI, row_no, col_no, bdi_value, bdi, RIGHT_TO_LEFT, j + i * (pCGI->CFI.block_width ) + 2);
					Sleep(pCGI->delay_of_block_moved);
				}
			}
		}
	}
	
		
		



	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：读键盘或鼠标
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   int &MAction							：如果返回 CCT_MOUSE_EVENT，则此值有效，为 MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK 三者之一
		                                               如果返回 CCT_KEYBOARD_EVENT，则此值无效
		   int &MRow								：如果返回 CCT_MOUSE_EVENT 且 MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK，则此值有效，表示左键选择的游戏区域的行号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &MCol								：如果返回 CCT_MOUSE_EVENT 且 MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK，则此值有效，表示左键选择的游戏区域的列号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode1							：如果返回 CCT_KEYBOARD_EVENT，则此值有效，为读到的键码（如果双键码，则为第一个）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode2							：如果返回 CCT_KEYBOARD_EVENT，则此值有效，为读到的键码（如果双键码，则为第二个，如果是单键码，则为0）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   const bool update_lower_status_line		：鼠标移动时，是否要在本函数中显示"[当前光标] *行*列/位置非法"的信息（true=显示，false=不显示，缺省为true）
  返 回 值：函数返回约定
		   1、如果是鼠标移动，得到的MRow/MCol与传入的相同(鼠标指针微小的移动)，则不返回，继续读
							  得到行列非法位置，则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
							  得到的MRow/MCol与传入的不同(行列至少一个变化)，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] *行*列"，再返回MOUSE_ONLY_MOVED（有些游戏返回后要处理色块的不同颜色显示）
		   2、如果是按下鼠标左键，且当前鼠标指针停留在主游戏区域的*行*列上，则返回 CCT_MOUSE_EVENT ，MAction 为 MOUSE_LEFT_BUTTON_CLICK, MRow 为行号，MCol 为列标
		                          且当前鼠标指针停留在非法区域（非游戏区域，游戏区域中的分隔线），则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
		   3、如果是按下鼠标右键，则不判断鼠标指针停留区域是否合法，直接返回 CCT_MOUSE_EVENT ，MAction 为 MOUSE_RIGHT_BUTTON_CLICK, MRow、MCol取当前值（因为消灭星星的右键标记需要坐标）
		   4、如果按下键盘上的某键（含双键码按键），则直接返回 CCT_KEYBOARD_EVENT，KeyCode1/KeyCode2中为对应的键码值
 说    明：通过调用 cmd_console_tools.cpp 中的 read_keyboard_and_mouse 函数实现
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO *const pCGI, int &MAction, int &MRow, int &MCol, int &KeyCode1, int &KeyCode2, const bool update_lower_status_line)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	cct_enable_mouse();
	int old_mr=-1, old_mc = -1;
	//int mr =0 ;              //将cmd坐标转换为框架中的行列坐标
	//int mc =0 ;
	int MRow0, MCol0;
	 
	int X = pCGI->extern_up_lines;                              //首先算出X，Y分别为游戏棋盘区域的初始左上角坐标，?
	int Y = pCGI->extern_left_cols;

	if (pCGI->draw_frame_with_row_no == 1)
		Y += 2;      //显示行号的话右移一列
	if (pCGI->SLI.is_top_status_line == 1)
		X++;  //有上状态栏，+1
	if (pCGI->draw_frame_with_col_no == 1)
		X++;
	
	while (1) {
		int a=cct_read_keyboard_and_mouse(MCol0, MRow0, MAction, KeyCode1, KeyCode2);
		if (pCGI->CFI.separator == 1) { //有分割线版本
			if (a == CCT_MOUSE_EVENT) {
				if (MAction == MOUSE_ONLY_MOVED) {
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y + 1);
				//cout << MCol0 << " " << MRow0 << " " << Y << " " << X<<" "<<pCGI->start_x;

					if (((MRow0 - X) % (pCGI->CFI.block_high + 1) <= pCGI->CFI.block_high) && ((MRow0 - X) % (pCGI->CFI.block_high + 1) >= 1))
						MRow = (MRow0 - X) / (pCGI->CFI.block_high + 1);
					else
						MRow = -1; //非法坐标
					if (((MCol0 - Y) % (pCGI->CFI.block_width + 2) <= pCGI->CFI.block_width) && ((MCol0 - Y) % (pCGI->CFI.block_width + 2) >= 2))
						MCol = (MCol0 - Y) / (pCGI->CFI.block_width + 2);
					else
						MCol = -1;//非法坐标
					if (MCol >= pCGI->col_num || MRow >= pCGI->row_num) {
						MCol = -1;
						MRow = -1;//越界非法
					}

					if (MRow == old_mr && MCol == old_mc) {
						continue;
					}
					else if (MRow == -1 || MCol == -1) {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
						cct_setcolor(0, 0);
						cout << "                                                ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//写
						cct_setcolor(0, 7);
						cout << "[当前光标] 位置非法";
					}
					else {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
						cct_setcolor(0, 0);
						cout << "                                                    ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
						cct_setcolor(0, 7);
						cout << "[当前光标] " << (char)(MRow + 'A') << "行" << MCol << "列";
						return CCT_MOUSE_EVENT;
					}
					old_mc = MCol;
					old_mr = MRow;
				}
				else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
					if (((MRow0 - X) % (pCGI->CFI.block_high + 1) <= pCGI->CFI.block_high) && ((MRow0 - X) % (pCGI->CFI.block_high + 1) >= 1))
						MRow = (MRow0 - X) / (pCGI->CFI.block_high + 1);
					else
						MRow = -1; //非法坐标
					if (((MCol0 - Y) % (pCGI->CFI.block_width + 2) <= pCGI->CFI.block_width) && ((MCol0 - Y) % (pCGI->CFI.block_width + 2) >= 2))
						MCol = (MCol0 - Y) / (pCGI->CFI.block_width + 2);
					else
						MCol = -1;//非法坐标
					if (MCol >= pCGI->col_num || MRow >= pCGI->row_num) {
						MCol = -1;
						MRow = -1;//越界非法
					}

					if (MRow == old_mr && MCol == old_mc) {
						return CCT_MOUSE_EVENT;
					}
					else if (MRow == -1 || MCol == -1) {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
						cct_setcolor(0, 0);
						cout << "                                                ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//写
						cct_setcolor(0, 7);
						cout << "[当前光标] 位置非法";
					}
					else {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
						cct_setcolor(0, 0);
						cout << "                                                    ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
						cct_setcolor(0, 7);
						cout << "[当前光标] " << (char)(MRow + 'A') << "行" << MCol << "列";

					}
					old_mc = MCol;
					old_mr = MRow;
					return CCT_MOUSE_EVENT;//无论合法与否都返回
				}
				else if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
					if (((MRow0 - X) % (pCGI->CFI.block_high + 1) <= pCGI->CFI.block_high) && ((MRow0 - X) % (pCGI->CFI.block_high + 1) >= 1))
						MRow = (MRow0 - X) / (pCGI->CFI.block_high + 1);
					else
						MRow = -1; //非法坐标
					if (((MCol0 - Y) % (pCGI->CFI.block_width + 2) <= pCGI->CFI.block_width) && ((MCol0 - Y) % (pCGI->CFI.block_width + 2) >= 2))
						MCol = (MCol0 - Y) / (pCGI->CFI.block_width + 2);
					else
						MCol = -1;//非法坐标
					if (MCol >= pCGI->col_num || MRow >= pCGI->row_num) {
						MCol = -1;
						MRow = -1;//越界非法
					}

					if (MRow == old_mr && MCol == old_mc) {
						continue;
					}
					else if (MRow == -1 || MCol == -1) {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
						cct_setcolor(0, 0);
						cout << "                                                ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//写
						cct_setcolor(0, 7);
						cout << "[当前光标] 位置非法";
					}
					else {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
						cct_setcolor(0, 0);
						cout << "                                                    ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
						cct_setcolor(0, 7);
						cout << "[当前光标] " << (char)(MRow + 'A') << "行" << MCol << "列";
						return CCT_MOUSE_EVENT;
					}
					old_mc = MCol;
					old_mr = MRow;
				}
			}
			else {

				return  CCT_KEYBOARD_EVENT;
			}

		}

		else {    //无分割线版本
		if (a == CCT_MOUSE_EVENT) {
			if (MAction == MOUSE_ONLY_MOVED) {
				//cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y + 1);
				//cout << MCol0 << " " << MRow0 << " " << Y << " " << X;

				//if (((MRow0 - X) % (pCGI->CFI.block_high + 1) <= pCGI->CFI.block_high) && ((MRow0 - X) % (pCGI->CFI.block_high + 1) >= 1))
				if ((MRow0 - X > pCGI->row_num * pCGI->CFI.block_high)||(MRow0-X<=0))
					MRow = -1;
				else
					MRow = (MRow0 - X-1) / (pCGI->CFI.block_high);
				
				//if (((MCol0 - Y) % (pCGI->CFI.block_width + 2) <= pCGI->CFI.block_width) && ((MCol0 - Y) % (pCGI->CFI.block_width + 2) >= 2))
				if ((MCol0 - Y > pCGI->col_num * pCGI->CFI.block_width) || (MCol0 - Y <= 0))
					MCol = -1;
				else
					MCol = (MCol0 - Y-2) / (pCGI->CFI.block_width );
				
				

				if (MRow == old_mr && MCol == old_mc) {
					continue;
				}
				else if (MRow == -1 || MCol == -1) {
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
					cct_setcolor(0, 0);
					cout << "                                                ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//写
					cct_setcolor(0, 7);
					cout << "[当前光标] 位置非法";
				}
				else {
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
					cct_setcolor(0, 0);
					cout << "                                                    ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
					cct_setcolor(0, 7);
					cout << "[当前光标] " << (char)(MRow + 'A') << "行" << MCol << "列";
					return CCT_MOUSE_EVENT;
				}
				old_mc = MCol;
				old_mr = MRow;
			}
			else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
				if ((MRow0 - X >= pCGI->row_num * pCGI->CFI.block_high) || (MRow0 - X <= 0))
					MRow = -1;
				else
					MRow = (MRow0 - X - 1) / (pCGI->CFI.block_high);

				//if (((MCol0 - Y) % (pCGI->CFI.block_width + 2) <= pCGI->CFI.block_width) && ((MCol0 - Y) % (pCGI->CFI.block_width + 2) >= 2))
				if ((MCol0 - Y >= pCGI->col_num * pCGI->CFI.block_width) || (MCol0 - Y <= 0))
					MCol = -1;
				else
					MCol = (MCol0 - Y - 2) / (pCGI->CFI.block_width);

				if (MRow == old_mr && MCol == old_mc) {
					return CCT_MOUSE_EVENT;
				}
				else if (MRow == -1 || MCol == -1) {
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
					cct_setcolor(0, 0);
					cout << "                                                ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//写
					cct_setcolor(0, 7);
					cout << "[当前光标] 位置非法";
				}
				else {
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
					cct_setcolor(0, 0);
					cout << "                                                    ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
					cct_setcolor(0, 7);
					cout << "[当前光标] " << (char)(MRow + 'A') << "行" << MCol << "列";

				}
				old_mc = MCol;
				old_mr = MRow;
				return CCT_MOUSE_EVENT;//无论合法与否都返回
			}
			else if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
				
				if ((MRow0 - X >= pCGI->row_num * pCGI->CFI.block_high) || (MRow0 - X <= 0))
					MRow = -1;
				else
					MRow = (MRow0 - X - 1) / (pCGI->CFI.block_high);

				//if (((MCol0 - Y) % (pCGI->CFI.block_width + 2) <= pCGI->CFI.block_width) && ((MCol0 - Y) % (pCGI->CFI.block_width + 2) >= 2))
				if ((MCol0 - Y >= pCGI->col_num * pCGI->CFI.block_width) || (MCol0 - Y <= 0))
					MCol = -1;
				else
					MCol = (MCol0 - Y - 2) / (pCGI->CFI.block_width);

				if (MRow == old_mr && MCol == old_mc) {
					continue;
				}
				else if (MRow == -1 || MCol == -1) {
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
					cct_setcolor(0, 0);
					cout << "                                                ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//写
					cct_setcolor(0, 7);
					cout << "[当前光标] 位置非法";
				}
				else {
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//擦除
					cct_setcolor(0, 0);
					cout << "                                                    ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
					cct_setcolor(0, 7);
					cout << "[当前光标] " << (char)(MRow + 'A') << "行" << MCol << "列";
					return CCT_MOUSE_EVENT;
				}
				old_mc = MCol;
				old_mr = MRow;
			}
		}
		else {

			return  CCT_KEYBOARD_EVENT;
		}
		}
		
		

	}
	return 0; //此句可根据需要修改
}
