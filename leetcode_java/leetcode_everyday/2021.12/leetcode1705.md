## 编号1705：吃苹果的最大数目

有一棵特殊的苹果树，一连 n 天，每天都可以长出若干个苹果。在第 i 天，树上会长出 apples[i] 个苹果，这些苹果将会在 days[i] 天后（也就是说，第 i + days[i] 天时）腐烂，变得无法食用。也可能有那么几天，树上不会长出新的苹果，此时用 apples[i] == 0 且 days[i] == 0 表示。

你打算每天 最多 吃一个苹果来保证营养均衡。注意，你可以在这 n 天之后继续吃苹果。

给你两个长度为 n 的整数数组 days 和 apples ，返回你可以吃掉的苹果的最大数目。



示例 1：
```
输入：apples = [1,2,3,5,2], days = [3,2,1,4,2]
输出：7
解释：你可以吃掉 7 个苹果：
- 第一天，你吃掉第一天长出来的苹果。
- 第二天，你吃掉一个第二天长出来的苹果。
- 第三天，你吃掉一个第二天长出来的苹果。过了这一天，第三天长出来的苹果就已经腐烂了。
- 第四天到第七天，你吃的都是第四天长出来的苹果。
```
示例 2：
```
输入：apples = [3,0,0,0,0,2], days = [3,0,0,0,0,2]
输出：5
解释：你可以吃掉 5 个苹果：
- 第一天到第三天，你吃的都是第一天长出来的苹果。
- 第四天和第五天不吃苹果。
- 第六天和第七天，你吃的都是第六天长出来的苹果。
```
提示：

* apples.length == n
* days.length == n
* 1 <= n <= 2 * 10^4
* 0 <= apples[i], days[i] <= 2 * 10^4
* 只有在 apples[i] = 0 时，days[i] = 0 才成立

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-number-of-eaten-apples
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 优先队列+贪心

为了将吃苹果的数目最大化，应该使用贪心策略，在尚未腐烂的苹果中优先选择腐烂日期最早的苹果。

计算吃苹果的最大数目分成两个阶段，第一阶段是第 0 天到第 n−1 天，即天数在数组下标范围内，第二阶段是第 n 天及以后，即天数在数组下标范围外。

在第一阶段，由于每天树上都可能长出苹果，因此需要对每一天分别计算是否能吃到苹果，并更新优先队列。具体做法如下：

* 1.将优先队列中的所有腐烂日期小于等于当前日期的元素取出，这些元素表示已经腐烂的苹果，无法食用；

* 2.根据days 和apples的当前元素计算当天长出的苹果的腐烂日期和数量，如果数量大于 0，则将腐烂日期和数量加入优先队列；

* 3.如果优先队列不为空，则当天可以吃 11 个苹果，将优先队列的队首元素的数量减 1，如果队首元素的数量变成 0 则将队首元素取出。

在第二阶段，由于树上不会再长出苹果，因此**只需要考虑能吃到的苹果数量**。由于优先队列中的每个元素的数量可能很大，因此需要根据当前日期和优先队列的队首元素的腐烂日期和数量计算能吃到的苹果数量。

假设当前日期是第 i 天，首先将优先队列中的所有腐烂日期小于等于 i 的元素取出，如果优先队列不为空，则根据优先队列的队首元素计算能吃到的苹果数量。假设优先队列的队首元素的腐烂日期是 x，数量是 y，其中 x>i，则有 y 个苹果，距离腐烂还有 x−i 天，因此能吃到的苹果数量是 curr = min(x−i,y)。将优先队列的队首元素 (x,y) 取出并将日期增加 curr，重复上述操作直到优先队列为空，即可得到吃苹果的最大数目。


代码如下：
```c++
typedef pair<int,int> pii;

class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int ans = 0;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        int n = apples.size();
        int i = 0;
        while (i < n) {
            while (!pq.empty() && pq.top().first <= i) {
                pq.pop();
            }
            int rottenDay = i + days[i];
            int count = apples[i];
            if (count > 0) {
                pq.emplace(rottenDay, count);
            }
            if (!pq.empty()) {
                pii curr = pq.top();
                pq.pop();
                curr.second--;
                if (curr.second != 0) {                  
                    pq.emplace(curr.first, curr.second);
                }
                ans++;
            }
            i++;
        }
        while (!pq.empty()) {
            while (!pq.empty() && pq.top().first <= i) {
                pq.pop();
            }
            if (pq.empty()) {
                break;
            }
            pii curr = pq.top();
            pq.pop();
            int num = min(curr.first - i, curr.second);
            ans += num;
            i += num;
        }
        return ans;
    }
};
```