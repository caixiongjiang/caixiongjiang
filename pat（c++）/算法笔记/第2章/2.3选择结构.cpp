#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <math.h>

using namespace std;

int main(){
//if语句（略）
//switch语句(分支条件较多时使用)
    int a=1,b=2;
    switch(a+b){
        case2:                              //若a+b的结果为2
            printf("%d\n",a);               
            break;                          //跳出此循环
        case3:                              //若a+b的结果为3
            printf("%d\n",b);
            break;
        case4:                              //若a+b的结果为4
            printf("%d\n",a+b);
            break;
        default:
            printf("sad story\n");          //输出结果：2
    }                                       
    
    getchar();
    system("pause");
    return 0;                         
}