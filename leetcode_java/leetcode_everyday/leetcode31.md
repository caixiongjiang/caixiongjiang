## 编号31：下一个排列

实现获取 下一个排列 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列（即，组合出下一个更大的整数）。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须 原地 修改，只允许使用额外常数空间。

 

示例 1：
```
输入：nums = [1,2,3]
输出：[1,3,2]
```
示例 2：
```
输入：nums = [3,2,1]
输出：[1,2,3]
```
示例 3：
```
输入：nums = [1,1,5]
输出：[1,5,1]
```
示例 4：
```
输入：nums = [1]
输出：[1] 
```
提示：

* 1 <= nums.length <= 100
* 0 <= nums[i] <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/next-permutation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

这道题因为按照字典序排列，所以位数越高的地方数字越小才会有比它大的序列。

因为要找下一个比它大的最小的序列，所以位数的交换从数字的末尾开始。**双指针都从末尾开始计数。**

i为第一个不是降序的数字的下标，j为第一个比i位置数值大的数值下标。

<span style="color:green">最后找到i和j的位置之后，先交换i和j的位数值，再将i+1 到 j 的字符串反转就得到了题目想要的结果。</span>


整体代码如下：
```c++
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;
        while(i >= 0 && nums[i] >= nums[i+1]){
            i--;
        }
        if(i >= 0){
            int j = nums.size() - 1;
            while(j >= 0 && nums[i] >= nums[j]){
                j--;
            }
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + i + 1, nums.end());
    }
};
```