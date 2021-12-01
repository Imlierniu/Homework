#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

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
	int n;
	FILE* fileopen;


	fileopen = fopen("student.txt", "r");
	if (fileopen == NULL) {
		printf("ReadError!\n");
		return -1;
	}
	fscanf(fileopen, "%d", &n);



	struct student* stu = (struct student*)malloc(sizeof(struct student) * n);
	if (stu == NULL) {
		printf("Create Error!");
		return -1;
	}
	for (int i = 0; i < n; i++) {
		fscanf(fileopen, "%d %s %d\n", &stu[i].no, stu[i].name, &stu[i].score);
	}


	//成绩排序求rank
	int max, imax;
	for (int i = 0; i < n; i++) {
		max = stu[i].score;
		imax = i;
		for (int j = i; j < n; j++) {
			if (max < stu[j].score) {
				imax = j;
				max = stu[j].score;
			}
		}
		struct student t = stu[i];
		stu[i] = stu[imax];
		stu[imax] = t;
	}
	//求rank
	stu[0].rank = 1;
	int r = 1;
	for (int i = 1; i < n; i++) {
		if (stu[i].score < stu[i - 1].score)
			stu[i].rank = ++r;
		else
			stu[i].rank = r;
	}
	//在成绩排序基础上按学号排序
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
			struct student t = stu[k];
			stu[k] = stu[imin];
			stu[imin] = t;
		}
		i = j - 1;
	}
	for (int i = 0; i < n; i++) {
		printf("%d %s %d %d\n", stu[i].no, stu[i].name, stu[i].score, stu[i].rank);
	}

	free(stu);
	fclose(fileopen);
}

*/