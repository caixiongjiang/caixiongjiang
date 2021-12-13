## 编号807:保持城市天际线

给你一座由 n x n 个街区组成的城市，每个街区都包含一座立方体建筑。给你一个下标从 0 开始的 n x n 整数矩阵 grid ，其中 grid[r][c] 表示坐落于 r 行 c 列的建筑物的 高度 。

城市的 天际线 是从远处观察城市时，所有建筑物形成的外部轮廓。从东、南、西、北四个主要方向观测到的 天际线 可能不同。

我们被允许为 任意数量的建筑物 的高度增加 任意增量（不同建筑物的增量可能不同） 。 高度为 0 的建筑物的高度也可以增加。然而，增加的建筑物高度 不能影响 从任何主要方向观察城市得到的 天际线 。

在 不改变 从任何主要方向观测到的城市 天际线 的前提下，返回建筑物可以增加的 最大高度增量总和 。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/06/21/807-ex1.png)

```
输入：grid = [[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]
输出：35
解释：建筑物的高度如上图中心所示。
用红色绘制从不同方向观看得到的天际线。
在不影响天际线的情况下，增加建筑物的高度：
gridNew = [ [8, 4, 8, 7],
            [7, 4, 7, 7],
            [9, 4, 8, 7],
            [3, 3, 3, 3] ]
```
示例 2：
```
输入：grid = [[0,0,0],[0,0,0],[0,0,0]]
输出：0
解释：增加任何建筑物的高度都会导致天际线的变化。 
```
提示：

* n == grid.length
* n == grid[r].length
* 2 <= n <= 50
* 0 <= grid[r][c] <= 100


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/max-increase-to-keep-city-skyline
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 贪心

从左侧和右侧看，城市天际线等于矩阵 grid 的每一行的建筑物高度最大值；从顶部和底部看，城市天际线等于矩阵 grid 的每一列的建筑物高度最大值。只要不改变每一行和每一列的建筑物高度最大值，就能保持城市天际线，因此可以使用贪心的思想计算建筑物高度可以增加的最大总和。

由于矩阵 grid 的行数和列数都是 n，因此创建两个长度为 n 的数组 rowMax 和 colMax 分别记录矩阵 grid 的每一行的最大值和每一列的最大值。遍历矩阵 grid 填入两个数组之后，再次遍历矩阵，计算每个建筑物高度可以增加的最大值。

当0≤i,j< n 时，对于第 i 行第 j 列的建筑物，其所在行的建筑物高度最大值是rowMax[i]，其所在列的建筑物高度最大值是colMax[j]。为了保持城市天际线，该建筑物增加后的高度不能超过其所在行和所在列的建筑物高度最大值，即该建筑物增加后的最大高度是 min(rowMax[i],colMax[j])。由于该建筑物的原始高度是 grid[i][j]，因此该建筑物高度可以增加的最大值是 min(rowMax[i],colMax[j])−grid[i][j]。

对于矩阵 grid 中的每个元素计算可以增加的最大值，即可得到建筑物高度可以增加的最大总和。

代码如下：
```c++
class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> rowMax(n);
        vector<int> colMax(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                rowMax[i] = max(rowMax[i], grid[i][j]);
                colMax[j] = max(colMax[j], grid[i][j]);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans += min(rowMax[i], colMax[j]) - grid[i][j];
            }
        }
        return ans;
    }
};
```
