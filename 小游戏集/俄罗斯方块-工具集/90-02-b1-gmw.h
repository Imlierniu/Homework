#pragma once
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include"../include/cmd_gmw_tools.h"
#include<ctime>
using namespace std;



int Init(CONSOLE_GRAPHICS_INFO& MyCGI,int& a, int& b,int D[40][5][5]);//选择row，col
void Show_Map(CONSOLE_GRAPHICS_INFO& MyCGI, int, int);//画棋盘
void Quit(int, int);//退出

void Init_6(CONSOLE_GRAPHICS_INFO& MyCGI, int& a, int& b, int Di[40][5][5]);//游戏程序


int get_next_num(const bool new_seed = false, const unsigned int seed = 0);//随机数函数
void Print_Digital(CONSOLE_GRAPHICS_INFO& MyCGI,int n, int L, int X, int Y, int D[40][5][5]);

bool Can_Move_Dy(int n, int L, int X, int Y, int D[40][5][5], int a, int b, int** M);
bool Left_Move(CONSOLE_GRAPHICS_INFO& MyCGI,int n, int L, int& X, int& Y, int D[40][5][5]);
bool Right_Move(CONSOLE_GRAPHICS_INFO& MyCGI,int n, int L, int& X, int& Y, int D[40][5][5]);
bool Down_Move(CONSOLE_GRAPHICS_INFO& MyCGI,int n, int L, int& X, int& Y, int D[40][5][5]);
bool Roll_Move(CONSOLE_GRAPHICS_INFO& MyCGI,int n, int L, int& X, int& Y, int D[40][5][5]);

bool Map_Record_score(CONSOLE_GRAPHICS_INFO& MyCGI, int** M, int a, int b, int D[40][5][5], int x, int L, int X, int Y, int& score);
void Map_Clear(CONSOLE_GRAPHICS_INFO& MyCGI, int a, int b, int** M, int I);
void Map_Print(CONSOLE_GRAPHICS_INFO& MyCGI, int a, int b, int** M);