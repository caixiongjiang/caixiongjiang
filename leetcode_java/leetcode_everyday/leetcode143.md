## 编号143：重排列表

给定一个单链表 L 的头节点 head ，单链表 L 表示为：

```L0 → L1 → … → Ln-1 → Ln```
请将其重新排列后变为：

```L0 → Ln → L1 → Ln-1 → L2 → Ln-2 →...```

不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

 

示例 1:

![avater](https://pic.leetcode-cn.com/1626420311-PkUiGI-image.png)

```
输入: head = [1,2,3,4]
输出: [1,4,2,3]
```
示例 2:

![avater](https://pic.leetcode-cn.com/1626420320-YUiulT-image.png)

```
输入: head = [1,2,3,4,5]
输出: [1,5,2,4,3]
```
提示：

* 链表的长度范围为 [1, 5 * 104]
* 1 <= node.val <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reorder-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

本篇将给出三种C++实现的方法：

* 数组模拟
* 双向队列模拟
* 直接分割链表

## 方法一

把链表放进数组中，然后通过双指针法，一前一后，来遍历数组，构造链表。

代码如下：
```c++
class Solution {
public:
    void reorderList(ListNode* head) {
        vector<ListNode*> vec;
        ListNode* cur = head;
        if (cur == nullptr) return;
        while(cur != nullptr) {
            vec.push_back(cur);
            cur = cur->next;
        }
        cur = head;
        int i = 1;
        int j = vec.size() - 1;  // i j为之前前后的双指针
        int count = 0; // 计数，偶数去后面，奇数取前面
        while (i <= j) {
            if (count % 2 == 0) {
                cur->next = vec[j];
                j--;
            } else {
                cur->next = vec[i];
                i++;
            }
            cur = cur->next;
            count++;
        }
        if (vec.size() % 2 == 0) { // 如果是偶数，还要多处理中间的一个
            cur->next = vec[i];
            cur = cur->next;
        }
        cur->next = nullptr; // 注意结尾
    }
};
```

## 方法二
把链表放进双向队列，然后通过双向队列一前一后弹出数据，来构造新的链表。这种方法比操作数组容易一些，不用双指针模拟一前一后了
```c++
class Solution {
public:
    void reorderList(ListNode* head) {
        deque<ListNode*> que;
        ListNode* cur = head;
        if (cur == nullptr) return;

        while(cur->next != nullptr) {
            que.push_back(cur->next);
            cur = cur->next;
        }

        cur = head;
        int count = 0; // 计数，偶数去后面，奇数取前面
        ListNode* node;
        while(que.size()) {
            if (count % 2 == 0) {
                node = que.back();
                que.pop_back();
            } else {
                node = que.front();
                que.pop_front();
            }
            count++;
            cur->next = node;
            cur = cur->next;
        }
        cur->next = nullptr; // 注意结尾
    }
};
```

## 方法三

将链表分割成两个链表，然后把第二个链表反转，之后在通过两个链表拼接成新的链表。

如图：

![avater](https://camo.githubusercontent.com/8906edb7c5dedb84254a4d91bfeb571e8316e4ca473ab077b383048c00887b1a/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3134332ee9878de68e92e993bee8a1a82e706e67)

这种方法，比较难，平均切割链表，看上去很简单，真正代码写的时候有很多细节，同时两个链表最后拼装整一个新的链表也有一些细节需要注意！

代码如下：
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
private:
    // 反转链表
    ListNode* reverseList(ListNode* head) {
        ListNode* temp; // 保存cur的下一个节点
        ListNode* cur = head;
        ListNode* pre = NULL;
        while(cur) {
            temp = cur->next;  // 保存一下 cur的下一个节点，因为接下来要改变cur->next
            cur->next = pre; // 翻转操作
            // 更新pre 和 cur指针,前后顺序不能变
            pre = cur;
            cur = temp;
        }
        return pre;
    }

public:
    void reorderList(ListNode* head) {
        if (head == nullptr) return;
        // 使用快慢指针法，将链表分成长度均等的两个链表head1和head2
        // 如果总链表长度为奇数，则head1相对head2多一个节点
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast && fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode* head1 = head;
        ListNode* head2;
        head2 = slow->next;
        slow->next = nullptr;//断链操作

        // 对head2进行翻转
        head2 = reverseList(head2);

        // 将head1和head2交替生成新的链表head
        ListNode* cur1 = head1;
        ListNode* cur2 = head2;
        ListNode* cur = head;//目标链表的指针
        cur1 = cur1->next;
        int count = 0; // 偶数取head2的元素，奇数取head1的元素
        while (cur1 && cur2) {
            if (count % 2 == 0) {
                cur->next = cur2;
                cur2 = cur2->next;
            } else {
                cur->next = cur1;
                cur1 = cur1->next;
            }
            count++;
            cur = cur->next;
        }
        if (cur2 != nullptr) { // 处理结尾
            cur->next = cur2;
        }
        if (cur1 != nullptr) {
            cur->next = cur1;
        }
    }
};
```