#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <math.h>

using namespace std;

const double pi=acos(-1.0);             //此处将pi定义为精确acos(-1.0)，因为cos(pi)=-1
typedef long long LL;                   //给long long起个别名LL

int main(){
    int n=12,m=3;
    n/=m+1;//赋值的优先级最低
    m%=2;
    printf("%d %d\n",n,m);
   
    char str[10];
    scanf("%s",str);                    //输入数据：abcd efg 输出结果：abcd
    printf("%s",str);                   //注：scanf对除%c以外的其他格式符的输入以空白符为结束判断标志（TAB/空格）
                                        //字符数组使用%s读入的时候以空格和换行为读入结束的标注。
    int a;
    char c,str1[10];
    scanf("%d%c%s",&a,&c,str1);
    printf("a=%d,c=%c,str=%s",a,c,str); //输入数据：1 a bcd 输出结果：a=1,c= ,str=a
                                        //%c格式可以读入空格
                                        //对于double类型的变量，printf中为%f,scanf中为%lf;而float都为%f。
    printf("%%");                       //输出%
    printf("//");                       //输出/

    int a1=123,b1=1234567;              //%md可以使不足m位进行右对齐输出，高位用空格补齐。
    printf("%5d\n",a1);                 //输出结果：  123
    printf("%5d\n",b1);                 //        1234567
    printf("%05d\n",a1);                //%0md可以使不足m位进行右对齐输出，高位用0补齐。
    printf("%05d\n",b1);                //输出结果：00123
                                        //         1234567  
    double d1=12.3456;                  //%.mf可以让浮点数保留m位小数输出，规则为"四舍六入五成双"
    printf("%.0f\n",d1);                //输出结果：12            若是四舍五入需要用到round函数
    printf("%.1f\n",d1);                //         12.3
    printf("%.2f\n",d1);                //         12.35
    printf("%.3f\n",d1);                //         12.346
    printf("%.4f\n",d1);                //         12.3456
    
    char c1,c2,c3;                      //getchar用来输入单个字符，putchar用来输出单个字符（scanf函数使用不便）
    c1=getchar();                       //第一个字符被c1接受
    getchar();                          //第二个字符虽然被接受但没有存储在变量中
    c2=getchar();                       //第三个字符被c2接受
    c3=getchar();                       //第四个字符被c3接受
    putchar(c1);                        //输入数据：abcd
    putchar(c2);                        //输出结果：acd
    putchar(c3);                        //getchar可以识别换行符，若输入ab按enter再输入c得到的结果为ac

    LL a2=123456789012345,b2=234567890123456;
    printf("%lld\n",a2+b2);             //使用长整型的简写LL,输出结果：358024679135801

    //取绝对值
    double db=-12.56;
    printf("%.2f\n",fabs(db));          //fabs(double x)用于对double型变量取绝对值

    double db1=-5.2,db2=5.2;
    printf("%.0f %.0f\n",floor(db1),ceil(db1));//floor(double x)用于double型变量向下取整
    printf("%.0f %.0f\n",floor(db2),ceil(db2));//ceil（double x）用于double型变量向上取整
                                               //输出结果：-6 -5
                                               //         5 6
                                        
    double db3=pow(2.0,3.0);            //该函数用于返回r的p次方（要求r和p都为double型）
    printf("%f\n",db3);                 //输出结果：8.000000

    double db4=sqrt(2.0);               //该函数用于返回double型变量的算术平方根
    printf("%f\n",db4);                 //输出结果：1.414214

    double db5=log(1.0);                //返回以自然对数为底的对数，输出结果为0.000000
    printf("%f\n",db5);                 //c语言中没有对任意底数求对数的函数，即loga^b=loge^b/loge^a

    double db6=sin(pi*45/180);          //返回double类型的sin，cos，tan值，反三角函数则用asin，acos，atan；
    double db7=cos(pi*45/180);
    double db8=tan(pi*45/180);
    printf("%f,%f,%f\n",db6,db7,db8);

    double db9=round(3.45);             //使用round对double型变量进行四舍五入
    double db10=round(3.50);
    printf("%d,%d\n",int(db9),int(db10));

    getchar();                        
    system("pause");
    return 0;                         
}
