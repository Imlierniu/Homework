#include"90-01-b2-mine_sweeper.h"

int main()//傀儡主函数，基本靠Init
{
	int num;
	int level;
	while (1) {
		cct_setfontsize("新宋体", 24, 0);
		num = menu();
		switch (num) {        //后续可以把switch取消
		case 1:
			level=Select_Level();
			Init(level,num);
			Quit();
			break;
		case 2:
			level = Select_Level();
			Init(level,num);
			Quit();
			break;
		case 3:
			level = Select_Level();
			Init(level, num);
			Quit();
			break;
		case 4:
			level = Select_Level();
			Init(level, num);
			Quit();
			break;
		case 5:
			level = Select_Level();
			Init2(level, num);
			//Print_Graph_Base(level);
			Quit();
			break;
		case 6:
			level = Select_Level();
			Init2(level, num);
			Quit();
			break;
		case 7:
			level = Select_Level();
			Init2(level, num);
			Quit();
			break;
		case 8:
			level = Select_Level();
			Init2(level, num);
			Quit();
			break;
		case 9:
			level = Select_Level();
			Init2(level, num);
			Quit();
			break;
		case 0:
			return 0;
			break;
		}
	}
}