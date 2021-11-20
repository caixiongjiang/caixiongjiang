## 编号594：最长和谐子序列

和谐数组是指一个数组里元素的最大值和最小值之间的差别 正好是 1 。

现在，给你一个整数数组 nums ，请你在所有可能的子序列中找到最长的和谐子序列的长度。

数组的子序列是一个由数组派生出来的序列，它可以通过删除一些元素或不删除元素、且不改变其余元素的顺序而得到。

 

示例 1：
```
输入：nums = [1,3,2,2,5,2,3,7]
输出：5
解释：最长的和谐子序列是 [3,2,2,2,3]
```
示例 2：
```
输入：nums = [1,2,3,4]
输出：2
```
示例 3：
```
输入：nums = [1,1,1,1]
输出：0 
```
提示：

* 1 <= nums.length <= 2 * 104
* -109 <= nums[i] <= 109

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-harmonious-subsequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 枚举

我们可以枚举数组中的每一个元素，对于当前枚举的元素x，它可以和x+1组成和谐子序列。我们只需要在数组中找出等于x或x+1的元素个数，就可以得到以x为最小值的和谐子序列的长度。

* 实际处理时，我们可以将数组按照从小到大进行排序，我们只需要依次找到相邻两个连续相同元素的子序列，检查该这两个子序列的元素的之差是否为 1。
* 利用类似与滑动窗口的做法，begin 指向第一个连续相同元素的子序列的第一个元素，end 指向相邻的第二个连续相同元素的子序列的末尾元素，如果满足二者的元素之差为 1，则当前的和谐子序列的长度即为两个子序列的长度之和，等于end−begin+1。


代码如下：
```c++
//枚举
class Solution {
public:
    int findLHS(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int res = 0, end = 0;
        for(int i = 0; i < n; i++){
            while(nums[i] - nums[end] > 1){
                end++;
            }
            if(nums[i] - nums[end] == 1){
                res = max(i - end + 1, res);
            }
        }
        return res;
    }
};
```

### 哈希表

可以用一个哈希映射来存储每个数出现的次数，这样就能在 O(1)的时间内得到x和x+1出现的次数。

我们首先遍历一遍数组，得到哈希映射。随后遍历哈希映射，设当前遍历到的键值对为(x,value)，那么我们就查询x+1在哈希映射中对应的统计次数，就得到了x和x+1出现的次数，和谐子序列的长度等于x和x+1出现的次数之和。


代码如下：
```c++
//哈希表
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> cnt;
        int res = 0;
        for (int num : nums) {
            cnt[num]++;
        }
        for (auto [key, val] : cnt) {
            if (cnt.count(key + 1)) {
                res = max(res, val + cnt[key + 1]);
            }
        }
        return res;
    }
};
```