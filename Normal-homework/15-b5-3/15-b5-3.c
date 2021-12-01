#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//根据需要可加入其它头文件


//此处为示例，允许修改结构体名称，允许修改结构体中的成员内容，要求sizeof必须是64
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
    { "玩家昵称：",1,16,0,0 },
    { "生命值：",17,18,0,10000 },
    { "力量值：",19,20,0,10000 },
    { "体质值：",21,22,0,8192 },
    { "灵巧值：",23,24,0,1024 },
    { "金钱值：",25,28,0,100000000 },
    { "名声值：",29,32,0,1000000 },
    { "魅力值：",33,36,0,1000000 },
    {"游戏累积时间(us)值：",37,44,0,10000000000000000},
    { "移动速度值：",45,45,0, 100 },
    { "攻击速度值：",46,46,0 ,100 },
    { "攻击范围值：",47,47,0,100 },
    //48不用
    { "攻击力值：",49,50,0,2000 },
    { "防御力值：",51,52,0 ,2000 },
    { "敏捷度值：",53,53,0,100 },
    { "智力值：",54,54,0,100 },
    { "经验值：",55,55,0,100 },
    { "等级值：",56,56,0,100 },
    { "魔法值：",57,58,0,10000 },
    { "消耗魔法值：",59,59,0, 100 },
    { "魔法伤害力值：",60,60,0 ,100 },
    { "命中率值：",61,61,0, 100 },
    { "魔法防御力值：",62,62,0 ,100 },
    { "暴击率值：",63,63,0,100 },
    { "耐力值：",64,64,0,100 },
};

/* 此处允许新增函数，数量不限
   1、所有新增的函数，均不允许定义新的 fstream / ifstream / ofstream 流对象，并进行打开/读/写/关闭等操作
   2、所有新增的函数，均不允许用C方式进行文件处理
   3、上述两个限制同样适用于main函数
*/
void Print(int modi);

long long Pow(long long a,int b)//由于c在linux使用math.h需要加编译参数-lm,为了防止作业不通过，只好自己写一个pow函数
{
    long long ans = 1;
    for (int i = 0; i < b; i++) {
        ans *= a;
    }
    return ans;
}

void Show_var(int i)
{
    long long temp = 0;
    if (i == 0) {
        for (int j = 0; data1.d[j] != '\0'; j++)
            printf("%c", data1.d[j]);
        //cout << endl;
    }
    else {
        for (int j = list[i].begin, j0 = j; j <= list[i].end; j++)
            temp += (long long)Pow(256, (j - j0)) * data1.d[j - 1];
        printf("%lld", temp);
    }
}

void Set_Data(int option, long long in, int isname)  //修改结构体中的数据
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

int Set()//打印选项，判断输入，调用Set_Data()
{
    printf("-----------------------------------\n");
    printf("      游戏存档文件修改工具\n");
    printf("-----------------------------------\n");
    Print(1);
    printf("-----------------------------------\n");
    printf("0.放弃修改\n");
    printf("1.存盘退出\n");
    printf("-----------------------------------\n");

    char c;
    int option = -1, is_name = 0;
    long long in = 0;


    while (1) {
        c = getchar();
        while ((c > 'y' || c < 'a') && (c != '0' && c != '1')) {        //防止死循环
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
                printf("当前   %s",list[option].opt);
                Show_var(option);
                printf("  范围[ %d---%lld ]请输入：\n", list[option].low, list[option].high);
                if (option == 0) {
                    scanf("%s",name);
                    is_name = 1;
                    break;
                }
                //scanf(" % d", &in);
                while (scanf("%lld", &in) != 1) {
                    rewind(stdin);
                    printf("当前   %s", list[option].opt);
                    Show_var(option);
                    printf("  范围[ %d---%lld ]请输入：\n", list[option].low, list[option].high);
                }
                

                if (in <= list[option].high && in >= list[option].low)
                    break;
                else
                    continue;
            }
            Set_Data(option, in, is_name);
            is_name = 0;
            printf("-----------------------------------\n");
            printf("      游戏存档文件修改工具\n");
            printf("-----------------------------------\n");
            Print(1);
            printf("-----------------------------------\n");
            printf("0.放弃修改\n");
            printf("1.存盘退出\n");
            printf("-----------------------------------\n");
        }
    }
    return 0;
}

int usage(const char* procname)
{
    printf("usage : %s--modify | --read\n", procname);
    return 0;
}

void Print(int modi)
{
    for (int i = 0; i < 25; i++) {
        if (modi)
            printf("%c.%s", i + 'a', list[i].opt);
        else
            printf("%20s",list[i].opt);
   
        Show_var(i);
        printf("\n");
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次open、一次read（因为包含错误处理，允许多次close）
***************************************************************************/
int read()
{
    /* 本函数中只允许定义一个 ifstream流对象，不再允许定义任何形式的fstream/ifstream/ofstream流对象，也不允许使用C方式的文件处理 */
    FILE* fp;

    /* 文件打开，具体要求为：
       1、要求以读方式打开，打开方式***自行指定
       2、除本次open外，本函数其它地方不允许再出现open  */
    if ((fp = fopen("game.dat", "r") )== NULL) {
        printf("open_error!\n");
        return 0;
    }
    fread(data1.d,64,1,fp);
    
    fclose(fp);
    return 1;

    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 gfile.read(***, sizeof(demo));
    */

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次open、一次read、一次write（因为包含错误处理，允许多次close）
***************************************************************************/
int modify()
{
    /* 本函数中只允许定义一个 fstream流对象，不再允许定义任何形式的fstream/ifstream/ofstream流对象，也不允许使用C方式的文件处理 */
    FILE* fp;

    /* 文件打开，具体要求为：
       1、要求以读写方式打开，打开方式***自行指定
       2、除本次open外，本函数其它地方不允许再出现open  */
    if ((fp = fopen("game.dat", "w"))== NULL) {
        printf("open_error!\n");
        return 0;
    }
    fwrite(data1.d, 64, 1, fp);

    fclose(fp);
    return 1;

    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 gfile.read(***, sizeof(demo));
             只允许用一次性写入64字节的方法将***的内容写入game.dat中（缓冲区名称、结构体名称自行指定）
                 gfile.write(***, sizeof(demo));
    */
    return 1;

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数允许带参数，不允许进行文件读写
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
