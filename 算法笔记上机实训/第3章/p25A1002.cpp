//多项式相加的题目

#include <stdio.h>

using namespace std;

const int x_max=1010;           
double p[x_max]={0};            //用于存放多项式的x的n次方前的系数

int main(){
    int k,n,count=0;
    double a;
    scanf("%d",&k);             //输入第一行
    for(int i=0;i<k;i++){
        scanf("%d %lf",&n,&a);
        p[n]+=a;
    }
     scanf("%d",&k);            //输入第二行
    for(int i=0;i<k;i++){
        scanf("%d %lf",&n,&a);
        p[n]+=a;
    }
    for(int i=0;i<x_max;i++){
        if(p[i]!=0)
        count++;
    }
    printf("%d",count);
    for(int i=x_max-1;i>=0;i--){
        if(p[i]!=0)
        printf(" %d %.1f",i,p[i]);
    }
    return 0;
}