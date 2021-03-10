#include<stdio.h>
int main()
{
 int count=0,count1=0,flag = 1;
 double average=0,sum=0,num=0;
 
 while(1){ 
        scanf("%lf",&num);
        if(num<0){ 
        if(count>0)   flag = 1;
        else if(count == 0 )  flag = 0;  //第一个成绩为负数，count==0
        break;
        }else{
            flag = 1;
            sum+=num;
            count++;  
            average = sum*1.0/count;
            if(num<60)
            count1++;
        }
    }  

    if(flag == 0)                        //用于判断在输入结束前的大于0的分数个数是否大于0，若大于0，flag==1；
    {
     printf("Average = 0.00");
    }else if(flag == 1){
    printf("Average = %.2lf\n",average);
    printf("Count = %d",count1);
 }
  return 0;
 }