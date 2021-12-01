
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include<cmath>
/* �������Ҫ���˴��������ͷ�ļ� */
using namespace std;
#include<bitset>
/* �����峣����/�궨�壬����������ȫ�ֱ��� */

/* ��������Լ���Ҫ�ĺ��� */

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡĳ����ҵ�������Ϣ������ǵ���������ӱ��
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
	/* ֻ�����岻���������������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	cout << prompt;
	for (int i = 0; i < 54; i++) {
		if (player & (long long)pow(2, i)) {
			if (i == 53)
				cout << "RJ ";
			else if (i == 52)
				cout << "BJ ";
			else {
				#ifdef linux
				if (i % 4 == 0)
					cout << 'C';
				else if (i % 4 == 1)
					cout << 'D';
				else if (i % 4 == 2)
					cout << 'H';
				else
					cout << 'S';
				#endif	
				#ifdef _WIN32
				if (i % 4 == 0)
					cout << (char)5;
				else if (i % 4 == 1)
					cout << (char)4;
				else if (i % 4 == 2)
					cout << (char)3;
				else
					cout << (char)6;
				#endif
				

				if (i /4 == 7)
					cout << "T ";
				else if (i /4== 8)
					cout << "J ";
				else if (i /4 == 9)
					cout << "Q ";
				else if (i /4 == 10)
					cout << "K ";
				else if (i /4 == 11)
					cout << "A ";
				else if (i /4 == 12)
					cout << "2 ";
				else {
					cout << char(i /4 + '3') << " ";
				}
			}
		}
	}
	cout << endl;

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ƣ����������������
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int deal(unsigned long long* player)
{
	/* ֻ�����岻����ʮ���������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	//54��������Ϣ����longlong��
	long long int A = ~0;
	int t1,t2,t3;
	srand(time(NULL));
	
	for(int i=0;i<17;i++){
		t1 = rand() % 54;
		while ((A & ((long long)pow(2, t1)))==0) {
			t1 = rand() % 54;
		}
		
		A &= ~((long long)pow(2, t1));
		player[0] |= ((long long)pow(2, t1));
		
		t2 = rand() % 54;
		while ((A & ((long long)pow(2, t2))) == 0) {
			t2 =rand() % 54;
		}
		
		A &= ~((long long)pow(2, t2));
		player[1] |= ((long long)pow(2, t2));
		
		
		t3 = rand() % 54;
		while ((A & ((long long)pow(2, t3))) == 0) {
			t3 = rand() % 54;
		}
		
		A &= ~((long long)pow(2, t3));
		player[2] |= ((long long)pow(2, t3));
		
		

		cout << "��" << i + 1 << "�ֽ�����" << endl;
		print("�׵��ƣ�", 0, player[0]);
		print("�ҵ��ƣ�", 1, player[1]);
		print("�����ƣ�", 2, player[2]);
		

	}
	//17�ֽ�����ʼ��������
	
	int num;
	while (1) {
		cout << "��ѡ��һ������[0-2]:" << endl;
		cin >> num;
		while (cin.fail()) {        //��ֹ��ѭ��
			cin.clear();
			cin.ignore(100, '\n');
			cout << "��ѡ��һ������[0-2]:" << endl;
			cin >> num;
		}
		if (num <= 2 && num >= 0)
			break;
		else
			continue;
	}
	
	for (int i = 0; i < 54; i++) {
		if (A & ((long long)pow(2, i))) {
			A &= ~(long long)pow(2, i);
			player[num] |= ((long long)pow(2, i));
		}
	}

	return 0; //�˴��޸�Ϊѡ���ĵ���(0-2)
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main��������׼�޸�
 ***************************************************************************/
int main()
{
	unsigned long long player[3] = { 0 }; //���������ҵķ�����Ϣ
	int landlord; //����0-2��ʾ�ĸ�����ǵ���

	cout << "���س�����ʼ����";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("�׵��ƣ�", (landlord == 0), player[0]);
	print("�ҵ��ƣ�", (landlord == 1), player[1]);
	print("�����ƣ�", (landlord == 2), player[2]);

	return 0;
}
