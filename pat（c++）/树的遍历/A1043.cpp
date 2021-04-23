//二叉搜索树的遍历
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>           //c++的标准库
#include <vector>           //c++功能更加丰富的数组

using namespace std;

struct TreeNode{
    int data;               //数据域
    TreeNode *left,*right;      //指针域
};

void insert(TreeNode*&root,int data){
    if(root==NULL){             //到达空节点时，即为需要插入的位置
        root=new TreeNode;
        root->data=data;
        root->left=root->right=NULL;//初始化插入的节点
        return;
    }
    if(data<root->data) insert(root->left,data);//递归调用insert，插在左子树
    else insert(root->right,data);              //递归调用insert，插在右子树
}

void preOrder(TreeNode*root,vector<int>&vi){
    if(root==NULL) return;                      //遍历终止条件(边界检查)
    vi.push_back(root->data);                   //递归调用实现先序遍历
    preOrder(root->left,vi);
    preOrder(root->right,vi);
}

void preOrderMirror(TreeNode*root,vector<int>&vi){
    if(root==NULL) return;                      //遍历终止条件(边界检查)
    vi.push_back(root->data);                   //递归调用实现先序镜像遍历
    preOrderMirror(root->right,vi);
    preOrderMirror(root->left,vi);
}

void postOrder(TreeNode*root,vector<int>&vi){
    if(root==NULL) return;                      //遍历终止条件(边界检查)                 
    postOrder(root->left,vi);                   //递归调用实现后序遍历
    postOrder(root->right,vi);
    vi.push_back(root->data); 
}

void postOrderMirror(TreeNode*root,vector<int>&vi){
    if(root==NULL) return;                      //遍历终止条件(边界检查)
    postOrderMirror(root->right,vi);            //递归调用实现后序镜像遍历
    postOrderMirror(root->left,vi);
    vi.push_back(root->data);                   
}
vector<int> origin,pre,preM,post,postM;

int main(){
    int n,Data;
    TreeNode*root=NULL;         //定义头结点
    scanf("%d",&n);             //输入节点个数
    while(n--){
        scanf("%d",&Data);
        origin.push_back(Data); //将数据加入origin
        insert(root,Data);      //将data插入二叉树
    }
    preOrder(root,pre);         //求先序
    preOrderMirror(root,preM);  //求镜像树先序
    postOrder(root,post);       //求后序
    postOrderMirror(root,postM);//求镜像树后序
    if(origin==pre){
        printf("YES\n");
        for(int i=0;i<post.size();i++){
            printf("%d",post[i]);
            if(i<post.size()-1) printf(" ");//每个元素序列之间加一个空格，最后一个元素之后不加空格
        }
    }
    else if(origin==preM){                 //初始序列等于镜像树先序序列
        printf("YES\n");
        for(int i=0;i<postM.size();i++){
            printf("%d",postM[i]);
            if(i<postM.size()-1) printf(" ");
        }
    }
    else{
        printf("NO\n");                    //否则输出0
    }

    getchar();
    system("pause");
    return 0;
}