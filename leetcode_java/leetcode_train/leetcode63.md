## 编号63：不同路径Ⅱ
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/robot_maze.png)


网格中的障碍物和空位置分别用 1 和 0 来表示。

 

示例 1：
![avater](https://assets.leetcode.com/uploads/2020/11/04/robot1.jpg)

```
输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
输出：2
解释：
3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：
1. 向右 -> 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右 -> 向右
```

示例 2：

![avater](https://assets.leetcode.com/uploads/2020/11/04/robot2.jpg)
```
输入：obstacleGrid = [[0,1],[0,0]]
输出：1 
```
提示：

* m == obstacleGrid.length
* n == obstacleGrid[i].length
* 1 <= m, n <= 100
* obstacleGrid[i][j] 为 0 或 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-paths-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

动规五部曲：

1.确定dp数组（dp table）以及下标的含义

dp[i][j] ：表示从（0 ，0）出发，到(i, j) 有dp[i][j]条不同的路径。

2.确定递推公式

递推公式和[62.不同路径一样](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode62.md)，dp[i][j] = dp[i - 1][j] + dp[i][j - 1]。

**但因为有了障碍，(i, j)如果就是障碍的话应该就保持初始状态（初始状态为0）。**

所以代码为：
```java
if(obstacleGrid[i][j] == 0){// 当(i，j)没有障碍的时候再推导dp[i][j]
    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
}
```

3.dp数组如何初始化

</br> 这题最大的不同就是多了障碍，除了m = 0 和n = 0为1的情况还要排除存在障碍的问题。
因为从(0, 0)的位置到(i, 0)的路径只有一条，所以dp[i][0]一定为1，dp[0][j]也同理。

但如果(i, 0) 这条边有了障碍之后，障碍之后（包括障碍）都是走不到的位置了，所以障碍之后的dp[i][0]应该还是初始值0。

如图：
![avater](https://camo.githubusercontent.com/dfb75a049324a60415c60d0dd9e75f79c2b4de612f6c14bcee9538cc7b2642b7/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303130343131343531333932382e706e67)

下标(0, j)的初始化情况同理。
</br>所以本题初始化的代码为：

```java
int[][] dp = new int[m][n];
for(int i = 0; i < m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
for(int j = 0; j < n && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1; 
```

**注意代码里for循环的终止条件，一旦遇到obstacleGrid[i][0] == 1的情况就停止dp[i][0]的赋值1的操作，dp[0][j]同理**

4.确定遍历顺序

从递归公式dp[i][j] = dp[i - 1][j] + dp[i][j - 1] 中可以看出，一定是从左到右一层一层遍历，这样保证推导dp[i][j]的时候，dp[i - 1][j] 和 dp[i][j - 1]一定是有数值。

代码如下：
```java
for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
        if(obstacleGrid[i][j] == 1) continue;
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }
}
```

5.举例推导dp数组

拿示例1来举例如题：

![avater](https://camo.githubusercontent.com/7b88f2191d6475fa5da5e041339d7ce3e0b724b637805c6138ac12353eb1128a/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303130343131343534383938332e706e67)

对应的dp数组如图：
![avater](https://camo.githubusercontent.com/2053ad430ecb7b12e306658f9f4b9fa1c1803a9994ddcaf76a49985e47b91e91/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303130343131343631303235362e706e67)

整体代码如下：
```java
class Solution {
    public int uniquePathsWithObstacles(int[][] obstacleGrid) {
        int n = obstacleGrid.length, m = obstacleGrid[0].length;
        int[][] dp = new int[n][m];
        dp[0][0] = 1 - obstacleGrid[0][0];
        //初始化
        for(int i = 1; i < m; i++){
            if(obstacleGrid[0][i] == 0 && dp[0][i - 1] == 1){
                //若本身无障碍但它的左边有障碍物这条路就走不通
                dp[0][i] = 1;
            }
        }
        for(int i = 1; i < n; i++){
            if(obstacleGrid[i][0] == 0 && dp[i - 1][0] == 1){
                //若本身无障碍但它的上边右障碍物这条路就走不通
                dp[i][0] = 1;
            }
        }
        for(int i = 1; i < n; i++){
            for(int j = 1; j < m; j++){
                if(obstacleGrid[i][j] == 1) continue;
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[n - 1][m - 1];
    }
}
```