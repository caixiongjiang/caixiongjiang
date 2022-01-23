## 编号2146：价格范围内最高排名的 K 样物品（×）

给你一个下标从 0 开始的二维整数数组 grid ，它的大小为 m x n ，表示一个商店中物品的分布图。数组中的整数含义为：

* 0 表示无法穿越的一堵墙。
* 1 表示可以自由通过的一个空格子。
* 所有其他正整数表示该格子内的一样物品的价格。你可以自由经过这些格子。

从一个格子走到上下左右相邻格子花费 1 步。

同时给你一个整数数组 pricing 和 start ，其中 pricing = [low, high] 且 start = [row, col] ，表示你开始位置为 (row, col) ，同时你只对物品价格在 闭区间 [low, high] 之内的物品感兴趣。同时给你一个整数 k 。

你想知道给定范围 内 且 排名最高 的 k 件物品的 位置 。排名按照优先级从高到低的以下规则制定：

* 1.距离：定义为从 start 到一件物品的最短路径需要的步数（较近 距离的排名更高）。
* 2.价格：较低 价格的物品有更高优先级，但只考虑在给定范围之内的价格。
* 3.行坐标：较小 行坐标的有更高优先级。
* 4.列坐标：较小 列坐标的有更高优先级。

请你返回给定价格内排名最高的 k 件物品的坐标，将它们按照排名排序后返回。如果给定价格内少于 k 件物品，那么请将它们的坐标 全部 返回。


示例 1：

![avater](https://assets.leetcode.com/uploads/2021/12/16/example1drawio.png)

```
输入：grid = [[1,2,0,1],[1,3,0,1],[0,2,5,1]], pricing = [2,5], start = [0,0], k = 3
输出：[[0,1],[1,1],[2,1]]
解释：起点为 (0,0) 。
价格范围为 [2,5] ，我们可以选择的物品坐标为 (0,1)，(1,1)，(2,1) 和 (2,2) 。
这些物品的排名为：
- (0,1) 距离为 1
- (1,1) 距离为 2
- (2,1) 距离为 3
- (2,2) 距离为 4
所以，给定价格范围内排名最高的 3 件物品的坐标为 (0,1)，(1,1) 和 (2,1) 。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/12/16/example2drawio1.png)

```
输入：grid = [[1,2,0,1],[1,3,3,1],[0,2,5,1]], pricing = [2,3], start = [2,3], k = 2
输出：[[2,1],[1,2]]
解释：起点为 (2,3) 。
价格范围为 [2,3] ，我们可以选择的物品坐标为 (0,1)，(1,1)，(1,2) 和 (2,1) 。
这些物品的排名为： 
- (2,1) 距离为 2 ，价格为 2
- (1,2) 距离为 2 ，价格为 3
- (1,1) 距离为 3
- (0,1) 距离为 4
所以，给定价格范围内排名最高的 2 件物品的坐标为 (2,1) 和 (1,2) 。
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2021/12/30/example3.png)

```
输入：grid = [[1,1,1],[0,0,1],[2,3,4]], pricing = [2,3], start = [0,0], k = 3
输出：[[2,1],[2,0]]
解释：起点为 (0,0) 。
价格范围为 [2,3] ，我们可以选择的物品坐标为 (2,0) 和 (2,1) 。
这些物品的排名为：
- (2,1) 距离为 5
- (2,0) 距离为 6
所以，给定价格范围内排名最高的 2 件物品的坐标为 (2,1) 和 (2,0) 。
注意，k = 3 但给定价格范围内只有 2 件物品。
```
提示：

* m == grid.length
* n == grid[i].length
* 1 <= m, n <= 10^5
* 1 <= m * n <= 10^5
* 0 <= grid[i][j] <= 10^5
* pricing.length == 2
* 2 <= low <= high <= 10^5
* start.length == 2
* 0 <= row <= m - 1
* 0 <= col <= n - 1
* grid[row][col] > 0
* 1 <= k <= m * n

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/k-highest-ranked-items-within-a-price-range
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

从起点开始BFS

注意点都在注释上了。

代码如下：
```c++
class Solution {
    typedef pair<int, int> pii;
    typedef pair<pii, pii> piiii;

    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};

public:
    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        int n = grid.size(), m = grid[0].size();
        map<pii, int> mp;//记录<pair<横纵坐标>，该坐标与起始坐标的距离>
        queue<pii> que;
        que.push(pii(start[0], start[1]));
        mp.insert(make_pair(pii(start[0], start[1]), 0));
        vector<piiii> vec;//记录<pair<距离，价格>, pair<横纵坐标>>

        //BFS
        while (!que.empty()) {
            pii t = que.front(); 
            que.pop();
            int i = t.first, j = t.second, x = grid[i][j], y = mp[t];
            if (x != 1 && x >= pricing[0] && x <= pricing[1]) vec.push_back(piiii(pii(y, x), pii(i, j)));
            for (int l = 0; l < 4; l++) {
                int dx = i + dir[l][0], dy = j + dir[l][1];
                if (dx < 0 || dy < 0 || dx >= n || dy >= m || grid[dx][dy] == 0) continue;
                if (mp.count(pii(dx, dy))) continue;
                que.push(pii(dx, dy));
                mp[pii(dx, dy)] = y + 1;
            }
        }
        //按照优先级进行排序，顺序必须是{距离，价格，横坐标，纵坐标}
        sort(vec.begin(), vec.end());

        vector<vector<int>> ans;
        k = min(k, (int)vec.size());
        for (int i = 0; i < k; i++){
            ans.push_back(vector<int>{vec[i].second.first, vec[i].second.second});
        }
        return ans;
    }
};
```
