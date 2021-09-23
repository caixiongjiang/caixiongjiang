## 编号300：最长递增子序列

给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

 
示例 1：
```
输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
```
示例 2：
```
输入：nums = [0,1,0,3,2,3]
输出：4
```
示例 3：
```
输入：nums = [7,7,7,7,7,7,7]
输出：1 
```
提示：

* 1 <= nums.length <= 2500
* -104 <= nums[i] <= 104
 

进阶：

* 你可以设计时间复杂度为 O(n2) 的解决方案吗？
* 你能将算法的时间复杂度降低到 O(n log(n)) 吗?

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-increasing-subsequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

最长上升子序列是动规的经典题目，这里dp[i]是可以根据dp[j] （j < i）推导出来的，那么依然用动规五部曲来分析详细一波：

1.dp[i]的定义

dp[i]表示i之前包括i的最长上升子序列的长度。

2.状态转移方程

位置i的最长升序子序列等于j从0到i-1各个位置的最长升序子序列 + 1 的最大值。

所以：if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);

**注意这里不是要dp[i] 与 dp[j] + 1进行比较，而是我们要取dp[j] + 1的最大值。**

3.dp[i]的初始化

每一个i，对应的dp[i]（即最长上升子序列）起始大小至少都是是1.

4.确定遍历顺序

dp[i] 是有0到i-1各个位置的最长升序子序列 推导而来，那么遍历i一定是从前向后遍历。

j其实就是0到i-1，遍历i的循环里外层，遍历j则在内层，代码如下：
```c++
for (int i = 1; i < nums.size(); i++) {
    for (int j = 0; j < i; j++) {
        if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
    }
    if (dp[i] > result) result = dp[i]; // 取长的子序列
}
```
5.举例推导dp数组

输入：[0,1,0,3,2]，dp数组的变化如下：
![avater](https://camo.githubusercontent.com/1fb513853fd8664dae8a5fdfa75e799ad6ebf0c231abcbd8ac9a3bb6e40b396e/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303131303137303934353631382e6a7067)

整体代码如下：
```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.size() <= 1) return nums.size();
        vector<int> dp(nums.size(), 1);
        int result = 0;
        for(int i = 1; i < nums.size(); i++){
            for(int j = 0; j < i; j++){
                if(nums[i] > nums[j]){
                    dp[i] = max(dp[i], dp[j] + 1);
                }
                if(dp[i] > result) result = dp[i];//取长的子序列
            }
        }
        return result;
    }
};
```

## 贪心+二分查找

考虑一个简单的贪心，如果我们要使上升子序列尽可能的长，则我们需要让序列上升得尽可能慢，因此我们希望每次在上升子序列最后加上的那个数尽可能的小。

基于上面的贪心思路，我们维护一个数组 d[i]，表示长度为i的最长上升子序列的末尾元素的最小值，用len记录目前最长上升子序列的长度，起始时len为 1,d[1]=nums[0]。

同时我们可以注意到 d[i] 是关于i单调递增的。因为如果d[j]>=d[i] 且 j < i，我们考虑从长度为 i 的最长上升子序列的末尾删除i−j个元素，那么这个序列长度变为j ，且第 j 个元素 x（末尾元素）必然小于 d[i]，也就小于d[j]。那么我们就找到了一个长度为 j 的最长上升子序列，并且末尾元素比 d[j] 小，从而产生了矛盾。因此数组 d 的单调性得证。

我们依次遍历数组nums中的每个元素，并更新数组 d 和 len 的值。如果nums[i]>d[len] 则更新 len=len+1，否则在d[1…len]中找满足d[i−1]< nums[j]< d[i] 的下标 i，并更新 d[i]=nums[j]。

根据 d 数组的单调性，我们可以使用二分查找寻找下标 i，优化时间复杂度。

最后整个算法流程为：

* 设当前已求出的最长上升子序列的长度为 len（初始时为 1），从前往后遍历数组 nums，在遍历到 nums[i] 时：

</br>&emsp;如果 nums[i]>d[len] ，则直接加入到 d 数组末尾，并更新len=len+1；

否则，在 d数组中二分查找，找到第一个比 nums[i] 小的数 d[k] ，并更新 d[k+1]=nums[i]。

以输入序列 [0, 8, 4, 12, 2] 为例：

* 第一步插入 0，d = [0]；
 
* 第二步插入 8，d = [0, 8]；

* 第三步插入 4，d = [0, 4]；

* 第四步插入 12，d = [0, 4, 12]；

* 第五步插入 2，d = [0, 2, 12]。

最终得到最大递增子序列长度为 3。

整体代码如下：
```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = 1, n = (int)nums.size();
        if (n == 0) {
            return 0;
        }
        vector<int> d(n + 1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > d[len]) {
                d[++len] = nums[i];
            } else {
                int l = 1, r = len, pos = 0; // 如果找不到说明所有的数都比 nums[i] 大，此时要更新 d[1]，所以这里将 pos 设为 0
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (d[mid] < nums[i]) {
                        pos = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                d[pos + 1] = nums[i];
            }
        }
        return len;
    }
};
```