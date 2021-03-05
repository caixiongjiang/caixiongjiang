//数组循环右移M位
#include <stdio.h>

using namespace std;

void move(int N,int A[]){
    int temp;
    temp=A[N-1];
    for(int i=N-1;i>0;i--){
    A[i]=A[i-1];
    }
    A[0]=temp;
}
int main(){
    int N,M;
    int A[110]={0};
    scanf("%d%d",&N,&M);
    for(int i=0;i<N;i++){
        scanf("%d",&A[i]);
    }
    for(int i=0;i<M;i++){
        move(N,A);
    }
    for(int i=0;i<N;i++){
        printf("%d",A[i]);
        if(i<N-1) printf(" ");
    }
    return 0;
}