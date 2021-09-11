## 编号494：目标和

给你一个整数数组 nums 和一个整数 target 。

向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 **表达式** ：

例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
返回可以通过上述方法构造的、运算结果等于 target 的不同 **表达式** 的数目。

 

示例 1：
```
输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有 5 种方法让最终目标和为 3 。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
```
示例 2：
```
输入：nums = [1], target = 1
输出：1
```
提示：

* 1 <= nums.length <= 20
* 0 <= nums[i] <= 1000
* 0 <= sum(nums[i]) <= 1000
* -1000 <= target <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/target-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
第一眼看去又是回溯的问题，此时可以套组合总和的回溯法代码。

当然它超时了！！

不过为了复习，先把回溯法先写一遍：

```c++
class Solution{
    private:
        vector<vector<int>> result;
        vector<int> path;
        void backTracking(vector<int>& candidates, int target, int sum, int startIndex){
            if(sum == target){
                result.push_back(path);
            }
            //如果sum + candidates[i] > target 就终止遍历
            for(int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++){
                sum += candidates[i];
                path.push_back(candidates[i]);
                backTracking(candidates, target, sum, i + 1);
                sum -= candidats[i];//回溯
                path.pop_back();//回溯
            }
        }
    public:
        int findTargetSumWays(vector<int>& nums, int S){
            int sum = 0;
            for(int i = 0; i < nums.size(); i++) sum += nums[i];
            if(S > sum) return 0;//此时没有方案
            if((S + sum) % 2) return 0;//此时没有方案，两个int相加的时候要各位小心数值溢出的问题
            int bigSize = (S + sum) / 2;//转变为组合总和问题，bigsize就是要求的和

            //回溯法代码
            result.clear();
            path.clear();
            sort(nums.begin(), nums.end());//需要排序
            backTracking(nums, bagSize, 0, 0);
            return result.size();
        }
};
```

## 动态规划
如何转化为01背包问题呢。

假设加法的总和为x，那么减法对应的总和就是sum - x。

所以我们要求的是 x - (sum - x) = S

x = (S + sum) / 2

**此时问题就转化为，装满容量为x背包，有几种方法。**

看到(S + sum) / 2 应该担心计算的过程中向下取整有没有影响。

这么担心就对了，例如sum 是5，S是2的话其实就是无解的，所以：
```c++
if((sum + S) % 2 == 1) return 0;//此时没有方案
```
同时如果S的绝对值已经大于sum，那么也是没有方案的
```c++
if(abs(S) > sum) return 0;//此时没有方案
```
再回归到01背包问题

因为每个物品（题目中的1）只用一次！

这次和之前遇到的背包问题不一样了，之前都是求容量为j的背包，最多能装多少。

本题则是装满有几种方法。其实这就是一个组合问题了。

1.确定dp数组以及下标的含义

dp[j] 表示：填满j（包括j）这么大容积的包，有dp[i]种方法

其实也可以使用二维dp数组来求解本题，dp[i][j]：使用 下标为[0, i]的nums[i]能够凑满j（包括j）这么大容量的包，有dp[i][j]种方法。

2.确定递推公式

有哪些来源可以推出dp[j]呢？

不考虑nums[i]的情况下，填满容量为j - nums[i]的背包，有dp[j - nums[i]]种方法。

那么只要搞到nums[i]的话，凑成dp[j]就有dp[j - nums[i]] 种方法。

举一个例子,nums[i] = 2： dp[3]，填满背包容量为3的话，有dp[3]种方法。

那么只需要搞到一个2（nums[i]），有dp[3]方法可以凑齐容量为3的背包，相应的就有多少种方法可以凑齐容量为5的背包。

**那么需要把 这些方法累加起来就可以了，dp[j] += dp[j - nums[i]]**

所以求组合类问题的公式，都是类似这种：
```c++
dp[j] += dp[j - nums[i]]
```
这个公式在后面在讲解背包解决排列组合问题的时候还会用到！

3.dp数组如何初始化

从递归公式可以看出，在初始化的时候dp[0] 一定要初始化为1，因为dp[0]是在公式中一切递推结果的起源，如果dp[0]是0的话，递归结果将都是0。

dp[0] = 1，理论上也很好解释，装满容量为0的背包，有1种方法，就是装0件物品。

dp[j]其他下标对应的数值应该初始化为0，从递归公式也可以看出，dp[j]要保证是0的初始值，才能正确的由dp[j - nums[i]]推导出来。

4.确定遍历顺序

在[动态规划：关于01背包问题，你该了解这些！（滚动数组）](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/%E5%85%B3%E4%BA%8E01%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%EF%BC%88%E6%BB%9A%E5%8A%A8%E6%95%B0%E7%BB%84%EF%BC%89.md)中已经做过，nums放在外循环，target在内循环，且内循环倒序。

5.举例推导dp数组

输入：nums: [1, 1, 1, 1, 1], S: 3

bagSize = (S + sum) / 2 = (3 + 5) / 2 = 4

dp数组状态变化如下：
![avater](https://camo.githubusercontent.com/e60424c50d31d323b52dae75063b7dce3ed98a62c583cdde8852197cffff3e02/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132353132303734333237342e6a7067)


c++代码如下：
```c++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for(int i = 0; i < nums.size(); i++){
            sum += nums[i];
        }
        if(abs(target) > sum) return 0;//此时没有方案
        if((target + sum) % 2 == 1) return 0;//此时没有方案
        int bagSize = (target + sum) / 2;
        vector<int> dp(bagSize + 1, 0);
        dp[0] = 1;
        for(int i = 0; i < nums.size(); i++){
            for(int j = bagSize; j >= nums[i]; j--){
                dp[j] +=dp[j - nums[i]];
            }
        }
        return dp[bagSize];
    }
};
```