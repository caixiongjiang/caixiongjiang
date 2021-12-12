## 编号：子数组范围和(AC)

给你一个整数数组 nums 。nums 中，子数组的 范围 是子数组中最大元素和最小元素的差值。

返回 nums 中 所有 子数组范围的 和 。

子数组是数组中一个连续 非空 的元素序列。

 

示例 1：
```
输入：nums = [1,2,3]
输出：4
解释：nums 的 6 个子数组如下所示：
[1]，范围 = 最大 - 最小 = 1 - 1 = 0 
[2]，范围 = 2 - 2 = 0
[3]，范围 = 3 - 3 = 0
[1,2]，范围 = 2 - 1 = 1
[2,3]，范围 = 3 - 2 = 1
[1,2,3]，范围 = 3 - 1 = 2
所有范围的和是 0 + 0 + 0 + 1 + 1 + 2 = 4
```
示例 2：
```
输入：nums = [1,3,3]
输出：4
解释：nums 的 6 个子数组如下所示：
[1]，范围 = 最大 - 最小 = 1 - 1 = 0
[3]，范围 = 3 - 3 = 0
[3]，范围 = 3 - 3 = 0
[1,3]，范围 = 3 - 1 = 2
[3,3]，范围 = 3 - 3 = 0
[1,3,3]，范围 = 3 - 1 = 2
所有范围的和是 0 + 0 + 0 + 2 + 0 + 2 = 4
```
示例 3：
```
输入：nums = [4,-2,-3,4,1]
输出：59
解释：nums 中所有子数组范围的和是 59 
```
提示：

* 1 <= nums.length <= 1000
* -109 <= nums[i] <= 109

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sum-of-subarray-ranges
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 滑动窗口

具体如何滑动窗口：
* 1.右窗口基于左窗口的位置，在左窗口的右边一个位置，慢慢往右滑动，每滑动一个位置维护当前情况的最大最小的差值。
* 2.遍历完后左窗口向右滑动一个位置，然后再重复上述步骤1。

代码如下：
```c++
class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        int maxval, minval;
        for(int i = 0; i < n; i++){
            maxval = minval = nums[i];
            for(int j = i + 1; j < n; j++){
                maxval = max(maxval, nums[j]);
                minval = min(minval, nums[j]);
                ans += maxval - minval;
            }
        }
        return ans;
    }
};



```
