## 编号279：完全平方数

给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。

给你一个整数 n ，返回和为 n 的完全平方数的 最少数量 。

完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。

 

示例 1：
```
输入：n = 12
输出：3 
解释：12 = 4 + 4 + 4
```
示例 2：
```
输入：n = 13
输出：2
解释：13 = 4 + 9
``` 
提示：

* 1 <= n <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/perfect-squares
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

**把题目翻译一下：完全平方数就是物品（可以无限件使用），凑个正整数n就是背包，问凑满这个背包最少有多少物品？**

感受出来了没，这么浓厚的完全背包氛围，而且和题目[动态规划：322. 零钱兑换](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode322.md)就是一样一样的！

动规五部曲分析如下：

1.确定dp数组（dp table）以及下标的含义

dp[i]：和为i的完全平方数的最少数量为dp[i]

2.确定递推公式

dp[j] 可以由dp[j - i * i]推出， dp[j - i * i] + 1 便可以凑成dp[j]。

此时我们要选择最小的dp[j]，所以递推公式：dp[j] = min(dp[j - i * i] + 1, dp[j]);

3.dp数组如何初始化

dp[0]表示 和为0的完全平方数的最小数量，那么dp[0]一定是0。

有同学问题，那0 * 0 也算是一种啊，为啥dp[0] 就是 0呢？

看题目描述，找到若干个完全平方数（比如 1, 4, 9, 16, ...），题目描述中可没说要从0开始，dp[0]=0完全是为了递推公式。

非0下标的dp[j]应该是多少呢？

从递归公式dp[j] = min(dp[j - i * i] + 1, dp[j]);中可以看出每次dp[j]都要选最小的，所以非0下标的dp[i]一定要初始为最大值，这样dp[j]在递推的时候才不会被初始值覆盖。

4.确定遍历顺序

我们知道这是完全背包，

**如果求组合数就是外层for循环遍历物品，内层for遍历背包。**

**如果求排列数就是外层for遍历背包，内层for循环遍历物品。**

所以本题外层for遍历背包，里层for遍历物品，还是外层for遍历物品，内层for遍历背包，都是可以的！

先给出外层遍历背包，里层遍历物品的代码：

```c++
vector<int> dp(n + 1, INT_MAX);
dp[0] = 0;
for (int i = 0; i <= n; i++) { // 遍历背包
    for (int j = 1; j * j <= i; j++) { // 遍历物品
        dp[i] = min(dp[i - j * j] + 1, dp[i]);
    }
}
```
5.举例推导dp数组

已输入n为5例，dp状态图如下：

![avater](https://camo.githubusercontent.com/424531db5a1cb7fb0597630f943f1d32793ff90cb53ce92cc05149875d9f074a/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303230323131323631373334312e6a7067)


整体代码如下：
```c++
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 1; i <=n; i++){//遍历背包
            for(int j = 1; j * j <= i; j++){//遍历物品
                dp[i] = min(dp[i - j * j] + 1,dp[i]);
            }
        }
        return dp[n];
    }
};
```



版本二：

```c++
class Solution{
public:
    int numSquares(int n){
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 1; i * i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(j - i * i >= 0){
                    dp[j] = min(dp[j - i * i] + 1, dp[j]);
                }
            }
        }
        return dp[n];
    }
};
```