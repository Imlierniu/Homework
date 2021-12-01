
#include <iostream>
#include <fstream>
#include<cstdlib>
#include<cstring>
using namespace std;

int usage(const char* procname)
{
	cout << "Usage: " << procname << " --check �ļ��� | --convert { wtol|ltow } Դ�ļ��� Ŀ���ļ���" << endl;
	cout << "               --check a.txt" << endl;
	cout << "               --convert wtol a.win.txt a.linux.txt" << endl;
	cout << "               --convert ltow a.linux.txt a.win.txt" << endl;
	return 0;
}
int check(ifstream &in,char**argv,int i)
{
	in.open(argv[i], ios::in | ios::binary);
	if (!in.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		return -1;
	}
	char c = 0, c_old = 0;
	int a1 = 0, a2 = 0;
	while ((c = in.get()) != EOF) {
		if (c == 10 && c_old == 13)
			a1 = 1;
		else if (c == 10 && c_old != 13)
			a2 = 1;
		c_old = c;
	}
	in.close();

	if ((a1 && a2) || (!a1 && !a2))
		return 0;
	else if (a1)
		return 1;
	else if (a2)
		return 2;
	return 0;
}

int wtol(ifstream&in,ofstream&out,char**argv)
{
	int sum = 0;
	in.open(argv[3], ios::in | ios::binary);
	out.open(argv[4], ios::out | ios::binary);
	if (!in.is_open()|| !out.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		return -1;
	}
	
	char c = 0;
	while ((c = in.get()) != EOF) {
		if (c == 13) {
			sum++;
			continue;
		}
		else 
			out.put(c);
	}

	in.close();
	out.close();
	cout << "ת����ɣ�ȥ��" <<sum<< "��0x0D" << endl;
	return 1;

}

int ltow(ifstream&in,ofstream&out,char**argv)
{
	int sum = 0;
	in.open(argv[3], ios::in | ios::binary);
	out.open(argv[4], ios::out | ios::binary);
	if (!in.is_open() || !out.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		return -1;
	}

	char c = 0;
	while ((c = in.get()) != EOF) {
		if (c == 10) {
			sum++;
			out.put(13);
		}
		out.put(c);
	}

	in.close();
	out.close();
	cout << "ת����ɣ�����" << sum << "��0x0D" << endl;
	return 1;
}

int main(int argc,char **argv)
{
	ifstream in;
	ofstream out;

	if ((argc != 3)&&(argc!=5)) {
		usage(argv[0]);
		return 0;
	}
	if (argc == 3) {
		if (strcmp(argv[1], "--check")) {
			usage(argv[0]);
			return 0;
		}
		else {
			int ans = check(in, argv,2);
			if (ans == -1)
				return 0;//�ļ���ʧ��
			else if (ans==0)
				cout << "�ļ���ʽ�޷�ʶ��" << endl;
			else if (ans==1)
				cout << "Windows��ʽ" << endl;
			else if (ans==2)
				cout << "Linux��ʽ" << endl;
			return 0;
		}
	}

	if (argc == 5) {
		if (strcmp(argv[1], "--convert")) {
			usage(argv[0]);
			return 0;
		}
		if (strcmp(argv[2], "wtol") && strcmp(argv[2], "ltow")) {
			usage(argv[0]);
				return 0;
		}
		int ans=check(in,argv,3);//��ʱĿ���ļ�����argv[3]
		if (ans == -1)
			return 0;
		if (ans==0 || (ans == 1 && strcmp(argv[2], "wtol")) || (ans == 2 && strcmp(argv[2], "ltow"))) {
			cout << "�ļ���ʽ�޷�ʶ��" << endl;
			return 0;
		}
		if (ans == 1) {
			wtol(in, out, argv);
		}
		else if (ans == 2) {
			ltow(in,out,argv);
		}
		return 0;
			
		
	}
}

