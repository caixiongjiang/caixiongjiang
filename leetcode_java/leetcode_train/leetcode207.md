## 编号207：课程表

你这个学期必须选修 numCourses 门课程，记为0到numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组prerequisites 给出，其中prerequisites[i] = [ai, bi] ，表示如果要学习课程ai 则 必须 先学习课程 bi 。

例如，先修课程对[0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。


示例 1：
```
输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
```
示例 2：
```
输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。
```
提示：

* 1 <= numCourses <= 105
* 0 <= prerequisites.length <= 5000
* prerequisites[i].length == 2
* 0 <= ai, bi < numCourses
* prerequisites[i] 中的所有课程对 互不相同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/course-schedule
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

拓扑排序模板题！

步骤：

1.遍历信息建图，更新入度表

2.通过入度表为0的节点开始遍历，进行拓扑排序

3.统计没有遍历的节点，如果有就返回false



代码如下：
```c++
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> edges(numCourses);//图的邻接矩阵
        vector<int> indegree(numCourses);//入度
        
        /*建图过程*/
        for(int i = 0; i < prerequisites.size(); i++){
            //l->r （依赖关系）
            int r = prerequisites[i][0];
            int l = prerequisites[i][1];
            edges[l].push_back(r);
            indegree[r]++;
        }
        
        /*拓扑排序开始*/
        queue<int> que;
        for(int i = 0; i < numCourses; i++){
            if(indegree[i] == 0) que.push(i);
        }
        //从入度为0的节点开始遍历
        while(!que.empty()){
            int x = que.front();
            que.pop();
            //每遍历一个节点就更新入度值，入度为0则入队作为起点
            for(int w : edges[x]){
                if(--indegree[w] == 0) que.push(w);
            }
        }

        //统计是否有节点剩余没有遍历
        for(int i = 0; i < numCourses; i++){
            if(indegree[i] != 0) return false;
        }
        return true;
    }
};
```