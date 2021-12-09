给你一个字符串数组 board 表示井字游戏的棋盘。当且仅当在井字游戏过程中，棋盘有可能达到 board 所显示的状态时，才返回 true 。

井字游戏的棋盘是一个 3 x 3 数组，由字符 ' '，'X' 和 'O' 组成。字符 ' ' 代表一个空位。

以下是井字游戏的规则：

* 玩家轮流将字符放入空位（' '）中。
* 玩家 1 总是放字符 'X' ，而玩家 2 总是放字符 'O' 。
* 'X' 和 'O' 只允许放置在空位中，不允许对已放有字符的位置进行填充。
* 当有 3 个相同（且非空）的字符填充任何行、列或对角线时，游戏结束。
* 当所有位置非空时，也算为游戏结束。
* 如果游戏结束，玩家不允许再放置字符。
 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/05/15/tictactoe1-grid.jpg)

```
输入：board = ["O  ","   ","   "]
输出：false
解释：玩家 1 总是放字符 "X" 。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/05/15/tictactoe2-grid.jpg)

```
输入：board = ["XOX"," X ","   "]
输出：false
解释：玩家应该轮流放字符。
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2021/05/15/tictactoe3-grid.jpg)

```
输入：board = ["XXX","   ","OOO"]
输出：false
```
Example 4:

![avater](https://assets.leetcode.com/uploads/2021/05/15/tictactoe4-grid.jpg)

```
输入：board = ["XOX","O O","XOX"]
输出：true 
```
提示：

* board.length == 3
* board[i].length == 3
* board[i][j] 为 'X'、'O' 或 ' '

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-tic-tac-toe-state
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

给定的棋盘大小固定，对于无效情况进行分情况讨论即可：

* 1.由于 X 先手，O 后手，两者轮流下子。因此 O 的数量不会超过 X，且两者数量差不会超过 11，否则为无效局面；
* 2.若局面是 X 获胜，导致该局面的最后一个子必然是 X，此时必然有 X 数量大于 O（X 为先手），否则为无效局面；
* 3.若局面是 O 获胜，导致该局面的最后一个子必然是 O，此时必然有 X 数量等于 O（X 为先手），否则为无效局面；
* 4.局面中不可能出现两者同时赢（其中一方赢后，游戏结束）。


代码如下：
```c++
class Solution {
public:
    bool validTicTacToe(vector<string> &board) {
        int xcount = 0, ocount = 0;
        for(string & row : board){
            for(char & c : row){
                xcount = (c == 'X') ? (xcount + 1): xcount;
                ocount = (c == 'O') ? (ocount + 1): ocount;
            }
        } 
        //O和X的数量不相等时，只有O比X的数量小1才行，因为X和O是轮流放置的
        if(ocount != xcount && ocount != xcount - 1) return false;
        //X赢了，则O的数量比X小1
        if(win(board, 'X') && ocount != xcount - 1) return false;
        //O赢了，则O和X的数量相等
        if(win(board, 'O') && ocount != xcount) return false;
        return true;
    }
    //判断x字符是否赢了
    bool win(vector<string> &board, char x){
        for(int i = 0; i < 3; i++){
            //列相连
            if(x == board[i][0] && x == board[i][1] && x == board[i][2]){
                return true;
            }
            //行相连
            if(x == board[0][i] && x == board[1][i] && x == board[2][i]){
                return true;
            }
        }
        //左上到右下相连
        if(x == board[0][0] && x == board[1][1] && x == board[2][2]){
            return true;
        }
        //右上到左下相连
        if(x == board[0][2] && x == board[1][1] && x == board[2][0]){
            return true;
        }
        return false;
    }
};
```