## 编号2106：摘水果（叉）

在一个无限的 x 坐标轴上，有许多水果分布在其中某些位置。给你一个二维整数数组 fruits ，其中 fruits[i] = [positioni, amounti] 表示共有 amounti 个水果放置在 positioni 上。fruits 已经按 positioni 升序排列 ，每个 positioni 互不相同 。

另给你两个整数 startPos 和 k 。最初，你位于 startPos 。从任何位置，你可以选择 向左或者向右 走。在 x 轴上每移动 一个单位 ，就记作 一步 。你总共可以走 最多 k 步。你每达到一个位置，都会摘掉全部的水果，水果也将从该位置消失（不会再生）。

返回你可以摘到水果的 最大总数 。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/11/21/1.png)
```
输入：fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
输出：9
解释：
最佳路线为：
- 向右移动到位置 6 ，摘到 3 个水果
- 向右移动到位置 8 ，摘到 6 个水果
移动 3 步，共摘到 3 + 6 = 9 个水果
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/11/21/2.png)
```
输入：fruits = [[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]], startPos = 5, k = 4
输出：14
解释：
可以移动最多 k = 4 步，所以无法到达位置 0 和位置 10 。
最佳路线为：
- 在初始位置 5 ，摘到 7 个水果
- 向左移动到位置 4 ，摘到 1 个水果
- 向右移动到位置 6 ，摘到 2 个水果
- 向右移动到位置 7 ，摘到 4 个水果
移动 1 + 3 = 4 步，共摘到 7 + 1 + 2 + 4 = 14 个水果
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2021/11/21/3.png)

```
输入：fruits = [[0,3],[6,4],[8,5]], startPos = 3, k = 2
输出：0
解释：
最多可以移动 k = 2 步，无法到达任一有水果的地方
```
提示：

* 1 <= fruits.length <= 105
* fruits[i].length == 2
* 0 <= startPos, positioni <= 2 * 105
* 对于任意 i > 0 ，positioni-1 < positioni 均成立（下标从 0 开始计数）
* 1 <= amounti <= 104
* 0 <= k <= 2 * 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-fruits-harvested-after-at-most-k-steps
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 前缀和+二分

简单分析一下，发现无非就是线段 [l, r] 覆盖了多少水果。

线段有多少种可能呢？假设人向左走 y 步，然后回到原点，再向右走 x 步，那么区间长度就是：x + 2y，其中 x + 2y ≤k ，区间表示为 [startPos - y, startPos + x] 。

同理，如果向右走 y 步，然后回到原点，再向左走 x 步，那么区间表示为 [startPos - x, startPos + y] 。

所以我们枚举 y 长度就可以把所有最长线段都枚举出来：
```c++
for (int x = k; x >= 0; -- x)
{
    int y = (k - x) / 2;
    int l, r;
    // x + 2y = k
    l = startPos - x, r = startPos + y;
    ans = max(线段 [l, r] 覆盖了多少水果, ans)
    // 2y + x = k
    l = startPos - y, r = startPos + x;
    ans = max(线段 [l, r] 覆盖了多少水果, ans)
}
```
那么，如何求 线段 [l, r] 覆盖了多少水果 ？

很容易想到**前缀和预处理，累加一下各个水果节点数量，然后二分找 l 和 r 各自对应的水果节点。**

完整代码如下:
```c++
class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        
        // 前缀和，用于求区间 [l, r] 共有多少水果
        vector<int> sum;
        sum.push_back(0);
        for (int i = 1; i <= n; ++ i)
            sum.push_back(fruits[i - 1][1] + sum[i - 1]);

        vector<int> pos;
        for (int i = 0; i < n; ++ i)
            pos.push_back(fruits[i][0]);

        // 枚举可能抵达的区间
        int ans = 0;
        for (int x = k; x >= 0; -- x)
        {
            int y = (k - x) / 2;
            int l, r;
            // x + 2y = k
            l = startPos - x, r = startPos + y;
            //lower_bound() 函数用于在指定区域内查找不小于目标值的第一个元素。
            //upper_bound() 函数用于在指定区域内查找不大于目标值的第一个元素。
            //使用这两个函数来保持寻找的位置在【l，r】区间内。
            auto pl = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
            auto pr = upper_bound(pos.begin(), pos.end(), r) - pos.begin();
            ans = max(ans, sum[pr] - sum[pl]);//两边位置上的前缀和之差就是这个区间里最多的水果数量
            // 2y + x = k ，同理
            l = startPos - y, r = startPos + x;
            pl = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
            pr = upper_bound(pos.begin(), pos.end(), r) - pos.begin();
            ans = max(ans, sum[pr] - sum[pl]);
        }
        return ans;
    }
};
```
