#pragma once

/* -----------------------------------------

	 本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ----------------------------------------- */
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
using namespace std;

/***题目允许的四个全局变量***/
extern int i;    //步数
extern int stack[3][15];//三个柱子上的盘子
extern int top[3];
extern int Time;

//汉诺塔基础函数
int menu();
void init();
void Clear();//一次运行结束后把全局变量处理一下
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

//画图函数
void Paint_1();//画柱子
void Paint_2(int, char&);//画饼子
void Paint_3(int, int, int, char&, char&, char&, int, bool);//画第一个盘子动画
void Game(int, int, char&, char&, char&, int[]);

void Quit();

