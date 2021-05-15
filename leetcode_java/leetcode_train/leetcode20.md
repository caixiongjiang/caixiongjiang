## 编号20：栈的应用（有效的括号）
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
 

示例 1：
```
输入：s = "()"
输出：true
```
示例 2：
```
输入：s = "()[]{}"
输出：true
```
示例 3：
```
输入：s = "(]"
输出：false
```
示例 4：
```
输入：s = "([)]"
输出：false
```
示例 5：
```
输入：s = "{[]}"
输出：true
```

提示：

1 <= s.length <= 104
s 仅由括号 '()[]{}' 组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

## 思路

由于栈结构的特殊性，非常适合做对称匹配类的题目。

首先要弄清楚，字符串里的括号不匹配有几种情况。

一些同学，在面试中看到这种题目上来就开始写代码，然后就越写越乱。

建议要写代码之前要分析好有哪几种不匹配的情况，如果不动手之前分析好，写出的代码也会有很多问题。

先来分析一下 这里有三种不匹配的情况：
![avater](https://camo.githubusercontent.com/9089c55ff04c99bf098437cc3dbc6eff5da9c03cd1fcba671508f9b41132bfd7/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f676966732f32302e2545362539432538392545362539352538382545362538422541432545352538462542372e676966)

第一种情况：已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以return false

第二种情况：遍历字符串匹配的过程中，发现栈里没有要匹配的字符。所以return false

第三种情况：遍历字符串匹配的过程中，栈已经为空了，没有匹配的字符了，说明右括号没有找到对应的左括号return false

那么什么时候说明左括号和右括号全都匹配了呢，就是字符串遍历完之后，栈是空的，就说明全都匹配了。

```java
class Solution {
    public boolean isValid(String s) {
        Deque<Character> deque=new LinkedList<>();//注意，java中Stack类型必需时包装类，int需使用Interger，char需使用Character.
        //这里使用dequeue双端队列来实现Stack
        char ch;
        for(int i=0;i<s.length();i++){
            ch=s.charAt(i);
            if(ch=='('){
                deque.push(')');
            }else if(ch=='{'){
                deque.push('}');
            }else if(ch=='['){
                deque.push(']');
            }else if(deque.isEmpty() ||deque.peek()!=ch){   //括号不匹配的情况
                return false;
            }else{                                          //括号匹配则出栈
                deque.pop();
            }
        }
        return deque.isEmpty();                             //如果最后栈为空则，则返回true，否则返回false
    }
}
```
传统Stack如下：

```java
class Solution {
    public boolean isValid(String s) {
        Stack<Character> stack=new Stack<>();//注意，java中Stack类型必需时包装类，int需使用Interger，char需使用Character.
        char ch;
        for(int i=0;i<s.length();i++){
            ch=s.charAt(i);
            if(ch=='('){
                stack.push(')');
            }else if(ch=='{'){
                stack.push('}');
            }else if(ch=='['){
                stack.push(']');
            }else if(stack.empty() ||stack.peek()!=ch){   //括号不匹配的情况
                return false;
            }else{                                          //括号匹配则出栈
                stack.pop();
            }
        }
        return stack.isEmpty();                             //如果最后栈为空则，则返回true，否则返回false
    }
}
```

这里也可以使用哈希表

```java
class Solution {
    public boolean isValid(String s) {

        Stack<Character> stack = new Stack<>();
        Map<Character, Character> map = new HashMap<Character, Character>() {
            {
                put('}', '{');
                put(']', '[');
                put(')', '(');
            }
        };

        for (Character c : s.toCharArray()) {               // 顺序读取字符
            if (!stack.isEmpty() && map.containsKey(c)) {   // 是右括号 && 栈不为空
                if (stack.peek() == map.get(c)) {               // 取其对应的左括号直接和栈顶比
                    stack.pop();                                // 相同则抵消，出栈
                } else {        
                    return false;                               // 不同则直接返回
                }
            } else {                                
                stack.push(c);                              // 左括号，直接入栈
            }
        }
        return stack.isEmpty();                             // 看左右是否抵消完
    }
}
```