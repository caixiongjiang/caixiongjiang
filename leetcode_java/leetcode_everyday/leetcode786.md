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

### 二分查找+双指针

我们可以随便猜测一个实数α，如果恰好有 k 个素数分数小于 α，那么这 k 个素数分数中最大的那个就是第 k 个最小的素数分数。

对于 α，我们如何求出有多少个小于 α 的素数分数呢？我们可以使用双指针来求出答案：

* 我们使用一个指针 j 指向分母，这个指针每次会向右移动一个位置，表示枚举不同的分母；

* 我们再使用一个指针 i 指向分子，这个指针会不断向右移动，并且保证 arr[i]/arr[j] < a
​
 <α 一直成立。当指针 ii 无法移动时，我们就可以知道 \textit{arr}[0], \cdots, \textit{arr}[i]arr[0],⋯,arr[i] 都可以作为分子，但 \textit{arr}[i+1]arr[i+1] 及以后的元素都不可以，即分母为 \textit{arr}[j]arr[j] 并且小于 \alphaα 的素数分数有 i+1i+1 个。

* 在 j 向右移动的过程中，我们把每一个 jj 对应的 i+1i+1 都加入答案。这样在双指针的过程完成后，我们就可以得到有多少个小于 \alphaα 的素数分数了。

如果我们得到的答案恰好等于 kk，那么我们再进行一遍上面的过程，求出所有 \dfrac{\textit{arr}[i]}{\textit{arr}[j]} 
arr[j]
arr[i]
​
  中的最大值即为第 kk 个最小的素数分数。但如果答案小于 kk，这说明我们猜测的 \alphaα 太小了，我们需要增加它的值；如果答案大于 kk，这说明我们猜测的 \alphaα 太大了，我们需要减少它的值。

这就提示我们使用二分查找来找到合适的 \alphaα。二分查找的上界为 11，下界为 00。在二分查找的每一步中，我们取上下界区间的中点作为 \alphaα，并计算小于 \alphaα 的素数分数的个数，并根据这个值来调整二分查找的上界或下界。

细节

由于我们是在实数范围内进行二分查找，那么最坏情况下需要进行多少步查找呢？

可以发现，数组 \textit{arr}arr 中元素的最大值为 3 \times 10^43×10 
4
 ，即任意两个素数分数的差值不会小于 \dfrac{1}{(3 \times 10^4)^2} = \dfrac{1}{9 \times 10^8} 
(3×10 
4
 ) 
2
 
1
​
 = 
9×10 
8
 
1
​
 。假设第 kk 个最小的素数分数为 \beta_kβ 
k
​
 ，第 k+1k+1 个为 \beta_{k+1}β 
k+1
​
 ，那么有：

\beta_{k+1} - \beta_k > \dfrac{1}{9 \times 10^8}
β 
k+1
​
 −β 
k
​
 > 
9×10 
8
 
1
​
 

只要我们的二分查找选取的 \alphaα 落在 (\beta_k, \beta_{k+1}](β 
k
​
 ,β 
k+1
​
 ] 的区间内，那么就可以结束二分查找并返回答案。而二分查找的初始区间为 [0, 1][0,1]，每一步区间的长度会减少一半，因此在进行第 \lceil \log (9 \times 10^8) \rceil = 30⌈log(9×10 
8
 )⌉=30 次二分查找后，区间的长度小于 \dfrac{1}{9 \times 10^8} 
9×10 
8
 
1
​
 ，这说明左边界和右边界中至少有一个落在 (\beta_k, \beta_{k+1}](β 
k
​
 ,β 
k+1
​
 ] 区间内。不失一般性设落在区间内的是左边界，由于左边界的初始值 0 \notin (\beta_k, \beta_{k+1}]0∈ 
/
​
 (β 
k
​
 ,β 
k+1
​
 ]，说明左边界的值在之前的某一步二分查找时被修改，即那一次二分查找选取的 \alphaα 就落在 (\beta_k, \beta_{k+1}](β 
k
​
 ,β 
k+1
​
 ] 内。

代码如下：
```c++
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        double left = 0.0, right = 1.0;
        while (true) {
            double mid = (left + right) / 2;
            int i = -1, count = 0;
            // 记录最大的分数
            int x = 0, y = 1;
            
            for (int j = 1; j < n; ++j) {
                while ((double)arr[i + 1] / arr[j] < mid) {
                    ++i;
                    if (arr[i] * y > arr[j] * x) {
                        x = arr[i];
                        y = arr[j];
                    }
                }
                count += i + 1;
            }

            if (count == k) {
                return {x, y};
            }
            if (count < k) {
                left = mid;
            }
            else {
                right = mid;
            }
        }
    }
};
```