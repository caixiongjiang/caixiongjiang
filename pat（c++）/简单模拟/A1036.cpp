#include <stdio.h>

using namespace std;

struct Student{
    char name[15];
    char id[15];
    int grade;
}male,female,temp;  //记录男性，女性和临时输入的变量

int main(){
    int N;
    char gender;
    male.grade=101;     //初始化男生最低分数为101
    female.grade=-1;    //初始化女生的最低分数为-1
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%s %c %s %d",&temp.name,&gender,&temp.id,&temp.grade);
        if(gender=='M' && temp.grade<male.grade){
            male=temp;
        }else if(gender=='F' && temp.grade>female.grade){
            female=temp;
        }
    }
    if(female.grade==-1){
        printf("Absent\n");
    }else{
        printf("%s %s\n",female.name,female.id);
    }
    if(male.grade==101){
        printf("Absent\n");
    }else{
        printf("%s %s\n",male.name,male.id);
    }
    if(female.grade==-1||male.grade==101){
        printf("NA");
    }else{
        printf("%d\n",female.grade-male.grade);
    }
    return 0;
}