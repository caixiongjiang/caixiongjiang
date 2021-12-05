## 编号2092：找出知晓秘密的所有专家(×)

给你一个整数 n ，表示有 n 个专家从 0 到 n - 1 编号。另外给你一个下标从 0 开始的二维整数数组 meetings ，其中 meetings[i] = [xi, yi, timei] 表示专家 xi 和专家 yi 在时间 timei 要开一场会。一个专家可以同时参加 多场会议 。最后，给你一个整数 firstPerson 。

专家 0 有一个 秘密 ，最初，他在时间 0 将这个秘密分享给了专家 firstPerson 。接着，这个秘密会在每次有知晓这个秘密的专家参加会议时进行传播。更正式的表达是，每次会议，如果专家 xi 在时间 timei 时知晓这个秘密，那么他将会与专家 yi 分享这个秘密，反之亦然。

秘密共享是 瞬时发生 的。也就是说，在同一时间，一个专家不光可以接收到秘密，还能在其他会议上与其他专家分享。

在所有会议都结束之后，返回所有知晓这个秘密的专家列表。你可以按 任何顺序 返回答案。

 

示例 1：
```
输入：n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
输出：[0,1,2,3,5]
解释：
时间 0 ，专家 0 将秘密与专家 1 共享。
时间 5 ，专家 1 将秘密与专家 2 共享。
时间 8 ，专家 2 将秘密与专家 3 共享。
时间 10 ，专家 1 将秘密与专家 5 共享。
因此，在所有会议结束后，专家 0、1、2、3 和 5 都将知晓这个秘密。
```
示例 2：
```
输入：n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
输出：[0,1,3]
解释：
时间 0 ，专家 0 将秘密与专家 3 共享。
时间 2 ，专家 1 与专家 2 都不知晓这个秘密。
时间 3 ，专家 3 将秘密与专家 0 和专家 1 共享。
因此，在所有会议结束后，专家 0、1 和 3 都将知晓这个秘密。
```
示例 3：
```
输入：n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
输出：[0,1,2,3,4]
解释：
时间 0 ，专家 0 将秘密与专家 1 共享。
时间 1 ，专家 1 将秘密与专家 2 共享，专家 2 将秘密与专家 3 共享。
注意，专家 2 可以在收到秘密的同一时间分享此秘密。
时间 2 ，专家 3 将秘密与专家 4 共享。
因此，在所有会议结束后，专家 0、1、2、3 和 4 都将知晓这个秘密。
```
示例 4：
```
输入：n = 6, meetings = [[0,2,1],[1,3,1],[4,5,1]], firstPerson = 1
输出：[0,1,2,3]
解释：
时间 0 ，专家 0 将秘密与专家 1 共享。
时间 1 ，专家 0 将秘密与专家 2 共享，专家 1 将秘密与专家 3 共享。
因此，在所有会议结束后，专家 0、1、2 和 3 都将知晓这个秘密。 
```
提示：

* 2 <= n <= 105
* 1 <= meetings.length <= 105
* meetings[i].length == 3
* 0 <= xi, yi <= n - 1
* xi != yi
* 1 <= timei <= 105
* 1 <= firstPerson <= n - 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-all-people-with-secret
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

我们用布尔数组 secret[i] 表示第 i 个人是否知道秘密。初始时，secret[0] 和 secret[firstPerson] 均为 True，其余的元素为 False。

我们将数组meetings 中的所有会议按照时间升序排序，这样在我们对meetings 进行遍历的过程中，就可以保证按照顺序地处理所有会议。根据题目要求，由于秘密共享是「瞬时发生」的，所以我们还需要将时间相同的一批会议进行「统一」处理。

我们可以把每一个时间发生的一批会议抽象成如下的一个图论模型：

* 我们将每一个专家看成图中的一个节点；

* 如果两个专家之间进行了一场会议，那么这两个专家在图中对应的节点之间存在一条无向边。

而我们需要解决的问题转变为：

* 对于任意一个专家，如果存在另一个已经知道秘密的专家，它们在图中对应的节点之间是连通的，那么这个专家就会知道秘密。

因此，我们可以使用广度优先搜索的方法解决该问题。我们将所有已经知道秘密的专家对应的节点（如果存在）放入队列，在广度优先搜索的每一步中，我们取出队首的节点 u，并枚举与 u 相邻的节点 v，如果 v 对应的专家还不知道秘密，就将 v 放入队列中以待后续的搜索。当广度优先搜索完成后，我们就将所有在当前时间知道了秘密的专家进行了更新。

最后我们只需要遍历数组 secret，将元素值为 True 的下标加入答案即可。

代码如下：
```c++
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        int m = meetings.size();
        sort(meetings.begin(), meetings.end(), [&](const auto& x, const auto& y) {
            return x[2] < y[2];
        });

        vector<int> secret(n);
        secret[0] = secret[firstPerson] = true;

        unordered_set<int> vertices;
        unordered_map<int, vector<int>> edges;

        for (int i = 0; i < m;) {
            // meetings[i .. j] 为同一时间
            int j = i;
            while (j + 1 < m && meetings[j + 1][2] == meetings[i][2]) {
                ++j;
            }

            vertices.clear();
            edges.clear();
            for (int k = i; k <= j; ++k) {
                int x = meetings[k][0], y = meetings[k][1];
                vertices.insert(x);
                vertices.insert(y);
                edges[x].push_back(y);
                edges[y].push_back(x);
            }
            
            queue<int> q;
            for (int u: vertices) {
                if (secret[u]) {
                    q.push(u);
                }
            }
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v: edges[u]) {
                    if (!secret[v]) {
                        secret[v] = true;
                        q.push(v);
                    }
                }
            }

            i = j + 1;
        }
        
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (secret[i]) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
```

找到一个更精简的版本：
```c++
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        vector<int> d(n, INT_MAX), done(n);
        vector<vector<pair<int, int>>> G(n);
        for (auto& v: meetings) {
            G[v[0]].emplace_back(v[1], v[2]);
            G[v[1]].emplace_back(v[0], v[2]);
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(d[0] = 0, 0);
        pq.emplace(d[firstPerson] = 0, firstPerson);
        vector<int> res;
        while (not pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if (done[u]) continue;
            done[u] = 1;
            res.push_back(u);
            for (auto [v, t] : G[u]) {
                if (t >= d[u] and d[v] > t) {
                    pq.emplace(d[v] = t, v);
                }
            }
        }
        return res;
    }
};
```

