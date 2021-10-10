## 编号5897：将数组分成两个数组并最小化数组和的差(×)

给你一个长度为 2 * n 的整数数组。你需要将 nums 分成 两个 长度为 n 的数组，分别求出两个数组的和，并 最小化 两个数组和之 差的绝对值 。nums 中每个元素都需要放入两个数组之一。

请你返回 最小 的数组和之差。

 

示例 1：
![avater](https://assets.leetcode.com/uploads/2021/10/02/ex1.png)

```
输入：nums = [3,9,7,3]
输出：2
解释：最优分组方案是分成 [3,9] 和 [7,3] 。
数组和之差的绝对值为 abs((3 + 9) - (7 + 3)) = 2 。
```
示例 2：
```
输入：nums = [-36,36]
输出：72
解释：最优分组方案是分成 [-36] 和 [36] 。
数组和之差的绝对值为 abs((-36) - (36)) = 72 。
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2021/10/02/ex3.png)
```
输入：nums = [2,-1,0,4,-2,-9]
输出：0
解释：最优分组方案是分成 [2,4,-9] 和 [-1,0,-2] 。
数组和之差的绝对值为 abs((2 + 4 + -9) - (-1 + 0 + -2)) = 0 。 
```
提示：

* 1 <= n <= 15
* nums.length == 2 * n
* -107 <= nums[i] <= 107

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 方法一：Meet in the middle + 动态规划 + 双指针


要让两个数组和的差最小，就是要让其中一个数组的和尽可能接近sum/2

直接枚举，在N=15时需要考虑15000000种情况（这里还没有考虑每种情况需要求和），显然会超时。

因此，我们考虑使用Meet in the middle的方法，也即：分别求出前N个数中取i（0≤i≤N）个能够形成的和，以及后N个数中取ii（0≤i≤N）个能够形成的和，最后枚举前NN个数中选取的个数，来求取最后的答案。在折半之后，最多需要考虑的情况只有6435种。

第一步是一个比较简单的动态规划，**注意这里最好使用集合类型来存储中间结果，以免出现大量重复。**

第二步中，假设从前N个数中选i个，则应当从后N个数中选N-i个。这时就变成了一个经典问题：从两个数组中各选择一个数，使得它们的和最接近某一个给定的数。我们对两个数组分别排序后使用双指针求解即可。

**在具体实现中，我们使用了一个小trick，也即将原数组中所有数变为两倍。这样可以保证我们的目标值sum/2是一个整数。**

整体代码如下：
```c++
class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        for (auto &num : nums){
            num *= 2;
        }
        int n = nums.size() / 2;
        int sum = 0;
        for (int num : nums){
            sum += num;
        }
        vector<unordered_set<int>> left(n + 1), right(n + 1);
        left[0].insert(0), right[0].insert(0);
        for (int i = 0; i < n; ++i) {
            for (int j = i; j >= 0; --j) {
                for (int val : left[j]){
                    left[j + 1].insert(val + nums[i]);
                }
            }
        }
        
        for (int i = n; i < n * 2; ++i) {
            for (int j = i - n; j >= 0; --j) {
                for (int val : right[j]){
                    right[j + 1].insert(val + nums[i]);
                }
            }
        }
        
        vector<vector<int>> ls(n + 1), rs(n + 1);
        for (int i = 0; i <= n; ++i) {
            ls[i] = vector<int>(left[i].begin(), left[i].end());
            rs[i] = vector<int>(right[i].begin(), right[i].end());
            sort(ls[i].begin(), ls[i].end());
            sort(rs[i].begin(), rs[i].end());
        }
        
        int target = sum / 2;
        int dist = INT_MAX;
        for (int i = 0; i <= n; ++i) {
            int llen = ls[i].size(), rlen = rs[n - i].size();
            int pl = 0, pr = rlen - 1;
            while (pl < llen && pr >= 0) {
                int curr = ls[i][pl] + rs[n - i][pr];
                dist = min(dist, abs(curr - target));
                if (curr < target){
                    pl++;
                }
                else{
                    pr--;
                }
            }
        }
        return dist;
    }
};
```


```c++
//版本二
unordered_map<int, set<int>> ss;

class Solution{
public:
    int minimumDifference(vector<int>& nums){
        int n = nums.size() / 2;
        ss.clear();
        for(int i = 0; i < (1 << n); i++){ // 1<<n 等价于2^n
            int s = 0, now = 0;
            for(int j = 0; j < n; j++){
                if(i & (1 << j)){//&表示按位与 ，当且仅当 i==2^j 的时候，i 按位与 1<<j 得到的结果不为 0
                    s++;
                    now += nums[j];
                }else{
                    s--;
                    now -= nums[j];
                }
            }
            ss[s].insert(now);
        }
        int ans = 1e9;
        for(int i = 0; i < (1 << n); i++){
            int s = 0, now = 0;
            for(int j = 0; j < n; j++){
                if(i & (1 << j)){
                    s--;
                    now += nums[j + n];
                }else{
                    s++;
                    now -= nums[j + n];
                }
            }
            now = -now;
            auto it = ss[s].lower_bound(now);
            if(it != ss[s].end()){
                ans = min(ans, *it - now);
            }
            if(it != ss[s].begin()){
                it--;
                ans = min(ans, now - *it);
            }
        }
        return ans;
    }
};
```