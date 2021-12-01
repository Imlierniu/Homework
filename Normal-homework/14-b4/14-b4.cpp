
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include<cmath>
/* 如果有需要，此处可以添加头文件 */
using namespace std;
#include<bitset>
/* 允许定义常变量/宏定义，但不允许定义全局变量 */

/* 可以添加自己需要的函数 */

/***************************************************************************
  函数名称：
  功    能：打印某个玩家的牌面信息，如果是地主，后面加标记
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
	/* 只允许定义不超过三个基本类型的简单变量，不能定义数组变量、结构体、string等 */
	cout << prompt;
	for (int i = 0; i < 54; i++) {
		if (player & (long long)pow(2, i)) {
			if (i == 53)
				cout << "RJ ";
			else if (i == 52)
				cout << "BJ ";
			else {
				#ifdef linux
				if (i % 4 == 0)
					cout << 'C';
				else if (i % 4 == 1)
					cout << 'D';
				else if (i % 4 == 2)
					cout << 'H';
				else
					cout << 'S';
				#endif	
				#ifdef _WIN32
				if (i % 4 == 0)
					cout << (char)5;
				else if (i % 4 == 1)
					cout << (char)4;
				else if (i % 4 == 2)
					cout << (char)3;
				else
					cout << (char)6;
				#endif
				

				if (i /4 == 7)
					cout << "T ";
				else if (i /4== 8)
					cout << "J ";
				else if (i /4 == 9)
					cout << "Q ";
				else if (i /4 == 10)
					cout << "K ";
				else if (i /4 == 11)
					cout << "A ";
				else if (i /4 == 12)
					cout << "2 ";
				else {
					cout << char(i /4 + '3') << " ";
				}
			}
		}
	}
	cout << endl;

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：发牌（含键盘输入地主）
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int deal(unsigned long long* player)
{
	/* 只允许定义不超过十个基本类型的简单变量，不能定义数组变量、结构体、string等 */
	//54张牌总信息放在longlong中
	long long int A = ~0;
	int t1,t2,t3;
	srand(time(NULL));
	
	for(int i=0;i<17;i++){
		t1 = rand() % 54;
		while ((A & ((long long)pow(2, t1)))==0) {
			t1 = rand() % 54;
		}
		
		A &= ~((long long)pow(2, t1));
		player[0] |= ((long long)pow(2, t1));
		
		t2 = rand() % 54;
		while ((A & ((long long)pow(2, t2))) == 0) {
			t2 =rand() % 54;
		}
		
		A &= ~((long long)pow(2, t2));
		player[1] |= ((long long)pow(2, t2));
		
		
		t3 = rand() % 54;
		while ((A & ((long long)pow(2, t3))) == 0) {
			t3 = rand() % 54;
		}
		
		A &= ~((long long)pow(2, t3));
		player[2] |= ((long long)pow(2, t3));
		
		

		cout << "第" << i + 1 << "轮结束：" << endl;
		print("甲的牌：", 0, player[0]);
		print("乙的牌：", 1, player[1]);
		print("丙的牌：", 2, player[2]);
		

	}
	//17轮结束开始发地主牌
	
	int num;
	while (1) {
		cout << "请选择一个地主[0-2]:" << endl;
		cin >> num;
		while (cin.fail()) {        //防止死循环
			cin.clear();
			cin.ignore(100, '\n');
			cout << "请选择一个地主[0-2]:" << endl;
			cin >> num;
		}
		if (num <= 2 && num >= 0)
			break;
		else
			continue;
	}
	
	for (int i = 0; i < 54; i++) {
		if (A & ((long long)pow(2, i))) {
			A &= ~(long long)pow(2, i);
			player[num] |= ((long long)pow(2, i));
		}
	}

	return 0; //此处修改为选定的地主(0-2)
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数，不准修改
 ***************************************************************************/
int main()
{
	unsigned long long player[3] = { 0 }; //存放三个玩家的发牌信息
	int landlord; //返回0-2表示哪个玩家是地主

	cout << "按回车键开始发牌";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("甲的牌：", (landlord == 0), player[0]);
	print("乙的牌：", (landlord == 1), player[1]);
	print("丙的牌：", (landlord == 2), player[2]);

	return 0;
}
