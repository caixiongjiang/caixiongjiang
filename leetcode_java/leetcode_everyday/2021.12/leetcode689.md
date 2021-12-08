## 编号689:三个无重叠子数组的最大和

给你一个整数数组 nums 和一个整数 k ，找出三个长度为 k 、互不重叠、且 3 * k 项的和最大的子数组，并返回这三个子数组。

以下标的数组形式返回结果，数组中的每一项分别指示每个子数组的起始位置（下标从 0 开始）。如果有多个结果，返回字典序最小的一个。

 

示例 1：
```
输入：nums = [1,2,1,2,6,7,5,1], k = 2
输出：[0,3,5]
解释：子数组 [1, 2], [2, 6], [7, 5] 对应的起始下标为 [0, 3, 5]。
也可以取 [2, 1], 但是结果 [1, 3, 5] 在字典序上更大。
```
示例 2：
```
输入：nums = [1,2,1,2,1,2,1,2,1], k = 2
输出：[0,2,4] 
```
提示：

* 1 <= nums.length <= 2 * 104
* 1 <= nums[i] < 216
* 1 <= k <= floor(nums.length / 3)


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-sum-of-3-non-overlapping-subarrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

要计算三个无重叠子数组的最大和，我们可以枚举第三个子数组的位置，同时维护前两个无重叠子数组的最大和及其位置。

要计算两个无重叠子数组的最大和，我们可以枚举第二个子数组的位置，同时维护第一个子数组的最大和及其位置。

因此，我们首先来解决单个子数组的最大和问题，然后解决两个无重叠子数组的最大和问题，最后解决三个无重叠子数组的最大和问题。

### 滑动窗口
#### 单个子数组的最大和

设sum 1为大小为 k 的窗口的元素和，当窗口从[i-k+1,i]向右滑动1个元素后，sum1增加了nums[i+1]，减少了nums[i−k+1]。据此我们可以 O(1) 地计算出向右滑动 1 个元素后的窗口的元素和。

我们从 [0,k-1]开始，不断地向右滑动窗口，直至窗口右端点到达数组末尾时停止。统计这一过程中的sum1的最大值记作maxSum1及其对应位置。

代码如下：
```c++
class Solution {
public:
    vector<int> maxSumOfOneSubarray(vector<int> &nums, int k) {
        vector<int> ans;
        int sum1 = 0, maxSum1 = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum1 += nums[i];
            if (i >= k - 1) {
                if (sum1 > maxSum1) {
                    maxSum1 = sum1;
                    ans = {i - k + 1};
                }
                sum1 -= nums[i - k + 1];
            }
        }
        return ans;
    }
};
```
#### 两个无重叠子数组的最大和

我们使用两个大小为 k 的滑动窗口。设sum1为第一个滑动窗口的元素和，该滑动窗口从[0,k-1]开始；sum2为第二个滑动窗口的元素和，该滑动窗口从[k,2k−1]开始。

我们同时向右滑动这两个窗口，并维护sum1的最大值maxSum1及其对应位置。每次滑动时，计算当前maxSum1与sum2之和。统计这一过程中的maxSum1+sum2的最大值（记作 maxSum12）及其对应位置。

代码如下：
```c++
class Solution {
public:
    vector<int> maxSumOfTwoSubarrays(vector<int> &nums, int k) {
        vector<int> ans;
        int sum1 = 0, maxSum1 = 0, maxSum1Idx = 0;
        int sum2 = 0, maxSum12 = 0;
        for (int i = k; i < nums.size(); ++i) {
            sum1 += nums[i - k];
            sum2 += nums[i];
            if (i >= k * 2 - 1) {
                if (sum1 > maxSum1) {
                    maxSum1 = sum1;
                    maxSum1Idx = i - k * 2 + 1;
                }
                if (maxSum1 + sum2 > maxSum12) {
                    maxSum12 = maxSum1 + sum2;
                    ans = {maxSum1Idx, i - k + 1};
                }
                sum1 -= nums[i - k * 2 + 1];
                sum2 -= nums[i - k + 1];
            }
        }
        return ans;
    }
};
```

#### 三个无重叠子数组的最大和

回到本题，我们使用三个大小为k的滑动窗口。设sum1为第一个滑动窗口的元素和，该滑动窗口从 [0,k−1] 开始sum 2为第二个滑动窗口的元素和，该滑动窗口从[k,2k-1]开始;sum3为第三个滑动窗口的元素和，该滑动窗口从 [2k,3k−1] 开始。

我们同时向右滑动这三个窗口，按照前文介绍的方法并维护maxSum12及其对应位置。每次滑动时，计算当前maxSum12与sum3之和。统计这一过程中的maxSum12+sum3的最大值及其对应位置。

**对于题目要求的最小字典序，由于我们是从左向右遍历的，并且仅当元素和超过最大元素和时才修改最大元素和，从而保证求出来的下标列表是字典序最小的。**

代码如下：
```c++

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int> &nums, int k) {
        vector<int> ans;
        int sum1 = 0, maxSum1 = 0, maxSum1Idx = 0;
        int sum2 = 0, maxSum12 = 0, maxSum12Idx1 = 0, maxSum12Idx2 = 0;
        int sum3 = 0, maxTotal = 0;
        for (int i = k * 2; i < nums.size(); ++i) {
            sum1 += nums[i - k * 2];
            sum2 += nums[i - k];
            sum3 += nums[i];
            if (i >= k * 3 - 1) {
                if (sum1 > maxSum1) {
                    maxSum1 = sum1;
                    maxSum1Idx = i - k * 3 + 1;
                }
                if (maxSum1 + sum2 > maxSum12) {
                    maxSum12 = maxSum1 + sum2;
                    maxSum12Idx1 = maxSum1Idx;
                    maxSum12Idx2 = i - k * 2 + 1;
                }
                if (maxSum12 + sum3 > maxTotal) {
                    maxTotal = maxSum12 + sum3;
                    ans = {maxSum12Idx1, maxSum12Idx2, i - k + 1};
                }
                sum1 -= nums[i - k * 3 + 1];
                sum2 -= nums[i - k * 2 + 1];
                sum3 -= nums[i - k + 1];
            }
        }
        return ans;
    }
};
```