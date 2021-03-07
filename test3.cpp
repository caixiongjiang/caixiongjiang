//多项式相乘
#include <stdio.h>

using namespace std;

const int max1=1010;
const int max2=2020;
double a1[max1]={};
double a2[max1]={};           //用于存放x的n次的系数
double b[max2]={};            //用于存放两个多项式相乘后结果的x的n次的系数

int main(){
    int K,n,count=0;
    double x;
    scanf("%d",&K);          //读入第一行数据
    for(int i=0;i<K;i++){
        scanf("%d%lf",&n,&x);
        a1[n]=x;
    }
    
    scanf("%d",&K);          //读入第二行数据
    for(int i=0;i<K;i++){
        scanf("%d%lf",&n,&x);
        a2[n]=x;
        for(int j=0;j<K;j++){
            b[n+j]+=a2[n]*a1[j];
        }
    }
    for(int i=0;i<=max2;i++){
        if(b[i]!=0){
            count++;
        }
    }
    printf("%d",count);
    for(int i=max2;i>0;i--){
        if(b[i]!=0){
        printf(" %d %.1f",i,b[i]);
        }
    }
    return 0;
}