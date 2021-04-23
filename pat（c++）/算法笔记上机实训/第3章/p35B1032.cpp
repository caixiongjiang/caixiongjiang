#include <stdio.h>
#include <math.h>           


using namespace std;
const int maxn=100001;
int school[maxn]={0};
int Max=-1,Max_id;

int main(){
    int N,school_id,score;
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d%d",&school_id,&score);
        school[school_id]+=score;
    }
    for(int i=1;i<=N;i++){
        if(school[i]>Max){
        Max=school[i];
        Max_id=i;
        }
    }
    printf("%d %d\n",Max_id,Max);
    return 0;
}