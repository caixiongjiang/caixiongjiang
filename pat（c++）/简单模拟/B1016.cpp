#include <stdio.h>

using namespace std;

int main(){
    long long A,Da,B,Db;
    long long Pa=0,Pb=0;
    scanf("%lld%lld%lld%lld",&A,&Da,&B,&Db);
    while(A){
        if(A%10==Da) Pa=Pa*10+Da;
        A /= 10;
    }
    while(B){
        if(B%10==Db) Pb=Pb*10+Db;
        B /= 10;
    }
    printf("%lld",Pa+Pb);
    return 0;
}