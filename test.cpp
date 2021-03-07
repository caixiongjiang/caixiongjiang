#include <stdio.h>
using namespace std;

int main(){
    double number1,number2,result;
    char op1;
    scanf("%lf%c%lf",&number1,&op1,&number2);
    if(op1=='+'){
        result=number1+number2;
        printf("%.2f",result);
    }else if(op1=='-'){
        result=number1-number2;
        printf("%.2f",result);
    }else if(op1=='*'){
        result=number1*number2;
        printf("%.2f",result);
    }else if(op1=='/'){
        if(number2==0){
            printf("Divisor can not be 0!");   
        }else{
            result=number1/number2;
            printf("%.2f",result);
        }
    }else{
        printf("Unknown operator!");
    }
    return 0;
}