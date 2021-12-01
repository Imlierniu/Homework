#include"90-02-b2.h"

void Game(int row, int col)
{
	/*��ܲ���*/
	CONSOLE_GRAPHICS_INFO MyCGI;
	int** Map = new int* [row];   //����a��ָ��һά�����ָ��
	for (int i = 0; i < row; i++) {
		Map[i] = new int[col];            //a�����飬ÿ�����鳤��Ϊb
		for (int j = 0; j < col; j++) {
			Map[i][j] = get_next_num();            //��ʼ����0
			cout << Map[i][j] << " ";
		}
	}
	gmw_init(&MyCGI);
	gmw_set_rowcol(&MyCGI, row, col);					//��Ϸ����row*col
	gmw_set_ext_rowcol(&MyCGI, 0, 0, 0, 16);				//���ö�������
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_HWHITE);		//�޸Ĵ�����ɫ�������޸���Ϸ��������״̬��
	gmw_set_font(&MyCGI, "Terminal", 16, 0);				//TrueType���壨�����壩��Ȳ���Ҫ������������
	gmw_set_frame_style(&MyCGI, 6, 3, true);				//ÿ��ɫ��������6��*�߶�3�У�Ҫ�ָ���
	gmw_set_frame_default_linetype(&MyCGI, 2);			//���ÿ������ΪԤ��ֵ2��ȫ��Ϊ���ߣ�
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK);		//��Ϸ��������ɫ
	gmw_set_rowno_switch(&MyCGI, true);					//��ʾ�к�
	gmw_set_colno_switch(&MyCGI, true);					//��ʾ�б�
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_FRAME, 0);		//���߿����ʱ
	gmw_set_block_border_switch(&MyCGI, true);			//����ɫ����ҪС�߿�
	gmw_set_block_default_linetype(&MyCGI, 2);
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE, false);//����Ҫ��/��״̬��
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE, true);
	//cct_setconsoleborder(93, 61, 93, 61);
	gmw_draw_frame(&MyCGI);
	
	/*ɫ�鲿��*/
	const BLOCK_DISPLAY_INFO bdi[] = {

			{0,COLOR_HWHITE, COLOR_HWHITE, NULL},				//NULL��0-8������ʾ�ڲ�����
			{1,1,COLOR_BLACK, NULL},				
			{2,2,COLOR_BLACK,NULL},
			{3,3,COLOR_BLACK,NULL},
			{4,4,COLOR_BLACK,NULL},
			{5,5,COLOR_BLACK,NULL},
			{6,6,COLOR_BLACK,NULL},
			{7,7,COLOR_BLACK,NULL},
			{8,8,COLOR_BLACK,NULL},
			{9,9,COLOR_BLACK,NULL},
			{10,10,COLOR_BLACK,NULL},
			{-6,COLOR_WHITE,0,"* "},//ը��

			{BDI_VALUE_END, -1, -1, NULL}			//��BDI_VALUE_END������һ��Ҫ��!!!
	};

	const BLOCK_DISPLAY_INFO bdi_h[] = {

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
	Show_Begin(MyCGI,bdi,Map,row,col);

	Mouse_operation(MyCGI, bdi, bdi_h, Map,row,col);
	

	Quit(row, col,MyCGI);
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
			gmw_draw_block(&MyCGI, mrow, mcol, Map[mrow][mcol], bdi_h);				 //������ڿ�������ɫ
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