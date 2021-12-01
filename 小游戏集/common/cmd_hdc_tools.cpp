#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//未定义的情况下才打开条件编译

/* 允许添加需要的头文件 */
#include<algorithm>
#include<cstdlib>
#include<cmath>
extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS中此处会有波浪线，不影响正常使用

/* 已定义的静态全局变量 */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* 允许适度使用静态全局变量，但仅限static，即外部不可见 */

/* 此处允许添加自定义函数，但仅限static，即外部不可见 */
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2);//函数声明

static void filled_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3,const int RGB_value) 
{
	//有两种方式一种是缩小三角形，另一种判断(x,y)是否在三角形内，这里采用第二种方式
		//太糟糕了，这里发现一个一个像素点判断是否在三角形内然后画点速度太慢了，不能瞬间画完，被迫改修改填充方案
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

	//通过向量叉乘判断点是否在三角形内进行画图
	/*int area = abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));//向量AB，AC求三角形面积*2
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

	//这里只好采用demo中的划线方式，即用水平线段来填充
	int y_max_x, y_min_x, y_mid_x;//三个y值对应的x坐标
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

	if (y_mid == y_min&& y_max == y_min) {   //直线
		hdc_set_pencolor(RGB_value);
		hdc_base_line(x_min, y_min, x_max, y_min);
	}
	else if(y_mid==y_min){   //顶水平
		for (int j = y_mid; j <= y_max; j++) {
			x_left = (j - y_max) * (y_max_x - y_mid_x) / (y_max - y_mid) + y_max_x;
			x_right = (j - y_max) * (y_max_x - y_min_x) / (y_max - y_min) + y_max_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
	else if (y_mid == y_max) {  //底水平
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
static void left_sector(const int point_x,const int point_y,const int angle_begin,const int angle_end,const int radius)//用于画在二、三象限内的扇形
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
		
	if (max_y < point_y && min_y < point_y) {  //在二象限
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
	else if (max_y > point_y && min_y > point_y) {   //在三象限
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
	else {      //跨越二三象限或者是有水平线的存在
		for (int j = min_y; j < point_y; j++) {
			x_left = point_x - sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_right = (j - min_y) * (point_x - min_y_x) / (point_y - min_y) + min_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
		hdc_base_line(point_x - radius, point_y, point_x, point_y);//避免分母为0 的情况
		for (int j = point_y + 1; j <= max_y; j++) {
			x_left = point_x - sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_right = (j - max_y) * (max_y_x - point_x) / (max_y - point_y) + max_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
}

static void right_sector(const int point_x, const int point_y, const int angle_begin, const int angle_end, const int radius)//用于画在1一、四象限内的扇形
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
	if (max_y < point_y && min_y < point_y) {  //在一象限
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
	else if (max_y > point_y && min_y > point_y) {   //在四象限
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
	else {      //跨越一四象限或90°
		for (int j = min_y; j < point_y; j++) {
			x_right = point_x + sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_left = (j - min_y) * (point_x - min_y_x) / (point_y - min_y) + min_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
		hdc_base_line(point_x, point_y, point_x + radius, point_y);//避免分母为0 的情
		for (int j = point_y + 1; j <= max_y; j++) {
			x_right = point_x + sqrt(pow(radius, 2) - pow((j - point_y), 2));
			x_left = (j - max_y) * (max_y_x - point_x) / (max_y - point_y) + max_y_x;
			hdc_base_line(x_left, j, x_right, j);
		}
	}
}
/* 下面给出了几个基本函数的完整实现，不要改动 */
/***************************************************************************
  函数名称：
  功    能：初始化
  输入参数：const int bgcolor：背景色
            const int fgcolor：前景色
			const int width  ：屏幕宽度（点阵）
			const int high   ：屏幕高度（点阵）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* 先释放，防止不release而再次init（hdc_release可重入） */
	hdc_release();

	/* 窗口init后，用一个静态全局量记录，后续hdc_cls()会用到 */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("点阵字体", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //将点阵的宽度及高度转换为特定字体的行列数，!!的含义：如果不是8/16的倍数，行列多+1
	cct_cls();
}

/***************************************************************************
  函数名称：
  功    能：释放画图资源
  输入参数：
  返 回 值：
  说    明：可重入
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB三色，值0-255
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  函数名称：
  功    能：清除屏幕上现有的图形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_cls()
{
    /* 发现一定要换一种颜色初始化才能清除像素点，找到更简便方法的同学可以通知我 */
	hdc_init(_BgColor_, (_FgColor_  + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* 部分机器上运行demo时，会出现hdc_cls()后第一根线有缺线的情况，加延时即可
	   如果部分机器运行还有问题，调高此延时值 */
	Sleep(30);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画出一个像素点
  输入参数：const int x：x坐标，左上角为(0,0)
            const int y：y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定，可以在调用处指定
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
  函数名称：
  功    能：在(x1,y1)-(x2,y2)之间画出一个像素点的连线
  输入参数：const int x1：起点x坐标，左上角为(0,0)
			const int y1：起点y坐标，左上角为(0,0)
			const int x2：终点y坐标，左上角为(0,0)
			const int y2：终点y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定
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
  函数名称：
  功    能：在(x,y)位置处用指定颜色画一个指定粗细的点(用画实心圆来模拟)
  输入参数：const int x			：x坐标，左上角为(0,0)
            const int y			：y坐标，左上角为(0,0)
			const int thickness	：点的粗细，下限位1，上限不限(如过大会导致不完全填充)（有缺省值）
			const int RGB_value	：点的颜色（有缺省值）
  返 回 值：
  说    明：改进运行效率
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	/* 不卡点直径的上限，但是单上限超过一定大小是，画出的圆部分位置未实心 */

	const int tn_end = (tn <= 1) ? 1 : tn/2;

	int angle, level;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;
	int count = 0;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	//改进运行效率，在像素的世界应当用直线填充，不会产生无效点。
	int y_min = y-tn_end , y_max = y + tn_end;
	double x_left, x_right;
	for (int j = y_min; j <= y_max; j++) {
		x_left = x + sqrt(pow(tn_end, 2) - pow((j - y), 2));
		x_right = x - sqrt(pow(tn_end, 2) - pow((j - y), 2));
		hdc_base_line(x_left, j, x_right, j);
	}

	/* 用画圆的方式模拟粗点,原始方法 */
	/*
	for (level = 1; level <= tn_end; level++) {
		for (angle = 0; angle <= 360; angle ++) {
			//注意，系统的坐标轴，0°在圆的最下方 
			x1 = x + (int)(level * sin(angle * PI / 180));
			y1 = y - (int)(level * cos(angle * PI / 180));

			//当半径很小时，角度变化不会引起int型的x1/y1变化，因此加判断语句，避免重复画同一像素点 
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
	}*/

#if 0
	/* 放开此注释，可以看到一个粗点用了几个像素点组成 */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	给出下列函数的实现，函数名及参数表不准改动
	1、不需要调用系统的其他有关图形操作的函数
	2、下列函数的实现都基于hdc_base_point/hdc_base_line函数的组合
	3、想一想，是不是所有函数都需要给出独立的实现过程？应该先实现哪些函数？
	4、填充是实现中最复杂的部分
	5、系统的角度与函数参数中的角度含义相差180°
   ------------------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：画线段
  输入参数：const int x1		：起点的x
            const int y1		：起点的y
			const int x2		：终点的x
			const int y2		：终点的y
			const int thickness	：线段的粗细（有缺省值）
			const int RGB_value	：线段的颜色（有缺省值）
  返 回 值：
  说    明：本函数可以用基于hdc_point的组合（速度慢）
                  也可以用hdc_base_point/hdc_base_line的组合（速度快）
***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	int tn = thickness;
	int xory = -1; //0代表沿x平移,1代表y平移，-1代表有斜率，按k平移
	int k = 0;//划base线平移的斜率k，与直线斜率互为负倒数
	if (tn < 1)
		tn = 1;		//处理下限
	/* 不卡点直径的上限，但是单上限超过一定大小是，画出的圆部分位置未实心 */

	const int tn_end = (tn <= 1) ? 1 : tn / 2;
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	hdc_base_line(x1, y1, x2, y2);//先画中间线

	

	//事实上到最后发现这种方式虽然可以把直线画的像长方体一样平整，但是在和其他图形拼接时连接处不自然，应当设计成上下长，中间最短的形式
	
	 if (x2 == x1)
		xory = 1;
	else if (y2 == y1)
		xory = 0;
	else
		k = -(x2 - x1) / (y2 - y1);
	for (int i = 1; i <= tn_end; i++) {//向两边扩展
		if (xory==1) {
			hdc_base_line(x1+i, y1, x2+i, y2);
			hdc_base_line(x1-i, y1, x2-i, y2);
		}
		else if(xory==0){
			hdc_base_line(x1 , y1+i, x2, y2+i);
			hdc_base_line(x1 , y1-i, x2, y2-i);
		}
		else {//有一个问题就是如果k太大会导致跳跃的非常快，产生间隙，这里用循环处理一下,让y自增不会超过1像素
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
  函数名称：
  功    能：给出三点的坐标，画一个三角形
  输入参数：const int x1		：第1个点的x
            const int y1		：第1个点的y
			const int x2		：第2个点的x
			const int y2		：第2个点的y
			const int x3		：第3个点的x
			const int y3		：第3个点的y
			bool filled			：是否需要填充（有缺省值）
			const int thickness	：边的粗细（有缺省值）
			const int RGB_value	：颜色（有缺省值）
  返 回 值：
  说    明：不判断三点是否共线，如果共线，划出一条直线即可
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
  函数名称：
  功    能：给出左上角坐标及宽度、高度，画出一个长方形
  输入参数：const int left_up_x			：左上角x
            const int left_up_y			：左上角y
			const int width				：宽度
			const int high				：高度
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）
			bool filled					：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	//规定从起点开始顺时针依次下标为0，1，2，3
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
  函数名称：
  功    能：给出左上角坐标及边长，画出一个正方形
  输入参数：const int left_up_x			：左上角x
			const int left_up_y			：左上角y
			const int length			：边长
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	hdc_rectangle(left_up_x,left_up_y,length,length,rotation_angles,filled,thickness,RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一段圆弧
  输入参数：const int point_x		：圆心的x
            const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	/* 不卡点直径的上限，但是单上限超过一定大小是，画出的圆部分位置未实心 */

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

	/* 用画圆的方式模拟圆圈 */
	for (angle = angle_begin; angle <= angle_end0; angle += 0.4)
	{
		x1 = point_x + (int)((radius ) * sin(angle * PI / 180));
		y1 = point_y - (int)((radius ) * cos(angle * PI / 180));
		hdc_point(x1,y1,thickness,RGB_value);
	}
	/*
	for (level = 0; level <= tn_end; level++) {
		for (angle = angle_begin; angle <= angle_end0; angle += 0.1) {
			// 注意，系统的坐标轴，0°在圆的最下方 
			

			// 当半径很小时，角度变化不会引起int型的x1/y1变化，因此加判断语句，避免重复画同一像素点 
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
		for (angle = angle_begin; angle <= angle_end0; angle += 0.1) {
			// 注意，系统的坐标轴，0°在圆的最下方 
			x1 = point_x + (int)((radius - level) * sin(angle * PI / 180));
			y1 = point_y - (int)((radius - level) * cos(angle * PI / 180));

			// 当半径很小时，角度变化不会引起int型的x1/y1变化，因此加判断语句，避免重复画同一像素点 
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
  函数名称：
  功    能：按照给出的参数画一个扇形
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：当起始/结束角度差值为360的倍数时，不画两条边
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	//角度预处理
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
	if (angle_e != angle_b) { //整圆不画半径了
		hdc_line(point_x, point_y, x2, y2, thickness, RGB_value);
		hdc_line(point_x, point_y, x3, y3, thickness, RGB_value);
	}
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	//填充
	if (filled) {  //这里必须用demo中的base_line来填充，而不能用圆圈或者直径扫描，否则吃豆子的时候会有延迟感觉
		
		if (angle_e == angle_b) { //整圆
			left_sector(point_x, point_y, 0, 180, radius);
			right_sector(point_x, point_y, 180, 360, radius);
		}
		else if (angle_e > 180 && angle_b >=180&&angle_e>angle_b) //说明在左半边
			left_sector(point_x, point_y,  angle_b, angle_e, radius);
		else if(angle_e <= 180 && angle_b < 180 && angle_e>angle_b)//在右半边
			right_sector(point_x, point_y, angle_b, angle_e, radius);
		else {                                                                          //横跨左右，拆分
			if (angle_b > angle_e) {  //跨过0/360
				if(angle_b<180){//既要跨越360也要跨越180
					right_sector(point_x, point_y, angle_b, 180, radius);
					left_sector(point_x, point_y, 180, 360, radius);
					right_sector(point_x, point_y, 0, angle_e, radius);
				}
				else if (angle_e > 180) {//既要跨越360也要跨越180
					left_sector(point_x, point_y, angle_b, 360, radius);
					right_sector(point_x, point_y, 0, 180, radius);
					left_sector(point_x, point_y, 180, angle_e, radius);
				}
				else {  //单次跨越0
					left_sector(point_x, point_y, angle_b, 360, radius);
					right_sector(point_x, point_y, 0, angle_e, radius);
				}
			}
			else if (angle_b < 180 && angle_e>180) {//单次跨越180
				right_sector(point_x, point_y, angle_b, 180, radius);
				left_sector(point_x, point_y, 180, angle_e, radius);
			}
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个圆
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	hdc_arc(point_x,point_y,radius,0,360,thickness,RGB_value);

	//圆圈式填充,这种速度好像有点慢。。
	/*if (filled) {
		for (level = radius; level >= 0; level--) {
			for (angle = 0; angle <= 360; angle += 0.1) {
				//注意，系统的坐标轴，0°在圆的最下方
				x1 = point_x + (int)((level)*sin(angle * PI / 180));
				y1 = point_y - (int)((level)*cos(angle * PI / 180));

				//当半径很小时，角度变化不会引起int型的x1/y1变化，因此加判断语句，避免重复画同一像素点
				if (x1 != old_x1 || y1 != old_y1) {
					old_x1 = x1;
					old_y1 = y1;
					hdc_base_point(x1, y1);
					++count;
				}
			}
		}
	}*/
	//demo的直线填充发法
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
  函数名称：
  功    能：按照给出的参数画一个椭圆
  输入参数：const int point_x			：圆心的x
			const int point_y			：圆心的y
			const int radius_a			：平行于X轴的半径
			const int radius_b			：平行于Y轴的半径
			const int rotation_angles	：以圆心为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	//正椭圆采用参数方程画，旋转椭圆采用坐标系旋转的方式来画
	int x, y;
	int x_r, y_r;//旋转后的坐标
	for (double angle = 0; angle <= 360; angle+=0.3) {
		//x = point_x + radius_a * cos(angle / 180 * PI);
		//y = point_y + radius_b * sin(angle / 180 * PI);
		x = radius_a * cos(angle/180*PI);
		y = radius_b * sin(angle/180*PI);
		x_r = x * cos(rotation_angles * PI / 180) - y * sin(rotation_angles * PI / 180);//与正常坐标系旋转相反，因为这里的y轴是向下为正的
		y_r = y * cos(rotation_angles * PI / 180) + x * sin(rotation_angles * PI / 180);
		hdc_point(x_r+point_x, y_r+point_y, thickness, RGB_value);
	}
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	if (filled) {  //这里也按照旋转坐标系来填充，会非常容易，只要画出正坐标下的填充，加上坐标旋转即可
		int x_left, x_right;
		int x_left_r, x_right_r,j_left_r,j_right_r;//旋转后的坐标值
		for (double j =  - radius_b; j <= radius_b;j+=1) {
			//注意这里需要先旋转再与point圆心坐标相加
			x_left = -sqrt(radius_a*radius_a-j*j*radius_a*radius_a/(radius_b*radius_b));
			x_right = sqrt(radius_a * radius_a - j * j * radius_a * radius_a / (radius_b * radius_b));

			x_left_r = x_left * cos(rotation_angles * PI / 180) - j * sin(rotation_angles * PI / 180);  //左点
			j_left_r = j * cos(rotation_angles * PI / 180) + x_left * sin(rotation_angles * PI / 180);
			x_right_r = x_right * cos(rotation_angles * PI / 180) - j * sin(rotation_angles * PI / 180);//又点
			j_right_r= j * cos(rotation_angles * PI / 180) + x_right * sin(rotation_angles * PI / 180);

			
			x_left_r += point_x;//加上原坐标系的偏移值，即圆心从原点移到实际位置。
			x_right_r += point_x;
			j_left_r += point_y;
			j_right_r += point_y;
			
			
			//hdc_base_line(x_left_r,j_left_r,x_right_r,j_right_r);
			hdc_line(x_left_r, j_left_r, x_right_r, j_right_r, 3, RGB_value);
			//为了提升运行效率，不把j的自增量设的太小，因为只有在x轴附近时，很小的j变换会应发
		}
	}
}

#endif !HDC_SERIES_BY_TEACHER
