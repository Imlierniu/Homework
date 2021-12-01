
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

	//先分析最后一项ip地址
	if (argc == 1) {
		cout << "Usage: 14-b2 [-l 大小] [-n 数量] [-t] IP地址";
		return 0;
	}

	if (strlen(argv[argc - 1]) > 15||strlen(argv[argc-1])<7||argv[argc-1][0]=='.') {
		cout << "ip地址错误" << endl;
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
				cout << "ip地址错误" << endl;
				return 0;
			}
			a[k] = argv[argc - 1][j];
			k++;
			j++;
			if (k == 4) {
				cout << "ip地址错误" << endl;
				return 0;
			}
		}
		if (!k) {
			cout << "ip地址错误" << endl;
			return 0;
		}
		a[k] = '\0';
		if (atoi(a) < 0 || atoi(a) > 255) {
			cout << "ip地址错误" << endl;
			return 0;
		}
		
	}

	if (count != 4) {
		cout << "ip地址错误" << endl;
		return 0;
	}
	

	//分析参数
	for (int i = 1; i < argc - 1; i+=2) {
		if (argv[i][0] != '-') {
			cout << "参数"<<argv[i]<<"不是以-开头的合法参数" << endl;
			return 0;
		}
		if (strcmp(argv[i], "-l")==0) {
			if (argv[i + 1][0] == '-' || i + 1 == argc - 1)//若后面是-x或者ip地址，错误
			{
				cout << "参数-l没有后续参数" << endl;
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
			if (argv[i + 1][0] == '-' || i + 1 == argc - 1)//若后面是-x或者ip地址，错误
			{
				cout << "参数-n没有后续参数" << endl;
				return 0;
			}
			else {
				if (atoi(argv[i + 1]) <= 100 && atoi(argv[i + 1]) >= 1)
					n = atoi(argv[i + 1]);
			}
		}
		else {
			cout <<"参数" << argv[i] << "不存在" << endl;
			return 0;
		}
	}

	//到这里匹配成功
	cout << "参数检查通过" << endl;
	cout << "-n参数：" << n << endl;
	cout << "-l参数：" << l << endl;
	cout << "-t参数：" << t << endl;
	cout << "IP地址：" << argv[argc - 1] << endl;

}