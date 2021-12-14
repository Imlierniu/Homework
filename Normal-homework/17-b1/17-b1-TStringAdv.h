
#pragma once
#include"17-b1-TString.h"

class TStringAdv :public TString
{

public:
	
	TStringAdv();
	TStringAdv(const TStringAdv&);
	TStringAdv(const char*);
	TStringAdv(const TString&);
	~TStringAdv();
	TStringAdv& operator=(const TStringAdv&);
	TStringAdv& operator=(const char*);
	
	//赋值
	TStringAdv& assign(const TStringAdv &);
	TStringAdv& assign(const char*);
	TStringAdv& assign(const char &);
	//+=追加
	TStringAdv& append(const TStringAdv&);
	TStringAdv& append(const char*);
	TStringAdv& append(const char&);
	//插入
	TStringAdv& insert(const TStringAdv&,int pos);
	TStringAdv& insert(const char*, int pos);
	TStringAdv& insert(const char&, int pos);
	//-=删除匹配项
	TStringAdv& erase(const TStringAdv&);
	TStringAdv& erase(const char*);
	TStringAdv& erase(const char&);
	//子串
	TStringAdv substr(const int pos,const int length=-1);
	//[]
	char& at(const int n);











};