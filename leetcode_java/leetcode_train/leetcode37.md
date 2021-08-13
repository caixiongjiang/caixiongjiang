## 编号37：解数独

编写一个程序，通过填充空格来解决数独问题。

数独的解法需 遵循如下规则：

1.数字 1-9 在每一行只能出现一次。
</br>2.数字 1-9 在每一列只能出现一次。
</br>3.数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
</br>数独部分空格内已填入了数字，空白格用 '.' 表示。
示例：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2021/04/12/250px-sudoku-by-l2g-20050714svg.png)
```
输入：board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
输出：[["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
解释：输入的数独如上图所示，唯一有效的解决方案如下所示：
```
![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2021/04/12/250px-sudoku-by-l2g-20050714_solutionsvg.png)

 

提示：

* board.length == 9
* board[i].length == 9
* board[i][j] 是一位数字或者 '.'
* 题目数据 保证 输入数独仅有一个解

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sudoku-solver
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
[N皇后问题](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode51.md)是因为每一行每一列只放一个皇后，只需要一层for循环遍历一行，递归来来遍历列，然后一行一列确定皇后的唯一位置。

本题就不一样了，**本题中棋盘的每一个位置都要放一个数字，并检查数字是否合法，解数独的树形结构要比N皇后更宽更深。**

因为这个树形结构太大了，我抽取一部分，如图所示：
![avater](https://camo.githubusercontent.com/ee23f09efc4a13a845174a1b6404b0d038bdd1e5524e662c5488a2a4cd2ac030/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032303131313732303435313739302e706e67)

## 回溯三部曲
* 递归终止条件
</br><span style="color:green">递归函数的返回值需要是bool类型，为什么呢？</span>

因为解数独找到一个符合的条件（就在树的叶子节点上）立刻就返回，相当于找从根节点到叶子节点一条唯一路径，所以需要使用bool返回值。

代码如下：
```java
boolean backTracking(char[][] board)
```

* 递归终止条件
本题递归不用终止条件，解数独是要遍历整个树形结构寻找可能的叶子节点就立刻返回。

**不用终止条件会不会死循环？**

递归的下一层的棋盘一定比上一层的棋盘多一个数，等数填满了棋盘自然就终止（填满当然好了，说明找到结果了），所以不需要终止条件！

**那么有没有永远填不满的情况呢？**

这个问题我在递归单层搜索逻辑里在来讲！

* 递归单层搜索逻辑
![avater](https://camo.githubusercontent.com/ee23f09efc4a13a845174a1b6404b0d038bdd1e5524e662c5488a2a4cd2ac030/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032303131313732303435313739302e706e67)

在树形图中可以看出我们需要的是一个二维的递归（也就是两个for循环嵌套着递归）

**一个for循环遍历棋盘的行，一个for循环遍历棋盘的列，一行一列确定下来之后，递归遍历这个位置放9个数字的可能性！**

代码如下：（**详细看注释**）
```java
for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
        if(board[i][j] != '.'){//跳过原始数字
            continue;
        }
        for(char k = '1'; k <= '9'; k++){
            if(isValidSudoku(i, j, k, board)){
                board[i][j] = k;
                if(traversing(board)){//如果找到合适一组立刻返回
                    return true;
                }
                board[i][j] = '.';//回溯
            }
        }
        //9个数都试完了，都不行，那么就返回false
        return false;
        //因为如果一行一列确定下来，这里尝试了9个数都不行，说明了这个棋盘找不到解决书店问题的解
        //那么会直接返回，【这就是为什么没有终止条件也不会永远填不满棋盘而无线递归下去】
    }
}
```

## 判断棋盘是否合法
判断棋盘是否合法有如下三个维度：

* 同行是否重复
* 同列是否重复
* 9宫格里是否重复
代码如下：
```java
public boolean isValidSudoku(int row, int col, char val, char[][] board){
    //同行是否重复
    for(int i = 0; i < 9; i++){
        if(board[row][i] == val){
            return false;
        }
    }
    //同列是否重复
    for(int j = 0; j < 9; j++){
        if(board[j][col] == val){
            return false;
        }
    }
    //九宫格里是否重复
    int startRow = (row / 3) * 3;// (row/3)是为了判断当前位置在第几行的九宫格里
    int startCol = (col / 3) * 3;// (col/3)是为了判断当前位置在第几列的九宫格里
    for(int i = startRow; i < startRow + 3; i++){
        for(int j = startCol; j < startCol + 3; j++){
            if(board[i][j] == val){
                return false;
            }
        }
    }
    return true;
}
```


整体代码如下：
```java
class Solution {
    public void solveSudoku(char[][] board) {
        traversing(board);
    }

    public boolean traversing(char[][] board){
        //[一个for循环遍历棋盘的行，一个for循环遍历棋盘的列，
        //一行一列确定下来，递归遍历这个位置放9个数字的可能性。
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] != '.'){//跳过原始数字
                    continue;
                }
                for(char k = '1'; k <= '9'; k++){
                    if(isValidSudoku(i, j, k, board)){
                        board[i][j] = k;
                        if(traversing(board)){//如果找到合适一组立刻返回
                            return true;
                        }
                        board[i][j] = '.';//回溯
                    }
                }
                //9个数都试完了，都不行，那么就返回false
                return false;
                //因为如果一行一列确定下来，这里尝试了9个数都不行，说明了这个棋盘找不到解决书店问题的解
                //那么会直接返回，【这就是为什么没有终止条件也不会永远填不满棋盘而无线递归下去】
            }
        }
        //遍历完没有返回false,说明找到了合适的棋盘位置
        return true;
    }
    /**
     * 判断棋盘是否合法有如下三个维度:
     *     同行是否重复
     *     同列是否重复
     *     9宫格里是否重复
     */
    public boolean isValidSudoku(int row, int col, char val, char[][] board){
        //同行是否重复
        for(int i = 0; i < 9; i++){
            if(board[row][i] == val){
                return false;
            }
        }
        //同列是否重复
        for(int j = 0; j < 9; j++){
            if(board[j][col] == val){
                return false;
            }
        }
        //九宫格里是否重复
        int startRow = (row / 3) * 3;// (row/3)是为了判断当前位置在第几行的九宫格里
        int startCol = (col / 3) * 3;// (col/3)是为了判断当前位置在第几列的九宫格里
        for(int i = startRow; i < startRow + 3; i++){
            for(int j = startCol; j < startCol + 3; j++){
                if(board[i][j] == val){
                    return false;
                }
            }
        }
        return true;
    }
}
```


