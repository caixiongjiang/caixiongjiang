## 编号2049：统计最高分的节点数目(×)

给你一棵根节点为 0 的 二叉树 ，它总共有 n 个节点，节点编号为 0 到 n - 1 。同时给你一个下标从 0 开始的整数数组 parents 表示这棵树，其中 parents[i] 是节点 i 的父节点。由于节点 0 是根，所以 parents[0] == -1 。

一个子树的 大小 为这个子树内节点的数目。每个节点都有一个与之关联的 分数 。求出某个节点分数的方法是，将这个节点和与它相连的边全部 删除 ，剩余部分是若干个 非空 子树，这个节点的 分数 为所有这些子树 大小的乘积 。

请你返回有 最高得分 节点的 数目 。

 

示例 1:

![avater](https://assets.leetcode.com/uploads/2021/10/03/example-1.png)

```
输入：parents = [-1,2,0,2,0]
输出：3
解释：
- 节点 0 的分数为：3 * 1 = 3
- 节点 1 的分数为：4 = 4
- 节点 2 的分数为：1 * 1 * 2 = 2
- 节点 3 的分数为：4 = 4
- 节点 4 的分数为：4 = 4
最高得分为 4 ，有三个节点得分为 4 （分别是节点 1，3 和 4 ）。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/10/03/example-2.png)

```
输入：parents = [-1,2,0]
输出：2
解释：
- 节点 0 的分数为：2 = 2
- 节点 1 的分数为：2 = 2
- 节点 2 的分数为：1 * 1 = 1
最高分数为 2 ，有两个节点分数为 2 （分别为节点 0 和 1 ）。 
```
提示：

* n == parents.length
* 2 <= n <= 105
* parents[0] == -1
* 对于 i != 0 ，有 0 <= parents[i] <= n - 1
* parents 表示一棵二叉树。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-nodes-with-the-highest-score
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

在这里我们可以把这棵二叉树树看成一个无向图，在这个图中，我们删除一个节点，最多形成3个连通分量， 即

* 左子树（如果存在）
* 右子树（如果存在）
* 除了 自身和两棵子树的其他部分（如果存在）

因此，本题的解题思路就出来了：

1.先使用dfs初始化出**以各个节点为根节点的子树**所包含的节点总数。

2.接着我们开始遍历每一个删除的节点， 求出他们剩余三部分的节点数量， 对其乘积结果就是这个节点的分数。

**Tips： 在求解分数的过程中，可能会超出32位，所以我们应该开long long;**

整体代码如下：
```c++
class Solution {
public:
    vector<vector<int>> child;
    vector<int> childTreeNums;
    long long ans = INT_MIN;
    int len, sum, ret = 0;     
    int countHighestScoreNodes(vector<int>& parents) {
        len = parents.size();
        child = vector<vector<int>>(len);
        childTreeNums = vector<int>(len, 0);
        //保存孩子节点
        for(int i = 0; i < len; i++){
            if(parents[i] != -1){
                child[parents[i]].push_back(i); 
            }
        }
        dfs(0);
        //节点总数
        sum = childTreeNums[0];
        //获得等于最大值的最大数目
        for(int i = 0; i < len; i++){
            long long temp = getScore(i);
            if(temp > ans){
                ret = 1;
                ans = temp;
            }else if(temp == ans){
                ret++;
            }
        }
        return ret;
    }

    //获取所有子树的值
    int dfs(int root){
        if(not child[root].size()) return (childTreeNums[root] = 1);
        for(int i = 0; i < child[root].size(); i++){
            childTreeNums[root] += dfs(child[root][i]);
        }
        return ++childTreeNums[root];
    }

    //得出山区item节点的分数，注意要开long long
    long long getScore(int item){
        long long score = 1;
        score = childTreeNums[0] - childTreeNums[item] == 0 ? 1 : childTreeNums[0] - childTreeNums[item];
        for(int i = 0; i < child[item].size(); i++){
            score *= childTreeNums[child[item][i]];
        } 
        return score;
    }    
};
```