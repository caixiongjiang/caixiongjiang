#include <stdio.h>

using namespace std;

const int maxn=1010;

struct Student{                 //将考生的准考证号，试机座位号和考试座位号放在同一个数组中
    long long examNum;
    int examSeat;
}testSeat[maxn];                //以试机座位号作为下标来记录考生

int main(){
    int N,n;
    long long examNum;  //准考证号
    int seat,examSeat;  //试机座位号和考试座位号
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%lld %d %d",&examNum,&seat,&examSeat);
        testSeat[seat].examNum=examNum;
        testSeat[seat].examSeat=examSeat;
    }
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&seat);
        printf("%lld %d\n",testSeat[seat].examNum,testSeat[seat].examSeat);
    }
    return 0;
}