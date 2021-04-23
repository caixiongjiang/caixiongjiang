#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <math.h>

using namespace std;

int main(){

//while循环语句
    int n=1,sum=0;
    while(n<=100){
        sum=sum+n;
        n++;
    }
    printf("sum=%d\n",sum);             //输出结果为sum=5050

//注：若表达式为!=0,则可以省略
//   若表达式为==0，则可以省略，并且在表达式前添加非运算符！
    int m=12345,count=0;
    while(m){                           //相当于while(n!=0)
        count=count+m%10;
        m=m/10;
    }
    printf("%d\n",count);               //输出结果：15

//do...while语句
    int n1=1,sum1=0;
    do{                                 //注：do...while语句会先执行循环体一次，然后才会判断条件是否为真
        sum1=sum1+n1;
        n1++;
    }while(n1<=100);
    printf("sum=%d\n",sum1);            //输出结果：sum=5050

//for循环(略)

//break和continue语句
    int n2,sum2=0;
    for(int i=1;i<=100;i++){
        sum2=sum2+i;
        if(sum2>=2000) break;           //如果sum2的结果大于2000则跳出循环
    }
    printf("sum=%d\n",sum2);            //输出结果：sum=2016

    int sum3=0;
    for(int i=1;i<=5;i++){
        if(i%2==1) continue;            //如果i为奇数，则不执行直接进入下一轮循环
        sum3=sum3+i;
    }
    printf("sum=%d\n",sum3);            //输出结果：sum=6

    getchar();
    system("pause");        
    return 0;                            
}