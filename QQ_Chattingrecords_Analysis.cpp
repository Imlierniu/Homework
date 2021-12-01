#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;

const int mon1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const int mon2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
bool Is_time(string s);//����
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
	const char* recname_def = "21221-�������(2020��).txt";
	const char* recname_new = "21221-�������(2020��)-1.txt";
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
	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--stulist filename   : ѧ���б��ļ���(ȱʡ:" << listname_def << ")" << endl;
	cout << setw(wopt) << ' ' << "--qq_record filename : �����������¼�ļ���(ȱʡ:" << recname_def << ")" << endl;
	cout << setw(wopt) << ' ' << "--begin timestr      : ��ʼʱ��(ʱ�䴮��ʽΪyyyy-mm-dd hh:mm:ss��������)" << endl;
	cout << setw(wopt) << ' ' << "--end timestr        : ����ʱ��(ʱ�䴮��ʽΪyyyy-mm-dd hh:mm:ss��������)" << endl;
	cout << setw(wopt) << ' ' << "ע��δ���ʱ�䴮��ȷ��" << endl;
	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--stuno stuno        : ָ��ĳ��ѧ��(�޴�ѡ����ȫ��ѧ��)" << endl;
	cout << setw(wopt) << ' ' << "--only_zero          : ����ʾ0����ѧ��(ָ��--stunoʱ������Ч)" << endl;
	cout << setw(wopt) << ' ' << "--more_than_zero     : ����ʾ�з���ѧ��(ָ��--stunoʱ������Ч������--only_zero����)" << endl;
	cout << endl;

	cout << "e.g.  " << procname << " --begin \"" << time_begin << "\" --end \"" << time_end << "\"" << endl;
	cout << setw(wkey) << "                               : ͳ��[" << recname_def << "]����[" << listname_def << "]�б��е�ѧ����[" << time_begin << "~" << time_end << "]��ķ�������" << endl;
	cout << "      " << procname << " --begin \"" << time_begin << "\" --end \"" << time_end << "\" --only_zero" << endl;
	cout << setw(wkey) << "                               : ͳ��[" << recname_def << "]����[" << listname_def << "]�б��е�ѧ����[" << time_begin << "~" << time_end << "]������0���Ե�ѧ��" << endl;
	cout << "      " << procname << " --begin \"" << time_begin << "\" --end \"" << time_end << "\" --stuno " << stu_no << endl;
	cout << setw(wkey) << "                               : ͳ��[" << recname_def << "]����[" << listname_def << "]�б��е�ѧ��" << stu_no << "��[" << time_begin << "~" << time_end << "]��ķ�������" << endl;
	cout << "      " << procname << " --stulist " << listname_new << " --qq_record " << recname_new << " --begin \"" << time_begin << "\" --end \"" << time_end << "\"" << endl;
	cout << setw(wkey) << "                               : ͳ��[" << recname_new << "'����[" << listname_new << "]�б��е�ѧ����[" << time_begin << "~" << time_end << "]��ķ�������" << endl;
	cout << "      " << procname << " --stulist " << listname_new << " --qq_record " << recname_new << " --begin \"" << time_begin << "\" --end \"" << time_end << "\" --only_zero" << endl;
	cout << setw(wkey) << "                               : ͳ��[" << recname_new << "'����[" << listname_new << "]�б��е�ѧ����[" << time_begin << "~" << time_end << "]������0���Ե�ѧ��" << endl;
	cout << "      " << procname << " --stulist " << listname_new << " --qq_record " << recname_new << " --begin \"" << time_begin << "\" --end \"" << time_end << "\" --more_than_zero" << endl;
	cout << setw(wkey) << "                               : ͳ��[" << recname_new << "'����[" << listname_new << "]�б��е�ѧ����[" << time_begin << "~" << time_end << "]������0���Ե�ѧ��" << endl;
	cout << "      " << procname << " --stulist " << listname_new << " --qq_record " << recname_new << " --begin \"" << time_begin << "\" --end \"" << time_end << "\" --stuno " << stu_no << endl;
	cout << setw(wkey) << "                               : ͳ��[" << recname_new << "]����[" << listname_new << "]�б��е�ѧ��" << stu_no << "��[" << time_begin << "~" << time_end << "]��ķ�������" << endl;
	cout << endl;
}

bool Is_run(int year)//�ж�����
{
	return (year % 400 == 0 || (year % 4 == 0 && year % 100));
}

bool Is_days(int year, int month,int days)//�ж������Ƿ�Ϸ�
{
	if (Is_run(year))
		return days <= mon2[month - 1];
	return days <= mon1[month - 1];
}

bool Is_time(string s)//���ڸ�ʽ�Ƿ�Ϸ�
{
	int space=0,i=0;
	//���ڼ��
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
	//ʱ����
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
	
	int data[6] = { -1 };//�ֱ��Ӧyear,month,day,hour,minute,second
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
	int* Map = new int[100000]();//��¼stulist�е�ѧ�ţ�ֻȡ2��4��5��6��7λ��

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
		num++;//������
		if (Is_time(s.substr(0, 19))) {
			type = 0;
			if (Time(s.substr(0, 19)) >= b && Time(s.substr(0, 19)) <= e) {//ѡȡָ����Χ�ڵ�ʱ�䣬ת����Time���ͽ��бȽ�
				not_in_list++;
				if (!begin_h)
					begin_h = num;//��¼���������ĵ�һ��
				flag = 1;//��ʱ�䷶Χ������ʱ����
			}
			else {
				flag = 0;
				if (begin_h&&!end_h)//���Ѿ���ʼ���ˣ���Ϊ0��˵��������
					end_h = num-1;
			}
			if (flag) {//��ָ��ʱ�������ڣ�
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
		if (flag) {//���ָ��ʱ�䷶Χ�ڵ���
			cout << "No=" << num;
			cout << " Type=" << type;
			cout << " line=" << s << endl;
		}
	}
	infile_qqrecord.close();

	//Map���Ѿ���¼��ÿ��ѧ�ŷ��Դ�������ȡstulist�ļ�������˳�����ÿ���˵ķ��Դ�������
	infile_stulist.open(stulist, ios::in |ios::binary);
	if (!infile_stulist.is_open()) {
		cout << "Read-<STULIST>-Error!" << endl;
		return 0;
	}
	string stu,map_id;
	cout << setw(22) << "����";
	cout << "    ���״���" << endl;
	
	while (infile_stulist.peek() != EOF) {
		getline(infile_stulist, stu);
		stu[(int)stu.length() - 1] = '\0';
		map_id = stu.substr(1, 1) + stu.substr(3, 4);
		if (stuno ) {//ָ��ѧ��
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
	cout << "�ļ���������" << lines<<endl;
	cout << "���������ĵ�һ�У�" << begin_h<<endl;
	cout << "�����������һ�У�";
	if (end_h)
		cout << end_h << endl;
	else
		cout << "<��>" << endl;
	cout << "����־��������������";
	if (end_h)
		cout << end_h - begin_h + 1 << endl;
	else
		cout << lines - begin_h + 1 << endl;
	cout << "���������еķ�������" << not_in_list-in_list<< endl;//not_in_list���ͳ�Ƶ������з���������ȥ�������е���������
	return 1;
}

int main(int argc, char** argv)
{
	string Para[7] = { "--stulist", "--qq_record", "--begin", "--end", "--stuno", "--only_zero","--more_than_zero"};
	int Bool[7] = { 0 };
	string Option[5];//ǰ5����������ľ���ѡ��,�ֱ��Ӧstulist,qqrecord,begin,end
	string stulist = "stulist.txt";
	string qqrecord = "2020��-�߳�[����].txt";
	Time time_begin, time_end;
	int Continue=0,stuno=0,more_than_zero=0,only_zero=0;


	if (argc < 5 || argc>13) {
		usage(argv[0], 1);
		return 0;
	}
	for (int i = 1; i < argc; i++) {
		int flag = 0;
		if (Continue) {//���������ֵ�����ǲ���ѡ��
			if (strlen(argv[i]) >= 2 && argv[i][0] == '-' && argv[i][1] == '-') {
				cout << "����[" << argv[i - 1] << "]ȱ�ٸ��Ӳ�����(����string)" << endl;
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
					cout << "����[" << argv[i] << "]�ظ�" << endl;
					return 0;
				}
				flag = 1;
				Bool[j] = 1;
				if (j < 5 && j >= 0) {//ǰ5��Ҫ��Ӳ���
					Continue = j+1;
				} 
			}
		}
		if (!flag) {
			cout << "����[" << argv[i] << "]�Ƿ�" << endl;
			return 0;
		}
	}
	if (Continue) {//������ж�û�к�������
		if (strlen(argv[argc - 1]) >= 2 && argv[argc - 1][0] == '-' && argv[argc - 1][1] == '-') {
			cout << "����[" << argv[argc - 1] << "]ȱ�ٸ��Ӳ�����(����string)" << endl;
			return 0;
		}
	}
	if (!Bool[2]) {//begin��end������
		usage(argv[0], 1);
		cout << "����ָ��[begin]��ʼʱ��" << endl;
		return 0;
	}
	if (!Bool[3]) {
		usage(argv[0], 1);
		cout << "����ָ��[end]����ʱ��" << endl;
		return 0;
	}
	
	//���˲�����Ŀ�����ƺϷ�������������жϲ��������Ƿ�Ϸ�
	if (Bool[0]) {
		stulist = Option[0];
	}
	if (Bool[1]) {
		qqrecord = Option[1];
	}

	if (Bool[2]) {
		if (!Is_time(Option[2])) {
			cout << "--begin������ʽ����" << endl;
			return 0;
		}
	}
	if (Bool[3]) {
		if (!Is_time(Option[3])) {
			cout << "--end������ʽ����" << endl;
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
			cout << "--stuno������ʽ����" << endl;
			return 0;
		}
		stuno = atoi(Option[4].c_str());
		only_zero = 0;
		more_than_zero = 0;
	}
	
	//����������
	time_begin = Time(Option[2]);
	time_end = Time(Option[3]);

	if (time_begin >= time_end) {
		cout << "��ʼʱ�����С�ڽ���ʱ��" << endl;
		return 0;
	}
	if (Bool[5] && Bool[6]&&!Bool[4]) {
		cout << "����--only_zero ��--more_than_zero��ͻ" << endl;
		return 0;
	}
	
	if (!ReadFile(stulist, qqrecord, time_begin, time_end, stuno, only_zero, more_than_zero))
		return 0;
	return 1;
}