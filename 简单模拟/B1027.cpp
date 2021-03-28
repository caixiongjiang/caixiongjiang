#include <stdio.h>
#include <math.h>
 
using namespace std;

int main(){
    int N;
    char c;
    scanf("%d %c",&N,&c);
    int bottom=(int)sqrt(2.0*(N+1))-1;      //三角形底边所拥有的的字符数
    if(bottom%2==0){
        bottom--;
    }
    int used=(bottom+1)*(bottom+1)/2-1;     //总共输出的非空格数
    //输出倒三角
    for(int i=bottom;i>=1;i-=2){
        for(int j=0;j<(bottom-i)/2;j++){
            printf(" ");                    //空格个数为(bottom-i)/2
        }
        for(int j=0;j<i;j++){
            printf("%c",c);
        }
        printf("\n");
    }
    //输出正三角
    for(int i=3;i<=bottom;i+=2){
        for(int j=0;j<(bottom-i)/2;j++){
            printf(" ");
        }
        for(int j=0;j<i;j++){
            printf("%c",c);
        }
        printf("\n");
    }
    printf("%d\n",N-used);
    return 0;
}