#pragma once

/* -----------------------------------------

	 ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ----------------------------------------- */
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
using namespace std;

/***��Ŀ������ĸ�ȫ�ֱ���***/
extern int i;    //����
extern int stack[3][15];//���������ϵ�����
extern int top[3];
extern int Time;

//��ŵ����������
int menu();
void init();
void Clear();//һ�����н������ȫ�ֱ�������һ��
int pop(int);
void push(int, int);
void print(int, int);
void set(char&, int&);
void show_3(int&, int&, char, char, char);
void show_4(int&, char, char, char);
void move(int&, int, int, int&, char, char, char);
void work(int&, int&, int&, int&, char&, char&, char&);
void Change_speed(int&);
void init(int&, char&, char&, char&, int[]);

//��ͼ����
void Paint_1();//������
void Paint_2(int, char&);//������
void Paint_3(int, int, int, char&, char&, char&, int, bool);//����һ�����Ӷ���
void Game(int, int, char&, char&, char&, int[]);

void Quit();

