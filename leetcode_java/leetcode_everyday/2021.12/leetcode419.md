## 编号419:甲板上的战舰

给你一个大小为 m x n 的矩阵 board 表示甲板，其中，每个单元格可以是一艘战舰 'X' 或者是一个空位 '.' ，返回在甲板 board 上放置的 战舰 的数量。

战舰 只能水平或者垂直放置在 board 上。换句话说，战舰只能按 1 x k（1 行，k 列）或 k x 1（k 行，1 列）的形状建造，其中 k 可以是任意大小。两艘战舰之间至少有一个水平或垂直的空位分隔 （即没有相邻的战舰）。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/04/10/battelship-grid.jpg)

```
输入：board = [["X",".",".","X"],[".",".",".","X"],[".",".",".","X"]]
输出：2
```
示例 2：
```
输入：board = [["."]]
输出：0 
```
提示：

* m == board.length
* n == board[i].length
* 1 <= m, n <= 200
* board[i][j] 是 '.' 或 'X'

**进阶**：你可以实现一次扫描算法，并只使用 O(1) 额外空间，并且不修改 board 的值来解决这个问题吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/battleships-in-a-board
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 脑筋急转弯（进阶要求的解法）

题目要求我们寻找战舰的数量（只要相连就只算一架战舰），如果我们的遍历方式为左上到右下，我们可以将左边或者上边已经有x的方格跳过不计数，这样就不会重复计数。

代码如下：
```c++
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();
        int ret = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(j > 0 && board[i][j - 1] == 'X') continue;
                if(i > 0 && board[i - 1][j] == 'X') continue;
                if(board[i][j] == 'X') ret++;
            }
        }
        return ret;
    }
};
```

### 遍历扫描(复杂度较高)

题目要求找到矩阵中战舰的数量，战舰用 ’X’ 表示，空位用 ’.’，而矩阵中的战舰的满足以下两个条件：

* 战舰只能水平或者垂直放置。战舰只能由子矩阵（1 行，N 列）组成，或者子矩阵（N 行, 1 列）组成，其中 N 可以是任意大小。
* 两艘战舰之间至少有一个水平或垂直的空位分隔，没有相邻的战舰。
我们遍历矩阵中的每个位置 (i,j) 且满足 board[i][j]=’X’，并将以 (i,j) 为起点的战舰的所有位置均设置为空位，从而我们即可统计出所有可能的战舰。

代码如下：
```c++
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int row = board.size();
        int col = board[0].size();
        int ans = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (board[i][j] == 'X') {
                    board[i][j] = '.';
                    for (int k = j + 1; k < col && board[i][k] == 'X'; ++k) {
                        board[i][k] = '.';
                    }                    
                    for (int k = i + 1; k < row && board[k][j] == 'X'; ++k) {
                        board[k][j] = '.';
                    }
                    ans++;
                }
            }
        }
        return ans;
    }
};
```


