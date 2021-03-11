#include<stdio.h> 
int main()
{
	int N,count = 0;
	int fib,fib1 = 1,fib2 = 1;
	scanf("%d", &N);
	if(N<1 )
	    printf("Invalid.");
	    else if(N == 1){       //考虑特殊情况n = 1时只输出第一项
		     printf("%11d",fib1);
        }
		else{
		     printf("%11d%11d",fib1,fib2);
	         count = 2;   //已经输出了前两项，计数初始化为1
        for(int i=3;i<=N;i++){
            fib=fib1+fib2;
            fib1=fib2;
            fib2=fib;
            printf("%11d",fib);
            count++;
            if(count%5==0){
                printf("\n");
            }
        }
        if(count<5){
            printf("\n");
        }
	}
}