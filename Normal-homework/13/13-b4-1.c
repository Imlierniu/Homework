
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
	int *no;
	char *name;
	int *score;
	struct student* next;
};

int main()
{
	FILE* infile;
	infile = fopen("list.txt", "r");
	if (infile == NULL) {
		printf("ReadFileError\n");
		return -1;
	}

	struct student* head = NULL, * p = NULL, * q = NULL;
	
	while (1) {
		p = (struct student*)malloc(sizeof(struct student));
		if (p == NULL) {
			printf("CreateError\n");
			return -1;
		}
		//��������
		p->no = (int*)malloc(sizeof(int));
		if (p->no == NULL) {
			printf("CreateError\n");
			return -1;
		}
		fscanf(infile, "%d ", p->no);
		if (*(p->no) == 9999999) {
			break;//����������
		}

		
		p->name = (char*)malloc(sizeof(char) * 10);
		if (p->name == NULL) {
			printf("CreateError\n");
			return -1;
		}
		fscanf(infile,"%s ", p->name);
		char*Name= (char*)realloc(p->name,sizeof(char)*(strlen(p->name)+1));
		if (Name == NULL) {
			printf("ReallocError");
			return -1;
		}
		p->name = Name;

		p->score = (int*)malloc(sizeof(int));
		if (p->score == NULL) {
			printf("CreateError\n");
			return -1;
		}
		fscanf(infile, "%d\n", p->score);
	
		/*p->score = (int*)malloc(sizeof(int));
		p->name = (char*)malloc(sizeof(char) * 10);
		p->no = (int*)malloc(sizeof(int));
		fscanf(infile,"%d %s %d\n", p->no, p->name, p->score);
		if (*p->no == 9999999)
			break;
			*/
		if (head == NULL)
			head = p;
		else
			q->next = p;
		q = p;
		p->next = NULL;
	}
	p = head;
	while (p) {//��ӡ���ͷŽ��
		printf("%d %s %d\n", *p->no, p->name, *p->score);
		q = p;
		p = p->next;
		free(q);
	}

}