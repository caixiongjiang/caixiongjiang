## 编号5887：两个有序数组的第 K 小乘积

给你两个 从小到大排好序 且下标从 0 开始的整数数组 nums1 和 nums2 以及一个整数 k ，请你返回第 k （从 1 开始编号）小的 nums1[i] * nums2[j] 的乘积，其中 0 <= i < nums1.length 且 0 <= j < nums2.length 。
 

示例 1：
```
输入：nums1 = [2,5], nums2 = [3,4], k = 2
输出：8
解释：第 2 小的乘积计算如下：
- nums1[0] * nums2[0] = 2 * 3 = 6
- nums1[0] * nums2[1] = 2 * 4 = 8
第 2 小的乘积为 8 。
```
示例 2：
```
输入：nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6
输出：0
解释：第 6 小的乘积计算如下：
- nums1[0] * nums2[1] = (-4) * 4 = -16
- nums1[0] * nums2[0] = (-4) * 2 = -8
- nums1[1] * nums2[1] = (-2) * 4 = -8
- nums1[1] * nums2[0] = (-2) * 2 = -4
- nums1[2] * nums2[0] = 0 * 2 = 0
- nums1[2] * nums2[1] = 0 * 4 = 0
第 6 小的乘积为 0 。
```
示例 3：
```
输入：nums1 = [-2,-1,0,1,2], nums2 = [-3,-1,2,4,5], k = 3
输出：-6
解释：第 3 小的乘积计算如下：
- nums1[0] * nums2[4] = (-2) * 5 = -10
- nums1[0] * nums2[3] = (-2) * 4 = -8
- nums1[4] * nums2[0] = 2 * (-3) = -6
第 3 小的乘积为 -6 。 
```
提示：

* 1 <= nums1.length, nums2.length <= 5 * 104
* -105 <= nums1[i], nums2[j] <= 105
* 1 <= k <= nums1.length * nums2.length
* nums1 和 nums2 都是从小到大排好序的。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/kth-smallest-product-of-two-sorted-arrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 解法：广度优先搜索 + 数学推导

我们假设某服务器 i 向主服务器传输信息需要的时间为 time，那么其收到反馈信息的时间为2×time。在[1,2×time−1] 秒内，该数据服务器每 patience[i] 秒重发一次信息，所以共重发了count=(2×time−1)/ patience[i] 次信息。最后一次信息的发送时间为第count×patience[i] 秒，该信息需要再经过一次主服务器反馈并返回服务器 i ，到达时间为count×patience[i]+2×time。

由此，我们遍历所有数据服务器，取所有这些服务器接收到最后一条反馈信息的时间中的最大值，该时间的下一秒网络就会空闲。

遍历所有数据服务器，我们可以先通过邻接表建图，并从主服务器 00 开始，利用广度优先搜索即可。

**算法细节**：
具体见代码注释

```c++
class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& p) {
        int n = p.size();
        
        // 邻接表建图
        vector<vector<int>> e(n);
        for(auto &ed : edges) {
            e[ed[0]].push_back(ed[1]);
            e[ed[1]].push_back(ed[0]);
        }
        
        // 记录哪些服务器已被扩展
        vector<bool> vis(n);
        queue<pair<int, int>> q;
        q.emplace(0, 0);
        vis[0] = true;
        
        // 记录最晚到达时间
        int ret = 0;
        
        // 广度优先搜索
        while(!q.empty()) {
            auto [c, time] = q.front();
            q.pop();
            
            if(c != 0) {
                // c != 0 是因为首先会扩展到主服务器
                int cost = ((2 * time - 1) / p[c]) * p[c] + 2 * time;
                ret = max(ret, cost);
            }
            
            // 扩展所有与当前数据服务器直接相连的服务器
            for(int &next : e[c]) {
                if(!vis[next]) {
                    vis[next] = true;
                    q.emplace(next, time + 1);
                }
            }
        }
        
        return ret + 1;
    }
};
```