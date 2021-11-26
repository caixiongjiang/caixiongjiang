## 编号542:01矩阵

给定一个由 0 和 1 组成的矩阵 mat ，请输出一个大小相同的矩阵，其中每一个格子是 mat 中对应位置元素到最近的 0 的距离。

两个相邻元素间的距离为 1 。

 

示例 1：

![avater](https://pic.leetcode-cn.com/1626667201-NCWmuP-image.png)

```
输入：mat = [[0,0,0],[0,1,0],[0,0,0]]
输出：[[0,0,0],[0,1,0],[0,0,0]]
```
示例 2：

![avater](https://pic.leetcode-cn.com/1626667205-xFxIeK-image.png)

```
输入：mat = [[0,0,0],[0,1,0],[1,1,1]]
输出：[[0,0,0],[0,1,0],[1,2,1]]
```
提示：

* m == mat.length
* n == mat[i].length
* 1 <= m, n <= 104
* 1 <= m * n <= 104
* mat[i][j] is either 0 or 1.
* mat 中至少有一个 0 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/01-matrix
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 广度优先搜索
* 我们需要对于每一个 1 找到离它最近的 0。如果只有一个 0 的话，我们从这个 0 开始广度优先搜索就可以完成任务了；

* 但在实际的题目中，我们会有不止一个 0。我们会想，要是我们可以把这些 0 看成一个整体好了。有了这样的想法，我们可以添加一个「超级零」，它与矩阵中所有的 00 相连，这样的话，任意一个 1 到它最近的 0 的距离，会等于这个 1 到「超级零」的距离减去一。由于我们只有一个「超级零」，我们就以它为起点进行广度优先搜索。这个「超级零」只和矩阵中的 0 相连，所以在广度优先搜索的第一步中，「超级零」会被弹出队列，而所有的 0 会被加入队列，它们到「超级零」的距离为 1。这就等价于：一开始我们就将所有的 0 加入队列，它们的初始距离为 0。这样以来，在广度优先搜索的过程中，我们每遇到一个 1，就得到了它到「超级零」的距离减去一，也就是 这个 1 到最近的 0 的距离。

下图中就展示了我们方法：

![avater](https://assets.leetcode-cn.com/solution-static/542_fig1.PNG)

熟悉「最短路」的读者应该知道，我们所说的「超级零」实际上就是一个「超级源点」。在最短路问题中，如果我们要求多个源点出发的最短路时，一般我们都会建立一个「超级源点」连向所有的源点，用「超级源点」到终点的最短路等价多个源点到终点的最短路。

代码如下：
```c++
class Solution { 
public:
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, 0));
        vector<vector<int>> seen(m, vector<int>(n, 0));
        queue<pair<int, int>> que;
        //将所有的0添加进初始队列
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(mat[i][j] == 0){
                    que.emplace(i, j);
                    seen[i][j] = 1;
                }
            }
        }

        //广度优先搜索
        while(!que.empty()){
            auto [i, j] = que.front();
            que.pop();
            for(int d = 0; d < 4; d++){
                int ni = i + dirs[d][0];
                int nj = j + dirs[d][1];
                if(ni >= 0 && ni < m && nj >= 0 && nj < n && !seen[ni][nj]){
                    dist[ni][nj] = dist[i][j] + 1;
                    que.emplace(ni, nj);
                    seen[ni][nj] = 1;
                }
            }
        }
        return dist;
    }
};
```

### 动态规划

对于矩阵中的任意一个 1 以及一个 0，我们如何从这个 1 到达 0 并且距离最短呢？根据上面的做法，我们可以从 1 开始，先在水平方向移动，直到与 0 在同一列，随后再在竖直方向上移动，直到到达 0 的位置。这样一来，从一个固定的 1 走到任意一个 0，在距离最短的前提下可能有四种方法：

* 只有 水平向左移动 和 竖直向上移动；

* 只有 水平向左移动 和 竖直向下移动；

* 只有 水平向右移动 和 竖直向上移动；

* 只有 水平向右移动 和 竖直向下移动。

例如下面这一个矩阵包含四个 0。从中心位置的 1 移动到这四个 0，就需要使用四种不同的方法：

```
0 _ _ _ 0
_ _ _ _ _
_ _ 1 _ _
_ _ _ _ _
0 _ _ _ 0
```
这样以来，我们就可以使用动态规划解决这个问题了。我们用 f(i,j) 表示位置 (i,j) 到最近的 00 的距离。如果我们只能「水平向左移动」和「竖直向上移动」，那么我们可以向上移动一步，再移动 f(i−1,j) 步到达某一个 0，也可以向左移动一步，再移动 f(i,j−1) 步到达某一个 00。因此我们可以写出如下的状态转移方程：
```c++
dp[i][j] = 1 + min(f[i - 1][j],f[i][j - 1]);
```

代码如下：
```c++
//动态规划
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // 初始化动态规划的数组，所有的距离值都设置为一个很大的数
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX / 2));
        // 如果 (i, j) 的元素为 0，那么距离为 0
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                }
            }
        }
        // 只有 水平向左移动 和 竖直向上移动，注意动态规划的计算顺序
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                }
                if (j - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }
        // 只有 水平向左移动 和 竖直向下移动，注意动态规划的计算顺序
        for (int i = m - 1; i >= 0; --i) {
            for (int j = 0; j < n; ++j) {
                if (i + 1 < m) {
                    dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
                }
                if (j - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }
        // 只有 水平向右移动 和 竖直向上移动，注意动态规划的计算顺序
        for (int i = 0; i < m; ++i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                }
                if (j + 1 < n) {
                    dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
                }
            }
        }
        //只有 水平向右移动 和 竖直向下移动，注意动态规划的计算顺序
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i + 1 < m) {
                    dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
                }
                if (j + 1 < n) {
                    dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
                }
            }
        }
        return dist;
    }
};
```



### 动态规划的常数级优化

方法二中的代码有一些重复计算的地方。实际上，我们只需要保留

* 只有 水平向左移动 和 竖直向上移动；

* 只有 水平向右移动 和 竖直向下移动。

这两者即可。

代码如下：
```c++
//动态规划
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // 初始化动态规划的数组，所有的距离值都设置为一个很大的数
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX / 2));
        // 如果 (i, j) 的元素为 0，那么距离为 0
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                }
            }
        }
        // 只有 水平向左移动 和 竖直向上移动，注意动态规划的计算顺序
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                }
                if (j - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }
        // 只有 水平向左移动 和 竖直向下移动，注意动态规划的计算顺序
        // for (int i = m - 1; i >= 0; --i) {
        //     for (int j = 0; j < n; ++j) {
        //         if (i + 1 < m) {
        //             dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
        //         }
        //         if (j - 1 >= 0) {
        //             dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
        //         }
        //     }
        // }
        // 只有 水平向右移动 和 竖直向上移动，注意动态规划的计算顺序
        // for (int i = 0; i < m; ++i) {
        //     for (int j = n - 1; j >= 0; --j) {
        //         if (i - 1 >= 0) {
        //             dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
        //         }
        //         if (j + 1 < n) {
        //             dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
        //         }
        //     }
        // }
        //只有 水平向右移动 和 竖直向下移动，注意动态规划的计算顺序
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i + 1 < m) {
                    dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
                }
                if (j + 1 < n) {
                    dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
                }
            }
        }
        return dist;
    }
};
//成功超过100%
```