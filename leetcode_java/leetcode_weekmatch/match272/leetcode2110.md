## 编号2110:股票平滑下跌阶段的数目

给你一个整数数组 prices ，表示一支股票的历史每日股价，其中 prices[i] 是这支股票第 i 天的价格。

一个 平滑下降的阶段 定义为：对于 连续一天或者多天 ，每日股价都比 前一日股价恰好少 1 ，这个阶段第一天的股价没有限制。

请你返回 平滑下降阶段 的数目。

 

示例 1：
```
输入：prices = [3,2,1,4]
输出：7
解释：总共有 7 个平滑下降阶段：
[3], [2], [1], [4], [3,2], [2,1] 和 [3,2,1]
注意，仅一天按照定义也是平滑下降阶段。
```
示例 2：
```
输入：prices = [8,6,7,7]
输出：4
解释：总共有 4 个连续平滑下降阶段：[8], [6], [7] 和 [7]
由于 8 - 6 ≠ 1 ，所以 [8,6] 不是平滑下降阶段。
```
示例 3：
```
输入：prices = [1]
输出：1
解释：总共有 1 个平滑下降阶段：[1] 
```
提示：

* 1 <= prices.length <= 105
* 1 <= prices[i] <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-smooth-descent-periods-of-a-stock
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 分区间统计

我的步骤：

1.双指针遍历数组，碰到题目说的**股票平滑下跌的日子**快指针就往后移动，直到找到不是**股票平滑下跌的日子**的那天的下标。

2.对这个区间进行一次统计，利用数学上的结论给出：int m = j - i ，个数为m * （m - 1）/ 2 。并将i指针移到j指针相邻的左边的位置，并将i，j指针都往后移动，继续按照步骤1进行判断

3.次数为数组自身的长度加上每个区间的次数之和。

注意点：

1.因为遍历是通过后一个下标进行计数，由于数组不能遍历到超出数组长度的位置，最后一次需要对数组的i的位置到结尾做一次单独的统计！

2.需要注意统计次数的时候可能超出int表示范围，需要强制转换为long long类型。

代码如下：
```c++
class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        int n = prices.size();
        long long ans = 0;
        int i = 0, j = 1;
        while(i < j && j < n){
            if(prices[j - 1] - prices[j] == 1){
                j++;
            }else{
                int m = j - i;
                //cout << m << endl;
                ans += (long long)((m - 1) * m / 2);
                i = j - 1;
                i++;//千万别忘记推进i和j的位置，不然就是死循环
                j++;
            }
        }
        ans += (long long)(j - i) * (j - i - 1) / 2;//这里注意乘法可能会超出int能表示的范围
        return ans + n;
    }
};
```


又copy了第一名的代码!

代码如下：
```c++
class Solution {
public:
    long long getDescentPeriods(vector<int>& a) {
        long long ans = 0;
        for(int i = 0; i < a.size(); ) {
            int j = i;
            while(j < a.size() && a[j] - a[i] == i - j) ++j;
            ans += (long long)(j - i) * (j - i + 1) / 2;
            i = j;
        }
        return ans;
    }
};
```

大体思路一致，这里的j的初值设置不一样，最后一步不需要单独处理，处理时间更加短。

### 直接计数的思想

代码如下：
```c++
class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        long long n = prices.size(), ans=1, len=1;
        for(int i = 1;i < n;i++){
            len = (prices[i] == prices[i-1] - 1) ? len + 1 : 1;
            ans += len;
        }
        return ans;
    }
};
```

**判断每一位和前一位是否符合”平滑下跌“，如是，记录长度+1，<span style="color:green">否则重新置1</span>，这样每一位的len记录的是“以当前位置结束的平滑下跌阶段的数目”，每次累加即可!**