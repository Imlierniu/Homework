/* 1752846 ������ ��������(����) */

#pragma once
#include<iostream>
using namespace std;

/* ������Ҫ�����Լ��Ķ��� */

class bitmap_image
{
protected:
    /* ������Ҫ�����Լ��Ķ��� */
    int wid;    //ͼƬ���ص���
    int hei;
    int Bit;    //1 4(16ɫ) 8(256ɫ) 24λ
    int wid_Byte;   //
    unsigned char head[54];  //�����ļ�ͷ��Ϣ��
    unsigned char rgb[256][4]; //��ɫ����Ϣ
    /*��ɫ�������ڷ����bmp��Ҳ���ǵ���24λ�ģ�����˵8λ����ɫ��ʹ�ô���ռ���Լ�С������˵8λֻ��256����ɫ����ֻ��Ҫ256*4��
    �ռ���������ɫ������Ϣ��rgb�ֱ��ռ1Bit��Ϊ�˶��룬���һ�ֽ���0�������������ÿ������ֻ��Ҫ8λ��1�ֽڣ���������ֵ���ɡ�
     
    Ȼ��������24λ���ʱ����Ȼ���������ķ�ʽ������Լ�ռ䣬��Ϊ������ɫ���������������ص�����������Ϊ24λRGB�����256^3��
    ��������������ʵʵÿ�����ص�ֱ��������ֽڱ�ʾR��G��B��
    */
    unsigned char* color; //��¼ÿ�����ص�������Ϣ

public:
    int width() const;	//����ͼƬ�Ŀ��
    int height() const; //����ͼƬ�ĸ߶�
    unsigned int get_pixel(int row, int col) const; //����ָ�����RGB��ɫ

    /* ������Ҫ�����Լ��Ķ��� */
    bitmap_image();
    bitmap_image(const char*);   //��ָ����ͼƬ
    ~bitmap_image();
    bool Read_head(const char*);
};

