#include <stdio.h>

using namespace std;

struct Student{             //令结构体Student型记录单个学生的姓名，学号，分数
    char name[15];          
    char id[15];            
    int score;
}temp,score_max,socre_min;  //此处为结构体的名称，temp存放临时输入的数据，score_max存放最高分，score_min存放最低分

int main(){
    int N;
    scanf("%d",&N);
    score_max.score=-1;
    socre_min.score=101;
    for(int i=0;i<N;i++){
        scanf("%s %s %d",&temp.name,&temp.id,&temp.score);
        if(temp.score>score_max.score){
            score_max=temp;
            }
        if(temp.score<socre_min.score){
            socre_min=temp;
        }
    }
    printf("%s %s\n",score_max.name,score_max.id);
    printf("%s %s\n",socre_min.name,socre_min.id);
    return 0;
}