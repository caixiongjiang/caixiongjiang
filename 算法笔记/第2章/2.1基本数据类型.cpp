#include <stdlib.h>
#include<stdio.h>//（头文件）/与输入输出有关
#define pi 3.14     //使用一个标识符来定义常量，末尾不加分号
	//在执行程序前所有pi都变成3.14
const double pi1 = 3.14;
#define ADD(a,b) ((a)+(b))
#define CAL(x) (x*2+1)
const int INF = (1 << 30) - 1;//用INF代表无穷大的数
//或用 const int INF=0x3fffffff;

using namespace std;

int main() {			//主函数：程序的入口位置，一个程序只能有一个
	double a = 3.14, b = 0.12;
	double c = a + b;
	printf("%f",c);
	
	char	c1 = 'z', c2 = 'j', c3 = 117;//117为u的ASCLL码
	printf("%c%c%c", c1, c2, c3);

	int num1 = 1, num2 = 2;
	printf("%d\n\n%d",num1,num2);
	printf("%c", 7);//7为控制电脑响铃的ASCLL码
	char	str1[25] = "wo ai de ren bu ai wo";
	char str2[25] = "so sad a story it is.";
	printf("%s,%s", str1, str2);//字符串常量可作为初值赋给字符数组/[注]：不能将字符串常量赋值给字符变量，如
											//char c="abcd";
	bool	flag1 = 0, flag2 = true;//c++中可以直接使用布尔类型，否则要加#include <stdbool.h>
	int e = 1, d = 1;
	printf("%d %d %d\n", flag1, flag2, e==d);
	
	double r = 12.56;
	int a1= 3, b1= 5;
	printf("%d\n", (int)r);//使用括号进行强制类型转换
	printf("%d\n", a1/ b1);
	printf("%.1f", (double)a1/ (double)b1);//保留1位小数

	double r1 = 3;
	printf("%f\n", pi * r1 * r1);

	double r2 = 3;
	printf("%f\n", 2 * pi * r2);

	int num3 = 3, num4 = 5;
	printf("%d", ADD(num3, num4));//使用预先定义的ADD语句

	int a2= 1;
	printf("%d\n", CAL(a2 + 1));//结果为4，不是5（宏陷阱）；CAL（a1+1）实际上是CAL(a+1*2+1),少加一个括号
	
	int a3 = 3, b3 = 4;
	double c4 = 1.23, d4= 0.24;
	printf("%d %d\n", a3 + b3, a3 - b3);
	printf("%f\n", c4 * d4);

	int a5 = 5, b5 = 4, c5 = 5, d5 = 6;
	printf("%d %d %d\n", a5 / b5, a5 / c5, a5 / d5);
	//当除数和被除数都是整型时，只会得到整型（取整数部分），不会是double型

	//自增运算符：i++是先使用i再将i加1，而++i则是先将i加1再使用i
	int a6 = 1, b6 = 1, n1, n2;
	n1 = a6++;
	n2 = ++b6;
	printf("%d %d\n", n1, a6);//输出结果为  1 2
	printf("%d %d\n", n2, b6);//					2 2

	//条件运算符
	int a7 = 3, b7 = 5;
	int c7 = a7 > b7 ? 7 : 11;
	printf("%d\n", c7);
	getchar();
    system("pause");
	return 0;
}