## 编号786：第 K 个最小的素数分数

给你一个按递增顺序排序的数组 arr 和一个整数 k 。数组 arr 由 1 和若干 素数  组成，且其中所有整数互不相同。

对于每对满足 0 < i < j < arr.length 的 i 和 j ，可以得到分数 arr[i] / arr[j] 。

那么第 k 个最小的分数是多少呢?  以长度为 2 的整数数组返回你的答案, 这里 answer[0] == arr[i] 且 answer[1] == arr[j] 。

 
示例 1：
```
输入：arr = [1,2,3,5], k = 3
输出：[2,5]
解释：已构造好的分数,排序后如下所示: 
1/5, 1/3, 2/5, 1/2, 3/5, 2/3
很明显第三个最小的分数是 2/5
```
示例 2：
```
输入：arr = [1,7], k = 1
输出：[1,7] 
```
提示：

* 2 <= arr.length <= 1000
* 1 <= arr[i] <= 3 * 104
* arr[0] == 1
* arr[i] 是一个 素数 ，i > 0
* arr 中的所有数字 互不相同 ，且按 严格递增 排序
* 1 <= k <= arr.length * (arr.length - 1) / 2

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/k-th-smallest-prime-fraction
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路


### 自定义排序

记数组 arr 的长度为 n。我们可以将全部的 n(n−1)/2个分数放入数组中进行自定义排序，规则为将这些分数按照升序进行排序。

在排序完成后，我们就可以得到第 kk 个最小的素数分数。

**细节**

当我们比较两个分数 a/b 和 c/d时，我们可以直接对它们的值进行比较，但这会产生浮点数的计算，降低程序的效率，并且可能会引入浮点数误差。一种可行的替代方法是用：a × d < b × c来替代a/b < c/d的判断，二者是等价的。

代码如下：
```c++
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        vector<pair<int, int>> frac;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                frac.emplace_back(arr[i], arr[j]);
            }
        }
        sort(frac.begin(), frac.end(), [&](const auto& x, const auto& y) {
            return x.first * y.second < x.second * y.first;
        });
        return {frac[k - 1].first, frac[k - 1].second};
    }
};
```