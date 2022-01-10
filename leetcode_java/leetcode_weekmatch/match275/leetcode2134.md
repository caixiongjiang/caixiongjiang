## 编号：最少交换次数来组合所有的 1 II(🍵)

交换 定义为选中一个数组中的两个 互不相同 的位置并交换二者的值。

环形 数组是一个数组，可以认为 第一个 元素和 最后一个 元素 相邻 。

给你一个 二进制环形 数组 nums ，返回在 任意位置 将数组中的所有 1 聚集在一起需要的最少交换次数。

 

示例 1：
```
输入：nums = [0,1,0,1,1,0,0]
输出：1
解释：这里列出一些能够将所有 1 聚集在一起的方案：
[0,0,1,1,1,0,0] 交换 1 次。
[0,1,1,1,0,0,0] 交换 1 次。
[1,1,0,0,0,0,1] 交换 2 次（利用数组的环形特性）。
无法在交换 0 次的情况下将数组中的所有 1 聚集在一起。
因此，需要的最少交换次数为 1 。
```
示例 2：
```
输入：nums = [0,1,1,1,0,0,1,1,0]
输出：2
解释：这里列出一些能够将所有 1 聚集在一起的方案：
[1,1,1,0,0,0,0,1,1] 交换 2 次（利用数组的环形特性）。
[1,1,1,1,1,0,0,0,0] 交换 2 次。
无法在交换 0 次或 1 次的情况下将数组中的所有 1 聚集在一起。
因此，需要的最少交换次数为 2 。
```
示例 3：
```
输入：nums = [1,1,0,0,1]
输出：0
解释：得益于数组的环形特性，所有的 1 已经聚集在一起。
因此，需要的最少交换次数为 0 。 
```
提示：

* 1 <= nums.length <= 105
* nums[i] 为 0 或者 1


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-swaps-to-group-all-1s-together-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

要将所有的1聚合在一起，寻找最少的交换次数，其实就是寻找最少的替换0的次数。

不如从全部1聚集在结果开始倒推，可以知道替换最少的次数就是这些位置上数组原先为0的数量，所以这题可以用滑动窗口来解决。

本体还有一个首位相邻的问题，这个可以用拼接数组来解决。

### 我的做法（超时）

我的思路与正确的思路别无二致，不过就是滑动窗口不太熟悉，导致了很多无效操作，超时了，导致这道题没AC

代码如下：
```c++
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0, res = 0, maxlen = 0;
        vector<int> v;
        
        //拼接数组
        for(auto &num : nums){
            if(num == 1) cnt++;
            v.push_back(num);
        }
        for(auto &num : nums){
            v.push_back(num);
        }

        //滑动窗口（垃圾写法）
        int left = 0, right = left + cnt - 1;
        while(right < 2 * n){
            int temp = 0;
            for(int i = left; i <= right; i++){
                if(v[i] == 1){
                    temp++;
                }
            }
            maxlen = max(maxlen, temp);
            left++;
            right++;
        }
        return cnt - maxlen;
    }
};
```

### 拼接数组 + 滑动窗口

改进后的写法终于过了,看的是[龟派气功的题解](https://leetcode-cn.com/problems/minimum-swaps-to-group-all-1s-together-ii/solution/c-hua-dong-chuang-kou-by-liyinxin-svn4/)

代码如下：
```c++
class Solution {
public:
    int minSwaps(vector<int>& num) {
        int n = num.size();
        vector<int> nums = num;//拼接，去环
        for(int i = 0; i < n;++i){
            nums.push_back(num[i]);
        }
        int sum = 0;
        for(auto &item : num){
            if(item == 1)++sum;
        }
        n = nums.size();
        int s = 0;
        for(int i = 0; i < sum;++i){
            if(nums[i] == 1)++s;
        }
        int right  = sum,res = sum - s,left = 0;
        while(right < n){
            if(nums[right++] == 1)++s;
            if(nums[left++] == 1)--s;
            res = min(res,sum-s);
        }
        return res;
    }
};

```

### 没有拼接数组的写法

突然想到好像不用拼接数组也可以，只要遍历2 * n的长度的数组，每个元素对n取模即可解决首位相邻的问题

代码如下：
```c++
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        int res = n, windowSize = 0;

        //统计数组中1的个数,作为滑动窗口的大小
        for(auto num : nums){
            if(num == 1) windowSize++;
        }

        /*开始滑动窗口*/
        int zeroCnt = 0;//维护0的数量
        
        //为了防止首位为相邻的问题，遍历2倍数量的元素（后面取模）
        for(int i = 0; i < 2 * n; i++){
            if(i >= windowSize){
                res = min(res, zeroCnt);
                if(nums[(i - windowSize) % n] == 0){
                    zeroCnt--;
                }
            }
            if (nums[i % n] == 0) zeroCnt++;
        }
        return res;
    }
};
```
