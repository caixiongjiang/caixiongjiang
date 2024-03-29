## 编号746：使用最小花费爬楼梯

数组的每个下标作为一个阶梯，第 i 个阶梯对应着一个非负数的体力花费值 cost[i]（下标从 0 开始）。

每当你爬上一个阶梯你都要花费对应的体力值，一旦支付了相应的体力值，你就可以选择向上爬一个阶梯或者爬两个阶梯。

请你找出达到楼层顶部的最低花费。在开始时，你可以选择从下标为 0 或 1 的元素作为初始阶梯。

 

示例 1：
```
输入：cost = [10, 15, 20]
输出：15
解释：最低花费是从 cost[1] 开始，然后走两步即可到阶梯顶，一共花费 15 。 
```
示例 2：
```
输入：cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
输出：6
解释：最低花费方式是从 cost[0] 开始，逐个经过那些 1 ，跳过 cost[3] ，一共花费 6 。 
```
提示：

* cost 的长度范围是 [2, 1000]。
* cost[i] 将会是一个整型数据，范围为 [0, 999] 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/min-cost-climbing-stairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

**注意：每当你爬上一个阶梯你都要花费对应的体力值，一旦支付了相应的体力值，你就可以选择向上爬一个阶梯或者爬两个阶梯。**

</br>

dp五部曲：

1.确定dp数组以及下标的含义
</br>使用动态规划，就要有一个数组来记录状态，本题只需要一个一维数组dp[i]就可以了。

dp[i]的定义：到达第i个台阶所花费的最少体力为dp[i]。（注意这里认为是第一步一定是要花费）

对于dp数组的定义，一定要清晰！

2.确定递推公式
</br>可以有两个途径得到dp[i]，一个是dp[i-1] 一个是dp[i-2]。

那么究竟是选dp[i-1]还是dp[i-2]呢？

**一定是选最小的，所以dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];**

注意这里为什么是加cost[i]，而不是cost[i-1],cost[i-2]之类的，因为题目中说了：每当你爬上一个阶梯你都要花费对应的体力值

3.dp数组如何初始化
</br>根据dp数组的定义，dp数组初始化其实是比较难的，因为不可能初始化为第i台阶所花费的最少体力。

那么看一下递归公式，dp[i]由dp[i-1]，dp[i-2]推出，既然初始化所有的dp[i]是不可能的，那么只初始化dp[0]和dp[1]就够了，其他的最终都是dp[0]dp[1]推出。

所以初始化代码为：
```java
int[] dp = new int[cost.length];
dp[0] = cost[0];
dp[1] = cost[1];
```
4.确定遍历顺序
</br>最后一步，递归公式有了，初始化有了，如何遍历呢？

本题的遍历顺序其实比较简单，简单到很多同学都忽略了思考这一步直接就把代码写出来了。

因为是模拟台阶，而且dp[i]又dp[i-1]dp[i-2]推出，所以是从前到后遍历cost数组就可以了。

**但是稍稍有点难度的动态规划，其遍历顺序并不容易确定下来。**

例如：01背包，都知道两个for循环，一个for遍历物品嵌套一个for遍历背包容量，那么为什么不是一个for遍历背包容量嵌套一个for遍历物品呢？ 以及在使用一维dp数组的时候遍历背包容量为什么要倒叙呢？

这些都是遍历顺序息息相关。

5.举例推导dp数组

拿示例2：cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1] ，来模拟一下dp数组的状态变化，如下：

![avater](https://camo.githubusercontent.com/af385ab256840227455598b45715ad5d5a59df439f6581250f979c342cea6f6a/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032313031303632313336333636392e706e67)

整体代码如下：
```java
class Solution {
    public int minCostClimbingStairs(int[] cost) {
        if(cost == null || cost.length == 0){
            return 0;
        }
        if(cost.length == 1){
            return cost[0];
        }
        int[] dp = new int[cost.length];
        dp[0] = cost[0];
        dp[1] = cost[1];
        for(int i = 2; i < cost.length; i++){
            dp[i] = Math.min(dp[i - 1], dp[i - 2]) + cost[i];
        }
        //最后一步，如果是由倒数第二步爬，则最后一步的体力花费可以不用算。
        return Math.min(dp[cost.length - 1], dp[cost.length - 2]);
    }
}
```