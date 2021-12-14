
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "17-b1-TStringAdv.h"
using namespace std;

#if defined(__linux) || defined(__linux__)
#include <sys/time.h>
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "���س�������";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
long get_cur_msec(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

#else
#include <Windows.h>
#include <conio.h>
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "���س�������";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
long get_cur_msec(void)
{
	return GetTickCount(); //ȡ��ǰϵͳʱ�䣬��λ����
}

#endif

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int memory_speed_test(int op)
{
	const int MAX_BYTES = 100 * 1024 * 1024;

	TStringAdv s1;
	int     total, len, i;
	int     MB_count, MB_prev_count;
	char    temp[65536];
	long    t_start, t_end, t_cur, t_prev;
	char* crc_str;

	cout << "�ڴ����ܲ���" << (op == 0 ? "(s1=s1+str��ʽ)" : "(s1+=str��ʽ)") << endl;
	cout << "ע�����1���������ò�ͬ����Լ1-10���ӣ����ڴ�ľ���������100MB�ֽ�Ϊ��������" << endl;
	cout << "          2����VS2019�²���ʱ���ȴ�������������۲����й����б�����ռ�õ��ڴ�ֵ" << endl;
	cout << "          3��VS2019������ڴ�ľ�������ִ�����ʾ����ʱ���Թ۲�����������б�����ռ�õ��ڴ�ֵ" << endl;
	cout << "             - ����ȵ��ڴ�ľ��ٴ���������������ܻ���Ϊ���ڴ���޷���" << endl;
	cout << "          4��Linux�������£�ÿ���û����������ڴ�Ϊ512MB�����������ռ�ʧ��" << endl;
	cout << "             - �����ڴ����ܲ�����Windows��ͨ��������Linux����" << endl;

	//Ϊ��ֹǰ��ఴ�س����´˴���ͣ�٣���������continue���ܼ���
	while (1) {
		char tmp[80];
		cout << "������continue�����" << endl;
		cin >> tmp;
		cin.ignore(65536, '\n'); //�����س�
		if (strcmp(tmp, "continue") == 0)
			break;
	}

	crc_str = new(nothrow) char[MAX_BYTES + 65536]; //���루100MB+64KB���ռ�
	if (crc_str == NULL) {
		cout << "�޷�����" << MAX_BYTES + 65536 << "�ֽڵ�У��ռ䣬������ֹ��������ٴ�����" << endl;
		return -1;
	}
	*crc_str = 0; //��Ϊ�մ�

	t_prev = t_start = get_cur_msec(); //ȡ��ǰϵͳʱ�䣬��λ����
	MB_prev_count = 0;
	srand((unsigned int)time(0));
	total = 0;
	while (1) {
		len = 32768 + rand() % 32768;

		for (i = 0; i < len; i++)
			temp[i] = ' ' + rand() % 95;	//����������ַ����
		temp[len] = 0;
		total += len;
		if (op == 0)
			s1 = s1 + temp;
		else
			s1 += temp;

		strcat(crc_str, temp);

		MB_count = s1.length() / (1024 * 1024);
		if (MB_count - MB_prev_count >= 1) {
			MB_prev_count = MB_count;

			t_cur = get_cur_msec();   //ȡ��ǰϵͳʱ��

			cout << "s1���г��ȣ�" << setw(10) << s1.length() / (1024.0 * 1024) << " MB�ֽڣ��������� " << setw(5) << len << " �ֽڣ�����ʱ"
				<< setw(10) << (t_cur - t_start) / 1000.0 << "�룬����1MB��ʱ" << setw(10) << (t_cur - t_prev) / 1000.0 << "��" << endl;
			t_prev = t_cur;
		}
		else
			cout << "s1���г��ȣ�" << setw(10) << s1.length() / (1024.0 * 1024) << " MB�ֽڣ��������� " << setw(5) << len << " �ֽ�" << endl;

		if (s1.length() == 0 || s1.length() > MAX_BYTES)	//��100MB���ڴ�ľ������
			break;
	}//end of while (1)

	t_end = get_cur_msec();   //ȡ��ǰϵͳʱ��

	cout << "time=" << (t_end - t_start) / 1000.0 << endl;

	if (s1.length() == 0) {
		cout << "�ڴ���䵽�� " << total / (1024 * 1024) << " MB�ֽں��ڴ�ľ�����������еĴ���" << endl;

#if !(defined(__linux) || defined(__linux__))
		cout << endl << "�۲�����������б�������ڴ�ռ�����..." << endl;
		wait_for_enter();
#endif
		exit(-1);
	}
	else
		cout << "�ڴ���䵽����100MB�����Խ���" << endl;

	int check1 = (s1 != crc_str);			//TString��ʽ�Ƚ������Ƿ����
	int check2 = strcmp(s1.c_str(), crc_str);	//strcmp��ʽ�Ƚ������Ƿ����

	delete[]crc_str; //�ͷ�У�鴮

	if (check1 || check2)
		cout << "s1�ۼ���֤������������ʵ�ֲ���" << endl;
	else {
		cout << "    ���β��Ժ�ʱ " << (t_end - t_start) / 1000.0 << "��" << endl;
		if (op == 0) {
			cout << "�ڴ����ܲ���(s1=s1+str��ʽ)" << endl;
#if !(defined(__linux) || defined(__linux__))
			cout << "    ��ʦ�Ļ�����CPU��AMD Ryzen 7 4700U, �ڴ棺DDR4 3200MHz������VS2019-Debug-x86����ĳ��򣬴�Լ��ʱ240-260��" << endl;
#else
			cout << "    Linux�����������У���Լ��ʱ110-130�루�������ͬʱ���ԣ�ƫ����ܽϴ�" << endl;
#endif
		}
		else {
			cout << "�ڴ����ܲ���(s1+=str��ʽ)" << endl;
#if !(defined(__linux) || defined(__linux__))
			cout << "    ��ʦ�Ļ�����CPU��AMD Ryzen 7 4700U, �ڴ棺DDR4 3200MHz������VS2019-Debug-x86����ĳ��򣬴�Լ��ʱ100-120��" << endl;
#else
			cout << "    Linux�����������У���Լ��ʱ50-70�루�������ͬʱ���ԣ�ƫ����ܽϴ�" << endl;
#endif
		}
		cout << "    ��˵������ֻ����ͬ�������µ�����ʱ����пɱ���" << endl;
		cout << "              ���ʱ�����̫�󣬳�CPU���ڴ�����ܲ����⣬���п������㷨����" << endl;

#if !(defined(__linux) || defined(__linux__))
		cout << endl << "�۲�����������б�������ڴ�ռ�����(��������115MB)..." << endl;
#endif
		wait_for_enter();
	}

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/

/*int main()
{
	TStringAdv s1 = "1235",s2="ABC�Բ�DEF",s3;
	s1.insert(s3, 3);
	//s1.erase("12");
	cout << s1 << endl;
	for (int i = 0; i < 4; i++) {
		cout << s1[i] << " " << s1.at(i) << endl;;
	}cout << endl;
	cout << s1.substr(6, 5);
}*/
int main()
{
	if (1) {
		const TStringAdv s1;                 //s1ΪNULL
		const TStringAdv s2("teststr2");      //s2Ϊ"teststr2"
		const TStringAdv s3 = "teststr3";       //s3Ϊ"teststr3"
		const TStringAdv s4 = NULL;            //s4ΪNULL
		const TStringAdv s5 = "";              //s5ΪNULL

		cout << "������󲢳�ʼ������(NULL���ַ���������ʼ��)" << endl;

		cout << "s1Ӧ����<NULL>��  ʵ�������" << s1 << endl;
		cout << "s2Ӧ����teststr2��ʵ�������" << s2 << endl;
		cout << "s3Ӧ����teststr3��ʵ�������" << s3 << endl;
		cout << "s4Ӧ����<NULL>��  ʵ�������" << s4 << endl;
		cout << "s5Ӧ����<NULL>��  ʵ�������" << s5 << endl;

		wait_for_enter();
	}

	if (1) {
		const TStringAdv s0 = "teststr1";
		const char* str1 = "teststr2";
		const char  str2[] = "teststr3";
		const char* str3 = NULL;
		const char  str4[] = "";
		const TStringAdv s1 = s0, s2 = str1, s3 = str2, s4 = str3, s5 = str4;

		cout << "������󲢳�ʼ������(TString�����ַ�ָ�롢�ַ�����)" << endl;

		cout << "s1Ӧ����teststr1��ʵ�������" << s1 << endl;
		cout << "s2Ӧ����teststr2��ʵ�������" << s2 << endl;
		cout << "s3Ӧ����teststr3��ʵ�������" << s3 << endl;
		cout << "s4Ӧ����<NULL>��  ʵ�������" << s4 << endl;
		cout << "s5Ӧ����<NULL>��  ʵ�������" << s5 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;

		cout << "����cin����" << endl;

		cout << "���ڼ���������Hello" << endl;
		cin >> s1;
		cout << "s1Ӧ����Hello��ʵ�������" << s1 << endl;

		cout << "���ڼ���������Hello 123" << endl;
		cin >> s1;
		cout << "s1Ӧ����Hello��ʵ�������" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Hello"), s2;

		cout << "��ֵ��������" << endl;

		cout << "s1Ӧ����Hello�� ʵ�������" << s1 << endl;

		s2 = s1;
		cout << "s2Ӧ����Hello�� ʵ�������" << s2 << endl;

		s1 = "Hi";
		cout << "s1Ӧ����Hi��    ʵ�������" << s1 << endl;

		s2 = "";
		cout << "s2Ӧ����<NULL>��ʵ�������" << s2 << endl;

		s1 = NULL;
		cout << "s1Ӧ����<NULL>��ʵ�������" << s1 << endl;

		s1 = "Hello";
		cout << "s1Ӧ����Hello�� ʵ�������" << (s1 = s1) << endl;
		cout << "s1Ӧ����Hello�� ʵ�������" << (s1 = s1 = s1 = s1 = s1) << endl;
		cout << "s1Ӧ����Hello�� ʵ�������" << (((s1 = s1) = s1) = s1) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s0, s1("tong"), s2("ji"), s3;

		cout << "����(+)����(����TString��)" << endl;

		s3 = s1 + s2;
		cout << "s3ӦΪtongji��ʵ�������" << s3 << endl;

		s3 = s2 + s1;
		cout << "s3ӦΪjitong��ʵ�������" << s3 << endl;

		s3 = s1 + s0;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = s0 + s2;
		cout << "s3ӦΪji��    ʵ�������" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s2, s3;

		cout << "����(+)����(TString����ַ�������)" << endl;

		s3 = s1 + "ji";
		cout << "s3ӦΪtongji��ʵ�������" << s3 << endl;

		s3 = "ji" + s1;
		cout << "s3ӦΪjitong��ʵ�������" << s3 << endl;

		s3 = s1 + "";
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = s1 + (char*)NULL;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = "" + s1;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = (char*)NULL + s1;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = s2 + (char*)NULL;
		cout << "s3ӦΪ<NULL>��ʵ�������" << s3 << endl;

		s3 = (char*)NULL + s2;
		cout << "s3ӦΪ<NULL>��ʵ�������" << s3 << endl;

		s3 = s2 + "";
		cout << "s3ӦΪ<NULL>��ʵ�������" << s3 << endl;

		s3 = "" + s2;
		cout << "s3ӦΪ<NULL>��ʵ�������" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s3;
		const char* str1 = "ji", * str2 = "", * str3 = NULL;

		cout << "����(+)����(TString����ַ�ָ��)" << endl;

		s3 = s1 + str1;
		cout << "s3ӦΪtongji��ʵ�������" << s3 << endl;

		s3 = str1 + s1;
		cout << "s3ӦΪjitong��ʵ�������" << s3 << endl;

		s3 = s1 + str2;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = str2 + s1;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = s1 + str3;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = str3 + s1;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s3;
		char str1[] = "ji", str2[] = "";

		cout << "����(+)����(TString����ַ�����)" << endl;

		s3 = s1 + str1;
		cout << "s3ӦΪtongji��ʵ�������" << s3 << endl;

		s3 = str1 + s1;
		cout << "s3ӦΪjitong��ʵ�������" << s3 << endl;

		s3 = s1 + str2;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = str2 + s1;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Hello"), s3;
		char c = '!';

		cout << "����(+)����(TString����ַ�)" << endl;

		s3 = s1 + c;
		cout << "s3ӦΪHello!��ʵ�������" << s3 << endl;

		s3 = c + s1;
		cout << "s3ӦΪ!Hello��ʵ�������" << s3 << endl;

		s1 = "ello";
		cout << "s3ӦΪHello!��ʵ�������" << 'H' + s1 + c << endl;

		s1 = "hina";
		cout << "s3ӦΪChina!��ʵ�������" << (s1 = 'C' + s1 + c) << endl;

		wait_for_enter();
	}

	if (1) {
		const TStringAdv s1("��"), s3 = "��", s5 = "Ҳ";
		TStringAdv s;
		const char* str2 = "��", str4[] = "��";
		const char c = '!';

		cout << "����(+)�ۺϲ���(TString���TString�ࡢ�ַ�ָ�롢�ַ����顢�ַ�)" << endl;
		s = s1 + str2 + s3 + str4 + s5 + c;
		cout << "sӦ���ǿ�������Ҳ!��ʵ�������" << s << endl;

		cout << "sӦ����Ҳ��������!��ʵ�������" << (s = s5 + s1 + str2 + s3 + str4[0] + str4[1] + c) << endl;
		cout << "sӦ������Ҳ������!��ʵ�������" << (s = str4 + s5 + s1.c_str() + str2 + s3 + c) << endl;
		cout << "sӦ��������Ҳ����!��ʵ�������" << (s = s3 + str4 + s5 + s1 + str2[0] + &str2[1] + c) << endl;
		cout << "sӦ����������Ҳ��!��ʵ�������" << (s = str2 + s3 + str4 + s5.c_str() + s1.c_str() + c) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s2 = "ji";
		const char* str3 = "tong", str4[] = "ji";

		cout << "������(+=)�򵥲���(TString���TString�ࡢ�ַ�ָ�롢�ַ����顢�ַ�)" << endl;

		s1 += s2;
		cout << "s1ӦΪtongji��ʵ�������" << s1 << endl;

		s1 = "tong";
		s2 += s1;
		cout << "s2ӦΪjitong��ʵ�������" << s2 << endl;

		s1 = "tong";
		s1 += "ji";
		cout << "s1ӦΪtongji��ʵ�������" << s1 << endl;

		s1 = "ji";
		s1 += str3;
		cout << "s1ӦΪjitong��ʵ�������" << s1 << endl;

		s1 = "tong";
		s1 += str4;
		cout << "s1ӦΪtongji��ʵ�������" << s1 << endl;

		s1 = "tong";
		s1 += 'j';
		s1 += 'i';
		cout << "s1ӦΪtongji��ʵ�������" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("��"), s3 = "��", s5 = "Ҳ";
		TStringAdv s;
		const char* str2 = "��", str4[] = "��";
		const char c = '!';

		cout << "������(+=)�ۺϲ���(TString���TString�ࡢ�ַ�ָ�롢�ַ����顢�ַ�)" << endl;

		s = "1.";
		s += s1 + str2 + s3 + str4 + s5 + c;
		cout << "sӦ����1.��������Ҳ!��ʵ�������" << s << endl;

		s = "2.";
		cout << "sӦ����2.Ҳ��������!��ʵ�������" << (s += s5 + s1 + str2 + s3 + str4[0] + str4[1] + c) << endl;

		s = NULL;
		cout << "sӦ����3.��Ҳ������!��ʵ�������" << ((s = "3.") += str4 + s5 + s1.c_str() + str2 + s3 + c) << endl;

		s = NULL;
		cout << "sӦ����4.����Ҳ����!��ʵ�������" << (((s += "4." + s3) += (str4 + s5)) += (((s1 += str2[0]) += &str2[1]) += c)) << endl;

		s = NULL;
		s += '5';
		s += '.';
		s1 = "��";
		cout << "sӦ����5.������Ҳ��!��ʵ�������" << ((((((s += str2) += s3) += str4) += s5.c_str()) += s1.c_str()) += c) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil"), s2("is"), s3;

		cout << "ɾ��(-)����(TString���TString��)" << endl;

		cout << "s1ӦΪTh is a pencil��ʵ�������" << (s1 = s1 - s2) << endl;
		s3 = s1 - s2;
		cout << "s3ӦΪTh  a pencil��  ʵ�������" << s3 << endl;

		s1 = "This is a pencil";
		cout << "s1ӦΪTh  a pencil��  ʵ�������" << s1 - s2 - s2 - s2 - s2 - s2 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil"), s2;
		const char* str1 = "is";
		const char str2[] = "is";

		cout << "ɾ��(-)����(TString���charָ�뼰����)" << endl;

		cout << "s1ӦΪTh is a pencil��ʵ�������" << (s1 = s1 - str1) << endl;
		s2 = s1 - str1;
		cout << "s2ӦΪTh  a pencil��  ʵ�������" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s1ӦΪTh is a pencil��ʵ�������" << (s1 = s1 - str2) << endl;
		s2 = s1 - str2;
		cout << "s2ӦΪTh  a pencil��  ʵ�������" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s1ӦΪTh  a pencil��  ʵ�������" << s1 - str1 - str1 - str1 - str1 - str1 << endl;

		s1 = "This is a pencil";
		cout << "s1ӦΪTh  a pencil��  ʵ�������" << s1 - str2 - str2 - str2 - str2 - str2 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil"), s2;
		char c1 = 'i';

		cout << "ɾ��(-)����(TString���char�ַ�)" << endl;

		cout << "s1ӦΪThs is a pencil��ʵ�������" << (s1 = s1 - c1) << endl;
		s2 = s1 - c1;
		cout << "s2ӦΪThs s a pencil�� ʵ�������" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s2ӦΪThs s a pencl��  ʵ�������" << (s1 - c1 - c1 - c1 - c1 - c1 - c1 - c1) << endl;

		s1 = "This is a pencil";
		cout << "s1ӦΪThi is a pencil��ʵ�������" << (s1 = s1 - 's') << endl;
		s2 = s1 - 's';
		cout << "s2ӦΪThi i a pencil�� ʵ�������" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s2ӦΪThi i a pencil�� ʵ�������" << (s1 - 's' - 's' - 's' - 's' - 's' - 's') << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;
		const TStringAdv s2 = "is";
		const char* str3 = "pen", str4[] = "a";
		const char c = ' ';

		cout << "��ɾ��(-=)�򵥲���(TString���TString�ࡢ�ַ�ָ�롢�ַ����顢�ַ�)" << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪTh is a red pencil�� ʵ�������" << (s1 -= s2) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThis is a red cil��  ʵ�������" << (s1 -= str3) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThis is  red pencil��ʵ�������" << (s1 -= str4) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThisis a red pencil��ʵ�������" << (s1 -= c) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;
		const TStringAdv s2 = "is";
		const char* str3 = "pen", str4[] = "a";
		const char c = ' ';

		cout << "��ɾ��(-=)�ۺϲ���(TString���TString�ࡢ�ַ�ָ�롢�ַ����顢�ַ�)" << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪTh  a red pencil��   ʵ�������" << ((s1 -= s2) -= s2) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThis is  red cil��   ʵ�������" << ((s1 -= str3) -= str4) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThisisaredpencil��   ʵ�������" << ((((s1 -= c) -= c) -= c) -= c) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪTh��                 ʵ�������" << ((((((((((((s1 -= s2) -= s2) -= str3) -= str4) -= c) -= c) -= c) -= c) -= "red") -= 'c') -= 'i') -= 'l') << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Hello"), s2;

		cout << "����(*)����(TString���int)" << endl;

		s2 = s1 * 2;
		cout << "s2ӦΪHelloHello��     ʵ�������" << s2 << endl;
		cout << "s1ӦΪHelloHelloHello��ʵ�������" << (s1 = s1 * 3) << endl;

		TStringAdv s3;
		cout << "s3ӦΪ<NULL>��         ʵ�������" << (s3 * 5) << endl;
		cout << "s3ӦΪ<NULL>��         ʵ�������" << (s3 = s3 * 5) << endl;

		int i, n = 100;
		s1 = "Hello";
		s2 = s1 * n;
		for (i = 1; i < n; i++)
			s2 = s2 - s1;
		cout << "s2ӦΪHello��          ʵ�������" << s2 << endl;

		s1 = "Hello";
		s2 = s1 * n;
		for (i = 0; i < n; i++)
			s2 = s2 - 'l';
		for (i = 0; i < n; i++)
			s2 = s2 - 'l';
		for (i = 0; i < n; i++)
			s2 = s2 - 'o';
		for (i = 0; i < n; i++)
			s2 = s2 - 'H';
		for (i = 1; i < n; i++)  //ע�⣬ֻ�����ѭ���Ǵ�1��ʼ������1��
			s2 = s2 - 'e';
		cout << "s2ӦΪe��              ʵ�������" << s2 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;

		cout << "�Ը���(*=)����(TString���int)" << endl;

		s1 = "Hello";
		cout << "s1ӦΪHelloHello��                       ʵ�������" << (s1 *= 2) << endl;
		s1 += '!';
		cout << "s1ӦΪHelloHello!HelloHello!HelloHello!��ʵ�������" << (s1 *= 3) << endl;

		s1 = "Hello";
		cout << "s1ӦΪHelloHello!HelloHello!HelloHello!��ʵ�������" << (((s1 *= 2) += '!') *= 3) << endl;

		//		�ر���ԣ����������е�ע�ͣ������������ᱨ�����������˵�����������⣬������Ԥ�ڵ����壨Ϊʲô����ϸ��!!!��
		//		cout << "s1ӦΪHelloHello!HelloHello!HelloHello!��ʵ�������" << (((s1 *= 2) + '!') *= 3) << endl;

		s1 = NULL;
		cout << "s1ӦΪ<NULL>��                           ʵ�������" << (s1 *= 100) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;

		cout << "������(+=)/��ɾ��(-=)/�Ը���(*=)�ۺϲ���" << endl;

		s1 = "Hello";
		cout << "s1ӦΪHello!Hello!Hello!��ʵ�������" << ((s1 += '!') *= 3) << endl;

		s1 = "Hello";
		cout << "s1ӦΪHeo!Heo!Heo!Heo!��  ʵ�������" << (((s1 += '!') -= "ll") *= 4) << endl;

		s1 = "Hello";
		cout << "s1ӦΪHellHello!��        ʵ�������" << (((s1 *= 2) -= 'o') += '!') << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil");

		cout << "��ת(!)����" << endl;

		cout << " s1ӦΪThis is a pencil��ʵ�������" << s1 << endl;
		cout << "!s1ӦΪlicnep a si sihT��ʵ�������" << !s1 << endl;
		cout << " s1��ΪThis is a pencil��ʵ�������" << s1 << endl;

		s1 = NULL;
		cout << " s1ӦΪ<NULL>��          ʵ�������" << s1 << endl;
		cout << "!s1ӦΪ<NULL>��          ʵ�������" << !s1 << endl;
		cout << " s1��Ϊ<NULL>��          ʵ�������" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house", s2 = "horse", s3 = "house", s4 = "", s5 = NULL;

		cout << "�Ƚ��������(����TString��)" << endl;

		cout << "��1=" << s1 << " ��2=" << s2 << "  > ���ӦΪ1��ʵ�ʣ�" << (s1 > s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "  >=���ӦΪ1��ʵ�ʣ�" << (s1 >= s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "  < ���ӦΪ0��ʵ�ʣ�" << (s1 < s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "  <=���ӦΪ0��ʵ�ʣ�" << (s1 <= s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "  ==���ӦΪ0��ʵ�ʣ�" << (s1 == s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "  !=���ӦΪ1��ʵ�ʣ�" << (s1 != s2) << endl;

		cout << "��1=" << s1 << " ��3=" << s3 << "  > ���ӦΪ0��ʵ�ʣ�" << (s1 > s3) << endl;
		cout << "��1=" << s1 << " ��3=" << s3 << "  >=���ӦΪ1��ʵ�ʣ�" << (s1 >= s3) << endl;
		cout << "��1=" << s1 << " ��3=" << s3 << "  < ���ӦΪ0��ʵ�ʣ�" << (s1 < s3) << endl;
		cout << "��1=" << s1 << " ��3=" << s3 << "  <=���ӦΪ1��ʵ�ʣ�" << (s1 <= s3) << endl;
		cout << "��1=" << s1 << " ��3=" << s3 << "  ==���ӦΪ1��ʵ�ʣ�" << (s1 == s3) << endl;
		cout << "��1=" << s1 << " ��3=" << s3 << "  !=���ӦΪ0��ʵ�ʣ�" << (s1 != s3) << endl;

		cout << "��1=" << s1 << " ��4=" << s4 << " > ���ӦΪ1��ʵ�ʣ�" << (s1 > s4) << endl;
		cout << "��1=" << s1 << " ��4=" << s4 << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= s4) << endl;
		cout << "��1=" << s1 << " ��4=" << s4 << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < s4) << endl;
		cout << "��1=" << s1 << " ��4=" << s4 << " <=���ӦΪ0��ʵ�ʣ�" << (s1 <= s4) << endl;
		cout << "��1=" << s1 << " ��4=" << s4 << " ==���ӦΪ0��ʵ�ʣ�" << (s1 == s4) << endl;
		cout << "��1=" << s1 << " ��4=" << s4 << " !=���ӦΪ1��ʵ�ʣ�" << (s1 != s4) << endl;

		cout << "��1=" << s1 << " ��5=" << s5 << " > ���ӦΪ1��ʵ�ʣ�" << (s1 > s5) << endl;
		cout << "��1=" << s1 << " ��5=" << s5 << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= s5) << endl;
		cout << "��1=" << s1 << " ��5=" << s5 << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < s5) << endl;
		cout << "��1=" << s1 << " ��5=" << s5 << " <=���ӦΪ0��ʵ�ʣ�" << (s1 <= s5) << endl;
		cout << "��1=" << s1 << " ��5=" << s5 << " ==���ӦΪ0��ʵ�ʣ�" << (s1 == s5) << endl;
		cout << "��1=" << s1 << " ��5=" << s5 << " !=���ӦΪ1��ʵ�ʣ�" << (s1 != s5) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";

		cout << "�Ƚ��������(TString����ַ�������)" << endl;

		cout << "��1=" << s1 << " ����=horse" << "  > ���ӦΪ1��ʵ�ʣ�" << (s1 > "horse") << endl;
		cout << "��1=" << s1 << " ����=horse" << "  >=���ӦΪ1��ʵ�ʣ�" << (s1 >= "horse") << endl;
		cout << "��1=" << s1 << " ����=horse" << "  < ���ӦΪ0��ʵ�ʣ�" << (s1 < "horse") << endl;
		cout << "��1=" << s1 << " ����=horse" << "  <=���ӦΪ0��ʵ�ʣ�" << (s1 <= "horse") << endl;
		cout << "��1=" << s1 << " ����=horse" << "  ==���ӦΪ0��ʵ�ʣ�" << (s1 == "horse") << endl;
		cout << "��1=" << s1 << " ����=horse" << "  !=���ӦΪ1��ʵ�ʣ�" << (s1 != "horse") << endl;

		cout << "��1=" << s1 << " ����=house" << "  > ���ӦΪ0��ʵ�ʣ�" << (s1 > "house") << endl;
		cout << "��1=" << s1 << " ����=house" << "  >=���ӦΪ1��ʵ�ʣ�" << (s1 >= "house") << endl;
		cout << "��1=" << s1 << " ����=house" << "  < ���ӦΪ0��ʵ�ʣ�" << (s1 < "house") << endl;
		cout << "��1=" << s1 << " ����=house" << "  <=���ӦΪ1��ʵ�ʣ�" << (s1 <= "house") << endl;
		cout << "��1=" << s1 << " ����=house" << "  ==���ӦΪ1��ʵ�ʣ�" << (s1 == "house") << endl;
		cout << "��1=" << s1 << " ����=house" << "  !=���ӦΪ0��ʵ�ʣ�" << (s1 != "house") << endl;

		cout << "��1=" << s1 << " ����=" << "       > ���ӦΪ1��ʵ�ʣ�" << (s1 > "") << endl;
		cout << "��1=" << s1 << " ����=" << "       >=���ӦΪ1��ʵ�ʣ�" << (s1 >= "") << endl;
		cout << "��1=" << s1 << " ����=" << "       < ���ӦΪ0��ʵ�ʣ�" << (s1 < "") << endl;
		cout << "��1=" << s1 << " ����=" << "       <=���ӦΪ0��ʵ�ʣ�" << (s1 <= "") << endl;
		cout << "��1=" << s1 << " ����=" << "       ==���ӦΪ0��ʵ�ʣ�" << (s1 == "") << endl;
		cout << "��1=" << s1 << " ����=" << "       !=���ӦΪ1��ʵ�ʣ�" << (s1 != "") << endl;

		cout << "��1=" << s1 << " ����=<NULL>" << " > ���ӦΪ1��ʵ�ʣ�" << (s1 > NULL) << endl;
		cout << "��1=" << s1 << " ����=<NULL>" << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= NULL) << endl;
		cout << "��1=" << s1 << " ����=<NULL>" << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < NULL) << endl;
		cout << "��1=" << s1 << " ����=<NULL>" << " <=���ӦΪ0��ʵ�ʣ�" << (s1 <= NULL) << endl;
		cout << "��1=" << s1 << " ����=<NULL>" << " ==���ӦΪ0��ʵ�ʣ�" << (s1 == NULL) << endl;
		cout << "��1=" << s1 << " ����=<NULL>" << " !=���ӦΪ1��ʵ�ʣ�" << (s1 != NULL) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = NULL, s2 = "";

		///* �յ�TString��NULL��"" ����Ϊ��ȣ������ϣ�NULL�ǵ�ַ��""�Ǵ���û�пɱ��ԣ����Ǵ˴������⴦�� 
		cout << "��1=" << s1 << " ��2=" << s2 << "  > ���ӦΪ0��ʵ�ʣ�" << (s1 > s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "  >=���ӦΪ1��ʵ�ʣ�" << (s1 >= s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "  < ���ӦΪ0��ʵ�ʣ�" << (s1 < s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "  <=���ӦΪ1��ʵ�ʣ�" << (s1 <= s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "  ==���ӦΪ1��ʵ�ʣ�" << (s1 == s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "  !=���ӦΪ0��ʵ�ʣ�" << (s1 != s2) << endl;

		cout << "��1=" << s1 << " ����=" << "       > ���ӦΪ0��ʵ�ʣ�" << (s1 > "") << endl;
		cout << "��1=" << s1 << " ����=" << "       >=���ӦΪ1��ʵ�ʣ�" << (s1 >= "") << endl;
		cout << "��1=" << s1 << " ����=" << "       < ���ӦΪ0��ʵ�ʣ�" << (s1 < "") << endl;
		cout << "��1=" << s1 << " ����=" << "       <=���ӦΪ1��ʵ�ʣ�" << (s1 <= "") << endl;
		cout << "��1=" << s1 << " ����=" << "       ==���ӦΪ1��ʵ�ʣ�" << (s1 == "") << endl;
		cout << "��1=" << s1 << " ����=" << "       !=���ӦΪ0��ʵ�ʣ�" << (s1 != "") << endl;

		cout << "��1=" << s1 << " ����=<NULL>" << " > ���ӦΪ0��ʵ�ʣ�" << (s1 > NULL) << endl;
		cout << "��1=" << s1 << " ����=<NULL>" << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= NULL) << endl;
		cout << "��1=" << s1 << " ����=<NULL>" << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < NULL) << endl;
		cout << "��1=" << s1 << " ����=<NULL>" << " <=���ӦΪ1��ʵ�ʣ�" << (s1 <= NULL) << endl;
		cout << "��1=" << s1 << " ����=<NULL>" << " ==���ӦΪ1��ʵ�ʣ�" << (s1 == NULL) << endl;
		cout << "��1=" << s1 << " ����=<NULL>" << " !=���ӦΪ0��ʵ�ʣ�" << (s1 != NULL) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";
		const char* str2 = "horse", * str3 = "house", * str4 = "", * str5 = NULL;

		cout << "�Ƚ��������(TString����ַ�ָ��)" << endl;

		cout << "��1=" << s1 << " ��2=" << str2 << "  > ���ӦΪ1��ʵ�ʣ�" << (s1 > str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << "  >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << "  < ���ӦΪ0��ʵ�ʣ�" << (s1 < str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << "  <=���ӦΪ0��ʵ�ʣ�" << (s1 <= str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << "  ==���ӦΪ0��ʵ�ʣ�" << (s1 == str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << "  !=���ӦΪ1��ʵ�ʣ�" << (s1 != str2) << endl;

		cout << "��1=" << s1 << " ��3=" << str3 << "  > ���ӦΪ0��ʵ�ʣ�" << (s1 > str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << "  >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << "  < ���ӦΪ0��ʵ�ʣ�" << (s1 < str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << "  <=���ӦΪ1��ʵ�ʣ�" << (s1 <= str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << "  ==���ӦΪ1��ʵ�ʣ�" << (s1 == str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << "  !=���ӦΪ0��ʵ�ʣ�" << (s1 != str3) << endl;

		cout << "��1=" << s1 << " ��4=" << str4 << "       > ���ӦΪ1��ʵ�ʣ�" << (s1 > str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "       >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "       < ���ӦΪ0��ʵ�ʣ�" << (s1 < str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "       <=���ӦΪ0��ʵ�ʣ�" << (s1 <= str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "       ==���ӦΪ0��ʵ�ʣ�" << (s1 == str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "       !=���ӦΪ1��ʵ�ʣ�" << (s1 != str4) << endl;

		cout << "��1=" << s1 << " ��5=<NULL>" << " > ���ӦΪ1��ʵ�ʣ�" << (s1 > str5) << endl;
		cout << "��1=" << s1 << " ��5=<NULL>" << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str5) << endl;
		cout << "��1=" << s1 << " ��5=<NULL>" << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < str5) << endl;
		cout << "��1=" << s1 << " ��5=<NULL>" << " <=���ӦΪ0��ʵ�ʣ�" << (s1 <= str5) << endl;
		cout << "��1=" << s1 << " ��5=<NULL>" << " ==���ӦΪ0��ʵ�ʣ�" << (s1 == str5) << endl;
		cout << "��1=" << s1 << " ��5=<NULL>" << " !=���ӦΪ1��ʵ�ʣ�" << (s1 != str5) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";
		char str2[] = "horse", str3[] = "house", str4[] = "";

		cout << "�Ƚ��������(TString����ַ�ָ��)" << endl;

		cout << "��1=" << s1 << " ��2=" << str2 << " > ���ӦΪ1��ʵ�ʣ�" << (s1 > str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << " <=���ӦΪ0��ʵ�ʣ�" << (s1 <= str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << " ==���ӦΪ0��ʵ�ʣ�" << (s1 == str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << " !=���ӦΪ1��ʵ�ʣ�" << (s1 != str2) << endl;

		cout << "��1=" << s1 << " ��3=" << str3 << " > ���ӦΪ0��ʵ�ʣ�" << (s1 > str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << " <=���ӦΪ1��ʵ�ʣ�" << (s1 <= str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << " ==���ӦΪ1��ʵ�ʣ�" << (s1 == str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << " !=���ӦΪ0��ʵ�ʣ�" << (s1 != str3) << endl;

		cout << "��1=" << s1 << " ��4=" << str4 << "      > ���ӦΪ1��ʵ�ʣ�" << (s1 > str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "      >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "      < ���ӦΪ0��ʵ�ʣ�" << (s1 < str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "      <=���ӦΪ0��ʵ�ʣ�" << (s1 <= str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "      ==���ӦΪ0��ʵ�ʣ�" << (s1 == str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "      !=���ӦΪ1��ʵ�ʣ�" << (s1 != str4) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "tong", s2;

		cout << "�󳤶Ȳ���(length()����)" << endl;

		cout << "s1Ϊtong��  ����ӦΪ4��ʵ�ʣ�" << s1.length() << endl;
		cout << "s2Ϊ<NULL>������ӦΪ0��ʵ�ʣ�" << s2.length() << endl;
		s2 = s1 + "ji";
		cout << "s2Ϊtongji������ӦΪ6��ʵ�ʣ�" << s2.length() << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "tong", s2;

		cout << "�󳤶Ȳ���(TStringLen()����)" << endl;

		cout << "s1Ϊtong��  ����ӦΪ4��ʵ�ʣ�" << TStringLen(s1) << endl;
		cout << "s2Ϊ<NULL>������ӦΪ0��ʵ�ʣ�" << TStringLen(s2) << endl;
		cout << "��Ϊtongji������ӦΪ6��ʵ�ʣ�" << TStringLen(s1 + (s2 = "ji")) << endl;
		cout << "��Ϊtongji������ӦΪ6��ʵ�ʣ�" << TStringLen(s1 + "ji") << endl;
		cout << "��Ϊtongji������ӦΪ6��ʵ�ʣ�" << TStringLen(s2 = s1 + "ji") << endl;
		cout << "��Ϊtong��  ����ӦΪ4��ʵ�ʣ�" << TStringLen(s1 + (char*)NULL) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";
		TStringAdv s2[4] = { "yangpu", "sipingroad", "tongji", "shanghai" };
		int i, j;
		char ch = 'P';

		cout << "[]���������" << endl;

		cout << "��1��" << s1 << "�����δ�ӡ�ַ��Ľ���ǣ�";
		for (i = 0; i < s1.length(); i++)
			cout << s1[i] << ' ';
		cout << endl << endl;

		cout << "��1��" << s1 << "�����δ�ӡ�ַ�intֵ�Ľ���ǣ���Խ�磩��" << endl;
		for (i = -4; i < s1.length() + 4; i++)
			cout << int(s1[i]) << ' ';
		cout << endl << endl;

		s1[0] = s1[0] - 32;
		cout << "��1��" << s1 << "�����δ�ӡ�ַ��Ľ���ǣ�";
		for (i = 0; i < s1.length(); i++)
			cout << s1[i] << ' ';
		cout << endl << endl;

		s1[1] = 'A';
		s1[2] = ch;
		ch += 32;
		s1[3] = ch;
		s1[4] = 'Y';
		cout << "��1��" << s1 << "�����δ�ӡ�ַ��Ľ���ǣ�";
		for (i = 0; i < s1.length(); i++)
			cout << s1[i] << ' ';
		cout << endl << endl;

		cout << "��2������4���ַ��������δ�ӡ�ַ��Ľ���ǣ�" << endl;
		for (i = 0; i < 4; i++) {
			cout << setw(16) << s2[i] << " => ";
			for (j = 0; j < s2[i].length(); j++)
				cout << s2[i][j] << ' ';
			cout << endl;
		}
		cout << endl;

		cout << "��2������4���ַ���������ĸ��д�����δ�ӡ�ַ��Ľ���ǣ�" << endl;
		for (i = 0; i < 4; i++) {
			s2[i][0] -= 32;
			cout << setw(16) << s2[i] << " => ";
			for (j = 0; j < s2[i].length(); j++)
				cout << s2[i][j] << ' ';
			cout << endl;
		}
		wait_for_enter();
	}

	if (0) {
		memory_speed_test(0);
		memory_speed_test(1);
	}

	if (1) {
		cout << "assign��������" << endl;
		TStringAdv s1("�Ƿ�"), s2="", s3;

		cout << "s1Ӧ�����Ƿ壬 ʵ�������" << s1 << endl;

		s3.assign(s1);
		cout << "s2Ӧ����<NULL>�� ʵ�������" << s2 << endl;
		cout << "s3Ӧ�����Ƿ壬 ʵ�������" << s3 << endl;

		s1.assign("����");
		cout << "s1Ӧ���Ƕ�����    ʵ�������" << s1 << endl;
		s2.assign("");
		cout << "s2Ӧ����<NULL>��ʵ�������" << s2 << endl;
		s3.assign((char*)NULL);
		cout << "s3Ӧ����<NULL>��ʵ�������" << s3 << endl;

		s1.assign("����");
		cout << "s1Ӧ�������� ʵ�������" << (s1.assign(s1)) << endl;
		cout << "s1Ӧ�������� ʵ�������" << (((s1.assign(s1)).assign(s1)).assign(s1)) << endl;
		cout << "s1Ӧ�������� ʵ�������" << (((s1.assign(s1)).assign(s1))).assign(s1) << endl;

		s2.assign('X');
		cout << "s1Ӧ����X�� ʵ�������" << s2<< endl;
		wait_for_enter();
	}

	if (1) {
		cout << "append��������" << endl;
		TStringAdv s1("�Ƿ�"), s2 = "�򹷰�", s3;

		const char* str3 = "�貨΢��", str4[] = "666";

		s1.append(s2);
		cout << "s1ӦΪ�Ƿ�򹷰���ʵ�������" << s1 << endl;

		s1 = "����";
		s2.append(s1);
		cout << "s2ӦΪ�򹷰�������ʵ�������" << s2 << endl;

		s1 = "������";
		s1.append("������");
		cout << "s1ӦΪ�����ﻯ���󷨣�ʵ�������" << s1 << endl;

		s1 = "����ˮ";
		s1.append(str3);
		cout << "s1ӦΪ����ˮ�貨΢����ʵ�������" << s1 << endl;
		
		s1 = "���������շ���";
		s1.append((char*)NULL);
		cout << "s1ӦΪ���������շ��У�ʵ�������" << s1 << endl;

		s1 = "������";
		s1.append(str4);
		cout << "s1ӦΪ������666��ʵ�������" << s1 << endl;

		s1 = "��";
		s1.append('y');
		s1.append('u');
		cout << "s1ӦΪ��yu��ʵ�������" << s1 << endl;
		wait_for_enter();

	}

	if (1) {
		cout << "append�����ۺϲ���" << endl;
		TStringAdv s1("��"), s3 = "��", s5 = "Ҳ";
		TStringAdv s;
		s = "1.";
		const char* str2 = "��", str4[] = "��";
		const char c = '!';
		s += s1 + str2 + s3 + str4 + s5 + c;
		cout << "sӦ����1.��������Ҳ!��ʵ�������" << s << endl;

		s = "2.";
		cout << "sӦ����2.Ҳ��������!��ʵ�������" << (s.append( s5 + s1 + str2 + s3 + str4[0] + str4[1] + c)) << endl;

		s = NULL;
		cout << "sӦ����3.��Ҳ������!��ʵ�������" << ((s = "3.").append(str4 + s5 + s1.c_str() + str2 + s3 + c)) << endl;

		s = NULL;
		cout << "sӦ����4.����Ҳ����!��ʵ�������" << (((s.append("4." + s3)).append(((str4 + s5))).append((((s1.append(str2[0])).append(&str2[1])).append(c))))) << endl;

		s = NULL;
		s += '5';
		s += '.';
		s1 = "��";
		cout << "sӦ����5.������Ҳ��!��ʵ�������" << ((((((s.append(str2).append(s3)).append(str4)).append(s5.c_str())).append(s1.c_str())).append(c))) << endl;
		wait_for_enter();
	}

	if (1) {
		cout << "insert��������" << endl;
		TStringAdv s1("1234"), s2 = "��ڤ����";

		s1.insert(s2,1);
		cout << "sӦ���Ǳ�ڤ����1234��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s2, 2);
		cout << "sӦ����1��ڤ����234��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s2, 3);
		cout << "sӦ����12��ڤ����34��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s2, 4);
		cout << "sӦ����123��ڤ��4�㣬ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s2, 5);
		cout << "sӦ����1234��ڤ���㣬ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s2, 5);
		cout << "sӦ����1234��ڤ���㣬ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s2, 100);
		cout << "sӦ����1234��ʵ�������" << s1 << endl;

		const char* s3 = "����Ϊ��";
		s1.insert(s3, 1);
		cout << "sӦ��������Ϊ��1234��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s3, 2);
		cout << "sӦ����1����Ϊ��234��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s3, 3);
		cout << "sӦ����12����Ϊ��34��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s3, 4);
		cout << "sӦ����123����Ϊ��4��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s3, 5);
		cout << "sӦ����1234����Ϊ�ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s3, 5);
		cout << "sӦ����1234����Ϊ�ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(s3, 100);
		cout << "sӦ����1234��ʵ�������" << s1 << endl;

		const char c = 'X';
		s1.insert(c, 1);
		cout << "sӦ����X1234��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(c, 2);
		cout << "sӦ����1X234��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(c, 3);
		cout << "sӦ����12X34��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(c, 4);
		cout << "sӦ����123X4��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(c, 5);
		cout << "sӦ����1234X��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(c, 5);
		cout << "sӦ����1234X��ʵ�������" << s1 << endl;
		s1 = "1234";
		s1.insert(c, 100);
		cout << "sӦ����1234��ʵ�������" << s1 << endl;

		s1 = "";
		s2 = "";
		s1.insert(s2, 1);
		cout << "sӦ����<NULL>��ʵ�������" << s1 << endl;

		s1 = "";
		s1.insert((char*)NULL,1);
		cout << "sӦ����<NULL>��ʵ�������" << s1 << endl;
		s1 = "";
		s2 = "123";
		s1.insert(s2, 2);
		cout << "sӦ����<NULL>��ʵ�������" << s1 << endl;
		s1 = "";
		s1.insert("abc", 2);
		cout << "sӦ����<NULL>��ʵ�������" << s1 << endl;
		s1 = "";
		s1.insert("abc", 1);
		cout << "sӦ����abc��ʵ�������" << s1 << endl;
		s1 = "";
		s2 = "ABC";
		s1.insert(s2, 1);
		cout << "sӦ����ABC��ʵ�������" << s1 << endl;
		s1 = "";
		s1.insert('C', 1);
		cout << "sӦ����C��ʵ�������" << s1 << endl;
		wait_for_enter();
	}

	if (1) {
		cout << "erase��������" << endl;
		TStringAdv s1;
		const TStringAdv s2 = "is";
		const char* str3 = "pen", str4[] = "a";
		const char c = ' ';

		s1 = "This is a red pencil";
		cout << "s1ӦΪTh is a red pencil�� ʵ�������" << (s1.erase(s2)) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThis is a red cil��  ʵ�������" << (s1.erase(str3)) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThis is  red pencil��ʵ�������" << (s1.erase(str4)) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThisis a red pencil��ʵ�������" << (s1.erase(c)) << endl;
		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;
		const TStringAdv s2 = "is";
		const char* str3 = "pen", str4[] = "a";
		const char c = ' ';
		cout << "erase�����ۺϲ���" << endl;
		
		s1 = "This is a red pencil";
		cout << "s1ӦΪTh  a red pencil��   ʵ�������" << ((s1.erase(s2)).erase(s2)) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThis is  red cil��   ʵ�������" << ((s1.erase(str3)).erase(str4)) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThisisaredpencil��   ʵ�������" << ((((s1.erase(c)).erase(c)).erase(c)).erase(c)) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪTh��                 ʵ�������" << ((((((((((((s1.erase(s2)).erase(s2)).erase(str3)).erase(str4)).erase(c))
			.erase(c)).erase(c)).erase(c)).erase("red")).erase('c')).erase('i')).erase('l')) << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "substr�����ۺϲ���" << endl;
		TStringAdv s1;
		cout << "s1ӦΪ<NULL>��   ʵ�������" << s1.substr(0,0)<< endl;
		s1 = "123456789";
		cout << "s1ӦΪ<NULL>��   ʵ�������" << s1.substr(0, 2) << endl;
		cout << "s1ӦΪ<NULL>��   ʵ�������" << s1.substr(2, 0) << endl;
		cout << "s1ӦΪ<NULL>��   ʵ�������" << s1.substr(10, 0) << endl;
		cout << "s1ӦΪ123456789��   ʵ�������" << s1.substr(1, 9) << endl;
		cout << "s1ӦΪ12345678��   ʵ�������" << s1.substr(1, 8) << endl;
		cout << "s1ӦΪ23456789��   ʵ�������" << s1.substr(2, 8) << endl;
		cout << "s1ӦΪ56��   ʵ�������" << s1.substr(5, 2) << endl;
		cout << "s1ӦΪ56789��   ʵ�������" << s1.substr(5, 100) << endl;
		
		cout << "s1ӦΪ123456789��   ʵ�������" << s1.substr(1) << endl;
		cout << "s1ӦΪ56789��   ʵ�������" << s1.substr(5) << endl;
		cout << "s1ӦΪ6789��   ʵ�������" << s1.substr(6) << endl;
		cout << "s1ӦΪ<NULL>��   ʵ�������" << s1.substr(10) << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "at�����ۺϲ���" << endl;
		TStringAdv s1 = "house";
		TStringAdv s2[4] = { "yangpu", "sipingroad", "tongji", "shanghai" };
		int i, j;
		char ch = 'P';


		cout << "��1��" << s1 << "�����δ�ӡ�ַ��Ľ���ǣ�";
		for (i = 0; i < s1.length(); i++)
			cout << s1.at(i) << ' ';
		cout << endl << endl;

		cout << "��1��" << s1 << "�����δ�ӡ�ַ�intֵ�Ľ���ǣ���Խ�磩��" << endl;
		for (i = -4; i < s1.length() + 4; i++)
			cout << int(s1.at(i)) << ' ';
		cout << endl << endl;

		s1[0] = s1[0] - 32;
		cout << "��1��" << s1 << "�����δ�ӡ�ַ��Ľ���ǣ�";
		for (i = 0; i < s1.length(); i++)
			cout << s1.at(i) << ' ';
		cout << endl << endl;

		s1[1] = 'A';
		s1[2] = ch;
		ch += 32;
		s1[3] = ch;
		s1[4] = 'Y';
		cout << "��1��" << s1 << "�����δ�ӡ�ַ��Ľ���ǣ�";
		for (i = 0; i < s1.length(); i++)
			cout << s1.at(i) << ' ';
		cout << endl << endl;

		cout << "��2������4���ַ��������δ�ӡ�ַ��Ľ���ǣ�" << endl;
		for (i = 0; i < 4; i++) {
			cout << setw(16) << s2[i] << " => ";
			for (j = 0; j < s2[i].length(); j++)
				cout << s2[i].at(j) << ' ';
			cout << endl;
		}
		cout << endl;

		cout << "��2������4���ַ���������ĸ��д�����δ�ӡ�ַ��Ľ���ǣ�" << endl;
		for (i = 0; i < 4; i++) {
			s2[i].at(0) -= 32;
			cout << setw(16) << s2[i] << " => ";
			for (j = 0; j < s2[i].length(); j++)
				cout << s2[i].at(j) << ' ';
			cout << endl;
		}
		wait_for_enter();
	}

	
#if !(defined(__linux) || defined(__linux__))
	system("pause"); //Linux����Ҫ
#endif

	return 0;
}
