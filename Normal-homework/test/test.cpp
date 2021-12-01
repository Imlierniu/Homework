#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
using namespace std;

template<typename T>
struct add{
	T operator() (const T&a,const T&b)
	{
		return a + b;
	}
};
int main()
{
	struct add<int> add_func;
	cout << add_func(1, 2) << endl;
	string ps[3] = { " " };
	for (auto i: ps) {
		cout << i << "?" << endl;
	}
}