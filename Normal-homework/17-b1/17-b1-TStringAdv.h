
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
	
	//��ֵ
	TStringAdv& assign(const TStringAdv &);
	TStringAdv& assign(const char*);
	TStringAdv& assign(const char &);
	//+=׷��
	TStringAdv& append(const TStringAdv&);
	TStringAdv& append(const char*);
	TStringAdv& append(const char&);
	//����
	TStringAdv& insert(const TStringAdv&,int pos);
	TStringAdv& insert(const char*, int pos);
	TStringAdv& insert(const char&, int pos);
	//-=ɾ��ƥ����
	TStringAdv& erase(const TStringAdv&);
	TStringAdv& erase(const char*);
	TStringAdv& erase(const char&);
	//�Ӵ�
	TStringAdv substr(const int pos,const int length=-1);
	//[]
	char& at(const int n);











};