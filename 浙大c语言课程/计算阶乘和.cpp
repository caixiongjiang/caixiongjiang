#include <stdio.h>

int main(){
    int N,sum=0;
    scanf("%d",&N);
    for(int i=1;i<=N;i++){
        int item=1;             //此句
        for(int j=1;j<=i;j++){
            item*=j;
        }
        sum+=item;
    }
    printf("%d",sum);
    return 0;
}