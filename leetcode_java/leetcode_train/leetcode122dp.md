## 编号122：买卖股票的最佳时机 II（动态规划）

给定一个数组 prices ，其中 prices[i] 是一支给定股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 

示例 1:
```
输入: prices = [7,1,5,3,6,4]
输出: 7
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。
```
示例 2:
```
输入: prices = [1,2,3,4,5]
输出: 4
解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
```
示例 3:
```
输入: prices = [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。 
```
提示：

* 1 <= prices.length <= 3 * 104
* 0 <= prices[i] <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

**在动规五部曲中，这个区别主要是体现在递推公式上**，其他都和[121. 买卖股票的最佳时机](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode121.md)一样一样的。

所以我们重点讲一讲递推公式。

这里重申一下dp数组的含义：

* dp[i][0] 表示第i天持有股票所得现金。
* dp[i][1] 表示第i天不持有股票所得最多现金
如果第i天持有股票即dp[i][0]， 那么可以由两个状态推出来

* 第i-1天就持有股票，那么就保持现状，所得现金就是昨天持有股票的所得现金 即：dp[i - 1][0]
* 第i天买入股票，所得现金就是昨天不持有股票的所得现金减去 今天的股票价格 即：dp[i - 1][1] - prices[i]
注意这里和[121. 买卖股票的最佳时机](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode121.md)唯一不同的地方，就是推导dp[i][0]的时候，第i天买入股票的情况。

在[121. 买卖股票的最佳时机](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode121.md)中，因为股票全程只能买卖一次，所以如果买入股票，那么第i天持有股票即dp[i][0]一定就是 -prices[i]。

而本题，因为一只股票可以买卖多次，所以当第i天买入股票的时候，所持有的现金可能有之前买卖过的利润。

那么第i天持有股票即dp[i][0]，如果是第i天买入股票，所得现金就是昨天不持有股票的所得现金 减去 今天的股票价格 即：dp[i - 1][1] - prices[i]。

在来看看如果第i天不持有股票即dp[i][1]的情况， 依然可以由两个状态推出来

* 第i-1天就不持有股票，那么就保持现状，所得现金就是昨天不持有股票的所得现金 即：dp[i - 1][1]
* 第i天卖出股票，所得现金就是按照今天股票佳价格卖出后所得现金即：prices[i] + dp[i - 1][0]

代码如下:

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(len, vector<int>(2,0));
        dp[0][0] -= prices[0];
        dp[0][1] = 0;
        for(int i = 1; i < len; i++){
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);//第i天持有股票
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);//第i天不持有股票
        }
        return dp[len - 1][1]; 
    }
};
```
* 时间复杂度：O(n)
* 空间复杂度：O(n)

大家可以本题和[121. 买卖股票的最佳时机](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode121.md)的代码几乎一样，唯一的区别在：

dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
**这正是因为本题的股票可以买卖多次！**所以买入股票的时候，可能会有之前买卖的利润即：dp[i - 1][1]，所以dp[i - 1][1] - prices[i]。

想到到这一点，对这两道题理解的比较深刻了。

这里我依然给出滚动数组的版本，C++代码如下：
```c++
// 版本二
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(2, vector<int>(2)); // 注意这里只开辟了一个2 * 2大小的二维数组
        dp[0][0] -= prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < len; i++) {
            dp[i % 2][0] = max(dp[(i - 1) % 2][0], dp[(i - 1) % 2][1] - prices[i]);
            dp[i % 2][1] = max(dp[(i - 1) % 2][1], prices[i] + dp[(i - 1) % 2][0]);
        }
        return dp[(len - 1) % 2][1];
    }
};
```
* 时间复杂度：O(n)
* 空间复杂度：O(1)