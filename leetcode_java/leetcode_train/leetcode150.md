## 编号150：逆波兰表达式求值(后缀表达式求值)

根据 逆波兰表示法，求表达式的值。

有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

 

说明：

整数除法只保留整数部分。
给定逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。
 

示例 1：
```
输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
```
示例 2：
```
输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
```
示例 3：
```
输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：
该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22 
```
提示：

1 <= tokens.length <= 104
tokens[i] 要么是一个算符（"+"、"-"、"*" 或 "/"），要么是一个在范围 [-200, 200] 内的整数

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/evaluate-reverse-polish-notation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

说明：

整数除法只保留整数部分。 给定逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。  
逆波兰表达式：是一种后缀表达式，所谓后缀就是指算符写在后面。

平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。

该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。

逆波兰表达式主要有以下两个优点：

去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。

适合用栈操作运算：<span style="color:green">遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中。</span>

存储整型元素的栈空间定义及初始化:
```java
Deque<Integer> stack=new LinkedList();
```
Integer.valueOf(s)用法:***Integer.valueOf(s)把字符串s解析成Integer对象类型，返回的integer 可以调用对象中的方法。***
```java
    String s = "123";
    Integer integer = Integer.valueOf(s);
    System.out.println("integer : " + integer);
```

### 关于Deque的接口分析
双向队列操作
插入元素
* addFirst(): 向队头插入元素，如果元素为空，则发生NPE

* addLast(): 向队尾插入元素，如果为空，则发生NPE

* offerFirst(): 向队头插入元素，如果插入成功返回true，否则返回false

* offerLast(): 向队尾插入元素，如果插入成功返回true，否则返回false

移除元素
* removeFirst(): 返回并移除队头元素，如果该元素是null，则发生NoSuchElementException

* removeLast(): 返回并移除队尾元素，如果该元素是null，则发生NoSuchElementException

* pollFirst(): 返回并移除队头元素，如果队列无元素，则返回null

* pollLast(): 返回并移除队尾元素，如果队列无元素，则返回null

获取元素
* getFirst(): 获取队头元素但不移除，如果队列无元素，则发生NoSuchElementException

* getLast(): 获取队尾元素但不移除，如果队列无元素，则发生NoSuchElementException

* peekFirst(): 获取队头元素但不移除，如果队列无元素，则返回null

* peekLast(): 获取队尾元素但不移除，如果队列无元素，则返回null

栈操作
* pop(): 弹出栈中元素，也就是返回并移除队头元素，等价于removeFirst()，如果队列无元素，则发生NoSuchElementException

* push(): 向栈中压入元素，也就是向队头增加元素，等价于addFirst()，如果元素为null，则发生NPE，如果栈空间受到限制，则发生IllegalStateException


本题代码如下：
```java
class Solution {
   public int evalRPN(String[] tokens) {
        Deque<Integer> stack = new LinkedList();
        for (String token : tokens) {
            char c = token.charAt(0);
            if (!isOpe(token)) {
                stack.addFirst(stoi(token));
            } else if (c == '+') {
                stack.push(stack.pop() + stack.pop());
            } else if (c == '-') {
                stack.push(- stack.pop() + stack.pop());
            } else if (c == '*') {
                stack.push( stack.pop() * stack.pop());
            } else {
                int num1 = stack.pop();
                int num2 = stack.pop();
                stack.push( num2/num1);
            }
        }
        return stack.pop();
    }


    private boolean isOpe(String s) {
        return s.length() == 1 && s.charAt(0) <'0' || s.charAt(0) >'9';
    }

    private int stoi(String s) {
        return Integer.valueOf(s);
    }
}
```