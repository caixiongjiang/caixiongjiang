## 编号：两栋颜色不同且距离最远的房子(AC)

街上有 n 栋房子整齐地排成一列，每栋房子都粉刷上了漂亮的颜色。给你一个下标从 0 开始且长度为 n 的整数数组 colors ，其中 colors[i] 表示第  i 栋房子的颜色。

返回 两栋 颜色 不同 房子之间的 最大 距离。

第 i 栋房子和第 j 栋房子之间的距离是 abs(i - j) ，其中 abs(x) 是 x 的绝对值。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/10/31/eg1.png)

```
输入：colors = [1,1,1,6,1,1,1]
输出：3
解释：上图中，颜色 1 标识成蓝色，颜色 6 标识成红色。
两栋颜色不同且距离最远的房子是房子 0 和房子 3 。
房子 0 的颜色是颜色 1 ，房子 3 的颜色是颜色 6 。两栋房子之间的距离是 abs(0 - 3) = 3 。
注意，房子 3 和房子 6 也可以产生最佳答案。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/10/31/eg2.png)

```
输入：colors = [1,8,3,8,3]
输出：4
解释：上图中，颜色 1 标识成蓝色，颜色 8 标识成黄色，颜色 3 标识成绿色。
两栋颜色不同且距离最远的房子是房子 0 和房子 4 。
房子 0 的颜色是颜色 1 ，房子 4 的颜色是颜色 3 。两栋房子之间的距离是 abs(0 - 4) = 4 。
```
示例 3：
```
输入：colors = [0,1]
输出：1
解释：两栋颜色不同且距离最远的房子是房子 0 和房子 1 。
房子 0 的颜色是颜色 0 ，房子 1 的颜色是颜色 1 。两栋房子之间的距离是 abs(0 - 1) = 1 。 
```
提示：

* n == colors.length
* 2 <= n <= 100
* 0 <= colors[i] <= 100
* 生成的测试数据满足 至少 存在 2 栋颜色不同的房子

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-furthest-houses-with-different-colors
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

需要注意排在最后的的房子和前面的房子也可以产生最远的距离。

代码如下：
```c++
class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int n = colors.size();
        int ans = 0;
        int begin = 0, end = n - 1;
        for(int i = 0; i < n; i++){
            if(colors[i] != colors[begin]){
                ans = max(ans, i - begin);
            }
            if(colors[i] != colors[end]){
                ans = max(ans,end - i);
            }
        }
        return ans;
    }
};
```