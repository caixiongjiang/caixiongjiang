## 编号225：用队列来实现栈

你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通队列的全部四种操作（push、top、pop 和 empty）。

实现 MyStack 类：

void push(int x) 将元素 x 压入栈顶。
int pop() 移除并返回栈顶元素。
int top() 返回栈顶元素。
boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。
 

注意：

你只能使用队列的基本操作 —— 也就是 push to back、peek/pop from front、size 和 is empty 这些操作。
你所使用的语言也许不支持队列。 你可以使用 list （列表）或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。
 

示例：
```
输入：
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 2, 2, false]

解释：
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // 返回 2
myStack.pop(); // 返回 2
myStack.empty(); // 返回 False
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/implement-stack-using-queues
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
队列模拟栈，其实一个队列就够了，那么我们先说一说两个队列来实现栈的思路。

***队列是先进先出的规则，把一个队列中的数据导入另一个队列中，数据的顺序并没有变，并有变成先进后出的顺序。***

所以用栈实现队列， 和用队列实现栈的思路还是不一样的，这取决于这两个数据结构的性质。
但是依然还是要用两个队列来模拟栈，***只不过没有输入和输出的关系，而是另一个队列完全用又来备份的！***


模拟的队列执行语句如下： queue.push(1); queue.push(2); queue.pop(); 
</br>// 注意弹出的操作 queue.push(3); queue.push(4); queue.pop(); 
</br>// 注意弹出的操作 queue.pop(); queue.pop(); queue.empty();

![avater](https://camo.githubusercontent.com/983f56473c8c3654dc727c790c8070dbb5a21b9db7f52dd0f3cf630a8c240598/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f676966732f3232352e2545372539342541382545392539382539462545352538382539372545352541452539452545372538452542302545362541302538382e676966)

```java
class MyStack {
    Queue<Integer> queue1;//和栈中保持一样元素的队列
    Queue<Integer> queue2;//辅助队列
    /** Initialize your data structure here. */
    public MyStack() {
        queue1=new LinkedList<>();
        queue2=new LinkedList<>();
    }
    
    /** Push element x onto stack. */
    public void push(int x) {
        queue2.add(x);//先放在辅助队列
        while(!queue1.isEmpty()){   //queue中只留最后一个元素
            queue2.add(queue1.poll());
        }
        Queue<Integer> queueTmp;
        queueTmp=queue1;
        queue1=queue2;
        queue2=queueTmp;//交换队列1和队列2，将所有元素都放到queue1中
    }
    
    /** Removes the element on top of the stack and returns that element. */
    public int pop() {
        return queue1.poll();
    }
    
    /** Get the top element. */
    public int top() {
        return queue1.peek();
    }
    
    /** Returns whether the stack is empty. */
    public boolean empty() {
        return queue1.isEmpty();
    }
}

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack obj = new MyStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * boolean param_4 = obj.empty();
 */
```