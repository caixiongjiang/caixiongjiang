## 编号：同时运行 N 台电脑的最长时间（×）

你有 n 台电脑。给你整数 n 和一个下标从 0 开始的整数数组 batteries ，其中第 i 个电池可以让一台电脑 运行 batteries[i] 分钟。你想使用这些电池让 全部 n 台电脑 同时 运行。

一开始，你可以给每台电脑连接 至多一个电池 。然后在任意整数时刻，你都可以将一台电脑与它的电池断开连接，并连接另一个电池，你可以进行这个操作 任意次 。新连接的电池可以是一个全新的电池，也可以是别的电脑用过的电池。断开连接和连接新的电池不会花费任何时间。

注意，你不能给电池充电。

请你返回你可以让 n 台电脑同时运行的 最长 分钟数。



示例 1：

![avater](https://assets.leetcode.com/uploads/2022/01/06/example1-fit.png)

```
输入：n = 2, batteries = [3,3,3]
输出：4
解释：
一开始，将第一台电脑与电池 0 连接，第二台电脑与电池 1 连接。
2 分钟后，将第二台电脑与电池 1 断开连接，并连接电池 2 。注意，电池 0 还可以供电 1 分钟。
在第 3 分钟结尾，你需要将第一台电脑与电池 0 断开连接，然后连接电池 1 。
在第 4 分钟结尾，电池 1 也被耗尽，第一台电脑无法继续运行。
我们最多能同时让两台电脑同时运行 4 分钟，所以我们返回 4 。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2022/01/06/example2.png)

```
输入：n = 2, batteries = [1,1,1,1]
输出：2
解释：
一开始，将第一台电脑与电池 0 连接，第二台电脑与电池 2 连接。
一分钟后，电池 0 和电池 2 同时耗尽，所以你需要将它们断开连接，并将电池 1 和第一台电脑连接，电池 3 和第二台电脑连接。
1 分钟后，电池 1 和电池 3 也耗尽了，所以两台电脑都无法继续运行。
我们最多能让两台电脑同时运行 2 分钟，所以我们返回 2 。
```
提示：

* 1 <= n <= batteries.length <= 105
* 1 <= batteries[i] <= 109

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-running-time-of-n-computers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 排序+贪心

我们对电池电量从大到小排序，然后从电量最大的电池开始遍历：

若该电池电量超过x，则将其供给一台电脑，问题缩减为 n-1 台电脑的子问题。

若该电池电量不超过 x，则其余电池的电量均不超过 x，此时有 n * x = n * abs（sum/n） <= sum


代码如下：
```c++
class Solution {
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        long long sum = 0;
        long long res = 0;

        sort(batteries.begin(), batteries.end(), greater<int>());
        for(auto &batterie : batteries){
            sum += batterie;
        }

        for(auto &batterie : batteries){
            if(batterie > sum / n){
                n -= 1;
                sum -= batterie;
            }else{
                res = sum / n;
                break;
            }
        }
        return res;
    }
};
```

### 二分法

代码如下：
```c++
class Solution {
public:
    long long maxRunTime(int n, vector<int> &batteries) {
        long tot = accumulate(batteries.begin(), batteries.end(), 0L);
        long l = 1, r = tot / n + 1;
        while (l < r) {
            long x = (l + r) / 2, sum = 0;
            for (long b : batteries) {
                sum += min(b, x);
            }
            if (n * x <= sum) {
                l = x + 1;
            } else {
                r = x;
            }
        }
        return l - 1;
    }
};
```
