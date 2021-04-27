## 编号707：设计链表
*设计链表的实现。您可以选择使用单链表或双链表。单链表中的节点应该具有两个属性：val 和 next。val 是当前节点的值，next 是指向下一个节点的指针/引用。如果要使用双向链表，则还需要一个属性 prev 以指示链表中的上一个节点。假设链表中的所有节点都是 0-index 的。*

在链表类中实现这些功能：

* get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回-1。
* addAtHead(val)：在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。
* addAtTail(val)：将值为 val 的节点追加到链表的最后一个元素。
* addAtIndex(index,val)：在链表中的第 index 个节点之前添加值为 val  的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。
* deleteAtIndex(index)：如果索引 index 有效，则删除链表中的第 index 个节点。
 

示例：
```java
MyLinkedList linkedList = new MyLinkedList();
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1,2);   //链表变为1-> 2-> 3
linkedList.get(1);            //返回2
linkedList.deleteAtIndex(1);  //现在链表是1-> 3
linkedList.get(1);            //返回3
```

提示：

* 所有val值都在 [1, 1000] 之内。
* 操作次数将在  [1, 1000] 之内。
* 请不要使用内置的 LinkedList 库。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/design-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---

```java
public class ListNode {
		  int val;
		  ListNode next;
		  ListNode(int x) { val = x; }
		}
	class MyLinkedList {
		int length;
		ListNode head;
		    /** 初始化构造器*/
		public MyLinkedList() {
			this.head=new ListNode(0);
			this.length=0;
		}
		    /**获取索引值对应的节点值 */
		public int get(int index) {
			if(index<0||index>=length) return -1;
			ListNode p=head;
			for(int i=0;i<=index;i++) {//index=0,对应第1个节点，第一个节点即为head.next
				p=p.next;
			}
			return p.val;
		}
		    /**在链表头添加节点 */
		public void addAtHead(int val) {
			ListNode first=new ListNode(val);
			first.next=head.next;
			head.next=first;
			length++;
			//addAtIndex(0,val);
		}
		    /** 在链表尾部添加节点 */
		public void addAtTail(int val) {
			ListNode p=head;
			while(p.next!=null) p=p.next;
			p.next=new ListNode(val);
			length++;
		}
		    /**在索引值为index的节点之前插入节点 */
		public void addAtIndex(int index, int val) {
			if(index<0) index=0;//addAtHead(val); return;
			if(index>length) return;
			/*if(index==length) { addAtTail(val); return; }*/
			length++;
			ListNode pre=head;
			for(int i=0;i<index;i++)pre=pre.next;
			ListNode temp=new ListNode(val);
			temp.next=pre.next;
			pre.next=temp;
		} 
		    /** 如果索引 index 有效，则删除链表索引值为 index的节点。 */
		public void deleteAtIndex(int index) {
			if(index<0||index>=length) return;
			length--;
			ListNode pre=head;
			for(int i=0;i<index;i++) pre=pre.next;
			pre.next=pre.next.next;	
		}
	}				
```