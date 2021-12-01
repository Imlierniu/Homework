#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main(int argc, char* argv[])
{
    ofstream out("out.txt", ios::out);
    out << "ABC\x1\x2\x1A\t\v\b\xff\175()-=def" << endl;
    out.close();

    ifstream in("out.txt", ios::in | ios::binary);
    int c = 0;
    char ch;
    while (!in.eof()) {
        ch=in.get();
        cout << ch << " ";
    }
    cout << c << endl;
    in.close();

    return 0;
}