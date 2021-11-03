## 编号684：冗余连接

树可以看成是一个连通且 无环 的 无向 图。

给定往一棵 n 个节点 (节点值 1～n) 的树中添加一条边后的图。添加的边的两个顶点包含在 1 到 n 中间，且这条附加的边不属于树中已存在的边。图的信息记录于长度为 n 的二维数组 edges ，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。

请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。如果有多个答案，则返回数组 edges 中最后出现的边。

 

示例 1：

![avater](https://pic.leetcode-cn.com/1626676174-hOEVUL-image.png)

```
输入: edges = [[1,2], [1,3], [2,3]]
输出: [2,3]
```
示例 2：

![avater](https://pic.leetcode-cn.com/1626676179-kGxcmu-image.png)

```
输入: edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
输出: [1,4] 
```
提示:

* n == edges.length
* 3 <= n <= 1000
* edges[i].length == 2
* 1 <= ai < bi <= edges.length
* ai != bi
* edges 中无重复元素
* 给定的图是连通的 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/redundant-connection
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

首先要知道并查集可以解决什么问题呢？

主要就是集合问题，两个节点在不在一个集合，也可以将两个节点添加到一个集合中。

这里整理出我的并查集模板如下：
```c++
int n = 1005; // 节点数量3 到 1000
int father[1005];

// 并查集初始化
void init() {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
    }
}
// 并查集里寻根的过程
int find(int u) {
    return u == father[u] ? u : father[u] = find(father[u]);
}
// 将v->u 这条边加入并查集
void join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return ;
    father[v] = u;
}
// 判断 u 和 v是否找到同一个根
bool same(int u, int v) {
    u = find(u);
    v = find(v);
    return u == v;
}
```

以上模板汇总，只要修改 n 和father数组的大小就可以了。

并查集主要有三个功能。

* 1.寻找根节点，函数：find(int u)，也就是判断这个节点的祖先节点是哪个
* 2.将两个节点接入到同一个集合，函数：join(int u, int v)，将两个节点连在同一个根节点上
* 3.判断两个节点是否在同一个集合，函数：same(int u, int v)，就是判断两个节点是不是同一个根节点

简单介绍并查集之后，我们再来看一下这道题目。

题目说是无向图，返回一条可以删去的边，使得结果图是一个有着N个节点的树。

如果有多个答案，则返回二维数组中最后出现的边。

那么我们就可以从前向后遍历每一条边，边的两个节点如果不在同一个集合，就加入集合（即：同一个根节点）。

如果边的两个节点已经出现在同一个集合里，说明着边的两个节点已经连在一起了，如果再加入这条边一定就出现环了。

这个思路清晰之后，代码就很好写了。

并查集C++代码如下：
```c++
class Solution {
private:
    int n = 1005; // 节点数量3 到 1000
    int father[1005];

    // 并查集初始化
    void init() {
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
    }
    // 并查集里寻根的过程
    int find(int u) {
        return u == father[u] ? u : father[u] = find(father[u]);
    }
    // 将v->u 这条边加入并查集
    void join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return ;
        father[v] = u;
    }
    // 判断 u 和 v是否找到同一个根，本题用不上
    bool same(int u, int v) {
        u = find(u);
        v = find(v);
        return u == v;
    }
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        init();
        for (int i = 0; i < edges.size(); i++) {
            if (same(edges[i][0], edges[i][1])) return edges[i];
            else join(edges[i][0], edges[i][1]);
        }
        return {};
    }
};
```
可以看出，主函数的代码很少，就判断一下边的两个节点在不在同一个集合就可以了。