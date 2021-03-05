#include <stdio.h>

using namespace std;

int main(){
    int N,A_han,A_hua,B_han,B_hua,A_drink=0,B_drink=0;
    scanf("%d",&N);
    while(N--){
        scanf("%d%d%d%d",&A_han,&A_hua,&B_han,&B_hua);
        if(A_han+B_han==A_hua&&A_han+B_han!=B_hua) B_drink++;
        if(A_han+B_han==B_hua&&A_han+B_han!=A_hua) A_drink++;
    }
    printf("%d %d",A_drink,B_drink);
    return 0;
}