#include <stdio.h>

using namespace std;
//函数的定义
//基本格式：返回类型 函数名称(参数类型 参数){
//          函数主体
//}
void change(int a[],int b[][5]){
    a[0]=1;
    a[1]=3;
    a[2]=5;
    b[0][0]=1;
}

//函数的嵌套调用：是指一个函数中调用另一个函数，调用方式和之前main函数调用其他函数是一样的
int max_2(int a,int b){
    if(a>b) return a;
    else return b;
}

int max_3(int a,int b,int c){
    int temp=max_2(a,b);
    temp=max_2(temp,c);         //函数里调用函数
    return temp;
}

//函数的递归调用
int F(int n){
    if(n==0) return 0;
    else return F(n-1)*n;
}

int main(){
    int a[3]={0};
    int b[5][5]={0};
    change(a,b);
    for(int i=0;i<3;i++){
        printf("%d\n",a[i]);
    }

    int a1,b1,c1;
    scanf("%d%d%d",&a1,&b1,&c1);
    printf("%d\n",max_3(a1,b1,c1));

    int n;
    scanf("%d",&n);
    printf("%d\n",F(n));
    return 0;
}