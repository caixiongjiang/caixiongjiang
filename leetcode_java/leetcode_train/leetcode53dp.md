## 编号53：最大子序和（动态规划）

给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

 

示例 1：
```
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
```
示例 2：
```
输入：nums = [1]
输出：1
```
示例 3：
```
输入：nums = [0]
输出：0
```
示例 4：
```
输入：nums = [-1]
输出：-1
```
示例 5：
```
输入：nums = [-100000]
输出：-100000 
```
提示：

* 1 <= nums.length <= 3 * 104
* -105 <= nums[i] <= 105

**进阶**：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的**分治法** 求解。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-subarray
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

动规五部曲如下：

1.确定dp数组（dp table）以及下标的含义

dp[i]：包括下标i之前的最大连续子序列和为dp[i]。

2.确定递推公式

dp[i]只有两个方向可以推出来：

* dp[i - 1] + nums[i]，即：nums[i]加入当前连续子序列和
* nums[i]，即：<span style="color:green">从头开始计算当前连续子序列和</span>
一定是取最大的，所以dp[i] = max(dp[i - 1] + nums[i], nums[i]);

3.dp数组如何初始化

从递推公式可以看出来dp[i]是依赖于dp[i - 1]的状态，dp[0]就是递推公式的基础。

dp[0]应该是多少呢?

更具dp[i]的定义，很明显dp[0]因为为nums[0]即dp[0] = nums[0]。

4.确定遍历顺序

递推公式中dp[i]依赖于dp[i - 1]的状态，需要从前向后遍历。

5.举例推导dp数组

以示例一为例，输入：nums = [-2,1,-3,4,-1,2,1,-5,4]，对应的dp状态如下：
![avater](https://camo.githubusercontent.com/3eab8becf49c18bab63e9d87628d0097197ca8ff25f9a3596fe7fb3fc44030be/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303330333130343132393130312e706e67)

**注意最后的结果可不是dp[nums.size() - 1]！ ，而是dp[6]。**

在回顾一下dp[i]的定义：包括下标i之前的最大连续子序列和为dp[i]。

那么我们要找最大的连续子序列，就应该找每一个i为终点的连续最大子序列。

所以在递推公式的时候，可以直接选出最大的dp[i]。

整体代码如下：
```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        int result = dp[0];
        for(int i = 1; i < nums.size(); i++){
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);//状态转移公式
            if(dp[i] > result) result = dp[i];
        } 
        return result;
    }
};
```