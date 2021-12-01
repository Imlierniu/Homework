
#include<iostream>
#include<fstream>
using namespace std;
/*
struct student
{
	int *no;
	char *name;
	int *score;
	struct student* next;
};

int main()
{
	ifstream fin;
	fin.open("list.txt", ios::in);
	if (!fin.is_open()) {
		cout << "openfile error!";
		return -1;
	}
	
	
	student* head = NULL, * p = NULL, * q = NULL;
	char Name[9];
	int L;
	while(1) {          //创建链表并读入
		p = new(nothrow) student;                   //申请student
		if (p == NULL) {
			cout << "createError!" << endl;
			return -1;
		}
		p->no = new(nothrow) int;                     //申请no
		if (p->no == NULL) {
			cout << "createError!" << endl;
			return -1;
		}
		fin >> *(p->no);
		if (*(p->no) == 9999999) {
			delete p->no;
			break;
		}

		fin >> Name;                          //申请name
		p->name = new(nothrow) char[strlen(Name) + 1];//按需分配
		if (p->name == NULL) {
			cout << "createError!" << endl;
			return -1;
		}
		L = strlen(Name) + 1;
		strcpy_s(p->name,L,Name);

		p->score = new(nothrow) int;
		if (p->score == NULL) {
			cout << "createError!" << endl;
			return -1;
		}
		fin >> *(p->score);


		if (head == NULL)
			head = p;//首节点
		else
			q->next = p;
		q = p;
		q->next = NULL;
	}

	p = head;
	while (p != NULL) {//一遍输出一遍释放
		q = p;
		cout << *(p->no) << " " << p->name << " " << *(p->score) << endl;
		p = p->next;
		delete q;
	}
	
}
*/