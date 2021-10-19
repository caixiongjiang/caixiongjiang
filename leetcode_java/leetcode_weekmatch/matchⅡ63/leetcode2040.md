## 编号2040：两个有序数组的第 K 小乘积（×）

给你两个 从小到大排好序 且下标从 0 开始的整数数组 nums1 和 nums2 以及一个整数 k ，请你返回第 k （从 1 开始编号）小的 nums1[i] * nums2[j] 的乘积，其中 0 <= i < nums1.length 且 0 <= j < nums2.length 。
 

示例 1：
```
输入：nums1 = [2,5], nums2 = [3,4], k = 2
输出：8
解释：第 2 小的乘积计算如下：
- nums1[0] * nums2[0] = 2 * 3 = 6
- nums1[0] * nums2[1] = 2 * 4 = 8
第 2 小的乘积为 8 。
```
示例 2：
```
输入：nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6
输出：0
解释：第 6 小的乘积计算如下：
- nums1[0] * nums2[1] = (-4) * 4 = -16
- nums1[0] * nums2[0] = (-4) * 2 = -8
- nums1[1] * nums2[1] = (-2) * 4 = -8
- nums1[1] * nums2[0] = (-2) * 2 = -4
- nums1[2] * nums2[0] = 0 * 2 = 0
- nums1[2] * nums2[1] = 0 * 4 = 0
第 6 小的乘积为 0 。
```
示例 3：
```
输入：nums1 = [-2,-1,0,1,2], nums2 = [-3,-1,2,4,5], k = 3
输出：-6
解释：第 3 小的乘积计算如下：
- nums1[0] * nums2[4] = (-2) * 5 = -10
- nums1[0] * nums2[3] = (-2) * 4 = -8
- nums1[4] * nums2[0] = 2 * (-3) = -6
第 3 小的乘积为 -6 。 
```
提示：

* 1 <= nums1.length, nums2.length <= 5 * 104
* -105 <= nums1[i], nums2[j] <= 105
* 1 <= k <= nums1.length * nums2.length
* nums1 和 nums2 都是从小到大排好序的。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/kth-smallest-product-of-two-sorted-arrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 解法框架：二分查找

首先令f(x)= 满足nums1[i]∗nums2[j]≤x 的数对个数，显然f(x)是关于x递增的，因此可以进行二分查找，找到第一个满足f(x)≥k 的x即可。

下面的给出三种求 f(x)的解法

### 解法一：双指针 + 分类讨论
首先，我们把nums1分成neg1和pos1，分别表示nums1的**负数部分**和**非负数部分**；

把nums2分成neg2和pos2，分别表示nums2的**负数部分**和**非负数部分**。

一图胜千言，下面用一幅图来解释双指针遍历的各种边界条件。

* 情形一：nums1[i]≥0，nums2[j]≥0，分别对应pos1和pos2；

* 情形二：nums1[i]<0，nums2[j]≥0，分别对应neg1和pos2；

* 情形三：nums1[i]≥0，nums2[j]<0，分别对应pos1和neg2；

* 情形四：nums1[i]<0，nums2[j]<0，分别对应neg1和neg2。

![avater](https://pic.leetcode-cn.com/1634479959-JGNSre-image.png)

代码如下：
```c++
class Solution {
public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        //把nums1分为neg1（负数）和pos1（正数）
        //把nums2分为neg2（负数）和pos2（正数）
        vector<int> neg1, pos1, neg2, pos2;
        for(int v : nums1) (v < 0)? neg1.push_back(v) : pos1.push_back(v);
        for(int v : nums2) (v < 0)? neg2.push_back(v) : pos2.push_back(v);

        long long l = -1e10, r = 1e10;
        while(l < r) {
            long long m = (l + r) >> 1;
            long long cur = 0;
            // a > 0 && b > 0
            for(int i = 0, j = (int)pos2.size() - 1; i < pos1.size(); ++i) {
                while(j >= 0 && 1ll * pos1[i] * pos2[j] > m) --j;
                cur += j + 1;
            }
            // a < 0 && b > 0
            for(int i = 0, j = 0; i < neg1.size(); ++i) {
                while(j < pos2.size() && 1ll * neg1[i] * pos2[j] > m) ++j;
                cur += (int)pos2.size() - j;
            }
            // a > 0 && b < 0
            for(int i = 0, j = 0; i < pos1.size(); ++i) {
                while(j < neg2.size() && 1ll * pos1[i] * neg2[j] <= m) ++j;
                cur += j;
            }
            // a < 0 && b < 0
            for(int i = 0, j = (int)neg2.size() - 1; i < neg1.size(); ++i) {
                while(j >= 0 && 1ll * neg1[i] * neg2[j] <= m) --j;
                cur += (int)neg2.size() - 1 - j;
            }
            if(cur < k) l = m + 1;
            else r = m;
        }
        return l;
    }
};
```

### 解法二：解不等式+嵌套二分查找

### 解法三：前缀和