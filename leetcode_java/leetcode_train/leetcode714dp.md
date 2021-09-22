## 编号714：买卖股票的最佳时机含手续费

给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格 ；整数 fee 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

注意：**这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。**

 

示例 1：
```
输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
输出：8
解释：能够达到的最大利润:  
在此处买入 prices[0] = 1
在此处卖出 prices[3] = 8
在此处买入 prices[4] = 4
在此处卖出 prices[5] = 9
总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8
```
示例 2：
```
输入：prices = [1,3,7,5,10,3], fee = 3
输出：6 
```
提示：

* 1 <= prices.length <= 5 * 104
* 1 <= prices[i] < 5 * 104
* 0 <= fee < 5 * 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

在讲解贪心专题的时候，我们已经讲过本题了[贪心算法：买卖股票的最佳时机含手续费](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode714.md)

使用贪心算法，的性能是：

时间复杂度：O(n)
空间复杂度：O(1)

那么我们再来看看是使用动规的方法如何解题。

相对于[动态规划：122.买卖股票的最佳时机II](ttps://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode122dp.md)，本题只需要在计算卖出操作的时候减去手续费就可以了，代码几乎是一样的。

唯一差别在于递推公式部分

这里重申一下dp数组的含义：

**dp[i][0] 表示第i天持有股票所省最多现金。 dp[i][1] 表示第i天不持有股票所得最多现金**

如果第i天持有股票即dp[i][0]， 那么可以由两个状态推出来

* 第i-1天就持有股票，那么就保持现状，所得现金就是昨天持有股票的所得现金 即：dp[i - 1][0]
* 第i天买入股票，所得现金就是昨天不持有股票的所得现金减去 今天的股票价格 即：dp[i - 1][1] - prices[i]

所以：dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);

在来看看如果第i天不持有股票即dp[i][1]的情况， 依然可以由两个状态推出来

* 第i-1天就不持有股票，那么就保持现状，所得现金就是昨天不持有股票的所得现金 即：dp[i - 1][1]
* 第i天卖出股票，所得现金就是按照今天股票价格卖出后所得现金，注意这里需要有手续费了即：dp[i - 1][0] + prices[i] - fee

所以：dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);

整体代码如下：
```c++
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = -prices[0];
        for(int i = 1; i < n; i++){
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
        }
        return max(dp[n - 1][0], dp[n - 1][1]);
    }
};
```
* 时间复杂度：O（n）
* 空间复杂度：O（n）