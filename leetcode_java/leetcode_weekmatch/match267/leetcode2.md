## 编号：反转偶数长度组的节点（×）

给你一个链表的头节点 head 。

链表中的节点 按顺序 划分成若干 非空 组，这些非空组的长度构成一个自然数序列（1, 2, 3, 4, ...）。一个组的 长度 就是组中分配到的节点数目。换句话说：

* 节点 1 分配给第一组
* 节点 2 和 3 分配给第二组
* 节点 4、5 和 6 分配给第三组，以此类推
注意，最后一组的长度可能小于或者等于 1 + 倒数第二组的长度 。

反转 每个 偶数 长度组中的节点，并返回修改后链表的头节点 head 。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/10/25/eg1.png)

```
输入：head = [5,2,6,3,9,1,7,3,8,4]
输出：[5,6,2,3,9,1,4,8,3,7]
解释：
- 第一组长度为 1 ，奇数，没有发生反转。
- 第二组长度为 2 ，偶数，节点反转。
- 第三组长度为 3 ，奇数，没有发生反转。
- 最后一组长度为 4 ，偶数，节点反转。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/10/25/eg2.png)

```
输入：head = [1,1,0,6]
输出：[1,0,1,6]
解释：
- 第一组长度为 1 ，没有发生反转。
- 第二组长度为 2 ，节点反转。
- 最后一组长度为 1 ，没有发生反转。
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2021/10/28/eg3.png)

```
输入：head = [2,1]
输出：[2,1]
解释：
- 第一组长度为 1 ，没有发生反转。
- 最后一组长度为 1 ，没有发生反转。
```
示例 4：
```
输入：head = [8]
输出：[8]
解释：只有一个长度为 1 的组，没有发生反转。 
```
提示：

* 链表中节点数目范围是 [1, 105]
* 0 <= Node.val <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-nodes-in-even-length-groups
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

题目要求是这么说的：

反转 每个 偶数 长度组中的节点，并返回修改后链表的头节点 head。

上面的栗子是这么分组的：
```
第一组：0 （奇数个元素，不反转）
第二组：4，2 （偶数个元素，反转）
第三组：1，3 （偶数个元素，反转）
```
这里就产生了错误！

<span style="color:green">这里反转是根据每组元素个数的奇偶来判断的，而非组数的奇偶！！！</span>

这一点理解清楚了，就好解决了。

思路：

**先将链表的所有结点存入一个vector容器中，然后借助vector容器中自带的函数来反转需要反转的结点（链表直接反转不太好操作），然后将最终的vector的值赋值给链表的每个结点即可。**

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
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        vector<int>a;
        ListNode* curr = head;
        while(curr){//将链表中的每个元素存入vector容器
            a.push_back(curr->val);
            curr = curr->next;
        }
        int i = 0, flag = 1;
        int n = a.size();
        for(; i + flag < n; ){
            if(flag % 2 == 0){//反转需要反转的结点
                reverse(a.begin() + i, a.begin() + i + flag);
            }
            i += flag;
            flag++;
        }
        if((n - i) % 2 == 0){//最后一组单独判断奇偶
            reverse(a.begin() + i, a.end());
        }
        curr = head;
        for(i = 0; i < n; i++){//将vector容器中的每个元素重新存入链表中
            curr->val = a[i];
            curr = curr->next;
        }
        return head;
    }
};
```

