## 编号24：两两交换链表中的节点
给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

 

示例 1：
![avater](https://assets.leetcode.com/uploads/2020/10/03/swap_ex1.jpg)
```
输入：head = [1,2,3,4]
输出：[2,1,4,3]
```
示例 2：
```
输入：head = []
输出：[]
```
示例 3：
```
输入：head = [1]
输出：[1] 
```
提示：

* 链表中节点的数目在范围 [0, 100] 内
* 0 <= Node.val <= 100
 

**进阶**：你能在不修改链表节点值的情况下解决这个问题吗?（也就是说，仅修改节点本身。）

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/swap-nodes-in-pairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
建议使用虚拟头结点，这样会方便很多，要不然每次针对头结点（没有前一个指针指向头结点），还要单独处理。

接下来就是交换相邻两个元素了，**此时一定要画图，不画图，操作多个指针很容易乱**，而且要操作的先后顺序

初始时，cur指向虚拟头结点，然后进行如下三步：

![avater](https://camo.githubusercontent.com/385aa33d7feaec2319dcfcd955f49381bd013a629f56c1c64fb826fc88ac4aab/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f32342e254534254238254134254534254238254134254534254241254134254536253844254132254539253933254245254538254131254138254534254238254144254537253941253834254538253841253832254537253832254239312e706e67)

操作之后，链表如下：
![avater](https://camo.githubusercontent.com/5cb49cd4d54b499130cd5de4ac3c58b8bcf273f2185bf4712d29f536f66aa795/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f32342e254534254238254134254534254238254134254534254241254134254536253844254132254539253933254245254538254131254138254534254238254144254537253941253834254538253841253832254537253832254239322e706e67)




整体代码如下：
```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);//设置一个虚拟头结点
        dummyHead->next = head;//指向头结点，方便后面做删除操作
        ListNode* cur = dummyHead;
        while(cur->next != nullptr && cur->next->next != nullptr){
            ListNode* tmp1 = cur->next;//记录临时节点1
            ListNode* tmp2 = cur->next->next->next;//记录临时节点2
            //三部曲
            cur->next = cur->next->next;//步骤一
            cur->next->next = tmp1;//步骤二
            cur->next->next->next = tmp2;//步骤三

            cur = cur->next->next;//cur移动两位，准备进行下一轮交换
        }
        return dummyHead->next;
    }
};
```

## 使用双指针避免中间变量
```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* swapPairs(struct ListNode* head){
    //使用双指针避免使用中间变量
    typedef struct ListNode ListNode;
    ListNode *fakehead = (ListNode *)malloc(sizeof(ListNode));
    fakehead->next = head;
    ListNode* right = fakehead->next;
    ListNode* left = fakehead;
    while(left && right && right->next ){
        left->next = right->next;
        right->next = left->next->next;
        left->next->next = right;
        left = right;
        right = left->next;
    }
    return fakehead->next;
}
```