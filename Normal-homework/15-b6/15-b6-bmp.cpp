
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
		for (int i = 0; i < (int)pow(2, Bit); i++) {//�����ɫ��
			for (int j = 0; j < 4; j++) {
				rgb[i][j] = infile.get();
			}
		}
	}
	
	//��ÿ�����ص���ɫ
	int len = wid * hei * Bit / 8;//len����Ҫ��ȡ���ֽ���
	if ((wid * Bit) % 8)//ÿ�����ص�λ���������������
		len = ((wid * Bit / 8) + 1) * hei;//ÿ�ж�Ҫ���һ���ֽڣ���Ϊ���������С��
	//cout << len << endl;
	while ((len/hei) % 4) {  //bmpһ�в���4�ֽ��������Ჹ0
		len++;
	}
	wid_Byte = len / hei;  //wid_Byte��ÿ��ʵ�ʵ��ֽ���
	
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

int bitmap_image::height() const //����ͼƬ�ĸ߶�
{
	return hei;
}

unsigned int bitmap_image:: get_pixel(int row, int col) const //����ָ�����RGB��ɫ
{
	row = hei - row-1;//bmp���ȱ���������һ������
	int b=0, g=0, r=0,i;
	unsigned char x,y;//xȡ�������ڵ��Ǹ��ֽڵ�ֵ,y�ǵ�ǰ������ռ���֣�Ҳ���Ǽ�¼�˵�ɫ������ֵ��
	i = (row) * wid + col;//i�ǵڼ������ص�
	
	if (Bit == 1) {
		x = color[row*wid_Byte+col/8];
		y = (x & (unsigned char)pow(2, (7 - (col % 8)))) ? 1 : 0;
		//����ɫ�尴����ȡֵ
		r = (int)rgb[y][0];
		g = (int)rgb[y][1];
		b = (int)rgb[y][2];
	}
	else if (Bit == 4) {
		x = color[row * wid_Byte + col / 2];
		y = (col % 2) ? 0xf & x : ((0xf0 & x)>>4);//ȡһ���ֽ����/��4λ
		
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
		//����һ�в���4�ֽ�Ҫ��0�����һ�е�ʵ���ֽ������������ص������Ե�λ���ص���ռ�ֽ���
	}
	return r * 256 * 256 + g * 256 + b;
}