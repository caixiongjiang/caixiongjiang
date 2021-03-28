#include <stdio.h>

using namespace std;

char radix[13]={'0','1','2','3','4','5','6','7','8','9','A','B','C'};

int main(){
    int red,green,blue;
    scanf("%d %d %d",&red,&green,&blue);
    printf("#");
    printf("%c%c",radix[red/13],radix[red%13]);
    printf("%c%c",radix[green/13],radix[green%13]);
    printf("%c%c",radix[blue/13],radix[blue%13]);
    return 0;
}