#include <stdio.h>
#include <cstring>

using namespace std;

int main(){
    char str[90];
    scanf("%s",str);
    int len=strlen(str);
    int n1=(len+2)/3;
    int n3=n1;
    int n2=len+2-n1-n3;
    for(int i=0;i<n1-1;i++){            //输出左边n-1行
        printf("%c",str[i]);
        for(int j=0;j<n2-2;j++){
            printf(" ");
        }
        printf("%c\n",str[len-i-1]);
    }
    for(int i=0;i<n2;i++){
        printf("%c",str[n1+i-1]);
    }
    return 0;
}