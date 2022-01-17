## 编号：解决智力问题（×）

给你一个下标从 0 开始的二维整数数组 questions ，其中 questions[i] = [pointsi, brainpoweri] 。

这个数组表示一场考试里的一系列题目，你需要 按顺序 （也就是从问题 0 开始依次解决），针对每个问题选择 解决 或者 跳过 操作。解决问题 i 将让你 获得  pointsi 的分数，但是你将 无法 解决接下来的 brainpoweri 个问题（即只能跳过接下来的 brainpoweri 个问题）。如果你跳过问题 i ，你可以对下一个问题决定使用哪种操作。

    * 比方说，给你 questions = [[3, 2], [4, 3], [4, 4], [2, 5]] ：
        * 如果问题 0 被解决了， 那么你可以获得 3 分，但你不能解决问题 1 和 2 。
        * 如果你跳过问题 0 ，且解决问题 1 ，你将获得 4 分但是不能解决问题 2 和 3 。

请你返回这场考试里你能获得的 最高 分数。



示例 1：
```
输入：questions = [[3,2],[4,3],[4,4],[2,5]]
输出：5
解释：解决问题 0 和 3 得到最高分。
- 解决问题 0 ：获得 3 分，但接下来 2 个问题都不能解决。
- 不能解决问题 1 和 2
- 解决问题 3 ：获得 2 分
总得分为：3 + 2 = 5 。没有别的办法获得 5 分或者多于 5 分。
```
示例 2：
```
输入：questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]
输出：7
解释：解决问题 1 和 4 得到最高分。
- 跳过问题 0
- 解决问题 1 ：获得 2 分，但接下来 2 个问题都不能解决。
- 不能解决问题 2 和 3
- 解决问题 4 ：获得 5 分
总得分为：2 + 5 = 7 。没有别的办法获得 7 分或者多于 7 分。
```
提示：

* 1 <= questions.length <= 10^5
* questions[i].length == 2
* 1 <= pointsi, brainpoweri <= 10^5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/solving-questions-with-brainpower
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 逆序dp（查表法）
设有 n 个问题，定义 f[i] 表示解决区间 [i,n−1] 内的问题可以获得的最高分数。

倒序遍历问题列表，对于第 i 个问题，我们有两种决策：跳过或解决。

若跳过，则有 f[i] = f[i+1]

若解决，则需要跳过后续brainpower[i] 个问题。记 j = i + brainpower[i] + 1，则有

f[i] = (point[i]+f[j], j < n; point[i],j ≥ n)

这两种决策取最大值。

最后答案为 f[0]。


代码如下：
```c++
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> dp(n + 1);//dp[i]代表区间【i，n - 1】内能得到的最大分数
        dp[n] = 0; //初值为0
        for(int i = n - 1; i >= 0; i--){
            /*每遍历一个question就往后查是否存在还可以是否还有题可以做
              每次遍历将可以做的题目的分数计入dp数组
              将不同题目的组合取最大值
            */
            auto &q = questions[i];
            int j = i + q[1] + 1;
            dp[i] = max(dp[i + 1], q[0] + (j < n ? dp[j] : 0));
        }
        return dp[0];
    }
};
```
### 正序dp

定义dp[i]为做到第i题时得到的最高分

1.选择跳过，不加此题得分，后续的题继承得分

2.选择做题，加上此题得分，跳过若干题后的下一题继承得分

3.答案为所有可能得分的最大值

代码如下：
```c++
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> dp(n);//代表做到第i题时的最高分
        for(int i = 0; i < n; i++){
            if(i + 1 < n){
                //继承得分
                dp[i + 1] = max(dp[i], dp[i + 1]);
            }
            dp[i] += questions[i][0];
            int j = i + questions[i][1] + 1;
            if(j < n){
                //做了第i题只能从第j题开始做
                dp[j] = max(dp[i], dp[j]);
            }
        }
        long long res = 0;
        for(int i = 0; i < n; i++){
            res = max(res, dp[i]);
            //cout << dp[i] << " ";
        }
        return res;
    }
};
```
