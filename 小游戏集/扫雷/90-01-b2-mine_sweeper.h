#pragma once
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include<ctime>
using namespace std;

//���溯��
int menu();
int Select_Level();
void Quit();

//base����
void Set_zhadan( int z[][2], char*,int , int , int );
void Print_zhadan( char*, int, int);
void Add_zhadan(int coord[][2],  char* zhadan, int a, int b, int x);
void Init(int,int);//����������ʹ��
void Print_unknow(int a, int b);//��ʾδ֪
bool Open_Area(int [][50],char* zhadan, int X, int Y, int a, int b,int&n,int tag,int num);
void Dfs(char*zhadan, int X, int Y, int a, int b, int A[][50],int&n);
void Open_Show(char* zhadan, int a, int b, int A[][50],int,int tag,int num);

int Is_Begin(char*,int,int,int,int&,int&);//�Ƿ��һ������ĵط�����ը���������ը����ˢ���ڲ����鱣֤������سɺ�
int Is_cin_right(int, int, int,int&,int&);//�ж���������Ϸ��� ,return -1����;�˳���0����ʧ�ܣ�1��ojbk
int Is_cin_right_4(int a, int b, int num, int& X, int& Y,int& tag);//�����ӱ��/ȡ����ǹ���
void Show_4_info();

//αͼ�κ���
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