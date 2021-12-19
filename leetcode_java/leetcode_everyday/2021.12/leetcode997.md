## 编号997:找到小镇的法官

在一个小镇里，按从 1 到 n 为 n 个人进行编号。传言称，这些人中有一个是小镇上的秘密法官。

如果小镇的法官真的存在，那么：

* 小镇的法官不相信任何人。
* 每个人（除了小镇法官外）都信任小镇的法官。
* 只有一个人同时满足条件 1 和条件 2 。
* 给定数组 trust，该数组由信任对 trust[i] = [a, b] 组成，表示编号为 a 的人信任编号为 b 的人。

如果小镇存在秘密法官并且可以确定他的身份，请返回该法官的编号。否则，返回 -1。

 

示例 1：
```
输入：n = 2, trust = [[1,2]]
输出：2
```
示例 2：
```
输入：n = 3, trust = [[1,3],[2,3]]
输出：3
```
示例 3：
```
输入：n = 3, trust = [[1,3],[2,3],[3,1]]
输出：-1
```
示例 4：
```
输入：n = 3, trust = [[1,2],[2,3]]
输出：-1
```
示例 5：
```
输入：n = 4, trust = [[1,3],[1,4],[2,3],[2,4],[4,3]]
输出：3 
```
提示：

1 <= n <= 1000
0 <= trust.length <= 104
trust[i].length == 2
trust[i] 互不相同
trust[i][0] != trust[i][1]
1 <= trust[i][0], trust[i][1] <= n

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-the-town-judge
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 使用辅助数组进行标记
我的思路：

1.通过一个标记数组，先通过条件1（法官不相信任何人）将不是法官的人标记，将剩下的人作为疑似法官的人

2.遍历trust数组对相信疑似法官的人数进行统计，如果等于n-1（其他所有人都相信法官），就为真正的法官！

代码如下：
```c++
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        int m = trust.size();
        int ans = 0;
        vector<int> vec(n);
        for(int i = 0; i < m; i++){
            vec[trust[i][0] - 1] = 1;
        }
        for(int i = 0; i < n; i++){
            if(vec[i] == 0) ans = i + 1;
        }
        int num = 0;//相信疑似为法官的人数
        for(int i = 0; i < m; i++){
            if(trust[i][1] == ans) num++;
        }
        if(num != n - 1) ans = -1; 
        return ans;
    }
};
```

### 计算各节点的入度和出度

干描述了一个有向图。每个人是图的节点，trust 的元素 trust[i] 是图的有向边，从 trust[i][0] 指向 trust[i][1]。我们可以遍历 trust，统计每个节点的入度和出度，存储在 inDegrees 和 outDegrees 中。

根据题意，在法官存在的情况下，法官不相信任何人，每个人（除了法官外）都信任法官，且只有一名法官。因此法官这个节点的入度是 n−1, 出度是 0。

我们可以遍历每个节点的入度和出度，如果找到一个符合条件的节点，由于题目保证只有一个法官，我们可以直接返回结果；如果不存在符合条件的点，则返回 −1。

代码如下：
```c++
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> in(n);//入度数组
        vector<int> out(n);//出度数组
        for(auto & t : trust){
            int x = t[0];
            int y = t[1];
            out[x - 1]++;
            in[y - 1]++;    
        }
        for(int i = 0; i < n; i++){
            if(out[i] == 0 && in[i] == n - 1) return i + 1;
        }
        return -1;
    }
};
```

