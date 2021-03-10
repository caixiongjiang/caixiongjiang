//人口普查
#include <stdio.h>

using namespace std;

struct Person{
    char name[10];      //名字的字符串不超过5个英文字符
    int year,month,day;
}oldest,youngest,left,right,temp;   //oldest存放最大年龄，youngest存放最小年龄，left和right存放合法的出生日期边界，temp用于临时存放

bool Older(Person a,Person b){    //如果a的日期小于等于b，返回true
   if(a.year!=b.year){
        return a.year<=b.year;
   }
   else if(a.month!=b.month){
       return a.month<=b.month;
   } 
   else{
       return a.day<=b.day;  
   }
}

bool Younger(Person a,Person b){      //如果a的日期大于b的日期，返回true
    if(a.year!=b.year){
        return a.year>=b.year;
   }
   else if(a.month!=b.month){
       return a.month>=b.month;
   } 
   else{
       return a.day>=b.day;  
   }
}
//上述两个函数用于判断输入的日期是否合法和比较日期大小
int main(){
    youngest.year=left.year=1814;
    oldest.year=right.year=2014;
    youngest.month=oldest.month=left.month=right.month=9;
    youngest.day=oldest.day=left.day=right.day=6;           //今天的日期是2014年9月16日
    int N,num=0;
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%s %d/%d/%d",&temp.name,&temp.year,&temp.month,&temp.day);
        if(Older(temp,right)&&Younger(temp,left)){
            num++;
            if(Older(temp,oldest)){
                oldest=temp;
            }
            if(Younger(temp,youngest)){
                youngest=temp;
            }
        }
    }
    if(num==0){
        printf("0\n");
    }
    else {
        printf("%d %s %s",num,oldest.name,youngest.name);
    }
    return 0;
}