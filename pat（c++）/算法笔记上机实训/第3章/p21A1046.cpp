#include <stdio.h>
#include <vector>

using namespace std;

int dis[100005];                             
int mySum(int r1,int r2){
    return dis[r2]-dis[r1];
}

// 1 2 4 14 9     [input]数组
// 0 1 3 7 21 30  [dis]数组
int main(){
    int n,temp,m,round1,round2,t;
    vector<int> input;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&temp);
        input.push_back(temp);
    }
    dis[1]=input[0];
    for(int i=2;i<=n;i++){
        dis[i]=dis[i-1]+input[i-1];
    }
    scanf("%d",&m);
    int total_sum=mySum(0,n);
    for(int i=0;i<m;i++){
        scanf("%d%d",&round1,&round2);
        if(round1>round2) swap(round1,round2);
        round1--;
        round2--;
        int my_sum1=mySum(round1,round2);
        int my_sum2=total_sum-my_sum1;
        if(my_sum1>my_sum2) printf("%d\n",my_sum2);
        else printf("%d\n",my_sum1);
    }
    return 0;
}
