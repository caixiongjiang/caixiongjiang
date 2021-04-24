## 编号59：螺旋矩阵Ⅱ

给你一个正整数 n ，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。

示例 1：

![avater](https://assets.leetcode.com/uploads/2020/11/13/spiraln.jpg)

```markdown
输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]
```
示例 2：
```markdown
输入：n = 1
输出：[[1]]
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/spiral-matrix-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
这道题目可以说在面试中出现频率较高的题目，「本题并不涉及到什么算法，就是模拟过程，但却十分考察对代码的掌控能力。」

要如何画出这个螺旋排列的正方形矩阵呢？
</br>注意<span style="color:red">「循环不变量原则」</span>:
可以发现这里的边界条件非常多，在一个循环中，如此多的边界条件，如果不按照固定规则来遍历，那就是「一进循环深似海，从此offer是路人」。
</br></br>这里一圈下来，我们要画每四条边，这四条边怎么画，每画一条边都要坚持一致的左闭右开，或者左开又闭的原则，这样这一圈才能按照统一的规则画下来。

那么我按照左闭右开的原则，来画一圈，大家看一下：
![avater](https://mmbiz.qpic.cn/mmbiz_png/ciaqDnJprwv75lvFebqBLu3d5uGMdAw1edpy4wAhTOucI7Bl63R2IQZwbpHlNzjXLhq4uVqA0jCzD8esO1KBOEA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

---
代码如下，已经详细注释了每一步的目的，可以看出while循环里判断的情况是很多的，代码里处理的原则也是统一的***左闭右开***。
```java
class Solution {
    public int[][] generateMatrix(int n) {
        int[][] res=new int[n][n];  // 定义一个二维数组
        int startx = 0, starty = 0; // 定义每循环一个圈的起始位置
        int loop = n / 2; // 每个圈循环几次，例如n为奇数3，那么loop = 1 只是循环一圈，矩阵中间的值需要单独处理
        int mid = n / 2; // 矩阵中间的位置，例如：n为3， 中间的位置就是(1，1)，n为5，中间位置为(2, 2)
        int count = 1; // 用来给矩阵中每一个空格赋值
        int offset = 1; // 每一圈循环，需要控制每一条边遍历的长度
        int i,j;
        while (loop -->0) {
            i = startx;
            j = starty;

            // 下面开始的四个for就是模拟转了一圈
            // 模拟填充上行从左到右(左闭右开)
            for (j = starty; j < starty + n - offset; j++) {
                res[startx][j] = count++;
            }
            // 模拟填充右列从上到下(左闭右开)
            for (i = startx; i < startx + n - offset; i++) {
                res[i][j] = count++;
            }
            // 模拟填充下行从右到左(左闭右开)
            for (; j > starty; j--) {
                res[i][j] = count++;
            }
            // 模拟填充左列从下到上(左闭右开)
            for (; i > startx; i--) {
                res[i][j] = count++;
            }

            // 第二圈开始的时候，起始位置要各自加1， 例如：第一圈起始位置是(0, 0)，第二圈起始位置是(1, 1)
            startx++;
            starty++;

            // offset 控制每一圈里每一条边遍历的长度
            offset += 2;
        }

        // 如果n为奇数的话，需要单独给矩阵最中间的位置赋值
        if (n % 2==1) {
            res[mid][mid] = count;
        }
        return res;
    }
}
```