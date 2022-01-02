## 编号：参加会议的最多员工数（×）

一个公司准备组织一场会议，邀请名单上有n位员工。公司准备了一张 圆形的桌子，可以坐下 任意数目的员工。

员工编号为 0到 n - 1。每位员工都有一位 喜欢的员工，每位员工当且仅当他被安排在喜欢员工的旁边，他才会参加会议。每位员工喜欢的员工 不会是他自己。

给你一个下标从 0开始的整数数组favorite，其中favorite[i]表示第i位员工喜欢的员工。请你返回参加会议的最多员工数目。


示例 1：

![avater](https://assets.leetcode.com/uploads/2021/12/14/ex1.png)

```
输入：favorite = [2,2,1,2]
输出：3
解释：
上图展示了公司邀请员工 0，1 和 2 参加会议以及他们在圆桌上的座位。
没办法邀请所有员工参与会议，因为员工 2 没办法同时坐在 0，1 和 3 员工的旁边。
注意，公司也可以邀请员工 1，2 和 3 参加会议。
所以最多参加会议的员工数目为 3 。
```
示例 2：
```
输入：favorite = [1,2,0]
输出：3
解释：
每个员工都至少是另一个员工喜欢的员工。所以公司邀请他们所有人参加会议的前提是所有人都参加了会议。
座位安排同图 1 所示：
- 员工 0 坐在员工 2 和 1 之间。
- 员工 1 坐在员工 0 和 2 之间。
- 员工 2 坐在员工 1 和 0 之间。
参与会议的最多员工数目为 3 。
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2021/12/14/ex2.png)

```
输入：favorite = [3,0,1,4,1]
输出：4
解释：
上图展示了公司可以邀请员工 0，1，3 和 4 参加会议以及他们在圆桌上的座位。
员工 2 无法参加，因为他喜欢的员工 0 旁边的座位已经被占领了。
所以公司只能不邀请员工 2 。
参加会议的最多员工数目为 4 。
```
提示：

* n == favorite.length
* 2 <= n <= 10^5
* 0 <= favorite[i] <= n - 1
* favorite[i] != i

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-employees-to-be-invited-to-a-meeting
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

照例，复刻大佬的代码。

```c++
class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        int n = favorite.size();
        vector<vector<int>> edges(n), redges(n);//图和反向图
        vector<int> degree(n);//每个节点的入度
        for(int i = 0; i < n; i++){
            int temp = favorite[i];
            edges[i].push_back(temp);
            redges[temp].push_back(i);
            degree[temp]++;
        }

        //拓扑排序模板
        queue<int> que;
        for(int i = 0; i < n; i++){
            //入度为0则加入队列
            if(degree[i] == 0){
                que.push(i);
            }
        }
        //从入度为0的点开始寻找
        while(!que.empty()){
            int x = que.front();
            que.pop();
            for(int w : edges[x]){
                //如果入度为1，则说明找到了按照拓扑的节点
                if(--degree[w] == 0) que.push(w);
            }
        }

        //寻找图edges上的环基
        vector<int> ring;
        vector<int> vis(n);
        function<void(int)> dfs = [&](int v){
            vis[v] = true;
            ring.push_back(v);
            for(int w : edges[v]){
                if(!vis[w]) dfs(w);
            }
        };

        //通过反图redges寻找树枝上最深的链
        int max_depth = 0;
        function<void(int, int, int)> rdfs = [&](int v, int fa, int depth){
            max_depth = max(max_depth, depth);
            for(int w : redges[v]){
                if(w != fa) rdfs(w, v, depth + 1);
            }
        };

        int max_ring_size = 0, sum_chain_size = 0;//环节点数和树枝节点数
        for(int i = 0; i < n; i++){
            if(!vis[i] && degree[i]){//遍历环基上的点（寻找拓扑排序后入度不为0）
                ring.resize(0);
                dfs(i);
                int sz = ring.size();
                if(sz == 2){//环基大小为2
                    int v = ring[0], w = ring[1];
                    max_depth = 0;
                    rdfs(v, w, 1);
                    sum_chain_size += max_depth;
                    max_depth = 0;
                    rdfs(w, v, 1);
                    sum_chain_size += max_depth;
                }else{
                    max_ring_size = max(max_ring_size, sz);//取所有环基的最大值
                }
            }
        }
        return max(max_ring_size, sum_chain_size);
    }
};
```

将两元环分开计数的情况。

代码如下：
```c++
const int N = 1e5 + 7;
bool vi[N];// 访问数组
bool isring[N];// 每一个点是否在环上
int dep[N];// 每一个点往后的最长链 不是环的情况
int ex[N];// 每一个节点的出度
int n,m,a,b;
class Solution {
public:
    vector<vector<int>> g;
    int be;
    int dfs(int p) {
        int res = 1;
        for(auto& next : g[p]) {
            if(!vi[next] && isring[next]) {
                vi[next] = true;
                res += dfs(next);
            }
        }
        return res;
    }
    int maximumInvitations(vector<int>& s) {
        n = s.size();
        g.resize(n);
        int res = 0;
        memset(dep,0,4 * n);// 最长链
        memset(vi,false,n);
        memset(isring,true,n);// 初始假设每一个都在环上
        memset(ex,0,4 * n);
        for(int i = 0;i < n;i ++) {
            g[s[i]].push_back(i);
            ex[s[i]] ++;
        }
        // 拓扑排序 求最长链
        queue<int> q;
        for(int i = 0;i < n;i ++) {
            if(!ex[i]) {
                q.push(i);
                dep[i] = 1;
                isring[i] = false;
            }
        }
        while(!q.empty()) {
            int t = q.front(); q.pop();
            ex[s[t]] --;
            if(!ex[s[t]]) dep[s[t]] = dep[t] + 1 , q.push(s[t]) , isring[s[t]] = false;
            else dep[s[t]] = dep[t];
        }
        // 深搜 求每一个环的大小
        for(int i = 0;i < n;i ++) {
            if(!vi[i] && isring[i]) {
                vi[i] = true;
                res = max(res,dfs(i));
            }
        }
        // 剩下的就是二元环的情况了
        int o = 0;
        for(int i = 0;i < n;i ++) {
            if(s[s[i]] == i) {
                // 两元环
                o += dep[i] + dep[s[i]] + 2;
            }
        }
        res = max(res,o / 2);// 每一个二元环的贡献计算了两次
        return res;
    }
};
```
