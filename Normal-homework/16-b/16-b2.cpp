
#include <iostream>
using namespace std;

const int ROW = 2;
const int COL = 3;

#define OPERATOR_IS_MENBER_FUNCTION		0	//运算符的重载用成员函数方式实现（如果值为0，表示用友元方式实现）

class matrix {
private:
	int value[ROW][COL];
	//除此之外不允许再添加数据成员
public:
	matrix(const int(*p)[COL]);	//构造函数，用数组初始化矩阵
	matrix();

#if OPERATOR_IS_MENBER_FUNCTION
	//给出+的成员函数实现方式的声明
	matrix operator+(const matrix&);
#else
	//给出+的友元函数实现方式的声明
	friend matrix operator+(const matrix&, const matrix&);
#endif
	friend ostream& operator<<(ostream&,matrix&);
	friend istream& operator>>(istream&,matrix&);
	/* ----根据需要添加其它成员函数的定义和友元函数的声明，数量不限---- */

};

/* ---- 给出成员函数的体外实现/友元函数的实现，其中+的实现有成员和友元两种形式，要求放在下面的预编译中 ---- */
matrix::matrix()
{
	for (int i = 0; i < COL * ROW; i++) {
		*((*value)+i) = 0;
	}
}

matrix::matrix(const int(*p)[COL])
{
	for (int i = 0; i < COL * ROW; i++) {
		*((*value) + i) = *(*p+i);
	}
}

ostream& operator<<(ostream&out, matrix&a)
{
	for (int i = 0; i < COL * ROW; i++) {
		out << *(*(a.value) + i) << " ";
		if ((i+1)% 3 == 0&&i)
			cout << endl;
	}
	return out;
}

istream& operator>>(istream&in, matrix&a)
{
	for (int i = 0; i < COL * ROW; i++) {
		in >> *(*(a.value) + i);
	}
	return in;
}

#if OPERATOR_IS_MENBER_FUNCTION
//给出+的成员函数方式的体外实现
matrix matrix:: operator+(const matrix& a)
{
	matrix ans;
	for (int i = 0; i < COL * ROW; i++) {
		*(*(ans.value) + i) = *(*(value)+i) + *(*(a.value) + i);
	}
	return ans;
}

#else
//给出+的友元函数方式的体外实现
matrix operator+(const matrix& a, const matrix& b)
{
	matrix ans;
	for (int i = 0; i < COL * ROW; i++) {
		*(*(ans.value) + i) = *(*(b.value)+i) + *(*(a.value) + i);
	}
	return ans;
}

#endif


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动
***************************************************************************/
int main()
{
	int a[ROW][COL] = { { 1,2,3 },{ 4,5,6 } };
	int b[ROW][COL] = { { 2,4,6 },{ 3,6,9 } };
	matrix m1(a), m2(b), m3; //m3的初值为全0

	/* 下面为定值测试 */
	cout << "初始矩阵m1的值" << endl;
	cout << m1 << endl;
	cout << "初始矩阵m2的值" << endl;
	cout << m2 << endl;

	m3 = m1 + m2;
	cout << "相加后矩阵m3的值" << endl;
	cout << m3 << endl;

	cout << "------------------" << endl;

	/* 下面为键盘输入测试 */
	cout << "请输入初始矩阵m1" << endl;
	cin >> m1;
	cout << "请输入初始矩阵m2" << endl;
	cin >> m2;

	cout << "初始矩阵m1的值" << endl;
	cout << m1 << endl;
	cout << "初始矩阵m2的值" << endl;
	cout << m2 << endl;
	cout << "相加后矩阵m3的值" << endl;
	cout << (m3 = m1 + m2) << endl;

	return 0;
}
