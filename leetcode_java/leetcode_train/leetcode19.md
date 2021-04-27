## 编号19：删除链表的倒数第N个节点(双指针的经典应用)

给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

进阶：你能尝试使用一趟扫描实现吗？

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg)
```
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
```
示例 2：
```
输入：head = [1], n = 1
输出：[]
```
示例 3：
```
输入：head = [1,2], n = 1
输出：[1]
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
### 思路
*双指针的经典应用，如果要删除倒数第n个节点，让fast移动n步，然后让fast和slow同时移动，直到fast指向链表末尾。删掉slow所指向的节点就可以了。*

思路是这样的，但要注意一些细节。
分为如下几步：

* 使用虚拟头结点，这样方面处理删除实际头结点的逻辑。

* 定义fast指针和slow指针，初始值为虚拟头结点，如图：
![avater](https://camo.githubusercontent.com/7d152f394ffaec592f553e1d9fa91196360d2a18e066fef99420843579c433e2/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f31392e2545352538382541302545392539392541342545392539332542452545382541312541382545372539412538342545352538302539322545362539352542302545372541432541434e2545342542382541412545382538412538322545372538322542392e706e67)
* fast首先走n + 1步 ，为什么是n+1呢，因为只有这样同时移动的时候slow才能指向删除节点的上一个节点（方便做删除操作），如图：
![avater](https://camo.githubusercontent.com/e72dccc9875eaf57a33bdf1a36510766d337610fa7ef4275c3ee222ed18378e2/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f31392e2545352538382541302545392539392541342545392539332542452545382541312541382545372539412538342545352538302539322545362539352542302545372541432541434e254534254238254141254538253841253832254537253832254239312e706e67)
* fast和slow同时移动，之道fast指向末尾，如图：
![avater](https://camo.githubusercontent.com/a87d8fe4ab540edbabb211120bec75af0950517c76bb7a72018a93f6ef2984cc/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f31392e2545352538382541302545392539392541342545392539332542452545382541312541382545372539412538342545352538302539322545362539352542302545372541432541434e254534254238254141254538253841253832254537253832254239322e706e67)
删除slow指向的下一个节点，如图：
![avater](https://camo.githubusercontent.com/149d85b95226a405592b9ba31324980ea183b936aead1617bdd51bb05f23508b/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f31392e2545352538382541302545392539392541342545392539332542452545382541312541382545372539412538342545352538302539322545362539352542302545372541432541434e254534254238254141254538253841253832254537253832254239332e706e67)

---
```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode removeNthFromEnd(ListNode head, int n) {
        /* 建立一个虚拟头节点*/
        ListNode sentinel/*哨兵的英文*/=new ListNode(0);
        sentinel.next=head;
        /*设立快慢指针*/
        ListNode fast=sentinel;
        ListNode slow=sentinel;
        while(n-- > 0&&fast!=null){
            fast=fast.next;
        }
        ListNode pre=null;
        /*删除操作的要点，必须要记住要删除节点的前驱节点 */
        while(fast!=null){
            pre=slow;
            slow=slow.next;
            fast=fast.next;
        }
        /*进行删除操作*/
        pre.next=slow.next;
        slow.next=null;//释放原来的slow节点的next指针，这句可有可无

        return sentinel.next;//返回真正的头节点
    }
}
```