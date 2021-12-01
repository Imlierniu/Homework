
#include <iostream>
#include <fstream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<conio.h>
using namespace std;
int usage(const char* procname)
{
	cout << "usage :" << procname << "--modify | --read" << endl;
	return 0;
}

void read_var(int pointer, ifstream& in,int len)
{
	int a=0, b=0, c=0, d = 0;
	long long x;
	in.seekg(pointer, ios::beg);
	if (len == 1) {
		a = in.get();
		cout << a<<endl;
	}
	else if (len == 2) {
		a = in.get();
		b = in.get();
		cout<< b * 256 + a<<endl;
	}
	else if (len == 4) {
		a = in.get();
		b = in.get();
		c = in.get();
		d = in.get();
		cout<< d * 256 * 256 * 256 + c * 256 * 256 + b * 256 + a<<endl;
	}
	else if (len == 8) {
		a = in.get();
		b = in.get();
		c = in.get();
		d = in.get();
		x = long long(d * 256 * 256 * 256) + c * 256 * 256 + b * 256 + a;
		a = in.get();
		b = in.get();
		c = in.get();
		d = in.get();
		x=long long(long long(x * 256 * 256 * 256 * 256)) + long long(d * 256 * 256 * 256) + long long(c * 256 * 256) + long long(b * 256) + a;
		cout << x << endl;
	}
	
}
int read(ifstream&in,bool modi)
{
	in.open("game.dat", ios::in | ios::binary);
	if (!in.is_open()) {
		cout << "文件打开失败" << endl;
		return -1;
	}
	char name[20];
	//name
	in.seekg(0, ios::beg);
	in >> name;
	if(modi)
		cout << "        a.玩家昵称：";
	else
		cout << "          玩家昵称：";
	cout << name << endl;

	//blood
	if(modi)
		cout << "          b.生命值：";
	else
		cout << "            生命值：";
	read_var(16, in, 2);
	

	//power
	if(modi)
		cout << "          c.力量值：";
	else
		cout << "            力量值：";
	read_var(18, in, 2);

	//
	if(modi)
		cout << "          d.体质值：";
	else
		cout << "            体质值：";
	read_var(20, in, 2);

	if(modi)
		cout << "          e.灵巧值：";
	else
		cout << "            灵巧值：";
	read_var(22, in, 2);
	if(modi)
		cout << "          f.金钱值：";
	else
		cout << "            金钱值：";
	read_var(24, in, 4);

	if(modi)
		cout << "          g.名声值：";
	else
		cout << "            名声值：";
	read_var(28, in, 4);

	if(modi)
		cout << "          h.魅力值：";
	else
		cout << "            魅力值：";
	read_var(32, in, 4);

	if(modi)
		cout << "i.游戏累计时间(us)值：";
	else
		cout << "游戏累计时间(us)值：";
	read_var(36, in, 8);
	
	if(modi)
		cout << "      j.移动速度值：";
	else
		cout << "        移动速度值：";
	read_var(44, in, 1);
	
	if(modi)
		cout << "      k.攻击速度值：";
	else
		cout << "        攻击速度值：";

	read_var(45, in, 1);
	if(modi)
		cout << "      l.攻击范围值：";
	else
		cout << "        攻击范围值：";
	read_var(46, in, 1);

	if(modi)
		cout << "      m.攻击力值：";
	else
		cout << "          攻击力值：";
	read_var(48, in, 2);
	
	if(modi)
		cout << "        n.防御力值：";
	else
		cout << "          防御力值：";
	read_var(50, in, 2);

	if(modi)
		cout << "        o.敏捷度值：";
	else
		cout << "          敏捷度值：";
	read_var(52, in, 1);

	if(modi)
		cout << "          p.智力值：";
	else
		cout << "            智力值：";
	read_var(53, in, 1);

	if(modi)
		cout << "          q.经验值：";
	else
		cout << "            经验值：";
	read_var(54, in, 1);
	
	if(modi)
		cout << "          r.等级值：";
	else
		cout << "            等级值：";
	read_var(55, in, 1);

	if(modi)
		cout << "          s.魔法值：";
	else
		cout << "            魔法值：";
	read_var(56, in, 2);
	
	if(modi)
		cout << "      t.消耗魔法值：";
	else
		cout << "        消耗魔法值：";
	read_var(58, in, 1);
	
	if(modi)
		cout << "    u.魔法伤害力值：";
	else
	cout << "      魔法伤害力值：";
	read_var(59, in, 1);

	if(modi)
		cout << "        v.命中率值：";
	else
		cout << "          命中率值：";
	read_var(60, in, 1);

	if(modi)
		cout << "    w.魔法防御力值：";
	else
		cout << "      魔法防御力值：";
	read_var(61, in, 1);
	
	if(modi)
		cout << "        x.暴击率值：";
	else
		cout << "          暴击率值：";
	read_var(62, in, 1);
	
	if(modi)
		cout << "          y.耐力值：";	
	else
		cout << "            耐力值：";
	read_var(63, in, 1);
	
}

int modify(ifstream& in, ofstream& out)
{
	cout << "-----------------------------------"<<endl;
	cout << "      游戏存档文件修改工具" << endl;
	cout << "-----------------------------------"<<endl;
	read(in, 1);
	cout << "-----------------------------------" << endl;
	cout << "0.放弃修改" << endl;
	cout << "1.存盘退出" << endl;
	cout << "-----------------------------------" << endl;
	
	int Begin[26] = {0,16,18,20,22,24,28,32,26,44,45,46,47,48,50,52,53,54,55,56,58,59,60,61,62,63};
	int Len[26] = {16,2,2,2,2,4,4,4,8,1,1,1,1,2,2,1,1,1,1,2,1,1,1,1,1,1};
	char c;
	while (1) {
		c = _getch();
		while ((c > 'x' || c < 'a') && (c != '0' && c != '1')) {        //防止死循环
			c = _getch();
		}
		if (c == '0') {
			return 0;
		}
		else if (c == '1') {
			return 1;
		}
		else {
			
		}
	}
	

	return 1;
}
/*int main(int argc, char** argv)
{
	ifstream in;
	ofstream out;
	if (argc != 2) {
		usage(argv[0]);
		return 0;
	}
	if (argc == 2 && strcmp(argv[1], "--read") == 0) {
		read(in,0);
	}
	if (argc == 2 && strcmp(argv[1], "--modify") == 0) {
		modify(in,out);
	}
}*/