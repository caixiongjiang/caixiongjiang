## 编号343：整数拆分
给定一个正整数 n，将其拆分为**至少**两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。

示例 1:
```
输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。
```
示例 2:
```
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。
```
**说明**: 你可以假设 n 不小于 2 且不大于 58。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/integer-break
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
这道题目主要的思考点在于会把这个整数拆分为几个。

## 动态规划
动态规划五部曲：

1.确定dp数组（dp table）以及下标的含义

dp[i]：分拆数字i，可以得到的最大乘积为dp[i]。


2.确定递推公式

可以想 dp[i]最大乘积是怎么得到的呢？

其实可以从1遍历j，然后有两种渠道得到dp[i].

一个是j * (i - j) 直接相乘。

<span style="color:green">一个是j * dp[i - j]，相当于是拆分(i - j)，对这个拆分不理解的话，可以回想dp数组的定义。</span>

**j为什么不拆分呢?**

j是从1开始遍历，拆分j的情况，在遍历j的过程中其实都计算过了。那么从1遍历j，比较(i - j) * j和dp[i - j] * j 取最大的。递推公式：dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));

也可以这么理解，j * (i - j) 是单纯的把整数拆分为两个数相乘，而j * dp[i - j]是拆分成两个以及两个以上的个数相乘。

如果定义dp[i - j] * dp[j] 也是默认将一个数强制拆成4份以及4份以上了。

所以递推公式：dp[i] = max({dp[i], (i - j) * j, dp[i - j] * j});

那么在取最大值的时候，为什么还要比较dp[i]呢？

因为在递推公式推导的过程中，每次计算dp[i],取最大的而已。

3.dp的初始化

拆分0和拆分1的最大乘积是多少？

这是无解的。

这里只初始化dp[2]=1，从dp[i]的定义来说，拆分数字2，得到的最大乘积是1。

4.确定遍历顺序

确定遍历顺序，先来看看递归公式：dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));

dp[i] 是依靠 dp[i - j]的状态，所以遍历i一定是从前向后遍历，先有dp[i - j]再有dp[i]。

**枚举j的时候，是从1开始的。i是从3开始，这样dp[i - j]就是dp[2]正好可以通过我们初始化的数值求出来。**

所以遍历顺序为：
```java
for(int i = 3; i <= n; i++){
    for(int j = 1; j < i - 1; j++){
        dp[i] = Math.max((i - j) * j, dp[i - j] * j);
    }
}
```

5.举例推导dp数组

举例当n为10的时候，dp数组里的数值，如下：
![avater](https://camo.githubusercontent.com/aa18a7a6ad2120e38d5b980b46c390e1e0550da8309573eef0a5eaf84f77ab13/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303130343137333032313538312e706e67)

整体代码如下：
```java
class Solution {
    public int integerBreak(int n) {
        //dp[i]为正整数i拆分结果的最大乘积
        int[] dp = new int[n + 1];
        dp[2] = 1;
        for(int i = 3; i <= n; i++){
            for(int j = 0; j < i - 1; j++){
                //j*(i - j)代表把i拆分成j和i-j两个数相乘
                //j*dp[i - j]代表把i拆分成j和继续把(i - j)这个数拆分，取(i - j)拆分结果中的最大乘积和j相乘。
                dp[i] = Math.max(dp[i], Math.max(j * (i - j), j * dp[i - j]));
            }
        }
        return dp[n];
    }
}
```