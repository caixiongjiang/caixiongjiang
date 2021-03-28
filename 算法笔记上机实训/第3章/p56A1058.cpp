#include <stdio.h>

using namespace std;

int main(){
    long long a1,b1,c1;
    long long a2,b2,c2;
    scanf("%lld.%lld.%lld %lld.%lld.%lld",&a1,&b1,&c1,&a2,&b2,&c2);
    long long money1=a1*17*29+b1*29+c1;
    long long money2=a2*17*29+b2*29+c2;
    long long all_money=money1+money2;
    printf("%lld.%lld.%lld",all_money/(17*29),all_money%(17*29)/29,all_money%29);
    return 0;
}