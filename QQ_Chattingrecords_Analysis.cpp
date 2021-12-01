#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;

const int mon1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const int mon2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
bool Is_time(string s);//声明
class Time
{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
public:
	Time();
	Time(string);
	bool operator >=(const Time&);
	bool operator <=(const Time&);
	//void show();
};

Time::Time()
{
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(string s)
{
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	minute = 0;
	second = 0;
	
	if(Is_time(s)) {
		sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	}
}

bool Time::operator<=(const Time& t1)
{
	if (year > t1.year)
		return 0;
	else if (year < t1.year)
		return 1;
	
	if (month > t1.month)
		return 0;
	else if (month < t1.month)
		return 1;

	if (day > t1.day)
		return 0;
	else if (day < t1.day)
		return 1;

	if (hour > t1.hour)
		return 0;
	else if (hour < t1.hour)
		return 1;

	if (minute > t1.minute)
		return 0;
	else if (minute < t1.minute)
		return 1;

	if (second > t1.second)
		return 0;
	else
		return 1;
}
bool Time::operator>=(const Time& t1)
{
	if (year < t1.year)
		return 0;
	else if (year > t1.year)
		return 1;

	if (month < t1.month)
		return 0;
	else if (month > t1.month)
		return 1;

	if (day < t1.day)
		return 0;
	else if (day > t1.day)
		return 1;

	if (hour < t1.hour)
		return 0;
	else if (hour > t1.hour)
		return 1;

	if (minute < t1.minute)
		return 0;
	else if (minute > t1.minute)
		return 1;

	if (second < t1.second)
		return 0;
	else
		return 1;
}


static void usage(const char* procname, const int arg_num)
{
	const char* recname_def = "21221-面向对象(2020级).txt";
	const char* recname_new = "21221-面向对象(2020级)-1.txt";
	const char* listname_def = "stulist.txt";
	const char* listname_new = "list1.txt";
	const char* time_begin = "2021-10-30 10:00:00";
	const char* time_end = "2021-10-30 11:59:59";
	const char* stu_no = "2051234";

	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	cout << "Usage: " << procname << " { --stulist | --qq_record | --begin | --end | {--stuno} | {--only_zero} }" << endl;
	cout << endl;
	cout << setw(wkey) << ' ' << "必选项：" << endl;
	cout << setw(wopt) << ' ' << "--stulist filename   : 学生列表文件名(缺省:" << listname_def << ")" << endl;
	cout << setw(wopt) << ' ' << "--qq_record filename : 导出的聊天记录文件名(缺省:" << recname_def << ")" << endl;
	cout << setw(wopt) << ' ' << "--begin timestr      : 起始时间(时间串格式为yyyy-mm-dd hh:mm:ss，加引号)" << endl;
	cout << setw(wopt) << ' ' << "--end timestr        : 结束时间(时间串格式为yyyy-mm-dd hh:mm:ss，加引号)" << endl;
	cout << setw(wopt) << ' ' << "注：未检查时间串正确性" << endl;
	cout << setw(wkey) << ' ' << "可选项：" << endl;
	cout << setw(wopt) << ' ' << "--stuno stuno        : 指定某个学生(无此选项则全部学生)" << endl;
	cout << setw(wopt) << ' ' << "--only_zero          : 仅显示0发言学生(指定--stuno时本项无效)" << endl;
	cout << setw(wopt) << ' ' << "--more_than_zero     : 仅显示有发言学生(指定--stuno时本项无效，且与--only_zero互斥)" << endl;
	cout << endl;

	cout << "e.g.  " << procname << " --begin \"" << time_begin << "\" --end \"" << time_end << "\"" << endl;
	cout << setw(wkey) << "                               : 统计[" << recname_def << "]中在[" << listname_def << "]列表中的学生在[" << time_begin << "~" << time_end << "]间的发言数量" << endl;
	cout << "      " << procname << " --begin \"" << time_begin << "\" --end \"" << time_end << "\" --only_zero" << endl;
	cout << setw(wkey) << "                               : 统计[" << recname_def << "]中在[" << listname_def << "]列表中的学生在[" << time_begin << "~" << time_end << "]间所有0发言的学生" << endl;
	cout << "      " << procname << " --begin \"" << time_begin << "\" --end \"" << time_end << "\" --stuno " << stu_no << endl;
	cout << setw(wkey) << "                               : 统计[" << recname_def << "]中在[" << listname_def << "]列表中的学生" << stu_no << "在[" << time_begin << "~" << time_end << "]间的发言数量" << endl;
	cout << "      " << procname << " --stulist " << listname_new << " --qq_record " << recname_new << " --begin \"" << time_begin << "\" --end \"" << time_end << "\"" << endl;
	cout << setw(wkey) << "                               : 统计[" << recname_new << "'中在[" << listname_new << "]列表中的学生在[" << time_begin << "~" << time_end << "]间的发言数量" << endl;
	cout << "      " << procname << " --stulist " << listname_new << " --qq_record " << recname_new << " --begin \"" << time_begin << "\" --end \"" << time_end << "\" --only_zero" << endl;
	cout << setw(wkey) << "                               : 统计[" << recname_new << "'中在[" << listname_new << "]列表中的学生在[" << time_begin << "~" << time_end << "]间所有0发言的学生" << endl;
	cout << "      " << procname << " --stulist " << listname_new << " --qq_record " << recname_new << " --begin \"" << time_begin << "\" --end \"" << time_end << "\" --more_than_zero" << endl;
	cout << setw(wkey) << "                               : 统计[" << recname_new << "'中在[" << listname_new << "]列表中的学生在[" << time_begin << "~" << time_end << "]间所有0发言的学生" << endl;
	cout << "      " << procname << " --stulist " << listname_new << " --qq_record " << recname_new << " --begin \"" << time_begin << "\" --end \"" << time_end << "\" --stuno " << stu_no << endl;
	cout << setw(wkey) << "                               : 统计[" << recname_new << "]中在[" << listname_new << "]列表中的学生" << stu_no << "在[" << time_begin << "~" << time_end << "]间的发言数量" << endl;
	cout << endl;
}

bool Is_run(int year)//判断闰年
{
	return (year % 400 == 0 || (year % 4 == 0 && year % 100));
}

bool Is_days(int year, int month,int days)//判断日期是否合法
{
	if (Is_run(year))
		return days <= mon2[month - 1];
	return days <= mon1[month - 1];
}

bool Is_time(string s)//日期格式是否合法
{
	int space=0,i=0;
	//日期检查
	for (i = 0; i < (int)s.length(); i++) {
		if (i < 4 && i >= 0) {
			if (s[i] > '9' || s[i] < '0')
				return 0;
		}
		if (i==4&&s[i] != '-')
			return 0;
		if (i > 5 && s[i] == '-') {
			if (atoi(s.substr(5, i - 5).c_str()) < 0) {
				return 0;
			}
		}
		if (i >= 8 && s[i] == ' ') {
			space = 1;
			break;
		}
	}
	if (!space)
		return 0;
	//时间检查
	i++;
	for (int j = 0,old=-1; j +i< (int)s.length();j++) {
		if ((s[j+i] > '9' || s[j+i] < '0') && (s[j+i] != ':'))
			return 0;
		if ( s[j+i] == ':') {
			if (j ==old||j-old==1)
				return 0;
			old = j;
		}
	}
	
	int data[6] = { -1 };//分别对应year,month,day,hour,minute,second
	sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", data, data+1, data+2, data+3, data+4, data+5);
	
	if (data[0] > 2021 || data[0] < 1998)
		return 0;
	if (data[1] > 12 || data[1] < 1)
		return 0;
	if (data[2] < 1 || data[2]>31)
		return 0;

	if (!Is_days(data[0], data[1], data[2])){
		return 0;
	}
	
	if (data[3] < 0 || data[3]>=24)
		return 0;
	if (data[4] < 0 || data[4]>=60)
		return 0;
	if (data[5] < 0 || data[5]>=60)
		return 0;
	return 1;
}

int ReadFile(string stulist,string qqrecord,Time& b,Time& e, int stuno, int only_zero, int more_than_zero)
{
	ifstream infile_stulist,infile_qqrecord;
	infile_qqrecord.open(qqrecord, ios::in | ios::binary);
	int* Map = new int[100000]();//记录stulist中的学号，只取2、4、5、6、7位，

	if (!infile_qqrecord.is_open()) {
		cout << "Read-<QQRECORD>-Error!" << endl;
		return 0;
	}

	int num = 0,type=1,flag=0;
	int begin_h = 0, end_h = 0, not_in_list = 0,in_list=0;
	string s,id;
	while (infile_qqrecord.peek()!=EOF) {
		type = 1;
		getline(infile_qqrecord, s);
		num++;//总行数
		if (Is_time(s.substr(0, 19))) {
			type = 0;
			if (Time(s.substr(0, 19)) >= b && Time(s.substr(0, 19)) <= e) {//选取指定范围内的时间，转换成Time类型进行比较
				not_in_list++;
				if (!begin_h)
					begin_h = num;//记录满足条件的第一行
				flag = 1;//在时间范围内且是时间行
			}
			else {
				flag = 0;
				if (begin_h&&!end_h)//当已经开始过了，再为0就说明结束了
					end_h = num-1;
			}
			if (flag) {//在指定时间区间内，
				if ((int)s.length() >= 28) {
					id = s.substr(20, 7);
					if (atoi(id.c_str()) > 0) {
						in_list++;
						id = id.substr(1, 1) + id.substr(3, 4);
						//cout << atoi(id.c_str()) << endl;
						Map[atoi(id.c_str())]++;
					}
				}
			}
		}
		if (flag) {//输出指定时间范围内的行
			cout << "No=" << num;
			cout << " Type=" << type;
			cout << " line=" << s << endl;
		}
	}
	infile_qqrecord.close();

	//Map中已经记录了每个学号发言次数，读取stulist文件，按照顺序输出每个人的发言次数即可
	infile_stulist.open(stulist, ios::in |ios::binary);
	if (!infile_stulist.is_open()) {
		cout << "Read-<STULIST>-Error!" << endl;
		return 0;
	}
	string stu,map_id;
	cout << setw(22) << "名单";
	cout << "    发炎次数" << endl;
	
	while (infile_stulist.peek() != EOF) {
		getline(infile_stulist, stu);
		stu[(int)stu.length() - 1] = '\0';
		map_id = stu.substr(1, 1) + stu.substr(3, 4);
		if (stuno ) {//指定学号
			if (atoi(stu.substr(0, 7).c_str()) == stuno) {
				cout << left << setw(25) << setfill('-') << stu;
				cout << Map[atoi(map_id.c_str())] << endl;
			}
		}
		else {
			if (only_zero && Map[atoi(map_id.c_str())] == 0) {
				cout << left << setw(25) << setfill('-') << stu;
				cout << Map[atoi(map_id.c_str())] << endl;
			}
			else if (more_than_zero && Map[atoi(map_id.c_str())] != 0) {
				cout << left << setw(25) << setfill('-') << stu;
				cout << Map[atoi(map_id.c_str())] << endl;
			}
			if (!more_than_zero && !only_zero) {
				cout << left << setw(25) << setfill('-') << stu;
				cout << Map[atoi(map_id.c_str())] << endl;
			}
			
		}
	}
	infile_stulist.close();

	infile_qqrecord.open(qqrecord, ios::in);
	if (!infile_qqrecord.is_open()) {
		cout << "OpenQQRECORDError" << endl;
		return 0;
	}
	char c;
	int lines = 0;
	while (infile_qqrecord.peek() != EOF) {
		c = infile_qqrecord.get();
		if (c == '\n')
			lines++;
	}
	infile_qqrecord.close();

	cout << "\n\n";
	cout << "文件总行数：" << lines<<endl;
	cout << "符合条件的第一行：" << begin_h<<endl;
	cout << "合条件的最后一行：";
	if (end_h)
		cout << end_h << endl;
	else
		cout << "<无>" << endl;
	cout << "在日志中搜索的行数：";
	if (end_h)
		cout << end_h - begin_h + 1 << endl;
	else
		cout << lines - begin_h + 1 << endl;
	cout << "不在名单中的发言数：" << not_in_list-in_list<< endl;//not_in_list最初统计的是所有发言数，减去在名单中的数量即可
	return 1;
}

int main(int argc, char** argv)
{
	string Para[7] = { "--stulist", "--qq_record", "--begin", "--end", "--stuno", "--only_zero","--more_than_zero"};
	int Bool[7] = { 0 };
	string Option[5];//前5个参数后跟的具体选项,分别对应stulist,qqrecord,begin,end
	string stulist = "stulist.txt";
	string qqrecord = "2020级-高程[计荣].txt";
	Time time_begin, time_end;
	int Continue=0,stuno=0,more_than_zero=0,only_zero=0;


	if (argc < 5 || argc>13) {
		usage(argv[0], 1);
		return 0;
	}
	for (int i = 1; i < argc; i++) {
		int flag = 0;
		if (Continue) {//读入参数的值而不是参数选项
			if (strlen(argv[i]) >= 2 && argv[i][0] == '-' && argv[i][1] == '-') {
				cout << "参数[" << argv[i - 1] << "]缺少附加参数。(类型string)" << endl;
				return 0;
			}
			Option[Continue-1] = argv[i];
			Continue = 0;
			continue;
		}
		for (int j = 0; j < 7; j++) {
			if (argv[i] == Para[j]) {
				//cout << Para[j] << endl;
				if (Bool[j]) {
					cout << "参数[" << argv[i] << "]重复" << endl;
					return 0;
				}
				flag = 1;
				Bool[j] = 1;
				if (j < 5 && j >= 0) {//前5种要后接参数
					Continue = j+1;
				} 
			}
		}
		if (!flag) {
			cout << "参数[" << argv[i] << "]非法" << endl;
			return 0;
		}
	}
	if (Continue) {//如果该有而没有后续参数
		if (strlen(argv[argc - 1]) >= 2 && argv[argc - 1][0] == '-' && argv[argc - 1][1] == '-') {
			cout << "参数[" << argv[argc - 1] << "]缺少附加参数。(类型string)" << endl;
			return 0;
		}
	}
	if (!Bool[2]) {//begin和end必须有
		usage(argv[0], 1);
		cout << "必须指定[begin]开始时间" << endl;
		return 0;
	}
	if (!Bool[3]) {
		usage(argv[0], 1);
		cout << "必须指定[end]结束时间" << endl;
		return 0;
	}
	
	//至此参数数目和名称合法，接下来逐个判断参数内容是否合法
	if (Bool[0]) {
		stulist = Option[0];
	}
	if (Bool[1]) {
		qqrecord = Option[1];
	}

	if (Bool[2]) {
		if (!Is_time(Option[2])) {
			cout << "--begin参数格式错误" << endl;
			return 0;
		}
	}
	if (Bool[3]) {
		if (!Is_time(Option[3])) {
			cout << "--end参数格式错误" << endl;
			return 0;
		}
	}
	
	if (Bool[5]) {
		only_zero = 1;
	}
	if (Bool[6]) {
		more_than_zero = 1;
	}
	if (Bool[4]) {
		if (Option[4].length() != 7) {
			cout << "--stuno参数格式错误" << endl;
			return 0;
		}
		stuno = atoi(Option[4].c_str());
		only_zero = 0;
		more_than_zero = 0;
	}
	
	//参数检查完毕
	time_begin = Time(Option[2]);
	time_end = Time(Option[3]);

	if (time_begin >= time_end) {
		cout << "起始时间必须小于结束时间" << endl;
		return 0;
	}
	if (Bool[5] && Bool[6]&&!Bool[4]) {
		cout << "参数--only_zero 和--more_than_zero冲突" << endl;
		return 0;
	}
	
	if (!ReadFile(stulist, qqrecord, time_begin, time_end, stuno, only_zero, more_than_zero))
		return 0;
	return 1;
}