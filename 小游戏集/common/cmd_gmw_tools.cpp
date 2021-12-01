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
		�˴����Ը�����Ҫ�ľ�̬ȫ�ֱ������������٣����û�У�����̬ȫ��ֻ������/�궨�壨�������ޣ���
   -------------------------------------------------- */


/* --------------------------------------------------
		�˴����Ը�����Ҫ���ڲ��������ߺ���
		1�����������ޣ�����Ϊ gmw_inner_* 
		2����������
		3��������static������ȷ��ֻ�ڱ�Դ�ļ���ʹ��
   -------------------------------------------------- */
static void move_draw(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi,int direction,int n)
{
	//��ԭ�����ڱ�׼�ط���ɫ��ĺ������ƹ���������ʱ���ƶ�һ��λ�þͿ�����
	int bdi_value1 = 0;   //���ǻ�bdi�������±�Ϊbdi_value�Ŀ飬���ǻ�bdi������valueֵ����bdi_value��ɫ�飬bdi_value1���±�
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
			X++;//����״̬��
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//���б�

		int Y = col_no * (pCGI->CFI.block_width + 2) + pCGI->extern_left_cols + 2;
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//���б�

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

			cout << pCGI->CBI.top_left;      //��һ��

			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;

			}
			cout << pCGI->CBI.top_right;

			cct_gotoxy(Y, X + 1);

			int j;
			for (j = 0; j < pCGI->CFI.block_high - 2; j++) {   //�м�ļ��У���ȥɫ�鶥�͵���

				if (j == ((pCGI->CFI.block_high - 2) / 2)) {//���м����һ�У��������ݵ���
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//�������
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
			cout << pCGI->CBI.lower_left;      //���һ��

			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;

			}
			cout << pCGI->CBI.lower_right;
		}
		else {
			for (int j = 0; j < pCGI->CFI.block_high; j++) {
				cct_gotoxy(Y, X + j);
				if (j == ((pCGI->CFI.block_high) / 2)) {//���м����һ�У��������ݵ���

					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//�������
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
			X++;//����״̬��
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//���б�

		int Y = col_no * (pCGI->CFI.block_width ) + pCGI->extern_left_cols + 2;
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//���б�

	
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

			cout << pCGI->CBI.top_left;      //��һ��

			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;

			}
			cout << pCGI->CBI.top_right;

			Sleep(time);
			cct_gotoxy(Y, X + 1);
			int j;
			for (j = 0; j < pCGI->CFI.block_high - 2; j++) {   //�м�ļ��У���ȥɫ�鶥�͵���

				if (j == ((pCGI->CFI.block_high - 2) / 2)) {//���м����һ�У��������ݵ���
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//�������
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
			cout << pCGI->CBI.lower_left;      //���һ��

			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;

			}
			cout << pCGI->CBI.lower_right;
		}
		else {
		for (int j = 0; j < pCGI->CFI.block_high; j++) {
			cct_gotoxy(Y, X + j);
			if (j == ((pCGI->CFI.block_high) / 2)) {//���м����һ�У��������ݵ���

				if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//�������
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
			X++;//����״̬��
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//���б�

		int Y = col_no * (pCGI->CFI.block_width + 2) + pCGI->extern_left_cols + 2;
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//���б�
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
			X++;//����״̬��
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//���б�

		int Y = col_no * (pCGI->CFI.block_width ) + pCGI->extern_left_cols + 2;
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//���б�
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
		ʵ����������ĺ���������������׼����
   ----------------------------------------------- */
/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ����ܵ�������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int row						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
			const int col						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
  �� �� ֵ��
  ˵    ����1��ָ��������Ϸ�ľ������������ֵ
            2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (pCGI->CFI.separator == 1)
		pCGI->lines -= pCGI->row_num * (pCGI->CFI.block_high + 1)+1;       //��ȥԭ����ֵ
	else
		pCGI->lines -= pCGI->row_num * (pCGI->CFI.block_high)+2;
	
	if (pCGI->CFI.separator == 1)
		pCGI->SLI.lower_start_y -= pCGI->row_num * (pCGI->CFI.block_high + 1)+1; //����Ӱ����״̬�������꣬������Ҫ�ı�
	else
		pCGI->SLI.lower_start_y -= pCGI->row_num * (pCGI->CFI.block_high )+2; //����Ӱ����״̬�������꣬������Ҫ�ı�
	


	if (row < 0)
		pCGI->row_num = 0;
	else
		pCGI->row_num = row;
	if(pCGI->CFI.separator==1)
		pCGI->lines += pCGI->row_num * (pCGI->CFI.block_high + 1)+1;       //������ֵ
	else
		pCGI->lines += pCGI->row_num * (pCGI->CFI.block_high )+2; //+1��Ϊ�������ʱ���ټ�һ��1��������ԭ��Ӧ��+2����1�Ϳ�����
	
	if (pCGI->CFI.separator == 1)
		pCGI->SLI.lower_start_y += pCGI->row_num * (pCGI->CFI.block_high + 1) + 1; //����Ӱ����״̬�������꣬������Ҫ�ı�
	else
		pCGI->SLI.lower_start_y += pCGI->row_num * (pCGI->CFI.block_high) + 2; //����Ӱ����״̬�������꣬������Ҫ�ı�
	
	/*COL*/
	if (pCGI->CFI.separator == 1)
		pCGI->cols -= pCGI->col_num * (pCGI->CFI.block_width + 2) + 2;       //��ȥ��ֵ
	else
		pCGI->cols -= pCGI->col_num * (pCGI->CFI.block_width + 2) + 4;
	if (col < 0)
		pCGI->col_num = 0;
	else
		pCGI->col_num = col;
	if (pCGI->CFI.separator == 1)
		pCGI->cols += pCGI->col_num * (pCGI->CFI.block_width + 2)+2;       //������ֵ
	else
		pCGI->cols += pCGI->col_num * (pCGI->CFI.block_width+2)+4;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڣ�����Ϸ�������������ڵ�����cmd���ڣ�����ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int bg_color					��ǰ��ɫ��ȱʡCOLOR_BLACK��
		   const int fg_color					������ɫ��ȱʡCOLOR_WHITE��
		   const bool cascade					���Ƿ�����ȱʡΪtrue-������
  �� �� ֵ��
  ˵    ����1��cascade = trueʱ
				ͬ���޸���Ϸ���������ɫ
				ͬ���޸�����״̬���������ı��ı���ɫ��ǰ��ɫ����Ŀ�ı��ı���ɫ��ǰ��ɫ���䣩
			2���������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15
				    ǰ��ɫ����ɫ��ֵһ�µ����޷���������
					ǰ��ɫ������״̬����Ŀǰ��ɫ�������޷�������Ŀ��ʾ
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
		sprintf(f, "%X", pCGI->area_fgcolor);  //ת���ɴ�д16������
		strcat_s(color, b);
		strcat_s(color, f);
		system(color); //������cmd������ɫ���Ĺ���

		gmw_set_status_line_color(pCGI, 0);
		gmw_set_status_line_color(pCGI, 1);
	}
	else {
		pCGI->area_bgcolor = bgcolor;
		pCGI->area_fgcolor = fgcolor;
	}
	
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ô��ڵ�����
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *fontname					���������ƣ�ֻ����"Terminal"��"������"���֣������򷵻�-1�����ı����壩
		   const int fs_high					������߶ȣ�ȱʡ������Ϊ16�������������ƣ���Ϊ��֤��
		   const int fs_width					������߶ȣ�ȱʡ������Ϊ8�������������ƣ���Ϊ��֤��
  �� �� ֵ��
  ˵    ����1����cmd_console_tools�е�setfontsize���ƣ�Ŀǰֻ֧�֡��������塱�͡������塱
            2������������������ֱ�ӷ��أ�����ԭ�������ò���
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO *const pCGI, const char *fontname, const int fs_high, const int fs_width)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (strcmp(fontname, "������") == 0 || strcmp(fontname, "Terminal") == 0) {
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʱ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type						����ʱ�����ͣ�ĿǰΪ3�֣�
		   const int delay_ms					����msΪ��λ����ʱ
			   ���߿����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ��ɫ�����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ɫ���ƶ�����ʱ��BLOCK_MOVED_DELAY_MS ~ �������ޣ���Ϊ��֤��ȷ�� <BLOCK_MOVED_DELAY_MS ���� BLOCK_MOVED_DELAY_MS��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int delay_ms)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ���������������Ϸ����ܽṹ֮����Ҫ�����Ķ�������
  ��    �ܣ�CONSOLE_GRAPHICS_INFO *const pCGI	��
		   const int up_lines					���ϲ�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int down_lines				���²�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int left_cols					����߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int right_cols				���ұ߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
  �� �� ֵ��
  ˵    �����������еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->cols -= pCGI->extern_left_cols + pCGI->extern_right_cols;//��ȥ��ֵ
	pCGI->lines -= pCGI->extern_up_lines + pCGI->extern_down_lines;

	pCGI->start_x -= pCGI->extern_up_lines;//��ȥ��ֵ?
	pCGI->start_y -= pCGI->extern_left_cols;

	pCGI->SLI.lower_start_y -= pCGI->extern_up_lines; //����Ӱ����״̬�������꣬������Ҫ�ı�
	pCGI->SLI.top_start_y -= pCGI->extern_up_lines; //����Ӱ����״̬�������꣬������Ҫ�ı�
	pCGI->SLI.lower_start_x -= pCGI->extern_left_cols;//Ӱ����״̬��������
	pCGI->SLI.top_start_x -= pCGI->extern_left_cols;//Ӱ����״̬��������
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
	pCGI->cols += pCGI->extern_left_cols + pCGI->extern_right_cols;//������ֵ
	pCGI->lines += pCGI->extern_up_lines + pCGI->extern_down_lines;

	pCGI->start_x += pCGI->extern_up_lines;//����ֵ
	pCGI->start_y += pCGI->extern_left_cols;

	pCGI->SLI.lower_start_y += pCGI->extern_up_lines; //����Ӱ����״̬�������꣬������Ҫ�ı�
	pCGI->SLI.top_start_y += pCGI->extern_up_lines; //����Ӱ����״̬�������꣬������Ҫ�ı�
	pCGI->SLI.lower_start_x += pCGI->extern_left_cols;//Ӱ����״̬��������
	pCGI->SLI.top_start_x += pCGI->extern_left_cols;//Ӱ����״̬��������

	

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 2) {
		strcpy_s(pCGI->CFI.top_left, "��");
		strcpy_s(pCGI->CFI.lower_left, "��");
		strcpy_s(pCGI->CFI.top_right, "��");
		strcpy_s(pCGI->CFI.lower_right, "��");
		strcpy_s(pCGI->CFI.h_normal, "��");
		strcpy_s(pCGI->CFI.v_normal, "��");
		strcpy_s(pCGI->CFI.h_top_separator, "��");
		strcpy_s(pCGI->CFI.h_lower_separator, "��");
		strcpy_s(pCGI->CFI.v_left_separator, "��");
		strcpy_s(pCGI->CFI.v_right_separator, "��");
		strcpy_s(pCGI->CFI.mid_separator, "��");	
	}
	else if (type == 1) {
		strcpy_s(pCGI->CFI.top_left, "�X");
		strcpy_s(pCGI->CFI.lower_left, "�^");
		strcpy_s(pCGI->CFI.top_right, "�[");
		strcpy_s(pCGI->CFI.lower_right, "�a");
		strcpy_s(pCGI->CFI.h_normal, "�T");
		strcpy_s(pCGI->CFI.v_normal, "�U");
		strcpy_s(pCGI->CFI.h_top_separator, "�j");
		strcpy_s(pCGI->CFI.h_lower_separator, "�m");
		strcpy_s(pCGI->CFI.v_left_separator, "�d");
		strcpy_s(pCGI->CFI.v_right_separator, "�g");
		strcpy_s(pCGI->CFI.mid_separator, "�p");
	}
	else if (type == 3) {
		strcpy_s(pCGI->CFI.top_left, "�V");
		strcpy_s(pCGI->CFI.lower_left, "�\");
		strcpy_s(pCGI->CFI.top_right, "�Y");
		strcpy_s(pCGI->CFI.lower_right, "�_");
		strcpy_s(pCGI->CFI.h_normal, "�T");
		strcpy_s(pCGI->CFI.v_normal, "��");
		strcpy_s(pCGI->CFI.h_top_separator, "�h");
		strcpy_s(pCGI->CFI.h_lower_separator, "�k");
		strcpy_s(pCGI->CFI.v_left_separator, "�b");
		strcpy_s(pCGI->CFI.v_right_separator, "�e");
		strcpy_s(pCGI->CFI.mid_separator, "�n");
	}
	else if (type == 4) {
		strcpy_s(pCGI->CFI.top_left, "�W");
		strcpy_s(pCGI->CFI.lower_left, "�]");
		strcpy_s(pCGI->CFI.top_right, "�Z");
		strcpy_s(pCGI->CFI.lower_right, "�`");
		strcpy_s(pCGI->CFI.h_normal, "��");
		strcpy_s(pCGI->CFI.v_normal, "�U");
		strcpy_s(pCGI->CFI.h_top_separator, "�i");
		strcpy_s(pCGI->CFI.h_lower_separator, "�l");
		strcpy_s(pCGI->CFI.v_left_separator, "�c");
		strcpy_s(pCGI->CFI.v_right_separator, "�f");
		strcpy_s(pCGI->CFI.mid_separator, "�o");
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const char *...						����11�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right,
	const char *lower_right, const char *h_normal, const char *v_normal, const char *h_top_separator,
	const char *h_lower_separator, const char *v_left_separator, const char *v_right_separator, const char *mid_separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�ɫ��������С���Ƿ���Ҫ�ָ��ߵ�
  ������������������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int block_width						����ȣ�����ȱʡ2����ΪԼ�������Ϊ�����Ʊ�����������������Ҫ+1��
			const int block_high						���߶ȣ�����ȱʡ1��
			const bool separator						���Ƿ���Ҫ�ָ��ߣ�ȱʡΪtrue����Ҫ�ָ��ߣ�
  �� �� ֵ��
  ˵    ������ܴ�С/�Ƿ���Ҫ�ָ��ߵȵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO *const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	//��
	if (pCGI->inited != CGI_INITED)
		return -1;
		
	if (pCGI->CFI.separator == 1)
		pCGI->cols -= pCGI->col_num * (pCGI->CFI.block_width + 2)+2;//��ȥ��ֵ
	else
		pCGI->cols -= pCGI->col_num * (pCGI->CFI.block_width )+4;//����+2��set_rowcol

	if (block_width <= 0)
		pCGI->CFI.block_width = 2;
	else if((block_width)%2==1)
		pCGI->CFI.block_width = block_width+1;
	else
		pCGI->CFI.block_width = block_width;
	

	//��
	if (pCGI->CFI.separator == 1)
		pCGI->lines -= pCGI->row_num * (pCGI->CFI.block_high + 1)+1;//��ȥ��ֵ
	else
		pCGI->lines -= pCGI->row_num * (pCGI->CFI.block_high )+2;//����+1��set_rowcol

	if (pCGI->CFI.separator == 1)
		pCGI->SLI.lower_start_y-= pCGI->row_num * (pCGI->CFI.block_high + 1);//����Ӱ����״̬����������
	else
		pCGI->SLI.lower_start_y -= pCGI->row_num * (pCGI->CFI.block_high )+2;

	if (pCGI->CFI.block_high <= 0)
		pCGI->CFI.block_high = 1;
	else
		pCGI->CFI.block_high = block_high;
	
	
	



	pCGI->CFI.separator = separator;//separator֮��ı�

	if (pCGI->CFI.separator == 1)
		pCGI->SLI.lower_start_y += pCGI->row_num * (pCGI->CFI.block_high + 1);//����Ӱ����״̬����������
	else
		pCGI->SLI.lower_start_y += pCGI->row_num * (pCGI->CFI.block_high) + 2;

	if (pCGI->CFI.separator == 1)
		pCGI->lines += pCGI->row_num * (pCGI->CFI.block_high + 1)+1;//������ֵ
	else
		pCGI->lines += pCGI->row_num * (pCGI->CFI.block_high)+2;

	if (pCGI->CFI.separator == 1)
		pCGI->cols += pCGI->col_num * (pCGI->CFI.block_width + 2)+2;
	else
		pCGI->cols += pCGI->col_num * (pCGI->CFI.block_width)+4;

	
	

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BORDER_TYPE �ṹ�е���ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int bg_color					������ɫ��ȱʡ -1��ʾ�ô��ڱ���ɫ��
			const int fg_color					��ǰ��ɫ��ȱʡ -1��ʾ�ô���ǰ��ɫ��
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ˫�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 2) {
		strcpy_s(pCGI->CBI.top_left, "��");
		strcpy_s(pCGI->CBI.lower_left, "��");
		strcpy_s(pCGI->CBI.top_right, "��");
		strcpy_s(pCGI->CBI.lower_right, "��");
		strcpy_s(pCGI->CBI.h_normal, "��");
		strcpy_s(pCGI->CBI.v_normal, "��");

	}
	else if (type == 1) {
		strcpy_s(pCGI->CBI.top_left, "�X");
		strcpy_s(pCGI->CBI.lower_left, "�^");
		strcpy_s(pCGI->CBI.top_right, "�[");
		strcpy_s(pCGI->CBI.lower_right, "�a");
		strcpy_s(pCGI->CBI.h_normal, "�T");
		strcpy_s(pCGI->CBI.v_normal, "�U");
	}
	else if (type == 3) {
		strcpy_s(pCGI->CBI.top_left, "�V");
		strcpy_s(pCGI->CBI.lower_left, "�\");
		strcpy_s(pCGI->CBI.top_right, "�Y");
		strcpy_s(pCGI->CBI.lower_right, "�_");
		strcpy_s(pCGI->CBI.h_normal, "�T");
		strcpy_s(pCGI->CBI.v_normal, "��");
	}
	else if (type == 4) {
		strcpy_s(pCGI->CBI.top_left, "�W");
		strcpy_s(pCGI->CBI.lower_left, "�]");
		strcpy_s(pCGI->CBI.top_right, "�Z");
		strcpy_s(pCGI->CBI.lower_right, "�`");
		strcpy_s(pCGI->CBI.h_normal, "��");
		strcpy_s(pCGI->CBI.v_normal, "�U");
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *...					����6�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right, const char *lower_right, const char *h_normal, const char *v_normal)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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

	
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ÿ����Ϸɫ��(����)�Ƿ���ҪС�߿�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡfalse��
  �� �� ֵ��
  ˵    �����߿�Լ��Ϊ�����Ʊ����˫��
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CBI.block_border = on_off;
	gmw_set_block_default_linetype(pCGI, 1);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ����״̬��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡtrue��
  �� �� ֵ��
  ˵    ����1��״̬�������Լ�����£�
			   1.1����״̬��ֻ��һ�У������������Ϸ�����/�б�����棬Ϊ��������ʼһ�У�����������Ͻ����������״̬�������꣩
			   1.2����״̬��ֻ��һ�У������������·����ߵ�����
			   1.3��״̬���Ŀ��Ϊ�������ȣ������Ϣ������ض�
		   2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	
	if (type == TOP_STATUS_LINE) {
		pCGI->lines -= pCGI->top_status_line * 1;//��ȥ��ֵ
		pCGI->SLI.lower_start_y -= pCGI->top_status_line * 1;
		pCGI->top_status_line = on_off;
		pCGI->SLI.is_top_status_line = on_off;
		pCGI->lines += pCGI->top_status_line * 1;//������ֵ
		pCGI->SLI.lower_start_y += pCGI->top_status_line * 1;
	}
	else {
		pCGI->lines -= pCGI->lower_status_line * 1;//��ȥ��ֵ
		pCGI->lower_status_line = on_off;
		pCGI->SLI.is_lower_status_line = on_off;
		pCGI->lines += pCGI->lower_status_line * 1;//����ֵ
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������״̬������ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const int normal_bgcolor			�������ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int normal_fgcolor			�������ı�ǰ��ɫ��ȱʡ -1��ʾʹ�ô���ǰ��ɫ��
			const int catchy_bgcolor			����Ŀ�ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int catchy_fgcolor			����Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
  ���������
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
			pCGI->SLI.top_catchy_fgcolor = 14;//����
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
			pCGI->SLI.lower_catchy_fgcolor = 14;//����
		else
			pCGI->SLI.lower_catchy_fgcolor = catchy_fgcolor;
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�к�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���к�Լ��Ϊ��ĸA��ʼ�������У��������26�����a��ʼ������52��ͳһΪ*��ʵ��Ӧ�ò����ܣ�
            2���Ƿ���ʾ�кŵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->cols -= pCGI->draw_frame_with_row_no * 2;//��ȥ��ֵ
	pCGI->draw_frame_with_row_no = on_off;
	pCGI->cols+= pCGI->draw_frame_with_row_no * 2;//����ֵ
	

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�б�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���б�Լ��Ϊ����0��ʼ�������У�����0-99������99ͳһΪ**��ʵ��Ӧ�ò����ܣ�
            2���Ƿ���ʾ�б�ı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->lines -= pCGI->draw_frame_with_col_no * 1;//����
	pCGI->SLI.lower_start_y-= pCGI->draw_frame_with_col_no * 1;//Ӱ������״̬��������
	pCGI->SLI.top_start_y-= pCGI->draw_frame_with_col_no * 1;

	pCGI->draw_frame_with_col_no = on_off;

	pCGI->lines += pCGI->draw_frame_with_col_no * 1;//����
	pCGI->SLI.lower_start_y += pCGI->draw_frame_with_col_no * 1;//Ӱ������״̬��������
	pCGI->SLI.top_start_y += pCGI->draw_frame_with_col_no * 1;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ CONSOLE_GRAPHICS_INFO �ṹ���еĸ���Աֵ
  ���������
  �� �� ֵ��
  ˵    ����1�����������ã���ӡ��ʽ�Զ���
            2������������������δ���ù������Բ�ʵ��
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��� CONSOLE_GRAPHICS_INFO �ṹ����ȱʡֵ���г�ʼ��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
		   const int row					����Ϸ����ɫ��������ȱʡ10��
		   const int col					����Ϸ����ɫ��������ȱʡ10��
		   const int bgcolor				���������ڱ���ɫ��ȱʡ COLOR_BLACK��
		   const int fgcolor				���������ڱ���ɫ��ȱʡ COLOR_WHITE��
  �� �� ֵ��
  ˵    �������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ��
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* �����ñ�� */
	//gmw_set_ext_rowcol(pCGI, col, row);
	pCGI->inited = CGI_INITED;
	//gmw_set_color(pCGI, bgcolor, fgcolor);
	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	pCGI->col_num = col;
	pCGI->row_num = row;//������������
	pCGI->start_x = pCGI->extern_up_lines;  
	pCGI->start_y = pCGI->extern_left_cols;

	gmw_set_font(pCGI,"Terminal");//��������,�߶ȿ��ΪĬ��ֵ?
	gmw_set_delay(pCGI, DELAY_OF_DRAW_BLOCK, 0);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_FRAME, 0);
	gmw_set_delay(pCGI, DELAY_OF_BLOCK_MOVED, 30);//����ʱ��
	gmw_set_ext_rowcol(pCGI);//���ö�����
	gmw_set_status_line_switch(pCGI, 0, 1);
	gmw_set_status_line_switch(pCGI, 1, 1);//����״̬������
	gmw_set_status_line_color(pCGI, TOP_STATUS_LINE, -1, -1, -1, -1);
	gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE, -1, -1, -1, -1);//״̬����ɫ����
	gmw_set_rowno_switch(pCGI, 0);
	gmw_set_colno_switch(pCGI, 0);//�������к��б�
	gmw_set_block_border_switch(pCGI, 0);//ɫ���ޱ߿�
	gmw_set_frame_style(pCGI, 2,1,1);//ɫ���С���ָ�����
	gmw_set_frame_color(pCGI);
	gmw_set_frame_linetype(pCGI);//Ĭ��ȫ˫�߿�

	//pCGI->start_x = ;
	//pCGI->start_y = ;
	//cmd��������
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

	//cnd��������
	if (pCGI->CFI.separator == 1)
		pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + (pCGI->col_num * (pCGI->CFI.block_width + 2) + 2)+1;
	else
		pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + (pCGI->col_num * (pCGI->CFI.block_width) + 4) + 1;


	if (pCGI->draw_frame_with_row_no)
		pCGI->cols += 2;
	//����״̬����ʼλ������
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.lower_start_y = pCGI->row_num * (pCGI->CFI.block_high + 1) + 1 + pCGI->extern_up_lines;//Ϊ�������෴?
	if (pCGI->SLI.is_top_status_line == 1)
		pCGI->SLI.lower_start_y++;//����״̬��+1
	if(pCGI->draw_frame_with_col_no==1)
		pCGI->SLI.lower_start_y++;//���б�+1
	pCGI->SLI.lower_start_x = pCGI->extern_left_cols;
	//cct_gotoxy(1, 30);
	//cout << pCGI->cols;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ���
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
  �� �� ֵ��
  ˵    ��������ɲο�demo��Ч��
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
		Y+=2;      //��ʾ�кŵĻ�����һ��
	//X = pCGI->extern_up_lines + 1;
	//Y = pCGI->extern_left_cols;
	if (pCGI->SLI.is_top_status_line == 1)
		X++;  //����״̬����+1
	
	
	
	if (pCGI->CFI.separator == 1) {
		if (pCGI->draw_frame_with_col_no == 1) { //�к�
			cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);//���к���ɫ��������ɫһ�£���CFI��ɫ��һ��һ��
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
		cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);//�ָ������ɫ
		
		cct_showstr(Y, X, pCGI->CFI.top_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);//��һ��
		//cout << pCGI->draw_frame_with_col_no;
		for (int j = 0; j < pCGI->col_num - 1; j++) {//��һ��
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
		//��ʼ�ڶ�С��
		int i0 = 0;
		for (; i0 < pCGI->row_num - 1; i0++) {
			int j = 0;
			for (; j < pCGI->CFI.block_high; j++) {
				if (pCGI->draw_frame_with_row_no == 1 && j == pCGI->CFI.block_high / 2) {//��ӡ�б�
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
		//���һ��
		for (int i = 0; i < pCGI->CFI.block_high; i++) {
			if (pCGI->draw_frame_with_row_no == 1 && i == pCGI->CFI.block_high / 2) {//��ӡ�б�
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
	else {//�޷ָ���
	if (pCGI->draw_frame_with_col_no == 1) { //�к�
		cct_gotoxy(Y, X);
		cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);//���к���ɫ��areaһ�¶���һ������һ��
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
		cct_showstr(Y, X, pCGI->CFI.top_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);//��һ��

		for (int j = 0; j < pCGI->col_num * (pCGI->CFI.block_width )/2; j++) {
			cout << pCGI->CFI.h_normal;
		}
		cout << pCGI->CFI.top_right;
		
		Sleep(time);
		//��ʼ�ڶ�С��
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
		
		cct_gotoxy(Y, ++X);//ĩ��
		cout << pCGI->CFI.lower_left;
		for (int j = 0; j < pCGI->col_num * (pCGI->CFI.block_width )/2 ; j++) {
			cout << pCGI->CFI.h_normal;
		}
		cout << pCGI->CFI.lower_right;
		Sleep(time);
	}


	
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���״̬������ʾ��Ϣ
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type							��ָ������/��״̬��
		   const char *msg						��������Ϣ
		   const char *catchy_msg					����Ҫ�ر��ע����Ϣ����������Ϣǰ��ʾ��
  �� �� ֵ��
  ˵    ����1���������޶�Ϊ����ܵĿ�ȣ����к��б�λ�ã����������ȥ
            2��������һ���ַ���ĳ���ֵ�ǰ������ᵼ�º������룬Ҫ����
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const char *msg, const char *catchy_msg)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if(type == TOP_STATUS_LINE&&pCGI->SLI.is_top_status_line==1){
		int X, Y;
		Y = pCGI->extern_left_cols;
		X = pCGI->extern_up_lines;
		
		
		cct_gotoxy(Y, X);//��ʼ������ݶ�����������
		cct_setcolor(pCGI->area_bgcolor, pCGI->area_bgcolor);
		cout << "                                     ";//���ԭ���Ķ���
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
			X++;//����״̬��+1
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//���б�+1
		cct_gotoxy(Y,X);
		//cct_setcolor(0, 0);
		cct_setcolor(pCGI->area_bgcolor, pCGI->area_bgcolor);
		cout << "                                     ";//���ԭ���Ķ���
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
			X++;//����״̬��+1
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//���б�+1
		cct_gotoxy(Y, X);
		if (catchy_msg != NULL) {
			cct_setcolor(pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor);
			cout << catchy_msg;
		}
		cct_setcolor(pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);
		cout << msg;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ��ʾĳһ��ɫ��(����Ϊ�ַ���������Ϊrow/col)
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const BLOCK_DISPLAY_INFO *const bdi		����Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
  �� �� ֵ��
  ˵    ����1��BLOCK_DISPLAY_INFO �ĺ����ͷ�ļ����÷��ο���������
            2��bdi_valueΪ BDI_VALUE_BLANK ��ʾ�հ׿飬Ҫ���⴦��
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO *const bdi)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/*ɫ������ϵ��ʼ����Ϊ(0, 0), ת����cmd����ϵΪ(extern_col + 1 + 1 + 2, extern_row + 3)
	��˽�(i,j)ɫ��ת��Ϊcmd����ϵ����(col_no*(block_width+2)+�ϱߵĳ�ֵ,(row_no*(block_high+1)))+�ϱߵĳ�ʼֵ) ָ ÿһ��ɫ������Ͻ�   */
	int bdi_value1=0;   //���ǻ�bdi�������±�Ϊbdi_value�Ŀ飬���ǻ�bdi������valueֵ����bdi_value��ɫ�飬bdi_value1���±�
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
	

	if (pCGI->CFI.separator == 1) {//�зָ���

		//�������е�����ת���ɻ�ͼcmd������XY
		Y = col_no * (pCGI->CFI.block_width + 2) + pCGI->extern_left_cols + 2;//+2�ǿ�ܵ���߿�
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//���б�

		X = row_no * (pCGI->CFI.block_high + 1) + pCGI->extern_up_lines + 1;//+1���Ͽ�ܵı߿�
		if (pCGI->SLI.is_top_status_line == 1)
			X++;//����״̬��
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//���б�

		cct_setcolor(bg_color, fg_color);
		cct_gotoxy(Y, X);

		if (pCGI->CBI.block_border == 1 && bdi_value1 != 0) {

			cout << pCGI->CBI.top_left;      //��һ��
			Sleep(time);
			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;
				Sleep(time);
			}
			cout << pCGI->CBI.top_right;
			Sleep(time);

			cct_gotoxy(Y, X + 1);
			int j;
			for (j = 0; j < pCGI->CFI.block_high - 2; j++) {    //�м�ļ��У���ȥɫ�鶥�͵���

				if (j == ((pCGI->CFI.block_high - 2) / 2)) {	//���м����һ�У��������ݵ���
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//�������
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
			cout << pCGI->CBI.lower_left;      //���һ��
			Sleep(time);
			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;
				Sleep(time);
			}
			cout << pCGI->CBI.lower_right;
			Sleep(time);
		}
		else {//�ޱ߿�

			for (int j = 0; j < pCGI->CFI.block_high; j++) {
				cct_gotoxy(Y, X + j);
				if (j == ((pCGI->CFI.block_high) / 2)) {//���м����һ�У��������ݵ���
					
					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//�������
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
	else {//�޷ָ���

		//�������е�����ת���ɻ�ͼcmd������XY
		Y = col_no * (pCGI->CFI.block_width ) + pCGI->extern_left_cols + 2;//+2�ǿ�ܵ���߿�
		if (pCGI->draw_frame_with_row_no == 1)
			Y += 2;//���б�

		X = row_no * (pCGI->CFI.block_high ) + pCGI->extern_up_lines + 1;//+1���Ͽ�ܵı߿�
		if (pCGI->SLI.is_top_status_line == 1)
			X++;//����״̬��
		if (pCGI->draw_frame_with_col_no == 1)
			X++;//���б�

		cct_setcolor(bg_color, fg_color);
		cct_gotoxy(Y,X);

		if (pCGI->CBI.block_border == 1 && bdi_value1 != 0) {//�б߿�

			cout << pCGI->CBI.top_left;      //��һ��
			Sleep(time);
			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;
				Sleep(time);
			}
			cout << pCGI->CBI.top_right;
			Sleep(time);

			
			cct_gotoxy(Y, X + 1);
			int j;
			for (j = 0; j < pCGI->CFI.block_high - 2; j++) {   //�м�ļ��У���ȥɫ�鶥�͵���

				if (j == ((pCGI->CFI.block_high - 2) / 2)) {//���м����һ�У��������ݵ���
					cct_gotoxy(Y, X + 1 + j);
					cout << pCGI->CBI.v_normal;
					Sleep(time);
					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//�������
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
			cout << pCGI->CBI.lower_left;      //���һ��
			Sleep(time);
			for (int i = 0; i < pCGI->CFI.block_width / 2 - 2; i++) {
				cout << pCGI->CBI.h_normal;
				Sleep(time);
			}
			cout << pCGI->CBI.lower_right;
			Sleep(time);
		}
		else {//�ޱ߿�
			for (int j = 0; j < pCGI->CFI.block_high; j++) {
				cct_gotoxy(Y, X + j);
				if (j == ((pCGI->CFI.block_high) / 2)) {//���м����һ�У��������ݵ���

					if (bdi[bdi_value1].content == NULL && bdi[bdi_value1].value != 0) {//�������
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

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ƶ�ĳһ��ɫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const int blank_bdi_value				���ƶ����������ڶ���Ч����ʾʱ���ڱ�ʾ�հ׵�ֵ��һ��Ϊ0���˴���Ϊ�������룬�ǿ��ǵ����ܳ��ֵ����������
		   const BLOCK_DISPLAY_INFO *const bdi		�������ʾֵ/�հ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
		   const int direction						���ƶ�����һ�����֣������cmd_gmw_tools.h
		   const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO *const bdi, const int direction, const int distance)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//cct_gotoxy(pCGI->SLI.lower_start_x + 2, pCGI->SLI.lower_start_y + 2);
	//cout << pCGI->delay_of_block_moved;
	if (pCGI->CFI.separator == 1) {  //�зָ��߰�
		for (int i = 0; i < distance; i++) {
			if (direction == DOWN_TO_UP) {
				for (int j = 0; j < pCGI->CFI.block_high + 1; j++) {
					//if ((j + i * (pCGI->CFI.block_high + 1)) % (pCGI->CFI.block_high + 1) == 0)//˵���ڱ�׼���ڣ���Ϊһ��ʼ������һ���ڿ���
						
					if(j==pCGI->CFI.block_high)
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, DOWN_TO_UP, j + i * (pCGI->CFI.block_high + 1), 1);//���߿���
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
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, UP_TO_DOWN, j + i * (pCGI->CFI.block_high + 1), 1);//���һ������
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

	else {//�޷ָ���
		for (int i = 0; i < distance; i++) {
			if (direction == DOWN_TO_UP) {
				for (int j = 0; j < pCGI->CFI.block_high ; j++) {
					//if ((j + i * (pCGI->CFI.block_high + 1)) % (pCGI->CFI.block_high + 1) == 0)//˵���ڱ�׼����
						move_erase(pCGI, row_no, col_no, bdi_value, bdi, DOWN_TO_UP, j + i * (pCGI->CFI.block_high ), 0);
					//else
						//move_erase(pCGI, row_no, col_no, bdi_value, bdi, DOWN_TO_UP, j + i * (pCGI->CFI.block_high + 1), 1);//���߿���
					Sleep(pCGI->delay_of_block_moved);
					move_draw(pCGI, row_no, col_no, bdi_value, bdi, DOWN_TO_UP, j + i * (pCGI->CFI.block_high ) + 1);
					Sleep(pCGI->delay_of_block_moved);
				}
			}
			else if (direction == UP_TO_DOWN) {
				for (int j = 0; j < pCGI->CFI.block_high ; j++) {
					//if ((j + i * (pCGI->CFI.block_high + 1)) % (pCGI->CFI.block_high + 1) == 0)//˵���ڱ�׼����
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
	
		
		



	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������̻����
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   int &MAction							��������� CCT_MOUSE_EVENT�����ֵ��Ч��Ϊ MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK ����֮һ
		                                               ������� CCT_KEYBOARD_EVENT�����ֵ��Ч
		   int &MRow								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &MCol								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode1							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ��һ����
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode2							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ�ڶ���������ǵ����룬��Ϊ0��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   const bool update_lower_status_line		������ƶ�ʱ���Ƿ�Ҫ�ڱ���������ʾ"[��ǰ���] *��*��/λ�÷Ƿ�"����Ϣ��true=��ʾ��false=����ʾ��ȱʡΪtrue��
  �� �� ֵ����������Լ��
		   1�����������ƶ����õ���MRow/MCol�봫�����ͬ(���ָ��΢С���ƶ�)���򲻷��أ�������
							  �õ����зǷ�λ�ã��򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
							  �õ���MRow/MCol�봫��Ĳ�ͬ(��������һ���仯)������ update_lower_status_line ����������״̬����ʾ"[��ǰ���] *��*��"���ٷ���MOUSE_ONLY_MOVED����Щ��Ϸ���غ�Ҫ����ɫ��Ĳ�ͬ��ɫ��ʾ��
		   2������ǰ������������ҵ�ǰ���ָ��ͣ��������Ϸ�����*��*���ϣ��򷵻� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_LEFT_BUTTON_CLICK, MRow Ϊ�кţ�MCol Ϊ�б�
		                          �ҵ�ǰ���ָ��ͣ���ڷǷ����򣨷���Ϸ������Ϸ�����еķָ��ߣ����򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
		   3������ǰ�������Ҽ������ж����ָ��ͣ�������Ƿ�Ϸ���ֱ�ӷ��� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_RIGHT_BUTTON_CLICK, MRow��MColȡ��ǰֵ����Ϊ�������ǵ��Ҽ������Ҫ���꣩
		   4��������¼����ϵ�ĳ������˫���밴��������ֱ�ӷ��� CCT_KEYBOARD_EVENT��KeyCode1/KeyCode2��Ϊ��Ӧ�ļ���ֵ
 ˵    ����ͨ������ cmd_console_tools.cpp �е� read_keyboard_and_mouse ����ʵ��
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO *const pCGI, int &MAction, int &MRow, int &MCol, int &KeyCode1, int &KeyCode2, const bool update_lower_status_line)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	cct_enable_mouse();
	int old_mr=-1, old_mc = -1;
	//int mr =0 ;              //��cmd����ת��Ϊ����е���������
	//int mc =0 ;
	int MRow0, MCol0;
	 
	int X = pCGI->extern_up_lines;                              //�������X��Y�ֱ�Ϊ��Ϸ��������ĳ�ʼ���Ͻ����꣬?
	int Y = pCGI->extern_left_cols;

	if (pCGI->draw_frame_with_row_no == 1)
		Y += 2;      //��ʾ�кŵĻ�����һ��
	if (pCGI->SLI.is_top_status_line == 1)
		X++;  //����״̬����+1
	if (pCGI->draw_frame_with_col_no == 1)
		X++;
	
	while (1) {
		int a=cct_read_keyboard_and_mouse(MCol0, MRow0, MAction, KeyCode1, KeyCode2);
		if (pCGI->CFI.separator == 1) { //�зָ��߰汾
			if (a == CCT_MOUSE_EVENT) {
				if (MAction == MOUSE_ONLY_MOVED) {
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y + 1);
				//cout << MCol0 << " " << MRow0 << " " << Y << " " << X<<" "<<pCGI->start_x;

					if (((MRow0 - X) % (pCGI->CFI.block_high + 1) <= pCGI->CFI.block_high) && ((MRow0 - X) % (pCGI->CFI.block_high + 1) >= 1))
						MRow = (MRow0 - X) / (pCGI->CFI.block_high + 1);
					else
						MRow = -1; //�Ƿ�����
					if (((MCol0 - Y) % (pCGI->CFI.block_width + 2) <= pCGI->CFI.block_width) && ((MCol0 - Y) % (pCGI->CFI.block_width + 2) >= 2))
						MCol = (MCol0 - Y) / (pCGI->CFI.block_width + 2);
					else
						MCol = -1;//�Ƿ�����
					if (MCol >= pCGI->col_num || MRow >= pCGI->row_num) {
						MCol = -1;
						MRow = -1;//Խ��Ƿ�
					}

					if (MRow == old_mr && MCol == old_mc) {
						continue;
					}
					else if (MRow == -1 || MCol == -1) {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
						cct_setcolor(0, 0);
						cout << "                                                ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//д
						cct_setcolor(0, 7);
						cout << "[��ǰ���] λ�÷Ƿ�";
					}
					else {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
						cct_setcolor(0, 0);
						cout << "                                                    ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
						cct_setcolor(0, 7);
						cout << "[��ǰ���] " << (char)(MRow + 'A') << "��" << MCol << "��";
						return CCT_MOUSE_EVENT;
					}
					old_mc = MCol;
					old_mr = MRow;
				}
				else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
					if (((MRow0 - X) % (pCGI->CFI.block_high + 1) <= pCGI->CFI.block_high) && ((MRow0 - X) % (pCGI->CFI.block_high + 1) >= 1))
						MRow = (MRow0 - X) / (pCGI->CFI.block_high + 1);
					else
						MRow = -1; //�Ƿ�����
					if (((MCol0 - Y) % (pCGI->CFI.block_width + 2) <= pCGI->CFI.block_width) && ((MCol0 - Y) % (pCGI->CFI.block_width + 2) >= 2))
						MCol = (MCol0 - Y) / (pCGI->CFI.block_width + 2);
					else
						MCol = -1;//�Ƿ�����
					if (MCol >= pCGI->col_num || MRow >= pCGI->row_num) {
						MCol = -1;
						MRow = -1;//Խ��Ƿ�
					}

					if (MRow == old_mr && MCol == old_mc) {
						return CCT_MOUSE_EVENT;
					}
					else if (MRow == -1 || MCol == -1) {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
						cct_setcolor(0, 0);
						cout << "                                                ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//д
						cct_setcolor(0, 7);
						cout << "[��ǰ���] λ�÷Ƿ�";
					}
					else {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
						cct_setcolor(0, 0);
						cout << "                                                    ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
						cct_setcolor(0, 7);
						cout << "[��ǰ���] " << (char)(MRow + 'A') << "��" << MCol << "��";

					}
					old_mc = MCol;
					old_mr = MRow;
					return CCT_MOUSE_EVENT;//���ۺϷ���񶼷���
				}
				else if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
					if (((MRow0 - X) % (pCGI->CFI.block_high + 1) <= pCGI->CFI.block_high) && ((MRow0 - X) % (pCGI->CFI.block_high + 1) >= 1))
						MRow = (MRow0 - X) / (pCGI->CFI.block_high + 1);
					else
						MRow = -1; //�Ƿ�����
					if (((MCol0 - Y) % (pCGI->CFI.block_width + 2) <= pCGI->CFI.block_width) && ((MCol0 - Y) % (pCGI->CFI.block_width + 2) >= 2))
						MCol = (MCol0 - Y) / (pCGI->CFI.block_width + 2);
					else
						MCol = -1;//�Ƿ�����
					if (MCol >= pCGI->col_num || MRow >= pCGI->row_num) {
						MCol = -1;
						MRow = -1;//Խ��Ƿ�
					}

					if (MRow == old_mr && MCol == old_mc) {
						continue;
					}
					else if (MRow == -1 || MCol == -1) {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
						cct_setcolor(0, 0);
						cout << "                                                ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//д
						cct_setcolor(0, 7);
						cout << "[��ǰ���] λ�÷Ƿ�";
					}
					else {
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
						cct_setcolor(0, 0);
						cout << "                                                    ";
						cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
						cct_setcolor(0, 7);
						cout << "[��ǰ���] " << (char)(MRow + 'A') << "��" << MCol << "��";
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

		else {    //�޷ָ��߰汾
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
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
					cct_setcolor(0, 0);
					cout << "                                                ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//д
					cct_setcolor(0, 7);
					cout << "[��ǰ���] λ�÷Ƿ�";
				}
				else {
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
					cct_setcolor(0, 0);
					cout << "                                                    ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
					cct_setcolor(0, 7);
					cout << "[��ǰ���] " << (char)(MRow + 'A') << "��" << MCol << "��";
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
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
					cct_setcolor(0, 0);
					cout << "                                                ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//д
					cct_setcolor(0, 7);
					cout << "[��ǰ���] λ�÷Ƿ�";
				}
				else {
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
					cct_setcolor(0, 0);
					cout << "                                                    ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
					cct_setcolor(0, 7);
					cout << "[��ǰ���] " << (char)(MRow + 'A') << "��" << MCol << "��";

				}
				old_mc = MCol;
				old_mr = MRow;
				return CCT_MOUSE_EVENT;//���ۺϷ���񶼷���
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
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
					cct_setcolor(0, 0);
					cout << "                                                ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//д
					cct_setcolor(0, 7);
					cout << "[��ǰ���] λ�÷Ƿ�";
				}
				else {
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);//����
					cct_setcolor(0, 0);
					cout << "                                                    ";
					cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
					cct_setcolor(0, 7);
					cout << "[��ǰ���] " << (char)(MRow + 'A') << "��" << MCol << "��";
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}
