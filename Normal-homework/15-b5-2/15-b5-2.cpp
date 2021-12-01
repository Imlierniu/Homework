
#include <iostream>
#include <fstream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
//#include<conio.h>
#include<cmath>
//������Ҫ�ɼ�������ͷ�ļ�
using namespace std;

//�˴�Ϊʾ���������޸Ľṹ�����ƣ������޸Ľṹ���еĳ�Ա���ݣ�Ҫ��sizeof������64
struct Game_Data {
    unsigned char d[64];
    //int d[64] = { 1 };
}data1;
char name[16];
struct Para
{
    const char* opt;
    int begin;
    int end;
    int low;
    long long high;
};

struct Para list[] =
{
    { "����ǳƣ�",1,16,0,0 },
    { "����ֵ��",17,18,0,10000 },
    { "����ֵ��",19,20,0,10000 },
    { "����ֵ��",21,22,0,8192 },
    { "����ֵ��",23,24,0,1024 },
    { "��Ǯֵ��",25,28,0,100000000 },
    { "����ֵ��",29,32,0,1000000 },
    { "����ֵ��",33,36,0,1000000 },
    {"��Ϸ�ۻ�ʱ��(us)ֵ��",37,44,0,10000000000000000},
    { "�ƶ��ٶ�ֵ��",45,45,0, 100 },
    { "�����ٶ�ֵ��",46,46,0 ,100 },
    { "������Χֵ��",47,47,0,100 },
    //48����
    { "������ֵ��",49,50,0,2000 },
    { "������ֵ��",51,52,0 ,2000 },
    { "���ݶ�ֵ��",53,53,0,100 },
    { "����ֵ��",54,54,0,100 },
    { "����ֵ��",55,55,0,100 },
    { "�ȼ�ֵ��",56,56,0,100 },
    { "ħ��ֵ��",57,58,0,10000 },
    { "����ħ��ֵ��",59,59,0, 100 },
    { "ħ���˺���ֵ��",60,60,0 ,100 },
    { "������ֵ��",61,61,0, 100 },
    { "ħ��������ֵ��",62,62,0 ,100 },
    { "������ֵ��",63,63,0,100 },
    { "����ֵ��",64,64,0,100 },
};

/* �˴�����������������������
   1�����������ĺ����������������µ� fstream / ifstream / ofstream �����󣬲����д�/��/д/�رյȲ���
   2�����������ĺ���������������C��ʽ�����ļ�����
   3��������������ͬ��������main����
*/
void Print(int modi);
void Show_var(int i)
{
    long long temp = 0;
    if (i == 0) {
        for (int j = 0; data1.d[j] != '\0'; j++)
            cout << data1.d[j];//����ֱ�����
        //cout << endl;
    }
    else {
        for (int j = list[i].begin, j0 = j; j <= list[i].end; j++)
            temp += (long long)pow(256, (j - j0)) * data1.d[j - 1];
        cout << temp;
    }
}

void Set_Data(int option, long long in, int isname)  //�޸Ľṹ���е�����
{
    if (isname) {
        int i;
        for (i = 0; i < 14; i++)
            data1.d[i] = name[i];
        data1.d[i] = '\0';
        return;
    }
    unsigned char t = 0;
    int b = list[option].begin, e = list[option].end;
    for (int i = b; i <= e; i++) {
        t = in & 0xff;
        data1.d[i - 1] = t;
        in >>= 8;
    }
}

int Set()//��ӡѡ��ж����룬����Set_Data()
{
    cout << "-----------------------------------" << endl;
    cout << "      ��Ϸ�浵�ļ��޸Ĺ���" << endl;
    cout << "-----------------------------------" << endl;
    Print(1);
    cout << "-----------------------------------" << endl;
    cout << "0.�����޸�" << endl;
    cout << "1.�����˳�" << endl;
    cout << "-----------------------------------" << endl;

    char c;
    int option = -1, is_name = 0;
    long long in = 0;


    while (1) {
        c = getchar();
        while ((c > 'y' || c < 'a') && (c != '0' && c != '1')) {        //��ֹ��ѭ��
            c = getchar();
        }
        if (c == '0') {
            return 0;
        }
        else if (c == '1') {
            return 1;
        }
        else {
            option = c - 'a';
            while (1) {
                cout << "��ǰ   " << list[option].opt;
                Show_var(option);
                cout << "  ��Χ[ " << list[option].low << "---" << list[option].high << "]�����룺" << endl;
                if (option == 0) {
                    cin >> name;
                    is_name = 1;
                    break;
                }
                cin >> in;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "��ǰ   " << list[option].opt;
                    Show_var(option);
                    cout << "  ��Χ[ " << list[option].low << "---" << list[option].high << "]�����룺" << endl;
                    cin >> in;
                }

                if (in <= list[option].high && in >= list[option].low)
                    break;
                else
                    continue;
            }
            Set_Data(option, in, is_name);
            is_name = 0;
            cout << "-----------------------------------" << endl;
            cout << "      ��Ϸ�浵�ļ��޸Ĺ���" << endl;
            cout << "-----------------------------------" << endl;
            Print(1);
            cout << "-----------------------------------" << endl;
            cout << "0.�����޸�" << endl;
            cout << "1.�����˳�" << endl;
            cout << "-----------------------------------" << endl;
        }
    }
    return 0;
}

int usage(const char* procname)
{
    cout << "usage :" << procname << "--modify | --read" << endl;
    return 0;
}

void Print(int modi)
{
    for (int i = 0; i < 25; i++) {
        if (modi)
            cout << char('a' + i) << '.' << list[i].opt;
        else
            cout << setw(20) << list[i].opt;
        Show_var(i);
        cout << endl;
    }
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������������ֻ�������һ��open��һ��read����Ϊ����������������close��
***************************************************************************/
int read()
{
    /* ��������ֻ������һ�� ifstream�����󣬲����������κ���ʽ��fstream/ifstream/ofstream������Ҳ������ʹ��C��ʽ���ļ����� */
    ifstream infile;

    /* �ļ��򿪣�����Ҫ��Ϊ��
       1��Ҫ���Զ���ʽ�򿪣��򿪷�ʽ***����ָ��
       2��������open�⣬�����������ط��������ٳ���open  */
    infile.open("game.dat", ios::in | ios::binary);
    if (!infile.is_open()) {
        cout << "open_error!" << endl;
        return -1;
    }
    infile.read((char*)data1.d,64);
    infile.close();
    return 1;

    /* ���к����������������������ļ�����ʾ����Ϸ���ֵ���ر��ļ��ȣ�������ú���
       ���У�ֻ������һ���Զ�ȡ64�ֽڵķ�����game.dat�����ݶ���***�����������ơ��ṹ����������ָ����
                 gfile.read(***, sizeof(demo));
    */

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������������ֻ�������һ��open��һ��read��һ��write����Ϊ����������������close��
***************************************************************************/
int modify()
{
    /* ��������ֻ������һ�� fstream�����󣬲����������κ���ʽ��fstream/ifstream/ofstream������Ҳ������ʹ��C��ʽ���ļ����� */
    fstream outfile;

    /* �ļ��򿪣�����Ҫ��Ϊ��
       1��Ҫ���Զ�д��ʽ�򿪣��򿪷�ʽ***����ָ��
       2��������open�⣬�����������ط��������ٳ���open  */
    outfile.open("game.dat", ios::out | ios::binary);
    if (!outfile.is_open()) {
        cout << "open_error!" << endl;
        return -1;
    }
    outfile.write((char*)data1.d,64);
    outfile.close();

    /* ���к����������������������ļ�����ʾ����Ϸ���ֵ���ر��ļ��ȣ�������ú���
       ���У�ֻ������һ���Զ�ȡ64�ֽڵķ�����game.dat�����ݶ���***�����������ơ��ṹ����������ָ����
                 gfile.read(***, sizeof(demo));
             ֻ������һ����д��64�ֽڵķ�����***������д��game.dat�У����������ơ��ṹ����������ָ����
                 gfile.write(***, sizeof(demo));
    */
    return 1;

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main�������������������������ļ���д
***************************************************************************/
int main(int argc, char** argv)
{
    memset(name, 0, sizeof(name));
    if (argc != 2) {
        usage(argv[0]);
        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "--read") == 0) {
        if (read() == -1)
            return 0;
        Print(0);
    }
    if (argc == 2 && strcmp(argv[1], "--modify") == 0) {
       if(read()==-1)
           return 0;
        if (Set() == 1)
            modify();
    }
    return 0;
}
