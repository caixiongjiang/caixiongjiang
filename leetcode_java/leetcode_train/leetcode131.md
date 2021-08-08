## 编号131：分割回文串
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。

回文串 是正着读和反着读都一样的字符串。

 

示例 1：
```
输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]
```
示例 2：
```
输入：s = "a"
输出：[["a"]] 
```
提示：

* 1 <= s.length <= 16
* s 仅由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-partitioning
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
本题这涉及到两个关键问题：

1.切割问题，有不同的切割方式
</br>2.判断回文

<span style="color:green">回溯到底如何切割字符串呢？</span>
例如对于字符串abcdef：

* 组合问题：选取一个a之后，在bcdef中再去选取第二个，选取b之后在cdef中在选组第三个.....。
* 切割问题：切割一个a之后，在bcdef中再去切割第二段，切割b之后在cdef中在切割第三段.....。

所以切割问题，也可以抽象为一颗树形结构，如图：
![avater](https://camo.githubusercontent.com/907a2a94961ed3e0c1b67469e6f51163ce7a044af822069f0983ceccf4c168a2/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3133312e2545352538382538362545352538392542322545352539422539452545362539362538372545342542382542322e6a7067)

**递归用来纵向遍历，for循环用来横向遍历，切割线(图中的红线)切割刀字符串的结尾位置，说明找到了一个切割方法**

## 递归三部曲
* 递归函数参数
全局变量result数组和deque存放切割后的回文子串。
</br>代码如下：

```java
List<List<Integer>> result;
Deque<String> deque;
public void backTracking(String s, int startIndex)
```
* 递归终止条件
![avater](https://camo.githubusercontent.com/907a2a94961ed3e0c1b67469e6f51163ce7a044af822069f0983ceccf4c168a2/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3133312e2545352538382538362545352538392542322545352539422539452545362539362538372545342542382542322e6a7067)

从树形结构的图中可以看出：**切割线切到了字符串最后面，说明找到了一种切割方法，此时就是本层递归的终止终止条件。**

那么在代码里什么是切割线呢？

在处理组合问题的时候，递归参数需要传入startIndex，表示下一轮递归遍历的起始位置，这个startIndex就是切割线。

所以终止条件代码如下：
```java
public void backTracking(String s, int startIndex){
    if(startIndex >= s.length()){
        result.add(new ArrayList<>(deque));
        return;
    }
}
```
* 单层搜索的逻辑
在```for(int i = startIndex; i < s.length(); i++)```循环中，我们 定义了起始位置startIndex，那么 [startIndex, i] 就是要截取的子串。

首先判断这个子串是不是回文，如果是回文，就加入在```Deque<String> deque```中，deque用来记录切割过的回文子串。

代码如下：
```java
for(int i = startIndex; i < s.length(); i++){
    if(isPalindrome(s, startIndex, i)){//是回文子串
        //获取[startIndex,i]在s中的子串
        String str = s.substring(startIndex, i + 1);//表示该字符串的子字符串（从第startIndex个到i个）
        deque.addLast(str);
    }else{
        continue;
    }
        //起始位置后移
        backTracking(s, i + 1);
        deque.removeLast();
    }
}
```

## 判断回文子串
可以使用双指针法，一个指针从前向后，一个指针从后先前，如果前后指针所指向的元素是相等的，就是回文字符串了。
```java
boolean isPalindrome(String s, int start, int end){
    for(int i = start, j = end; i < j; i++, j--){
        if(s.charAt(i) != s.charAt(j)){
            return false;
        }
    }
    return true;
}
```
## 整体代码
```java
class Solution {
    List<List<String>> result = new ArrayList<>();
    Deque<String> deque = new LinkedList<>();

    public List<List<String>> partition(String s) {
        backTracking(s, 0);
        return result;
    }

    public void backTracking(String s, int startIndex){
        if(startIndex >= s.length()){
            result.add(new ArrayList<>(deque));
            return;
        }
        for(int i = startIndex; i < s.length(); i++){
            if(isPalindrome(s, startIndex, i)){//是回文子串
                //获取[startIndex,i]在s中的子串
                String str = s.substring(startIndex, i + 1);//表示该字符串的子字符串（从第startIndex个到i个）
                deque.addLast(str);
            }else{
                continue;
            }
            //起始位置后移
            backTracking(s, i + 1);
            deque.removeLast();
        }
    }
    //用于判断字符串是否为回文串
    boolean isPalindrome(String s, int start, int end){
        for(int i = start, j = end; i < j; i++, j--){
            if(s.charAt(i) != s.charAt(j)){
                return false;
            }
        }
        return true;
    }
}
```