
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

int main(int argc,char **argv)
{
	int l = 128;
	int n = 100;
	int t = 0;
	int count = 0;

	//�ȷ������һ��ip��ַ
	if (argc == 1) {
		cout << "Usage: 14-b2 [-l ��С] [-n ����] [-t] IP��ַ";
		return 0;
	}

	if (strlen(argv[argc - 1]) > 15||strlen(argv[argc-1])<7||argv[argc-1][0]=='.') {
		cout << "ip��ַ����" << endl;
		return 0;
	}

	for (int j=0; j<(int)strlen(argv[argc-1]); count++,j++) {
		if (argv[argc - 1][j] == '\0') {
			break;
		}
		char a[20];
		int k = 0;
		while (argv[argc - 1][j] != '.'&& argv[argc - 1][j] != '\0') {
			if (argv[argc - 1][j] < '0' || argv[argc - 1][j]>'9')
			{
				cout << "ip��ַ����" << endl;
				return 0;
			}
			a[k] = argv[argc - 1][j];
			k++;
			j++;
			if (k == 4) {
				cout << "ip��ַ����" << endl;
				return 0;
			}
		}
		if (!k) {
			cout << "ip��ַ����" << endl;
			return 0;
		}
		a[k] = '\0';
		if (atoi(a) < 0 || atoi(a) > 255) {
			cout << "ip��ַ����" << endl;
			return 0;
		}
		
	}

	if (count != 4) {
		cout << "ip��ַ����" << endl;
		return 0;
	}
	

	//��������
	for (int i = 1; i < argc - 1; i+=2) {
		if (argv[i][0] != '-') {
			cout << "����"<<argv[i]<<"������-��ͷ�ĺϷ�����" << endl;
			return 0;
		}
		if (strcmp(argv[i], "-l")==0) {
			if (argv[i + 1][0] == '-' || i + 1 == argc - 1)//��������-x����ip��ַ������
			{
				cout << "����-lû�к�������" << endl;
				return 0;
			}
			else {
				if (atoi(argv[i + 1]) <= 64000 && atoi(argv[i + 1]) >= 64)
					l = atoi(argv[i + 1]);
			}
		}
		else if (strcmp(argv[i], "-t") == 0) {
			t = 1;
			i--;
		}
		else if (strcmp(argv[i], "-n") == 0) {
			if (argv[i + 1][0] == '-' || i + 1 == argc - 1)//��������-x����ip��ַ������
			{
				cout << "����-nû�к�������" << endl;
				return 0;
			}
			else {
				if (atoi(argv[i + 1]) <= 100 && atoi(argv[i + 1]) >= 1)
					n = atoi(argv[i + 1]);
			}
		}
		else {
			cout <<"����" << argv[i] << "������" << endl;
			return 0;
		}
	}

	//������ƥ��ɹ�
	cout << "�������ͨ��" << endl;
	cout << "-n������" << n << endl;
	cout << "-l������" << l << endl;
	cout << "-t������" << t << endl;
	cout << "IP��ַ��" << argv[argc - 1] << endl;

}