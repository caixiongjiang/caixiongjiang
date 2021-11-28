## 编号：半径为 k 的子数组平均值(AC)

给你一个下标从 0 开始的数组 nums ，数组中有 n 个整数，另给你一个整数 k 。

半径为 k 的子数组平均值 是指：nums 中一个以下标 i 为 中心 且 半径 为 k 的子数组中所有元素的平均值，即下标在 i - k 和 i + k 范围（含 i - k 和 i + k）内所有元素的平均值。如果在下标 i 前或后不足 k 个元素，那么 半径为 k 的子数组平均值 是 -1 。

构建并返回一个长度为 n 的数组 avgs ，其中 avgs[i] 是以下标 i 为中心的子数组的 半径为 k 的子数组平均值 。

x 个元素的 平均值 是 x 个元素相加之和除以 x ，此时使用截断式 整数除法 ，即需要去掉结果的小数部分。

例如，四个元素 2、3、1 和 5 的平均值是 (2 + 3 + 1 + 5) / 4 = 11 / 4 = 3.75，截断后得到 3 。
 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/11/07/eg1.png)

```
输入：nums = [7,4,3,9,1,8,5,2,6], k = 3
输出：[-1,-1,-1,5,4,4,-1,-1,-1]
解释：
- avg[0]、avg[1] 和 avg[2] 是 -1 ，因为在这几个下标前的元素数量都不足 k 个。
- 中心为下标 3 且半径为 3 的子数组的元素总和是：7 + 4 + 3 + 9 + 1 + 8 + 5 = 37 。
  使用截断式 整数除法，avg[3] = 37 / 7 = 5 。
- 中心为下标 4 的子数组，avg[4] = (4 + 3 + 9 + 1 + 8 + 5 + 2) / 7 = 4 。
- 中心为下标 5 的子数组，avg[5] = (3 + 9 + 1 + 8 + 5 + 2 + 6) / 7 = 4 。
- avg[6]、avg[7] 和 avg[8] 是 -1 ，因为在这几个下标后的元素数量都不足 k 个。
```
示例 2：
```
输入：nums = [100000], k = 0
输出：[100000]
解释：
- 中心为下标 0 且半径 0 的子数组的元素总和是：100000 。
  avg[0] = 100000 / 1 = 100000 。
```
示例 3：
```
输入：nums = [8], k = 100000
输出：[-1]
解释：
- avg[0] 是 -1 ，因为在下标 0 前后的元素数量均不足 k 。
```
提示：

* n == nums.length
* 1 <= n <= 105
* 0 <= nums[i], k <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/k-radius-subarray-averages
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路


这道题目是求指定范围的2 * k + 1的平均值，可以在遍历之前先算好前k个数的和add，在每次往后遍历，维护这个add的值。

注意点：
* 我们维护的add的值很有可能超过int值的上限。
* 在for循环里面做判断需要看边界值的问题
* 在求add的初始值时，要注意k过大造成数组越界的问题

代码如下：
```c++
class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        vector<int> ans;
        int average = 0;
        long long add = 0;
        if(2 * k + 1 < nums.size()){
            for(int i = 0; i < k; i++) add += nums[i];
        }
        for(int i = 0; i < nums.size(); i++){
            if(i + k <= nums.size() - 1) add += nums[i + k];
            if(i - k - 1 >= 0) add -= nums[i - k - 1];
            if(i - k < 0 || i + k > nums.size() - 1) ans.push_back(-1);
            average = int(add / (2 * k + 1));
            if(i - k >= 0 && i + k <= nums.size() - 1) ans.push_back(average);
        }
        return ans;
    }
};
```


看了大神的题解，思路相同，代码简洁很多：
```c++
class Solution {
public:
    vector<int> getAverages(vector<int>& a, int k) {
        int n = a.size();
        vector<long long> sum(n + 1);
        for(int i = 0; i < n; ++i) sum[i + 1] = sum[i] + a[i];
        vector<int> ret(n);
        for(int i = 0; i < n; ++i) {
            int l = i - k, r = i + k;
            if(l < 0 || r >= n) {
                ret[i] = -1;
            } else {
                ret[i] = (sum[r + 1] - sum[l]) / (2 * k + 1);
            }
        }
        return ret;
    }
};
```