## 编号：链表最大孪生和（AC）

在一个大小为 n 且 n 为 偶数 的链表中，对于 0 <= i <= (n / 2) - 1 的 i ，第 i 个节点（下标从 0 开始）的孪生节点为第 (n-1-i) 个节点 。

比方说，n = 4 那么节点 0 是节点 3 的孪生节点，节点 1 是节点 2 的孪生节点。这是长度为 n = 4 的链表中所有的孪生节点。
孪生和 定义为一个节点和它孪生节点两者值之和。

给你一个长度为偶数的链表的头节点 head ，请你返回链表的 最大孪生和 。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/12/03/eg1drawio.png)

```
输入：head = [5,4,2,1]
输出：6
解释：
节点 0 和节点 1 分别是节点 3 和 2 的孪生节点。孪生和都为 6 。
链表中没有其他孪生节点。
所以，链表的最大孪生和是 6 。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/12/03/eg2drawio.png)

```
输入：head = [4,2,2,3]
输出：7
解释：
链表中的孪生节点为：
- 节点 0 是节点 3 的孪生节点，孪生和为 4 + 3 = 7 。
- 节点 1 是节点 2 的孪生节点，孪生和为 2 + 2 = 4 。
所以，最大孪生和为 max(7, 4) = 7 。
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2021/12/03/eg3drawio.png)

```
输入：head = [1,100000]
输出：100001
解释：
链表中只有一对孪生节点，孪生和为 1 + 100000 = 100001 。 
```
提示：

* 链表的节点数目是 [2, 10^5] 中的 偶数 。
* 1 <= Node.val <= 10^5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-twin-sum-of-a-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

因为链表上只能一步一步移动，对首位的和统计不方便，所以我们就把它存入数组中，再利用双指针进行求首位和。

### 我的做法

我通常采用链表的虚拟头节点方法来处理！

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
public:
    int pairSum(ListNode* head) {
        int maxval = 0;
        
        ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
        dummyHead->next = head;
        ListNode* cur;
        cur = dummyHead;
        vector<int> nums;
        
        //链表转数组
        while(cur->next){
            cur = cur->next;
            nums.push_back(cur->val);
        }
        
        //双指针求首尾最大和
        for(int i = 0, j = nums.size() - 1; i < j; i++, j--){
            maxval = max(nums[i] + nums[j], maxval);
        }
        return maxval;
    }
};
```

惯例，copy代码学习!

###  [何逊](https://leetcode-cn.com/u/heltion/)的做法

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
public:
    int pairSum(ListNode* head) {
        vector<int> v;
        for (auto p = head; p; p = p->next) v.push_back(p->val);
        int ans = 0;
        for (int i = 0; i < v.size(); i += 1)
            ans = max(v[i] + v[v.size() - 1 - i], ans);
        return ans;
    }
};
```

整体做法一样！

### 链表做法（相同时间复杂度情况下更低的空间复杂度）

两个孪生元素分别为首尾第i个和第n-i-1个元素。我们需要从头到中间遍历前n/2个，同时从尾到中间遍历后n/2个。但是后n/2个在原有链表基础上是没有办法完成从后往前的遍历的，只能选择将其反转。

因此，解题思路分为三步：

（1）利用快慢指针求出链表的中点

（2）反转后一半的元素

（3）双指针，一个指针遍历从前到后遍历前n/2个元素，另一个指针遍历从后到前遍历后n/2个元素。

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
public:
    int pairSum(ListNode* head) {
        //快慢指针求中间的节点，求完slow为后一半元素的第一个
        ListNode *fast = head, *slow = head;
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
        }

        //双指针方法：反转后一半的元素(不清楚的可以画图)
        ListNode *pre = nullptr;//反转完变成了最后一个节点
        ListNode *cur = slow;
        while(cur != nullptr){
            ListNode *temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }

        int ans = 0;
        ListNode *p;    
        ListNode *q;
        //前一半从头开始后一半从尾开始，分别像中间遍历
        for(p = head, q = pre; q; p = p->next, q = q->next){
            ans = max(ans, p->val + q->val);
        }
        return ans;
    }
};
```
