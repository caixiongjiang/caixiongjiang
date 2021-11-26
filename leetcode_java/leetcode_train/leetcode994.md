## 编号994:腐烂的橘子

在给定的网格中，每个单元格可以有以下三个值之一：

* 值 0 代表空单元格；
* 值 1 代表新鲜橘子；
* 值 2 代表腐烂的橘子。
每分钟，任何与腐烂的橘子（在 4 个正方向上）相邻的新鲜橘子都会腐烂。

返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1。

 

示例 1：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/02/16/oranges.png)

```
输入：[[2,1,1],[1,1,0],[0,1,1]]
输出：4
```
示例 2：
```
输入：[[2,1,1],[0,1,1],[1,0,1]]
输出：-1
解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个正向上。
```
示例 3：
```
输入：[[0,2]]
输出：0
解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。
```
提示：

* 1 <= grid.length <= 10
* 1 <= grid[0].length <= 10
* grid[i][j] 仅为 0、1 或 2

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rotting-oranges
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 广度优先搜索

这道题的思路和[01矩阵](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode542.md)相似。

整体做法：先将所有腐烂的🍊入队，从这里开始向外进行广度优先搜索，每一轮遇到新鲜🍊就将它腐烂，最后判断是否所有的🍊都腐烂了，计算需要的时间。

需要两个数组，一个dist记录腐烂grid[i][j]处的🍊所需要的时间，一个visted记录grid[i][j]处的🍊是否被访问过。

代码如下：
```c++
class Solution {
public:
    int dirs[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n));//记录所需要的时间
        vector<vector<int>> visited(m, vector<int>(n));
        queue<pair<int, int>> que;
        int step = 0;//最终需要的时间
        int cnt = 0;//记录新鲜橘子的数量
        //将所有的腐烂的橘子加入初始队列
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 2){
                    que.emplace(i, j);
                    visited[i][j] = 1;
                    dist[i][j] = 0;
                }else if(grid[i][j] == 1){
                    cnt += 1;
                }
            }
        }        

        //广度优先搜索
        while(!que.empty()){
            auto [i, j] = que.front();
            que.pop();
            for(int d = 0; d < 4; d++){
                int dx = i + dirs[d][0];
                int dy = j + dirs[d][1];
                if(dx < 0 || dx >= m || dy < 0 || dy >= n || visited[dx][dy] || !grid[dx][dy]){
                    continue;
                }
                dist[dx][dy] = dist[i][j] + 1;
                visited[dx][dy] = 1;
                que.emplace(dx, dy);
                if(grid[dx][dy] == 1){
                    cnt -= 1;
                    step = dist[dx][dy];
                    if(cnt == 0) break;
                }
            }
        }
        return cnt ? -1 : step;//新鲜橘子数量大于0说明不能全部腐烂，等于0说明全部腐烂了
    }
};
```