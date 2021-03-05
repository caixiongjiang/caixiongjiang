#include <stdio.h>

using namespace std;

const int n=54;
char str[5]={'S','H','C','D','J'};

int main(){
    int N;
    int start[55]={0},order[55]={0},end[55]={0};
    scanf("%d",&N);
    for(int i=1;i<=n;i++){              //初始化牌的编号
        start[i]=i;
    }
    for(int i=1;i<=n;i++){              //输入每个位置上的牌在操作后的位置
        scanf("%d",&order[i]);
    }
    for(int i=0;i<N;i++){
        for(int j=1;j<=n;j++){
            end[order[j]]=start[j];
        }
        for(int i=1;i<=n;i++){
            start[i]=end[i];
        }
    }
    for(int i=1;i<=n;i++){
        start[i]--;
        printf("%c%d",str[start[i]/13],start[i]%13+1);
        if(i<54)    printf(" ");
    }
    return 0;
}