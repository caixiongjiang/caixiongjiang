## 编号1034:边界着色

给你一个大小为 m x n 的整数矩阵 grid ，表示一个网格。另给你三个整数 row、col 和 color 。网格中的每个值表示该位置处的网格块的颜色。

当两个网格块的颜色相同，而且在四个方向中任意一个方向上相邻时，它们属于同一 连通分量 。

连通分量的边界 是指连通分量中的所有与不在分量中的网格块相邻（四个方向上）的所有网格块，或者在网格的边界上（第一行/列或最后一行/列）的所有网格块。

请你使用指定颜色 color 为所有包含网格块 grid[row][col] 的 连通分量的边界 进行着色，并返回最终的网格 grid 。

 

示例 1：

输入：grid = [[1,1],[1,2]], row = 0, col = 0, color = 3
输出：[[3,3],[3,2]]
示例 2：

输入：grid = [[1,2,2],[2,3,2]], row = 0, col = 1, color = 3
输出：[[1,3,3],[2,3,3]]
示例 3：

输入：grid = [[1,1,1],[1,1,1],[1,1,1]], row = 1, col = 1, color = 2
输出：[[2,2,2],[2,1,2],[2,2,2]]
 

提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 50
1 <= grid[i][j], color <= 1000
0 <= row < m
0 <= col < n

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/coloring-a-border
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

常规的思路是可以使用深度优先搜索或者广度优先搜索来寻找出位置 (row,col) 的所在的连通分量，额外要做的是搜索的时候需要判断当前的点是否属于边界。如果属于边界，需要把该点加入到一个用来存所有边界点的数组中。当搜索完毕后，再将所有边界点的进行着色。


### 广度优先搜索（BFS）

代码如下：
```c++
class Solution {
public:
    //按照上下左右的顺序
    int dirx[4] = {1, -1, 0, 0};
    int diry[4] = {0, 0, -1, 1};
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        int m = grid.size();
        int n = grid[0].size();
        int originalColor = grid[row][col];
        queue<pair<int, int>> que;
        vector<vector<int>> visited(m, vector<int>(n, 0));
        vector<pair<int, int>> borders;
        que.emplace(row, col);
        visited[row][col] = 1;
        while(!que.empty()){
            auto [x, y] = que.front();
            que.pop();
            bool isBorder = false;//默认不属于边界
            for(int d = 0; d < 4; d++){
                int dx = x + dirx[d];
                int dy = y + diry[d];
                //不属于连通分量就属于边界
                if(!(dx >= 0 && dx < m && dy >= 0 && dy < n && grid[dx][dy] == originalColor)){
                    isBorder = true;
                }else if(!visited[dx][dy]){ //如果没有访问过就入队
                    que.emplace(dx, dy);
                    visited[dx][dy] = 1;
                }
            }
            if(isBorder){
                borders.emplace_back(x, y);
            }
        }
        for(auto &[x, y] : borders){
            grid[x][y] = color;
        }
        return grid;
    }
};
```

### 深度优先搜索

代码如下：
```c++
typedef pair<int, int> pii;

class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pii> borders;
        int originalColor = grid[row][col];
        visited[row][col] = true;
        dfs(grid, row, col, visited, borders, originalColor);
        for (auto & [x, y] : borders) {
            grid[x][y] = color;
        }
        return grid;
    }

    void dfs(vector<vector<int>>& grid, int x, int y, vector<vector<bool>> & visited, vector<pii> & borders, int originalColor) {
        int m = grid.size(), n = grid[0].size();
        bool isBorder = false;
        int direc[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (int i = 0; i < 4; i++) {
            int nx = direc[i][0] + x, ny = direc[i][1] + y;
            if (!(nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == originalColor)) {
                isBorder = true;
            } else if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                dfs(grid, nx, ny, visited, borders, originalColor);
            }                
        }
        if (isBorder) {
            borders.emplace_back(x, y);
        }
    }
};
```

