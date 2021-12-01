


/* -----------------------------------------

	 ���ļ����ܣ�
	1���ű� hanoi_main.cpp/hanoi_menu.cpp �еĸ��������õĲ˵������Ӧ��ִ�к���

	 ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------- */


   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ�
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/


#include"90-01-b1-hanoi.h"


int pop(int i)
{
	return stack[i][--top[i]];
}
void push(int x, int i)
{
	stack[i][top[i]] = x;
	top[i]++;
}

void print(int i, int n)
{
	int j = 0;
	while (j < top[i]) {
		cout << stack[i][j++] << " ";
	}

	int k = n - top[i];
	while (k-- > 0) {
		cout << "  ";
	}
}


void set(char& a, int& n)
{
	int i = (int)(a - 'A');
	for (; top[i] < n; top[i]++) {
		stack[i][top[i]] = (n - top[i]);
	}
}
void show_1(int& x, char a, char b, char c)
{
	cout << "# " << x << " " << a << "-->" << c << endl;
}
void show_2(int& x, char a, char b, char c)
{
	cout << "��" << setw(4) << i << "��(#" << x << " " << a << "-->" << c << endl;
}
void show_3(int& n, int& x, char a, char b, char c)
{
	cout << "��" << setw(4) << i << "��(#" << x << "):";
	cout << a << "-->" << c << "  ";
	cout << "A: ";
	print(0, n);
	cout << "|";
	cout << "B: ";
	print(1, n);
	cout << "|";
	cout << "C: ";
	print(2, n);
	cout << "|";
	cout << endl;
}
void show_4(int& x, char a, char b, char c)
{
	if (Time) {
		Sleep(Time);   //�ٶ�
	}
	else {             //����
		while (1)
		{
			char ch = getchar();
			if (ch == '\n')
				break;

		}
	}
	//�������ŵ��
	system("cls");
	cout << endl;
	for (int i = 14; i >= 0; i--) {
		if (i < top[0])
			cout << setw(12) << stack[0][i];
		else
			cout << "            ";

		if (i < top[1])
			cout << setw(12) << stack[1][i];
		else
			cout << "            ";

		if (i < top[2])
			cout << setw(12) << stack[2][i];
		else
			cout << "            ";
		cout << endl;
	}

	cout << "       " << "=================================" << endl;;
	cout << setw(12) << "A" << setw(12) << "B" << setw(12) << "C" << endl;
	cout << "\n\n\n";

	cout << "��" << setw(4) << i << "��(#" << x << "):";
	cout << a << "-->" << c << "  ";

}
void move_stack(int num, int n, int N, int& x, char a, char b, char c)//�ѵݹ麯�����ܲ�ֳ���
{
	i++;   //���ڼǲ�
	x++;   //���ڼ�¼�����ƶ����̺�
	int t_pop=0;
	switch (a) {
	case'A':
		t_pop = pop(0);
		break;
	case'B':
		t_pop = pop(1);
		break;
	case'C':
		t_pop = pop(2);
		break;
	default:
		break;
	}
	switch (c) {
	case'A':
		push(t_pop, 0);
		break;
	case'B':
		push(t_pop, 1);
		break;
	case'C':
		push(t_pop, 2);
		break;
	default:
		break;
	}
	if (num == 4)
		show_4(x, a, b, c);
	else if (num == 3)
		show_3(N, x, a, b, c);
	else if (num == 1)
		show_1(x, a, b, c);
	else if (num == 2)
		show_2(x, a, b, c);
	else if (num == 8) {
		Paint_3(N, top[(int)(a - 'A')], x, a, b, c, x, 0); //�ڶ���x����ɫ����ɫ�����ӺŰ󶨹�ϵ
		if (Time) {
			Sleep(Time);//�ٶ�
		}
		else {             //����
			while (1)
			{
				char ch = getchar();
				if (ch == '\n')
					break;
			}
		}
	}

	return;

}
void move(int& num, int n, int N, int& x, char a, char b, char c)
{
	if (n == 1)
		move_stack(num, n, N, x, a, b, c);
	else {
		x = 0;
		move(num, n - 1, N, x, a, c, b);
		x = n - 1;
		move(num, 1, N, x, a, b, c);
		x = 0;
		move(num, n - 1, N, x, b, a, c);
	}
}
void work(int& num, int& N, int& x, int& mode, char& Begin, char& Temp, char& End)
{
	switch (mode)
	{
	case 1:Time = 1000; break;
	case 2:Time = 800; break;
	case 3:Time = 600; break;
	case 4:Time = 400; break;
	case 5:Time = 200; break;
	}
	if (num == 3) {
		cout << "��ʼ��" << "              ";
		cout << "A: ";
		print(0, N);
		cout << "|";
		cout << "B: ";
		print(1, N);
		cout << "|";
		cout << "C: ";
		print(2, N);
		cout << "|";
		cout << endl;
	}
	move(num, N, N, x, Begin, Temp, End);

}

void Change_speed(int& mode)
{
	while (1) {
		cout << "�������ƶ��ٶ�(0-5��0-���س�������ʾ 1-��ʱ� 5-��ʱ���";
		cin >> mode;
		while (cin.fail()) {        //��ֹ��ѭ��
			cin.clear();
			cin.ignore(100, '\n');
			cout << "�������ƶ��ٶ�(0-5��0-���س�������ʾ 1-��ʱ� 5-��ʱ���" << endl;
			cin >> mode;
		}
		if (mode <= 5 && mode >= 0)
			break;
		else
			continue;
	}

}
void init(int& n, char& Begin, char& Temp, char& End, int game_top[])
{
	while (1) {                       //����������
		cout << "���������n(1-10)��" << endl;
		cin >> n;
		while (cin.fail()) {        //��ֹ��ѭ��
			cin.clear();
			cin.ignore(100, '\n');
			cout << "���������n(1-10)��" << endl;
			cin >> n;
		}
		if (n <= 10 && n >= 1)
			break;
		else
			continue;
	}


	int tag[3] = { 0,0,0 };   //�ƶ�Temp����
	while (1) {  //������ʼԲ�����
		cout << "������ʼԲ��<A-C>";
		cin >> Begin;
		if (Begin <= 'C' && Begin >= 'A' ){	 //��֤��Сд����
				tag[(Begin - 'A')] = 1;
			break;
		}
		else if (Begin <= 'c' && Begin >= 'a') {
			Begin -= 32;
			tag[(Begin - 'A')] = 1;
			break;
		}
		else
			continue;
	}
	while (1) {          //������ֹԲ�����
		cout << "������ֹԲ��<A-C>";
		cin >> End;
		if (Begin == End) {
			cout << "��ʼ��ֹԲ��������ͬ����������" << endl;
			continue;
		}
		if ((End <= 'C') && (End >= 'A')) {
			tag[End - 'A'] = 1;
			break;
		}
		else if (End <= 'c' && End >= 'a') {
			End -= 32;
			tag[End - 'A'] = 1;
			break;
		}
		else
			continue;

	}

	if (!tag[0])
		Temp = 'A';
	else if (!tag[1])
		Temp = 'B';
	else
		Temp = 'C';


	game_top[Begin - 'A'] = 1;
	game_top[Temp - 'A'] = 0;
	game_top[End - 'A'] = 0;



}
void Clear()
{
	i = 0;    //����
	//int stack[3][15];//���������ϵ�����
	top[0] = 0;
	top[1] = 0;
	top[2] = 0;
	Time = 0;
	cout << "���س��˳�" << endl;
	char ch = _getch();
	while (ch != 13) {
		ch = _getch();
	}
}

//��ͼ
void Paint_1()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j <= 20; j++) {
			cct_showstr(30 * i + j, 18, " ", 14, 7, 1, -1);
			Sleep(10);
		}
		for (int k = 17; k >= 2; k--) {
			cct_showstr(i * 30 + 10, k, " ", 14, 7, 1, -1);
			Sleep(10);
		}
	}
}
void Paint_2(int n, char& Begin)
{
	int center = (Begin - 'A') * 30 + 10;
	for (int i = 0; i < n; i++) {
		for (int j = center - n + i; j < center + n - i + 1; j++) {
			cct_showstr(j, 17 - i, " ", n - i, 7, 1, -1);
			Sleep(10);
		}
	}
}
void Paint_3(int N, int n, int x, char& Begin, char& Temp, char& End, int color, bool is_static)//x��ǰ���Ӻ�
{
	int center_1 = (Begin - 'A') * 30 + 10;//��ʼλ��
	int center_2;                          //ĩ��λ�ã���һ������End��
	cct_gotoxy(0, 0);
	cct_setcolor(0, 7);

	/*if (n % 2) {
		center_2 = (End - 'A') * 30 + 10;
		cout << "��" << Begin << " ���ƶ���" << End << "�̣���" << n << "��\n";
	}
	else {
		center_2 = (Temp - 'A') * 30 + 10;
		cout << "��" << Begin << " ���ƶ���" << Temp << "�̣���" << n << "��\n";
	}*/
	center_2 = (End - 'A') * 30 + 10;
	cout << "��" << Begin << " ���ƶ���" << End << "�̣���" << N << "��\n";


	int x0 = center_1 - x;   //���������
	int x1 = center_2 - x;   //�յ������
	int y1 = 18 - top[(int)(End - 'A')];
	int length = 2 * x + 1;
	int y0 = 17 - top[Begin - 'A'];//�ƶ�ʱջ�Ѿ��ı��ˣ�����18-1=17
	if (is_static) {                       //ѡ��7ֱ�������ջָ��δ�����ֶ�����һ��
		y0 += 1;
		y1 -= 1;
	}
	for (int j = y0; j > 2; j--) {                        //�ӵ�һ����ƽ�Ƶ���

		for (int i = x0; i < x0 + length; i++) {
			if (i == 10 || i == 40 || i == 70)
				cct_showstr(i, j, " ", 14, 0, 1, -1);
			else
				cct_showstr(i, j, " ", color, 0, 1, -1);

		}
		Sleep(20);
		for (int i = x0; i < x0 + length; i++) {
			if (i == 10 || i == 40 || i == 70)
				cct_showstr(i, j, " ", 14, 0, 1, -1);
			else
				cct_showstr(i, j, " ", 0, 0, 1, -1);

		}

	}
	if (x1 - x0 > 0) {
		for (int i = x0; i < x1; i++) {                     //�ڶ��������ƶ�
			for (int j = i; j < i + length; j++) {
				cct_showstr(j, 1, " ", color, 0, 1, -1);
			}
			Sleep(10);
			for (int j = i; j < i + length; j++) {
				cct_showstr(j, 1, " ", 0, 0, 1, -1);
			}
			//Sleep(10);
		}
	}
	else {
		for (int i = x0; i > x1; i--) {                     //�ڶ��������ƶ�
			for (int j = i; j < i + length; j++) {
				cct_showstr(j, 1, " ", color, 0, 1, -1);
			}
			Sleep(10);
			for (int j = i; j < i + length; j++) {
				cct_showstr(j, 1, " ", 0, 0, 1, -1);
			}
			//Sleep(10);
		}
	}

	for (int j = 2; j < y1; j++) {                        //���ո�ƽ�Ƶ���
		for (int i = x1; i < x1 + length; i++) {
			if (i == 10 || i == 40 || i == 70)
				cct_showstr(i, j, " ", 14, 0, 1, -1);
			else
				cct_showstr(i, j, " ", color, 0, 1, -1);
			//Sleep(10);
		}
		Sleep(20);
		for (int i = x1; i < x1 + length; i++) {
			if (i == 10 || i == 40 || i == 70)
				cct_showstr(i, j, " ", 14, 0, 1, -1);
			else
				cct_showstr(i, j, " ", 0, 0, 1, -1);
			//Sleep(10);
		}
	}
	for (int i = x1; i < x1 + length; i++) {     //�յ㴦
		cct_showstr(i, y1, " ", color, 0, 1, -1);
	}

}

void Game_error_clear()
{
	cct_showstr(0, 26, "                                                       ", 0, 0, 1, -1);
	cct_gotoxy(0, 26);
	cct_setcolor(0, 7);
	cin.clear();
	cin.ignore(100, '\n');
}

void Game(int N, int x, char& Begin, char& Temp, char& End, int game_top[])
{
	i = 0;
	char End1 = End;
	while (1) {

		cct_gotoxy(0, 25);
		cct_setcolor(0, 7);
		cout << "�������ƶ�������(������ʽ��AC=A���˵������ƶ���C��Q=�˳�) ��" << endl;
		while (1) {  //������ʼԲ�����
			cct_gotoxy(0, 28);
			Begin = getchar();
			if (Begin <= 'C' && Begin >= 'A' || Begin <= 'c' && Begin >= 'a') {
				if (Begin <= 'c' && Begin >= 'a')   //��֤��Сд����
					Begin -= 32;
				if (top[(Begin - 'A')]==0) {
					cct_gotoxy(0, 26);
					cout << "��ʼ������Ϊ�գ�";
					Sleep(1000);
					Game_error_clear();
					continue;
				}
				break;
			}
			else
				continue;
		}
		while (1) {          //������ֹԲ�����
			cct_gotoxy(0, 28);
			End = getchar();
			if (Begin == End) {
				cct_gotoxy(0, 26);
				cout << "��ʼ��ֹԲ��������ͬ����������";
				Sleep(1000);
				Game_error_clear();
				continue;
			}
			if (End <= 'C' && End >= 'A' || End <= 'c' && End >= 'a') {
				if (End <= 'c' && End >= 'a')
					End -= 32;
				if (top[End - 'A'] && (game_top[Begin - 'A'] > game_top[End - 'A'])) {
					cct_gotoxy(0, 26);
					cout << "���̲��ܷ���С��֮�ϣ�";
					Sleep(1000);
					Game_error_clear();
					continue;
				}
				break;
			}
			else
				continue;

		}


		//cout << Begin << "--->" << End << endl;
		
		
		int t_pop=0;
		switch (Begin) {
		case'A':
			t_pop = pop(0);
			break;
		case'B':
			t_pop = pop(1);
			break;
		case'C':
			t_pop = pop(2);
			break;
		default:
			break;
		}
		switch (End) {
		case'A':
			push(t_pop, 0);
			break;
		case'B':
			push(t_pop, 1);
			break;
		case'C':
			push(t_pop, 2);
			break;
		default:
			break;
		}
		//game_top[End - 'A'] = game_top[Begin - 'A'];
		//game_top[Begin - 'A']=stack[Begin-'A'][top[Begin-'A']-1];
		
		x = game_top[Begin - 'A'];
		Paint_3(N, top[(int)(Begin - 'A')], x, Begin, Temp, End, x, 0);
		i++;

		game_top[Begin - 'A'] = stack[Begin - 'A'][top[Begin - 'A'] - 1];
		game_top[End - 'A'] = stack[End - 'A'][top[End - 'A'] - 1];

		if (top[End1 - 'A'] == N) {
			Game_error_clear();
			cout << "ţ��ţ����,��һ������ " << i << " �����" << endl;
			break;
		}
	}

}
void Quit()
{
	cct_gotoxy(0, 30);
	cct_setcolor(0, 7);
	Clear();
}