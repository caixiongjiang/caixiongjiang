//输出完全二叉排序树，使用数组保存完全二叉树的节点。
//完全二叉树可以只存输入的元素，普通二叉树还要多存空节点的值。
#include <stdio.h>
#include <algorithm>            //c++算法库  

using namespace std;
const int maxn=1010;
int CBT[maxn],number[maxn];                  //全局变量自动定义数组元素全为0
int N, counter=0;                          //题目中给的根节点的编号为1
void inorderTraversal(int root){
    if(root>N) return;
    inorderTraversal(2*root);
    //中序遍历将节点赋值放在中间
    CBT[root]=number[counter++];
    inorderTraversal(2*root+1);

}

int main(){
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&number[i]);
    }
    sort(number,number+N);               //数组名是一个指针，指向数组第一个元素的位置，引用的函数参数
    inorderTraversal(1);                 //遵循左闭右开的原则
    for(int i=1;i<=N;i++){               //根节点从1开始，方便寻找孩子节点
        printf("%d",CBT[i]);
        if(i<N) printf(" ");
    }   
    return 0;
}