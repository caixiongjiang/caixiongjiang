#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;
const int maxn=100001;
double total_sale=0;
double unit_price,rate;

struct TreeNode{
    double data;
    vector<int> child;                //将子节点存入数组
}static_tree[maxn];

void dfs(int depth,int index){        //depth代表深度，index代表数组下标
    if(static_tree[index].child.empty()){   //如果为叶子节点，则计算它的价格总和
        total_sale+=
        (static_tree[index].data*pow(1+rate,depth)*unit_price);
    }
    for(int i=0;i<static_tree[index].child.size();i++){
        dfs(depth+1,static_tree[index].child[i]);//递归访问子节点，static_tree[index].child[i]代表
    }                                            //该节点的第i个儿子
}


int main(){
    int N,k,temp;                                   //N代表总节点数，k代表子节点数，temp为临时变量
    scanf("%d%lf%lf",&N,&unit_price,&rate);
    rate=rate/100;
    for(int i=0;i<N;i++){
        scanf("%d",&k);
        if(k==0){                                 //如果k==0，代表零售商，此时的temp
            scanf("%d",&temp);                    //代表零售商卖商品的数量
            static_tree[i].data=temp;
        }
        else{                                     //如果k不为0，代表经销商，此时的temp代表子节点的下标
            for(int j=0;j<k;j++){
                scanf("%d",&temp);
                static_tree[i].child.push_back(temp);
            }
        }

    }
//遍历n叉树,算出价格总额
    dfs(0,0);
//输出结果
    printf("%.1f\n",total_sale);
    getchar();
    system("pause");
    return 0;
}