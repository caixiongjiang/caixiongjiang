## 编号05：最长回文子串

给你一个字符串 s，找到 s 中最长的回文子串。

 

示例 1：
```
输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
```
示例 2：
```
输入：s = "cbbd"
输出："bb"
```
示例 3：
```
输入：s = "a"
输出："a"
```
示例 4：
```
输入：s = "ac"
输出："a" 
```
提示：

* 1 <= s.length <= 1000
* s 仅由数字和英文字母（大写和/或小写）组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-palindromic-substring
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 暴力解法
两层for循环，遍历区间起始位置和终止位置，然后判断这个区间是不是回文。

时间复杂度：O(n^3)

## 动态规划

动规五部曲：

1.确定dp数组（dp table）以及下标的含义

布尔类型的dp[i][j]：表示区间范围[i,j] （注意是左闭右闭）的子串是否是回文子串，如果是dp[i][j]为true，否则为false。

2.确定递推公式

在确定递推公式时，就要分析如下几种情况。

整体上是两种，就是s[i]与s[j]相等，s[i]与s[j]不相等这两种。

当s[i]与s[j]不相等，那没啥好说的了，dp[i][j]一定是false。

当s[i]与s[j]相等时，这就复杂一些了，有如下三种情况

* 情况一：下标i 与 j相同，同一个字符例如a，当然是回文子串
* 情况二：下标i 与 j相差为1，例如aa，也是文子串
* 情况三：下标：i 与 j相差大于1的时候，例如cabac，此时s[i]与s[j]已经相同了，我们看i到j区间是不是回文子串就看aba是不是回文就可以了，<span style="color:yellow">那么aba的区间就是 i+1 与 j-1区间，这个区间是不是回文就看dp[i + 1][j - 1]是否为true。</span>

以上三种情况分析完了，那么递归公式如下：
```c++
if (s[i] == s[j]) {
    if (j - i <= 1) { // 情况一 和 情况二
        dp[i][j] = true;
    } else if (dp[i + 1][j - 1]) { // 情况三
        dp[i][j] = true;
    }
}
```
注意这里我没有列出当s[i]与s[j]不相等的时候，因为在下面dp[i][j]初始化的时候，就初始为false。

在得到[i,j]区间是否是回文子串的时候，直接保存最长回文子串的左边界和右边界，代码如下：
```c++
if (s[i] == s[j]) {
    if (j - i <= 1) { // 情况一 和 情况二
        dp[i][j] = true;
    } else if (dp[i + 1][j - 1]) { // 情况三
        dp[i][j] = true;
    }
}
if (dp[i][j] && j - i + 1 > maxlenth) {
    maxlenth = j - i + 1;
    left = i;
    right = j;
}
```

3.dp数组如何初始化

dp[i][j]可以初始化为true么？ 当然不行，怎能刚开始就全都匹配上了。

所以dp[i][j]初始化为false。

4.确定遍历顺序

遍历顺序可有有点讲究了。

首先从递推公式中可以看出，情况三是根据dp[i + 1][j - 1]是否为true，在对dp[i][j]进行赋值true的。

dp[i + 1][j - 1] 在 dp[i][j]的左下角，如图：

![avater](https://camo.githubusercontent.com/9cb222226e85be9b2772d59cbb1c7e1e0f3d263baf96134b8c0661008b56952c/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132313137313033323437332e6a7067)

如果这矩阵是从上到下，从左到右遍历，那么会用到没有计算过的dp[i + 1][j - 1]，也就是根据不确定是不是回文的区间[i+1,j-1]，来判断了[i,j]是不是回文，那结果一定是不对的。

**所以一定要从下到上，从左到右遍历，这样保证dp[i + 1][j - 1]都是经过计算的。**

有的代码实现是优先遍历列，然后遍历行，其实也是一个道理，都是为了保证dp[i + 1][j - 1]都是经过计算的。

代码如下：
```c++
for (int i = s.size() - 1; i >= 0; i--) { // 注意遍历顺序
    for (int j = i; j < s.size(); j++) {
        if (s[i] == s[j]) {
            if (j - i <= 1) { // 情况一 和 情况二
                dp[i][j] = true;
            } else if (dp[i + 1][j - 1]) { // 情况三
                dp[i][j] = true;
            }
        }
        if (dp[i][j] && j - i + 1 > maxlenth) {
            maxlenth = j - i + 1;
            left = i;
            right = j;
        }
    }

}
```

5.举例推导dp数组

举例，输入："aaa"，dp[i][j]状态如下：

![avater](https://camo.githubusercontent.com/6ccc0bab6ea0416fa723e9290cfb0ac19b054bd203fa13d436bea7caf123a203/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132313137313035393935312e6a7067)

**注意因为dp[i][j]的定义，所以j一定是大于等于i的，那么在填充dp[i][j]的时候一定是只填充右上半部分。**

以上分析完毕，C++代码如下：
```c++
class Solution {
public:
    string longestPalindrome(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        int maxlenth = 0;
        int left = 0;
        int right = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j]) {
                    if (j - i <= 1) { // 情况一 和 情况二
                        dp[i][j] = true;
                    } else if (dp[i + 1][j - 1]) { // 情况三
                        dp[i][j] = true;
                    }
                }
                if (dp[i][j] && j - i + 1 > maxlenth) {
                    maxlenth = j - i + 1;
                    left = i;
                    right = j;
                }
            }

        }
        return s.substr(left, right - left + 1);
    }
};
```

以上代码是为了凸显情况一二三，当然是可以简洁一下的，如下：

```c++
class Solution {
public:
    string longestPalindrome(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        int maxlenth = 0;
        int left = 0;
        int right = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j] && (j - i <= 1 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                }
                if (dp[i][j] && j - i + 1 > maxlenth) {
                    maxlenth = j - i + 1;
                    left = i;
                    right = j;
                }
            }
        }
        return s.substr(left, maxlenth);
    }
};
```

## 双指针

动态规划的空间复杂度是偏高的，我们再看一下双指针法。

首先确定回文串，就是找中心然后想两边扩散看是不是对称的就可以了。

在遍历中心点的时候，要注意中心点有两种情况。

一个元素可以作为中心点，两个元素也可以作为中心点。

那么有人同学问了，三个元素还可以做中心点呢。其实三个元素就可以由一个元素左右添加元素得到，四个元素则可以由两个元素左右添加元素得到。

所以我们在计算的时候，要注意一个元素为中心点和两个元素为中心点的情况。

这两种情况可以放在一起计算，但分别计算思路更清晰，我倾向于分别计算，代码如下：
```c++
class Solution {
public:
    int left = 0;
    int right = 0;
    int maxLength = 0;
    string longestPalindrome(string s) {
        int result = 0;
        for (int i = 0; i < s.size(); i++) {
            extend(s, i, i, s.size()); // 以i为中心
            extend(s, i, i + 1, s.size()); // 以i和i+1为中心
        }
        return s.substr(left, maxLength);
    }
    void extend(const string& s, int i, int j, int n) {
        while (i >= 0 && j < n && s[i] == s[j]) {
            if (j - i + 1 > maxLength) {
                left = i;
                right = j;
                maxLength = j - i + 1;
            }
            i--;
            j++;
        }
    }
};
```