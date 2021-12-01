
/* 允许添加需要的头文件、宏定义等 */
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "16-b5.h"
using namespace std;

/* 给出 TString 类的所有成员函数的体外实现 */
TString::TString()
{
	content = nullptr;
	len = 0;
}

TString::TString(const char*s)
{
	if (s != nullptr) {
		len = strlen(s);
		content = new char[len + 1];
		strcpy(content, s);
		content[len] = '\0';
	}
	else {
		content = nullptr;
		len = 0;
	}
}

/*TString::TString(char* s)
{
	if (s != nullptr) {
		len = strlen(s);
		content = new char[len + 1];
		strcpy(content, s);
		content[len] = '\0';
	}
}*/

TString::TString(const TString&x)
{
	if (x.len) {
		len = x.len;
		content = new char[len + 1];
		strcpy(content, x.content);
	}
	else {
		content = nullptr;
		len = 0;
	}
}

TString::~TString()
{
	delete []content;
	content = nullptr;
	len = 0;
}

inline void TString::Delete()
{
	delete []content;
	content = nullptr;
	len = 0;
}

istream& operator>>(istream&in, TString&ts)
{
	ts.Delete();
	char* temp = new char[1024];
	if (in >> temp) {
		ts = temp;
	}
	delete[]temp;
	return in;
}


ostream& operator<<(ostream&out, const TString&ts)
{
	if (ts.content != nullptr&&ts.content[0]!='\0')
		out << ts.content;
	else
		out << "<NULL>";
	return out;
}

const char* TString::c_str()const
{
	return content;
}

/*TString& TString::operator=(int n)
{
	if (!n)
		Delete();
	return *this;
}*/

TString& TString:: operator=(const TString&ts )
{
	TString temp = ts;
	Delete();
	if (temp.len) {
		len = temp.len;
		content = new char[len + 1];
		strcpy(content, temp.content);
		content[len] = '\0';
	}
	return *this;
}

TString& TString::operator=(const char*s)
{
	Delete();
	if (s != nullptr) {
		len = strlen(s);
		content = new char[len + 1];
		strcpy(content, s);
		content[len] = '\0';
	}
	return *this;
}

/**************************************************************/
// +
TString operator+(const TString&a, const TString&b)
{
	TString ans;
	ans.len = a.len + b.len;
	if (ans.len == 0)
		return ans;
	ans.content = new char[ans.len + 1];
	if (a.content) {
		strcpy(ans.content, a.content);
		if(b.content)
			strcat(ans.content, b.content);
	}
	else {
		if (b.content)
			strcpy(ans.content, b.content);
	}
	
	return ans;
}

TString operator+(const TString&a, const char*s)
{
	TString ans;
	ans.len = a.len;
	if(s)
		ans.len = a.len + strlen(s);
	ans.content = new char[ans.len + 1];
	
	if (a.content) {
		strcpy(ans.content, a.content);
		if(s!=NULL)
			strcat(ans.content, s);
	}
	else {
		if(s!=NULL)
			strcpy(ans.content, s);
	}
	
	return ans;
}

TString operator+(const char*s, const TString&a)
{
	TString ans;
	ans.len = a.len;
	if(s)
		ans.len = a.len +  strlen(s);
	ans.content = new char[ans.len + 1];
	if (s) {
		strcpy(ans.content, s);
		if (a.content)
			strcat(ans.content, a.content);
	}
	else {
		if (a.content)
			strcpy(ans.content, a.content);
	}
		

	return ans;
}

TString operator+(const TString&a, char*s)
{
	TString ans;
	ans.len = a.len;
	if(s)
		ans.len = a.len + strlen(s);
	ans.content = new char[ans.len + 1];
	
	if (a.content) {
		strcpy(ans.content, a.content);
		if(s)
			strcat(ans.content, s);
	}
	else {
		if(s)
			strcpy(ans.content, s);
	}

	return ans;
}

TString operator+(char*s, const TString&a)
{
	TString ans;
	ans.len = a.len;
	if (s)
		ans.len = a.len + strlen(s);
	ans.content = new char[ans.len + 1];
	if (s) {
		strcpy(ans.content, s);
		if (a.content)
			strcat(ans.content, a.content);
	}
	else {
		if (a.content)
			strcpy(ans.content, a.content);
	}
	return ans;
}

TString operator+(const TString&a, char c)
{
	TString ans;
	ans.len = a.len + 1;
	ans.content = new char[ans.len + 1];
	if (a.content)
		strcpy(ans.content, a.content);
	ans.content[ans.len - 1] = c;
	ans.content[ans.len] = '\0';
	return ans;
}

TString operator+(char c, const TString&a)
{
	TString ans;
	ans.len = a.len + 1;
	ans.content = new char[ans.len + 1];
	ans.content[0] = c;
	ans.content[1] = '\0';
	if (a.content)
		strcat(ans.content, a.content);
	ans.content[ans.len] = '\0';
	return ans;
}

/***********************************************/
//+=
TString& TString::operator+=(const TString&a)
{
	if (a.len) {
		
		if (len == 0) {
			len = a.len;
			content = new char[len + 1];
			strcpy(content,a.content);
		}
		else {
			int len_t = len+a.len;
			char* temp = new char[len_t + 1];
			strcpy(temp, content);
			strcat(temp,a.content);
			
			Delete();
		
			len = len_t;
			content = new char[len + 1];
			strcpy(content, temp);
			delete []temp;
		}
	}
	return *this;
}

TString& TString::operator+=(const char*s)
{
	if (s) {
		if (len == 0) {
			Delete();
			len = strlen(s);
			content = new char[len + 1];
			strcpy(content, s);
		}
		else {
			len += strlen(s);
			char* old_content = content;
			content = new char[len + 1];
			strcpy(content, old_content);
			strcat(content, s);

			delete[]old_content;
		}
	}
	return *this;
}

 TString& TString::operator+=(char*s)//ceshi
{
	if (s) {
		if (len == 0) {
			len = strlen(s);
			content = new char[len + 1];
			strcpy(content, s);
		}
		else {
			len += strlen(s);
			char* old_content = content;
			content = new char[len + 1];
			strcpy(content,old_content);
			strcat(content, s);
			
			delete []old_content;
			
		}
	}
	return *this;
}

TString& TString::operator+=(char c)
{
	if (len == 0) {
		len = 1;
		content = new char[len + 1];
		content[0] = c;
		content[1] = '\0';
	}
	else {
		++len;
		//char* temp = new char[len_t + 1];
		char* old_content = content;
		content = new char[len + 1];
		strcpy(content,old_content);
		content[len-1] = c;
		content[len] = '\0';
	
		delete []old_content;
	}

	return *this;
}

TString TString::operator-(const TString& a)
{
	TString ans;	
	if (a.len==0||strstr(content, a.content) == nullptr) 
		ans = *this;
		
	else {
		char* p = strstr(content, a.content);
		int iter = p - content;//下标
		char* temp = new char[len -a.len+1];
		strncpy(temp,content,iter);
		p += a.len;
		while (*p != '\0') {
			temp[iter++] = *p++;
		}


		temp[len - a.len] = '\0';
		ans.content = new char[len-a.len+1];
		ans.len = len - a.len;
		strcpy(ans.content, temp);
		delete[]temp;
	}
	

	return ans;
}
TString TString::operator-(const char*s)
{
	TString ans;
	if (!s||strstr(content, s) == nullptr)
		ans = *this;

	else {
		char* p = strstr(content, s);
		int iter = p - content;
		char* temp = new char[len - strlen(s) + 1];
		strncpy(temp, content, iter);
		p += strlen(s);
		while (*p != '\0') {
			temp[iter++] = *p++;
		}


		temp[len - strlen(s)] = '\0';
		ans.content = new char[len - strlen(s) + 1];
		ans.len = len - strlen(s);
		strcpy(ans.content, temp);
		delete[]temp;
	}


	return ans;
}
TString TString::operator-(char*s)
{
	TString ans;
	if (!s || strstr(content, s) == nullptr)
		ans = *this;

	else {
		char* p = strstr(content, s);
		int iter = p - content;
		char* temp = new char[len - strlen(s) + 1];
		strncpy(temp, content, iter);
		p += strlen(s);
		while (*p != '\0') {
			temp[iter++] = *p++;
		}


		temp[len - strlen(s)] = '\0';
		ans.content = new char[len - strlen(s) + 1];
		ans.len = len - strlen(s);
		strcpy(ans.content, temp);
		delete[]temp;
	}


	return ans;
}

TString TString::operator-(char c)
{
	TString ans;
	if (strchr(content, c) == nullptr)
		ans = *this;

	else {
		char* p = strchr(content, c);
		int iter = p - content;
		char* temp = new char[len ];
		strncpy(temp, content, iter);
		p += 1;
		while (*p != '\0') {
			temp[iter++] = *p++;
		}


		temp[len - 1] = '\0';
		ans.content = new char[len ];
		ans.len = len -1;
		strcpy(ans.content, temp);
		delete[]temp;
	}


	return ans;
}

TString& TString::operator-=(const TString&a)
{
	if (a.len == 0 || strstr(content, a.content) == nullptr)
		return *this;

	else {
		char* p = strstr(content, a.content);
		int iter = p - content;
		char* temp = new char[len - a.len + 1];
		strncpy(temp, content, iter);
		p += a.len;
		while (*p != '\0') {
			temp[iter++] = *p++;
		}

		temp[len - a.len] = '\0';
		int len_t = len;
		Delete();
		content = new char[len_t - a.len + 1];
		len = len_t - a.len;
		strcpy(content, temp);
		delete[]temp;
	}
	return *this;
}

TString& TString::operator-=(const char*s)
{
	if (!s || strstr(content, s) == nullptr)
		return *this;

	else {
		char* p = strstr(content, s);
		int iter = p - content;
		char* temp = new char[len - strlen(s) + 1];
		strncpy(temp, content, iter);
		p += strlen(s);
		while (*p != '\0') {
			temp[iter++] = *p++;
		}

		temp[len - strlen(s)] = '\0';
		int len_t = len;
		Delete();
		content = new char[len_t - strlen(s) + 1];
		len = len_t - strlen(s);
		strcpy(content, temp);
		delete[]temp;
	}
	return *this;
}

TString& TString::operator-=(char* s)
{
	if (!s || strstr(content, s) == nullptr)
		return *this;

	else {
		char* p = strstr(content, s);
		int iter = p - content;
		char* temp = new char[len - strlen(s) + 1];
		strncpy(temp, content, iter);
		p += strlen(s);
		while (*p != '\0') {
			temp[iter++] = *p++;
		}

		temp[len - strlen(s)] = '\0';
		int len_t = len;
		Delete();
		content = new char[len_t - strlen(s) + 1];
		len = len_t - strlen(s);
		strcpy(content, temp);
		delete[]temp;
	}
	return *this;
}

TString& TString::operator-=(char c)
{
	if (strchr(content, c) == nullptr)
		return *this;

	else {
		char* p = strchr(content, c);
		int iter = p - content;
		char* temp = new char[len];
		strncpy(temp, content, iter);
		p += 1;
		while (*p != '\0') {
			temp[iter++] = *p++;
		}

		temp[len - 1] = '\0';
		int len_t = len;
		Delete();
		content = new char[len_t];
		len = len_t - 1;
		strcpy(content, temp);
		delete[]temp;
	}

	return *this;
}

TString TString::operator*(int n)
{
	TString ans;
	if (n == 0 || len == 0)
		return ans;
	ans.content = new char[n * len + 1];
	ans.len = n * len;
	char* temp = new char[n * len + 1];
	strcpy(temp, content);
	for (int i = 0; i < n-1; i++) {
		strcat(temp, content);
	}
	strcpy(ans.content, temp);
	delete[]temp;
	return ans;

}

TString& TString::operator*=(int n)
{
	if (n == 0 || len == 0) {
		Delete();
		return *this;
	}
	char* temp0 = new char[len + 1];
	strcpy(temp0, content);
	Delete();
	len = n * strlen(temp0);
	content = new char[n * len + 1];
	
	char* temp = new char[n * len + 1];
	strcpy(temp, temp0);
	for (int i = 0; i < n-1; i++) {
		strcat(temp, temp0);
	}
	strcpy(content, temp);
	delete[]temp;
	delete[]temp0;
	return *this;
}



TString TString::operator!()
{
	TString ans = *this;
	if (ans.len == 0)
		return ans;
	Strrev(ans.content);
	return ans;
}

/*****************compare******************/
bool TString::operator<(const TString&a)
{
	if (!a.content||a.len==0)
		return 0;
	if (!content||len==0)
		return 1;
	return strcmp(content,a.content)<0;
}

bool TString::operator<=(const TString&a)
{
	if (!content||len==0)
		return 1;
	if (!a.content||a.len==0)
		return 0;//注意顺序
	return strcmp(content, a.content) <= 0;
}

bool TString::operator>(const TString& a)
{
	if (!content||len==0)
		return 0;
	if (!a.content||a.len==0)
		return 1;
	return strcmp(content, a.content) > 0;
}

bool TString::operator>=(const TString& a)
{
	if (!a.content || a.len == 0)
		return 1;
	if (!content || len == 0)
		return 0;
	return strcmp(content, a.content) >= 0;
}

bool TString::operator==(const TString& a)
{
	if ((!a.content && !content)||(a.len==0&&len==0))
		return 1;
	if (!a.content || !content||a.len == 0||len == 0)
		return 0;
	return strcmp(content, a.content) == 0;
}

bool TString::operator!=(const TString& a)
{
	if ((!a.content && !content)||(a.len == 0 && len == 0))
		return 0;
	if (!a.content || !content||a.len==0||len==0)
		return 1;
	return strcmp(content, a.content) != 0;
}

//const char*
bool TString::operator<(const char*s)
{
	if (!s || strlen(s) == 0)
		return 0;
	if (!content||len==0)
		return 1;
	return strcmp(content, s) < 0;
}

bool TString::operator<=(const char* s)
{
	if (!content||len==0)
		return 1;
	if (!s || strlen(s) == 0)
		return 0;//注意顺序
	return strcmp(content, s) <= 0;
}

bool TString::operator>(const char* s)
{
	if (!content||len==0)
		return 0;
	if (!s || strlen(s) == 0)
		return 1;
	return strcmp(content, s) > 0;
}

bool TString::operator>=(const char* s)
{
	if (!s||strlen(s)==0)
		return 1;
	if (!content || len == 0)
		return 0;
	return strcmp(content, s) >= 0;
}

bool TString::operator==(const char* s)
{
	if ((!s || strlen(s) == 0 )&& (!content || len == 0))
		return 1;
	if ((!s || strlen(s) == 0 )|| !content || len == 0)
		return 0;
	return strcmp(content, s) == 0;
}

bool TString::operator!=(const char* s)
{
	if ((!s || strlen(s) == 0) && (!content || len == 0))
		return 0;
	if ((!s || strlen(s) == 0 )|| !content || len == 0)
		return 1;
	return strcmp(content, s) != 0;
}

bool operator <(const char*s, const TString&a)
{
	if (!a.content || a.len == 0)
		return 0;
	if (!s || strlen(s) == 0)
		return 1;
	
	return strcmp(s,a.content) < 0;
}
bool operator<=(const char*s, const TString&a)
{
	if (!s || strlen(s) == 0)
		return 1;
	if (!a.content || a.len == 0)
		return 0;
	return strcmp(s, a.content) <= 0;
}
bool operator>(const char*s, const TString&a)
{
	if (!s || strlen(s) == 0)
		return 0;
	if (!a.content || a.len == 0)
		return 1;
	 return strcmp(s, a.content) > 0;
}
bool operator>=(const char*s, const TString&a)
{
	if (!a.content || a.len == 0)
		return 1;
	if (!s || strlen(s) == 0)
		return 0;
	return strcmp(s, a.content) >= 0;
}
bool operator==(const char*s, const TString&a)
{
	if ((!s || strlen(s) == 0)&& (!a.content || a.len == 0))
		return 1;
	if (!s || strlen(s) == 0 || !a.content || a.len == 0)
		return 0;
	return strcmp(s, a.content) == 0;
}
bool operator!=(const char*s, const TString&a)
{
	if ((!s || strlen(s) == 0)&& (!a.content || a.len == 0))
		return 0;
	if (!s || strlen(s) == 0 || !a.content || a.len == 0)
		return 1;
	return strcmp(s, a.content) != 0;
}


//


/****************length()***************************/
int TString::length()const
{
	return len;
}



/****************[ ]*********************/
char& TString::operator[](int n)
{
	if (n < 0 || n >= len)
		return content[0];//如果为空如何处理？
	return content[n];
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */
int TStringLen(const TString& a)
{
	return a.length();
}

void Strrev(char*&s)
{
	if (!s)
		return ;
	char* ans = new char[strlen(s) + 1];
	int i = 0;
	for (; i < (int)strlen(s); i++) {
		ans[i] = s[(int)strlen(s) - 1-i];
	}
	ans[i] = '\0';
	delete[]s;
	s = ans;
	return;
}
