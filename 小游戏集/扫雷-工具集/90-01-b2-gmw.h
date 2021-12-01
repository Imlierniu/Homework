#pragma once
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include"../include/cmd_gmw_tools.h"
#include<ctime>
using namespace std;

int Select_Level();
void Quit(CONSOLE_GRAPHICS_INFO MyCGI);

void Set_zhadan(int z[][2], char*, int, int, int);
void Print_zhadan(char*, int, int);
void Add_zhadan(int coord[][2], char* zhadan, int a, int b, int x);
void Print_Graph_unknow(int, CONSOLE_GRAPHICS_INFO MyCGI,const BLOCK_DISPLAY_INFO bdi[],int,int);
void add(char* zhadan, int x, int y, int a, int b);
void Init(int);

int Is_Begin(char* zhadan, int a, int b, int num, int& X, int& Y);
void Dfs(char* zhadan, int X, int Y, int a, int b, int A[][50], int& n);
bool Open_Area_Graph(CONSOLE_GRAPHICS_INFO& MyCGI, const BLOCK_DISPLAY_INFO bdi[], int A[][50], char* zhadan, int X, int Y, int a, int b, int& n, int tag, int level);
