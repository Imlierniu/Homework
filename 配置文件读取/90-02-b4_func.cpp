/* �������̣�������1752856 ������*/

#include"90-02-b4.h"
#include<fstream>
typedef struct block {
	int   value;	
	int   bgcolor;	
	int   fgcolor;	
	const char content[5]; 
}BLOCK;            //���ڴ�Ŵ��ļ������Ķ���Ȼ���ʼ��BLOCK_DISPLAY_INFO�ṹ��

void Read(CONSOLE_GRAPHICS_INFO& temp, int& target, BLOCK* bdi_temp, BLOCK* bdi_h_temp, const char* filename)
{
	CFT cfg;
	cfg.open(filename, OPEN_OPT_RDONLY);
	if (cfg.is_open() == false) {
		cout << "�޷��������ļ�(" << filename << ")." << endl;
		return;
	}
	string s;
	cfg.item_get_value("��������", "��ʼ�к�", temp.extern_up_lines);
	//cout <<"??????????????????\n" << temp.extern_up_lines << endl;
	cfg.item_get_value("��������", "��ʼ�к�", temp.extern_left_cols);
	cfg.item_get_value("��������", "�·�����", temp.extern_down_lines);
	cfg.item_get_value("��������", "�Ҳ����", temp.extern_right_cols);
	cfg.item_get_value("��������", "����", temp.row_num);
	cfg.item_get_value("��������", "����", temp.col_num);
	cfg.item_get_value("��������", "����ɫ", temp.area_bgcolor);
	cfg.item_get_value("��������", "ǰ��ɫ", temp.area_fgcolor);
	cfg.item_get_value("��������", "����", temp.CFT.font_type);
	cfg.item_get_value("��������", "�ֺ�", temp.CFT.font_size_high);
	cfg.item_get_value("��������", "���߿���ʱ", temp.delay_of_draw_block);
	cfg.item_get_value("��������", "ɫ���ƶ���ʱ", temp.delay_of_block_moved);

/***************************************************************************************************/
	cfg.item_get_value("�߿�����", "�߿���-���Ͻ�",temp.CFI.top_left);
	//cout << temp.CFI.top_left << endl;
	cfg.item_get_value("�߿�����", "�߿���-���½�",temp.CFI.lower_left);
	cfg.item_get_value("�߿�����", "�߿���-���Ͻ�", temp.CFI.top_right);
	cfg.item_get_value("�߿�����", "�߿���-���½�", temp.CFI.lower_right);
	cfg.item_get_value("�߿�����", "�߿���-����", temp.CFI.h_normal);
	cfg.item_get_value("�߿�����", "�߿���-����", temp.CFI.v_normal);
	cfg.item_get_value("�߿�����", "�߿���-�Ϸָ���",temp.CFI.h_top_separator);
	cfg.item_get_value("�߿�����", "�߿���-�·ָ���",temp.CFI.h_lower_separator);
	cfg.item_get_value("�߿�����", "�߿���-��ָ���",temp.CFI.v_left_separator);
	cfg.item_get_value("�߿�����", "�߿���-�ҷָ���",temp.CFI.v_right_separator);

	cfg.item_get_value("�߿�����", "��Ҫ�ָ���", s);
	if (s == "Y" || s == "y")
		temp.CFI.separator = 1;
	else if (s == "N" || s == "n")
		temp.CFI.separator = 0;

	
	cfg.item_get_value("�߿�����", "�к��б���ʾ",s) ;
	if (s == "Y" || s == "y") {
		temp.draw_frame_with_row_no = 1;
		temp.draw_frame_with_col_no = 1;
	}
	else if (s == "N" || s == "n") {
		temp.draw_frame_with_row_no = 0;
		temp.draw_frame_with_col_no = 0;
	}

	cfg.item_get_value("�߿�����", "����ɫ", temp.CFI.bgcolor);
	cfg.item_get_value("�߿�����", "ǰ��ɫ", temp.CFI.fgcolor);
	


	/****************************************************************************************************/
	cfg.item_get_value("ɫ������", "���", temp.CFI.block_width);
	cfg.item_get_value("ɫ������", "�߶�", temp.CFI.block_high);

	
	cfg.item_get_value("ɫ������", "ɫ��1-ǰ��ɫ", bdi_temp[1].fgcolor);
	//cout << bdi_temp[1].fgcolor << endl;
	cfg.item_get_value("ɫ������", "ɫ��1-����ɫ", bdi_temp[1].bgcolor);
	//cout << bdi_temp[1].bgcolor << endl;
	cfg.item_get_value("ɫ������", "ɫ��2-ǰ��ɫ", bdi_temp[2].fgcolor);
	cfg.item_get_value("ɫ������", "ɫ��2-����ɫ", bdi_temp[2].bgcolor);
	cfg.item_get_value("ɫ������", "ɫ��3-ǰ��ɫ", bdi_temp[3].fgcolor);
	cfg.item_get_value("ɫ������", "ɫ��3-����ɫ", bdi_temp[3].bgcolor);
	cfg.item_get_value("ɫ������", "ɫ��4-ǰ��ɫ", bdi_temp[4].fgcolor);
	cfg.item_get_value("ɫ������", "ɫ��4-����ɫ", bdi_temp[4].bgcolor);
	cfg.item_get_value("ɫ������", "ɫ��5-ǰ��ɫ", bdi_temp[5].fgcolor);
	cfg.item_get_value("ɫ������", "ɫ��5-����ɫ", bdi_temp[5].bgcolor);
	cfg.item_get_value("ɫ������", "ɫ��6-ǰ��ɫ", bdi_temp[6].fgcolor);
	cfg.item_get_value("ɫ������", "ɫ��6-����ɫ", bdi_temp[6].bgcolor);
	cfg.item_get_value("ɫ������", "ɫ��7-ǰ��ɫ", bdi_temp[7].fgcolor);
	cfg.item_get_value("ɫ������", "ɫ��7-����ɫ", bdi_temp[7].bgcolor);
	cfg.item_get_value("ɫ������", "ɫ��8-ǰ��ɫ", bdi_temp[8].fgcolor);
	cfg.item_get_value("ɫ������", "ɫ��8-����ɫ", bdi_temp[8].bgcolor);
	cfg.item_get_value("ɫ������", "ɫ��9-ǰ��ɫ", bdi_temp[9].fgcolor);
	cfg.item_get_value("ɫ������", "ɫ��9-����ɫ", bdi_temp[9].bgcolor);
	cfg.item_get_value("ɫ������", "ɫ��10-ǰ��ɫ", bdi_temp[10].fgcolor);
	cfg.item_get_value("ɫ������", "ɫ��10-����ɫ", bdi_temp[10].bgcolor);
	//cfg.item_get_value("ɫ������", "ɫ��1-ǰ��ɫ", bdi_temp[11].fgcolor);
//	cfg.item_get_value("ɫ������", "ɫ��1-����ɫ", bdi_temp[11].bgcolor);
	

	cfg.close(); //�ر��ļ���ģ�Ȿ���������

}
/***************************************************************************
  �������ƣ�
  ��    �ܣ��ȳ�ʼ��ȱʡֵ����ȡ�ļ��ж�������������ȱʡֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void ReadCfgfile(CONSOLE_GRAPHICS_INFO& temp,int&target,BLOCK*bdi_temp,BLOCK*bdi_h_temp,const char*filename,int mode)
{
//��ʼ����ѡ���Ƿ���ļ�
	
//��������
	temp.extern_up_lines=0;
	temp.extern_down_lines=0;
	temp.extern_left_cols=0;
	temp.extern_right_cols=0;
	temp.row_num=10;
	temp.col_num=10;
	temp.area_bgcolor=0;
	temp.area_fgcolor=7;
	temp.delay_of_draw_frame=0;		//������ǵ���ʱ
	temp.delay_of_block_moved=10; //ɫ���ƶ���ʱ
	strcpy(temp.CFT.font_type,"��������");
	temp.CFT.font_size_width=8;
	temp.CFT.font_size_high=8;

//�߿�����
	strcpy(temp.CFI.top_left,"�X");			// "�X"
	strcpy(temp.CFI.lower_left,"�^");		// "�^"
	strcpy(temp.CFI.top_right,"�[");			// "�["
	strcpy(temp.CFI.lower_right,"�a");		// "�a"
	strcpy(temp.CFI.h_normal, "�T");			// "�T"	//Horizontal
	strcpy(temp.CFI.v_normal, "�U");			// "�U"	//Vertical
	strcpy(temp.CFI.h_top_separator, "�j");	// "�h"
	strcpy(temp.CFI.h_lower_separator, "�m");	// "�k"
	strcpy(temp.CFI.v_left_separator, "�d");
	strcpy(temp.CFI.v_right_separator, "�g");	// "�f"
	strcpy(temp.CFI.mid_separator, "�p");		// "��"

	temp.CFI.bgcolor=15;
	temp.CFI.fgcolor=0;

	temp.CFI.separator = 1;//!!!!!!!!!!!!!!!YYYYYYYYYYYYYYYYYYYYYYYY

	//�Ƿ���Ҫ���кţ�Ĭ��1
	temp.draw_frame_with_row_no=1;
	temp.draw_frame_with_col_no=1;


//ɫ������
	strcpy(temp.CBI.top_left,"�X");			// "�X"
	strcpy(temp.CBI.lower_left, "�^");		// "�^"
	strcpy(temp.CBI.top_right, "�[");			// "�["
	strcpy(temp.CBI.lower_right, "�a");		// "�a"
	strcpy(temp.CBI.h_normal, "�T");			// "�T"	//Horizontal
	strcpy(temp.CBI.v_normal, "�U");			// "�U"	//Vertical

	/* ÿ��ɫ��Ŀ�Ⱥ͸߶�(ע�⣺��ȱ�����2�ı���) */
	temp.CFI.block_width = 6;
	temp.CFI.block_high = 3;

	bool block_border;
	
	
//״̬������
	temp.SLI.is_top_status_line=1;//!!!!!!!!!!!!!!!!!!YYYYYYYYYYYYYYYYY
	temp.SLI.is_lower_status_line=1;//YYYYYYYYYYYYYYYYYYYYYYYYYYY
	if(mode)
		Read(temp, target, bdi_temp, bdi_h_temp, filename);
	
}

void cfgfilebaseset(CONSOLE_GRAPHICS_INFO&MyCGI, CONSOLE_GRAPHICS_INFO& temp,int row,int col,BLOCK*bdi_temp,BLOCK*bdi_h_temp,const char*filename,int mode)
{
	
	gmw_init(&MyCGI);

	//CONSOLE_GRAPHICS_INFO temp;//���ļ�����һ���Զ�������ṹ�������
	int target = 5;

	ReadCfgfile(temp,target,bdi_temp,bdi_h_temp,filename,mode);//��ʼ������ѡ���Ƿ���ļ�
	if (!mode) {
		temp.col_num = col;
		temp.row_num = row;
	}

//��ֵ�������ú���
	gmw_set_rowcol(&MyCGI, temp.row_num, temp.col_num);
	//gmw_set_rowcol(&MyCGI, row, col);					//��Ϸ����row*col
	gmw_set_ext_rowcol(&MyCGI, temp.extern_up_lines, temp.extern_down_lines, 
		temp.extern_left_cols, temp.extern_right_cols);				//���ö�������
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_HWHITE);		//�޸Ĵ�����ɫ�������޸���Ϸ��������״̬��
	gmw_set_font(&MyCGI, temp.CFT.font_type, temp.CFT.font_size_high, temp.CFT.font_size_width);				//TrueType���壨�����壩��Ȳ���Ҫ������������
	gmw_set_frame_style(&MyCGI, temp.CFI.block_width, temp.CFI.block_high, temp.CFI.separator);				//ÿ��ɫ��������6��*�߶�3�У�Ҫ�ָ���
	//gmw_set_frame_default_linetype(&MyCGI, 2);			//���ÿ������ΪԤ��ֵ2��ȫ��Ϊ���ߣ�
	gmw_set_frame_linetype(&MyCGI,temp.CFI.top_left,temp.CFI.lower_left,temp.CFI.top_right,
		temp.CFI.lower_right, temp.CFI.h_normal,temp.CFI.v_normal, temp.CFI.h_top_separator,
		temp.CFI.h_lower_separator, temp.CFI.v_left_separator, temp.CFI.v_right_separator,
		temp.CFI.mid_separator);
	gmw_set_frame_color(&MyCGI, temp.area_bgcolor, temp.area_fgcolor);		//��Ϸ��������ɫ
	gmw_set_rowno_switch(&MyCGI, temp.draw_frame_with_row_no);					//��ʾ�к�
	gmw_set_colno_switch(&MyCGI, temp.draw_frame_with_col_no);					//��ʾ�б�
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_FRAME, temp.delay_of_draw_block);		//���߿����ʱ
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_BLOCK, temp.delay_of_draw_block);
	//gmw_set_delay(&MyCGI, DELAY_OF_BLOCK_MOVED, temp.delay_of_block_moved);//����ʱ��
	gmw_set_delay(&MyCGI, DELAY_OF_BLOCK_MOVED, 0);//����ʱ��
	gmw_set_block_border_switch(&MyCGI, true);			//����ɫ����ҪС�߿�
	//gmw_set_block_default_linetype(&MyCGI, 2);
	gmw_set_block_linetype(&MyCGI, temp.CBI.top_left, temp.CBI.lower_left, temp.CBI.top_right, temp.CBI.lower_right,
		temp.CBI.h_normal, temp.CBI.v_normal);
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE,false);//����Ҫ��/��״̬��
	//gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE, true);
	//cct_setconsoleborder(93, 61, 93, 61);


	gmw_draw_frame(&MyCGI);
}

void Game(int row, int col,const char*filename,int mode)
{
	/*��ܲ���*/
	CONSOLE_GRAPHICS_INFO MyCGI;


	CONSOLE_GRAPHICS_INFO temp;
	BLOCK* bdi_t=0, *bdi_h_t=0;//temp��bdi_t��bdi_h_t�����ڴ�����ļ����Ķ�����Ȼ�󴫸��������߸�ֵ��bdi��bdi_h
	
	bdi_t = new BLOCK[13]{

			{0,COLOR_HWHITE, COLOR_HWHITE, NULL},				//NULL��0-8������ʾ�ڲ�����
			{1,1,COLOR_BLACK, NULL},
			{2,2,COLOR_BLACK,NULL},
			{3,3,COLOR_BLACK,NULL},
			{4,4,COLOR_BLACK,NULL},
			{5,5,COLOR_BLACK,NULL},
			{6,9,COLOR_BLACK,NULL},
			{7,10,COLOR_BLACK,NULL},
			{8,11,COLOR_BLACK,NULL},
			{9,12,COLOR_BLACK,NULL},
			{10,13,COLOR_BLACK,NULL},
			{-6,COLOR_WHITE,0,"* "},//ը��

			{BDI_VALUE_END, -1, -1, NULL}			//��BDI_VALUE_END������һ��Ҫ��!!!
	};

	bdi_h_t = new BLOCK[13]{

			{0,  COLOR_HWHITE, COLOR_HWHITE, NULL},				//NULL��0-8������ʾ�ڲ�����
			{1,1,COLOR_HWHITE, NULL},
			{2,2,COLOR_HWHITE,NULL},
			{3,3,COLOR_HWHITE,NULL},
			{4,4,COLOR_HWHITE,NULL},
			{5,5,COLOR_HWHITE,NULL},
			{6,6,COLOR_HWHITE,NULL},
			{7,7,COLOR_HWHITE,NULL},
			{8,8,COLOR_HWHITE,NULL},
			{9,9,COLOR_HWHITE,NULL},
			{10,10,COLOR_HWHITE,NULL},
			{-6,COLOR_WHITE,0,"* "},//ը��

			{BDI_VALUE_END, -1, -1, NULL}			//��BDI_VALUE_END������һ��Ҫ��!!!
	};

	//�����ֵ���ٶ��ļ����ٰ����ݴ������ú���
	cfgfilebaseset(MyCGI,temp, row,col,bdi_t,bdi_h_t,filename,mode);
	
	const BLOCK_DISPLAY_INFO bdi[13] = {

			{bdi_t[0].value,bdi_t[0].bgcolor,bdi_t[0].fgcolor,NULL},
			{bdi_t[1].value,bdi_t[1].bgcolor,bdi_t[1].fgcolor,NULL},
			{bdi_t[2].value,bdi_t[2].bgcolor,bdi_t[2].fgcolor,NULL},
			{bdi_t[3].value,bdi_t[3].bgcolor,bdi_t[3].fgcolor,NULL},
			{bdi_t[4].value,bdi_t[4].bgcolor,bdi_t[4].fgcolor,NULL},
			{bdi_t[5].value,bdi_t[5].bgcolor,bdi_t[5].fgcolor,NULL},
			{bdi_t[6].value,bdi_t[6].bgcolor,bdi_t[6].fgcolor,NULL},
			{bdi_t[7].value,bdi_t[7].bgcolor,bdi_t[7].fgcolor,NULL},
			{bdi_t[8].value,bdi_t[8].bgcolor,bdi_t[8].fgcolor,NULL},
			{bdi_t[9].value,bdi_t[9].bgcolor,bdi_t[9].fgcolor,NULL},
			{bdi_t[10].value,bdi_t[10].bgcolor,bdi_t[10].fgcolor,NULL},
			{bdi_t[11].value,bdi_t[11].bgcolor,bdi_t[11].fgcolor,NULL},
			{bdi_t[12].value,bdi_t[12].bgcolor,bdi_t[12].fgcolor,NULL}
	};

	const BLOCK_DISPLAY_INFO bdi_h[13] = {
			{bdi_h_t[0].value,bdi_h_t[0].bgcolor,bdi_h_t[0].fgcolor,NULL},
			{bdi_h_t[1].value,bdi_h_t[1].bgcolor,bdi_h_t[1].fgcolor,NULL},
			{bdi_h_t[2].value,bdi_h_t[2].bgcolor,bdi_h_t[2].fgcolor,NULL},
			{bdi_h_t[3].value,bdi_h_t[3].bgcolor,bdi_h_t[3].fgcolor,NULL},
			{bdi_h_t[4].value,bdi_h_t[4].bgcolor,bdi_h_t[4].fgcolor,NULL},
			{bdi_h_t[5].value,bdi_h_t[5].bgcolor,bdi_h_t[5].fgcolor,NULL},
			{bdi_h_t[6].value,bdi_h_t[6].bgcolor,bdi_h_t[6].fgcolor,NULL},
			{bdi_h_t[7].value,bdi_h_t[7].bgcolor,bdi_h_t[7].fgcolor,NULL},
			{bdi_h_t[8].value,bdi_h_t[8].bgcolor,bdi_h_t[8].fgcolor,NULL},
			{bdi_h_t[9].value,bdi_h_t[9].bgcolor,bdi_h_t[9].fgcolor,NULL},
			{bdi_h_t[10].value,bdi_h_t[10].bgcolor,bdi_h_t[10].fgcolor,NULL},
			{bdi_h_t[11].value,bdi_h_t[11].bgcolor,bdi_h_t[11].fgcolor,NULL},
			{bdi_h_t[12].value,bdi_h_t[12].bgcolor,bdi_h_t[12].fgcolor,NULL}
	};

	//cout << temp.row_num << "" << temp.col_num << endl;
	
	int** Map = new int* [temp.row_num];   //����a��ָ��һά�����ָ��
	for (int i = 0; i < temp.row_num; i++) {
		Map[i] = new int[temp.col_num];            //a�����飬ÿ�����鳤��Ϊb
		for (int j = 0; j < temp.col_num; j++) {
			Map[i][j] = get_next_num();            //��ʼ����0
			//cout << Map[i][j] << " ";
		}
	}
	if(!mode)//�˵�ģʽ
		Show_Begin(MyCGI, bdi, Map, row,col);
	else     //�����ļ�ģʽ
		Show_Begin(MyCGI,bdi,Map,temp.row_num,temp.col_num);

	if(!mode)
		Mouse_operation(MyCGI, bdi, bdi_h, Map, row,col);
	else
		Mouse_operation(MyCGI, bdi, bdi_h, Map, temp.row_num, temp.col_num);

	

	Quit(temp.row_num, temp.col_num,MyCGI);
}

void Mouse_operation(CONSOLE_GRAPHICS_INFO& MyCGI, const BLOCK_DISPLAY_INFO bdi[],const BLOCK_DISPLAY_INFO bdi_h[],int **Map,int a,int b)
{
	int maction, old_mrow, old_mcol, mrow = -1, mcol = -1;
	int keycode1, keycode2;
	int ret;
	int N=-1;
	int A[10][10] = { 0 };
	int n = 0;//���������ϲ�������
	int max=0;

	while (1) {
		old_mrow = mrow;
		old_mcol = mcol;
		ret = gmw_read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) {//��������ѡһ�鿪ʼ��Ϸ���ж��Ƿ��ܴ�
			if (Map[mrow][mcol] != 0 && A[mrow][mcol] == 0) {//��������
				N = Map[mrow][mcol];
				Lighten_Block(MyCGI, bdi, bdi_h, mrow, mcol, Map, a, b, N, A,0,n,max);
			}
			else if (Map[mrow][mcol] != 0 && A[mrow][mcol] == 1) {//���������ʾ�ĵط�������ʹ�
				N = Map[mrow][mcol];
				Lighten_Block(MyCGI, bdi, bdi_h, mrow, mcol, Map, a, b, N, A, 1,n,max);
				n = 0;
			}
		}
		else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED) {
			if (old_mrow != mrow || old_mcol != mcol) {//����ƶ�����������
				for (int i = 0; i < a; i++) {
					for (int j = 0; j < b; j++) {
						if (A[i][j]==1) {
							A[i][j] = 0;
							gmw_draw_block(&MyCGI, i, j, Map[i][j], bdi);
						}
					}
				}
			}
			
			if (old_mrow >= 0 && old_mcol >= 0)//A����Ԫ��Ϊ0����ͨʾ״̬
				gmw_draw_block(&MyCGI, old_mrow, old_mcol, Map[old_mrow][old_mcol], bdi);		//ԭɫ����ʾ������ɫ
			gmw_draw_block(&MyCGI, mrow, mcol, Map[mrow][mcol], bdi_h);				
		}

	}
}

void Lighten_Block(CONSOLE_GRAPHICS_INFO& MyCGI, const BLOCK_DISPLAY_INFO bdi[], const BLOCK_DISPLAY_INFO bdi_h[],int mrow,int mcol,int **Map,int a,int b,int N,int A[10][10],int tag,int& n,int& max)
{
	if (tag == 0) {
		A[mrow][mcol] = 1;
		Dfs(MyCGI, bdi, bdi_h, Map, mrow, mcol, a, b, N, A,0,n);//�����������
			//������ʾ
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				if (A[i][j] == 1) {
					gmw_draw_block(&MyCGI, i, j, Map[i][j], bdi_h);
					++n;
				}
			}
		}
	}
	else if (tag == 1) {
		if(n>=2){
			Map[mrow][mcol] = N + 1;//����������ϳ�
			if (N + 1 > 10)
				Map[mrow][mcol] = 10;//����������ʾ10
			
			if (N + 1 > max&&N<10)
				max = N + 1;//���µ�ǰ���ֵ
			Dfs(MyCGI, bdi, bdi_h, Map, mrow, mcol, a, b, N, A,1,n);//�����������

			//gmw_draw_block(&MyCGI, mrow, mcol, Map[mrow][mcol], bdi);//������ϳ���֮����˸
			for (int s = 0; s < 40; s++) {
				if (s % 2 == 0)
					gmw_draw_block(&MyCGI, mrow, mcol, Map[mrow][mcol], bdi_h);
				else
					gmw_draw_block(&MyCGI, mrow, mcol, Map[mrow][mcol], bdi);
				Sleep(1);
			}
			//��ʼ׹��
			for (int j = 0; j < b; j++) {
				Sleep(20);
				for (int i = a-1; i >=0 ; i--) {
					int L = 0;
					if (Map[i][j] == 0) {
						int i1 = i;
						while (Map[i1][j] == 0) {
							if (i1 == 0)
								break;
							i1--;
						}  //�ҵ�0��һ��
						for (int k=0 ; (i1-k)>=0 ; k++) {//ÿ��׹��һ��
							if (Map[i1][j] != 0) {    //==0˵����һ�ε�������0������׹��
								gmw_set_delay(&MyCGI, DELAY_OF_BLOCK_MOVED, 0.9);
								gmw_move_block(&MyCGI, i1 - k, j, Map[i1 - k][j], 0, bdi, UP_TO_DOWN, i - i1);
								
								Map[i - k][j] = Map[i1 - k][j];
								Map[i1 - k][j] = 0;
							}
							
						}
					}
				}
				
			}
			//׹������������µ�
			for (int i = 0; i < a; i++) {
				for (int j = 0; j < b; j++) {
					if (Map[i][j] == 0) {
						Map[i][j] = get_next_num(max);//�ϳ�4֮����ܲ���4������ֻ����1-3������
						gmw_draw_block(&MyCGI, i, j, Map[i][j], bdi);
					}
				}
			}
		}
	}
	
}



void Dfs(CONSOLE_GRAPHICS_INFO& MyCGI, const BLOCK_DISPLAY_INFO bdi[], const BLOCK_DISPLAY_INFO bdi_h[],int **Map, int mrow, int mcol, int a, int b,int N,int A[10][10],int tag,int&n)
{
	int Row_4[4] = { 1,-1,0,0 };//��������4���ط�
	int Col_4[4] = { 0,0,1,-1 };
	
		for (int i = 0; i < 4; i++) {
			int NextRow = mrow + Row_4[i];
			int NextCol = mcol + Col_4[i];
			if (NextRow >= 0 && NextRow < a && NextCol >= 0 && NextCol < b) {
				if (Map[NextRow][NextCol]==N&&A[NextRow][NextCol]!=1&&tag==0) {
					A[NextRow][NextCol] = 1;
					Dfs(MyCGI, bdi, bdi_h, Map, NextRow, NextCol, a, b, N, A,0,n);
				}
				else if (Map[NextRow][NextCol] == N && A[NextRow][NextCol] == 1 && tag == 1) {
					Map[NextRow][NextCol] = 0;//��0
					A[NextRow][NextCol] = 0;
					Dfs(MyCGI, bdi, bdi_h, Map, NextRow, NextCol, a, b, N, A, 1,n);
					gmw_draw_block(&MyCGI, NextRow, NextCol,Map[NextRow][NextCol],bdi_h);
					
				}
				
			}
		}

}

void Show_Begin(CONSOLE_GRAPHICS_INFO& MyCGI, const BLOCK_DISPLAY_INFO bdi[],int** Map,int row,int col)
{
	for (int i = 0; i < row; i++) {
		for(int j=0;j<col;j++){
			gmw_draw_block(&MyCGI, i, j, Map[i][j], bdi);
		}
	}
}

int get_next_num(int max,const bool new_seed, const unsigned int seed)//max�����������ֵ
{
	if (new_seed)
		srand(seed);

	return rand() % max+1;
}