
#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

void show(bool i,const short&a)
{
	if (i) 
		cout<<"当前状态:";
	else
		cout << "初始状态:";

	cout << "0x" << setw(4) << setfill('0') << hex<<a << endl;
	for (int i = 0; i < 10; i++) {
		cout << char('A' + i) << "   ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		if (a & (int)pow(2, i))
			cout << "ON  ";
		else
			cout << "OFF ";
	}
	cout << endl<<endl;
	cout<< "请以(\"A On / J Off\"形式输入，输入\"Q on / off\"退出)"<<endl;

}
int main()
{
	short a = 0;
	show(0,a);
	//初始状态输出完毕
	char s[30];
	while (1) {
		cin.getline(s, 30);
		if ((s[0] <= 'j' && s[0] >= 'a') || (s[0] <= 'J' && s[0] >= 'A')||(s[0]=='q'||s[0]=='Q')) {
			int i,q=0;
			if (s[0] == 'q' || s[0] == 'Q') {
				q = 1;
			}
			for (i = 1; i < 30; i++) {
				if (s[i] == 'o' || s[i] == 'O')
					break;	
			}

			if ((s[i + 1] == 'n' && s[i + 2] == '\0') || (s[i + 1] == 'N'&& s[i + 2] == '\0')) {
				if (q)
					return 0;

				if (s[0] <= 'j' && s[0] >= 'a') 
					a |= (int)pow(2, int(s[0] - 'a'));
				else 
					a |= (int)pow(2, int(s[0] - 'A'));
				show(1, a);
				continue;
			}
			else if (s[i + 1] == 'f' || s[i + 1] == 'F') {
				if ((s[i + 2] == 'f' && s[i + 3] == '\0' )|| (s[i + 2] == 'F' && s[i + 3] == '\0')) {
					if (q)
						return 0;

					if (s[0] <= 'j' && s[0] >= 'a') 
						a &= (~(int)pow(2, int(s[0] - 'a')));
					else 
						a &= ~((int)pow(2, int(s[0] - 'A')));
					show(1, a);
					continue;
				}
						
			}
			cout << "请以(\"A On / J Off\"形式输入，输入\"Q on / off\"退出)"<<endl;		
		}
	}
}



