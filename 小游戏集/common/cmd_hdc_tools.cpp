#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//δ���������²Ŵ���������

/* ���������Ҫ��ͷ�ļ� */
#include<algorithm>
#include<cstdlib>
#include<cmath>
extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS�д˴����в����ߣ���Ӱ������ʹ��

/* �Ѷ���ľ�̬ȫ�ֱ��� */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* �����ʶ�ʹ�þ�̬ȫ�ֱ�����������static�����ⲿ���ɼ� */

/* �˴���������Զ��庯����������static�����ⲿ���ɼ� */
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2);//��������

static void filled_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3,const int RGB_value) 
{
	//�����ַ�ʽһ������С�����Σ���һ���ж�(x,y)�Ƿ����������ڣ�������õڶ��ַ�ʽ
		//̫����ˣ����﷢��һ��һ�����ص��ж��Ƿ�����������Ȼ�󻭵��ٶ�̫���ˣ�����˲�仭�꣬���ȸ��޸���䷽��
	//int i, j;
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	int x_min, x_max, y_min, y_max, x_mid, y_mid;
	int sum = 0;
	x_min = min(min(x1, x2), x3);
	y_min = min(min(y1, y2), y3);
	x_max = max(max(x1, x2), x3);
	y_max = max(max(y1, y2), y3);
	x_mid = x1 + x2 + x3 - x_min - x_max;
	y_mid = y1 + y2 + y3 - y_min - y_max;

	//ͨ����������жϵ��Ƿ����������ڽ��л�ͼ
	/*int area = abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));//����AB��AC�����������*2
	for (i = x_min; i <= x_max; i++) {
		for (j = y_min; j <= y_max; j++) {
			sum = 0;
			sum += abs((x2 - i) * (y3 - j) - (x3 - i) * (y2 - j));
			sum += abs((x1 - i) * (y3 - j) - (x3 - i) * (y1 - j));
			sum+=abs((x2 - i) * (y1 - j) - (x1 - i) * (y2 - j));
			if (sum <= area)
				hdc_base_point(i, j);
		}
	}
	hdc_base_point(i, j);*/

	//����ֻ�ò���demo�еĻ��߷�ʽ������ˮƽ�߶������
	int y_max_x, y_min_x, y_mid_x;//����yֵ��Ӧ��x����
	if (y_mid == y1) {
		y_mid_x = x1;
		if (y2 == y_max) {
			y_max_x = x2;
			y_min_x = x3;
		}
		else {
			y_max_x = x3;
			y_min_x = x2;
		}
	}
	else if (y_mid == y2) {
		y_mid_x = x2;
		if (y1 == y_max) {
			y_max_x = x1;
			y_min_x = x3;
		}
		else {
			y_max_x = x3;
			y_min_x = x1;
		}
	}
	else if (y_mid == y3) {
		y_mid_x = x3;
		if (y2 == y_max) {
			y_max_x = x2;
			y_min_x = x1;
		}
		else {
			y_max_x = x1;
			y_min_x = x2;
		}
	}
	int x_left, x_right;

	if (y_mid == y_min&& y_max == y_min) {   //ֱ��
		hdc_set_pencolor(RGB_value);
		hdc_base_line(x_min, y_min, x_max, y_min);
	}
	else if(y_mid==y_min){   //��ˮƽ
		for (int j = y_mid; j <= y_max; j++) {
			x_left = (j - y_max) * (y_max_x - y_mid_x) / (y_max - y_mid) + y_max_x;
			x_right = (j - y_max) * (y_max_x - y_min_x) / (y_max - y_min) + y_max_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
	else if (y_mid == y_max) {  //��ˮƽ
		for (int j = y_min; j <= y_mid; j++) {
			x_left = (j - y_mid) * (y_mid_x - y_min_x) / (y_mid - y_min) + y_mid_x;
			x_right = (j - y_max) * (y_max_x - y_min_x) / (y_max - y_min) + y_max_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
	else {
		for (int j = y_min; j <= y_mid; j++) {
			x_left = (j - y_mid) * (y_mid_x - y_min_x) / (y_mid - y_min) + y_mid_x;
			x_right = (j - y_max) * (y_max_x - y_min_x) / (y_max - y_min) + y_max_x;
			hdc_base_line(x_left, j, x_right, j);
		}
		for (int j = y_mid; j <= y_max; j++) {
			x_left = (j - y_max) * (y_max_x - y_mid_x) / (y_max - y_mid) + y_max_x;
			x_right = (j - y_max) * (y_max_x - y_min_x) / (y_max - y_min) + y_max_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
}
static void left_sector(const int point_x,const int point_y,const int angle_begin,const int angle_end,const int radius)//���ڻ��ڶ����������ڵ�����
{
	
	int x2, y2, x3, y3;
	x2 = point_x + (int)(radius * sin(angle_begin * PI / 180));
	y2 = point_y - (int)(radius * cos(angle_begin * PI / 180));
	x3 = point_x + (int)(radius * sin(angle_end * PI / 180));
	y3 = point_y - (int)(radius * cos(angle_end * PI / 180));
	int max_y, min_y, max_y_x, min_y_x;
	if (y2 > y3) {
		max_y = y2;
		min_y = y3;
		max_y_x = x2;
		min_y_x = x3;
	}
	else {
		max_y = y3;
		max_y_x = x3;
		min_y = y2;
		min_y_x = x2;
	}

	int x_left, x_right;
		
	if (max_y < point_y && min_y < point_y) {  //�ڶ�����
		for (int j = min_y; j <= max_y; j++) {
			x_left = point_x - sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_right = (j - min_y) * (point_x - min_y_x) / (point_y - min_y) + min_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
		for (int j = max_y; j <= point_y; j++) {
			x_left = (j - max_y) * (max_y_x - point_x) / (max_y - point_y) + max_y_x;
			x_right = (j - min_y) * (point_x - min_y_x) / (point_y - min_y) + min_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
	else if (max_y > point_y && min_y > point_y) {   //��������
		for (int j = point_y; j <= min_y; j++) {
			x_left = (j - min_y) * (point_x - min_y_x) / (point_y - min_y) + min_y_x;
			x_right = (j - max_y) * (max_y_x - point_x) / (max_y - point_y) + max_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
		for (int j = min_y; j <= max_y; j++) {
			x_left = point_x - sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_right = (j - max_y) * (max_y_x - point_x) / (max_y - point_y) + max_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
	else {      //��Խ�������޻�������ˮƽ�ߵĴ���
		for (int j = min_y; j < point_y; j++) {
			x_left = point_x - sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_right = (j - min_y) * (point_x - min_y_x) / (point_y - min_y) + min_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
		hdc_base_line(point_x - radius, point_y, point_x, point_y);//�����ĸΪ0 �����
		for (int j = point_y + 1; j <= max_y; j++) {
			x_left = point_x - sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_right = (j - max_y) * (max_y_x - point_x) / (max_y - point_y) + max_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
}

static void right_sector(const int point_x, const int point_y, const int angle_begin, const int angle_end, const int radius)//���ڻ���1һ���������ڵ�����
{
	
	int x2, y2, x3, y3;
	x2 = point_x + (int)(radius * sin(angle_begin * PI / 180));
	y2 = point_y - (int)(radius * cos(angle_begin * PI / 180));
	x3 = point_x + (int)(radius * sin(angle_end * PI / 180));
	y3 = point_y - (int)(radius * cos(angle_end * PI / 180));
	int max_y, min_y, max_y_x, min_y_x;
	if (y2 > y3) {
		max_y = y2;
		min_y = y3;
		max_y_x = x2;
		min_y_x = x3;
	}
	else {
		max_y = y3;
		max_y_x = x3;
		min_y = y2;
		min_y_x = x2;
	}

	int x_left, x_right;
	if (max_y < point_y && min_y < point_y) {  //��һ����
		for (int j = min_y; j <= max_y; j++) {
			x_right = point_x + sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_left = (j - min_y) * (point_x - min_y_x) / (point_y - min_y) + min_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
		for (int j = max_y; j <= point_y; j++) {
			x_right = (j - max_y) * (max_y_x - point_x) / (max_y - point_y) + max_y_x;
			x_left = (j - min_y) * (point_x - min_y_x) / (point_y - min_y) + min_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
	else if (max_y > point_y && min_y > point_y) {   //��������
		for (int j = point_y; j <= min_y; j++) {
			x_right = (j - min_y) * (point_x - min_y_x) / (point_y - min_y) + min_y_x;
			x_left = (j - max_y) * (max_y_x - point_x) / (max_y - point_y) + max_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
		for (int j = min_y; j <= max_y; j++) {
			x_right = point_x + sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_left = (j - max_y) * (max_y_x - point_x) / (max_y - point_y) + max_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
	else {      //��Խһ�����޻�90��
		for (int j = min_y; j < point_y; j++) {
			x_right = point_x + sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_left = (j - min_y) * (point_x - min_y_x) / (point_y - min_y) + min_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
		hdc_base_line(point_x, point_y, point_x + radius, point_y);//�����ĸΪ0 ����
		for (int j = point_y + 1; j <= max_y; j++) {
			x_right = point_x + sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_left = (j - max_y) * (max_y_x - point_x) / (max_y - point_y) + max_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
}
/* ��������˼�����������������ʵ�֣���Ҫ�Ķ� */
/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʼ��
  ���������const int bgcolor������ɫ
            const int fgcolor��ǰ��ɫ
			const int width  ����Ļ��ȣ�����
			const int high   ����Ļ�߶ȣ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* ���ͷţ���ֹ��release���ٴ�init��hdc_release�����룩 */
	hdc_release();

	/* ����init����һ����̬ȫ������¼������hdc_cls()���õ� */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("��������", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //������Ŀ�ȼ��߶�ת��Ϊ�ض��������������!!�ĺ��壺�������8/16�ı��������ж�+1
	cct_cls();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ͷŻ�ͼ��Դ
  ���������
  �� �� ֵ��
  ˵    ����������
***************************************************************************/
void hdc_release()
{
	if (hdc) {
		ReleaseDC(hWnd, hdc);
		hdc = NULL;
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGBֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGB��ɫ��ֵ0-255
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ļ�����е�ͼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_cls()
{
    /* ����һ��Ҫ��һ����ɫ��ʼ������������ص㣬�ҵ�����㷽����ͬѧ����֪ͨ�� */
	hdc_init(_BgColor_, (_FgColor_  + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* ���ֻ���������demoʱ�������hdc_cls()���һ������ȱ�ߵ����������ʱ����
	   ������ֻ������л������⣬���ߴ���ʱֵ */
	Sleep(30);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ����һ�����ص�
  ���������const int x��x���꣬���Ͻ�Ϊ(0,0)
            const int y��y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨�������ڵ��ô�ָ��
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	//if (_Delay_ms > 0)
		//Sleep(_Delay_ms);
		Sleep(0);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x1,y1)-(x2,y2)֮�仭��һ�����ص������
  ���������const int x1�����x���꣬���Ͻ�Ϊ(0,0)
			const int y1�����y���꣬���Ͻ�Ϊ(0,0)
			const int x2���յ�y���꣬���Ͻ�Ϊ(0,0)
			const int y2���յ�y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	//if (_Delay_ms > 0)
		//Sleep(_Delay_ms);
	Sleep(0.9);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ��һ��ָ����ϸ�ĵ�(�û�ʵ��Բ��ģ��)
  ���������const int x			��x���꣬���Ͻ�Ϊ(0,0)
            const int y			��y���꣬���Ͻ�Ϊ(0,0)
			const int thickness	����Ĵ�ϸ������λ1�����޲���(�����ᵼ�²���ȫ���)����ȱʡֵ��
			const int RGB_value	�������ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �����Ľ�����Ч��
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	/* ������ֱ�������ޣ����ǵ����޳���һ����С�ǣ�������Բ����λ��δʵ�� */

	const int tn_end = (tn <= 1) ? 1 : tn/2;

	int angle, level;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;
	int count = 0;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	//�Ľ�����Ч�ʣ������ص�����Ӧ����ֱ����䣬���������Ч�㡣
	int y_min = y-tn_end , y_max = y + tn_end;
	double x_left, x_right;
	for (int j = y_min; j <= y_max; j++) {
		x_left = x + sqrt(pow(tn_end, 2) - pow((j - y), 2));
		x_right = x - sqrt(pow(tn_end, 2) - pow((j - y), 2));
		hdc_base_line(x_left, j, x_right, j);
	}

	/* �û�Բ�ķ�ʽģ��ֵ�,ԭʼ���� */
	/*
	for (level = 1; level <= tn_end; level++) {
		for (angle = 0; angle <= 360; angle ++) {
			//ע�⣬ϵͳ�������ᣬ0����Բ�����·� 
			x1 = x + (int)(level * sin(angle * PI / 180));
			y1 = y - (int)(level * cos(angle * PI / 180));

			//���뾶��Сʱ���Ƕȱ仯��������int�͵�x1/y1�仯����˼��ж���䣬�����ظ���ͬһ���ص� 
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
	}*/

#if 0
	/* �ſ���ע�ͣ����Կ���һ���ֵ����˼������ص���� */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	�������к�����ʵ�֣���������������׼�Ķ�
	1������Ҫ����ϵͳ�������й�ͼ�β����ĺ���
	2�����к�����ʵ�ֶ�����hdc_base_point/hdc_base_line���������
	3����һ�룬�ǲ������к�������Ҫ����������ʵ�ֹ��̣�Ӧ����ʵ����Щ������
	4�������ʵ������ӵĲ���
	5��ϵͳ�ĽǶ��뺯�������еĽǶȺ������180��
   ------------------------------------------------------------------------- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ����߶�
  ���������const int x1		������x
            const int y1		������y
			const int x2		���յ��x
			const int y2		���յ��y
			const int thickness	���߶εĴ�ϸ����ȱʡֵ��
			const int RGB_value	���߶ε���ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ���������������û���hdc_point����ϣ��ٶ�����
                  Ҳ������hdc_base_point/hdc_base_line����ϣ��ٶȿ죩
***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	int tn = thickness;
	int xory = -1; //0������xƽ��,1����yƽ�ƣ�-1������б�ʣ���kƽ��
	int k = 0;//��base��ƽ�Ƶ�б��k����ֱ��б�ʻ�Ϊ������
	if (tn < 1)
		tn = 1;		//��������
	/* ������ֱ�������ޣ����ǵ����޳���һ����С�ǣ�������Բ����λ��δʵ�� */

	const int tn_end = (tn <= 1) ? 1 : tn / 2;
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	hdc_base_line(x1, y1, x2, y2);//�Ȼ��м���

	

	//��ʵ�ϵ���������ַ�ʽ��Ȼ���԰�ֱ�߻����񳤷���һ��ƽ���������ں�����ͼ��ƴ��ʱ���Ӵ�����Ȼ��Ӧ����Ƴ����³����м���̵���ʽ
	
	 if (x2 == x1)
		xory = 1;
	else if (y2 == y1)
		xory = 0;
	else
		k = -(x2 - x1) / (y2 - y1);
	for (int i = 1; i <= tn_end; i++) {//��������չ
		if (xory==1) {
			hdc_base_line(x1+i, y1, x2+i, y2);
			hdc_base_line(x1-i, y1, x2-i, y2);
		}
		else if(xory==0){
			hdc_base_line(x1 , y1+i, x2, y2+i);
			hdc_base_line(x1 , y1-i, x2, y2-i);
		}
		else {//��һ������������k̫��ᵼ����Ծ�ķǳ��죬������϶��������ѭ������һ��,��y�������ᳬ��1����
			int k0 = 0;
			if (k >= 1) {
				while (k0<=i) {
					hdc_base_line(x1 + i, y1 + k0, x2 + i, y2 + k0);
					hdc_base_line(x1 - i, y1 - k0, x2 - i, y2 - k0);
					k0++;
				}
			}
			else if (k <= -1) {
				while (k0 >= -i) {
					hdc_base_line(x1 + i, y1 + k0, x2 + i, y2 + k0);
					hdc_base_line(x1 - i, y1 - k0, x2 - i, y2 - k0);
					k0--;
				}
			}
			else {
				hdc_base_line(x1 + i, y1 + i * double(k), x2 + i, y2 + i * double(k));
				hdc_base_line(x1 - i, y1 - i * double(k), x2 - i, y2 - i * double(k));
			}	
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������������꣬��һ��������
  ���������const int x1		����1�����x
            const int y1		����1�����y
			const int x2		����2�����x
			const int y2		����2�����y
			const int x3		����3�����x
			const int y3		����3�����y
			bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness	���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value	����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �������ж������Ƿ��ߣ�������ߣ�����һ��ֱ�߼���
***************************************************************************/
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled, const int thickness, const int RGB_value)
{
	hdc_line(x1, y1, x2, y2, thickness,RGB_value);
	hdc_line(x2, y2, x3, y3, thickness, RGB_value);
	hdc_line(x3, y3, x1, y1, thickness, RGB_value);
	if (filled) {
		filled_triangle(x1,y1,x2,y2,x3,y3,RGB_value);
	}

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰��ȡ��߶ȣ�����һ��������
  ���������const int left_up_x			�����Ͻ�x
            const int left_up_y			�����Ͻ�y
			const int width				�����
			const int high				���߶�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ����
			bool filled					���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	//�涨����㿪ʼ˳ʱ�������±�Ϊ0��1��2��3
	int x0,y0,x1, y1, x2, y2, x3, y3;
	x0 = left_up_x;
	y0 = left_up_y;
	x1 = x0 + width * cos(rotation_angles / 180.0 * PI);
	y1 = y0 + width * sin(rotation_angles / 180.0 * PI);
	x3 = x0 - high * cos((90 - rotation_angles) / 180.0 * PI);
	y3 = y0 + high * sin((90 - rotation_angles) / 180.0 * PI);
	x2 = x1 + x3 - x0;
	y2 = y1 + y3 - y0;
	//cout << x0 << x1 << x2 << x3 << endl;
	//cout << y0 << y1 << y2 << y3 << endl;
	
	hdc_line(x0, y0, x1, y1, thickness, RGB_value);
	hdc_line(x1, y1, x2, y2, thickness, RGB_value);
	hdc_line(x2, y2, x3, y3, thickness, RGB_value);
	hdc_line(x3, y3, x0, y0, thickness, RGB_value);

	if (filled) {
		filled_triangle(x0, y0, x1, y1, x3, y3,RGB_value);
		filled_triangle(x3,y3,x1,y1,x2,y2,RGB_value);
		hdc_line(x1, y1, x3, y3, 4, RGB_value);

	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰�߳�������һ��������
  ���������const int left_up_x			�����Ͻ�x
			const int left_up_y			�����Ͻ�y
			const int length			���߳�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	hdc_rectangle(left_up_x,left_up_y,length,length,rotation_angles,filled,thickness,RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ��
  ���������const int point_x		��Բ�ĵ�x
            const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	/* ������ֱ�������ޣ����ǵ����޳���һ����С�ǣ�������Բ����λ��δʵ�� */

	const int tn_end = (tn <= 1) ? 1 : tn / 2;

	int  level;
	double angle;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;
	int count = 0;
	int angle_end0=angle_end;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	

	while(angle_end0 <= angle_begin) {
		angle_end0 += 360;
	}

	/* �û�Բ�ķ�ʽģ��ԲȦ */
	for (angle = angle_begin; angle <= angle_end0; angle += 0.4)
	{
		x1 = point_x + (int)((radius ) * sin(angle * PI / 180));
		y1 = point_y - (int)((radius ) * cos(angle * PI / 180));
		hdc_point(x1,y1,thickness,RGB_value);
	}
	/*
	for (level = 0; level <= tn_end; level++) {
		for (angle = angle_begin; angle <= angle_end0; angle += 0.1) {
			// ע�⣬ϵͳ�������ᣬ0����Բ�����·� 
			

			// ���뾶��Сʱ���Ƕȱ仯��������int�͵�x1/y1�仯����˼��ж���䣬�����ظ���ͬһ���ص� 
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
		for (angle = angle_begin; angle <= angle_end0; angle += 0.1) {
			// ע�⣬ϵͳ�������ᣬ0����Բ�����·� 
			x1 = point_x + (int)((radius - level) * sin(angle * PI / 180));
			y1 = point_y - (int)((radius - level) * cos(angle * PI / 180));

			// ���뾶��Сʱ���Ƕȱ仯��������int�͵�x1/y1�仯����˼��ж���䣬�����ظ���ͬһ���ص� 
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
	}*/
	
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ������
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ��������ʼ/�����ǶȲ�ֵΪ360�ı���ʱ������������
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	//�Ƕ�Ԥ����
	int angle_b = angle_begin;
	int angle_e = angle_end;
	if (angle_b < 0)
		angle_b += 360;
	else if (angle_b > 360)
		angle_b -= 360;
	if (angle_e < 0)
		angle_e += 360;
	else if (angle_e > 360)
		angle_e -= 360;

	

	hdc_arc(point_x, point_y, radius, angle_begin, angle_end, thickness, RGB_value);
	int x2, y2, x3, y3;
	x2= point_x + (int)(radius * sin(angle_begin * PI / 180));
	y2 = point_y - (int)(radius * cos(angle_begin * PI / 180));
	x3 = point_x + (int)(radius * sin(angle_end * PI / 180));
	y3 = point_y - (int)(radius * cos(angle_end * PI / 180));
	if (angle_e != angle_b) { //��Բ�����뾶��
		hdc_line(point_x, point_y, x2, y2, thickness, RGB_value);
		hdc_line(point_x, point_y, x3, y3, thickness, RGB_value);
	}
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	//���
	if (filled) {  //���������demo�е�base_line����䣬��������ԲȦ����ֱ��ɨ�裬����Զ��ӵ�ʱ������ӳٸо�
		
		if (angle_e == angle_b) { //��Բ
			left_sector(point_x, point_y, 0, 180, radius);
			right_sector(point_x, point_y, 180, 360, radius);
		}
		else if (angle_e > 180 && angle_b >=180&&angle_e>angle_b) //˵��������
			left_sector(point_x, point_y,  angle_b, angle_e, radius);
		else if(angle_e <= 180 && angle_b < 180 && angle_e>angle_b)//���Ұ��
			right_sector(point_x, point_y, angle_b, angle_e, radius);
		else {                                                                          //������ң����
			if (angle_b > angle_e) {  //���0/360
				if(angle_b<180){//��Ҫ��Խ360ҲҪ��Խ180
					right_sector(point_x, point_y, angle_b, 180, radius);
					left_sector(point_x, point_y, 180, 360, radius);
					right_sector(point_x, point_y, 0, angle_e, radius);
				}
				else if (angle_e > 180) {//��Ҫ��Խ360ҲҪ��Խ180
					left_sector(point_x, point_y, angle_b, 360, radius);
					right_sector(point_x, point_y, 0, 180, radius);
					left_sector(point_x, point_y, 180, angle_e, radius);
				}
				else {  //���ο�Խ0
					left_sector(point_x, point_y, angle_b, 360, radius);
					right_sector(point_x, point_y, 0, angle_e, radius);
				}
			}
			else if (angle_b < 180 && angle_e>180) {//���ο�Խ180
				right_sector(point_x, point_y, angle_b, 180, radius);
				left_sector(point_x, point_y, 180, angle_e, radius);
			}
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	hdc_arc(point_x,point_y,radius,0,360,thickness,RGB_value);

	//ԲȦʽ���,�����ٶȺ����е�������
	/*if (filled) {
		for (level = radius; level >= 0; level--) {
			for (angle = 0; angle <= 360; angle += 0.1) {
				//ע�⣬ϵͳ�������ᣬ0����Բ�����·�
				x1 = point_x + (int)((level)*sin(angle * PI / 180));
				y1 = point_y - (int)((level)*cos(angle * PI / 180));

				//���뾶��Сʱ���Ƕȱ仯��������int�͵�x1/y1�仯����˼��ж���䣬�����ظ���ͬһ���ص�
				if (x1 != old_x1 || y1 != old_y1) {
					old_x1 = x1;
					old_y1 = y1;
					hdc_base_point(x1, y1);
					++count;
				}
			}
		}
	}*/
	//demo��ֱ����䷢��
	if (filled) {
		int y_min = point_y - radius, y_max = point_y + radius;
		double x_left, x_right;
		for (int j = y_min; j <= y_max; j+=2) {
			x_left = point_x + sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_right = point_x - sqrt(pow(radius, 2) - pow((j - point_y), 2));
			//hdc_base_line(x_left, j, x_right, j,2,RGB_value);
			hdc_line(x_left, j, x_right, j, 2, RGB_value);
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ����Բ
  ���������const int point_x			��Բ�ĵ�x
			const int point_y			��Բ�ĵ�y
			const int radius_a			��ƽ����X��İ뾶
			const int radius_b			��ƽ����Y��İ뾶
			const int rotation_angles	����Բ��Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			����ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	//����Բ���ò������̻�����ת��Բ��������ϵ��ת�ķ�ʽ����
	int x, y;
	int x_r, y_r;//��ת�������
	for (double angle = 0; angle <= 360; angle+=0.3) {
		//x = point_x + radius_a * cos(angle / 180 * PI);
		//y = point_y + radius_b * sin(angle / 180 * PI);
		x = radius_a * cos(angle/180*PI);
		y = radius_b * sin(angle/180*PI);
		x_r = x * cos(rotation_angles * PI / 180) - y * sin(rotation_angles * PI / 180);//����������ϵ��ת�෴����Ϊ�����y��������Ϊ����
		y_r = y * cos(rotation_angles * PI / 180) + x * sin(rotation_angles * PI / 180);
		hdc_point(x_r+point_x, y_r+point_y, thickness, RGB_value);
	}
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	if (filled) {  //����Ҳ������ת����ϵ����䣬��ǳ����ף�ֻҪ�����������µ���䣬����������ת����
		int x_left, x_right;
		int x_left_r, x_right_r,j_left_r,j_right_r;//��ת�������ֵ
		for (double j =  - radius_b; j <= radius_b;j+=1) {
			//ע��������Ҫ����ת����pointԲ���������
			x_left = -sqrt(radius_a*radius_a-j*j*radius_a*radius_a/(radius_b*radius_b));
			x_right = sqrt(radius_a * radius_a - j * j * radius_a * radius_a / (radius_b * radius_b));

			x_left_r = x_left * cos(rotation_angles * PI / 180) - j * sin(rotation_angles * PI / 180);  //���
			j_left_r = j * cos(rotation_angles * PI / 180) + x_left * sin(rotation_angles * PI / 180);
			x_right_r = x_right * cos(rotation_angles * PI / 180) - j * sin(rotation_angles * PI / 180);//�ֵ�
			j_right_r= j * cos(rotation_angles * PI / 180) + x_right * sin(rotation_angles * PI / 180);

			
			x_left_r += point_x;//����ԭ����ϵ��ƫ��ֵ����Բ�Ĵ�ԭ���Ƶ�ʵ��λ�á�
			x_right_r += point_x;
			j_left_r += point_y;
			j_right_r += point_y;
			
			
			//hdc_base_line(x_left_r,j_left_r,x_right_r,j_right_r);
			hdc_line(x_left_r, j_left_r, x_right_r, j_right_r, 3, RGB_value);
			//Ϊ����������Ч�ʣ�����j�����������̫С����Ϊֻ����x�ḽ��ʱ����С��j�任��Ӧ��
		}
	}
}

#endif !HDC_SERIES_BY_TEACHER
