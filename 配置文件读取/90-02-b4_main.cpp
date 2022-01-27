/* 车辆工程（汽车）1752856 边泽轩*/
#include"90-02-b4.h"


int main(int argc,char**argv)//合成十
{
	int row=0, col=0,mod=0;
	char filename[100];
	if (argc == 3&&!strcmp(argv[1],"-f") && !strcmp(argv[2],"config.cfg")) {
		strcpy(filename, argv[2]);
		mod = 1;
	}
	//const char* filename="config.cfg";
	while (1) {
		if(!mod)
			menu(row, col);
		Game(row, col,filename,mod);
		
	}
	/*char filename[100] = "config.cfg";
	while (1) {
		menu(row, col);
		Game(row, col, filename,1);
	}*/
}