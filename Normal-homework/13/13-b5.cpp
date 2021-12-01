
#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;

struct student
{
	int no;
	char name[10];
	char school[10];
	char tag;
};
/*
int main()
{
	int M;
	int N;
	ifstream fin;
	fin.open("stulist.txt", ios::in);
	if (!fin.is_open()) {
		cout << "openerror" << endl;
		return -1;
	}
	fin >> N >> M;
	student* stu = new(nothrow) student[M];
	if (stu == NULL) {
		cout << "createrror" << endl;
		return -1;
	}
	for (int i = 0; i < M; i++) {
		fin >> stu[i].no >> stu[i].name >> stu[i].school;
		stu[i].tag = 0;
	}

	srand(time(0));//随机抽取
	ofstream fout("result.txt", ios::out);
	int t;
	for (int i = 0; i < N; i++) {
		while (1) {
			t = rand() % M;
			if (stu[t].tag != 1) {    //保证不会重复
				stu[t].tag = 1;
				break;
			}
		}
		fout << stu[t].no << " " << stu[t].name << " " << stu[t].school << endl;
		
	}
	delete []stu;
	cout << "OK" << endl;

	/*我用的是动态数组形式，因为抽取需要随机访问，而链表适合进行移动增删等等
}*/