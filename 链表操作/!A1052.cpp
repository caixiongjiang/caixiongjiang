//链表排序（这里使用直接插入排序）
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <math.h>

using namespace std;
struct Node{
    int key;
    int next;
}static_list[100001];

int insert_sort(int L){
    int new_L=100000;                   //新设立一个链表用来存储从小到大插入的链表
    static_list[new_L].key=0x80000000;  //新链表的表头初始化
    static_list[new_L].next=-1;
    //寻找插入的位置
    static_list[new_L].next=L;          //先将第一个元素插入新链表
    L=static_list[L].next;
    int r;                              //用于保存L的后继节点，防止L断链
    while(L!=-1){
        int temp=static_list[L].key;    //将旧链表所有节点代表的值记录在temp中
        int start=static_list[new_L].next;
        int pre=new_L;                  //用来保存start前驱节点的位置                
        while(temp>static_list[start].key&&start!=-1){
            start=static_list[start].next;
            pre=static_list[pre].next;    
        }
    //位置确定就退出循环
    r=static_list[L].next;
    //执行插入过程(位置必须插在pre和start之间)
        static_list[pre].next=L;
        static_list[L].next=start;
        L=r;
    }
    return static_list[new_L].next;

}
int main(){
    int n,L;
    int N=n;
    scanf("%d%d",&n,&L);
    int Address,Key,Next;
    while(n--){
        scanf("%d %d %d",&Address,&Key,&Next);
        static_list[Key].key=Key;               //初始化的过程
        static_list[Key].next=Next;
    }
    L=insert_sort(L);
    printf("%d %05d\n",N,L);
    while(L!=-1){
        if(static_list[L].next==-1)
        printf("%05d %d -1\n",L,static_list[L].key);
        else
        printf("%05d %d %05d\n",L,static_list[L].key,static_list[L].next);
    }
    getchar();
    system("pause");
    return 0;                         
}