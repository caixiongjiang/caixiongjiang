## 编号132：分割回文串Ⅱ

给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文。

返回符合要求的**最少分割次数**。

 

示例 1：
```
输入：s = "aab"
输出：1
解释：只需一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。
```
示例 2：
```
输入：s = "a"
输出：0
```
示例 3：
```
输入：s = "ab"
输出：1 
```
**提示：**

* 1 <= s.length <= 2000
* s 仅由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-partitioning-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

动规五部曲分析如下：

1.确定dp数组（dp table）以及下标的含义

dp[i]：范围是[0, i]的回文子串，最少分割次数是dp[i]。

2.确定递推公式

来看一下由什么可以推出dp[i]。

如果要对长度为[0, i]的子串进行分割，分割点为j。

那么如果分割后，区间[j + 1, i]是回文子串，那么dp[i] 就等于 dp[j] + 1。

**这里可能有同学就不明白了，为什么只看[j + 1, i]区间，不看[0, j]区间是不是回文子串呢？**

那么在回顾一下dp[i]的定义： 范围是[0, i]的回文子串，最少分割次数是dp[i]。

[0, j]区间的最小切割数量，我们已经知道了就是dp[j]。

**此时就找到了递推关系，当切割点j在[0, i] 之间时候，dp[i] = dp[j] + 1;**

本题是要找到最少分割次数，所以遍历j的时候要取最小的dp[i]。

所以最后递推公式为：dp[i] = min(dp[i], dp[j] + 1);

<span style="color:green">注意这里不是要 dp[j] + 1 和 dp[i]去比较，而是要在遍历j的过程中取最小的dp[i]！</span>

可以有dp[j] + 1推出，当[j + 1, i] 为回文子串

3.dp数组如何初始化

首先来看一下dp[0]应该是多少。

dp[i]： 范围是[0, i]的回文子串，最少分割次数是dp[i]。

那么dp[0]一定是0，长度为1的字符串最小分割次数就是0。这个是比较直观的。

在看一下非零下标的dp[i]应该初始化为多少？

在递推公式dp[i] = min(dp[i], dp[j] + 1) 中我们可以看出每次要取最小的dp[i]。

**那么非零下标的dp[i]就应该初始化为一个最大数，这样递推公式在计算结果的时候才不会被初始值覆盖！**

如果非零下标的dp[i]初始化为0，在那么在递推公式中，所有数值将都是零。

非零下标的dp[i]初始化为一个最大数。

代码如下：
```c++
vector<int> dp(s.size(), INT_MAX);
dp[0] = 0;
```
其实也可以这样初始化，更具dp[i]的定义，dp[i]的最大值其实就是i，也就是把每个字符分割出来。

所以初始化代码也可以为：
```c++
vector<int> dp(s.size());
for (int i = 0; i < s.size(); i++) dp[i] = i;
```

4.确定遍历顺序

根据递推公式：dp[i] = min(dp[i], dp[j] + 1);

<span style="color:red">j是在[0，i]之间，所以遍历i的for循环一定在外层，这里遍历j的for循环在内层才能通过 计算过的dp[j]数值推导出dp[i]。</span>

代码如下：
```c++
for (int i = 1; i < s.size(); i++) {
    if (isPalindromic[0][i]) { // 判断是不是回文子串
        dp[i] = 0;
        continue;
    }
    for (int j = 0; j < i; j++) {
        if (isPalindromic[j + 1][i]) {
            dp[i] = min(dp[i], dp[j] + 1);
        }
    }
}
```
大家会发现代码里有一个isPalindromic函数，这是一个二维数组isPalindromic[i][j]，记录[i, j]是不是回文子串。

所以先用一个二维数组来保存整个字符串的回文情况。

代码如下：
```c++
vector<vector<bool>> isPalindromic(s.size(), vector<bool>(s.size(), false));
for (int i = s.size() - 1; i >= 0; i--) {
    for (int j = i; j < s.size(); j++) {
        if (s[i] == s[j] && (j - i <= 1 || isPalindromic[i + 1][j - 1])) {
            isPalindromic[i][j] = true;
        }
    }
}
```
5.举例推导dp数组

以输入："aabc" 为例：

![avater](https://camo.githubusercontent.com/8dea3bb96774d001be75fae5f1f73cfd3cb92cdd2723000777988b100b51d731/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132343138323231383834342e6a7067)

整体代码如下：
```c++
class Solution {
public:
    int minCut(string s) {
        vector<vector<bool>> isPalindromic(s.size(), vector<bool>(s.size(), false));
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j] && (j - i <= 1 || isPalindromic[i + 1][j - 1])) {
                    isPalindromic[i][j] = true;
                }
            }
        }
        // 初始化
        vector<int> dp(s.size(), 0);
        for (int i = 0; i < s.size(); i++) dp[i] = i;

        for (int i = 1; i < s.size(); i++) {
            if (isPalindromic[0][i]) {
                dp[i] = 0;
                continue;
            }
            for (int j = 0; j < i; j++) {
                if (isPalindromic[j + 1][i]) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
        return dp[s.size() - 1];
    }
};
```