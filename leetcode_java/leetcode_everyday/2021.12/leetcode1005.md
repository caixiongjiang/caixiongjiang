## 编号1005: K 次取反后最大化的数组和

给你一个整数数组 nums 和一个整数 k ，按以下方法修改该数组：

* 选择某个下标 i 并将 nums[i] 替换为 -nums[i] 。
重复这个过程恰好 k 次。可以多次选择同一个下标 i 。

以这种方式修改数组后，返回数组 可能的最大和 。

 

示例 1：
```
输入：nums = [4,2,3], k = 1
输出：5
解释：选择下标 1 ，nums 变为 [4,-2,3] 。
```
示例 2：
```
输入：nums = [3,-1,0,2], k = 3
输出：6
解释：选择下标 (1, 2, 2) ，nums 变为 [3,1,0,2] 。
```
示例 3：
```
输入：nums = [2,-3,-1,5,-4], k = 2
输出：13
解释：选择下标 (1, 4) ，nums 变为 [2,3,-1,5,4] 。 
```
提示：

* 1 <= nums.length <= 104
* -100 <= nums[i] <= 100
* 1 <= k <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximize-sum-of-array-after-k-negations
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路


### 贪心

注意点：
* 1.一个下标的数组是可以反复反转的
* 2.对数组进行修改后会改变原数组，不能通过遍历来确定最小值。所以要采用排序函数，提前改变数组的位置，这样可以通过元素的位置来判断数字大小。

本题可以根据 nums 数组中的负数的数量 和 k 之间的关系，贪心的选择翻转的位置，使数组和最大。

* 情况1，若负数数量 大于 等于k，则将最小的k个负数变为正数。
* 情况2，若负数数量小于k，则将所有负数变为正数，之后根据 k 减去 负数的数量 的剩余值的奇偶性，进一步判断。
    * 若剩余值为偶数，则不用管。
    * 若剩余值为奇数，减去绝对值最小的值。
时间复杂度：O(nlogn)

空间复杂度：O(1)

代码如下：
```c++
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        int abs_min = 100, sum = 0; 
        for (int i = 0; i < nums.size(); i++) {
          	// 计算绝对值最小的值
            abs_min = min(abs(nums[i]), abs_min);
            // 所有数字的和
            sum += nums[i]; 
        }
        
        sort(nums.begin(), nums.end());
        // 根据k，翻转值为负数的nums[i]，并更新sum
        for (int i = 0; i < nums.size() && k; i++, k--) {
            if (nums[i] >= 0)
                break;
            //负数变成正数，sum加两倍的绝对值
            sum += 2 * abs(nums[i]);
        }
        // 若k有剩余，且为奇数，减去其在sum中的值
        if (k > 0 && (k & 1))
            sum -= 2 * abs_min;
        return sum;
    }
};
```