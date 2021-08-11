## 编号51：N皇后

**n 皇后问题** 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回所有不同的 **n 皇后问题** 的解决方案。

每一种解法包含一个不同的 **n 皇后问题** 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

 

示例 1：
![avater](https://assets.leetcode.com/uploads/2020/11/13/queens.jpg)
```
输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。
```
示例 2：
```
输入：n = 1
输出：[["Q"]] 
```
提示：

* 1 <= n <= 9
* 皇后彼此不能相互攻击，也就是说：任何两个皇后都不能处于同一条横行、纵行或斜线上。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
n皇后问题是回溯算法解决的经典问题，但是用回溯解决多了组合、切割、子集、排列问题之后，遇到这种二位矩阵还会有点不知所措。

首先来看一下皇后们的约束条件：

</br>1.不能同行
</br>2.不能同列
</br>3.不能同斜线
</br>确定完约束条件，来看看究竟要怎么去搜索皇后们的位置，其实搜索皇后的位置，可以抽象为一棵树。

下面我用一个3 * 3 的棋牌，将搜索过程抽象为一颗树，如图：
![avater](https://camo.githubusercontent.com/b662efc3d23bb487d910e79df9c8dcd5a4bc8d3c73e4a96bda8717cce5038856/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303133303138323533323330332e6a7067)
从图中，可以看出，二维矩阵中矩阵的高就是这颗树的高度，矩阵的宽就是树形结构中每一个节点的宽度。

那么我们用皇后们的约束条件，来回溯搜索这颗树，**只要搜索到了树的叶子节点，说明就找到了皇后们的合理位置了。**

## 回溯三部曲
* 递归函数参数
定义全局变量二维数组result来记录最终结果。

参数n是棋牌的大小，然后用row来记录当前遍历到棋盘的第几层了。
代码如下：
```java
List<List<String>> res;
public void backTracking(int n, int row, char[][] chessboard)
```

* 递归终止条件
当递归到棋盘最底层（也就是叶子节点）的时候，就可以收集结果并返回了。

代码如下：
```java
if (row == n) {
    result.add(myArrayList(chessboard));
    return;
}
```

* 单层搜索的逻辑
递归深度就是row控制棋盘的行，每一层里for循环的col控制棋盘的列，一行一列，确定了放置皇后的位置。

每次都是要从新的一行的起始位置开始搜，所以都是从0开始。

代码如下：
```java
for(int col = 0;col < n; col++){//col代表列
    if(isValid(row, col, n, chessboard)){
        chessboard[row][col] = 'Q';
        backTracking(n, row + 1, chessboard);
        chessboard[row][col] = '.';
    }
}
```
* 验证棋盘是否合法
代码如下：
```java
public boolean isValid(int row, int col, int n, char[][] chessboard){
        //n每次都在递增，没有必要判断是否在同一行
        //检查列
        for(int i = 0; i < n; i++){
            if(chessboard[i][col] == 'Q'){
                return false;
            }
        }
        //检查45°斜线
        for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--){
            if(chessboard[i][j] == 'Q'){
                return false;
            }
        }
        //检查135°斜线
        for(int i = row - 1, j = col + 1; i >= 0 && j <= n-1; i--, j++){
            if(chessboard[i][j] == 'Q'){
                return false;
            }
        }
        return true;
    }
}
```

整体代码如下：
```java
class Solution {
    List<List<String>> res = new ArrayList<>();

    public List<List<String>> solveNQueens(int n) {
        //构造棋盘并初始化
        char[][] chessboard = new char[n][n];
        for(char[] c : chessboard){
            Arrays.fill(c, '.');
        }
        
        backTracking(n, 0, chessboard);
        return res;
    }
    //默认第n个皇后放在第n行
    public void backTracking(int n, int row, char[][] chessboard){
        if(row == n){
            res.add(myArrayList(chessboard));
            return;
        }

        for(int col = 0;col < n; col++){//col代表列
            if(isValid(row, col, n, chessboard)){
                chessboard[row][col] = 'Q';
                backTracking(n, row + 1, chessboard);
                chessboard[row][col] = '.';
            }
        }
    }

    public List myArrayList(char[][] chessboard){
        List<String> list = new ArrayList<>();

        for(char[] c : chessboard){
            list.add(String.copyValueOf(c));
        }
        return list;
    }

    /*
        row代表行,col代表列,n代表第n个皇后，chessboard二维数组模拟棋盘    
     */
    public boolean isValid(int row, int col, int n, char[][] chessboard){
        //n每次都在递增，没有必要判断是否在同一行
        //检查列
        for(int i = 0; i < n; i++){
            if(chessboard[i][col] == 'Q'){
                return false;
            }
        }
        //检查45°斜线
        for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--){
            if(chessboard[i][j] == 'Q'){
                return false;
            }
        }
        //检查135°斜线
        for(int i = row - 1, j = col + 1; i >= 0 && j <= n-1; i--, j++){
            if(chessboard[i][j] == 'Q'){
                return false;
            }
        }
        return true;
    }
}
```