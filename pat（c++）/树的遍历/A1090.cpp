#include <stdio.h>
#include <vector>              //n叉树一般用vector数组来保存孩子节点
#include <math.h>

using namespace std;

const int maxn=100001;          //const代表不能修改的常量
double unit_price,rate;
double max_price=-1;
int counter=0;

struct TreeNode{
    int data;
    vector<int> child;
}static_tree[maxn];

void dfs(int depth,int index){
    if(static_tree[index].child.empty()){
        double cur_price=unit_price*pow((1+rate),depth);
        if(cur_price>max_price){            //如果当前价格大于之前定义的最大价格，则更新最大价格的值
            max_price=cur_price;
            counter=1;                      //最大价格的个数重新变为1
        }
        else if(cur_price==max_price){
            counter++; //如果当前价格等于最高价格，最大价格数量+1
        }return;
    }
    for(int i=0;i<static_tree[index].child.size();i++){
        dfs(depth+1,static_tree[index].child[i]);
    }
}

int main(){
    int N,father,root;
    scanf("%d%lf%lf",&N,&unit_price,&rate);
    rate=rate/100;
    for(int i=0;i<N;i++){
        scanf("%d",&father);
        if(father!=-1){
            static_tree[father].child.push_back(i);
        }else{
            root=i;
        }
    }
    dfs(0,root);
    printf("%.2f %d",max_price,counter);
    system("pause");
    return 0;
}