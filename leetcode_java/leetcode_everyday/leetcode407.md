## 编号407：接雨水 II

给你一个 m x n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度，请计算图中形状最多能接多少体积的雨水。

 

示例 1:

![avater](https://assets.leetcode.com/uploads/2021/04/08/trap1-3d.jpg)

```
输入: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
输出: 4
解释: 下雨后，雨水将会被上图蓝色的方块中。总的接雨水量为1+2+1=4。
```
示例 2:

![avater](https://assets.leetcode.com/uploads/2021/04/08/trap2-3d.jpg)

```
输入: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
输出: 10
```
提示:

* m == heightMap.length
* n == heightMap[i].length
* 1 <= m, n <= 200
* 0 <= heightMap[i][j] <= 2 * 104
 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/trapping-rain-water-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 方法一：最小堆
### 思路与算法

本题为经典题目，解题的原理和方法都可以参考[42.接雨水](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode42.md)，本题主要从一维数组变成了二维数组。
首先我们思考一下什么样的方块一定可以接住水：

* 该方块不为最外层的方块；
* 该方块自身的高度比其上下左右四个相邻的方块接水后的高度都要低；

我们假设方块的索引为 (i,j)，方块的高度为heightMap[i][j]，方块接水后的高度为water[i][j]。则我们知道方块 (i,j) 的接水后的高度为：

water[i][j]=max(heightMap[i],min(water[i−1][j],water[i+1][j],water[i][j−1],water[i][j+1]))

我们知道方块 (i,j) 实际接水的容量计算公式为water[i][j]−heightMap[i][j]。
首先我们可以确定的是，矩阵的最外层的方块接水后的高度就是方块的自身高度，因为最外层的方块无法接水，因此最外层的方块water[i][j]=heightMap[i][j]。

根据木桶原理，接到的雨水的高度由这个容器周围最短的木板来确定的。我们可以知道容器内水的高度取决于最外层高度最低的方块，如图1所示：

![avater](https://assets.leetcode-cn.com/solution-static/407/407_1.PNG)

我们假设已经知道最外层的方块接水后的高度的最小值，则此时我们根据木桶原理，肯定可以确定最小高度方块的相邻方块的接水高度。我们同时更新最外层的方块标记，我们在新的最外层的方块再次找到接水后的高度的最小值，同时确定与其相邻的方块的接水高度，如图 2 所示:

![avater](https://assets.leetcode-cn.com/solution-static/407/407_2.PNG)

然后再次更新最外层，依次迭代直到求出所有的方块的接水高度，即可知道矩阵中的接水容量。

代码如下：
```c++
typedef pair<int,int> pii;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {  
        if (heightMap.size() <= 2 || heightMap[0].size() <= 2) {
            return 0;
        }  
        int m = heightMap.size();
        int n = heightMap[0].size();
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        vector<vector<bool>> visit(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    pq.push({heightMap[i][j], i * n + j});
                    visit[i][j] = true;
                }
            }
        }

        int res = 0;
        int dirs[] = {-1, 0, 1, 0, -1};
        while (!pq.empty()) {
            pii curr = pq.top();
            pq.pop();            
            for (int k = 0; k < 4; ++k) {
                int nx = curr.second / n + dirs[k];
                int ny = curr.second % n + dirs[k + 1];
                if( nx >= 0 && nx < m && ny >= 0 && ny < n && !visit[nx][ny]) {
                    if (heightMap[nx][ny] < curr.first) {
                        res += curr.first - heightMap[nx][ny]; 
                    }
                    visit[nx][ny] = true;
                    pq.push({max(heightMap[nx][ny], curr.first), nx * n + ny});
                }
            }
        }
        
        return res;
    }
};
```

### 方法二：广度优先搜索
### 思路与算法

我们假设初始时矩阵的每个格子都接满了水，且高度均为 \textit{maxHeight}maxHeight，其中 \textit{maxHeight}maxHeight 为矩阵中高度最高的格子。我们知道方块接水后的高度为water[i][j]，它的求解公式与方法一样。方块 (i,j) 的接水后的高度为：

water[i][j]=max(heightMap[i],min(water[i−1][j],water[i+1][j],water[i][j−1],water[i][j+1]))

我们知道方块 (i,j) 实际接水的容量计算公式为water[i][j]−heightMap[i][j]。
我们首先假设每个方块 (i,j) 的接水后的高度均为water[i][j]=maxHeight，首先我们知道最外层的方块的肯定不能接水，所有的多余的水都会从最外层的方块溢出，我们每次发现当前方块 (i,j) 的接水高度water[i][j] 小于与它相邻的4个模块的接水高度时，则我们将进行调整接水高度，我们将其相邻的四个方块的接水高度调整与 (i,j) 的高度保持一致，我们不断重复的进行调整，直到所有的方块的接水高度不再有调整时即为满足要求。

代码如下：
```c++
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size(), n = heightMap[0].size();
        int maxHeight = 0;
        int dirs[] = {-1, 0, 1, 0, -1};

        for (int i = 0; i < m; ++i) {
            maxHeight = max(maxHeight, *max_element(heightMap[i].begin(), heightMap[i].end()));
        }
        vector<vector<int>> water(m, vector<int>(n, maxHeight));
        queue<pair<int,int>> qu;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    if (water[i][j] > heightMap[i][j]) {
                        water[i][j] = heightMap[i][j];
                        qu.push(make_pair(i, j));
                    }
                }
            }
        }        
        while (!qu.empty()) {
            int x = qu.front().first, y = qu.front().second;
            qu.pop();
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i], ny = y + dirs[i + 1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                    continue;
                }
                if (water[x][y] < water[nx][ny] && water[nx][ny] > heightMap[nx][ny]) {
                    water[nx][ny] = max(water[x][y], heightMap[nx][ny]);
                    qu.push(make_pair(nx, ny));
                }
            }
        }

        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res += water[i][j] - heightMap[i][j];
            }
        }
        return res;
    }
};
```

