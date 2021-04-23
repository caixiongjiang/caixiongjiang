//内存限制为64MB=16777216B
#include <stdio.h>
#include <queue>

using namespace std;

int Brain[1300][130][61];           //一个数组元素为4B，总共需要10309000B
int total_number=0;
int M,N,L,T;
bool visited[1300][130][61]={false};//用于标记已经访问过的节点数组，此处不能用int数组，否则会超过内存限制
struct node{
   int x,y,z;                       //代表节点的位置 
}Node;

bool judge(int x,int y,int z){
    if(x<0||x>=M) return false;
    if(y<0||y>=N) return false;
    if(z<0||z>=L) return false;
    if(visited[x][y][z]==true) return false;
    if(Brain[x][y][z]==0) return false;
    return true;
}
int BFS(int x,int y,int z){
    queue<node> Q;
    int number=0;
    Node.x=x;
    Node.y=y;
    Node.z=z;
    Q.push(Node);
    visited[x][y][z]=true;             //代表三维数组中的点已经访问过
//BFS模板
    while(!Q.empty()){
        node temp=Q.front();        //将队列的第一个元素赋值给temp变量
        Q.pop();
        number++;                   //每一轮入队一个节点就number就+1
        if(judge(temp.x+1,temp.y,temp.z)){         //判断该节点之前是否已经入队
            Node.x=temp.x+1;
            Node.y=temp.y;
            Node.z=temp.z;
            Q.push(Node);
            visited[Node.x][Node.y][Node.z]=true;
        }
        if(judge(temp.x-1,temp.y,temp.z)){
            Node.x=temp.x-1;
            Node.y=temp.y;
            Node.z=temp.z;
            Q.push(Node);
            visited[Node.x][Node.y][Node.z]=true;
        }
        if(judge(temp.x,temp.y+1,temp.z)){ 
            Node.x=temp.x;
            Node.y=temp.y+1;
            Node.z=temp.z;
            Q.push(Node);
            visited[Node.x][Node.y][Node.z]=true;
        }
        if(judge(temp.x,temp.y-1,temp.z)){ 
            Node.x=temp.x;
            Node.y=temp.y-1;
            Node.z=temp.z;
            Q.push(Node);
            visited[Node.x][Node.y][Node.z]=true;
        }
        if(judge(temp.x,temp.y,temp.z+1)){ 
            Node.x=temp.x;
            Node.y=temp.y;
            Node.z=temp.z+1;
            Q.push(Node);
            visited[Node.x][Node.y][Node.z]=true;
        }
        if(judge(temp.x,temp.y,temp.z-1)){ 
            Node.x=temp.x;
            Node.y=temp.y;
            Node.z=temp.z-1;
            Q.push(Node);
            visited[Node.x][Node.y][Node.z]=true;
        }
    }
    return number;
}

int main(){
    scanf("%d%d%d%d",&M,&N,&L,&T);
    for(int i=0;i<L;i++){
        for(int j=0;j<M;j++){
            for(int k=0;k<N;k++){
                scanf("%d",&Brain[j][k][i]);
            }
        }
    }
    for(int i=0;i<L;i++){
        for(int j=0;j<M;j++){
            for(int k=0;k<N;k++){
                if (Brain[j][k][i]!=0&&visited[j][k][i]!=true){
                    int num=BFS(j,k,i);
                    if(num>=T) total_number+=num;
                }
            }
        }
    }
    printf("%d",total_number);
    return 0;
}