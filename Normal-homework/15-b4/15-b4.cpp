
#include <iostream>
#include <fstream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
using namespace std;

int usage(const char* procname)
{
	cout << "Usage: " << procname << " --infile hex格式文件  --outfile bin格式文件 " << endl;
	cout << "       " << procname << " --infile a.hex --outfile a.bin" << endl;
	return 0;
}

void Out(ifstream& in)
{
	int a=0,b=0,c=0,d=0,ch;
	while ((a = in.get()) != EOF) {
		
		if (d == 32 && a == 32) {
			if (b <= 'f' && b >= 'a') {
				if (c <= 'f' && c >= 'a') {
					ch = (c - 'a' + 10) * 16 + (b - 'a' + 10);
					cout << char(ch);
				}
				else if (c <= '9' && c >= '0') {
					ch = (c - '0') * 16 + (b - 'a' + 10);
					cout << char(ch);
				}
			}
			else if (b >= '0' && b <= '9') {
				if (c <= 'f' && c >= 'a') {
					ch = (c - 'a'+10) * 16 + (b - '0');
					cout << char(ch);
				}
				else if (c <= '9' && c >= '0') {
					ch = (c - '0') * 16 + (b - '0');
					cout << char(ch);
				}
			}
		}
		d = c;
		c = b;
		b = a;
	
	}
	
}
int convert_bin(ifstream&in,ofstream&out,char**argv,int i,int o)
{
	in.open(argv[i], ios::in | ios::binary);
	if (!in.is_open()) {
		cout << "输入文件" << argv[i] << "打开失败!" << endl;
		return -1;
	}
	streambuf* coutbuf = cout.rdbuf();
	out.open(argv[o], ios::out | ios::binary);
	if (!out.is_open()) {
		cout << "文件2打开失败" << endl;
		return -1;
	}
	streambuf* foutbuf = out.rdbuf();
	cout.rdbuf(foutbuf);

	Out(in);

	out.flush();
	out.close();

	in.close();
	cout.rdbuf(coutbuf);
	return 0;
}

int main(int argc,char** argv)
{
	ifstream in;
	ofstream out;
	if (argc != 5) {
		usage(argv[0]);
		return 0;
	}
	
	
	if (strcmp(argv[1], "--infile") == 0 && strcmp(argv[3], "--outfile") == 0) {
		convert_bin(in, out, argv, 2, 4);
	}
	else if (strcmp(argv[3], "--infile") == 0 && strcmp(argv[1], "--outfile") == 0) {
		convert_bin(in, out, argv, 4, 2);
	}
	else {
		usage(argv[0]);
		return 0;
	}
	
	return 0;
}