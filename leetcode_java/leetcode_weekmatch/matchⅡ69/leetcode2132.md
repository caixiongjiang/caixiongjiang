## 编号2132：用邮票贴满网格图（×）

给你一个 m x n 的二进制矩阵 grid ，每个格子要么为 0 （空）要么为 1 （被占据）。

给你邮票的尺寸为 stampHeight x stampWidth 。我们想将邮票贴进二进制矩阵中，且满足以下 限制 和 要求 ：

* 1.覆盖所有 空 格子。
* 2.不覆盖任何 被占据 的格子。
* 3.我们可以放入任意数目的邮票。
* 4.邮票可以相互有 重叠 部分。
* 5.邮票不允许 旋转 。
* 6.邮票必须完全在矩阵 内 。
* 7如果在满足上述要求的前提下，可以放入邮票，请返回 true ，否则返回 false 。



示例 1：

![avater](https://assets.leetcode.com/uploads/2021/11/03/ex1.png)

```
输入：grid = [[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0]], stampHeight = 4, stampWidth = 3
输出：true
解释：我们放入两个有重叠部分的邮票（图中标号为 1 和 2），它们能覆盖所有与空格子。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/11/03/ex2.png)
```
输入：grid = [[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]], stampHeight = 2, stampWidth = 2 
输出：false 
解释：没办法放入邮票覆盖所有的空格子，且邮票不超出网格图以外。
```
提示：

* m == grid.length
* n == grid[r].length
* 1 <= m, n <= 105
* 1 <= m * n <= 2 * 105
* grid[r][c] 要么是 0 ，要么是 1 。
* 1 <= stampHeight, stampWidth <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/stamping-the-grid
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 二维前缀和 + 二维差分

首先自己先看了一下什么是二维前缀和，可以看下这个[csdn上网址](https://www.cnblogs.com/acioi/p/11705205.html#%E4%BA%8C%E7%BB%B4%E5%89%8D%E7%BC%80%E5%92%8C)的解释。

其实用一句话来说就是

在网格中 f[i][j] = {从网格左上角0，0到i，j组成的长方形的和}

如图所示：

![avater](https://cdn.luogu.com.cn/upload/image_hosting/0dwklyet.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们将其分成四个部分

![avater](https://cdn.luogu.com.cn/upload/image_hosting/cjmiifza.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

整个方块的的面积等于黑色方块加上两个黄色方块加上一个红色方块，而每个黄色方块可以通过大方块减去红色方块来得到

显而易见，前缀和的公式就出来了。

**二维前缀和的递推公式**：

f[i][j] = f[i−1][j] + f[i][j−1] - f[i−1][j−1] + grid[i][j]

我又去看了二维差分是什么意思，出自[这个网址](https://blog.csdn.net/justidle/article/details/104506724)

看图：
![avater](https://img-blog.csdnimg.cn/20200225221053457.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2p1c3RpZGxl,size_16,color_FFFFFF,t_70)

二维差分的公式为

p[i][j] = f[i][j] - f[i - 1][j] - f[i][j - 1] + f[i - 1][j - 1]


二维前缀和与二位差分以及原矩阵的关系看下图

![avater](https://pic2.zhimg.com/80/v2-9e6a70869ff205c1a1a2384b3b3a61a1_1440w.jpg)


<span style = "color:green">**所以本题是通过求二维前缀和在进行二维差分来判断从i-h，j-w到i，j组成的方块是否存在×（也就是邮票是否能贴上）**</span>

思路就很明显了！（思路copy的[newhar的题解](https://leetcode-cn.com/problems/stamping-the-grid/solution/er-wei-qian-zhui-he-er-wei-chai-fen-by-n-wlzw/)）

1.在矩阵中标记所有的可放置邮票的区域；

2.对矩阵求二维前缀和；

3.检查矩阵中是否存在值为 00 的点。如果存在，那么该点无法被邮票覆盖。

建议可以去练习一下304题。

代码如下：(代码参考的有注释的版本：[CodeBugZore的题解](https://leetcode-cn.com/problems/stamping-the-grid/solution/2022nian-jing-sai-yi-ding-shang-2022fen-1kd5e/))
```c++
class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int h, int w) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> sums(n + 1, vector<int>(m + 1)); // 前缀和数组用于检查是否能放
        vector<vector<int>> diff(n + 2, vector<int>(m + 2)); // 差分数组用于标记放置点
        
        for(int i = 1; i <= n; ++i) // 初始化前缀和数组
        {
            for(int j = 1; j <= m; ++j)
            {
                sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + grid[i - 1][j - 1];
            }
        }
        
        for(int i = h; i <= n; ++i) // 利用差分标记可放置的点
        {
            for(int j = w; j <= m; ++j)
            {
                int x = sums[i][j] - sums[i - h][j] - sums[i][j - w] + sums[i - h][j - w];
                if(x == 0) // 可以放置
                {
                    ++diff[i - h + 1][j - w + 1];
                    --diff[i - h + 1][j + 1];
                    --diff[i + 1][j - w + 1];
                    ++diff[i + 1][j + 1];
                }
            }
        }
        
        // 利用前缀和 与 差分数组还原出填充的数组
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= m; ++j)
            {
                diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
                if(grid[i - 1][j - 1]) continue;
                if(diff[i][j] == 0)
                    return false;
            }
        }

        return true;
    }
};
```

