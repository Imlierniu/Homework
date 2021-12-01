#pragma once
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include<ctime>
using namespace std;

//界面函数
int menu();
int Select_Level();
void Quit();

//base函数
void Set_zhadan( int z[][2], char*,int , int , int );
void Print_zhadan( char*, int, int);
void Add_zhadan(int coord[][2],  char* zhadan, int a, int b, int x);
void Init(int,int);//方便主函数使用
void Print_unknow(int a, int b);//显示未知
bool Open_Area(int [][50],char* zhadan, int X, int Y, int a, int b,int&n,int tag,int num);
void Dfs(char*zhadan, int X, int Y, int a, int b, int A[][50],int&n);
void Open_Show(char* zhadan, int a, int b, int A[][50],int,int tag,int num);

int Is_Begin(char*,int,int,int,int&,int&);//是否第一次输入的地方不是炸弹，如果是炸弹，刷新内部数组保证不会落地成盒
int Is_cin_right(int, int, int,int&,int&);//判断输入坐标合法性 ,return -1：中途退出，0：打开失败，1：ojbk
int Is_cin_right_4(int a, int b, int num, int& X, int& Y,int& tag);//新增加标记/取消标记功能
void Show_4_info();

//伪图形函数
void Init2(int level, int num);
void Print_Graph_Base(int);
void Graph_1(int);
void Graph_2(int);
void Graph_3(int);
void Graph_1_array(char zhadan[][9]);
void Graph_2_array(char zhadan[][16]);
void Graph_3_array(char zhadan[][30]);
int Show_Mouse(int,int,char*,int&,int&,int&);
void Print_Graph_unknow(int);
void Is_Click_Begin(int level, int num, char* zhandan,int& X,int& Y);
void Open_Show_Graph(char*zhadan, int a, int b, int A[][50], int n, int tag, int num,int level);
bool Open_Area_Graph(int A[][50], char* zhadan, int X, int Y, int a, int b, int& n, int tag, int num,int level);