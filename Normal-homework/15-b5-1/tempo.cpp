

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<fstream>
#include<conio.h>

#define For(i,l,r) for(int i=l;i<=r;++i)
#define sFor(i,l,r) for(int i=l;i<r;++i)
#define opFor(i,r,l) for(int i=r;i>=l;--i)
#define FFLUSH while(getchar()!='\n')
#define PAUSE while(_getch()!='\r')
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))

using namespace std;

const int N = 64;

struct Data
{
	const char* opt;
	int l;
	int r;
	int low;
	int high;
};
const struct Data list[] = {
	{ NULL,-1,-1,-1,-1 },
	{ "����ǳ�",1,16,0,0 },
	{ "����ֵ",17,18,0,10000 },
	{ "����ֵ",19,20,0,10000 },
	{ "����ֵ",21,22,0,8192 },
	{ "����ֵ",23,24,0,1024 },
	{ "��Ǯֵ",25,28,0,100000000 },
	{ "����ֵ",29,32,0,100000000 },
	{ "����ֵ",33,36,0,100000000 },
	{ "�ƶ��ٶ�ֵ",45,45,0, 100 },
	{ "�����ٶ�ֵ",46,46,0 ,100 },
	{ "������Χֵ",47,47,0,100 },
	{ "������ֵ",49,50,0,2000 },
	{ "������ֵ",51,52,0 ,2000 },
	{ "���ݶ�ֵ",53,53,0,100 },
	{ "����ֵ",54,54,0,100 },
	{ "����ֵ",55,55,0,100 },
	{ "�ȼ�ֵ",56,56,0,100 },
	{ "ħ��ֵ",57,58,0,10000 },
	{ "����ħ��ֵ",59,59,0, 100 },
	{ "ħ���˺���ֵ",60,60,0 ,100 },
	{ "������ֵ",61,61,0, 100 },
	{ "ħ��������ֵ",62,62,0 ,100 },
	{ "������ֵ",63,63,0,100 },
	{ "����ֵ",64,64,0,100 },
	{ NULL,-1,-1,-1,-1 }
};

bool Modify(short Hex[], const int l, const int r)
{
	ifstream infile;
	infile.open("game.dat", ios::binary);
	if (!infile.is_open())
	{
		cout << "Fail to search game.data" << endl;
		cout << "Press enter for continue...";
		PAUSE;
		return 0;
	}

	char cpy[N + 1];
	For(i, 1, N)
		cpy[i] = infile.get();
	infile.close();
	For(i, l, r)
		cpy[i] = char(Hex[i - l + 1]);

	ofstream outfile;
	outfile.open("game.dat", ios::binary);
	if (!outfile.is_open())
	{
		cout << "Fail to search game.data" << endl;
		cout << "Press enter for continue...";
		PAUSE;
		return 0;
	}
	outfile.write(cpy + 1, N);
	outfile.close();

	return 1;
}
void work(const int op)
{
	system("cls");
	cout << "The option you want to change: " << (list + op)->opt << "\n\n";
	short Hex[17] = { 0 };
	if (op == 1)
	{
		cout << "Please enter the new name(We will take first 15 bits if it is too long): ";
		char tmp[1000] = { "LoveTaihouForever" };
		cin >> tmp;
		int len = Min(strlen(tmp), 15);
		Hex[len] = '\0';
		For(i, 0, len)
			Hex[i + 1] = short(tmp[i]) & 0xff;
	}
	else
	{
		int l = (list + op)->low, r = (list + op)->high;
		cout << "Please enter the new data";
		cout << "([" << l << "-" << r << "]): ";
		int num;
		cin >> num;
		if (cin.fail())
		{
			cin.clear();
			num = -1;
		}
		if (num<l || num>r)
		{
			FFLUSH;
			cout << "Input Error" << endl;
			cout << "Press enter for continue...";
			PAUSE;
			return;
		}
		int n = (list + op)->r - (list + op)->l + 1;
		For(i, 1, n)
			Hex[i] = short(num) & 0xff, num >>= 8; //************* low to high
	}

	if (!Modify(Hex, (list + op)->l, (list + op)->r))
		return;
	cout << endl;
	cout << "Modify successfully" << endl;
	cout << "Press enter for continue...";
	PAUSE;
}

int select(int& op, const int n)
{
	cin >> op;
	if (cin.fail())
	{
		cin.clear();
		op = -1;
	}
	if (op<0 || op>n)
	{
		FFLUSH;
		return 0;
	}
	return 1;
}

bool output_menu(int& n)
{
	ifstream infile;
	infile.open("game.dat", ios::binary);
	if (!infile.is_open())
	{
		cout << "Fail to search game.data" << endl;
		cout << "Press enter for continue...";
		PAUSE;
		return 0;
	}

	system("cls");
	int i = 1;
	for (; (list + i)->opt != NULL; ++i)
		cout << setw(2) << i << "." << (list + i)->opt << endl;
	n = i - 1;
	cout << " 0.�˳�" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "Please select the option you want to change [1-" << n << "] ";

	return 1;
}

/*int main()
{
	while (1)
	{
		int n;
		if (!output_menu(n))
			return -1;
		int op;
		if (!select(op, n))
			continue;
		if (!op)
			break;
		work(op);
	}

	return 0;
}*/
