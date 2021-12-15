## 编号851:喧闹和富有

有一组 n 个人作为实验对象，从 0 到 n - 1 编号，其中每个人都有不同数目的钱，以及不同程度的安静值（quietness）。为了方便起见，我们将编号为 x 的人简称为 "person x "。

给你一个数组 richer ，其中 richer[i] = [ai, bi] 表示 person ai 比 person bi 更有钱。另给你一个整数数组 quiet ，其中 quiet[i] 是 person i 的安静值。richer 中所给出的数据 逻辑自恰（也就是说，在 person x 比 person y 更有钱的同时，不会出现 person y 比 person x 更有钱的情况 ）。

现在，返回一个整数数组 answer 作为答案，其中 answer[x] = y 的前提是，在所有拥有的钱肯定不少于 person x 的人中，person y 是最安静的人（也就是安静值 quiet[y] 最小的人）。

 

示例 1：
```
输入：richer = [[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]], quiet = [3,2,5,4,6,1,7,0]
输出：[5,5,2,5,4,5,6,7]
解释： 
answer[0] = 5，
person 5 比 person 3 有更多的钱，person 3 比 person 1 有更多的钱，person 1 比 person 0 有更多的钱。
唯一较为安静（有较低的安静值 quiet[x]）的人是 person 7，
但是目前还不清楚他是否比 person 0 更有钱。
answer[7] = 7，
在所有拥有的钱肯定不少于 person 7 的人中（这可能包括 person 3，4，5，6 以及 7），
最安静（有较低安静值 quiet[x]）的人是 person 7。
其他的答案也可以用类似的推理来解释。
```
示例 2：
```
输入：richer = [], quiet = [0]
输出：[0] 
```
提示：

* n == quiet.length
* 1 <= n <= 500
* 0 <= quiet[i] < n
* quiet 的所有值 互不相同
* 0 <= richer.length <= n * (n - 1) / 2
* 0 <= ai, bi < n
* ai != bi
* richer 中的所有数对 互不相同
* 对 richer 的观察在逻辑上是一致的

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/loud-and-rich
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 深度优先搜索
我们可以根据 richer 构建一张有向图：把人看成点，如果ai比bi更有钱，那么就从bi向ai连一条有向边。由于题目保证 richer 中所给出的数据逻辑自恰，我们得到的是一张有向无环图。

因此我们从图上任意一点（设为 x）出发，沿着有向边所能访问到的点，都比 x 更有钱。

题目需要计算拥有的钱肯定不少于 x 的人中，最安静的人。我们可以分为拥有的钱肯定与 x 相等，以及拥有的钱肯定比 x 多两种情况。对于前者，根据题目所给信息，我们只知道 x 拥有的钱肯定与自己相等，无法知道是否有其他人拥有的钱肯定与 x 相等；对于后者，我们可以先计算出 x 的邻居的 answer 值，再取这些 answer 值中的最小值为结果，这是因为从 x 的邻居出发所能访问到的点，并上 x 的邻居后所得到的点集，就是从 x 出发所能访问到的点。总的来说，最安静的人要么是 x 自己，要么是 x 的邻居的 answer 中最安静的人。

计算 x 的每个邻居的 answer 值是一个递归的过程，我们可以用深度优先搜索来实现。为避免重复运算，在已经计算出 answer[x] 的情况下可以直接返回。

代码如下：
```c++
class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        vector<vector<int>> edges(n);
        for(auto &r : richer){
            edges[r[1]].emplace_back(r[0]);//贫穷指向富有
        }

        vector<int> ret(n, -1);
        function<void(int)> dfs = [&](int x){
            if(ret[x] != -1) return;
            ret[x] = x;
            for(int y : edges[x]){//y是比x更富有的人
                dfs(y);
                if(quiet[ret[y]] < quiet[ret[x]]){//如果他更安静，则为想要的结果
                    ret[x] = ret[y];
                }
            }
        };
        //对每个人都进行dfs遍历，并更新ret数组
        for(int i = 0; i < n; i++){
            dfs(i);
        }
        return ret;
    }
};
```

### 拓扑排序

如果 ai比bi更有钱，我们从ai向bi连一条有向边。

这同样得到的是一张有向无环图，因此我们从图上任意一点（设为 x）出发，沿着有向边所能访问到的点，拥有的钱都比 x 少。这意味着我们可以在计算出 answer[x] 后，用 answer[x] 去更新 x 所能访问到的点的 answer 值。

要实现这一算法，我们可以将每个 answer[x] 初始化为 x，然后对这张图执行一遍拓扑排序，并按照拓扑序去更新 x 的邻居的 answer 值。通过这一方式我们就能将 answer[x] 的值「传播」到 x 所能访问到的点上。

代码如下：
```c++
class Solution{
public:
    vector<int> loudAndRich(vector<vector<int>> &richer, vector<int> &quiet){
        int n = quiet.size();
        vector<vector<int>> edges(n);
        vector<int> inDeg(n);
        for(auto &r : richer){
            edges[r[0]].emplace_back(r[1]);//富有指向贫穷
            inDeg[r[1]]++;//说明有人比他更富有
        }

        vector<int> ret(n);
        iota(ret.begin(), ret.end(), 0);// fill ret with 0, 1, 2, 3...
        queue<int> que;
        for(int i = 0; i < n; i++){
            if(inDeg[i] == 0){//说明他是最富有的，没有人比他富有
                que.emplace(i);
            }
        }
        while(!que.empty()){
            int x = que.front();
            que.pop();
            for(int y : edges[x]){//y比x更贫穷
                if(quiet[ret[x]] < quiet[ret[y]]){//符合题目的要求：x更加富有也更加安静
                    ret[y] = ret[x];//更新x的邻居的答案
                }
                if(--inDeg[y] == 0){//没有其他人比他富有，比他富有的人已经遍历过
                    que.emplace(y);
                }
            }
        }
        return ret;
    }
};
```