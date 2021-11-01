## 编号：两个最好的不重叠活动

给你一个下标从 0 开始的二维整数数组 events ，其中 events[i] = [startTimei, endTimei, valuei] 。第 i 个活动开始于 startTimei ，结束于 endTimei ，如果你参加这个活动，那么你可以得到价值 valuei 。你 最多 可以参加 两个时间不重叠 活动，使得它们的价值之和 最大 。

请你返回价值之和的 最大值 。

注意，活动的开始时间和结束时间是 包括 在活动时间内的，也就是说，你不能参加两个活动且它们之一的开始时间等于另一个活动的结束时间。更具体的，如果你参加一个活动，且结束时间为 t ，那么下一个活动必须在 t + 1 或之后的时间开始。

示例 1:

![avater](https://assets.leetcode.com/uploads/2021/09/21/picture5.png)


```
输入：events = [[1,3,2],[4,5,2],[2,4,3]]
输出：4
解释：选择绿色的活动 0 和 1 ，价值之和为 2 + 2 = 4 。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/09/21/picture1.png)

```
输入：events = [[1,3,2],[4,5,2],[1,5,5]]
输出：5
解释：选择活动 2 ，价值和为 5 。
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2021/09/21/picture3.png)

```
输入：events = [[1,5,3],[1,5,1],[6,6,5]]
输出：8
解释：选择活动 0 和 2 ，价值之和为 3 + 5 = 8 。 
```
提示：

2 <= events.length <= 105
events[i].length == 3
1 <= startTimei <= endTimei <= 109
1 <= valuei <= 106

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-best-non-overlapping-events
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

按照题目意思，我们需要找到最多两个时间不重叠的活动，求出这个最高的价值。也就是说，**我们要从每一个活动中找寻其他活动中开始时间大于该活动结束时间且价值最大的一个。寻找开始时间大于该活动结束时间的第一个活动我们可以通过二分查找的方式快速解决，因为是有序存放的开始时间，所以查找到的活动后面的所有活动开始时间都必定大于查找到的这一个，我们通过后缀的方式预先求出查找位置以后所有活动的最大值即可。**

* 1.使用map表有序存放每个活动的开始时间和最大值, 如果有重复的开始时间保存最大的那个即可。
* 2.**通过后缀和的方式，反序遍历map表，通过哈希表记录大于当前开始时间的最大价值**，比如说大于90时间的最大值是50，大于30时间的最大值是20，那么此时大于30时间的最大值就应该变为50。经过此操作，哈希表内存放的是大于当前开始时间的所有后续活动的最大价值。
* 3.遍历每一个活动events，**在map里查找大于本活动结束时间的开始时间第一个活动**，在操作2的哈希表里面获取大于这个开始时间的所有后续活动的最大价值即可。

代码如下：
```c++
class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        int n = events.size();
        map<int, int> mapping;
        for (int i = 0; i < n; ++i) { // 保存{开始时间，最大价值}
            if (mapping.count(events[i][0]) > 0) {
                mapping[events[i][0]] = max(mapping[events[i][0]], events[i][2]);
            } else {
                mapping[events[i][0]] = events[i][2];
            }
        }
        auto x = mapping.rbegin();
        unordered_map<int, int> mx; // 保存{大于此开始时间的最大价值}
        int tot = 0;
        while (x != mapping.rend()) {
            tot = max(tot, x->second);
            mx[x->first] = tot;
            ++x;
        }
        int val = 0;
        for (int i = 0; i < n; ++i) {
            auto idx = mapping.upper_bound(events[i][1]); // 二分查找开始时间大于本活动结束时间的第一个活动
            if (idx == mapping.end()) {
                val = max(val, events[i][2]);
            } else {
                int cnt = mx[idx->first];
                val = max(val, events[i][2] + cnt); // 查找哈希表
            }
        }
        return val;
    }
}; 
```