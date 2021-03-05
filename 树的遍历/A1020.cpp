//已知后序，中序，求先序，然后用层序遍历输出
#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn=50;
struct TreeNode{
    int data;
    TreeNode* lchild;
    TreeNode* rchild;
};
int post[maxn],in[maxn];//后序，中序
int n;                  //节点个数

TreeNode*buildTree(int postL,int postR,int inL,int inR){
    if(inL>inR){                //确定的递归的边界
        return NULL;
    }
    TreeNode*root=new TreeNode;     //新建一个节点，用于存放二叉树的根节点
    int root_key=post[postR];
    root->data=root_key;
    int k;
    for(k=inL;k <= inR; k++){
        if(in[k]==root_key){
            break;
        }
    }
        int leftn=k-inL;
        root->lchild=buildTree(postL,postL+leftn-1,inL,k-1);//根据算法笔记p296页的图确定参数
        root->rchild=buildTree(postL+leftn,postR-1,k+1,inR);//递归调用建立二叉树
        return root;                //返回根节点
}

int num=0;
void layerTraverals(TreeNode*T){  //层序遍历
    queue<TreeNode*> Q;           //注意队列里存的是树的地址
    Q.push(T);
    while(!Q.empty()){
        TreeNode* now=Q.front();
        Q.pop();
        printf("%d",now->data);
        num++;
        if(num<n) printf(" ");
        if(now->lchild!=NULL) Q.push(now->lchild);
        if(now->rchild!=NULL) Q.push(now->rchild);
    }
}
int main(){
//读取数据
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&post[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&in[i]);
    }
//建树过程
    TreeNode*T=buildTree(0,n-1,0,n-1);
//层序遍历
    layerTraverals(T);
    getchar();
    system("pause");
    return 0;
}