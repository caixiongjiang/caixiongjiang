#include <stdio.h>

using namespace std;

int main() {
    int N;
    char c1,c2;
    char BCJ[3]={'B','C','J'};              //记录石头剪刀布
    int win_A[3]={0},win_B[3]={0};          //分别记录甲乙靠石头剪刀布赢的次数
    int times_A[3]={0},times_B[3]={0};      //分别记录甲乙胜平负的次数
    scanf("%d\n",&N);
    for(int i=0;i<N;i++){
        scanf("%c %c\n",&c1,&c2);
        if(c1==c2){
            times_A[1]++;
            times_B[1]++;
        }
        if(c1=='B'&&c2=='J'){
            times_B[0]++;
            times_A[2]++;
            win_B[2]++;
        }
        if(c1=='B'&&c2=='C'){
            times_A[0]++;
            times_B[2]++;
            win_A[0]++;
        }
        if(c1=='C'&&c2=='B'){
            times_A[2]++;
            times_B[0]++;
            win_B[0]++;
        }
        if(c1=='C'&&c2=='J'){
            times_A[0]++;
            times_B[2]++;
            win_A[1]++;
        }
        if(c1=='J'&&c2=='C'){
            times_A[2]++;
            times_B[0]++;
            win_B[1]++;
        }
        if(c1=='J'&&c2=='B'){
            times_A[0]++;
            times_B[2]++;
            win_A[2]++;
        }
    }
    printf("%d %d %d\n",times_A[0],times_A[1],times_A[2]);
    printf("%d %d %d\n",times_B[0],times_B[1],times_B[2]);
    int id1=0,id2=0;
    for(int i=0;i<3;i++){
        if(win_A[i]>win_A[id1]) id1=i;
        if(win_B[i]>win_B[id2]) id2=i;
    }
    printf("%c %c",BCJ[id1],BCJ[id2]);
	return 0;
}