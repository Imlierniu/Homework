
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

/* �˴�������ӱ���Ķ����������������ȫ�ֱ����� */
class Teacher;
/* Student ��Ķ��壨��Ա��������������ʵ�֣� */
class Student {
private:
	int num;	//ѧ��
	char name[16];	//����
	char sex;	//�Ա�ֻ���� F/M ���֣���Сд������
	char addr[64];	//��ͥסַ
	//˽�в��ֲ���������κ�����
public:
	Student();
	Student(const int num1, const char* name1, const char sex1, const char* addr1);
	friend ostream& operator<<(ostream& out, const Student& stu);
	//���в���������ӳ�Ա����������ʵ�֣���������������ݳ�Ա����Ԫ����
	Student(Teacher&);
	operator Teacher();
};

/* ----����Student���Ա��������Ԫ����������ʵ�֣������޷��ڴ˴�ʵ�ֵĺ�������������ţ�---- */
Student::Student()
{
	num = 1950000;
	strcpy(name, "<ѧ��S>");
	sex = 'M';
	strcpy(addr, "��ƽ·1239��");
}

Student::Student(const int num1, const char* name1, const char sex1, const char* addr1)
{
	num = num1;
	strcpy(name, name1);
	sex = sex1;
	strcpy(addr, addr1);
}

ostream& operator<<(ostream& out, const Student& stu)
{
	out << "ѧ����Ϣ��" << stu.num << " " << stu.name << " " << stu.sex << " " << stu.addr;
	return out;
}


/* Teacher ��Ķ���(Teacher���в�����������κ����ݳ�Ա����Ա��������Ԫ����Ա��������������ʵ��) */
class Teacher {
private:
	int num;	//����
	char name[16];	//����
	char sex;	//�Ա�ֻ���� F/M ���֣���Сд������
	char addr[64];	//��ͥסַ
	//˽�в��ֲ���������κ�����
public:
	Teacher();
	Teacher(const int num1, const char* name1, const char sex1, const char* addr1);
	friend ostream& operator<<(ostream& out, const Teacher& te);
	friend Student;
	//���в��ֲ���������κ�����
};

/* ----����Teacher���Ա��������Ԫ����������ʵ��---- */
Teacher::Teacher()
{
	num = 19000;
	strcpy(name, "<��ʦT>");
	sex = 'M';
	strcpy(addr, "��ƽ·1239���Ժ�¥");
}

Teacher::Teacher(const int num1, const char* name1, const char sex1, const char* addr1)
{
	num = num1;
	strcpy(name, name1);
	sex = sex1;
	strcpy(addr, addr1);
}

ostream& operator<<(ostream& out, const Teacher& te)
{
	out << "��ʦ��Ϣ��" << te.num << " " << te.name << " " << te.sex << " " << te.addr;
	return out;
}
/* ----����Studentr���б�����Teacher��ʵ�ֵĳ�Ա����������ʵ��---- */

Student::Student(Teacher&te)
{
	num = 1950000 + te.num % 1000;
	sex = te.sex;
	strcpy(name, te.name);
	char t = name[4];
	strcpy(name, "ѧ��");
	name[4] = t;

	strcpy(addr, te.addr);
	strcat(addr, "101��");
}

Student ::operator Teacher()
{
	Teacher te;
	te.num = 19000 + num % 1000;
	strcpy(te.addr, addr);
	strcat(te.addr, "����ѧԺ");
	te.sex = sex;
	strcpy(te.name, name);
	char t = te.name[4];
	strcpy(te.name, "��ʦ");
	te.name[4] = t;
	return te;
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼��
***************************************************************************/
int main()
{
	Student s1;	//ȱʡֵ - ѧ�ţ�1950000 ������<ѧ��S> �Ա�M ��ַ����ƽ·1239��
	Student s2 = Student(1951234, "ѧ����", 'M', "�ܰ���·4800��");
	Teacher t1;	//ȱʡֵ - ���ţ�19000 ������<��ʦT> �Ա�M ��ַ����ƽ·1239���Ժ�¥
	Teacher t2 = Teacher(19123, "��ʦA", 'F', "�ܰ���·4800�����Ź�");

	/* ��ӡԭʼѧ����Ϣ */
	cout << "ѧ����Ϣ��" << s1 << endl;				//���������"ѧ����Ϣ��1950000 <ѧ��S> M ��ƽ·1239��"
	cout << "ѧ����Ϣ��" << s2 << endl;				//���������"ѧ����Ϣ��1951234 ѧ���� M �ܰ���·4800��"
	cout << endl;

	/* ��ӡԭʼ��ʦ��Ϣ */
	cout << "��ʦ��Ϣ��" << t1 << endl;				//���������"��ʦ��Ϣ��19000 <��ʦT> M ��ƽ·1239���Ժ�¥"
	cout << "��ʦ��Ϣ��" << t2 << endl;				//���������"��ʦ��Ϣ��19123 ��ʦA F �ܰ���·4800�����Ź�"
	cout << endl;

	/* ѧ��ת��ʦ���ԣ�
		ѧ��ת���Ź��򣺹��� = 19 + ѧ�ź���λ
		����ת������ǰ��������ת��Ϊ"��ʦ"�������ַ�����
		�Ա�ת������ԭ��ת��
		��ַת������ԭ��ַ���"����ѧԺ"(�������ַ���Խ��)    */
	t1 = s2;
	cout << "ѧ����Ϣ��" << s2 << endl;				//���������"ѧ����Ϣ��1951234 ѧ���� M �ܰ���·4800��"
	cout << "ת��Ϊ��ʦ����Ϣ��" << t1 << endl;			//���������"ת��Ϊ��ʦ����Ϣ��19234 ��ʦ�� M �ܰ���·4800�ŵ���ѧԺ"
	cout << endl;

	/* ��ʦתѧ�����ԣ�
		����תѧ�Ź���ѧ�� = 1950 + ���ź���λ
		����ת������ǰ��������ת��Ϊ"ѧ��"�������ַ�����
		�Ա�ת������ԭ��ת��
		��ַת������ԭ��ַ���"101��"(�������ַ���Խ��)    */
	s1 = t2;
	cout << "��ʦ��Ϣ��" << t2 << endl;				//���������"��ʦ��Ϣ��19123 ��ʦA F �ܰ���·4800�����Ź�"
	cout << "ת��Ϊѧ������Ϣ��" << s1 << endl;			//���������"ת��Ϊѧ������Ϣ��1950123 ѧ��A F �ܰ���·4800�����Ź�101��"
	cout << endl;

	return 0;
}
