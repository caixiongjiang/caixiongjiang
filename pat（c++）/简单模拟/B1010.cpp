#include <stdio.h>

using namespace std;

int main(){
    int a,b;
    int count=0;                                //记录有多少个求导后的非零项
    while(scanf("%d %d", &a, &b) != EOF){       //输入系数和指数直到文件末尾
        if(a!=0&&b!=0){
            if(count!=0) printf(" ");           //除了开头输出中间都用空格分开
            printf("%d ",a*b);                  //系数后要加一个空格
            printf("%d",b-1);
            count++;
        }
    }
    if(count==0) printf("0 0");
    return 0;
}
