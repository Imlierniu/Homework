
#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

int usage(const char* procname)
{
	cout << "Usage: " << procname << " Ҫ����ѧ��/all ƥ��ѧ��/all Դ������/all ���ƶȷ�ֵ(60-100) ���(filename/screen)" << endl;
	cout << "               2059999          2059998      all          80                screen" << endl;
	cout << "               2059999          all          7-b2.cpp     75                result.txt" << endl;
	cout << "               all              all          7-b2.cpp     80                check.dat" << endl;
	cout << "               all              all          all          85                screen" << endl;

	return 0;
}

int main(int argc,char **argv)
{
	int ALL = 0;
	int pipeidu = 80;
	if (argc != 6) {
		usage(argv[0]);
		return 0;
	}

	//Ҫ����ѧ��
	if (strcmp(argv[1], "all") == 0) {
		ALL = 1;
	}
	else {
		if (strlen(argv[1]) != 7) {
			cout << "Ҫ����ѧ�Ų���7λ" << endl;
			return 0;
		}
		for (int i = 0; i < 7; i++) {
			if (argv[1][i] > '9' || argv[1][i] < '0') {
				cout << "Ҫ����ѧ�Ų���7λ����" << endl;
				return 0;
			}
		}
	}
	//Ŀ��ѧ��
	if (ALL) {
		if (strcmp(argv[2], "all")) {
			cout << "���ѧ����all��ƥ��ѧ�ű�����all" << endl;
			return 0;
		}
	}
	else {
		if (strcmp(argv[2], "all") == 0) {
			;
		}
		else {
			if (strlen(argv[2]) != 7) {
				cout << "Ҫƥ���ѧ�Ų���7λ" << endl;
				return 0;
			}
			for (int i = 0; i < 7; i++) {
				if (argv[2][i] > '9' || argv[2][i] < '0') {
					cout << "Ҫƥ���ѧ�Ų���7λ����" << endl;
					return 0;
				}
			}
		}
	}

	//�ļ���
	if (strlen(argv[3]) > 32) {
		cout << "�ļ������ȳ���32�ֽ�" << endl;
		return 0;
	}

	//ƥ���
	if (atoi(argv[4])<=100&&atoi(argv[4])>=60) {
		pipeidu = atoi(argv[4]);
	}

	//
	if (strlen(argv[5]) > 32) {
		cout << "�ļ������ȳ���32�ֽ�" << endl;
		return 0;
	}

	//���˼��ͨ��
	cout << "�������ͨ��" << endl;
	cout << "���ѧ��:" << argv[1] << endl;
	cout << "ƥ��ѧ��:" << argv[2] << endl;
	cout << "Դ�ļ���:" << argv[3] << endl;
	cout << "ƥ����ֵ:" << pipeidu << endl;
	cout << "���Ŀ��:" << argv[5] << endl;
	
}

