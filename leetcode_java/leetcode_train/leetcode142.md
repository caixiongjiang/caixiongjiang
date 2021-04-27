## 编号142：环形链表Ⅱ

给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。注意，pos 仅仅是用于标识环的情况，并不会作为参数传递到函数中。

说明：不允许修改给定的链表。

进阶：

你是否可以使用 O(1) 空间解决此题？

示例 1：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist.png)

```
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。
```
示例 2：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test2.png)

```
输入：head =[1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。
```
示例 3：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test3.png)

```
输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环。
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/linked-list-cycle-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
### 思路
这道题目，不仅考察对链表的操作，而且还需要一些数学运算。

主要考察两知识点：

* 判断链表是否有环
* 如果有环，如何找到这个环的入口

</br><span style="color:green">*判断链表是否有环*</span>
</br>可以使用快慢指针法， 分别定义 fast 和 slow指针，从头结点出发，fast指针每次移动两个节点，slow指针每次移动一个节点，如果 fast 和 slow指针在途中相遇 ，说明这个链表有环。
</br></br>fast 走两个节点，slow走一个节点，有环的话，一定会在环内相遇呢，而不是永远的错开呢
</br>首先第一点： fast指针一定先进入环中，如果fast 指针和slow指针相遇的话，一定是在环中相遇，这是毋庸置疑的。
</br>那么来看一下，为什么fast指针和slow指针一定会相遇呢？
</br>可以画一个环，然后让 fast指针在任意一个节点开始追赶slow指针。
会发现最终都是这种情况， 如下图：

![avater](https://camo.githubusercontent.com/a34c992347976733ef3a34e19202a2248ef6b72a24f55f08bd27aa51dbaedc55/68747470733a2f2f747661312e73696e61696d672e636e2f6c617267652f30303865476d5a456c7931676f6f3478676c6b397967333066733062367530782e676966)

<span style="color:green">*如果有环，如何找到这个环的入口*</span>
</br>假设从头结点到环形入口节点 的节点数为x。 环形入口节点到 fast指针与slow指针相遇节点 节点数为y。 从相遇节点 再到环形入口节点节点数为 z。 如图所示：
![avater](https://camo.githubusercontent.com/0c6e7f151c5324fca67245440e3f15d76209496a3744604287feff7226645f4e/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303331383136323933383339372e706e67)
那么相遇时： slow指针走过的节点数为: x + y， fast指针走过的节点数： x + y + n (y + z)，n为fast指针在环内走了n圈才遇到slow指针， （y+z）为 一圈内节点的个数A。
</br><span style="color:green">*因为fast指针是一步走两个节点，slow指针一步走一个节点， 所以 fast指针走过的节点数 = slow指针走过的节点数 * 2：*</span>

<span style="color:green">*(x + y) * 2 = x + y + n (y + z)*</span>

<span style="color:green">*两边消掉一个（x+y）: x + y = n (y + z)*</span>

因为要找环形的入口，那么要求的是x，因为x表示 头结点到 环形入口节点的的距离。

所以要求x ，将x单独放在左面：x = n (y + z) - y ,

再从n(y+z)中提出一个 （y+z）来，整理公式之后为如下公式：x = (n - 1) (y + z) + z 注意这里n一定是大于等于1的，因为 fast指针至少要多走一圈才能相遇slow指针。

这个公式说明什么呢？

先拿n为1的情况来举例，意味着fast指针在环形里转了一圈之后，就遇到了 slow指针了。

当 n为1的时候，公式就化解为 x = z，

这就意味着，从头结点出发一个指针，从相遇节点 也出发一个指针，这两个指针每次只走一个节点， 那么当这两个指针相遇的时候就是 环形入口的节点。(此时走过了n个环)

也就是在相遇节点处，定义一个指针index1，在头结点处定一个指针index2。

让index1和index2同时移动，每次移动一个节点， 那么他们相遇的地方就是 环形入口的节点。

动画如下：

![avater](https://camo.githubusercontent.com/1b5bd012c476c747f6b783fa53a5f5a7cc50ef750ddbc40177b44043198650e5/68747470733a2f2f747661312e73696e61696d672e636e2f6c617267652f30303865476d5a456c7931676f6f3538676175696467333066773062693471722e676966)

如果slow进环入口，fast也在环入口，那么把这个环展开成直线，就是如下图的样子：
![avater](https://camo.githubusercontent.com/59852323777b9828df5b584d701e9639099565298ca72a06d5aac0110074a723/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032313033313831363530333236362e706e67)

---
### 方法1：哈希表
#### *一个非常直观的思路是：我们遍历链表中的每个节点，并将它记录下来；一旦遇到了此前遍历过的节点，就可以判定链表中存在环。借助哈希表可以很方便地实现。*
```java
public class Solution {
    public ListNode detectCycle(ListNode head) {
        ListNode pos = head;
        Set<ListNode> visited = new HashSet<ListNode>();
        while (pos != null) {
            if (visited.contains(pos)) {
                return pos;
            } else {
                visited.add(pos);
            }
            pos = pos.next;
        }
        return null;
    }
}
```

### 方法2：快慢指针
```java
/**
 * Definition for singly-linked list.
 * class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public ListNode detectCycle(ListNode head) {
        ListNode fast=head;
        ListNode slow=head;
        while(fast!=null&&slow!=null){
            if (fast.next != null) {
                fast = fast.next.next;//快指针每次走2步
            }else return null;
            slow=slow.next;//慢指针每次走1步
            if(slow==fast){
                ListNode index1=fast;//index1从相遇节点开始走
                ListNode index2=head;//index1从头节点开始走
                /*走到两个指针相遇便找到了环的入口节点*/
                while(index1!=index2){
                    index1=index1.next;
                    index2=index2.next;
                }
                return index2;
            }
        }
        return null;
    }
}
```