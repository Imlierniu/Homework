/* 1752846 边泽轩 车辆工程(汽车) */

#pragma once
#include<iostream>
using namespace std;

/* 根据需要加入自己的定义 */

class bitmap_image
{
protected:
    /* 根据需要加入自己的定义 */
    int wid;    //图片像素点宽度
    int hei;
    int Bit;    //1 4(16色) 8(256色) 24位
    int wid_Byte;   //
    unsigned char head[54];  //读入文件头信息，
    unsigned char rgb[256][4]; //调色板信息
    /*调色板适用于非真彩bmp，也就是低于24位的，比如说8位。调色板使得储存空间可以减小，比如说8位只有256种颜色，则只需要256*4的
    空间来储存颜色索引信息（rgb分别各占1Bit，为了对齐，最后一字节是0），这样后面的每个像素只需要8位（1字节）储存索引值即可。
     
    然而当采用24位真彩时，显然采用索引的方式并不节约空间，因为可能颜色数量量级高于像素点数量级（因为24位RGB组合有256^3种
    ）。。还是老老实实每个像素点分别用三个字节表示R、G、B。
    */
    unsigned char* color; //记录每个像素的数据信息

public:
    int width() const;	//返回图片的宽度
    int height() const; //返回图片的高度
    unsigned int get_pixel(int row, int col) const; //返回指定点的RGB颜色

    /* 根据需要加入自己的定义 */
    bitmap_image();
    bitmap_image(const char*);   //打开指定的图片
    ~bitmap_image();
    bool Read_head(const char*);
};

