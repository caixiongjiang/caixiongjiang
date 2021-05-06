## 剑指Offer58Ⅱ：左旋字符串

字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。

 

示例 1：
```
输入: s = "abcdefg", k = 2
输出: "cdefgab"
```
示例 2：
```
输入: s = "lrloseumgh", k = 6
输出: "umghlrlose"
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
#### 方法一
此题看上去很简单，一般会先想到使用额外的数组空间，按题目所要求的顺序重新写入数组。

#### 方法二

为了让本题更有意义，提升一下本题难度：<span style="color:green">*不能申请额外空间，只能在本串上操作。*</span>
<span style="color:pink">使用整体反转+局部反转就可以实现，反转单词顺序的目的。</span>

这道题目也非常类似，依然可以通过局部反转+整体反转 达到左旋转的目的。
具体步骤为：

反转区间为前n的子串
反转区间为n到末尾的子串
反转整个字符串
最后就可以得到左旋n的目的，而不用定义新的字符串，完全在本串上操作。

例如 ：示例1中 输入：字符串abcdefg，n=2

![avater](https://camo.githubusercontent.com/180542168b66ce8aed12460261519362b7183e7f578adbefe44797eb99b0893f/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f2545352538392539312545362538432538374f6666657235382d49492e2545352542372541362545362539372538422545382542442541432545352541442539372545372541432541362545342542382542322e706e67)


c++代码：

```c++
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        reverse(s.begin(), s.begin() + n);
        reverse(s.begin() + n, s.end());
        reverse(s.begin(), s.end());
        return s;
    }
};
```

java代码：

```java
class Solution {
    public void reverse(char[] s,int start,int end){
        char tmp=0;
        for(;start<end;start++,end--){
            tmp=s[start];
            s[start]=s[end];
            s[end]=tmp;
        }
    }
    public String reverseLeftWords(String s, int n) {
        char[] ch=s.toCharArray();
        reverse(ch,0,n-1);
        reverse(ch,n,ch.length-1);
        reverse(ch,0,ch.length-1);
        String res=new String(ch);
        return res;
    }
}
```