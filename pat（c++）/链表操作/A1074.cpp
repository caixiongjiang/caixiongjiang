//反转链表
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <math.h>

using namespace std;
struct Node{
    int data;
    int next;
}static_list[100001];
//      node0->node1->node2-node3->*
//      head                tail
//pre   cur    nex(第一轮)
//      pre    cur    nex(第二轮)
void my_reverse(int head,int tail,int &new_head,int &new_tail){
    int pre,cur,nex;
    new_head=tail;          //交换头尾
    new_tail=head;
    cur=head;
    pre=-1;
    while(pre!=tail){
        nex=static_list[cur].next;  //第一步
        static_list[cur].next=pre;  //第二步
        pre=cur;
        cur=nex;
    }
}

int main(){
    int L,Address,Data,Next,n,K;        //n为节点数，K为每k个反转一次
    scanf("%d%d%d",&L,&n,&K);

    while(n--){
        scanf("%d%d%d",&Address,&Data,&Next);
        static_list[Address].data=Data;
        static_list[Address].next=Next;
    }
    int pre,nex;
    static_list[100000].next=L;
    pre=100000;                          //pre代表整个链表的前驱
    int hair=pre;
    while(true){                        //试探是否能够k个一组
        int tail=pre;
        for(int i=0;i<K;i++){
            tail=static_list[tail].next;
            if(tail==-1) 
            break;                      //退出for循环
        }
        if(tail==-1)
        break;                          //退出while循环
        nex=static_list[tail].next;
    //开始反转链表
        int new_head,new_tail;
        my_reverse(L,tail,new_head,new_tail);//L是每一轮反转的头，tail是每一轮反转的尾；
                                             //new_head是反转之后的头，new_tail是反转之后的尾；
    //重新连接链表
        static_list[new_tail].next=nex;
        static_list[pre].next=new_head;
        pre=new_tail;
        L=nex;
    }
    //从头开始打印链表
    hair=static_list[hair].next;
    while (hair!=-1)
    {
        if(static_list[hair].next==-1)
        printf("%05d %d -1\n",hair,static_list[hair].data);
        else
        printf("%05d %d %05d\n",hair,static_list[hair].data,static_list[hair].next);
        hair=static_list[hair].next;
    }
    
    getchar();
    system("pause");
    return 0;                         
}