#pragma once
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include"../include/cmd_gmw_tools.h"
#include<ctime>
using namespace std;


void menu(int&, int&);
void Game(int row, int col);
int get_next_num(int max=3,const bool new_seed = false, const unsigned int seed = 0);
void Quit(int, int, CONSOLE_GRAPHICS_INFO& );
void Show_Begin(CONSOLE_GRAPHICS_INFO& MyCGI, const BLOCK_DISPLAY_INFO bdi[], int** Map,int row, int col);
void Mouse_operation(CONSOLE_GRAPHICS_INFO& MyCGI, const BLOCK_DISPLAY_INFO bdi[], const BLOCK_DISPLAY_INFO bdi_h[], int** Map,int,int);
void Lighten_Block(CONSOLE_GRAPHICS_INFO& MyCGI, const BLOCK_DISPLAY_INFO bdi[], const BLOCK_DISPLAY_INFO bdi_h[], int mrow, int mcol, int** Map, int a, int b,int N,int A[10][10],int tag,int&,int&max);//tag=0µãÁÁ£¬1´ò¿ª
void Dfs(CONSOLE_GRAPHICS_INFO& MyCGI, const BLOCK_DISPLAY_INFO bdi[], const BLOCK_DISPLAY_INFO bdi_h[], int** Map, int mrow, int mcol, int a, int b, int N,int A[10][10],int tag,int&);

