## 编号：从数组中移除最大值和最小值(AC)

给你一个下标从 0 开始的数组 nums ，数组由若干 互不相同 的整数组成。

nums 中有一个值最小的元素和一个值最大的元素。分别称为 最小值 和 最大值 。你的目标是从数组中移除这两个元素。

一次 删除 操作定义为从数组的 前面 移除一个元素或从数组的 后面 移除一个元素。

返回将数组中最小值和最大值 都 移除需要的最小删除次数。

 

示例 1：
```
输入：nums = [2,10,7,5,4,1,8,6]
输出：5
解释：
数组中的最小元素是 nums[5] ，值为 1 。
数组中的最大元素是 nums[1] ，值为 10 。
将最大值和最小值都移除需要从数组前面移除 2 个元素，从数组后面移除 3 个元素。
结果是 2 + 3 = 5 ，这是所有可能情况中的最小删除次数。
```
示例 2：
```
输入：nums = [0,-4,19,1,8,-2,-3,5]
输出：3
解释：
数组中的最小元素是 nums[1] ，值为 -4 。
数组中的最大元素是 nums[2] ，值为 19 。
将最大值和最小值都移除需要从数组前面移除 3 个元素。
结果是 3 ，这是所有可能情况中的最小删除次数。 
```
示例 3：
```
输入：nums = [101]
输出：1
解释：
数组中只有这一个元素，那么它既是数组中的最小值又是数组中的最大值。
移除它只需要 1 次删除操作。 
```
提示：

* 1 <= nums.length <= 105
* -105 <= nums[i] <= 105
* nums 中的整数 互不相同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/removing-minimum-and-maximum-from-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

1.首先我们要找到数组中最小值和最大值的位置：我的做法是复制一个克隆数组，将原数组排序，找出头尾的值，在克隆数组中找到两个数值对应的下标。

2.将两个下标在原数组中的位置进行判断，一共有四种情况：
* 两个下标都离开头较近
* 两个下标都离结尾较近
* 一个在头在尾：
	* 最大值在头，最小值在尾
	* 最小值在头，最大值在尾

3.特别要注意在统计删除元素次数的时候，注意比较从两头删除和从一边删除离得远的元素的大小，取最小的。


我的代码如下：
```c++
class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int m = nums.size();
        vector<int> clone(m);
        int minindex = 0, maxindex = 0;
        int ans = 0;
        if(m <= 2) return m;
        clone = nums;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < m; i++){
            if(clone[i] == nums[0]) minindex = i;
            if(clone[i] == nums[m - 1]) maxindex = i;
        }
        if(abs(minindex - 0) <= abs(m - 1 - minindex) && abs(maxindex - 0) <= abs(m - 1 - maxindex)){
            ans = max(abs(minindex - 0) + 1, abs(maxindex - 0) + 1);
        }
        if(abs(minindex - 0) > abs(m - 1 - minindex) && abs(maxindex - 0) < abs(m - 1 - maxindex)){
            ans = min(abs(m - 1 - minindex) + abs(maxindex - 0) + 2, min(abs(minindex - 0) + 1, abs(m - 1 - maxindex) + 1));
        }
        if(abs(minindex - 0) >= abs(m - 1 - minindex) && abs(maxindex - 0) >= abs(m - 1 - maxindex)){
            ans = max(abs(m - 1 - minindex) + 1, abs(m - 1 - maxindex) + 1);
        }
        if(abs(minindex - 0) < abs(m - 1 - minindex) && abs(maxindex - 0) > abs(m - 1 - maxindex)){
            ans = min(abs(minindex - 0) + abs(m - 1 - maxindex) + 2, min(abs(m - 1 - minindex) + 1, abs(maxindex - 0) + 1));
        }
        return ans;
    }
};
```

别人的思路：
* 找出最值的下标，存在三种情况：
	* 从右边删
	* 从左边删
	* 从两边删

代码如下：
```c++
class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        int imax, imin;
        int maxv = INT_MIN, minv = INT_MAX;
	//不产生额外辅助空间的情况下，找出最大值和最小值的下标
        for(int i = 0; i < n; i++){
            if(nums[i] < minv) {
                minv = nums[i];
                imin = i;
            }
            if(nums[i] > maxv) {
                maxv = nums[i];
                imax = i;
            }
        }
	//交换最大值和最小值的相对位置
        if(imin > imax) swap(imin, imax);
        
        int res = min(min(imax+1, n-imin), imin+1 + n-imax); 
        return res;
    }
};
```