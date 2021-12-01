
#include <iostream>
#include <fstream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
using namespace std;

int usage(const char* procname)
{
	cout << "Usage: " << procname << " --infile 原始文件[ --outfile hex格式文件 ]" << endl;
	cout << "       " << procname << " --infile a.docx" << endl;
	cout << "       " << procname << " --infile a.docx --outfile a.hex"<<endl;
	return 0;
}
void Out(ifstream&in,  bool file)
{
	int c, h = 0;
	int a[16], b[16] = { 0 };

	while ((c = in.get()) != EOF) {
		if (h % 16 == 0) {
			cout << setw(8) << setfill('0') << hex << h;
			cout << "  ";
		}
		cout << setw(2) << setfill('0') << hex << c;
		a[h % 16] = c;
		b[h % 16] = 1;
		h++;
		cout << " ";
		if (h % 16 == 0) {
			cout << "    ";
			for (int i = 0; i < 16; i++) {
				if (!b[i])                 //最后一行如果读不满16，保证不会输出后面的那些东西
					continue;
				if (a[i] <= 126 && a[i] >= 33)
					cout << (char)a[i];
				else
					cout << '.';
				//cout << (char)a[i];
			}
			memset(b, 0, sizeof(b));
			cout << endl;
		}
		if (h % 8 == 0 && h % 16) {
			cout << "- ";
		}

	}
	//输出空白
	if (h % 16 == 0)
		return;
	if (h % 16 < 8) {//在 - 左侧
		for (int i = 0; i < 16 - (h % 16); i++) {
			cout << "   ";
		}
		cout << "      ";
	}
	else {
		for (int i = 0; i < 16 - (h % 16); i++) {
			cout << "   ";
		}
		cout << "    ";
	}

	for (int i = 0; i < 16; i++) {//最后一行
		if (!b[i])
			continue;
		if (a[i] <= 126 && a[i] >= 33)
			cout << (char)a[i];
		else
			cout << '.';
	}
	
}

int convert_hex(ifstream&in,ofstream&out,char**argv,int i,int o,bool file)
{
	//in.open(argv[i], ios::in );//肯定有区别，因为十进制读\r\n只会读10而没有前面的13
	in.open(argv[i], ios::in |ios::binary);
	if (!in.is_open()) {
		cout << "输入文件" << argv[i] << "打开失败!" << endl;
		return -1;
	}
	if (file) {//输出重定向
	
		streambuf* coutbuf = cout.rdbuf();
		//out.open(argv[o],ios::out|ios::binary);
		out.open(argv[o], ios::out );
		if (!out.is_open()) {
			cout << "文件打开失败" << endl;
			return -1;
		}
		streambuf* foutbuf = out.rdbuf();
		cout.rdbuf(foutbuf);
		Out(in, 1);
		cout.rdbuf(coutbuf);
	}
	Out(in, 0);
	
	out.flush();
	out.close();
	
	in.close();
	
	return 0;

}
int main(int argc, char** argv)
{
	ifstream in;
	ofstream out;
	if ((argc != 3) && (argc != 5)) {
		usage(argv[0]);
		return 0;
	}
	if (argc == 3) {
		if (strcmp(argv[1], "--infile")) {
			usage(argv[0]);
			return 0;
		}
		convert_hex(in, out,argv,2,0,0);
	}
	else if (argc == 5) {
		if (strcmp(argv[1], "--infile")==0&&strcmp(argv[3],"--outfile")==0) {
			convert_hex(in, out,argv,2,4,1);
		}
		else if(strcmp(argv[3], "--infile") == 0 && strcmp(argv[1], "--outfile") == 0) {
			convert_hex(in, out,argv,4,2,1);
		}
		else {
			usage(argv[0]);
			return 0;
		}
	}
	return 0;
}