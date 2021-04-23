#include <stdio.h>
#include <math.h>


using namespace std;

int main(){
    int N=10,n;
    char c;
    scanf("%d %c",&N,&c);
    n=round(N/2.0);         //除以2.0是为了N/2的结果保持一位小数
    for(int i=0;i<N;i++){
        printf("%c",c);
    }
    printf("\n");           //换行
    for(int i=0;i<n-2;i++){
        for(int j=0;j<N;j++){
            if (j==0||j==N-1) printf("%c",c);
            else printf(" ");
            }
        printf("\n");
    }
    for(int i=0;i<N;i++){
        printf("%c",c);
    }
    return 0;
}