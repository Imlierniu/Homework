#include"90-01-b1-hanoi.h"


/* -----------------------------------------

	 ���ļ����ܣ�
	1����main����
	2����ʼ����Ļ
	3�����ò˵�������hanoi_menu.cpp�У�������ѡ��
	4������ѡ����ò˵������Ӧ��ִ�к�����hanoi_multiple_solutions.cpp�У�

	 ���ļ�Ҫ��
	1����������ȫ�ֱ��������ⲿȫ�ֺ;�̬ȫ����const��#define�������Ʒ�Χ�ڣ�
	2����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	3���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------- */

   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ�
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/

   /******��Ŀ������ĸ�ȫ�ֱ���*******/
int i;    //����
int stack[3][15];//���������ϵ�����
int top[3];
int Time;

int main()
{
	while (1) {
		int x = 0;    //��ǰ�ƶ������Ӻ�
	//int isshow; //�Ƿ���ʾ��
		char Begin, Temp, End;
		int mode;
		int n;
		int num;//10��ѡ��

		int game_top[3] = { 0 };//���������Ǽ���,��Ϸ��

		/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
		cct_setconsoleborder(120, 40, 120, 9000);
		num = menu();
		switch (num) {
		case 1:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			move(num, n, n, x, Begin, Temp, End);
			Clear();
			break;
		case 2:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			move(num, n, n, x, Begin, Temp, End);
			Clear();
			break;
		case 3:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			work(num, n, x, mode, Begin, Temp, End);
			Clear();
			break;
		case 4:
			init(n, Begin, Temp, End, game_top);
			Change_speed(mode);
			set(Begin, n);
			system("cls");
			work(num, n, x, mode, Begin, Temp, End);
			Clear();
			break;
		case 5:
			system("cls");
			Paint_1();
			Quit();
			break;
		case 6:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			Paint_1();
			Paint_2(n, Begin);
			Quit();
			break;
		case 7:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			Paint_1();
			Paint_2(n, Begin);
			if (n % 2)
				Paint_3(n, top[Begin - 'A'], 1, Begin, End, Temp, 1, 1);
			else
				Paint_3(n, top[Begin - 'A'], 1, Begin, Temp, End, 1, 1);

			Quit();
			break;
		case 8:
			init(n, Begin, Temp, End, game_top);
			Change_speed(mode);
			set(Begin, n);
			system("cls");
			Paint_1();
			Paint_2(n, Begin);
			work(num, n, x, mode, Begin, Temp, End);
			Quit();
			break;
		case 9:
			init(n, Begin, Temp, End, game_top);
			set(Begin, n);
			system("cls");
			Paint_1();
			Paint_2(n, Begin);

			x = game_top[Begin - 'A'];
			Game(n, x, Begin, Temp, End, game_top);
			Quit();
			break;
		case 0:
			return 0;
			break;
		}

	}

	return 0;
}
