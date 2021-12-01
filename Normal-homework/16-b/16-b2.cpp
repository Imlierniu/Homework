
#include <iostream>
using namespace std;

const int ROW = 2;
const int COL = 3;

#define OPERATOR_IS_MENBER_FUNCTION		0	//������������ó�Ա������ʽʵ�֣����ֵΪ0����ʾ����Ԫ��ʽʵ�֣�

class matrix {
private:
	int value[ROW][COL];
	//����֮�ⲻ������������ݳ�Ա
public:
	matrix(const int(*p)[COL]);	//���캯�����������ʼ������
	matrix();

#if OPERATOR_IS_MENBER_FUNCTION
	//����+�ĳ�Ա����ʵ�ַ�ʽ������
	matrix operator+(const matrix&);
#else
	//����+����Ԫ����ʵ�ַ�ʽ������
	friend matrix operator+(const matrix&, const matrix&);
#endif
	friend ostream& operator<<(ostream&,matrix&);
	friend istream& operator>>(istream&,matrix&);
	/* ----������Ҫ���������Ա�����Ķ������Ԫ��������������������---- */

};

/* ---- ������Ա����������ʵ��/��Ԫ������ʵ�֣�����+��ʵ���г�Ա����Ԫ������ʽ��Ҫ����������Ԥ������ ---- */
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
//����+�ĳ�Ա������ʽ������ʵ��
matrix matrix:: operator+(const matrix& a)
{
	matrix ans;
	for (int i = 0; i < COL * ROW; i++) {
		*(*(ans.value) + i) = *(*(value)+i) + *(*(a.value) + i);
	}
	return ans;
}

#else
//����+����Ԫ������ʽ������ʵ��
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼��
***************************************************************************/
int main()
{
	int a[ROW][COL] = { { 1,2,3 },{ 4,5,6 } };
	int b[ROW][COL] = { { 2,4,6 },{ 3,6,9 } };
	matrix m1(a), m2(b), m3; //m3�ĳ�ֵΪȫ0

	/* ����Ϊ��ֵ���� */
	cout << "��ʼ����m1��ֵ" << endl;
	cout << m1 << endl;
	cout << "��ʼ����m2��ֵ" << endl;
	cout << m2 << endl;

	m3 = m1 + m2;
	cout << "��Ӻ����m3��ֵ" << endl;
	cout << m3 << endl;

	cout << "------------------" << endl;

	/* ����Ϊ����������� */
	cout << "�������ʼ����m1" << endl;
	cin >> m1;
	cout << "�������ʼ����m2" << endl;
	cin >> m2;

	cout << "��ʼ����m1��ֵ" << endl;
	cout << m1 << endl;
	cout << "��ʼ����m2��ֵ" << endl;
	cout << m2 << endl;
	cout << "��Ӻ����m3��ֵ" << endl;
	cout << (m3 = m1 + m2) << endl;

	return 0;
}
