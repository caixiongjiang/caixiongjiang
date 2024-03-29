## 编号2111:使数组 K 递增的最少操作次数(叉)

给你一个下标从 0 开始包含 n 个正整数的数组 arr ，和一个正整数 k 。

如果对于每个满足 k <= i <= n-1 的下标 i ，都有 arr[i-k] <= arr[i] ，那么我们称 arr 是 K 递增 的。

* 比方说，arr = [4, 1, 5, 2, 6, 2] 对于 k = 2 是 K 递增的，因为：
    * arr[0] <= arr[2] (4 <= 5)
    * arr[1] <= arr[3] (1 <= 2)
    * arr[2] <= arr[4] (5 <= 6)
    * arr[3] <= arr[5] (2 <= 2)
* 但是，相同的数组 arr 对于 k = 1 不是 K 递增的（因为 arr[0] > arr[1]），对于 k = 3 也不是 K 递增的（因为 arr[0] > arr[3] ）。
每一次 操作 中，你可以选择一个下标 i 并将 arr[i] 改成任意 正整数。

请你返回对于给定的 k ，使数组变成 K 递增的 最少操作次数 。

 

示例 1：
```
输入：arr = [5,4,3,2,1], k = 1
输出：4
解释：
对于 k = 1 ，数组最终必须变成非递减的。
可行的 K 递增结果数组为 [5,6,7,8,9]，[1,1,1,1,1]，[2,2,3,4,4] 。它们都需要 4 次操作。
次优解是将数组变成比方说 [6,7,8,9,10] ，因为需要 5 次操作。
显然我们无法使用少于 4 次操作将数组变成 K 递增的。
```
示例 2：
```
输入：arr = [4,1,5,2,6,2], k = 2
输出：0
解释：
这是题目描述中的例子。
对于每个满足 2 <= i <= 5 的下标 i ，有 arr[i-2] <= arr[i] 。
由于给定数组已经是 K 递增的，我们不需要进行任何操作。
```
示例 3：
```
输入：arr = [4,1,5,2,6,2], k = 3
输出：2
解释：
下标 3 和 5 是仅有的 3 <= i <= 5 且不满足 arr[i-3] <= arr[i] 的下标。
将数组变成 K 递增的方法之一是将 arr[3] 变为 4 ，且将 arr[5] 变成 5 。
数组变为 [4,1,5,4,6,5] 。
可能有其他方法将数组变为 K 递增的，但没有任何一种方法需要的操作次数小于 2 次。
```
提示：

* 1 <= arr.length <= 105
* 1 <= arr[i], k <= arr.length


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-operations-to-make-the-array-k-increasing
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 动态规划(官方题解)

**题目的要求本质上是对于每一个i (0≤ i < k)，数组 arr 的“子序列”是单调递增的！**

这里的子序列指每个像个k个位置的字符抽离出来的子序列。

提示1的解释：

我们将数组 arr 中的每个元素根据其下标对 k 取模的值，分成了 k 个子序列（即下标对 k 取模的值分别为 0, 1, ···,k−1 ）。这 k−1 个子序列分别都是单调递增的。

提示2的解释：

对于序列中那些需要被修改的元素，由于我们可以把它们修改成任意元素，因此它们修改之前的值并不重要，我们可以忽略它们。

<span style="color:green">**而对于序列中那些没有被修改的元素，由于最终的序列是单调递增的，因此这些没有被修改的元素组成的子序列也一定是单调递增的。要想修改的元素越少，这个子序列就要越长。因此我们的目标就是求出序列的最长递增的子序列。**</span>

代码如下：
```c++
class Solution {
public:
    int kIncreasing(vector<int>& arr, int k) {
        int n = arr.size();
        int ans = 0;
        for(int i = 0; i < k; i++){
            vector<int> vec;
            int length = 0;
            for(int j = i; j < n; j += k){
                length++;
                //upper_bound( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。
                //lower_bound( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于或等于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。
                //找到第一个大于arr[j]值的下标
                auto it = upper_bound(vec.begin(), vec.end(), arr[j]);
                if(it == vec.end()){
                    //将符合递增条件的元素组成子串
                    vec.emplace_back(arr[j]);
                }else{
                    *it = arr[j];//将大于arr[j]下标的位置的值改成等于arr[j]
                }
            }
            ans += length - vec.size();
        }
        return ans;
    }
};
```

继续copy第一名的代码！

思路和官方题解一样，只是将求子元素递增数量的算法抽象成一个算法模版的形式，更加的清晰。

代码如下：
```c++
class Solution {
public:
    template<typename T>
    int lis(vector<T> a) {
        vector<T> dp;
        for(auto x : a) {
            auto it = upper_bound(dp.begin(), dp.end(), x); // > : lower, >= : upper
            if(it == dp.end()) dp.push_back(x);
            else *it = x;
        }
        return dp.size();
    }
    int kIncreasing(vector<int>& a, int k) {
        int n = a.size();
        int ans = 0;
        for(int i = 0; i < k; ++i) {
            vector<int> b;
            for(int j = i; j < n; j += k) {
                b.push_back(a[j]);
            }
            ans += lis(b);
        }
        return n - ans;
    }
};
```
