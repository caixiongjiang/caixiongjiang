#include <stdio.h>

using namespace std;

int main(){
    int x,mask=1;
    scanf("%d",&x);
    int t=x;
    while(t>9){             
        t/=10;
        mask*=10;
    }
    printf("x=%d,mask=%d\n",x,mask);
    do{
        int d=x/mask;
        printf("%d",d);
        if(mask>9){
            printf(" ");    
        }
        x%=mask;
        mask/=10;
    }while(mask>0);
    printf("\n");
    return 0;
}