## 最长回文子序列

给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。

子序列定义为：**不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。**

 

示例 1：
```
输入：s = "bbbab"
输出：4
解释：一个可能的最长回文子序列为 "bbbb" 。
```
示例 2：
```
输入：s = "cbbd"
输出：2
解释：一个可能的最长回文子序列为 "bb" 。 
```
提示：

* 1 <= s.length <= 1000
* s 仅由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-palindromic-subsequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

我们刚刚做过了[动态规划：回文子串](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode647.md)，求的是回文子串，而本题要求的是回文子序列， 要搞清楚这两者之间的区别。

**回文子串是要连续的，回文子序列可不是连续的！** 回文子串，回文子序列都是动态规划经典题目。

回文子串，可以做这两题：

* 647.回文子串
* 5.最长回文子串

动规五部曲分析如下：

1.确定dp数组（dp table）以及下标的含义

dp[i][j]：字符串s在[i, j]范围内最长的回文子序列的长度为dp[i][j]。

2.确定递推公式

在判断回文子串的题目中，关键逻辑就是看s[i]与s[j]是否相同。

如果s[i]与s[j]相同，那么dp[i][j] = dp[i + 1][j - 1] + 2;

如图：
![avater](https://camo.githubusercontent.com/26c1690292f01e432c840c87dbeb7f5cd1dc27bf2ed5ef6223708db158e7424a/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132373135313335303536332e6a7067)

如果s[i]与s[j]不相同，说明s[i]和s[j]的同时加入 并不能增加[i,j]区间回文子串的长度，那么分别加入s[i]、s[j]看看哪一个可以组成最长的回文子序列。

加入s[j]的回文子序列长度为dp[i + 1][j]。

加入s[i]的回文子序列长度为dp[i][j - 1]。

那么dp[i][j]一定是取最大的，即：dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);

![avater](https://camo.githubusercontent.com/c599f773ad7ef3a496edc1831b98fdcf06f0e99eabc41031d43f570c658dcc72/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132373135313432303437362e6a7067)

代码如下：
```c++
if (s[i] == s[j]) {
    dp[i][j] = dp[i + 1][j - 1] + 2;
} else {
    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
}
```

3.dp数组如何初始化

首先要考虑当i 和j 相同的情况，从递推公式：dp[i][j] = dp[i + 1][j - 1] + 2; 可以看出 递推公式是计算不到 i 和j相同时候的情况。

**所以需要手动初始化一下，当i与j相同，那么dp[i][j]一定是等于1的，即：一个字符的回文子序列长度就是1。**

其他情况dp[i][j]初始为0就行，这样递推公式：dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]); 中dp[i][j]才不会被初始值覆盖。
```c++
vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
for (int i = 0; i < s.size(); i++) dp[i][i] = 1;
```
4.确定遍历顺序

从递推公式dp[i][j] = dp[i + 1][j - 1] + 2 和 dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]) 可以看出，dp[i][j]是依赖于dp[i + 1][j - 1] 和 dp[i + 1][j]，

也就是从矩阵的角度来说，dp[i][j] 下一行的数据。**所以遍历i的时候一定要从下到上遍历，这样才能保证，下一行的数据是经过计算的。**

递推公式：dp[i][j] = dp[i + 1][j - 1] + 2，dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]) 分别对应着下图中的红色箭头方向，如图：
![avater](https://camo.githubusercontent.com/8b10e533b5f06271e76a5169c4a3cda4acd56d97444b61d1d44a8baba8eec071/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132373135313435323939332e6a7067)

代码如下：
```c++
for (int i = s.size() - 1; i >= 0; i--) {
    for (int j = i + 1; j < s.size(); j++) {
        if (s[i] == s[j]) {
            dp[i][j] = dp[i + 1][j - 1] + 2;
        } else {
            dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
}
```
5.举例推导dp数组
输入s:"cbbd" 为例，dp数组状态如图：
![avater](https://camo.githubusercontent.com/2d6c0fc8f91fdca3a1760492e8e3b1f0b0f519fc994c614e7aba3aa4676193c2/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132373135313532313433322e6a7067)

整体代码如下：
```c++
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        //特殊值初始化
        for(int i = 0; i < s.size(); i++) dp[i][i] = 1;
        for(int i = s.size() - 1; i >= 0; i--){//注意遍历顺序
            for(int j = i + 1; j < s.size(); j++){
                if(s[i] == s[j]){
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }else{
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][s.size() - 1];
    }
};
```