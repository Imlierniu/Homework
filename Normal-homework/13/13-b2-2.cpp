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
	
	for (int i = 0; i < n; i++) {
		fin >> stu[i].no >> stu[i].name >> stu[i].score;
	}
	int max, imax = 0;

	for (int i = 0; i < n; i++) {
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
	
	
	int r = 1;
	stu[0].rank = 1;
	for (int i = 1; i < n; i++) {
		if (stu[i].score == stu[i - 1].score)
			stu[i].rank = r;
		else
			stu[i].rank = ++r;
	}
	
	int min ,imin=0;
	for (int i = 0; i < n-1; i++) {
		min = stu[i].no;
		imin = i;
		for (int j = i+1; j < n; j++) {
			if (min > stu[j].no) {
				min = stu[j].no;
				imin = j;
			}
		}
		student t;
		t = stu[i];
		stu[i] = stu[imin];
		stu[imin] = t;
	}

	for (int i = 0; i < n; i++) {
		cout << stu[i].no << stu[i].name << stu[i].score << " " <<stu[i].rank<<endl;
	}
	delete[]stu;
}
*/