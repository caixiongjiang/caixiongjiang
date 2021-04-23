#include <stdio.h>

using namespace std;
int a;
int counter=0;

void Callatz(int N){
    if(N==1) return;
    counter++;
    if(N%2==1) Callatz((3*N+1)/2);
    else if(N%2==0) Callatz(N/2); 
}

int main(){
    scanf("%d",&a);
    Callatz(a);
    printf("%d",counter);
    return 0; 
}