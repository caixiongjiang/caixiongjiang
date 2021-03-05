#include <stdio.h>

using namespace std;

int main(){
    int C1,C2;              //C1和C2为打点数
    scanf("%d%d",&C1,&C2);
    int deta=C2-C1;
    if(deta%100>=50){
        deta=deta/100+1;
    }else{
        deta=deta/100;
    }
    printf("%02d:%02d:%02d",deta/3600,deta%3600/60,deta%60);
    return 0;
}