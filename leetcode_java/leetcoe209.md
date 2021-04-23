## 编号209：长度最小的子数组

给定一个含有 n 个正整数的数组和一个正整数 target 。

找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

 

示例 1：
```markdown
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
示例 2：
```
```markdown
输入：target = 4, nums = [1,4,4]
输出：1
示例 3：
```
```markdown
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
```

提示：
```markdown
1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 105
```
 

进阶：

如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-size-subarray-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
*暴力解法*
```java
class Solution {
    public int minSubArrayLen(int target, int[] nums) {
    int result = Integer.MAX_VALUE; // 最终的结果
        int sum = 0; // 子序列的数值之和
        int subLength = 0; // 子序列的长度
        for (int i = 0; i < nums.length; i++) { // 设置子序列起点为i
            sum = 0;
            for (int j = i; j < nums.length; j++) { // 设置子序列终止位置为j
                sum += nums[j];
                if (sum >= target) { // 一旦发现子序列和超过了target，更新result
                    subLength = j - i + 1; // 取子序列的长度
                    result = result < subLength ? result : subLength;
                    break; // 因为我们是找符合条件最短的子序列，所以一旦符合条件就break
                }
            }
        }
        // 如果result没有被赋值的话，就返回0，说明没有符合条件的子序列
        return result == Integer.MAX_VALUE ? 0 : result;
    }    
}
```
---
*滑动窗口*
</br>接下来就开始介绍数组操作中另一个重要的方法：「滑动窗口」。

所谓滑动窗口，<span style="color:green">*就是不断的调节子序列的起始位置和终止位置，从而得出我们要想的结果。*</span>

这里还是以题目中的示例来举例，s=7， 数组是 2，3，1，2，4，3，来看一下查找的过程：
![avater](https://mmbiz.qpic.cn/mmbiz_gif/ciaqDnJprwv6MwIsdYLFnPSXSJ3WgSPQRf3oaBEAYc57vWs1aSc4YMjmMSawj3QQxd4A81P4XYF6sibPK0lZ1ic4w/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1)

```java
class Solution {
    public int minSubArrayLen(int target, int[] nums) {
    int result = Integer.MAX_VALUE;
        int sum = 0; // 滑动窗口数值之和
        int i = 0; // 滑动窗口起始位置
        int subLength = 0; // 滑动窗口的长度
        for (int j = 0; j < nums.length; j++) {
            sum += nums[j];
            // 注意这里使用while，每次更新 i（起始位置），并不断比较子序列是否符合条件
            while (sum >= target) {
                subLength = (j - i + 1); // 取子序列的长度
                result = result < subLength ? result : subLength;
                sum -= nums[i++]; // 这里体现出滑动窗口的精髓之处，不断变更i（子序列的起始位置）
            }
        }
        // 如果result没有被赋值的话，就返回0，说明没有符合条件的子序列
        return result == Integer.MAX_VALUE ? 0 : result;
    }  
}
```
可以发现<span style="color:red">「滑动窗口的精妙之处在于根据当前子序列和大小的情况，不断调节子序列的起始位置。从而将O(n^2)的暴力解法降为O(n)。」</span>