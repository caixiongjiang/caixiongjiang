#include <stdio.h>

using namespace std;
int flag=1;

int main() {
    int N,A1=0,A2=0,A3=0,A4=0,A5=0,temp,counter[5]={0};
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&temp);
        if(temp%5==0&&temp%2==0){
            A1=A1+temp;
            counter[0]++;
        }
        if(temp%5==1){
            counter[1]++;
            A2=A2+flag*temp;
            flag=flag*-1;
        }
        if(temp%5==2){
            counter[2]++;
        }
        A3=counter[2];
        if(temp%5==3){ 
            counter[3]++;
            A4=A4+temp;
        }
        if(temp%5==4&&temp>A5){
            A5=temp;
            counter[4]++;
        }
    }
    if(counter[0]==0) printf("N ");
    else printf("%d ",A1);
    if(counter[1]==0) printf("N ");
    else printf("%d ",A2);
    if(counter[2]==0) printf("N ");
    else printf("%d ",A3);
    if(counter[3]==0) printf("N ");
    else printf("%.1f ",((double)A4)/counter[3]);
    if(counter[4]==0) printf("N");
    else printf("%d",A5);
	return 0;
}