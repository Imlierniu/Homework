
#include<iostream>
#include<fstream>
using namespace std;

struct student
{
	int no;
	char name[9];
	int score;
	struct student* next;
};

/*int main()
{
	ifstream fin;

	fin.open("list.txt", ios::in);
	if (!fin.is_open()) {
		cout << "openfile error!";
		return -1;
	}
	
	
	student* head = NULL, * p = NULL, * q = NULL;

	while(1) {          //������������
		p = new(nothrow) student;
		if (p == NULL) {
			cout << "createError!" << endl;
			return -1;
		}
		fin >> p->no >> p->name >> p->score;
		if (p->no == 9999999) {
			break;//����������
		}
		if (head == NULL)
			head = p;//�׽ڵ�
		else
			q->next = p;
		q = p;
		q->next = NULL;
	}
	
	p = head;
	while (p!= NULL) {
		cout << p->no << " " << p->name << " " << p->score << endl;
		p = p->next;
	}

	//�ͷ�����
	q = head;
	while (q!=NULL) {
		p = q;
		q = p->next;
		delete p;
	}

	
	
}

*/
