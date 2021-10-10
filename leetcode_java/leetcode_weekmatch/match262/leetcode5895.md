## 编号5895：获取单值网格的最小操作数

给你一个大小为 m x n 的二维整数网格 grid 和一个整数 x 。每一次操作，你可以对 grid 中的任一元素 加 x 或 减 x 。

单值网格 是全部元素都相等的网格。

返回使网格化为单值网格所需的 最小 操作数。如果不能，返回 -1 。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/09/21/gridtxt.png)

```
输入：grid = [[2,4],[6,8]], x = 2
输出：4
解释：可以执行下述操作使所有元素都等于 4 ： 
- 2 加 x 一次。
- 6 减 x 一次。
- 8 减 x 两次。
共计 4 次操作。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/09/21/gridtxt-1.png)
```
输入：grid = [[1,5],[2,3]], x = 1
输出：5
解释：可以使所有元素都等于 3 。
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2021/09/21/gridtxt-2.png)

```
输入：grid = [[1,2],[3,4]], x = 2
输出：-1
解释：无法使所有元素相等。 
```
提示：

* m == grid.length
* n == grid[i].length
* 1 <= m, n <= 105
* 1 <= m * n <= 105
* 1 <= x, grid[i][j] <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-operations-to-make-a-uni-value-grid
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路