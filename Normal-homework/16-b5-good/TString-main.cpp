
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

/* 用包含cpp的方法将 TString.cpp 和 TString_main.cpp 当做一个源程序文件进行编译
   注意：1、TString.cpp 需要放在与 TString_main.cpp 相同的目录下
		 2、VS中，这种方法在project中仅有 TString_main.cpp即可，不需要加入 TString.cpp
			附：为了方便打开文件并编辑，希望在 project 里面看到 TString.cpp 和 TString_main.cpp，但是 CTRL+F5 仅编译 TString_main.cpp 并执行
				a)、将 TString.cpp 和 TString_main.cpp 均加入 project 中
				b)、在 TString.cpp 上鼠标右键，菜单中选择“属性”-左侧“配置属性”选常规，右侧“从生成中排除”选择“是”
				c)、可以看到解决方案资源管理器中 TSting.cpp 有一个红色的减号
		 3、Linux下，用 c++ -Wall -o TString Tstring_main.cpp 即可，，不需要加入 TString.cpp 	 */
#include "TString.cpp"

		 /* 下面的工具函数及main不允许改动 */

#if defined(__linux) || defined(__linux__)
#include <sys/time.h>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
long get_cur_msec(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

#else
#include <Windows.h>
#include <conio.h>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
long get_cur_msec(void)
{
	return GetTickCount(); //取当前系统时间，单位毫秒
}

#endif

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_str(const char* str, const char* prompt)
{
	cout << endl << "输入" << str << prompt << endl;
	char tmp[1024];
	while (1) {
		cin >> tmp;
		if (strcmp(tmp, str) == 0)
			break;
	}
	cout << endl << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int memory_speed_test(void)
{
	const int MAX_BYTES = 100 * 1024 * 1024;

	TString s1;
	int     total, len, i;
	int     MB_count, MB_prev_count;
	char    temp[65536];
	long    t_start, t_end, t_cur, t_prev;
	char* crc_str;

	cout << "字符串累加性能测试(s1+=str方式)" << endl;
	wait_for_str("continue", "开始");

	crc_str = new(nothrow) char[MAX_BYTES + 65536]; //申请（100MB+64KB）空间
	if (crc_str == NULL) {
		cout << "无法申请" << MAX_BYTES + 65536 << "字节的校验空间，程序终止，请检查后再次运行" << endl;
		return -1;
	}
	*crc_str = 0; //置为空串

	t_prev = t_start = get_cur_msec(); //取当前系统时间，单位毫秒
	MB_prev_count = 0;
	srand((unsigned int)time(0));
	total = 0;
	while (1) {
		len = 32768 + rand() % 32768;

		for (i = 0; i < len; i++)
			temp[i] = ' ' + rand() % 95;	//数组用随机字符填充
		temp[len] = 0;
		total += len;
		s1 += temp;

		strcat(crc_str, temp);

		MB_count = s1.length() / (1024 * 1024);
		if (MB_count - MB_prev_count >= 1) {
			MB_prev_count = MB_count;

			t_cur = get_cur_msec();   //取当前系统时间

			cout << "s1已有长度：" << setw(10) << s1.length() / (1024.0 * 1024) << " MB字节，本次增加 " << setw(5) << len << " 字节，总用时"
				<< setw(10) << (t_cur - t_start) / 1000.0 << "秒，本次1MB用时" << setw(10) << (t_cur - t_prev) / 1000.0 << "秒" << endl;
			t_prev = t_cur;
		}
		else
			cout << "s1已有长度：" << setw(10) << s1.length() / (1024.0 * 1024) << " MB字节，本次增加 " << setw(5) << len << " 字节" << endl;

		if (s1.length() == 0 || s1.length() > MAX_BYTES)	//满100MB或内存耗尽则结束
			break;
	}//end of while (1)

	t_end = get_cur_msec();   //取当前系统时间

	cout << "time=" << (t_end - t_start) / 1000.0 << endl;

	if (s1.length() == 0) {
		cout << "内存分配到达 " << total / (1024 * 1024) << " MB字节后，内存耗尽（请检查程序中的错误）" << endl;

#if !(defined(__linux) || defined(__linux__))
		cout << endl << "观察任务管理器中本程序的内存占用情况..." << endl;
		wait_for_str("end", "结束");
#endif
		exit(-1);
	}
	else
		cout << "内存分配到达满100MB，测试结束" << endl;

	int check1 = (s1 != crc_str);			//TString方式比较两串是否相等（必须保证长度一样，对应位置字符一致，此处作弊，学期总分-20!!!）
	delete[]crc_str; //释放校验串

	if (check1)
		cout << "s1累加验证出错，请检查程序的实现部分" << endl;
	else {
		cout << "    本次测试耗时 " << (t_end - t_start) / 1000.0 << "秒" << endl;
#if !(defined(__linux) || defined(__linux__))
		cout << endl << "观察任务管理器中本程序的内存占用情况(不允许超过115MB)..." << endl;
		wait_for_str("end", "结束"); //Linux最后不需要再输入continue
#endif
	}

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	memory_speed_test();

#if !(defined(__linux) || defined(__linux__))
	system("pause");
#endif

	return 0;
}
