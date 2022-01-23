## 编号2148：元素计数(AC)

给你一个整数数组 nums ，统计并返回在 nums 中同时具有一个严格较小元素和一个严格较大元素的元素数目。


示例 1：
```
输入：nums = [11,7,2,15]
输出：2
解释：元素 7 ：严格较小元素是元素 2 ，严格较大元素是元素 11 。
元素 11 ：严格较小元素是元素 7 ，严格较大元素是元素 15 。
总计有 2 个元素都满足在 nums 中同时存在一个严格较小元素和一个严格较大元素。
```
示例 2：
```
输入：nums = [-3,3,3,90]
输出：2
解释：元素 3 ：严格较小元素是元素 -3 ，严格较大元素是元素 90 。
由于有两个元素的值为 3 ，总计有 2 个元素都满足在 nums 中同时存在一个严格较小元素和一个严格较大元素。
```
提示：

* 1 <= nums.length <= 100
* -10^5 <= nums[i] <= 10^5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-elements-with-strictly-smaller-and-greater-elements
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

先排序，再遍历，如果比最小的大，最大的小就计数


代码如下：
```c++
class Solution {
public:
    int countElements(vector<int>& nums) {
       int res = 0;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 1; i < n - 1; i++){
            if(nums[i] > nums[0] && nums[i] < nums[n - 1]) res++;
        }
        return res;
    }
};
```