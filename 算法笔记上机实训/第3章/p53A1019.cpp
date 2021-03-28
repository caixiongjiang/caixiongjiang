#include <stdio.h>

using namespace std;

bool judge(int z[],int num){
    for(int i=0;i<=num/2;i++){
        if(z[i]!=z[num-1-i]){
            return false;
        }
    }
    return true;
}

int main(){
    int N,b;
    int z[40],num=0;        //z[40]存放转化结果，num保存其位数
    scanf("%d %d",&N,&b);
    do{
        z[num++]=N%b;
        N/=b;
    }while(N!=0);
    bool flag=judge(z,num);
    if(flag==true) printf("Yes\n");
    else printf("No\n");
    for(int i=num-1;i>=0;i--){
        printf("%d",z[i]);
        if(i!=0) printf(" ");
    }
    return 0;
}