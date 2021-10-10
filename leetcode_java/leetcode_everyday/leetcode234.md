## 编号234：回文链表

给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。

 

示例 1：
![avater](https://assets.leetcode.com/uploads/2021/03/03/pal1linked-list.jpg)
```
输入：head = [1,2,2,1]
输出：true
```
示例 2：
![avater](https://assets.leetcode.com/uploads/2021/03/03/pal2linked-list.jpg)
```
输入：head = [1,2]
输出：false 
```
提示：

* 链表中节点数目在范围[1, 105] 内
* 0 <= Node.val <= 9
 

**进阶：**你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

把链表装成数组，在进行判断：
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
    bool isPalindrome(ListNode* head) {
        vector<int> vec;
        ListNode* cur = head;
        while(cur){
            vec.push_back(cur->val);
            cur = cur->next;
        }
        //比较回文数组
        for(int i = 0, j = vec.size() - 1; i < j; i++, j--){
            if(vec[i] != vec[j]) return false;
        }
        return true;
    }
};
```
**上面代码可以在优化，就是先求出链表长度，然后给定vector的初始长度，这样避免vector每次添加节点重新开辟空间**
```c++
class Solution {
public:
    bool isPalindrome(ListNode* head) {

        ListNode* cur  = head;
        int length = 0;
        while (cur) {
            length++;
            cur = cur->next;
        }
        vector<int> vec(length, 0); // 给定vector的初始长度，这样避免vector每次添加节点重新开辟空间
        cur = head;
        int index = 0;
        while (cur) {
            vec[index++] = cur->val;
            cur = cur->next;
        }
        // 比较数组回文
        for (int i = 0, j = vec.size() - 1; i < j; i++, j--) {
            if (vec[i] != vec[j]) return false;
        }
        return true;
    }
};
```

## 方法二：反转后半部分链表

分为如下几步：

* 用快慢指针，快指针有两步，慢指针走一步，快指针遇到终止位置时，慢指针就在链表中间位置
* 同时用pre记录慢指针指向节点的前一个节点，用来分割链表
* 将链表分为前后均等两部分，如果链表长度是奇数，那么后半部分多一个节点
* 将后半部分反转 ，得cur2，前半部分为cur1
* 按照cur1的长度，一次比较cur1和cur2的节点数值
如图所示：
![avater](https://camo.githubusercontent.com/49d99aa26be2492073f56a3c4ed4b50bc3d29d69bb4a54d51b598648a3f37814/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3233342ee59b9ee69687e993bee8a1a82e706e67)

代码如下：
```c++
class Solution{
public:
    bool isPalindrome(ListNode* head){
        if(head == nullptr || head->next == nullptr) return true;
        ListNode* slow = head;//慢指针，找到链表中间位置，进行分割
        ListNode* fast = head;
        ListNode* pre = head;//记录慢指针的前一个节点，用来分隔链表
        while(fast && fast->next){
            pre = slow;
            slow = slow->next;//慢指针一次走一步
            fast = fast->next->next;//快指针一次走两步
        }
        pre->next = nullptr;//分割链表

        ListNode* cur1 = head;
        ListNode* cur2 = reverseList(slow);//反转后半部分，总链表长度为奇数，cur2比cur1多一个节点

        //开始两个链表的比较
        while(cur1){
            if(cur1->val != cur2->val) return false;
            cur1 = cur1->next;
            cur2 = cur2->next; 
        }
        return true;
    }
    //反转链表
    ListNode* reverseList(ListNode* head){
        ListNode* temp;//保存cur的下一个节点
        ListNode* cur = head;
        ListNode* pre = nullptr;
        while(cur){
            temp = cur->next;//保存一下cur的下一个节点，因为接下来要改变cur->next
            cur->next = pre;//翻转操作:断链
            //更新pre和cur指针
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};
```