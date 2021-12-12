## 编号2095：删除链表的中间节点（AC）

给你一个链表的头节点 head 。删除 链表的 中间节点 ，并返回修改后的链表的头节点 head 。

长度为 n 链表的中间节点是从头数起第 ⌊n / 2⌋ 个节点（下标从 0 开始），其中 ⌊x⌋ 表示小于或等于 x 的最大整数。

* 对于 n = 1、2、3、4 和 5 的情况，中间节点的下标分别是 0、1、1、2 和 2 。
 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/11/16/eg1drawio.png)

```
输入：head = [1,3,4,7,1,2,6]
输出：[1,3,4,1,2,6]
解释：
上图表示给出的链表。节点的下标分别标注在每个节点的下方。
由于 n = 7 ，值为 7 的节点 3 是中间节点，用红色标注。
返回结果为移除节点后的新链表。 
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/11/16/eg2drawio.png)

```
输入：head = [1,2,3,4]
输出：[1,2,4]
解释：
上图表示给出的链表。
对于 n = 4 ，值为 3 的节点 2 是中间节点，用红色标注。
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2021/11/16/eg3drawio.png)

```
输入：head = [2,1]
输出：[2]
解释：
上图表示给出的链表。
对于 n = 2 ，值为 1 的节点 1 是中间节点，用红色标注。
值为 2 的节点 0 是移除节点 1 后剩下的唯一一个节点。
```
提示：

* 链表中节点的数目在范围 [1, 105] 内
* 1 <= Node.val <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/delete-the-middle-node-of-a-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

思路：通过快慢双指针的方法来寻找待删除节点的前驱节点，然后删除中间节点。

步骤：
* 设置虚拟头节点，并设置快慢指针
* 快指针每次走两步，慢指针每次走一步：
	* 若节点数为奇数，快指针走到最后一个节点时，慢指针刚好走到中间节点的前驱节点
	* 若节点数为偶数，快指针走到倒数第二个节点时，慢指针刚好走到中间节点的前驱节点
* 利用指针进行删除操作

注意点：节点数为1 或者 2时，需要单独处理。


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
    ListNode* deleteMiddle(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next=head;
        ListNode* slow = dummyHead;
        ListNode* fast = dummyHead;
        if(head->next == nullptr) return NULL;
        if(head->next->next == nullptr){
            head->next = nullptr;
            return head;
        }
        while(fast->next && fast->next->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        slow->next = slow->next->next;
        return dummyHead->next;
    }
};
```