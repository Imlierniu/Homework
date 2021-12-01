
#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

int usage(const char* procname)
{
	cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl;
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

	//要检查的学号
	if (strcmp(argv[1], "all") == 0) {
		ALL = 1;
	}
	else {
		if (strlen(argv[1]) != 7) {
			cout << "要检查的学号不是7位" << endl;
			return 0;
		}
		for (int i = 0; i < 7; i++) {
			if (argv[1][i] > '9' || argv[1][i] < '0') {
				cout << "要检查的学号不是7位数字" << endl;
				return 0;
			}
		}
	}
	//目标学号
	if (ALL) {
		if (strcmp(argv[2], "all")) {
			cout << "检查学号是all，匹配学号必须是all" << endl;
			return 0;
		}
	}
	else {
		if (strcmp(argv[2], "all") == 0) {
			;
		}
		else {
			if (strlen(argv[2]) != 7) {
				cout << "要匹配的学号不是7位" << endl;
				return 0;
			}
			for (int i = 0; i < 7; i++) {
				if (argv[2][i] > '9' || argv[2][i] < '0') {
					cout << "要匹配的学号不是7位数字" << endl;
					return 0;
				}
			}
		}
	}

	//文件名
	if (strlen(argv[3]) > 32) {
		cout << "文件名长度超过32字节" << endl;
		return 0;
	}

	//匹配度
	if (atoi(argv[4])<=100&&atoi(argv[4])>=60) {
		pipeidu = atoi(argv[4]);
	}

	//
	if (strlen(argv[5]) > 32) {
		cout << "文件名长度超过32字节" << endl;
		return 0;
	}

	//到此检查通过
	cout << "参数检查通过" << endl;
	cout << "检查学号:" << argv[1] << endl;
	cout << "匹配学号:" << argv[2] << endl;
	cout << "源文件名:" << argv[3] << endl;
	cout << "匹配阈值:" << pipeidu << endl;
	cout << "输出目标:" << argv[5] << endl;
	
}

