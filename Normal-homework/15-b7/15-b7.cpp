/* 1752846 边泽轩 车辆工程（汽车） */
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>
#include<fstream>

#ifdef linux
#include<dirent.h>
#include <sys/stat.h>
#else 
#include<io.h>
#endif
using namespace std; 

static void  Usage(const char* procname)
{
	cout << "Usage: " << procname << " --firstline | --courseid cid | --filename name/a"<< endl;
	cout << "--firstline    :首行检查" << endl;
	cout << "--courseid    :课号" << endl;
	cout << "filename     文件名（all表示全部）" << endl;
	cout << "e.g.   " << procname << " --firstline --courseid 100692 --filename 3-b1.cpp :检查100692课程的3-b1.cpp的首行" << endl;
	cout << "       " << procname << " --firstline --courseid 100692 --filename all      :检查100692课程的全部文件的首行" << endl;
	cout << endl;
}

static bool Match(string source_string, string target_string) //待检测行首与目标信息是否匹配
{
	string target_s[10];//储存目标串分解的四个部分
	string source_s[10];//储存源串分解的三个部分
	int sum = 0;
	int Is_match[4] = { 0 };
	
	for (int i = 0,j=0; i <= (int)target_string.length(); i++) {
		if ((int)target_string[i] == 9 || (int)target_string[i] == 32||target_string[i]=='\0') {
			target_s[sum++] = target_string.substr(j, i - j);
			while (i < (int)target_string.length() && (target_string[i] == '	' || target_string[i] == ' ')) 
				i++;
			j = i;
		}
	}
	sum = 0;
	for (int i = 0, j = 0; i <= (int)source_string.length(); i++) {
		if ((int)source_string[i] == 9 || (int)source_string[i] == 32 || source_string[i] == '\0') {
			source_s[sum++] = source_string.substr(j, i - j);
			while (i < (int)source_string.length() && (source_string[i] == '	' || source_string[i] == ' ')) {
				i++;
			}
			j = i;
		}
	}
	/*for (int i = 0; i < 3; i++) {
		cout << source_s[i] << endl;
	}*/
	if (sum > 3) {
		cout << "首行信息过多";
		return 0;
	}
	else if (sum < 3) {
		//cout << sum;
		cout << "首行信息不全";
		return 0;
	}
	//到这里保证source串只有3个信息
	for (int i = 0; i < sum; i++) {
		for (int j = 0; j < 4; j++) {
			if (source_s[i] == target_s[j])
				Is_match[j] = 1;
		}
	}
	int flag = 0;
	if (!Is_match[0]) {
		cout << "学号不匹配 ";
		flag = 1;
	}
	if (!Is_match[1]) {
		cout << "姓名不匹配 ";
		flag = 1;
	}
	if (!Is_match[2]&&!Is_match[3]) {
		cout << "班级不匹配 ";
		flag = 1;
	}
	if (flag) {
		//cout << endl;
		return 0;
	}
	return 1;
}

static string headtail(string s)//把待检测字符串行首尾的多余空格、符号去掉
{
	//先去空格
	int i0;
	for (i0 = 0; i0 < (int)s.length(); i0++) {
		if (s[i0] != ' ' && s[i0] != '	')
			break;
	}
	s = s.substr(i0);//掐头
	for (i0 = s.length() - 1; i0 >= 0; i0--) {
		if (s[i0] != ' ' && s[i0] != '	')
			break;
	}
	s = s.substr(0, i0 + 1);//去尾
	
	if (s[0] == '/' && s[1] == '/') //去符号 //
		s = s.substr(2);
	else 
		s = s.substr(2, s.length() - 4);//去符号 /**/
	int i = 0, j = s.length() - 1,sub;//头尾指针
	for (; i < j; ) {//去空格和tab
		sub = i - j;
		if (s[i] == 32 || s[i] == 9) 
			i++;
		if (s[j] == ' ' || s[j] == '	')
			j--;
		if (sub == i - j)
			break;
	}
	return 	s.substr(i, j - i + 1);
}

static bool Is_zhushi(string s)//判断是佛是注释，不是直接给出  “未收到首行信息”的提示
{
	int i;
	for (i= 0; i < (int)s.length(); i++) {
		if (s[i] != ' ' && s[i] != '	')
			break;
	}
	s = s.substr(i);//掐头
	for (i = s.length() - 1; i >= 0; i--) {
		if (s[i] != ' ' && s[i] != '	')
			break;
	}
	s = s.substr(0, i + 1);//去尾
	//cout<<"+"<<s<<"+"<<endl;
	if (s.length() < 2){
		return 0;
	}
	if ((s[0] == '/' && s[1] == '/'))
		return 1;
	if ((int)s.length() >= 4 && s[0] == '/' && s[1] == '*' &&
		s[(int)s.length() - 1] == '/' && s[(int)s.length() - 2] == '*')
		return 1;

	return 0;
}

void Check(string route,string target_str,string filename)     //
{
	//格式化target_str为输出形式
	string target_str_out;
	for (int i = 0,j=0,sum=0; i < (int)target_str.length()&&sum<3; i++) {
		if (target_str[i] == ' ' || target_str[i] == '	') {
			target_str_out += target_str.substr(j,i-j);
			j = i + 1;
			sum++;
			if (sum != 3)
				target_str_out += '-';
		}
	}
	cout << target_str_out << " : " << filename << " : ";

	ifstream infile_homework;
	infile_homework.open(route, ios::in|ios::binary);
	string source_str;
	if (!infile_homework.is_open()) {
		//说明不存在文件
		cout << "未提交";
		return;
	}
	
	while (infile_homework.peek() != EOF) {
		getline(infile_homework, source_str);
		source_str = source_str.substr(0, source_str.length() - 1);
		if (source_str.length() == 0) //排出空行
			continue;
		for (int i = 0; source_str.length() != 0; i++) {         //排除前面的空格或者tab
			if (source_str[0] == ' ' || source_str[0] == '	')
				source_str = source_str.substr(1);
			else
				break;
		}
		if(source_str.length()!=0)
			break;//找到第一行就可退出了
	}
	
	if (!Is_zhushi(source_str)) {
		cout << "未收到首行信息";
		return;
	}
	source_str = headtail(source_str);
	//cout << source_str << "---";
	if (Match(source_str, target_str))
		cout << "通过" ;
}

void sort(int *id,int end)
{
	int min = 0, imin = 0;
	for (int i = 0; i < end; i++) {
		min = id[i];
		imin = i;
		for (int j = i + 1; j < end; j++) {
			if (min > id[j]) {
				min = id[j];
				imin = j;
			}
		}
		swap(id[i], id[imin]);
	}
}

int ReadFile(string courseid, string filename)//将名单中学号排序，进入对应目录找
{
	ifstream infile_courseid, infile_filename;
	string courseid_filename = "./source/" + courseid + ".dat";
	string target_s, route;
	int ID[50] = { 0 };
	infile_courseid.open(courseid_filename, ios::in);
	if (!infile_courseid.is_open()) {
		cout << "无法打开" << courseid_filename << endl;
		return 0;
	}
	int num = 0;
	while (infile_courseid.peek() != EOF) {
		getline(infile_courseid, target_s);
		ID[num++] = atoi(target_s.substr(0, 7).c_str());
	}
	infile_courseid.close();
	sort(ID, num);//对学号排序
	
	
#ifdef linux //Linux下利用dirent结构
	struct dirent* file_sub;
	//	DIR* pDir;
	route = "./source/";//某门课程+学号对于的文件夹名称
	string route_sub, id, route_find, route_sub_find;//find是在某位添加了通配符的
	route_find = route;
	
	for (int i = 0; i < num; i++) {
		route_sub = route + courseid + "-" + to_string(ID[i]) + "/";
		infile_courseid.open(courseid_filename, ios::in|ios::binary);
		if (!infile_courseid.is_open()) {
			//cout << "无法打开" << courseid_filename << endl;
			return 0;
		}
		while (infile_courseid.peek() != EOF) {
			getline(infile_courseid, target_s);
			target_s = target_s.substr(0, target_s.length() - 1);
			if (target_s.substr(0, 7) == to_string(ID[i])) {
				break;
			}
		}
		infile_courseid.close();

		//寻找子目录下文件
		if (filename == "all")
			route_sub_find = route_sub;
		else
			route_sub_find = route_sub + filename;//指定文件
		if (filename == "all") {
			DIR* pDir_sub = opendir(route_sub_find.c_str());
			if (pDir_sub == NULL) {
				continue;
			}
			while ((file_sub = readdir(pDir_sub)) != NULL) {
				if (strstr(file_sub->d_name, ".cpp") == NULL
					&& strstr(file_sub->d_name, ".c") == NULL
					&& strstr(file_sub->d_name, ".h") == NULL)
					continue;//不是源文件
				Check(route_sub + file_sub->d_name, target_s, file_sub->d_name);//route_sbu+find_sub.name是文件路径，target_s是从名单中获取的信息
				//cout<<file_sub->d_name<<endl;
				//cout<<target_s<<endl;
				cout << endl;
			}
			closedir(pDir_sub);
		}
		else
			Check(route_sub + filename, target_s, filename);
		cout << endl;
	}
	
	
#else
	long hand_sub;
	struct _finddata_t  find_sub;
	route = "./source/";//某门课程+学号对于的文件夹名称
	string route_sub, route_sub_find;//find是在某位添加了通配符的

	for (int i = 0; i < num; i++) {
		route_sub = route + courseid + "-" + to_string(ID[i]) + "/";
		infile_courseid.open(courseid_filename, ios::in);
		if (!infile_courseid.is_open()) {
			//cout << "无法打开" << courseid_filename << endl;
			return 0;
		}
		while (infile_courseid.peek() != EOF) {
			getline(infile_courseid, target_s);
			if (target_s.substr(0, 7) == to_string(ID[i])) {
				break;
			}
		}
		infile_courseid.close();
		if (filename == "all")
			route_sub_find = route_sub + "*.*";
		else
			route_sub_find = route_sub + filename;//指定文件
		if (filename == "all") {
			if ((hand_sub = _findfirst(route_sub_find.c_str(), &find_sub)) == -1)
				continue;
			do {
				if (strstr(find_sub.name, ".cpp") == NULL
					&& strstr(find_sub.name, ".c") == NULL
					&& strstr(find_sub.name, ".h") == NULL)
					continue;//不是源文件
				Check(route_sub + find_sub.name, target_s, find_sub.name);//route_sbu+find_sub.name是文件路径，target_s是从名单中获取的信息
				cout << endl;
				//cout << route_sub+find_sub.name << endl;
				//cout << target_s << endl;
			} while (!_findnext(hand_sub, &find_sub));
			_findclose(hand_sub);
		}
		else
			Check(route_sub + filename, target_s, filename);//指定文件名时
		cout << endl;
	}
#endif
	return 1;
}

int ReadFile0(string courseid, string filename)//逐个打开每个子目录，以及子目录下的文件，判断是否在名单中
{
	ifstream infile_courseid, infile_filename;
	string courseid_filename = "./source/" + courseid + ".dat";
	string target_s,route;
	
	/*开始误会题意以为要以目录名学号为基准，去名单中中有没有对应的学号。。因此利用dirent（linux）和finddata(windows)*/
#ifdef linux //Linux下利用dirent结构
	struct dirent* file,*file_sub;
//	DIR* pDir;
	route = "./source/";//某门课程+学号对于的文件夹名称
	string route_sub, id, route_find, route_sub_find;//find是在某位添加了通配符的
	route_find = route ;
	DIR * pDir=opendir(route_find.c_str());
	if (pDir ==NULL){
		//cout<<"can't open"<<endl;
		return 0;
	}
//	cout<<"?";
	while ((file = readdir(pDir)) != NULL) {
		//	cout<<file->d_name<<endl;
		if (file->d_type == 4) {
			if (strcmp(file->d_name, ".") && strcmp(file->d_name, "..")) {
				route_sub = route + file->d_name + "/";
				id = file->d_name;
				id = id.substr(7);
				//		cout << file->d_name << endl;
			}
			else
				continue;
		}
		else
			continue;
		int flag = 0;
		infile_courseid.open(courseid_filename, ios::in|ios::binary);
		if (!infile_courseid.is_open()) {
			cout << "无法打开" << courseid_filename << endl;
			return 0;
		}
		while (infile_courseid.peek() != EOF) {
			getline(infile_courseid, target_s);
			target_s = target_s.substr(0, target_s.length() - 1);
			if (target_s.substr(0, 7) == id) {
				flag = 1;
				break;
			}
		}
		infile_courseid.close();
		if (!flag)//如果不在名单中，就不用找了
			continue;

		//寻找子目录下文件
		if (filename == "all")
			route_sub_find = route_sub;
		else
			route_sub_find = route_sub + filename;//指定文件
		if (filename == "all") {
			DIR* pDir_sub = opendir(route_sub_find.c_str());
			if (pDir_sub == NULL) {
				continue;
			}
			while ((file_sub = readdir(pDir_sub)) != NULL) {
				if (strstr(file_sub->d_name, ".cpp") == NULL
					&& strstr(file_sub->d_name, ".c") == NULL
					&& strstr(file_sub->d_name, ".h") == NULL)
					continue;//不是源文件
				Check(route_sub + file_sub->d_name, target_s, file_sub->d_name);//route_sbu+find_sub.name是文件路径，target_s是从名单中获取的信息
				//cout<<file_sub->d_name<<endl;
				//cout<<target_s<<endl;
				cout << endl;
			}
			closedir(pDir_sub);
		}
		else
			Check(route_sub + filename, target_s, filename);
		cout << endl;
	}
	closedir(pDir);

#else//windows下
	long hand, hand_sub;
	struct _finddata_t find, find_sub;
	//先打开一个一个子目录。。
	route = "./source/";//某门课程+学号对于的文件夹名称
	string route_sub, id, route_find, route_sub_find;//find是在某位添加了通配符的
	route_find = route + "*";
	//cout << route_find << endl;
	//getchar();
	if ((hand = _findfirst(route_find.c_str(), &find)) == -1)
		return 0;
	do {
		if (find.attrib == _A_SUBDIR) {   //这里实际上应该用递归dfs把所有文件名找到。。。
			if (strcmp(find.name, ".") && strcmp(find.name, "..")) {
				route_sub = route + find.name + "/";
				id = find.name;
				id = id.substr(7);
				//cout << id << endl;
			}
			else
				continue;
		}
		else
			continue;

		//判断在不在名单中
		int flag = 0;
		infile_courseid.open(courseid_filename, ios::in);
		if (!infile_courseid.is_open()) {
			cout << "无法打开" << courseid_filename << endl;
			return 0;
		}
		while (infile_courseid.peek() != EOF) {
			getline(infile_courseid, target_s);
			if (target_s.substr(0, 7) == id) {
				flag = 1;
				break;
			}
		}
		infile_courseid.close();
		if (!flag)//如果不在名单中，就不用找了
			continue;

		//寻找子目录下文件
		if (filename == "all")
			route_sub_find = route_sub + "*.*";
		else
			route_sub_find = route_sub + filename;//指定文件
		if (filename == "all") {
			if ((hand_sub = _findfirst(route_sub_find.c_str(), &find_sub)) == -1)
				continue;
			do {
				if (strstr(find_sub.name, ".cpp") == NULL
					&& strstr(find_sub.name, ".c") == NULL
					&& strstr(find_sub.name, ".h") == NULL)
					continue;//不是源文件

				//route_sub += find_sub.name;
				Check(route_sub + find_sub.name, target_s, find_sub.name);//route_sbu+find_sub.name是文件路径，target_s是从名单中获取的信息
				cout << endl;
				//cout << route_sub+find_sub.name << endl;
			} while (!_findnext(hand_sub, &find_sub));
			_findclose(hand_sub);
		}
		else
			Check(route_sub + filename, target_s, filename);
		cout << endl;
	} while (!_findnext(hand, &find));
	_findclose(hand);
#endif

	return 1;
}

int main(int argc,char **argv)
{
	if (argc == 1)
		Usage(argv[0]);
	string para[3] = { "--firstline","--courseid","--filename"};
	string option[3];//读入参数值
	int Bool[3] = { 0 },Continue=0,flag=0;
	for (int i = 1; i < argc; i++) {
		flag = 0;
		if (Continue) { //是读取的参数值而不是参数名
			if (strlen(argv[i]) >= 2 && argv[i][0] == '-' && argv[i][1] == '-') {
				cout << "参数[" << argv[i-1] << "]缺少附加参数。(类型string)" << endl;
				return 0;
			}
			option[Continue] = argv[i];
			Continue = 0;
			continue;
		}
		for (int j = 0; j < 3; j++) {
			if (argv[i] == para[j]) {
				if (Bool[j]) {
					cout << "参数[" << para[j] << "]重复" << endl;
					return 0;
				}
				flag = 1;
				Bool[j] = 1;
				if (j > 0)
					Continue = j;
			}
		}
		if (!flag) {
			cout << "参数[" << argv[i] << "]非法" << endl;
			return 0;
		}
	}
	if (Continue) {
		if (strlen(argv[argc-1]) >= 2 && argv[argc-1][0] == '-' && argv[argc-1][1] == '-') {
			cout << "参数[" << argv[argc-1] << "]缺少附加参数。(类型string)" << endl;
			return 0;
		}
	}
	
	//判断参数是否缺少
	for (int i = 0; i < 3; i++) {
		if (!Bool[i]) {
			Usage(argv[0]);
			cout << "必须指定参数[" << para[i] << "]" << endl;
			return 0;
		}
	}

	//判断filename是否是源程序文件,至于能不能打开放到读文件的地方判断
	if (option[2] != "all") {
		if (option[2].length() < 2) {
			cout << "不是源程序文件" << endl;
			return 0;
		}
		else if (option[2].length() == 2 || option[2].length() == 3) {
			if ((option[2][option[2].length() - 1] == 'h' && option[2][option[2].length() - 2] == '.')
				|| (option[2][option[2].length() - 1] == 'c' && option[2][option[2].length() - 2] == '.'));
			else {
				cout << "不是源程序文件" << endl;
				return 0;
			}
		}
		else if (option[2].length() > 3) {
			if ((option[2][option[2].length() - 1] == 'h' && option[2][option[2].length() - 2] == '.')
				|| (option[2][option[2].length() - 1] == 'c' && option[2][option[2].length() - 2] == '.')
				|| (option[2][option[2].length() - 1] == 'p' && option[2][option[2].length() - 2] == 'p'
					&& option[2][option[2].length() - 3] == 'c' && option[2][option[2].length() - 4] == '.'));
			else {
				cout << "不是源程序文件" << endl;
				return 0;
			}
		}
	}


	if (!ReadFile(option[1], option[2]))//也就是courseid和filename；
		return 1;
	
	return 0;
}
