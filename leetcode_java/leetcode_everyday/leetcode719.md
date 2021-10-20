## 编号719：找出第k小的距离对

给定一个整数数组，返回所有数对之间的第 k 个最小距离。一对 (A, B) 的距离被定义为 A 和 B 之间的绝对差值。

示例 1:
```
输入：
nums = [1,3,1]
k = 1
输出：0 
解释：
所有数对如下：
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
因此第 1 个最小距离的数对是 (1,1)，它们之间的距离为 0。
```
提示:

* 2 <= len(nums) <= 10000.
* 0 <= nums[i] < 1000000.
* 1 <= k <= len(nums) * (len(nums) - 1) / 2.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-k-th-smallest-pair-distance
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 1.排序
```c++
sort(nums.begin(), nums.end());
```

### 2.二分

我们要搜索的目标是第k大的距离，距离的范围是：
```c++
int min = 0, max = nums.back() - nums.front();
```
这便是我们二分的起始条件。

max是最大距离，min是最小距离，第k大距离在这二者之间，是我们要去二分查找的。

二分的过程非常标准(左闭右开)：
```c++
while (min < max) {
    int mid = min + ((max - min) >> 1);    
    if (check(mid))
        max = mid;
    else
        min = mid + 1;
}
```
最后返回min或max距离

### 3.滑窗

check(mid)函数检查大于mid的距离是否超过k个。

遍历r。由于已经排序，如果窗口首末距离nums[r]-nums[l]超过mid，那么窗口不可能再扩大，收缩窗口左限l++。
累计窗口内满足条件的数对数量。

程序为：
```c++
int check(int mid) {
    int count = 0;
    int l = 0, 
    for (int r = 0; r < nums.size(); r++) {
        while (l < r && nums[r] - nums[l] > mid)
            l++;
        count += r - l;
    }
}
```
对于每一个nums[r]，找到满足条件的最大窗口，累计窗口内满足以下条件的数对数量：

&emsp;1.大数为nums[r]
</br>&emsp;2.距离小于mid

这个数量是r-l。

**例：**
下图是```r=4```时满足条件的最大窗口。满足条件的数对包括

(3,12),(4,12),(11,12)

一共有 r - l = 3 对。

![avater](https://pic.leetcode-cn.com/1624109768-KAiBlY-%E5%B9%BB%E7%81%AF%E7%89%875.JPG)

**(3,4) 这种距离也小于mid怎么算呢？实际上这个已经在 r=2, nums[r]=4 的时候计算过了喔~！**

总体代码如下：
```c++
//左闭右开
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        //代表最小距离和最大距离
        int min = 0, max = nums.back() - nums.front();
        while(min < max){
            int mid = min + ((max - min) >> 1);
            int count = 0;
            for(int l = 0, r = 0; r < nums.size(); r++){
                while(l < r && nums[r] - nums[l] > mid) l++;
                count += r - l;
            }
            if(count >= k){
                max = mid;
            }else{
                min = mid + 1;
            }
        }
        return min;
    }
};
```
