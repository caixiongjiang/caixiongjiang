#include <stdio.h>

using namespace std;

int main(){
    int A,B,D,ans[31];
    scanf("%d %d %d",&A,&B,&D);
    int sum=A+B,num=0;
    //进制转换
    do{
        ans[num++]=sum%D;
        sum=sum/D;
    }while(sum!=0);
    for(int i=num-1;i>=0;i--){
        printf("%d",ans[i]);
    }
    return 0;
}