## 编号5895：获取单值网格的最小操作数(AC)

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

## 我的题解

整体代码如下：
```c++
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int n = grid.size();
        int m = grid[0].size();
        //将二维数组先转化为一维数组
        vector<int> vec;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                vec.push_back(grid[i][j]);
            }
        }
        //排序
        sort(vec.begin(), vec.end());
        for(int i = 0; i < vec.size(); i++){
            if(vec[i] % x != vec[0] % x){
                return -1;
            }
        }
        //定义中位数
        int pos = vec.size() / 2;
        int mid = vec[pos];
        int ans = 0;
        for(int i = 0; i < pos; i++){
            ans += (mid - vec[i]) / x;
        }
        for(int i = pos; i < vec.size(); i++){
            ans += (vec[i] - mid) / x;
        }
        return ans;
    }
};
```

## 贪心

首先，所有数如果不是关于X同余，则本题显然无解。

**在所有数关于X同余的情况下，我们可以将所有数除以X**。这时就变成了经典的数轴集合问题（N个人在数轴上，要集合到一个位置使得所有人移动距离之和最小），最优的集合位置就是中位数。我们找到这些数的中位数，再计算总距离（也即总操作数）即可。

寻找中位数可以排序；也可以使用快速选择算法（比如C++中的nth_element），以得到更优的时间复杂度。

我自己AC的代码中使用排序寻找中位数。

* 时间复杂度O(NM)。
* 空间复杂度O(NM)。

整体代码如下：
```c++
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int n = grid.size(), m = grid[0].size(), mod = grid[0][0] % x;
        vector<int> v;
        for (auto &row : grid)
            for (int cell : row) {
                if (cell % x != mod)
                    return -1;
                v.emplace_back(cell / x);
            }
        int mid = n * m / 2;
        nth_element(v.begin(), v.begin() + mid, v.end());
        int ans = 0;
        for (int vi : v)
            ans += abs(vi - v[mid]);
        return ans;
    }
};
```
