## 编号2149：按符号重排数组(AC)

给你一个下标从 0 开始的整数数组 nums ，数组长度为 偶数 ，由数目相等的正整数和负整数组成。

你需要 重排 nums 中的元素，使修改后的数组满足下述条件：

任意 连续 的两个整数 符号相反

* 1.对于符号相同的所有整数，保留 它们在 nums 中的 顺序 。
* 2.重排后数组以正整数开头。  
* 3.重排元素满足上述条件后，返回修改后的数组。


示例 1：
```
输入：nums = [3,1,-2,-5,2,-4]
输出：[3,-2,1,-5,2,-4]
解释：
nums 中的正整数是 [3,1,2] ，负整数是 [-2,-5,-4] 。
重排的唯一可行方案是 [3,-2,1,-5,2,-4]，能满足所有条件。
像 [1,-2,2,-5,3,-4]、[3,1,2,-2,-5,-4]、[-2,3,-5,1,-4,2] 这样的其他方案是不正确的，因为不满足一个或者多个条件。 
```
示例 2：
```
输入：nums = [-1,1]
输出：[1,-1]
解释：
1 是 nums 中唯一一个正整数，-1 是 nums 中唯一一个负整数。
所以 nums 重排为 [1,-1] 。
```
提示：

* 2 <= nums.length <= 2 * 10^5
* nums.length 是 偶数
* 1 <= |nums[i]| <= 105
* nums 由 相等 数量的正整数和负整数组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rearrange-array-elements-by-sign
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

数组拆分再重建。

代码如下：
```c++
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> v1, v2;
        for(auto num : nums){
            if(num > 0) v1.push_back(num);
            if(num < 0) v2.push_back(num);
        }
        int n = nums.size();
        vector<int> res(n);
        for(int i = 0, j = 1, index = 0; i < n, j < n; i += 2, j += 2){
            res[i] = v1[index];
            res[j] = v2[index];
            index++;
        }
        return res;
    }
};
```