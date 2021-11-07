## 编号2063:分配给商店的最多商品的最小值（×）

给你一个整数 n ，表示有 n 间零售商店。总共有 m 种产品，每种产品的数目用一个下标从 0 开始的整数数组 quantities 表示，其中 quantities[i] 表示第 i 种商品的数目。

你需要将 所有商品 分配到零售商店，并遵守这些规则：

一间商店 至多 只能有 一种商品 ，但一间商店拥有的商品数目可以为 任意 件。
分配后，每间商店都会被分配一定数目的商品（可能为 0 件）。用 x 表示所有商店中分配商品数目的最大值，你希望 x 越小越好。也就是说，你想 最小化 分配给任意商店商品数目的 最大值 。
请你返回最小的可能的 x 。

 

示例 1：
```
输入：n = 6, quantities = [11,6]
输出：3
解释： 一种最优方案为：
- 11 件种类为 0 的商品被分配到前 4 间商店，分配数目分别为：2，3，3，3 。
- 6 件种类为 1 的商品被分配到另外 2 间商店，分配数目分别为：3，3 。
分配给所有商店的最大商品数目为 max(2, 3, 3, 3, 3, 3) = 3 。
```
示例 2：
```
输入：n = 7, quantities = [15,10,10]
输出：5
解释：一种最优方案为：
- 15 件种类为 0 的商品被分配到前 3 间商店，分配数目为：5，5，5 。
- 10 件种类为 1 的商品被分配到接下来 2 间商店，数目为：5，5 。
- 10 件种类为 2 的商品被分配到最后 2 间商店，数目为：5，5 。
分配给所有商店的最大商品数目为 max(5, 5, 5, 5, 5, 5, 5) = 5 。
```
示例 3：
```
输入：n = 1, quantities = [100000]
输出：100000
解释：唯一一种最优方案为：
- 所有 100000 件商品 0 都分配到唯一的商店中。
分配给所有商店的最大商品数目为 max(100000) = 100000 。 
```
提示：

* m == quantities.length
* 1 <= m <= n <= 105
* 1 <= quantities[i] <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimized-maximum-of-products-distributed-to-any-store
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

如果一个目标是x能满足某种条件，x+1一定能满足某种条件；且检验条件的复杂度不高。 我们就可以考虑二分搜索的这种方式。

在这道题中，check的过程就是采用贪心法，假设x可以满足条件，每个店都分配最大的商品（假设值），这样分配的店数一定是最少的。

由于同一个店只能持有一种商品，所以某个商品需要的店数一定为 商品总数 除以 最大分配数 向上取整。

我们基于贪心的策略，去看分配的店数量是否满足条件即可；然后在进一步缩小搜索空间，直到找到最小的最大值。

代码如下：
```c++
class Solution {
public:
    bool check(vector<int>& q, int n, long long x) {
        int nn = 0;
        for (auto cnt: q) {
            nn += cnt / x;
            if (cnt % x != 0) nn++;
        }
        if (nn > n) return false;
        return true;
    }
    
    int minimizedMaximum(int n, vector<int>& quantities) {
        long long sum = 0;
        for (auto q: quantities) {
            sum += q;
        }
        long long l = 0;
        long long r = sum;
        
        while(l < r) {
            long long mid = (l + r)  / 2;
            if (mid == 0) return 1;
            if (check(quantities, n, mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        
        return l;
    }
};
```