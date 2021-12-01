
#include<iostream>
#include<fstream>
using namespace std;

struct student
{
	int no;
	char name[9];
	int score;
	int rank;
};
/*
int main()
{
	ifstream fin;
	int n;
	fin.open("student.txt", ios::in);
	if (!fin.is_open()) {
		cout << "openfile error!";
		return -1;
	}
	fin >> n;
	student* stu = new(nothrow) student[n];
	if (stu == NULL) {
		cout << "create error" << endl;
		return -1;
	}

	for (int i = 0; i < n; i++) {          //读入
		fin >> stu[i].no >> stu[i].name >> stu[i].score;
	}
	int max, imax = 0;

	for (int i = 0; i < n; i++) {          //按成绩排名
		max = stu[i].score;
		imax = i;
		for (int j = i; j < n; j++) {
			if (max < stu[j].score) {
				max = stu[j].score;
				imax = j;
			}
		}
		student t;
		t = stu[i];
		stu[i] = stu[imax];
		stu[imax] = t;
	}

	int r = 1;                            //求rank
	stu[0].rank = 1;
	for (int i = 1; i < n; i++) {
		if (stu[i].score == stu[i - 1].score)
			stu[i].rank = r;
		else
			stu[i].rank = ++r;
	}

	//多字段排序，成绩优先级高于学号
	int imin, min;
	for (int i = 0; i < n; i++) {
		int j = i;
		while (stu[j].rank == stu[i].rank) {
			j++;
		}
		for (int k = i; k < j; k++) {
			min = stu[k].no;
			imin = k;
			for (int k0 = k; k0 < j; k0++) {
				if (min > stu[k0].no) {
					min = stu[k0].no;
					imin = k0;
				}
			}
			student t = stu[k];
			stu[k] = stu[imin];
			stu[imin] = t;
		}
		i = j-1;
	}

	for (int i = 0; i < n; i++) {
		cout << stu[i].no << stu[i].name << stu[i].score << " " << stu[i].rank << endl;
	}
	delete[]stu;
}*/