
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    char p[10];
    strcpy(p, "123456789");
    //p[10] = 'a';  //�˾�Խ��
    p[14] = 'A';    //�˾�Խ��
    p[15] = 'B';    //�˾�Խ��
    //p[-2] = 'A';
    p[10] = '\xfcc'; //�˾�Խ��
    cout << "addr:" << hex << (void*)(p) << endl;
    for (int i = -4; i < 16; i++)
        cout << hex << (void*)(p + i) << ":" << int(p[i]) << endl;
   // delete[]p;

    return 0;
}