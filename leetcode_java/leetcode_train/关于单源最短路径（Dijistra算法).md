## 关于单源最短路径（Dijistra算法)

最短路径（DP的应用）
单源最短路径，不允许出现负环
核心思想：更新估算距离，松弛
δ ( u , v ) ≤ δ ( u , x ) + δ ( x , v ) \delta(u, v) \leq \delta(u, x) + \delta(x, v)
δ(u,v)≤δ(u,x)+δ(x,v)

时间复杂度与采用的数据结构有关，标准的dijkstra应该是用堆实现的。
Array O(v 2 v^2v 
2
 )
Binary heap O(( V + E ) l g V (V+E)lgV(V+E)lgV)
Fibonacci heap O(E + V l g V E+VlgVE+VlgV)

如果对于所有的边权值均为1，那么Dijkstra算法可以用BFS实现
使用FIFO队列代替Priority队列，其时间复杂度为O(V + E V+EV+E)

**数组实现：**
```c++
#include <iostream>
using namespace std;
void dijkstra();
int e[10][10];
int vis[10];
int dis[10];
int n, m;
int min1 = 99999999;
int u = 0;
int main()
{
    cin >> n >> m;
    // 初始化邻接表
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
            {
                e[i][j] = 0;
            }
            else
            {
                e[i][j] = 99999999;
            }
        }
    }
    // 填充数据
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        e[a][b] = c;
    }
    for (int i = 1; i <= n; i++)
    {
        dis[i] = e[1][i];
    }
    vis[1] = 1;

    dijkstra();

    for (int i = 1; i <= n; i++)
    {
        cout << dis[i];
    }

    system("pause");
    return 0;
}
void dijkstra()
{
    for (int i = 1; i <= n - 1; i++)
    {
        min1 = 99999999;
        // 寻找权值最小的点u
        for (int j = 1; j <= n; j++)
        {
            if (vis[j] == 0 && dis[j] < min1)
            {
                min1 = dis[j];
                u = j;
            }
        }

        vis[u] = 1;

        for (int v = 1; v <= n; v++)
        {
            // 对于每个u可达的v来说
            if (e[u][v] < 99999999)
            {
                // 如果当前的dis[v]不满足三角形不等式，那么进行松弛操作
                if (dis[v] > dis[u] + e[u][v])
                {
                    dis[v] = dis[u] + e[u][v];
                }
            }
        }
    }
}
```

**堆实现:**

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int Ni = 10000;
const int INF = 1 << 27;
struct node
{
    int point, value;
    // 构造
    node(int a, int b)
    {
        point = a;
        value = b;
    }
    // 重载<操作符
    bool operator<(const node &a) const
    {
        // 对小于运算符进行重载，如果两个值相等，那么继续判断point，如果不等，则返回false
        if (value == a.value)
        {
            return point < a.point;
        }
        else
        {
            return value > a.value;
        }
    }
};
vector<node> e[Ni];
int dis[Ni], n;
priority_queue<node> q;
void dijkstra();
int main()
{
    int a, b, c, m;
    scanf("%d%d", &n, &m);
    while (m--)
    {
        scanf("%d%d%d", &a, &b, &c);
        e[a].push_back(node(b, c));
        e[b].push_back(node(a, c));
    }
    
    // for (int i = 0; i <= n; i++)
    // {
    //     dis[i] = INF;
    // }
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    // 优先队列，队头元素最大，但是如果类型为struct需要重载<运算符
    q.push(node(1, dis[1]));

    dijkstra();

    for (int i = 1; i <= n; i++)
    {
        printf("%d ", dis[i]);
    }
    system("pause");
    return 0;
}
void dijkstra()
{
    while (!q.empty())
    {
        node x = q.top();
        q.pop();
        for (int i = 0; i < e[x.point].size(); i++)
        {
            node y = e[x.point][i];
            if (dis[y.point] > dis[x.point] + y.value)
            {
                dis[y.point] = dis[x.point] + y.value;
                q.push(node(y.point, dis[y.point]));
            }
        }
    }
}
```