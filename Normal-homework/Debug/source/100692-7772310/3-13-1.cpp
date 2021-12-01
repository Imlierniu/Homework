//7772310 杨铁心 数理强化班
#include<iostream>
using namespace std;
int main()
{
	double i;
	int bonus;
	cout << "请输入本月利润额：";
	cin >> i;
	
	if(i <= 100000)
	{
		bonus = 0.1 * i;
		cout << "奖金为：" << bonus << endl;
	}
	else if(i <= 200000)
	{
		bonus = 10000 + 0.075 * (i - 100000);
		cout << "奖金为：" << bonus << endl;
	}
	else if(i <= 400000)
	{
		bonus = 17500 + 0.05 * (i - 200000);
		cout << "奖金为：" << bonus << endl;
	}
	else if(i <= 600000)
	{
		bonus = 27500 + 0.03 * (i - 400000);
		cout << "奖金为：" << bonus << endl;
	}
	else if(i <= 1000000)
	{
		bonus = 33500 + 0.015 * (i - 600000);
		cout << "奖金为：" << bonus << endl;
	}
	else
	{
		bonus = 39500 + 0.01 * (i - 1000000);
		cout << "奖金为：" << bonus << endl;
	}

	return 0;
}

		
	
