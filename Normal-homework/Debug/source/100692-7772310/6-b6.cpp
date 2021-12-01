/* 请写入你的信息(忘了写，5%的分数没有了哦) */

#include <iostream>
using namespace std;

/* 函数的原型定义不准变 */
int   tj_strlen(const char *str);
char *tj_strcat(char *s1, const char *s2);
char *tj_strcpy(char *s1, const char *s2);
char *tj_strncpy(char *s1, const char *s2, const int len);
int   tj_strcmp(const char *s1, const char *s2);
int   tj_strcasecmp(const char *s1, const char *s2);
int   tj_strncmp(const char *s1, const char *s2, const int len);
int   tj_strcasencmp(const char *s1, const char *s2, const int len);
char *tj_strupr(char *str);
char *tj_strlwr(char *str);
int   tj_strchr(const char *str, const char ch);
int   tj_strstr(const char *str, const char *substr);
int   tj_strrchr(const char *str, const char ch);
int   tj_strrstr(const char *str, const char *substr);
char *tj_strrev(char *str);


/* ----- 不允许定义任何形式的全局数组!!!!! ----- */

/* 函数实现部分，{ }内的东西可以任意调整，目前的return只是一个示例，可改变 */

int tj_strlen(const char *str)    //字符串长度
{
	int counter = 0;
	if(str == 0)
		return 0;
	else
	{
	    for( ; *str != 0; str++)
	    	counter ++;
        return counter;
	}
}

char *tj_strcat(char *s1, const char *s2)   //字符串的拼接
{
	char *p1 = s1;

	if(s2 == 0 || tj_strlen(s2) == 0 || s1 == 0)
		;
	else 
	{
		for( ; *p1 != 0; p1++)
			;
		for( ; *s2 != 0; p1++, s2++)
			*p1 = *s2;
		*p1 = 0;
	}

    return s1;
}

char *tj_strcpy(char *s1, const char *s2)     //字符串的复制
{
	char *p1 = s1;

	if(s1 == 0)
		;
	else if(s2 == 0 || tj_strlen(s2) == 0)
		*p1 = 0;
	else
	{
		for( ; *s2 != 0; p1++, s2++)
			*p1 = *s2;
		*p1 = 0;
	}

    return s1;
}

char *tj_strncpy(char *s1, const char *s2, const int len)    //复制几个字符
{
	char *p1 = s1;

	if(s1 == 0)
		;
	else if(s2 == 0 || tj_strlen(s2) == 0)
		;
	else
	{
		for( ; *s2 != 0 && p1 - s1 < len; p1++, s2++)
			*p1 = *s2;
	}

    return s1;
}

int tj_strcmp(const char *s1, const char *s2)        //比较字符串
{
	if(s1 == 0)
	{
		if(s2 == 0)
			return 0;
		else
			return -1;
	}
	else
	{
		if(s2 == 0)
			return 1;
		else
		{
			for( ; (*s1 == *s2) && *s1 != 0 && *s2 != 0; s1++, s2++)
				;

			return (*s1-*s2);
		}
	}
}

int tj_strcasecmp(const char *s1, const char *s2)
{
    if(s1 == 0)
	{
		if(s2 == 0)
			return 0;
		else
			return -1;
	}
	else
	{
		if(s2 == 0)
			return 1;
		else
		{
			for( ;*s1 != 0 && *s2 != 0; s1++, s2++)
			{
				if(*s1 != *s2)
				{
					if( *s1 >= 'a' && *s1 <= 'z')
					{
						if(*s1 - 32 != *s2)
							break;
					}
					else if( *s1 >= 'A' && *s1 <= 'Z')
					{
						if(*s1 + 32 != *s2)
						    break;
					}
				}
			}
			return (*s1-*s2);
		}
	}
}


int tj_strncmp(const char *s1, const char *s2, const int len)
{
	int counter = 1;

	if(s1 == 0)
	{
		if(s2 == 0)
			return 0;
		else
			return -1;
	}
	else
	{
		if(s2 == 0)
			return 1;
		else
		{
			for( ; (*s1 == *s2) && *s1 != 0 && *s2 != 0 && counter < len; s1++, s2++, counter++)
				;

			return (*s1-*s2);
		}
	}

    return 0;
}

int tj_strcasencmp(const char *s1, const char *s2, const int len)
{
	int counter = 1;

    if(s1 == 0)
	{
		if(s2 == 0)
			return 0;
		else
			return -1;
	}
	else
	{
		if(s2 == 0)
			return 1;
		else
		{
			for( ;*s1 != 0 && *s2 != 0 && counter < len; s1++, s2++, counter++)
			{
				if(*s1 != *s2)
				{
					if( *s1 >= 'a' && *s1 <= 'z')
					{
						if(*s1 - 32 != *s2)
							break;
					}
					else if( *s1 >= 'A' && *s1 <= 'Z')
					{
						if(*s1 + 32 != *s2)
						    break;
					}
				}
			}
			if( *s1 >= 'a' && *s1 <= 'z')
			{
				if(*s1 - 32 == *s2)
					return 0;
			}
			else if( *s1 >= 'A' && *s1 <= 'Z')
			{
				if(*s1 + 32 == *s2)
				   return 0;
			}
			return (*s1-*s2);
		}
	}
    return 0;
}

char *tj_strupr(char *str)
{
	char *p =str;

	if(str == 0)
		return 0;
	else
	{
	    for( ; *p != 0; p++)
		{
			if(*p <= 'z' && *p >= 'a')
				*p -= 32;
		}
	}

    return str;
}

char *tj_strlwr(char *str)
{
    char *p =str;

	if(str == 0)
		return 0;
	else
	{
	    for( ; *p != 0; p++)
		{
			if(*p <= 'Z' && *p >= 'A')
				*p += 32;
		}
	}

    return str;
}

int tj_strchr(const char *str, const char ch)  //确定某字符在字符串中的位置
{
	int counter = 1;
	if(str == 0)
		return 0;
	else
	{
	    for( ; *str != 0 && *str != ch; str++)
	    	counter ++;
		if(*str != 0)
            return counter;
		else
			return 0;
	}
}

int tj_strstr(const char *str, const char *substr)
{
	int k;
    int counter = 1;
	if(str == 0)
		return 0;
	else if(substr == 0)
		return 0;
	else
	{
	    for( ; *str != 0; str++)
		{
			if(*str == *substr)
			{
				k = counter;
				if( tj_strncmp(str, substr, tj_strlen(substr)) == 0 )
					return counter;
			}
	    	counter ++;
		}
	}

    return 0;
}

int tj_strrchr(const char *str, const char ch)
{
	int b = 0;
    int counter = 1;
	if(str == 0)
		return 0;
	else
	{
	    for( ; *str != 0 ; str++)
		{
			if(*str == ch)
				b = counter;
			counter ++;
		}
	    return b;
	}
}

int tj_strrstr(const char *str, const char *substr)
{
    int k = 0;
    int counter = 1;
	if(str == 0)
		return 0;
	else if(substr == 0)
		return 0;
	else
	{
	    for( ; *str != 0; str++)
		{
			if(*str == *substr)
			{
				if(tj_strncmp(str, substr, tj_strlen(substr)) == 0 )
					k = counter;
			}
	    	counter ++;
		}
	}

    return k;
}

char *tj_strrev(char *str)
{
	int counter = 1;
	int a;
	char temp;
	a = tj_strlen(str);

	char *p = str;
    if(str == 0)
		;
	else
	{
		for( str += a-1 ; counter <= a/2 ; str--, p++)
		{
			temp = *p;
			*p = *str;
			*str = temp;
			counter++;
		}
		if(a % 2)
    	    str -= (a/2);
		else
			str -= (a/2)-1;
	}

    return str;
}
/* ==The End==(函数实现部分) */

void press_key(char *prompt="")
{
    cout << endl << prompt << "，按回车键继续" << endl;
    getchar();
    cin.clear();
    cin.sync();
}

/* main函数(细节可能有错，若发现，请及时反映) */
int main()
{
    if (1) {
        char  s1[]="abcdefghijklmnopqrstuvwxyz";
        char  s2[]="abcdefghijklmnopqrstuvwxyz\0UVWXYZ";
        char  s3[]="";
        char *p4 =NULL;

        cout << "tj_strlen()测试部分：" << endl;
        cout << "1.s1      的长度应该是26，实际是：" << tj_strlen(s1)      << endl;
        cout << "2.s2      的长度应该是26，实际是：" << tj_strlen(s2)      << endl;
        cout << "3.&s2[27] 的长度应该是6， 实际是：" << tj_strlen(&s2[27]) << endl;
        cout << "4.s3      的长度应该是0， 实际是：" << tj_strlen(s3)      << endl;
        cout << "5.p4      的长度认为是0， 实际是：" << tj_strlen(p4)      << endl;

        press_key("tj_strlen() 测试完成");
        }

    if (1) {
        char  s1[80]="abcdefghij";
        char  s2[]="abcde";
        char  s3[]="hello\0UVWXYZ";
        char  s4[]="";
        char *p5=NULL;

        cout << "tj_strcat()测试部分：" << endl;
        cout << "1.s1的输出应该是abcdefghij，                实际是：" << s1 << endl;
        cout << "  s1的长度应该是10，                        实际是：" << tj_strlen(s1) << endl;

        cout << "2.s1的输出应该是abcdefghijabcde，           实际是：" << tj_strcat(s1, s2) << endl;
        cout << "  s1的长度应该是15，                        实际是：" << tj_strlen(s1)     << endl;

        cout << "3.s1的输出应该是abcdefghijabcdehello，      实际是：" << tj_strcat(s1, s3) << endl;
        cout << "  s1的长度应该是20，                        实际是：" << tj_strlen(s1)     << endl;

        cout << "4.s1的输出应该是abcdefghijabcdehelloUVWXYZ，实际是：" << tj_strcat(s1, &s3[6]) << endl;
        cout << "  s1的长度应该是26，                        实际是：" << tj_strlen(s1)         << endl;

        cout << "5.s1的输出应该是abcdefghijabcdehelloUVWXYZ，实际是：" << tj_strcat(s1, s4) << endl;
        cout << "  s1的长度应该是26，                        实际是：" << tj_strlen(s1)     << endl;

        cout << "6.s1的输出应该是abcdefghijabcdehelloUVWXYZ，实际是：" << tj_strcat(s1, p5) << endl;
        cout << "  s1的长度应该是26，                        实际是：" << tj_strlen(s1)     << endl;

        cout << "7.p5的输出应该是<NULL>，                    实际是：" << (tj_strcat(p5, s1)==NULL ? "<NULL>":tj_strcat(p5, s1)) << endl;
        cout << "  p5的长度应该是0，                         实际是：" << tj_strlen(p5)     << endl;

        cout << "8.p5的输出应该是<NULL>，                    实际是：" << (tj_strcat(p5, NULL)==NULL ? "<NULL>":tj_strcat(p5, NULL)) << endl;
        cout << "  p5的长度应该是0，                         实际是：" << tj_strlen(p5)     << endl;

        press_key("tj_strcat() 测试完成");
        }

    if (1) {
        char  s0[80];
        char  s1[80]="abcdefghijklm";
        char  s2[]="abcde";
        char  s3[]="hello\0UVWXYZ";
        char  s4[]="";
        char *p5=NULL;
        char *p6=NULL;

        cout << "tj_strcpy()测试部分：" << endl;
        cout << "1.s1的输出应该是abcdefghijklm，   实际是：" << s1            << endl;
        cout << "  s1的长度应该是13，              实际是：" << tj_strlen(s1) << endl;

        cout << "2.s1的输出应该是abcde，           实际是：" << tj_strcpy(s1, s2) << endl;
        cout << "  s1的长度应该是5，               实际是：" << tj_strlen(s1)     << endl;

        cout << "3.s1的输出应该是UVWXYZ，          实际是：" << tj_strcpy(s1, &s3[6]) << endl;
        cout << "  s1的长度应该是6，               实际是：" << tj_strlen(s1)         << endl;

        cout << "4.s1的输出应该是hello，           实际是：" << tj_strcpy(s1, s3) << endl;
        cout << "  s1的长度应该是5，               实际是：" << tj_strlen(s1)     << endl;

        cout << "5.s1的输出应该是--，              实际是：-" << tj_strcpy(s1, s4) << '-' << endl;
        cout << "  s1的长度应该是0，               实际是："  << tj_strlen(s1)     << endl;

        tj_strcpy(s0, s2);
	    tj_strcat(s0, s3);
        cout << "6.s0的输出应该是abcdehelloUVWXYZ，实际是：" << tj_strcat(s0, &s3[6]) << endl;
        cout << "  s0的长度应该是16，              实际是：" << tj_strlen(s0)         << endl;

        cout << "7.s0的输出应该是--，              实际是：-" << tj_strcpy(s0, p5) << '-' << endl;
        cout << "  s0的长度应该是0，               实际是："  << tj_strlen(s0)     << endl;

        cout << "8.p5的输出应该是<NULL>，          实际是："  << (tj_strcpy(p5, s0)==NULL ? "<NULL>" : tj_strcpy(p5, s0)) << endl;
        cout << "  p5的长度应该是0，               实际是："  << tj_strlen(p5)     << endl;

        cout << "9.p5的输出应该是<NULL>，          实际是："  << (tj_strcpy(p5, p6)==NULL ? "<NULL>" : tj_strcpy(p5, p6)) << endl;
        cout << "  p5的长度应该是0，               实际是："  << tj_strlen(p5)     << endl;

        press_key("tj_strcpy() 测试完成");
        }

    if (1) {
        char  s0[80];
        char  s1[80]="abcdefghijklm";
        char  s2[]="abcde";
        char  s3[]="hello\0UVWXYZ";
        char  s4[]="";
        char *p5=NULL;
        char *p6=NULL;

        cout << "tj_strncpy()测试部分：" << endl;
        cout << "1. s1的输出应该是abcdefghijklm，   实际是：" << s1            << endl;
        cout << "   s1的长度应该是13，              实际是：" << tj_strlen(s1) << endl;

        cout << "2. s1的输出应该是hellofghijklm，   实际是：" << tj_strncpy(s1, s3, 10) << endl;
        cout << "   s1的长度应该是13，              实际是：" << tj_strlen(s1)          << endl;

        tj_strcpy(s1, "abcdefghijklm");
        cout << "3. s1的输出应该是hellofghijklm，   实际是：" << tj_strncpy(s1, s3, 5) << endl;
        cout << "   s1的长度应该是13，              实际是：" << tj_strlen(s1)         << endl;

        tj_strcpy(s1, "abcdefghijklm");
        cout << "4. s1的输出应该是heldefghijklm，   实际是：" << tj_strncpy(s1, s3, 3) << endl;
        cout << "   s1的长度应该是13，              实际是：" << tj_strlen(s1)         << endl;

        tj_strcpy(s1, "abcdefghijklm");
        cout << "5. s1的输出应该是abcdefghijklm，   实际是：" << tj_strncpy(s1, s4, 2) << endl;
        cout << "   s1的长度应该是13，              实际是：" << tj_strlen(s1)         << endl;

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], s3, 10);
        cout << "6. s1的输出应该是abcdhellojklm，   实际是：" << s1            << endl;
        cout << "   s1的长度应该是13，              实际是：" << tj_strlen(s1) << endl;

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], s3, 5);
        cout << "7. s1的输出应该是abcdhellojklm，   实际是：" << s1            << endl;
        cout << "   s1的长度应该是13，              实际是：" << tj_strlen(s1) << endl;

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], s3, 3);
        cout << "8. s1的输出应该是abcdhelhijklm，   实际是：" << s1            << endl;
        cout << "   s1的长度应该是13，              实际是：" << tj_strlen(s1) << endl;

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], &s3[6], 10);
        cout << "9. s1的输出应该是abcdUVWXYZklm，   实际是：" << s1            << endl;
        cout << "   s1的长度应该是13，              实际是：" << tj_strlen(s1) << endl;

        press_key("tj_strncpy() 测试暂停");

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], &s3[6], 6);
        cout << "10.s1的输出应该是abcdUVWXYZklm，   实际是：" << s1            << endl;
        cout << "   s1的长度应该是13，              实际是：" << tj_strlen(s1) << endl;

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], &s3[6], 3);
        cout << "11.s1的输出应该是abcdUVWhijklm，   实际是：" << s1            << endl;
        cout << "   s1的长度应该是13，              实际是：" << tj_strlen(s1) << endl;

        tj_strncpy(s0, s2, tj_strlen(s2));
        s0[tj_strlen(s2)] = 0;
        cout << "12.s0的输出应该是abcde，           实际是：" << s0            << endl;
        cout << "   s0的长度应该是5，               实际是：" << tj_strlen(s0) << endl;

        cout << "13.s0的输出应该是abcdehello，      实际是：" << tj_strcat(s0, s3) << endl;
        cout << "   s0的长度应该是10，              实际是：" << tj_strlen(s0)     << endl;
        
        int old_len = tj_strlen(s0);
        tj_strncpy(&s0[10], &s3[6], tj_strlen(&s3[6]));
        s0[old_len + tj_strlen(&s3[6]) ] = 0;
        cout << "14.s0的输出应该是abcdehelloUVWXYZ，实际是：" << s0            << endl;
        cout << "   s0的长度应该是16，              实际是：" << tj_strlen(s0) << endl;

        cout << "15.s0的输出应该是abcdehelloUVWXYZ，实际是："  << tj_strncpy(s0, p5, 2) << endl;
        cout << "   s0的长度应该是16，              实际是："  << tj_strlen(s0)     << endl;

        cout << "16.p5的输出应该是<NULL>，          实际是："  << (tj_strncpy(p5, s0, 2)==NULL ? "<NULL>" : tj_strncpy(p5, s0, 2)) << endl;
        cout << "   p5的长度应该是0，               实际是："  << tj_strlen(p5)     << endl;

        cout << "17.p5的输出应该是<NULL>，          实际是："  << (tj_strncpy(p5, p6, 2)==NULL ? "<NULL>" : tj_strncpy(p5, p6, 2)) << endl;
        cout << "   p5的长度应该是0，               实际是："  << tj_strlen(p5)     << endl;

        press_key("tj_strncpy() 测试完成");
        }

    if (1) {
        char  s1[]="horse";
        char  s2[]="house";
        char  s3[]="hell";
        char  s4[]="hello";
        char  s5[]="hello";
        char  s6[]="hell";
        char  s7[]="hello";
        char  s8[]="hello";
        char  s9[]="hello";
        char  s10[]="hello\0UVWXYZ";
        char  s11[]="HELLO";
        char  s12[]="hello";
        char  s13[]="HeLlO";
        char  s14[]="hElLo";
        char *p15 = NULL;
        char *p16 = NULL;

        cout << "tj_strcmp()测试部分：" << endl;
        cout << "1.s1 和s2 的输出应该是-3，  实际是：" << tj_strcmp(s1,  s2)  << endl;
        cout << "2.s3 和s4 的输出应该是-111，实际是：" << tj_strcmp(s3,  s4)  << endl;
        cout << "3.s5 和s6 的输出应该是111， 实际是：" << tj_strcmp(s5,  s6)  << endl;
        cout << "4.s7 和s8 的输出应该是0，   实际是：" << tj_strcmp(s7,  s8)  << endl;
        cout << "5.s9 和s10的输出应该是0，   实际是：" << tj_strcmp(s9,  s10) << endl;
        cout << "6.s11和s12的输出应该是-32， 实际是：" << tj_strcmp(s11, s12) << endl;
        cout << "7.s13和s14的输出应该是-32， 实际是：" << tj_strcmp(s13, s14) << endl;
        cout << "8.p15和s1 的输出应该是-1，  实际是：" << tj_strcmp(p15, s1)  << endl;
        cout << "  s1 和p15的输出应该是1，   实际是：" << tj_strcmp(s1,  p15) << endl;
        cout << "  p15和p16的输出应该是0，   实际是：" << tj_strcmp(p15, p16) << endl;

        press_key("tj_strcmp() 测试完成");
        }

    if (1) {
        char  s1[]="horse";
        char  s2[]="house";
        char  s3[]="hell";
        char  s4[]="hello";
        char  s5[]="hello";
        char  s6[]="hell";
        char  s7[]="hello";
        char  s8[]="hello";
        char  s9[]="hello";
        char  s10[]="hello\0UVWXYZ";
        char  s11[]="HELLO";
        char  s12[]="hello";
        char  s13[]="HeLlO";
        char  s14[]="hElLo";
        char *p15 = NULL;
        char *p16 = NULL;

        cout << "tj_strcasecmp()测试部分：" << endl;
        cout << "1.s1 和s2 的输出应该是-3，  实际是：" << tj_strcasecmp(s1,  s2)  << endl;
        cout << "2.s3 和s4 的输出应该是-111，实际是：" << tj_strcasecmp(s3,  s4)  << endl;
        cout << "3.s5 和s6 的输出应该是111， 实际是：" << tj_strcasecmp(s5,  s6)  << endl;
        cout << "4.s7 和s8 的输出应该是0，   实际是：" << tj_strcasecmp(s7,  s8)  << endl;
        cout << "5.s9 和s10的输出应该是0，   实际是：" << tj_strcasecmp(s9,  s10) << endl;
        cout << "6.s11和s12的输出应该是0，   实际是：" << tj_strcasecmp(s11, s12) << endl;
        cout << "7.s13和s14的输出应该是0，   实际是：" << tj_strcasecmp(s13, s14) << endl;
        cout << "8.p15和s1 的输出应该是-1，  实际是：" << tj_strcasecmp(p15, s1)  << endl;
        cout << "  s1 和p15的输出应该是1，   实际是：" << tj_strcasecmp(s1,  p15) << endl;
        cout << "  p15和p16的输出应该是0，   实际是：" << tj_strcasecmp(p15, p16) << endl;

        press_key("tj_strcasecmp() 测试完成");
        }

    if (1) {
        char  s1[]="horse";
        char  s2[]="house";
        char  s3[]="hell";
        char  s4[]="hello";
        char  s5[]="hello";
        char  s6[]="hell";
        char  s7[]="hello";
        char  s8[]="hello";
        char  s9[]="hello";
        char  s10[]="hello\0UVWXYZ";
        char  s11[]="HELLO";
        char  s12[]="hello";
        char  s13[]="HeLlO";
        char  s14[]="hElLo";
        char *p15 = NULL;
        char *p16 = NULL;

        cout << "tj_strncmp()测试部分：" << endl;
        cout << "1.s1 和s2 比较前10个字符的输出应该是-3，  实际是：" << tj_strncmp(s1,  s2,  10) << endl;
        cout << "  s1 和s2 比较前5 个字符的输出应该是-3，  实际是：" << tj_strncmp(s1,  s2,  5)  << endl;
        cout << "  s1 和s2 比较前3 个字符的输出应该是-3，  实际是：" << tj_strncmp(s1,  s2,  3)  << endl;
        cout << "  s1 和s2 比较前2 个字符的输出应该是0，   实际是：" << tj_strncmp(s1,  s2,  2)  << endl;
        cout << "2.s3 和s4 比较前10个字符的输出应该是-111，实际是：" << tj_strncmp(s3,  s4,  10) << endl;
        cout << "  s3 和s4 比较前5 个字符的输出应该是-111，实际是：" << tj_strncmp(s3,  s4,  5)  << endl;
        cout << "  s3 和s4 比较前4 个字符的输出应该是0，   实际是：" << tj_strncmp(s3,  s4,  4)  << endl;
        cout << "3.s5 和s6 比较前10个字符的输出应该是111 ，实际是：" << tj_strncmp(s5,  s6,  10) << endl;
        cout << "  s5 和s6 比较前5 个字符的输出应该是111， 实际是：" << tj_strncmp(s5,  s6,  5)  << endl;
        cout << "  s5 和s6 比较前4 个字符的输出应该是0，   实际是：" << tj_strncmp(s5,  s6,  4)  << endl;
        cout << "4.s7 和s8 比较前10个字符的输出应该是0 ，  实际是：" << tj_strncmp(s7,  s8,  10) << endl;
        cout << "  s7 和s8 比较前5 个字符的输出应该是0，   实际是：" << tj_strncmp(s7,  s8,  5)  << endl;
        cout << "  s7 和s8 比较前4 个字符的输出应该是0，   实际是：" << tj_strncmp(s7,  s8,  4)  << endl;
        cout << "5.s9 和s10比较前10个字符的输出应该是0 ，  实际是：" << tj_strncmp(s9,  s10, 10) << endl;
        cout << "  s9 和s10比较前5 个字符的输出应该是0，   实际是：" << tj_strncmp(s9,  s10, 5)  << endl;
        cout << "  s9 和s10比较前4 个字符的输出应该是0，   实际是：" << tj_strncmp(s9,  s10, 4)  << endl;
        press_key("tj_strncmp() 测试暂停");

        cout << "6.s11和s12比较前10个字符的输出应该是-32， 实际是：" << tj_strncmp(s11, s12, 10) << endl;
        cout << "  s11和s12比较前5 个字符的输出应该是-32， 实际是：" << tj_strncmp(s11, s12, 5)  << endl;
        cout << "  s11和s12比较前2 个字符的输出应该是-32， 实际是：" << tj_strncmp(s11, s12, 2)  << endl;
        cout << "7.s13和s14比较前10个字符的输出应该是-32， 实际是：" << tj_strncmp(s13, s14, 10) << endl;
        cout << "  s13和s14比较前5 个字符的输出应该是-32， 实际是：" << tj_strncmp(s13, s14, 5)  << endl;
        cout << "  s13和s14比较前2 个字符的输出应该是-32， 实际是：" << tj_strncmp(s13, s14, 2)  << endl;
        cout << "8.p15和s1 比较前2 个字符的输出应该是-1，  实际是：" << tj_strncmp(p15, s1,  2) << endl;
        cout << "  s1 和p15比较前2 个字符的输出应该是1，   实际是：" << tj_strncmp(s1,  p15, 5)  << endl;
        cout << "  p15和p16比较前2 个字符的输出应该是0，   实际是：" << tj_strncmp(p15, p16, 2)  << endl;

        press_key("tj_strncmp() 测试结束");
        }

    if (1) {
        char  s1[]="horse";
        char  s2[]="house";
        char  s3[]="hell";
        char  s4[]="hello";
        char  s5[]="hello";
        char  s6[]="hell";
        char  s7[]="hello";
        char  s8[]="hello";
        char  s9[]="hello";
        char  s10[]="hello\0UVWXYZ";
        char  s11[]="HELLO";
        char  s12[]="hello";
        char  s13[]="HeLlO";
        char  s14[]="hElLo";
        char *p15 = NULL;
        char *p16 = NULL;

        cout << "tj_strcasencmp()测试部分：" << endl;
        cout << "1.s1 和s2 比较前10个字符的输出应该是-3，  实际是：" << tj_strcasencmp(s1,  s2,  10) << endl;
        cout << "  s1 和s2 比较前5 个字符的输出应该是-3，  实际是：" << tj_strcasencmp(s1,  s2,  5)  << endl;
        cout << "  s1 和s2 比较前3 个字符的输出应该是-3，  实际是：" << tj_strcasencmp(s1,  s2,  3)  << endl;
        cout << "  s1 和s2 比较前2 个字符的输出应该是0，   实际是：" << tj_strcasencmp(s1,  s2,  2)  << endl;
        cout << "2.s3 和s4 比较前10个字符的输出应该是-111，实际是：" << tj_strcasencmp(s3,  s4,  10) << endl;
        cout << "  s3 和s4 比较前5 个字符的输出应该是-111，实际是：" << tj_strcasencmp(s3,  s4,  5)  << endl;
        cout << "  s3 和s4 比较前4 个字符的输出应该是0，   实际是：" << tj_strcasencmp(s3,  s4,  4)  << endl;
        cout << "3.s5 和s6 比较前10个字符的输出应该是111 ，实际是：" << tj_strcasencmp(s5,  s6,  10) << endl;
        cout << "  s5 和s6 比较前5 个字符的输出应该是111， 实际是：" << tj_strcasencmp(s5,  s6,  5)  << endl;
        cout << "  s5 和s6 比较前4 个字符的输出应该是0，   实际是：" << tj_strcasencmp(s5,  s6,  4)  << endl;
        cout << "4.s7 和s8 比较前10个字符的输出应该是0 ，  实际是：" << tj_strcasencmp(s7,  s8,  10) << endl;
        cout << "  s7 和s8 比较前5 个字符的输出应该是0，   实际是：" << tj_strcasencmp(s7,  s8,  5)  << endl;
        cout << "  s7 和s8 比较前4 个字符的输出应该是0，   实际是：" << tj_strcasencmp(s7,  s8,  4)  << endl;
        cout << "5.s9 和s10比较前10个字符的输出应该是0 ，  实际是：" << tj_strcasencmp(s9,  s10, 10) << endl;
        cout << "  s9 和s10比较前5 个字符的输出应该是0，   实际是：" << tj_strcasencmp(s9,  s10, 5)  << endl;
        cout << "  s9 和s10比较前4 个字符的输出应该是0，   实际是：" << tj_strcasencmp(s9,  s10, 4)  << endl;
        press_key("tj_strcasencmp() 测试暂停");

        cout << "6.s11和s12比较前10个字符的输出应该是0，   实际是：" << tj_strcasencmp(s11, s12, 10) << endl;
        cout << "  s11和s12比较前5 个字符的输出应该是0，   实际是：" << tj_strcasencmp(s11, s12, 5)  << endl;
        cout << "  s11和s12比较前2 个字符的输出应该是0，   实际是：" << tj_strcasencmp(s11, s12, 2)  << endl;
        cout << "7.s13和s14比较前10个字符的输出应该是0，   实际是：" << tj_strcasencmp(s13, s14, 10) << endl;
        cout << "  s13和s14比较前5 个字符的输出应该是0，   实际是：" << tj_strcasencmp(s13, s14, 5)  << endl;
        cout << "  s13和s14比较前2 个字符的输出应该是0，   实际是：" << tj_strcasencmp(s13, s14, 2)  << endl;
        cout << "8.p15和s1 比较前2 个字符的输出应该是-1，  实际是：" << tj_strcasencmp(p15, s1,  2) << endl;
        cout << "  s1 和p15比较前2 个字符的输出应该是1，   实际是：" << tj_strcasencmp(s1,  p15, 5)  << endl;
        cout << "  p15和p16比较前2 个字符的输出应该是0，   实际是：" << tj_strcasencmp(p15, p16, 2)  << endl;

        press_key("tj_strcasencmp() 测试完成");
        }

     if (1) {
        char  s1[]="123horseHELLO*#@";
        char  s2[]="1A2b3C*d#E@f";
        char *p3 = NULL;

        cout << "tj_strupr()测试部分：" << endl;
        cout << "1.s1 的输出应该是123HORSEHELLO*#@，实际是：" << tj_strupr(s1) << endl;
        cout << "2.s2 的输出应该是1A2B3C*D#E@F，    实际是：" << tj_strupr(s2) << endl;
        cout << "3.p3 的输出应该是<NULL>，          实际是：" << (tj_strupr(p3)==NULL ? "<NULL>":tj_strupr(p3)) << endl;

        press_key("tj_strupr() 测试完成");
        }

     if (1) {
        char  s1[]="123horseHELLO*#@";
        char  s2[]="1A2b3C*d#E@f";
        char *p3 = NULL;

        cout << "tj_strlwr()测试部分：" << endl;
        cout << "1.s1 的输出应该是123horsehello*#@，实际是：" << tj_strlwr(s1) << endl;
        cout << "2.s2 的输出应该是1a2b3c*d#e@f，    实际是：" << tj_strlwr(s2) << endl;
        cout << "3.p3 的输出应该是<NULL>，          实际是：" << (tj_strlwr(p3)==NULL ? "<NULL>":tj_strlwr(p3)) << endl;

        press_key("tj_strlwr() 测试完成");
        }

     if (1) {
        char  s1[]="This is a pencil.";
        char *p2 = NULL;

        cout << "tj_strchr()测试部分：" << endl;
        cout << "1.s1 的输出应该是1，实际是：" << tj_strchr(s1, 'T') << endl;
        cout << "2.s1 的输出应该是3，实际是：" << tj_strchr(s1, 'i') << endl;
        cout << "3.s1 的输出应该是5，实际是：" << tj_strchr(s1, ' ') << endl;
        cout << "4.s1 的输出应该是0，实际是：" << tj_strchr(s1, 'x') << endl;
        cout << "5.p2 的输出应该是0，实际是：" << tj_strchr(p2, 'a') << endl;

        press_key("tj_strchr() 测试完成");
        }

     if (1) {
        char  s1[]="This is a pencil.";
        char  s2[]="aabbbceddbbbceeeff";
        char  s3[]="abcde";
        char *p4 = NULL;

        cout << "tj_strstr()测试部分：" << endl;
        cout << "1.s1 的输出应该是1， 实际是：" << tj_strstr(s1, "T")      << endl;
        cout << "  s1 的输出应该是3， 实际是：" << tj_strstr(s1, "is")     << endl;
        cout << "  s1 的输出应该是11，实际是：" << tj_strstr(s1, "pencil") << endl;
        cout << "  s1 的输出应该是0， 实际是：" << tj_strstr(s1, "Pencil") << endl;
        cout << "2.s2 的输出应该是3， 实际是：" << tj_strstr(s2, "bb")     << endl;
        cout << "  s2 的输出应该是3， 实际是：" << tj_strstr(s2, "bbb")    << endl;
        cout << "  s2 的输出应该是4， 实际是：" << tj_strstr(s2, "bbc")    << endl;
        cout << "  s2 的输出应该是0， 实际是：" << tj_strstr(s2, "bbbb")   << endl;
        cout << "  s2 的输出应该是6， 实际是：" << tj_strstr(s2, "ce")     << endl;
        cout << "  s2 的输出应该是13，实际是：" << tj_strstr(s2, "cee")    << endl;
        cout << "3.s3 的输出应该是1， 实际是：" << tj_strstr(s3, "abcde")  << endl;
        cout << "  s3 的输出应该是0， 实际是：" << tj_strstr(s3, "abcdef") << endl;
        cout << "  s3 的输出应该是0， 实际是：" << tj_strstr(s3, NULL)     << endl;
        cout << "4.p4 的输出应该是0， 实际是：" << tj_strstr(p4, "abc")    << endl;
        cout << "  p4 的输出应该是0， 实际是：" << tj_strstr(p4, NULL)     << endl;

        press_key("tj_strstr() 测试完成");
        }

     if (1) {
        char  s1[]="This is a pencil.";
        char *p2  = NULL;

        cout << "tj_strrchr()测试部分：" << endl;
        cout << "1.s1 的输出应该是1， 实际是：" << tj_strrchr(s1, 'T') << endl;
        cout << "2.s1 的输出应该是15，实际是：" << tj_strrchr(s1, 'i') << endl;
        cout << "3.s1 的输出应该是10，实际是：" << tj_strrchr(s1, ' ') << endl;
        cout << "4.s1 的输出应该是0， 实际是：" << tj_strrchr(s1, 'x') << endl;
        cout << "5.p2 的输出应该是0， 实际是：" << tj_strrchr(p2, 'a') << endl;

        press_key("tj_strrchr() 测试完成");
        }

     if (1) {
        char  s1[]="This is a pencil.";
        char  s2[]="aabbbceddbbbceeeff";
        char  s3[]="abcde";
        char *p4 = NULL;

        cout << "tj_strrstr()测试部分：" << endl;
        cout << "1.s1 的输出应该是1， 实际是：" << tj_strrstr(s1, "T")      << endl;
        cout << "  s1 的输出应该是6， 实际是：" << tj_strrstr(s1, "is")     << endl;
        cout << "  s1 的输出应该是11，实际是：" << tj_strrstr(s1, "pencil") << endl;
        cout << "  s1 的输出应该是0， 实际是：" << tj_strrstr(s1, "Pencil") << endl;
        cout << "2.s2 的输出应该是11，实际是：" << tj_strrstr(s2, "bb")     << endl;
        cout << "  s2 的输出应该是10，实际是：" << tj_strrstr(s2, "bbb")    << endl;
        cout << "  s2 的输出应该是11，实际是：" << tj_strrstr(s2, "bbc")    << endl;
        cout << "  s2 的输出应该是0， 实际是：" << tj_strrstr(s2, "bbbb")   << endl;
        cout << "  s2 的输出应该是13，实际是：" << tj_strrstr(s2, "ce")     << endl;
        cout << "  s2 的输出应该是13，实际是：" << tj_strrstr(s2, "cee")    << endl;
        cout << "3.s3 的输出应该是1， 实际是：" << tj_strrstr(s3, "abcde")  << endl;
        cout << "  s3 的输出应该是0， 实际是：" << tj_strrstr(s3, "abcdef") << endl;
        cout << "  s3 的输出应该是0， 实际是：" << tj_strrstr(s3, NULL)     << endl;
        cout << "4.p4 的输出应该是0， 实际是：" << tj_strrstr(p4, "abc")    << endl;
        cout << "  p4 的输出应该是0， 实际是：" << tj_strrstr(p4, NULL)     << endl;

        press_key("tj_strrstr() 测试完成");
        }

     if (1) {
        char  s1[]="This is a pencil.";
        char  s2[]="aabbbceddbbbceeeff";
        char  s3[]="";
        char *p4 = NULL;

        cout << "tj_strrev()测试部分：" << endl;
        cout << "1.s1 的输出应该是This is a pencil.，  实际是：" << s1 << endl;
        cout << "  s1 的输出应该是.licnep a si sihT，  实际是：" << tj_strrev(s1) << endl;

        cout << "2.s2 的输出应该是aabbbceddbbbceeeff， 实际是：" << s2 << endl;
        cout << "  s2 的输出应该是ffeeecbbbddecbbbaa， 实际是：" << tj_strrev(s2) << endl;

        cout << "3.s3 的输出应该是--， 实际是：-" << s3            << "-" << endl;
        cout << "  s3 的输出应该是--， 实际是：-" << tj_strrev(s3) << "-" << endl;

        cout << "4.p4 的输出应该是<NULL>， 实际是：" << (p4==NULL ? "<NULL>" : p4) << endl;
        cout << "  p4 的输出应该是<NULL>， 实际是：" << (tj_strrev(p4)==NULL ? "<NULL>" : tj_strrev(s3)) << endl;

        press_key("tj_strrev() 测试完成");
        }

    return 0;
}