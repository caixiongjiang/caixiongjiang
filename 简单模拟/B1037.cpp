#include <stdio.h>

using namespace std;

int main(){
    int a1,b1,c1;
    int a2,b2,c2;
    scanf("%d.%d.%d %d.%d.%d",&a1,&b1,&c1,&a2,&b2,&c2);
    //将所有货币换算成最小的单位
    int price=a1*17*29+b1*29+c1;        
    int money=a2*17*29+b2*29+c2;
    int change=money-price;
    if(change<0){
        printf("-");
        change=-change; //取绝对值
    }  
    printf("%d.%d.%d",change/(17*29),change%(17*29)/29,change%29); 
    return 0;
}