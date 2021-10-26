## 编号841：钥匙和房间

有 N 个房间，开始时你位于 0 号房间。每个房间有不同的号码：0，1，2，...，N-1，并且房间里可能有一些钥匙能使你进入下一个房间。

在形式上，对于每个房间 i 都有一个钥匙列表 rooms[i]，每个钥匙 rooms[i][j] 由 [0,1，...，N-1] 中的一个整数表示，其中 N = rooms.length。 钥匙 rooms[i][j] = v 可以打开编号为 v 的房间。

最初，除 0 号房间外的其余所有房间都被锁住。

你可以自由地在房间之间来回走动。

如果能进入每个房间返回 true，否则返回 false。

示例 1：
```
输入: [[1],[2],[3],[]]
输出: true
解释:  
我们从 0 号房间开始，拿到钥匙 1。
之后我们去 1 号房间，拿到钥匙 2。
然后我们去 2 号房间，拿到钥匙 3。
最后我们去了 3 号房间。
由于我们能够进入每个房间，我们返回 true。
```
示例 2：
```
输入：[[1,3],[3,0,1],[2],[0]]
输出：false
解释：我们不能进入 2 号房间。
```
提示：

* 1 <= rooms.length <= 1000
* 0 <= rooms[i].length <= 1000
* 所有房间中的钥匙数量总计不超过 3000。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/keys-and-rooms
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

其实这道题的本质就是判断各个房间所连成的有向图，说明不用访问所有的房间。

如图所示：

![avater](https://camo.githubusercontent.com/2ce9905a96f2f7215fca1741c9f04e3361a3b07ffae2e542000e3b981d7d4663/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3834312ee992a5e58c99e5928ce688bfe997b42e706e67)

示例1就可以访问所有的房间，因为通过房间里的key将房间连在了一起。

示例2中，就不能访问所有房间，从图中就可以看出，房间2是一个孤岛，我们从0出发，无论怎么遍历，都访问不到房间2。

认清本质问题之后，使用**广度优先搜索(BFS) 还是 深度优先搜索(DFS)都是可以的。**

BFS C++代码代码如下：

```c++
class Solution {
public:
    bool bfs(const vector<vector<int>>& rooms) {
        vector<int> visited(rooms.size(), 0);   //标记房间是否被访问过
        visited[0] = 1;   //0号房间开始
        queue<int> que;
        que.push(0);

        //广度优先搜索的过程
        while(!que.empty()){
            int key = que.front();
            que.pop();
            vector<int> keys = rooms[key];
            for(int key : keys){
                if(!visited[key]){
                    que.push(key);
                    visited[key] = 1;
                }
            }
        }
        //检查房间是否都被遍历过
        for(int i : visited){
            if(i == 0) return false;
        }
        return true;
    }
    bool canVisitAllRooms(vector<vector<int>>& rooms){
        return bfs(rooms);
    }
};
```

DFS C++代码如下：

```c++
class Solution {
private:
    void dfs(int key, const vector<vector<int>>& rooms, vector<int>& visited) {
        if (visited[key]) {
            return;
        }
        visited[key] = 1;
        vector<int> keys = rooms[key];
        for (int key : keys) {
            // 深度优先搜索遍历
            dfs(key, rooms, visited);
        }
    }
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        vector<int> visited(rooms.size(), 0);
        dfs(0, rooms, visited);
        //检查是否都访问到了
        for (int i : visited) {
            if (i == 0) return false;
        }
        return true;
    }
};
```