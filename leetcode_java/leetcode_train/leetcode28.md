## 编号28：实现strSTR():KMP算法中的核心

实现 strStr() 函数。

给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回  -1 。

 

说明：

当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与 C 语言的 strstr() 以及 Java 的 indexOf() 定义相符。

 

示例 1：
```
输入：haystack = "hello", needle = "ll"
输出：2
```
示例 2：
```
输入：haystack = "aaaaa", needle = "bba"
输出：-1
```
示例 3：
```
输入：haystack = "", needle = ""
输出：0
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/implement-strstr
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
* [KMP算法的详解(理论篇)](https://www.bilibili.com/video/BV1PD4y1o7nd/)
* [KMP算法的详解(求next数组代码篇)](https://www.bilibili.com/video/BV1M5411j7Xx)

### 什么是KMP算法？
KMP算法也叫模式匹配算法，KMP主要应用在字符串匹配上。

KMP的主要思想是当出现字符串不匹配时，可以知道一部分之前已经匹配的文本内容，可以利用这些信息避免从头再去做匹配了。

所以如何记录已经匹配的文本内容，是KMP的重点，也是next数组肩负的重任。
### 什么是前缀表？
next数组就是一个前缀表（prefix table）。

前缀表有什么作用呢？

<span style="color:yellow">**前缀表是用来回退的，它记录了模式串与主串(文本串)不匹配的时候，模式串应该从哪里开始重新匹配。**</span>

举例：
```
要在文本串：aabaabaafa 中查找是否出现过一个模式串：aabaaf。
```
前缀表的任务是当前位置匹配失败，找到之前已经匹配上的位置，在重新匹配，此也意味着在某个字符失配时，**前缀表会告诉你下一步匹配中，模式串应该跳到哪个位置。**

### 最长公共前后缀
字符串的前缀是指不包含尾字符的所有以首字符开头的连续子串；
</br>后缀是指不包含首字符的所有以尾字符结尾的连续子串。
</br>举例：

```
aabaaf的前缀：a,aa,aab,aaba,aabaa
aabaaf的后缀：f,af,aaf,baaf,abaaf
(前缀表)aabaaf最长相等前后缀的长度 a,0;   
                                aa,1;   
                                aab:0;   
                                aaba,1;   
                                aabaa,2;   
                                aabaaf：0
```
看图：

![avater](https://camo.githubusercontent.com/4538e884e8d97faa1f871654099f471b5f0a57d13e8cc061112eeefb405fd54c/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f4b4d50254537254232254245254538254145254232322e706e67)
</br><span style="color:green">*下标5之前这部分的字符串（也就是字符串aabaa）的最长相等的前缀 和 后缀字符串是 子字符串aa ，因为找到了最长相等的前缀和后缀，匹配失败的位置是后缀子串的后面，那么我们找到与其相同的前缀的后面从新匹配就可以了。*</span>

所以前缀表具有告诉我们当前位置匹配失败，跳到之前已经匹配过的地方的能力。

### next数组
前缀表往右移动一位，然后将第一位变为-1
</br>上述例子即变为-1，0，1，0，1，2
第i个元素不匹配时，next[i]就是模式串要跳的位置。(数组下标从0开始) 

### 使用next数组来匹配
匹配过程：

![avater](https://camo.githubusercontent.com/e3bfb8332e176125704b8a6b63c8b1d07454ed95b855e7229d865f1c03357e43/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f676966732f4b4d50254537254232254245254538254145254232342e676966)

### 构造next数组

构造next数组其实就是计算模式串s，前缀表的过程。 主要有如下三步：

* 初始化
* 处理前后缀不相同的情况
* 处理前后缀相同的情况

```java
public void getNext(int[] next,String s){
    int j = -1;
    next[0] = j;//初始化 j指向前缀末尾为止(还代表前面j-1位字符组成的子串前后缀重合字符数)，i指向后缀末尾位置
    for(int i = 1; i < s.length; i++) { // 注意i从1开始(第二个元素)
        while (j >= 0 && s[i] != s[j + 1]) { // 前后缀不相同了
            j = next[j]; // 向前回退
        }
        if (s[i] == s[j + 1]) { // 找到相同的前后缀
            j++;
        }
        next[i] = j; // 将j（前缀的长度）赋给next[i]
    }
}
```
---
### next数组（整体减一）java实现

```java
class Solution {
    public void getNext(int[] next,String s){
        int j=-1;
        next[0]=j;
        for(int i=1;i<s.length();i++){//注意i从1开始
            while(j>=0 && s.charAt(i)!=s.charAt(j+1)){//前后缀不相同了
                j=next[j];//回退操作
            }
            if(s.charAt(i)==s.charAt(j+1)){
                j++;
            }
            next[i]=j;//将前缀的长度赋给next数组
        }
    }
    public int strStr(String haystack, String needle) {
        if(needle.length()==0){
            return 0;
        }
        int[] next=new int[needle.length()];
        getNext(next,needle);
        int j=-1;
        for(int i=0;i<haystack.length();i++){
            while(j>=0 && haystack.charAt(i)!=needle.charAt(j+1)){
                j=next[j];
            }
            if(haystack.charAt(i)==needle.charAt(j+1)){//匹配时，i和j同时向后移
                j++;//i++在for循环中
            }
            if(j==(needle.length()-1)){//文本串s中出现了模式串
                return (i-needle.length()+1);
            }
        }
        return -1;
    }
}
```


### 前缀表（不减一）java实现

```java
class Solution {
    public int strStr(String haystack, String needle) {
        int n = haystack.length(), m = needle.length();
        if (m == 0) {
            return 0;
        }
        int[] pi = new int[m];
        for (int i = 1, j = 0; i < m; i++) {
            while (j > 0 && needle.charAt(i) != needle.charAt(j)) {
                j = pi[j - 1];
            }
            if (needle.charAt(i) == needle.charAt(j)) {
                j++;
            }
            pi[i] = j;
        }
        for (int i = 0, j = 0; i < n; i++) {
            while (j > 0 && haystack.charAt(i) != needle.charAt(j)) {
                j = pi[j - 1];
            }
            if (haystack.charAt(i) == needle.charAt(j)) {
                j++;
            }
            if (j == m) {
                return i - m + 1;
            }
        }
        return -1;
    }
}
```