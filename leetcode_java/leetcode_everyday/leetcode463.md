## 编号463：岛屿的周长

给定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地， grid[i][j] = 0 表示水域。

网格中的格子**水平和垂直**方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。

岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。

 

示例 1：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/12/island.png)

```
输入：grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
输出：16
解释：它的周长是上面图片中的 16 个黄色的边
```
示例 2：
```
输入：grid = [[1]]
输出：4
```
示例 3：
```
输入：grid = [[1,0]]
输出：4 
```
提示：

* row == grid.length
* col == grid[i].length
* 1 <= row, col <= 100
* grid[i][j] 为 0 或 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/island-perimeter
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

岛屿问题最容易让人想到BFS或者DFS，但是这道题还真的没有必要，别把简单问题搞复杂了。

### 解法一（模拟法）

遍历每一个空格，遇到岛屿，计算其上下左右的情况，遇到水域或者出界的情况，就可以计算边了。

如图：

![avater](https://camo.githubusercontent.com/7cdbbd825e7e2da7496294968acf4fba0552ae36fb94f6196e321c7fab566620/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3436332ee5b29be5b1bfe79a84e591a8e995bf2e706e67)

c++代码如下所示：
```c++
class Solution {
public:
    //代表上下左右四个方向上的x和y坐标的变化情况
    int direction[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
    int islandPerimeter(vector<vector<int>>& grid) {
        int result = 0;
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                if(grid[i][j] == 1){
                    for(int k = 0; k < 4; k++){       //上下左右四个方向
                        int x = i + direction[k][0];    
                        int y = j + direction[k][1];  //计算周边坐标x，y
                        if(x < 0                      //i在边界上
                                || x >= grid.size()   //i在边界上
                                || y < 0              //j在边界上
                                || y >= grid[0].size()//j在边界上
                                || grid[x][y] == 0){  //x,y位置是水域
                                    result++;
                                }
                    }
                }
            }
        }
        return result;
    }
};
```

### 解法二(数学上的方法)

计算出总的岛屿数量，因为有一对相邻两个陆地，边的总数就减2，那么在计算出相邻岛屿的数量就可以了。

<span style = "color:green">**result = 岛屿数量 * 4 - cover * 2;**</span>

如图：

![avater](https://camo.githubusercontent.com/f2e76b3b2668f75c857cd3ea84a6dbc37f7607c20c42ba164e2810148199769d/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3436332ee5b29be5b1bfe79a84e591a8e995bf312e706e67)

c++代码如下所示：
```c++
class Solution{
public:
    int islandPerimeter(vector<vector<int>>& grid){
        int sum = 0;    //陆地数量
        int cover = 0;  //相邻数量
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                if(grid[i][j] == 1){
                    sum++;
                    //统计上边的相邻陆地
                    if(i - 1 >= 0 && grid[i - 1][j] == 1) cover++;
                    //统计左边的相邻陆地
                    if(j - 1 >= 0 && grid[i][j - 1] == 1) cover++;
                    //这里不统计下边和右边，是为了避免重复统计
                 }
            }
        }
        return sum * 4 - cover * 2; 
    }
};
```