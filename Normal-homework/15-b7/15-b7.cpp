/* 1752846 ������ �������̣������� */
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
	cout << "--firstline    :���м��" << endl;
	cout << "--courseid    :�κ�" << endl;
	cout << "filename     �ļ�����all��ʾȫ����" << endl;
	cout << "e.g.   " << procname << " --firstline --courseid 100692 --filename 3-b1.cpp :���100692�γ̵�3-b1.cpp������" << endl;
	cout << "       " << procname << " --firstline --courseid 100692 --filename all      :���100692�γ̵�ȫ���ļ�������" << endl;
	cout << endl;
}

static bool Match(string source_string, string target_string) //�����������Ŀ����Ϣ�Ƿ�ƥ��
{
	string target_s[10];//����Ŀ�괮�ֽ���ĸ�����
	string source_s[10];//����Դ���ֽ����������
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
		cout << "������Ϣ����";
		return 0;
	}
	else if (sum < 3) {
		//cout << sum;
		cout << "������Ϣ��ȫ";
		return 0;
	}
	//�����ﱣ֤source��ֻ��3����Ϣ
	for (int i = 0; i < sum; i++) {
		for (int j = 0; j < 4; j++) {
			if (source_s[i] == target_s[j])
				Is_match[j] = 1;
		}
	}
	int flag = 0;
	if (!Is_match[0]) {
		cout << "ѧ�Ų�ƥ�� ";
		flag = 1;
	}
	if (!Is_match[1]) {
		cout << "������ƥ�� ";
		flag = 1;
	}
	if (!Is_match[2]&&!Is_match[3]) {
		cout << "�༶��ƥ�� ";
		flag = 1;
	}
	if (flag) {
		//cout << endl;
		return 0;
	}
	return 1;
}

static string headtail(string s)//�Ѵ�����ַ�������β�Ķ���ո񡢷���ȥ��
{
	//��ȥ�ո�
	int i0;
	for (i0 = 0; i0 < (int)s.length(); i0++) {
		if (s[i0] != ' ' && s[i0] != '	')
			break;
	}
	s = s.substr(i0);//��ͷ
	for (i0 = s.length() - 1; i0 >= 0; i0--) {
		if (s[i0] != ' ' && s[i0] != '	')
			break;
	}
	s = s.substr(0, i0 + 1);//ȥβ
	
	if (s[0] == '/' && s[1] == '/') //ȥ���� //
		s = s.substr(2);
	else 
		s = s.substr(2, s.length() - 4);//ȥ���� /**/
	int i = 0, j = s.length() - 1,sub;//ͷβָ��
	for (; i < j; ) {//ȥ�ո��tab
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

static bool Is_zhushi(string s)//�ж��Ƿ���ע�ͣ�����ֱ�Ӹ���  ��δ�յ�������Ϣ������ʾ
{
	int i;
	for (i= 0; i < (int)s.length(); i++) {
		if (s[i] != ' ' && s[i] != '	')
			break;
	}
	s = s.substr(i);//��ͷ
	for (i = s.length() - 1; i >= 0; i--) {
		if (s[i] != ' ' && s[i] != '	')
			break;
	}
	s = s.substr(0, i + 1);//ȥβ
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
	//��ʽ��target_strΪ�����ʽ
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
		//˵���������ļ�
		cout << "δ�ύ";
		return;
	}
	
	while (infile_homework.peek() != EOF) {
		getline(infile_homework, source_str);
		source_str = source_str.substr(0, source_str.length() - 1);
		if (source_str.length() == 0) //�ų�����
			continue;
		for (int i = 0; source_str.length() != 0; i++) {         //�ų�ǰ��Ŀո����tab
			if (source_str[0] == ' ' || source_str[0] == '	')
				source_str = source_str.substr(1);
			else
				break;
		}
		if(source_str.length()!=0)
			break;//�ҵ���һ�оͿ��˳���
	}
	
	if (!Is_zhushi(source_str)) {
		cout << "δ�յ�������Ϣ";
		return;
	}
	source_str = headtail(source_str);
	//cout << source_str << "---";
	if (Match(source_str, target_str))
		cout << "ͨ��" ;
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

int ReadFile(string courseid, string filename)//��������ѧ�����򣬽����ӦĿ¼��
{
	ifstream infile_courseid, infile_filename;
	string courseid_filename = "./source/" + courseid + ".dat";
	string target_s, route;
	int ID[50] = { 0 };
	infile_courseid.open(courseid_filename, ios::in);
	if (!infile_courseid.is_open()) {
		cout << "�޷���" << courseid_filename << endl;
		return 0;
	}
	int num = 0;
	while (infile_courseid.peek() != EOF) {
		getline(infile_courseid, target_s);
		ID[num++] = atoi(target_s.substr(0, 7).c_str());
	}
	infile_courseid.close();
	sort(ID, num);//��ѧ������
	
	
#ifdef linux //Linux������dirent�ṹ
	struct dirent* file_sub;
	//	DIR* pDir;
	route = "./source/";//ĳ�ſγ�+ѧ�Ŷ��ڵ��ļ�������
	string route_sub, id, route_find, route_sub_find;//find����ĳλ�����ͨ�����
	route_find = route;
	
	for (int i = 0; i < num; i++) {
		route_sub = route + courseid + "-" + to_string(ID[i]) + "/";
		infile_courseid.open(courseid_filename, ios::in|ios::binary);
		if (!infile_courseid.is_open()) {
			//cout << "�޷���" << courseid_filename << endl;
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

		//Ѱ����Ŀ¼���ļ�
		if (filename == "all")
			route_sub_find = route_sub;
		else
			route_sub_find = route_sub + filename;//ָ���ļ�
		if (filename == "all") {
			DIR* pDir_sub = opendir(route_sub_find.c_str());
			if (pDir_sub == NULL) {
				continue;
			}
			while ((file_sub = readdir(pDir_sub)) != NULL) {
				if (strstr(file_sub->d_name, ".cpp") == NULL
					&& strstr(file_sub->d_name, ".c") == NULL
					&& strstr(file_sub->d_name, ".h") == NULL)
					continue;//����Դ�ļ�
				Check(route_sub + file_sub->d_name, target_s, file_sub->d_name);//route_sbu+find_sub.name���ļ�·����target_s�Ǵ������л�ȡ����Ϣ
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
	route = "./source/";//ĳ�ſγ�+ѧ�Ŷ��ڵ��ļ�������
	string route_sub, route_sub_find;//find����ĳλ�����ͨ�����

	for (int i = 0; i < num; i++) {
		route_sub = route + courseid + "-" + to_string(ID[i]) + "/";
		infile_courseid.open(courseid_filename, ios::in);
		if (!infile_courseid.is_open()) {
			//cout << "�޷���" << courseid_filename << endl;
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
			route_sub_find = route_sub + filename;//ָ���ļ�
		if (filename == "all") {
			if ((hand_sub = _findfirst(route_sub_find.c_str(), &find_sub)) == -1)
				continue;
			do {
				if (strstr(find_sub.name, ".cpp") == NULL
					&& strstr(find_sub.name, ".c") == NULL
					&& strstr(find_sub.name, ".h") == NULL)
					continue;//����Դ�ļ�
				Check(route_sub + find_sub.name, target_s, find_sub.name);//route_sbu+find_sub.name���ļ�·����target_s�Ǵ������л�ȡ����Ϣ
				cout << endl;
				//cout << route_sub+find_sub.name << endl;
				//cout << target_s << endl;
			} while (!_findnext(hand_sub, &find_sub));
			_findclose(hand_sub);
		}
		else
			Check(route_sub + filename, target_s, filename);//ָ���ļ���ʱ
		cout << endl;
	}
#endif
	return 1;
}

int ReadFile0(string courseid, string filename)//�����ÿ����Ŀ¼���Լ���Ŀ¼�µ��ļ����ж��Ƿ���������
{
	ifstream infile_courseid, infile_filename;
	string courseid_filename = "./source/" + courseid + ".dat";
	string target_s,route;
	
	/*��ʼ���������ΪҪ��Ŀ¼��ѧ��Ϊ��׼��ȥ����������û�ж�Ӧ��ѧ�š����������dirent��linux����finddata(windows)*/
#ifdef linux //Linux������dirent�ṹ
	struct dirent* file,*file_sub;
//	DIR* pDir;
	route = "./source/";//ĳ�ſγ�+ѧ�Ŷ��ڵ��ļ�������
	string route_sub, id, route_find, route_sub_find;//find����ĳλ�����ͨ�����
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
			cout << "�޷���" << courseid_filename << endl;
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
		if (!flag)//������������У��Ͳ�������
			continue;

		//Ѱ����Ŀ¼���ļ�
		if (filename == "all")
			route_sub_find = route_sub;
		else
			route_sub_find = route_sub + filename;//ָ���ļ�
		if (filename == "all") {
			DIR* pDir_sub = opendir(route_sub_find.c_str());
			if (pDir_sub == NULL) {
				continue;
			}
			while ((file_sub = readdir(pDir_sub)) != NULL) {
				if (strstr(file_sub->d_name, ".cpp") == NULL
					&& strstr(file_sub->d_name, ".c") == NULL
					&& strstr(file_sub->d_name, ".h") == NULL)
					continue;//����Դ�ļ�
				Check(route_sub + file_sub->d_name, target_s, file_sub->d_name);//route_sbu+find_sub.name���ļ�·����target_s�Ǵ������л�ȡ����Ϣ
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

#else//windows��
	long hand, hand_sub;
	struct _finddata_t find, find_sub;
	//�ȴ�һ��һ����Ŀ¼����
	route = "./source/";//ĳ�ſγ�+ѧ�Ŷ��ڵ��ļ�������
	string route_sub, id, route_find, route_sub_find;//find����ĳλ�����ͨ�����
	route_find = route + "*";
	//cout << route_find << endl;
	//getchar();
	if ((hand = _findfirst(route_find.c_str(), &find)) == -1)
		return 0;
	do {
		if (find.attrib == _A_SUBDIR) {   //����ʵ����Ӧ���õݹ�dfs�������ļ����ҵ�������
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

		//�ж��ڲ���������
		int flag = 0;
		infile_courseid.open(courseid_filename, ios::in);
		if (!infile_courseid.is_open()) {
			cout << "�޷���" << courseid_filename << endl;
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
		if (!flag)//������������У��Ͳ�������
			continue;

		//Ѱ����Ŀ¼���ļ�
		if (filename == "all")
			route_sub_find = route_sub + "*.*";
		else
			route_sub_find = route_sub + filename;//ָ���ļ�
		if (filename == "all") {
			if ((hand_sub = _findfirst(route_sub_find.c_str(), &find_sub)) == -1)
				continue;
			do {
				if (strstr(find_sub.name, ".cpp") == NULL
					&& strstr(find_sub.name, ".c") == NULL
					&& strstr(find_sub.name, ".h") == NULL)
					continue;//����Դ�ļ�

				//route_sub += find_sub.name;
				Check(route_sub + find_sub.name, target_s, find_sub.name);//route_sbu+find_sub.name���ļ�·����target_s�Ǵ������л�ȡ����Ϣ
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
	string option[3];//�������ֵ
	int Bool[3] = { 0 },Continue=0,flag=0;
	for (int i = 1; i < argc; i++) {
		flag = 0;
		if (Continue) { //�Ƕ�ȡ�Ĳ���ֵ�����ǲ�����
			if (strlen(argv[i]) >= 2 && argv[i][0] == '-' && argv[i][1] == '-') {
				cout << "����[" << argv[i-1] << "]ȱ�ٸ��Ӳ�����(����string)" << endl;
				return 0;
			}
			option[Continue] = argv[i];
			Continue = 0;
			continue;
		}
		for (int j = 0; j < 3; j++) {
			if (argv[i] == para[j]) {
				if (Bool[j]) {
					cout << "����[" << para[j] << "]�ظ�" << endl;
					return 0;
				}
				flag = 1;
				Bool[j] = 1;
				if (j > 0)
					Continue = j;
			}
		}
		if (!flag) {
			cout << "����[" << argv[i] << "]�Ƿ�" << endl;
			return 0;
		}
	}
	if (Continue) {
		if (strlen(argv[argc-1]) >= 2 && argv[argc-1][0] == '-' && argv[argc-1][1] == '-') {
			cout << "����[" << argv[argc-1] << "]ȱ�ٸ��Ӳ�����(����string)" << endl;
			return 0;
		}
	}
	
	//�жϲ����Ƿ�ȱ��
	for (int i = 0; i < 3; i++) {
		if (!Bool[i]) {
			Usage(argv[0]);
			cout << "����ָ������[" << para[i] << "]" << endl;
			return 0;
		}
	}

	//�ж�filename�Ƿ���Դ�����ļ�,�����ܲ��ܴ򿪷ŵ����ļ��ĵط��ж�
	if (option[2] != "all") {
		if (option[2].length() < 2) {
			cout << "����Դ�����ļ�" << endl;
			return 0;
		}
		else if (option[2].length() == 2 || option[2].length() == 3) {
			if ((option[2][option[2].length() - 1] == 'h' && option[2][option[2].length() - 2] == '.')
				|| (option[2][option[2].length() - 1] == 'c' && option[2][option[2].length() - 2] == '.'));
			else {
				cout << "����Դ�����ļ�" << endl;
				return 0;
			}
		}
		else if (option[2].length() > 3) {
			if ((option[2][option[2].length() - 1] == 'h' && option[2][option[2].length() - 2] == '.')
				|| (option[2][option[2].length() - 1] == 'c' && option[2][option[2].length() - 2] == '.')
				|| (option[2][option[2].length() - 1] == 'p' && option[2][option[2].length() - 2] == 'p'
					&& option[2][option[2].length() - 3] == 'c' && option[2][option[2].length() - 4] == '.'));
			else {
				cout << "����Դ�����ļ�" << endl;
				return 0;
			}
		}
	}


	if (!ReadFile(option[1], option[2]))//Ҳ����courseid��filename��
		return 1;
	
	return 0;
}
