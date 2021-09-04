## 编号134：加油站
在一条环路上有 N 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。

说明: 

* 如果题目有解，该答案即为唯一答案。
* 输入数组均为非空数组，且长度相同。
* 输入数组中的元素均为非负数。
示例 1:
```
输入: 
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

输出: 3

解释:
从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
因此，3 可为起始索引。
```
示例 2:
```
输入: 
gas  = [2,3,4]
cost = [3,4,3]

输出: -1

解释:
你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
因此，无论怎样，你都不可能绕环路行驶一周。
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/gas-station
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
暴力解法当然为O(n^2),不作讨论。
## 贪心算法(方法一)
直接从全局进行贪心选择，情况如下：

* 情况一：如果gas的总和小于cost总和，那么无论从哪里出发，一定是跑不了一圈的

* 情况二：rest[i] = gas[i]-cost[i]为一天剩下的油，i从0开始计算累加到最后一站，如果累加没有出现负数，说明从0出发，油就没有断过，那么0就是起点。

* 情况三：如果累加的最小值是负数，汽车就要从非0节点出发，从后向前，看哪个节点能这个负数填平，能把这个负数填平的节点就是出发节点。

</br>整体代码如下：

```java
class Solution {
    public int canCompleteCircuit(int[] gas, int[] cost) {
        int curSum = 0;
        int min = Integer.MAX_VALUE;//从起点出发，邮箱里的油量最小值
        for(int i = 0; i < gas.length; i++){
            int rest = gas[i] - cost[i];
            curSum += rest;
            if(curSum < min){
                min = curSum;
            }
        }
        if(curSum < 0) return -1;//情况一
        if(min >= 0) return 0;//情况二
        //情况三
        for(int i = gas.length - 1; i >= 0; i--){
            int rest = gas[i] - cost[i];
            min += rest;
            if(min >= 0){
                return i;
            }
        }
        return -1;
    }
}
```
**这种方法没有找出局部最优，直接从全局最优来考虑。**

## 贪心算法(方法二)
首先如果总油量减去总消耗大于等于零那么一定可以跑完一圈，说明 各个站点的加油站 剩油量rest[i]相加一定是大于等于零的。

每个加油站的剩余量rest[i]为gas[i] - cost[i]。

**i从0开始累加rest[i]，和记为curSum，一旦curSum小于零，说明[0, i]区间都不能作为起始位置，起始位置从i+1算起，再从0计算curSum。**
</br></br>
如图：
![avater](https://camo.githubusercontent.com/df6c8b10ac9072ae3c268f4224ebcb0e9338f7e41a657840a45f8bba84961987/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313231333136323832313935382e706e67)

那么为什么一旦[i，j] 区间和为负数，起始位置就可以是j+1呢，j+1后面就不会出现更大的负数？

如果出现更大的负数，就是更新j，那么起始位置又变成新的j+1了。

而且j之前出现了多少负数，j后面就会出现多少正数，因为耗油总和是大于零的（前提我们已经确定了一定可以跑完全程）。

**那么局部最优：当前累加rest[j]的和curSum一旦小于0，起始位置至少要是j+1，因为从j开始一定不行。全局最优：找到可以跑一圈的起始位置。**

局部最优可以推出全局最优。
整体代码如下：
```java
class Solution {
    public int canCompleteCircuit(int[] gas, int[] cost) {
        int curSum = 0;
        int totalSum = 0;
        int start = 0;//返回出发加油站的下标
        for(int i = 0; i < gas.length; i++){
            curSum += gas[i] - cost[i];
            totalSum += gas[i] - cost[i];
            if(curSum < 0){//当前累加rest[i]和curSum一旦小于0
                start = i + 1;//起始位置更新为i+1
                curSum = 0;//curSum重新从0开始
            } 
        }
        if(totalSum < 0) return -1;
        return start;
    }
}
```