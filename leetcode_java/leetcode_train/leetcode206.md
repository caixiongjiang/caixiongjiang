## 编号206：反转链表

给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。

示例 1：
```
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
```
---
### 思路
如果再定义一个新的链表，实现链表元素的反转，其实这是对内存空间的浪费。

其实只需要改变链表的next指针的指向，直接将链表反转 ，而不用重新定义一个新的链表，如图所示:

![avater](https://camo.githubusercontent.com/29085c56cc66b79e244cdd3762e3cdfd40828eafea4a327569f1dd01e2441378/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303231383039303930313230372e706e67)

拿有示例中的链表来举例，如动画所示：
![avater](https://camo.githubusercontent.com/36cf9298bccf54091dbcabb9ede884bf98d5b2f6f04bd89a36ac2904b26d0971/68747470733a2f2f747661312e73696e61696d672e636e2f6c617267652f30303865476d5a456c7931676e7266316f626f757067333067793063343471702e676966)

</br></br></br>
首先定义一个cur指针，指向头结点，再定义一个pre指针，初始化为null。

然后就要开始反转了，首先要把 cur->next 节点用tmp指针保存一下，也就是保存一下这个节点。

为什么要保存一下这个节点呢，因为接下来要改变 cur->next 的指向了，将cur->next 指向pre ，此时已经反转了第一个节点了。

接下来，就是循环走如下代码逻辑了，继续移动pre和cur指针。

最后，cur 指针已经指向了null，循环结束，链表也反转完毕了。 此时我们return pre指针就可以了，pre指针就指向了新的头结点。

---
### 双指针法

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
    public ListNode reverseList(ListNode head) {
        ListNode tmp;
        ListNode cur=head;
        ListNode pre=null;
        while(cur!=null){
            tmp=cur.next;//保存后继节点
            cur.next=pre;//翻转操作
            /*更新下一个要传入的节点*/
            pre=cur;
            cur=tmp;
        }
        return pre;//返回下一个循环的进入节点
    }
}
```

### 递归写法

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
    public ListNode reverse(ListNode pre,ListNode cur) {
        if(cur==null) return pre;
        ListNode tmp=cur.next;//保存下一个节点
        cur.next=pre;//翻转操作
        return reverse(cur,tmp);//传入新的参数
    }
    public ListNode reverseList(ListNode head){
        return reverse(null,head);
    }
}
```