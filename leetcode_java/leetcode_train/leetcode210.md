## 编号210：课程表Ⅱ

现在你总共有 numCourses 门课需要选，记为0到numCourses - 1。给你一个数组prerequisites ，其中 prerequisites[i] = [ai, bi] ，表示在选修课程 ai 前 必须 先选修bi 。

例如，想要学习课程 0 ，你需要先完成课程1 ，我们用一个匹配来表示：[0,1] 。
返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组 。



示例 1：
```
输入：numCourses = 2, prerequisites = [[1,0]]
输出：[0,1]
解释：总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。
```
示例 2：
```
输入：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
输出：[0,2,1,3]
解释：总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。
```
示例 3：
```
输入：numCourses = 1, prerequisites = []
输出：[0]
```
提示：
* 1 <= numCourses <= 2000
* 0 <= prerequisites.length <= numCourses * (numCourses - 1)
* prerequisites[i].length == 2
* 0 <= ai, bi < numCourses
* ai != bi
* 所有[ai, bi] 互不相同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/course-schedule-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

拓扑排序模板题！

步骤：

1.遍历信息建图，更新入度表

2.通过入度表为0的节点开始遍历，进行拓扑排序

3.统计没有遍历的节点，每遍历一个就将它加入结果数组

4.如果res的长度与节点数相等则输出，否则输出空数组。

代码如下：
```c++
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = prerequisites.size();
        vector<int> res;
        vector<vector<int>> edges(numCourses);
        vector<int> indegree(numCourses);
        for(int i = 0; i < prerequisites.size(); i++){
            int l = prerequisites[i][1];
            int r = prerequisites[i][0];
            edges[l].push_back(r);
            indegree[r]++;
        }
        queue<int> que;
        for(int i = 0; i < numCourses; i++){
            if(indegree[i] == 0) que.push(i);
        }
        while(!que.empty()){
            int x = que.front();
            res.push_back(x);
            que.pop();
            for(int w : edges[x]){
                if(--indegree[w] == 0) que.push(w);
            }
        }
        if(res.size() == numCourses) return res;
        return {};
    }
};
```