#include <stdio.h>
int main(){
    int flag=1; //用于标记是否为素数
    int num=0;  // 输入的整数
    printf("输入一个整数：");
    scanf("%d",&num);
    for(int i=2;i<num;i++){
        if(num%i==0){
            flag=0;  // 素数个数加1
            break;   //若已经判断为素数就跳出循环
        }
    }
    if(flag==1){
        printf("%d是素数。\n", num);
    }else{
        printf("%d不是素数。\n", num);
    }
    return 0;
}