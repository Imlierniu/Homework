#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
#include<cmath>

using namespace std;
#define PI 3.1415926
static void flower(int point_x,int point_y)
{
	//õ����

	int RGB_value=RGB(190,183,255);
	int x, y,a=100,n=8;
	for (double cta = 0; cta <= 360; cta+=0.01) {
		x= a * sin(n * cta*PI/180) * cos(cta*PI/180)+point_x;
		y= a * sin(n * cta*PI/180) * sin(cta*PI/180)+point_y;
		hdc_point(x, y, 5, RGB_value);
	}
}
//���ڸо�õ����̫���ף�����ĳɷ������ߣ����������ڳ��ֵ�һ�鹤�߻����ģ�Сʱ���ϲ����ģ����ð壩��
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
	/********��ͼ������һ�Դ���ڳ��ֺ�С����������϶��ɣ�С�������кܶ�ʵĲ�ף�ѡ��һ�����ѱʼ���룬Ȼ�����Ի������ˡ���
	�������£�
		����ְ뾶R
		С���ְ뾶r
		�ʿ׵�С���ֵľ���t
		�����Ƕ�seta	
	************************************************************/
	hdc_cls();
	cout << "��������" << endl;
	double T;//���ڣ�ÿ�ֲ��������ڲ���ͬ
	T = r/Zuidagongyueshu(int(R), int(r));
	int A_x, A_y;
	for (double seta = 0; seta <= 360*T; seta+=0.05) {//��Ϊ�������������T�����Ų����仯���仯��
		/*˵�������������������ʵ��(r)����R��r�����Լ��������������Լ����1����ô�����빫תrȦ*/
		
		A_x = (R - r) * cos(seta * PI / 180) + cos((R / r) * seta * PI / 180) * t;
		A_y = (R - r) * sin(seta * PI / 180) - sin((R / r) * seta * PI / 180) * t;
		hdc_point(A_x+point_x, A_y+point_y, thickness, RGB_value);
	}

}
