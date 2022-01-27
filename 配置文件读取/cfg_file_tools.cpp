/*1752846 边泽轩 车辆工程 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <io.h>
#include "../include/cfg_file_tools.h"
using namespace std;

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */
#define AddGroup 0
#define DelGroup 1
#define ModGroup 2

#define AddItem 3
#define DelItem 4
#define UpdItem 5
#define GetItem 6

#define ExiGroup 7//判断是否存在该组的模式
#define ExiItem 8//是否存在该项

static bool UpdAddItem(string& CFGfile,string group_name,string Item)//update时如果没找到就添加
{
	int i = CFGfile.find(group_name, 0);
	i += group_name.length();
	CFGfile = CFGfile.substr(0, i) + Item + CFGfile.substr(i);
	return 1;
}



static void DelNotation(string& s)
{
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ';' || s[i] == '#') {
			s = s.substr(0, i);         //去除注释
			return;
		}
	}
}

static void DelSpaceOfHeadTail(string& s)
{
	DelNotation(s);
	int left = 0, right = s.length() - 1;
	while (left < right) {
		if (s[left] == ' ' || s[left] == '	')
			left++;
		if (s[right] == ' ' || s[right] == '	')
			right--;
		if ((s[left] != ' '&&s[left]!='	') && (s[right] != ' '&&s[right]!='	'))
			break;
	}
	s=s.substr(left, right-left+1);
}




static bool IsGroup(string s)//判断是否是组名
{
	DelSpaceOfHeadTail(s);
	if (s.length() <= 2)
		return 0;
	return (s[0] == '[' && s[s.length() - 1] == ']');
}

static bool IsGroupname(string s, string group_name)//判断是否是目标组名
{
	DelSpaceOfHeadTail(s);
	if (!IsGroup(s) || s.length() <= 2)
		return 0;

	/*int left = 0, right = s.length() - 1;
	while (left < right) {
		if (s[left] != '[')
			left++;
		if (s[right] != ']')
			right--;
		if (s[left] == '[' && s[right] == ']')
			break;
	}*/
	//if (left >= right||right-left-1!=group_name.length())
	//string sub_s = s.substr(left,group_name.length());
	return (group_name == s);
}

static bool IsItem(string s,string Item_name)
{
	//S已经掐头去尾了，仅处理“=”前后的空格即可

	int i = 0,len=s.length();
	for (; i < s.length(); i++) {
		if (s[i] == '=') {
			s = s.substr(0, i+1);
			break;
		}
	}
	if (i == len)	//说明不含等号
		return 0;
	string s0 = s;
	string Item_name0 = Item_name;
	DelSpaceOfHeadTail(s0);
	DelSpaceOfHeadTail(Item_name0);
	
	if (!s0.length()||!Item_name0.length()||s0[s0.length() - 1] != '=' || Item_name0[Item_name0.length() - 1] != '=')
		return 0;
	else {
		s0 = s0.substr(0, s0.length() - 1);
		Item_name0 = Item_name0.substr(0, Item_name0.length() - 1);
		DelSpaceOfHeadTail(s0);
		DelSpaceOfHeadTail(Item_name0);
	}
	return s0 == Item_name0;
	//return (s.substr(0, Item_name.length()) == Item_name);
}

static int DelAllItem(fstream& fp, string& CFGfile, string Item)
{
	fp.clear();
	fp.seekg(0, ios::beg);
	string s;
	int flag = 0;
	while (fp.peek() != EOF) {
		getline(fp, s);
		if (IsItem(s, Item))
			flag++;
		else
			CFGfile += s + "\n";
	}
	return flag;
}

static int ReadFile(fstream& fp,string& CFGfile,const char*group_name,int mode)
{
	fp.clear();
	fp.seekg(0, ios::beg);
	string gname="[" + (string)group_name + "]" ;
	//cout << gname << '-' << endl;
	//cout << fp.tellp() << endl;
	//cout << fp.peek() << endl;
	string s;
	if (mode == AddGroup) {
		while (fp.peek() != EOF) {
			//cout << "!";
			getline(fp, s);
			//DelSpaceOfHeadTail(s);
			//cout << s << endl;
			//DelSpaceOfHeadTail(s);
			if (IsGroupname(s, gname))
				return 0;
			//CFGfile += s + '\n';
		}
		CFGfile += "[" + (string)group_name + "]" + "\n";
		//CFGfile += "\n";
	}
	else if (mode == DelGroup) {
		int del_num = 0;
		while (fp.peek() != EOF) {
			getline(fp, s);
			
			//DelSpaceOfHeadTail(s_old);
			if (IsGroupname(s, gname)) {
				del_num++;
				while (fp.peek() != EOF) {
					getline(fp, s);
					if(IsGroupname(s,gname))
						del_num++;
					else if (!IsGroupname(s, gname)&&IsGroup(s)) 
						break;
				}
			}
			CFGfile += s + "\n";
		}
		return del_num;
	}
	else if (mode == ExiGroup) {
		while (fp.peek() != EOF) {
			getline(fp, s);
			if (IsGroupname(s, gname))
				return 1;
		}
	}
	else
		return 0;
	
	return 1;
}

static bool WriteFile(fstream& fp, string& CFGfile)//?
{
	fp << CFGfile;
	return 1;
}

static void Write(fstream& fp, string& CFGfile)
{
	fp.clear();
	fp.seekg(0, ios::beg);
	//fp << CFGfile<<endl;
	fp << CFGfile << "\n";
}

static int ReadFile_item(fstream& fp, string& CFGfile,string& add, const char* group_name, const char*item_name,int mode)
{
	fp.clear();
	fp.seekg(0, ios::beg);
	string tmp;
	//if (!ReadFile(fp, tmp, group_name, ExiGroup))
		//return 0;//如果不存在该组return0；
	fp.clear();
	fp.seekg(0, ios::beg);


	string gname = "[" + (string)group_name + "]";
	int flag = 0;
	string s;
	if (mode == AddItem) {
		while (fp.peek() != EOF) {
			//cout << "!";
			getline(fp, s);
			CFGfile += s+"\n";
			//DelSpaceOfHeadTail(s);
			//cout << s << endl;
			if (IsGroupname(s, gname)&&!flag) {//只在第一个组添加
				CFGfile += add;
				//fp << CFGfile << endl;
				//cout << "ok" << endl;
				flag = 1;
			}
		}
	}
	else if (mode == DelItem) {
		while (fp.peek() != EOF) {
			getline(fp, s);
			CFGfile += s + "\n";
			//DelSpaceOfHeadTail(s);
			if (IsGroupname(s, gname)&&!flag) {
				while (fp.peek() != EOF) {
					getline(fp, s);
					//string s_old = s;
					//DelSpaceOfHeadTail(s_old);
					if (IsItem(s, add)) {//add此时是del,只是item的名字
						flag++;
						break;
					}
					else
						CFGfile += s + "\n";
					if (!IsGroupname(s, gname) && IsGroup(s))
						break;
				}
			}
		}
	}
	else if (mode == UpdItem) {
		string itemname = (string)item_name + " = ";
		//cout << itemname <<'-' << endl;
		int flag = -1;
		while (fp.peek() != EOF) {
			getline(fp, s);
			CFGfile += s + "\n";
			if (IsGroupname(s, gname)) {
				while (fp.peek() != EOF) {
					getline(fp, s);
					//string s_old = s;
					//DelSpaceOfHeadTail(s_old);
					//cout << s << "---" << itemname << endl;
					if (IsItem(s, itemname)) {//add此时是upd，是要更新的一整行
						CFGfile += add;
						flag = 1;
						break;
					}
					else
						CFGfile += s + "\n";
				}
			}
		}
		return flag;
	}
	else if (mode == ExiItem) {
		string itemname = (string)item_name + " = ";
		while (fp.peek() != EOF) {
			getline(fp, s);
			if (IsGroupname(s, gname)) {
				while (fp.peek() != EOF) {
					getline(fp, s);
					if (IsItem(s, itemname))
						return 1;
					if (!IsGroupname(s, gname) && IsGroup(s))
						return 0;
				}
			}
		}
		fp.clear();
		fp.seekg(0, ios::beg);
		return 0;
	}
	//cout << fp.tellp() << endl;
	//cout << CFGfile << endl;
	//fp << "OK" << endl;
	return flag;
}

static string GetVal(fstream&fp,const char*group_name,const char*item_name,int mode)
{
	fp.clear();
	fp.seekg(0, ios::beg);
	int flag = 0;
	
	string gname;
	if (group_name)
		gname = "[" + (string)group_name + "]";
	string itemname = (string)item_name + " = ",s;
	//cout << gname << "--" << itemname << endl;
	if (mode == 1) {   //复杂配置文件
		while (fp.peek() != EOF) {
			getline(fp, s);
			DelSpaceOfHeadTail(s);
			if (IsGroupname(s, gname)) {
				while (fp.peek() != EOF) {
					getline(fp, s);
					DelSpaceOfHeadTail(s);
					if (IsItem(s, itemname)) {
						for (int i = 0; i < s.length(); i++) {
							if (s[i] == '=') {
								if (i + 1 >= s.length())
									return "";
								s = s.substr(i+1);
								break;
							}
						}
						DelSpaceOfHeadTail(s);
						return s;
						//return s.substr(itemname.length());
					}
				}
			}

		}
	}
	else if(mode==0) {//简单配置文件
		while (fp.peek() != EOF) {
			getline(fp, s);
			DelSpaceOfHeadTail(s);
			if (IsItem(s, itemname))
				return s.substr(itemname.length());
		}
	}
	
	return "";
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：如有必要，按需加入其它内容
***************************************************************************/
CFT::CFT()
{
	filename = "";
	isopen = 0;//防止双参构造后调用open
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：如有必要，按需加入其它内容
***************************************************************************/
CFT::~CFT()
{
	if (fp.is_open()) {
		fp.close();
		isopen = 0;
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
CFT::CFT(const char* cfgname, int opt)
{
	open(cfgname, opt);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void CFT::open(const char* cfgname, int opt)
{
	this->filename = cfgname;
	if (isopen)
		return;
	if (opt == OPEN_OPT_RDONLY) 
		fp.open(cfgname, ios::in);
	else {
		fp.open(cfgname, ios::out | ios::in | ios::app);
		//fp.clear();
		//fp.seekp(0, ios::beg);
		//cout << fp.tellp() << "!" << endl;
	}
	
	isopen = !!fp.is_open();
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：打开成功返回true，否则返回false
***************************************************************************/
bool CFT::is_open(void)
{
	return isopen;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void CFT::close()
{
	if (fp.is_open()) {
		//cout << "??" << endl;
		fp.close();
		isopen = 0;
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：C++17中有filesystem::resize_file直接可以修改文件大小，之前的版本无
                   因此本函数扔沿用C的旧方法
	    已实现，不要动
***************************************************************************/
int CFT::file_resize(int newsize)
{
	/* 如果大小是负数则直接返回-1 */
	if (newsize < 0)
		return -1;

	if (!fp.good())
		fp.clear();

	/* 取fp当前指针位置 */
	int now_pos = int(fp.tellg());

	/* 首先：C++方式关闭 */
	this->close();

	/* 其次：C方式打开并改变文件大小 */
	FILE* fp_cstyle;
	fp_cstyle = fopen(filename.c_str(), "rb+"); //rw方式打开
	if (fp_cstyle) {
		_chsize(_fileno(fp_cstyle), newsize);
		fclose(fp_cstyle);
	}
	else
		cout << "open [" << filename << "] for resize failed" << endl;

	/* 再次：C++方式重新打开 */
	fp.open(filename, ios::in | ios::out | ios::binary);
	if (fp.is_open()==0) {
		cout << "reopen [" << filename << "] after resize failed" << endl;
		return -1;
	}

	/* 文件指针移动到原位置 */
	fp.seekg(now_pos < newsize ? now_pos:newsize, ios::beg);
	return 0;
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（protected）
   ---------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int CFT::group_add(const char* group_name)
{
	//fp.clear();
	//fp.seekp(0, ios::beg);
	//cout << fp.tellp() << endl;
	string CFGfile;
	//cout << fp.tellp() << endl;
	if (ReadFile(fp, CFGfile, group_name, AddGroup)) {//不存在group_name,重写
		//cout << fp.tellp() << "!!" << endl;
		//this->file_resize(0);
		//fp.clear();
		//cout << fp.tellp() << endl;
		//fp.seekg(0, ios::beg);
		//fp.seekp(0, ios::beg);
		//cout << fp.tellp() << endl;
		//cout << fp.tellg() << "X" <<fp.tellp()<< endl;
		//fp.write("0", 10);
		
		//fp.close();
		
		Write(fp, CFGfile);
		return 1;
	}
	return 0; //此句根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::group_del(const char* group_name)
{
	string CFGfile;
	int ans = 0;
	if (ans=ReadFile(fp, CFGfile, group_name, DelGroup)) {
		this->file_resize(0);
		//fp.clear();
		//fp.seekg(0, ios::beg);
		// 
		// 
		//cout << CFGfile.length() << endl;
		//fp << CFGfile;
		Write(fp, CFGfile);
		return ans;
	}
	return ans; //此句根据需要修改
}

static int ItemAdd(fstream&fp,string&CFGfile,string add, const char* group_name, const char* item_name)
{

	if (ReadFile_item(fp, CFGfile, add, group_name, item_name, ExiItem))//该组若有Item不加了
		return 0;
	return ReadFile_item(fp, CFGfile, add, group_name, item_name, AddItem);
}

static int ItemSimpleAdd(fstream&fp,string &CFGfile,string add,const char*item_name)
{
	fp.clear();
	fp.seekg(0, ios::beg);
	string s;
	string Item = (string)item_name + " = ";
	int flag = 1;
	while (fp.peek() != EOF) {
		getline(fp, s);
		if (IsItem(s, Item))
			return 0;
		else
			CFGfile += s +"\n";
	}
	CFGfile += add;
	return flag;
}

static int ItemSimpleUpd(fstream& fp, string& CFGfile, string upd, const char* item_name)
{
	fp.clear();
	fp.seekg(0, ios::beg);
	string s;
	string Item = (string)item_name + " = ";
	int flag = 0;
	while (fp.peek() != EOF) {
		getline(fp, s);
		if (IsItem(s, Item)&&!flag) {
			CFGfile += upd;
			flag = 1;
		}
		else
			CFGfile += s + "\n";
	}
	if (!flag) {
		CFGfile += upd;
		flag = 1;
	}
	return flag;
}



static bool IsSamplefile(fstream& fp, const char* group_name)
{
	fp.clear();
	fp.seekg(0, ios::beg);
	string s;
	while (fp.peek() != EOF) {
		getline(fp, s);
		if (IsGroup(s))
			return 0;
	}
	fp.clear();
	fp.seekg(0, ios::beg);
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name, const int item_value)
{
	string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans = 1,issimp= IsSamplefile(fp, group_name);
	if (group_name && issimp)
		return 0;
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleAdd(fp, CFGfile, add, item_name)) {
			return 0;
		}
	}
	else
		ans = ItemAdd(fp, CFGfile, add, group_name, item_name);
	if (ans == 0)
		return 0;
	this->file_resize(0);
	Write(fp, CFGfile);
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name, const double item_value)
{
	string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	//string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans = 1, issimp = IsSamplefile(fp, group_name);
	if (group_name && issimp)
		return 0;
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleAdd(fp, CFGfile, add, item_name)) {
			return 0;
		}
	}
	else
		ans = ItemAdd(fp, CFGfile, add, group_name, item_name);
	if (ans == 0)
		return 0;
	this->file_resize(0);
	Write(fp, CFGfile);
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name, const char *item_value)
{
	//int ans=1;
	string CFGfile = "", add = (string)item_name + " = " + string(item_value) + "\n";
	//string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans = 1, issimp = IsSamplefile(fp, group_name);
	if (group_name && issimp)
		return 0;
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleAdd(fp, CFGfile, add, item_name)) {
			return 0;
		}
	}
	else
		ans = ItemAdd(fp, CFGfile, add, group_name, item_name);
	if (ans == 0)
		return 0;
	this->file_resize(0);
	Write(fp, CFGfile);
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name, const string &item_value)
{
	string CFGfile = "", add = (string)item_name + " = " + (item_value)+"\n";
	//string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans = 1, issimp = IsSamplefile(fp, group_name);
	if (group_name && issimp)
		return 0;
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleAdd(fp, CFGfile, add, item_name)) {
			return 0;
		}
	}
	else
		ans = ItemAdd(fp, CFGfile, add, group_name, item_name);
	if (ans == 0)
		return 0;
	this->file_resize(0);
	Write(fp, CFGfile);
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name, const char item_value)
{
	string CFGfile = "", add = (string)item_name + " = " + item_value + "\n";
	//string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans = 1, issimp = IsSamplefile(fp, group_name);
	if (group_name && issimp)
		return 0;
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleAdd(fp, CFGfile, add, item_name)) {
			return 0;
		}
	}
	else
		ans = ItemAdd(fp, CFGfile, add, group_name, item_name);
	if (ans == 0)
		return 0;
	this->file_resize(0);
	Write(fp, CFGfile);
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_add(const char* group_name, const char* item_name)
{
	string CFGfile, add = (string)item_name + " = " + "\n";
	//string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans = 1, issimp = IsSamplefile(fp, group_name);
	if (group_name && issimp)
		return 0;
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleAdd(fp, CFGfile, add, item_name)) {
			return 0;
		}
	}
	else
		ans = ItemAdd(fp, CFGfile, add, group_name, item_name);
	if (ans == 0)
		return 0;
	this->file_resize(0);
	Write(fp, CFGfile);
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_del(const char* group_name, const char* item_name)
{
	string CFGfile, del = (string)item_name + " = ";
	int ans;
	if (group_name == NULL) {//
		ans=DelAllItem(fp,CFGfile,del);
	}
	else {
		ans = ReadFile_item(fp, CFGfile, del, group_name, item_name, DelItem);
	}
	this->file_resize(0);
	Write(fp, CFGfile);
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name, const int item_value)
{
	//string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	//int ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, UpdItem);
	/*if (ans == -1) {  //说明没有Item，要添加
		string gname = "[" + (string)group_name + "]\n";
		UpdAddItem(CFGfile, gname, add);
	}*/
	
	string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans=1, issimp = IsSamplefile(fp, group_name);
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleUpd(fp, CFGfile, add, item_name))
			return 0;
	}
	else {
		if (!ReadFile_item(fp, CFGfile, add, group_name, item_name, ExiItem)) {//没有就添加
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, AddItem);
		}
		else {
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, UpdItem);
		}
	}
	
	this->file_resize(0);
	fp.clear();
	fp.seekg(0, ios::beg);
	fp << CFGfile;
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name, const double item_value)
{
	string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	//string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans=1;
	/*if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
	}
	if (!ReadFile_item(fp, CFGfile, add, group_name, item_name, ExiItem)) {//没有就添加
		ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, AddItem);
	}
	else {
		ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, UpdItem);
	}*/
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleUpd(fp, CFGfile, add, item_name))
			return 0;
	}
	else {
		if (!ReadFile_item(fp, CFGfile, add, group_name, item_name, ExiItem)) {//没有就添加
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, AddItem);
		}
		else {
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, UpdItem);
		}
	}
	this->file_resize(0);
	fp.clear();
	fp.seekg(0, ios::beg);
	fp << CFGfile << "\n";
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name, const char* item_value)
{
	string CFGfile = "", add = (string)item_name + " = " + string(item_value) + "\n";
	//string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans=1;
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleUpd(fp, CFGfile, add, item_name))
			return 0;
	}
	else {
		if (!ReadFile_item(fp, CFGfile, add, group_name, item_name, ExiItem)) {//没有就添加
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, AddItem);
		}
		else {
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, UpdItem);
		}
	}
	this->file_resize(0);
	fp.clear();
	fp.seekg(0, ios::beg);
	fp << CFGfile << "\n";
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name, const string &item_value)
{
	string CFGfile = "", add = (string)item_name + " = " + (item_value) + "\n";
	//string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans=1;
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleUpd(fp, CFGfile, add, item_name))
			return 0;
	}
	else {
		if (!ReadFile_item(fp, CFGfile, add, group_name, item_name, ExiItem)) {//没有就添加
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, AddItem);
		}
		else {
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, UpdItem);
		}
	}
	this->file_resize(0);
	fp.clear();
	fp.seekg(0, ios::beg);
	//fp << CFGfile << endl;
	fp << CFGfile << "\n";
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name, const char item_value)
{
	string CFGfile = "", add = (string)item_name + " = " + item_value + "\n";
	//string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans=1;
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleUpd(fp, CFGfile, add, item_name))
			return 0;
	}
	else {
		if (!ReadFile_item(fp, CFGfile, add, group_name, item_name, ExiItem)) {//没有就添加
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, AddItem);
		}
		else {
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, UpdItem);
		}
	}
	this->file_resize(0);
	fp.clear();
	fp.seekg(0, ios::beg);
	//fp << CFGfile << endl;
	fp << CFGfile << "\n";
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_update(const char* group_name, const char* item_name)
{
	string CFGfile = "", add = (string)item_name + " = " + "\n";
	//string CFGfile = "", add = (string)item_name + " = " + to_string(item_value) + "\n";
	int ans=1;
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
		else if (!ItemSimpleUpd(fp, CFGfile, add, item_name))
			return 0;
	}
	else {
		if (!ReadFile_item(fp, CFGfile, add, group_name, item_name, ExiItem)) {//没有就添加
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, AddItem);
		}
		else {
			ans = ReadFile_item(fp, CFGfile, add, group_name, item_name, UpdItem);
		}
	}
	this->file_resize(0);
	fp.clear();
	fp.seekg(0, ios::beg);
	fp << CFGfile << "\n";
	//fp << CFGfile << endl;
	return ans;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name, int &item_value)
{
	int mode = !IsSamplefile(fp, group_name);
	if (group_name == NULL) {
		if (mode==1)
			return 0;
	}
	string val = GetVal(fp, group_name, item_name, mode);
	//cout << val << endl;
	if (!val.length())
		return 0;
	DelSpaceOfHeadTail(val);//掐头去尾
	item_value = atoi(val.c_str());
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name, double& item_value)
{
	/*if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
	}
	string val = GetVal(fp, group_name, item_name);
	//cout << val << endl;
	if (!val.length())
		return 0;
	DelSpaceOfHeadTail(val);//掐头去尾
	item_value = atof(val.c_str());
	return 1;*/
	int mode = !IsSamplefile(fp, group_name);
	if (group_name == NULL) {
		if (mode == 1)
			return 0;
	}
	string val = GetVal(fp, group_name, item_name, mode);
	//cout << val << endl;
	if (!val.length())
		return 0;
	DelSpaceOfHeadTail(val);//掐头去尾
	item_value = atof(val.c_str());
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name, char *item_value)
{
	int mode = !IsSamplefile(fp, group_name) ;
	if (group_name == NULL) {
		if (mode == 1)
			return 0;
	}
	string val = GetVal(fp, group_name, item_name, mode);
	//cout << val << endl;
	if (!val.length())
		return 0;
	DelSpaceOfHeadTail(val);//掐头去尾
	strcpy(item_value,val.c_str());
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name, string &item_value)
{
	int mode = !IsSamplefile(fp, group_name);
	if (group_name == NULL) {
		if (mode == 1)
			return 0;
	}
	string val = GetVal(fp, group_name, item_name, mode);
	//cout << val << endl;
	if (!val.length())
		return 0;
	DelSpaceOfHeadTail(val);//掐头去尾
	item_value = val;
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name, char& item_value)
{
	int mode = !IsSamplefile(fp, group_name);
	if (group_name == NULL) {
		if (mode == 1)
			return 0;
	}
	string val = GetVal(fp, group_name, item_name, mode);
	//cout << val << endl;
	if (!val.length())
		return 0;
	DelSpaceOfHeadTail(val);//掐头去尾
	item_value = val[0];
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int CFT::item_get_value(const char* group_name, const char* item_name)
{
	if (group_name == NULL) {
		if (!IsSamplefile(fp, group_name))
			return 0;
	}
	return 1; //此句根据需要修改
}

