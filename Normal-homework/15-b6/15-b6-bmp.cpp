
#include"15-b6-bmp.h"
#include <fstream>
#include<cstdlib>
#include<cmath>
bitmap_image::bitmap_image()
{
	wid = 0;
	hei = 0;
	Bit = 0;
}

bitmap_image::bitmap_image(const char*filename)//
{
	wid = 0;
	hei = 0;
	Read_head(filename);
}

bitmap_image::~bitmap_image()
{
	delete []color;
}

bool bitmap_image::Read_head(const char*filename)
{
	ifstream infile;
	infile.open(filename, ios::in | ios::binary);
	if (!infile.is_open()) {
		cout << "ReadFileError!" << endl;
		return 0;
	}
	for (int i = 0; i < 54 && !infile.eof(); i++) {
		head[i] = infile.get();
	}
	Bit = head[28];
	for (int i = 0; i < 4; i++) {
		wid += head[18 + i] * (int)pow(256, i);
		hei += head[22 + i] * (int)pow(256, i);
	}
	if (Bit != 24) {
		for (int i = 0; i < (int)pow(2, Bit); i++) {//读入调色板
			for (int j = 0; j < 4; j++) {
				rgb[i][j] = infile.get();
			}
		}
	}
	
	//读每个像素点颜色
	int len = wid * hei * Bit / 8;//len是需要读取的字节数
	if ((wid * Bit) % 8)//每行像素点位奇数的情况。。。
		len = ((wid * Bit / 8) + 1) * hei;//每行都要多读一个字节，因为整除会舍掉小数
	//cout << len << endl;
	while ((len/hei) % 4) {  //bmp一行不是4字节整数倍会补0
		len++;
	}
	wid_Byte = len / hei;  //wid_Byte是每行实际的字节数
	
	color = new unsigned char[len];
	for (int i = 0; i < len; i++) {
		color[i] = infile.get();
	}
	infile.close();
	
	return 1;
}

int bitmap_image::width() const
{
	return wid;
}

int bitmap_image::height() const //返回图片的高度
{
	return hei;
}

unsigned int bitmap_image:: get_pixel(int row, int col) const //返回指定点的RGB颜色
{
	row = hei - row-1;//bmp最先保存的是最后一行数据
	int b=0, g=0, r=0,i;
	unsigned char x,y;//x取数据所在的那个字节的值,y是当前像素所占部分（也就是记录了调色板索引值）
	i = (row) * wid + col;//i是第几个像素点
	
	if (Bit == 1) {
		x = color[row*wid_Byte+col/8];
		y = (x & (unsigned char)pow(2, (7 - (col % 8)))) ? 1 : 0;
		//到调色板按索引取值
		r = (int)rgb[y][0];
		g = (int)rgb[y][1];
		b = (int)rgb[y][2];
	}
	else if (Bit == 4) {
		x = color[row * wid_Byte + col / 2];
		y = (col % 2) ? 0xf & x : ((0xf0 & x)>>4);//取一个字节里高/低4位
		
		r = (int)rgb[y][0];
		g = (int)rgb[y][1];
		b = (int)rgb[y][2];
	}
	else if (Bit == 8) {
		x = color[i+ (wid_Byte - wid * Bit / 8) * row];
		y = x;
		r = (int)rgb[y][0];
		g = (int)rgb[y][1];
		b = (int)rgb[y][2];
	}
	else if (Bit == 24) {
		r = (int)color[i*3+0+ (wid_Byte - wid * Bit / 8) * row];
		g = (int)color[i*3+1+ (wid_Byte - wid * Bit / 8) * row];
		b = (int)color[i*3+2+ (wid_Byte - wid * Bit / 8) * row];
		//由于一行不足4字节要补0，因此一行的实际字节数并不是像素点数乘以单位像素点所占字节数
	}
	return r * 256 * 256 + g * 256 + b;
}