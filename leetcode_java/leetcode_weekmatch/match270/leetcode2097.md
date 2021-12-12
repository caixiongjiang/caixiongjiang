## 编号2097：合法重新排列数对(×)

给你一个下标从 0 开始的二维整数数组 pairs ，其中 pairs[i] = [starti, endi] 。如果 pairs 的一个重新排列，满足对每一个下标 i （ 1 <= i < pairs.length ）都有 endi-1 == starti ，那么我们就认为这个重新排列是 pairs 的一个 合法重新排列 。

请你返回 任意一个 pairs 的合法重新排列。

注意：数据保证至少存在一个 pairs 的合法重新排列。

 

示例 1：
```
输入：pairs = [[5,1],[4,5],[11,9],[9,4]]
输出：[[11,9],[9,4],[4,5],[5,1]]
解释：
输出的是一个合法重新排列，因为每一个 endi-1 都等于 starti 。
end0 = 9 == 9 = start1 
end1 = 4 == 4 = start2
end2 = 5 == 5 = start3
```
示例 2：
```
输入：pairs = [[1,3],[3,2],[2,1]]
输出：[[1,3],[3,2],[2,1]]
解释：
输出的是一个合法重新排列，因为每一个 endi-1 都等于 starti 。
end0 = 3 == 3 = start1
end1 = 2 == 2 = start2
重新排列后的数组 [[2,1],[1,3],[3,2]] 和 [[3,2],[2,1],[1,3]] 都是合法的。
```
示例 3：
```
输入：pairs = [[1,2],[1,3],[2,1]]
输出：[[1,2],[2,1],[1,3]]
解释：
输出的是一个合法重新排列，因为每一个 endi-1 都等于 starti 。
end0 = 2 == 2 = start1
end1 = 1 == 1 = start2
``` 

提示：

* 1 <= pairs.length <= 105
* pairs[i].length == 2
* 0 <= starti, endi <= 109
* starti != endi
* pairs 中不存在一模一样的数对。
* 至少 存在 一个合法的 pairs 重新排列。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-arrangement-of-pairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路


### 欧拉路径

代码如下：
```c++
class Solution {
public:
    unordered_map<int,int> Degree;
    unordered_map<int,vector<int>> edges;//建图
    vector<int> res;
    void dfs(int start){
        //既然不知道谁是死胡同，那么我就遍历，直到遍历到死胡同的时候，我先把死胡同加进去，然后再把死胡同上一个节点加入，也就是逆序保存路径
        while(!edges[start].empty()){
            int next = edges[start].back();
            edges[start].pop_back();
            dfs(next);
        }
        res.push_back({start});
    }
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        for(auto &item : pairs){
            int v1 = item[0],v2 = item[1];
            //入度是加，出度是减
            --Degree[v1];++Degree[v2];
            edges[v1].push_back(v2);
        }
        //开始找点，起点的入度是0，出度是1
        for(auto &[point,value] : Degree){
            if(value == -1){//入度为0，所以是起点
                dfs(point);
            }
        }
        if(res.empty()){//如果说，没有找到起点，那么肯定就随便一个都可以作为起点了
            dfs(Degree.begin()->first);
        }
        //逆序合并
        reverse(res.begin(),res.end());
        int n = res.size();
        vector<vector<int>> ans;
        for(int i = 0; i < n-1;++i){
            ans.push_back({res[i],res[i+1]});
        }
        return ans;
    }
};
```