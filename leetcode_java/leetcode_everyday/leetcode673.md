## 编号673：最长递增子序列的个数

给定一个未排序的整数数组，找到最长递增子序列的个数。

示例 1:
```
输入: [1,3,5,4,7]
输出: 2
解释: 有两个最长递增子序列，分别是 [1, 3, 4, 7] 和[1, 3, 5, 7]。
```
示例 2:
```
输入: [2,2,2,2,2]
输出: 5
解释: 最长递增子序列的长度是1，并且存在5个子序列的长度为1，因此输出5。
注意: 给定的数组长度不超过 2000 并且结果一定是32位有符号整数。
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

这道题可以说是[300.最长上升子序列](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode300.md)的进阶版本

确定dp数组（dp table）以及下标的含义
这道题目我们要一起维护两个数组。

dp[i]：i之前（包括i）最长递增子序列的长度为dp[i]

count[i]：以nums[i]为结尾的字符串，最长递增子序列的个数为count[i]

1.确定递推公式

在[300.最长上升子序列](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode300.md)中，我们给出的状态转移是：

```c++
if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
```

即：位置i的最长递增子序列长度 等于j从0到i-1各个位置的最长升序子序列 + 1的最大值。

本题就没那么简单了，我们要考虑两个维度，一个是dp[i]的更新，一个是count[i]的更新。

那么如何更新count[i]呢？

以nums[i]为结尾的字符串，最长递增子序列的个数为count[i]。

**那么在nums[i] > nums[j]前提下，如果在[0, i-1]的范围内，找到了j，使得dp[j] + 1 > dp[i]，说明找到了一个更长的递增子序列。**

<span style = "color:green">那么以j为结尾的子串的最长递增子序列的个数，就是最新的以i为结尾的子串的最长递增子序列的个数，即：count[i] = count[j]。</span>

在nums[i] > nums[j]前提下，如果在[0, i-1]的范围内，找到了j，使得dp[j] + 1 == dp[i]，说明找到了两个相同长度的递增子序列。

那么以i为结尾的子串的最长递增子序列的个数 就应该加上以j为结尾的子串的最长递增子序列的个数，即：count[i] += count[j];

代码如下：
```c++
if (nums[i] > nums[j]) {
    if (dp[j] + 1 > dp[i]) {
        count[i] = count[j];
    } else if (dp[j] + 1 == dp[i]) {
        count[i] += count[j];
    }
    dp[i] = max(dp[i], dp[j] + 1);
}
```
当然也可以这么写：
```c++
if (nums[i] > nums[j]) {
    if (dp[j] + 1 > dp[i]) {
        dp[i] = dp[j] + 1; // 更新dp[i]放在这里，就不用max了
        count[i] = count[j];
    } else if (dp[j] + 1 == dp[i]) {
        count[i] += count[j];
    }
}
```
这里count[i]记录了以nums[i]为结尾的字符串，最长递增子序列的个数。dp[i]记录了i之前（包括i）最长递增序列的长度。

题目要求最长递增序列的长度的个数，我们应该把最长长度记录下来。

代码如下：
```c++
for (int i = 1; i < nums.size(); i++) {
    for (int j = 0; j < i; j++) {
        if (nums[i] > nums[j]) {
            if (dp[j] + 1 > dp[i]) {
                count[i] = count[j];
            } else if (dp[j] + 1 == dp[i]) {
                count[i] += count[j];
            }
            dp[i] = max(dp[i], dp[j] + 1);
        }
        if (dp[i] > maxCount) maxCount = dp[i]; // 记录最长长度
    }
}
```

3.dp数组如何初始化

再回顾一下dp[i]和count[i]的定义

count[i]记录了以nums[i]为结尾的字符串，最长递增子序列的个数。

那么最少也就是1个，所以count[i]初始为1。

dp[i]记录了i之前（包括i）最长递增序列的长度。

最小的长度也是1，所以dp[i]初始为1。

代码如下：
```c++
vector<int> dp(nums.size(), 1);
vector<int> count(nums.size(), 1);
```
其实动规的题目中，初始化很有讲究，也很考察对dp数组定义的理解。

4.确定遍历顺序

dp[i] 是由0到i-1各个位置的最长升序子序列 推导而来，那么遍历i一定是从前向后遍历。

j其实就是0到i-1，遍历i的循环里外层，遍历j则在内层，代码如下：
```c++
for (int i = 1; i < nums.size(); i++) {
    for (int j = 0; j < i; j++) {
        if (nums[i] > nums[j]) {
            if (dp[j] + 1 > dp[i]) {
                count[i] = count[j];
            } else if (dp[j] + 1 == dp[i]) {
                count[i] += count[j];
            }
            dp[i] = max(dp[i], dp[j] + 1);
        }
        if (dp[i] > maxCount) maxCount = dp[i];
    }
}
```
最后还有再遍历一遍dp[i]，把最长递增序列长度对应的count[i]累计下来就是结果了。

代码如下：
```c++
for (int i = 1; i < nums.size(); i++) {
    for (int j = 0; j < i; j++) {
        if (nums[i] > nums[j]) {
            if (dp[j] + 1 > dp[i]) {
                count[i] = count[j];
            } else if (dp[j] + 1 == dp[i]) {
                count[i] += count[j];
            }
            dp[i] = max(dp[i], dp[j] + 1);
        }
        if (dp[i] > maxCount) maxCount = dp[i];
    }
}
int result = 0; // 统计结果
for (int i = 0; i < nums.size(); i++) {
    if (maxCount == dp[i]) result += count[i];
}
```
统计结果，可能有的同学又有点看懵了，那么就再回顾一下dp[i]和count[i]的定义。

5.举例推导dp数组

输入：[1,3,5,4,7]

![avater](https://camo.githubusercontent.com/1d151d9ea2a5aa1df221417e34376cf927e5d129aed5619474f2abfb03a6ce49/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303131323130343535353233342e6a7067)

**如果代码写出来了，怎么改都通过不了，那么把dp和count打印出来看看对不对！**

以上分析完毕，C++整体代码如下：

```c++
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        vector<int> dp(nums.size(), 1);
        vector<int> count(nums.size(), 1);
        int maxCount = 0;
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        count[i] = count[j];
                    } else if (dp[j] + 1 == dp[i]) {
                        count[i] += count[j];
                    }
                }
                if (dp[i] > maxCount) maxCount = dp[i];
            }
        }
        int result = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (maxCount == dp[i]) result += count[i];
        }
        return result;
    }
};
```