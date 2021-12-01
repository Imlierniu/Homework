#pragma once
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
using namespace std;

int menu();
void Quit(int,int);

//游戏功能函数
int Init(int &,int &);//菜单1
void Init_2(int ,int, int D[40][5][5]);//菜单2
void Init_3(int a, int b, int D[40][5][5]);//菜单3
void Init_4(int a, int b, int D[40][5][5]);//菜单4
void Init_5(int a, int b, int D[40][5][5]);//菜单5
void Init_6(int a, int b, int Di[40][5][5],int god);
bool Map_Record(int**M, int a, int b, int D[40][5][5], int x, int L, int X, int Y);//记录已落地的方块
bool Map_Record_score(int** M, int a, int b, int D[40][5][5], int x, int L, int X, int Y,int& score);//增加了分数功能
int get_next_num(const bool new_seed = false, const unsigned int seed = 0);//随机数函数
void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime, int x, int L, int X, int Y, int a, int b, int Di[40][5][5], int** Map);//定时器回调函数

//判断能否进行移动并执行操作
bool Left_Move(int n, int L, int& X, int& Y, int D[40][5][5]);
bool Right_Move(int n, int L, int& X, int& Y, int D[40][5][5]);
bool Down_Move(int n, int L, int& X, int& Y, int D[40][5][5]);
bool Roll_Move(int n, int L, int& X, int& Y, int D[40][5][5]);
bool Can_Move(int n, int L, int X, int Y, int D[40][5][5],int a,int b);
bool Can_Move_Dy(int n, int L, int X, int Y, int D[40][5][5], int a, int b, int** M);//增加地图记录


//画图函数
void Show_Map(int a, int b);     //显示游戏边框
void Draw_Line(int b,int);           //底色
void Show_Block_Base(int X, int Y); //在指定坐标处画出一个方块
void Print_Digital(int n, int L, int X, int Y,int D[40][5][5]);//画出某个数字的某种形态
void Erase_Block_Base(int X, int Y);//为擦除数字函数调用，擦除某个块
void Erase_Digital(int, int,int,int,int[40][5][5]);//擦除数字
void Map_Clear(int a, int b, int** M, int I);//消除某一行
void Map_Print(int a, int b, int** M);//消除完某一行后刷新显示
void Show_Block(int,int,int,int D[40][5][5]);//画出某个数字的三种形态，菜单2
void Show_Roll_Block(int n, int X, int Y,int D[40][5][5]);//在中间画一个数字并允许通过↑键旋转它，菜单3
