
#include"90-01-b2-mine_sweeper.h"
int menu()
{
	int num;
	char c;
	system("cls");
	cout << "-----------------------------------------" << endl;
	cout << "1.ѡ���ѶȲ���ʾ�ڲ�����" << endl;
	cout << "2.�����ʼλ�ò���ʾ���򿪵�����" << endl;
	cout << "3.�ڲ����������" << endl;
	cout << "4.�ڲ�����������" << endl;
	cout << "5.����αͼ�λ���ܲ���ʾ�ڲ�����" << endl;
	cout << "6.������λ�úͺϷ���" << endl;
	cout << "7.���ѡ���ʼλ�ò���ʾ���򿪵ĳ�ʼ����" << endl;
	cout << "8.αͼ�ν��������" << endl;
	cout << "9.Ϊͼ�ν���������" << endl;
	cout << "0.�˳�" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "[��ѡ��]" << endl;

	c = _getch();
	while (c<'0' || c>'9') {        //��ֹ��ѭ��
		c = _getch();
	}
	num = (int)(c - '0');


	return num;
}
int Select_Level()
{
	system("cls");
	int num;
	char c;
	cout << "��ѡ���Ѷ�" << endl;
	cout << "  1.������ 9x9   - 10�����ף�" << endl;
	cout << "  2.�м���16x16  - 40�����ף�" << endl;
	cout << "  3.�߼���16x30  - 99�����ף�" << endl;
	cout << "������1.2.3" << endl;
	c = _getch();
	while (c<'1' || c>'3') {        //��ֹ��ѭ��
		c = _getch();
	}
	num = (int)(c - '0');


	return num;

}
void Quit()
{
	cout << "���س��˳�" << endl;
	char ch = _getch();
	while (ch != 13) {
		ch = _getch();
	}
}