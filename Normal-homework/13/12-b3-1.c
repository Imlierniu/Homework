#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

struct student
{
	int no;
	char name[9];
	int score;
	struct student* next;
};
/*
int main()
{
	FILE *infile;
	infile=fopen("list.txt", "r");
	if (infile == NULL) {
		printf("ReadFileError\n");
		return - 1;
	}

	struct student* head = NULL, * p = NULL, * q = NULL;
	while (1) {
		p = (struct student*)malloc(sizeof(struct student));
		if (p == NULL) {
			printf("CreateError\n");
			return -1;
		}
		fscanf(infile, "%d %s %d\n", &(p->no), p->name, &(p->score));
		if (p->no == 9999999) {
			break;//不加入链表
		}
		if (head == NULL)
			head = p;
		else
			q->next = p;
		q = p;
		p->next = NULL;
	}
	p = head;
	while (p) {//打印并释放结点
		printf("%d %s %d\n", p->no, p->name, p->score);
		q = p;
		p=p->next;
		free(q); 
	}
}*/
