#include"90-02-b1-gmw.h"


int Init(CONSOLE_GRAPHICS_INFO& MyCGI,int& a, int& b,int Di[40][5][5])//ѡ��ߴ�
{
	while (1) {
		cct_cls();
		cout << "ѡ��߶ȣ�18-26�� :";
		cin >> a;
		while (cin.fail()) {        //��ֹ��ѭ��
			cin.clear();
			cin.ignore(100, '\n');
			cct_cls();
			cout << "ѡ��߶ȣ�18-26�� :";
			cin >> a;
		}
		if (a <= 26 && a >= 18)
			break;
		else
			continue;
	}
	while (1) {
		cct_cls();
		cout << "ѡ����(4-7)*3 :";
		cin >> b;
		while (cin.fail()) {        //��ֹ��ѭ��
			cin.clear();
			cin.ignore(100, '\n');
			cct_cls();
			cout << "ѡ����(4-7)*3 :";
			cin >> b;
		}
		if (b <= 21 && b >= 12 && b % 3 == 0)
			break;
		else
			continue;
	}
	gmw_init(&MyCGI);
	gmw_set_rowcol(&MyCGI,a, b);					//��Ϸ����row*col
	gmw_set_ext_rowcol(&MyCGI, 0, 0, 0, 16);				//���ö�������
	gmw_set_color(&MyCGI, COLOR_WHITE, COLOR_HBLACK);		//�޸Ĵ�����ɫ�������޸���Ϸ��������״̬��
	gmw_set_font(&MyCGI, "������", 10, 0);				//TrueType���壨�����壩��Ȳ���Ҫ������������
	gmw_set_frame_style(&MyCGI, 6, 3, false);				//ÿ��ɫ��������6��*�߶�3�У�Ҫ�ָ���
	gmw_set_frame_default_linetype(&MyCGI, 2);			//���ÿ������ΪԤ��ֵ2��ȫ��Ϊ���ߣ�
	gmw_set_rowno_switch(&MyCGI, false);					//��ʾ�к�
	gmw_set_colno_switch(&MyCGI, false);					//��ʾ�б�
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_FRAME, 0);		//���߿����ʱ
	gmw_set_block_border_switch(&MyCGI, true);			//����ɫ����ҪС�߿�
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE, false);//����Ҫ��/��״̬��
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE, true);
	/* ��ʾ��� */
	//cct_setconsoleborder(93, 61,200,200);
	Show_Map(MyCGI, a, b);
	Init_6(MyCGI, a, b, Di);
	return 1;
}

void Quit(int a, int b)
{
	cct_gotoxy(0, a * 3 + 3);
	cout << "���س��˳�" << endl;
	char ch = _getch();
	while (ch != 13) {
		ch = _getch();
	}
}