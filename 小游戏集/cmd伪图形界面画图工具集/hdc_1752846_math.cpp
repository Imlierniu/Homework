#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
#include<cmath>

using namespace std;
#define PI 3.1415926
static void flower(int point_x,int point_y)
{
	//玫瑰线

	int RGB_value=RGB(190,183,255);
	int x, y,a=100,n=8;
	for (double cta = 0; cta <= 360; cta+=0.01) {
		x= a * sin(n * cta*PI/180) * cos(cta*PI/180)+point_x;
		y= a * sin(n * cta*PI/180) * sin(cta*PI/180)+point_y;
		hdc_point(x, y, 5, RGB_value);
	}
}
//由于感觉玫瑰线太容易，这里改成繁花曲线，用类似于内齿轮的一组工具画出的，小时候很喜欢玩的（龟兔板）。
static int Zuidagongyueshu(int a, int b) 
{
	int c;
	while (1) {
		c = a % b;
		if (!c)
			return b;
		else {
			a = b;
			b = c;
		}
	}
}

void hdc_draw_Mathematical_curve_1752846(const double R, const double r, const int t, const int point_x, const int point_y, const int thickness, const int RGB_value)
{
	/********画图工具由一对大的内齿轮和小的外齿轮啮合而成，小齿轮上有很多笔的插孔，选择一个洞把笔尖插入，然后无脑画就行了。。
	参数如下：
		大齿轮半径R
		小齿轮半径r
		笔孔到小齿轮的距离t
		参数角度seta	
	************************************************************/
	hdc_cls();
	cout << "繁花曲线" << endl;
	double T;//周期，每种参数的周期不相同
	T = r/Zuidagongyueshu(int(R), int(r));
	int A_x, A_y;
	for (double seta = 0; seta <= 360*T; seta+=0.05) {//因为这个东西的周期T是随着参数变化而变化的
		/*说明，这个东西的周期其实是(r)除以R和r的最大公约数，如果二者最大公约数是1，那么他必须公转r圈*/
		
		A_x = (R - r) * cos(seta * PI / 180) + cos((R / r) * seta * PI / 180) * t;
		A_y = (R - r) * sin(seta * PI / 180) - sin((R / r) * seta * PI / 180) * t;
		hdc_point(A_x+point_x, A_y+point_y, thickness, RGB_value);
	}

}
