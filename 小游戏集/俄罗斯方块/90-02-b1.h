#pragma once
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
using namespace std;

int menu();
void Quit(int,int);

//��Ϸ���ܺ���
int Init(int &,int &);//�˵�1
void Init_2(int ,int, int D[40][5][5]);//�˵�2
void Init_3(int a, int b, int D[40][5][5]);//�˵�3
void Init_4(int a, int b, int D[40][5][5]);//�˵�4
void Init_5(int a, int b, int D[40][5][5]);//�˵�5
void Init_6(int a, int b, int Di[40][5][5],int god);
bool Map_Record(int**M, int a, int b, int D[40][5][5], int x, int L, int X, int Y);//��¼����صķ���
bool Map_Record_score(int** M, int a, int b, int D[40][5][5], int x, int L, int X, int Y,int& score);//�����˷�������
int get_next_num(const bool new_seed = false, const unsigned int seed = 0);//���������
void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime, int x, int L, int X, int Y, int a, int b, int Di[40][5][5], int** Map);//��ʱ���ص�����

//�ж��ܷ�����ƶ���ִ�в���
bool Left_Move(int n, int L, int& X, int& Y, int D[40][5][5]);
bool Right_Move(int n, int L, int& X, int& Y, int D[40][5][5]);
bool Down_Move(int n, int L, int& X, int& Y, int D[40][5][5]);
bool Roll_Move(int n, int L, int& X, int& Y, int D[40][5][5]);
bool Can_Move(int n, int L, int X, int Y, int D[40][5][5],int a,int b);
bool Can_Move_Dy(int n, int L, int X, int Y, int D[40][5][5], int a, int b, int** M);//���ӵ�ͼ��¼


//��ͼ����
void Show_Map(int a, int b);     //��ʾ��Ϸ�߿�
void Draw_Line(int b,int);           //��ɫ
void Show_Block_Base(int X, int Y); //��ָ�����괦����һ������
void Print_Digital(int n, int L, int X, int Y,int D[40][5][5]);//����ĳ�����ֵ�ĳ����̬
void Erase_Block_Base(int X, int Y);//Ϊ�������ֺ������ã�����ĳ����
void Erase_Digital(int, int,int,int,int[40][5][5]);//��������
void Map_Clear(int a, int b, int** M, int I);//����ĳһ��
void Map_Print(int a, int b, int** M);//������ĳһ�к�ˢ����ʾ
void Show_Block(int,int,int,int D[40][5][5]);//����ĳ�����ֵ�������̬���˵�2
void Show_Roll_Block(int n, int X, int Y,int D[40][5][5]);//���м仭һ�����ֲ�����ͨ��������ת�����˵�3
