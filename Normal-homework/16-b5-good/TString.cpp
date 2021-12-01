

/* 允许添加需要的头文件、宏定义等 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "TString.h"

using namespace std;

struct node {
	char a;
	node* next;
};
/* 给出 TString 类的所有成员函数的体外实现 */
TString::TString()
{
	content = 0;
	len = 0;
	len_buf = 0;
}


TString::~TString()
{
	delete[]content;
	content = nullptr;
	len = 0;
}

const char* TString::c_str()const
{
	return content;
}


TString& TString::operator+=(char* s)//ceshi
{
	if (s) {
		
			
	}
	
	//sstre << s;
	//len+=strlen(s);
	
	/*if (s) {
		v.pop_back();
		for (int i = 0; s[i] != '\0'; i++) {
			v.push_back(s[i]);
			len++;
		}
		v.push_back('\0');
	}*/

	return *this;
}



bool TString::operator!=(const char* s)
{
	if ((!s || strlen(s) == 0) && (!content || len == 0))
		return 0;
	if ((!s || strlen(s) == 0) || !content || len == 0)
		return 1;
	return strcmp(content, s) != 0;
}

/****************length()***************************/
int TString::length()const
{
	return len;
}

int TStringLen(const TString& a)
{
	return a.length();
}

/****************[ ]*********************/

/* 如果有需要的其它全局函数的实现，可以写于此处 */

char* strcat(char* des, char* tar)
{
	static char* last_begin = NULL;
	static char* last_end = NULL;
	if (des == last_begin) {
		while (*tar) {
			*last_end++ = *tar++;
		}
		*last_end = '\0';
	}
	else {
		char* p = des;
		while (*des) {
			des++;
		}
		while (*tar) {
			*des++ = *tar++;
		}
		*des = 0;

		if (des - p >= 32768) {
			last_begin = p;
			last_end = des;
		}
	}
	return last_begin;
	
}