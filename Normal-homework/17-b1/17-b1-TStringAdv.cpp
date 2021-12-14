
#define _CRT_SECURE_NO_WARNINGS
#include"17-b1-TStringAdv.h"

TStringAdv::TStringAdv():TString()
{
}

TStringAdv::TStringAdv(const TStringAdv&x):TString(x)
{
}

TStringAdv::TStringAdv(const char* s) : TString(s)
{
}

TStringAdv::TStringAdv(const TString& a):TString(a)
{	
}

TStringAdv::~TStringAdv()
{
	if (content)
		delete[] content;
	content = nullptr;
	len = 0;
}

TStringAdv& TStringAdv::operator=(const TStringAdv&x)
{
	this->TString::operator=(x);
	return *this;
}

TStringAdv& TStringAdv::operator=(const char*s)
{
	this->TString::operator=(s);
	return *this;
}

TStringAdv& TStringAdv::assign(const TStringAdv&x)
{
	*this = x;
	return *this;
}

TStringAdv& TStringAdv::assign(const char*s)
{
	*this = s;
	return *this;
}

TStringAdv& TStringAdv::assign(const char&c)
{
	Delete();
	content = new char[2];
	content[0] = c;
	content[1] = 0;
	len = 1;
	return *this;
}

//+=追加
TStringAdv& TStringAdv::append(const TStringAdv&x)
{
	*this += x;
	return *this;
}

TStringAdv& TStringAdv::append(const char*s)
{
	*this += s;
	return *this;
}

TStringAdv& TStringAdv::append(const char&c)
{
	*this += c;
	return *this;
}

//插入
TStringAdv& TStringAdv::insert(const TStringAdv&x, int pos)
{
	if (pos<1 || pos>len+1||!x.content)
		return *this;
	char* temp = content;
	this->content = new char[x.len + len + 1];
	this->len = len+x.len;

	int it = 0,it_temp=0;
	for (it = 0; it < pos - 1; it++) {
		content[it] = temp[it];
	}
	it_temp = it;
	for (int it_x=0; it_x < x.len; ) {
		content[it++] = x.content[it_x++];
	}
	while (it < len) {
		content[it++] = temp[it_temp++];
	}
	content[it] = '\0';
	delete[]temp;
	return *this;

}

TStringAdv& TStringAdv::insert(const char*s, int pos)
{
	if (pos<1 || pos>len + 1||!s)
		return *this;
	char* temp = content;
	this->content = new char[strlen(s)+ len + 1];
	this->len = len +strlen(s);

	int it = 0, it_temp = 0;
	for (it = 0; it < pos - 1; it++) {
		content[it] = temp[it];
	}
	it_temp = it;
	for (int it_x = 0; it_x < strlen(s); ) {
		content[it++] =s[it_x++];
	}
	while (it < len) {
		content[it++] = temp[it_temp++];
	}
	content[it] = '\0';
	delete[]temp;
	return *this;
}
TStringAdv& TStringAdv::insert(const char&c, int pos)
{
	if (pos<1 || pos>len + 1)
		return *this;
	char* temp = content;
	this->content = new char[len+2];
	this->len = len + 1;

	int it = 0, it_temp = 0;
	for (it = 0; it < pos - 1; it++) {
		content[it] = temp[it];
	}
	it_temp = it;
	
	content[it++] =c;
	
	while (it < len) {
		content[it++] = temp[it_temp++];
	}
	content[it] = '\0';
	delete[]temp;
	return *this;
}

//-=删除匹配项
TStringAdv& TStringAdv::erase(const TStringAdv&x)
{
	*this -= x;
	return *this;
}

TStringAdv& TStringAdv::erase(const char*s)
{
	*this -= s;
	return *this;
}

TStringAdv& TStringAdv::erase(const char&c)
{
	*this -= c;
	return *this;
}
//子串
TStringAdv TStringAdv::substr(const int begin, const int length)
{
	TStringAdv ans;	
	if (begin<1 || begin>this->len||length==0)
		return ans;
	int ans_len;
	if (length == -1)//默认值
		ans_len = this->len - begin + 1;
	else
		ans_len = (length < this->len - begin + 1) ? length : this->len - begin + 1;
	ans.len = ans_len;
	ans.content = new char[ans.len + 1];
	int i = 0,source_i=begin-1;
	for (; i < ans_len; i++) {
		ans.content[i] = content[source_i++];
	}
	ans.content[i] = '\0';
	return ans;
}

//[]
char& TStringAdv::at(const int n)
{
	return (*this)[n];
}
