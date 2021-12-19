## 编号：找到和最大的长度为 K 的子序列(×)

给你一个整数数组 nums 和一个整数 k 。你需要找到 nums 中长度为 k 的 子序列 ，且这个子序列的 和最大 。

请你返回 任意 一个长度为 k 的整数子序列。

子序列 定义为从一个数组里删除一些元素后，不改变剩下元素的顺序得到的数组。

 

示例 1：
```
输入：nums = [2,1,3,3], k = 2
输出：[3,3]
解释：
子序列有最大和：3 + 3 = 6 。
```
示例 2：
```
输入：nums = [-1,-2,3,4], k = 3
输出：[-1,3,4]
解释：
子序列有最大和：-1 + 3 + 4 = 6 。
```
示例 3：
```
输入：nums = [3,4,3,3], k = 2
输出：[3,4]
解释：
子序列有最大和：3 + 4 = 7 。
另一个可行的子序列为 [4, 3] 。
```
提示：

* 1 <= nums.length <= 1000
* -105 <= nums[i] <= 105
* 1 <= k <= nums.length

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-subsequence-of-length-k-with-the-largest-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

数组 nums 中和最大的长度为 K 的子序列一定是由 nums 中最大的 K 个数组成的。为了使得排序寻找最大的 K 个数后，还能按照它们在原数组 nums 中的顺序组成目标子序列，我们建立辅助数组 vals，它的第 i 个元素 (i,nums[i]) 包含下标 i 本身，以及数组中的对应数值 nums[i]。

首先，我们将辅助数组按照原数组中的数值 nums[i] 为关键字降序排序，排序后的前 K 个元素对应原数组的数值即为原数组 nums 中最大的 K 个数，对应的下标即为它们在 nums 中的下标。随后，我们将这 K 个元素按照下标 i 为关键字升序排序，排序后的 K 个数值保持了它们在原数组中的顺序，我们用新的数组顺序记录这些数值，该数组即为 nums 中和最大的长度为 K 的子序列。我们返回该数组作为答案。

代码如下：
```c++
class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        int n = nums.size();
        vector<pair<int, int>> vals;
        for(int i = 0; i < n; i++){
            vals.emplace_back(i, nums[i]);
        }
        //按照值进行降序排序
        sort(vals.begin(), vals.end(), [&](auto x1, auto x2) {
            return x1.second > x2.second;
        });
        //取前k个并按照下标进行升序排序
        sort(vals.begin(), vals.begin() + k);
        vector<int> res;//目标子序列
        for(int i = 0; i < k; i++){
            res.push_back(vals[i].second);
        }
        return res;
    }
};

```