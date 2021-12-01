#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
#include<cmath>
using namespace std;
#define PI 3.1415926

#define COLOR_HAIR RGB(0,0,0)
//#define COLOR_FACE RGB(249,216,177)
#define COLOR_FACE RGB(251,194,147)
#define COLOR_WHITE RGB(255,255,255)
#define COLOR_SWEATER RGB(252,115,43)
#define COLOR_SWEATER_FACE RGB(0,168,243)

static void draw_map(const int base_x, const int base_y)
{
	
	hdc_square(base_x-300,base_y-300,600,0,1,1,COLOR_WHITE);
}
static void draw_hair(const int base_x, const int base_y)
{
	hdc_sector(base_x, base_y, 225, -35,180,1, 2, COLOR_HAIR);
	hdc_ellipse(base_x - 140, base_y + 160, 125, 75, 45, 1, 1, COLOR_HAIR);
	hdc_rectangle(base_x - 150, base_y + 50, 380, 200, 0, 1, 1, COLOR_HAIR);
	hdc_rectangle(base_x - 120, base_y - 225, 120, 50, 0, 1, 1, COLOR_HAIR);
	hdc_sector(base_x-165,base_y-200,75,90,150,1,1,COLOR_HAIR);
	hdc_sector(base_x-100, base_y-225, 50, -180, -90, 1, 2, COLOR_HAIR);
	hdc_sector(base_x, base_y + 60, 235, 70, 140, 1, 1, COLOR_HAIR);
	hdc_sector(base_x + 126, base_y - 204, 30, 195, 250, 1, 1, COLOR_HAIR);
	hdc_circle(base_x + 75, base_y - 184, 30,1, 1, COLOR_HAIR);
	hdc_ellipse(base_x + 250, base_y + 140, 40, 25, -75, 1, 1, COLOR_WHITE);

	hdc_sector(base_x - 200, base_y +31, 40, 150, 200, 1, 2, COLOR_HAIR);//±Ç×ÓÏÂÃæµÄºÚÉ«
	
	
}
static void draw_face(const int base_x, const int base_y) 
{
	hdc_ellipse(base_x - 25, base_y - 100, 125, 75, 0, 1, 1, COLOR_FACE);
	hdc_ellipse(base_x , base_y - 100, 125, 80, 0, 1, 1, COLOR_FACE);
	hdc_circle(base_x, base_y - 25, 100, 1, 1, COLOR_FACE);
	hdc_circle(base_x+30, base_y - 60, 100, 1, 1, COLOR_FACE);
	hdc_circle(base_x + 50, base_y - 60, 84, 1, 1, COLOR_FACE);
	hdc_circle(base_x + 5, base_y - 50, 115, 1, 1, COLOR_FACE);
	hdc_circle(base_x -150, base_y +15, 56, 1, 1, COLOR_FACE);
	hdc_rectangle(base_x - 200, base_y , 250, 60, 0, 1, 1, COLOR_FACE);
	hdc_arc(base_x - 150, base_y + 15, 56, 180,80,10, COLOR_HAIR);//±Ç×ÓÂÖÀª
	hdc_circle(base_x - 180, base_y + 120, 65, 1, 1, COLOR_HAIR);
	hdc_rectangle(base_x - 200, base_y + 60, 250, 90, 0, 1, 1, COLOR_HAIR);
	hdc_ellipse(base_x - 30, base_y + 60, 25, 15, 70, 1, 1, COLOR_HAIR);

	hdc_ellipse(base_x - 172, base_y + 10, 35, 16,-70,1,1,RGB(255,244,232));//±ÇÍ·
	
	
	
	hdc_circle(base_x +20, base_y , 68, 1, 1, COLOR_FACE);
	hdc_ellipse(base_x - 18, base_y + 60, 35, 10, 45, 1, 1, COLOR_HAIR);
	hdc_circle(base_x - 45, base_y+60, 15, 1, 1, COLOR_HAIR);
	hdc_circle(base_x + -62, base_y+46, 13, 1, 1, COLOR_FACE);

	hdc_arc(base_x - 27, base_y +59, 66, 270, 45, 10, COLOR_HAIR);//Á³¼ÕÂÖÀª
	hdc_sector(base_x - 200, base_y + 31, 40, 150, 200, 1, 2, COLOR_HAIR);//±Ç×ÓÏÂÃæµÄºÚÉ«
}

static void draw_noise(int base_x,int base_y)
{
	hdc_arc(base_x - 100, base_y -2, 100, 150, 213, 8, COLOR_WHITE);//ÑÀ³Ý
	hdc_arc(base_x - 100, base_y - 2, 108, 147, 213, 8, COLOR_WHITE);//ÑÀ³Ý
	hdc_arc(base_x - 100, base_y - 2, 116, 145, 215, 8, COLOR_WHITE);//ÑÀ³Ý
	hdc_circle(base_x -162, base_y + 84, 12, 1, 1, COLOR_WHITE);//ÉÏÑÀ×ó
	hdc_circle(base_x - 44, base_y + 90, 11, 1, 1, COLOR_WHITE);//ÉÏÑÀÓÒ

	hdc_arc(base_x - 100, base_y - 2, 140, 149, 212, 8, COLOR_WHITE);//ÑÀ³Ý
	hdc_arc(base_x - 100, base_y - 2, 148, 150, 211, 8, COLOR_WHITE);//ÑÀ³Ý
	hdc_circle(base_x - 172, base_y + 84+36, 8, 1, 1, COLOR_WHITE);//ÏÂÑÀ×ó
	hdc_circle(base_x - 32, base_y + 90+32, 8, 1, 1, COLOR_WHITE);//ÏÂÑÀÓÒ
	hdc_line(base_x-162, base_y+148, base_x-44, base_y+148, 2, COLOR_HAIR);

	hdc_line(base_x - 100, base_y + 80, base_x - 100, base_y + 160, 16, COLOR_HAIR);
	hdc_line(base_x - 116, base_y + 92, base_x - 116, base_y + 118, 18, RGB(255,242,0));//´ó½ðÑÀ
	//hdc_point(base_x-114,base_y+105,20,RGB(255,242,0));

	hdc_line(base_x - 66, base_y + 80, base_x - 66, base_y + 160, 16, COLOR_HAIR);
	hdc_line(base_x - 134, base_y + 80, base_x - 134, base_y + 160, 16, COLOR_HAIR);
	

}

static void draw_eyes(const int base_x, const int base_y)
{
	hdc_circle(base_x - 75, base_y - 48, 28,1,10, COLOR_HAIR);
	hdc_ellipse(base_x - 57, base_y - 54, 55, 32, -65, 1, 8, COLOR_WHITE);
	
	hdc_ellipse(base_x - 55, base_y - 54, 55, 32, -65, 0, 10, COLOR_HAIR);
	hdc_circle(base_x - 75, base_y - 48, 21, COLOR_WHITE);
	
	
	hdc_circle(base_x - 75, base_y - 48, 15, 1, 1, COLOR_HAIR);//ÑÛÖé×Ó
	hdc_point(base_x-75,base_y-48,38,COLOR_HAIR);

	//×óÑÛ
	hdc_sector(base_x - 123, base_y - 67, 52, 230, 275, 1, 1, COLOR_HAIR);
	hdc_ellipse(base_x - 146, base_y - 67, 39, 26, 70, 1, 10, COLOR_WHITE);
	//hdc_ellipse(base_x - 143, base_y - 67, 40, 25, 85, 1, 8, COLOR_HAIR);
	hdc_ellipse(base_x - 146, base_y - 67, 39, 26, 70, 0, 10, COLOR_HAIR);


	hdc_arc(base_x + 185,base_y + 100, 322,293,323, 8, COLOR_HAIR);//ÓÒÃ¼Ã«
	hdc_arc(base_x + 185, base_y + 100, 330, 293, 323, 10, COLOR_HAIR);//ÓÒÃ¼Ã«
	hdc_line(base_x-5, base_y - 166, base_x + 42, base_y - 105, 18, COLOR_HAIR);
	hdc_point(base_x - 5, base_y - 164 ,18, COLOR_HAIR);
	hdc_rectangle(base_x, base_y - 152, 70, 10, 50, 1, 1, COLOR_FACE);

	hdc_arc(base_x -240, base_y , 144, 34, 74, 10, COLOR_HAIR);//Ã¼Ã«

	hdc_circle(base_x - 162, base_y - 120, 4, 1, 1, COLOR_HAIR);//×óÃ¼Ã«¼â

	hdc_arc(base_x - 110, base_y - 110, 40,270,330, 10, COLOR_HAIR);//¶îÍ·
	
	//¶ú¶ä
	hdc_ellipse(base_x + 165, base_y + 28, 55, 35, 90, 1, 1, COLOR_FACE);
	hdc_rectangle(base_x + 134, base_y + 28, 20, 55, 0, 1, 1, COLOR_FACE);
	hdc_arc(base_x + 135, base_y, 25, 120, 200, 10, COLOR_HAIR);

}

static void draw_sweater(int base_x,int base_y)
{
	hdc_ellipse(base_x + 185, base_y + 230, 75, 40, -60, 1, 1, COLOR_SWEATER);
	hdc_ellipse(base_x + 185, base_y + 230, 75, 40, -69, 0, 8, COLOR_HAIR);
	hdc_ellipse(base_x - 35, base_y + 260, 35, 20, 90, 1, 8,COLOR_SWEATER_FACE);

	hdc_ellipse(base_x + 15, base_y + 260, 35, 18, 98, 1, 8, COLOR_SWEATER_FACE);//ÒÂÁìÓÒ
	hdc_ellipse(base_x +60, base_y + 263, 35, 16, 93, 1, 8, COLOR_SWEATER_FACE);
	hdc_ellipse(base_x +104, base_y + 258, 35, 14, 80, 1, 8, COLOR_SWEATER_FACE);
	hdc_ellipse(base_x +138, base_y + 250, 35, 20, 90, 1, 8, COLOR_SWEATER_FACE);

	hdc_ellipse(base_x - 85, base_y + 250, 35, 12, 80, 1, 8, COLOR_SWEATER);//ÒÂÁì×ó
	hdc_ellipse(base_x - 129, base_y + 250, 35, 17, 99, 1, 8, COLOR_SWEATER);
	hdc_ellipse(base_x - 175, base_y + 250, 35, 22, 110, 1, 8, COLOR_SWEATER);
	hdc_ellipse(base_x - 175, base_y + 250, 35, 22, 110, 0, 8, COLOR_HAIR);

	hdc_ellipse(base_x + 185, base_y + 230, 75, 40, -60, 1, 1, COLOR_SWEATER);
	hdc_ellipse(base_x + 185, base_y + 230, 75, 40, -69, 0, 8, COLOR_HAIR);

	hdc_rectangle(base_x - 300, base_y + 250, 600, 55, 0, 1, 1, COLOR_WHITE);
	
}
void hdc_draw_cartoon_1752846(const int base_x, const int base_y)
{
	hdc_cls();

	draw_map(base_x, base_y);
	draw_hair(base_x, base_y);
	draw_face(base_x, base_y);
	draw_noise(base_x, base_y);
	draw_eyes(base_x, base_y);
	draw_sweater(base_x,base_y);
	cout << "¿ñÒ°ÀÏºº" << endl;


	
	getchar();
	getchar();
}