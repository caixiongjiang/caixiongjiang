## 编号1049：最后一块石头的重量Ⅱ

有一堆石头，用整数数组 stones 表示。其中 stones[i] 表示第 i 块石头的重量。

每一回合，从中选出**任意两块石头**，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：

* 如果 x == y，那么两块石头都会被完全粉碎；
* 如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
最后，**最多只会剩下一块** 石头。返回此石头 **最小的可能重量** 。如果没有石头剩下，就返回 0。

 

示例 1：
```
输入：stones = [2,7,4,1,8,1]
输出：1
解释：
组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]，
组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]，
组合 2 和 1，得到 1，所以数组转化为 [1,1,1]，
组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。
```
示例 2：
```
输入：stones = [31,26,33,21,40]
输出：5
```
示例 3：
```
输入：stones = [1,2]
输出：1 
```
提示：

* 1 <= stones.length <= 30
* 1 <= stones[i] <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/last-stone-weight-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

本题其实就是尽量让石头分成重量相同的两堆，相撞之后剩下的石头最小，这样就化解成01背包问题了。

是不是感觉和昨天讲解的[416. 分割等和子集](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode416.md)非常像了。

本题物品的重量为store[i]，物品的价值也为store[i]。

对应着01背包里的物品重量weight[i]和 物品价值value[i]。

接下来进行动规五步曲：

1.确定dp数组以及下标的含义

**dp[j]表示容量为j的背包，最多可以背dp[j]这么重的石头。**

2.确定递推公式

01背包的递推公式为：dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);

本题则是：**dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);**

可能看到这dp[j - stones[i]] + stones[i]中 又有- stones[i] 又有+stones[i]，看着有点晕乎。

还是要牢记dp[j]的含义，要知道dp[j - stones[i]]为 容量为j - stones[i]的背包最大所背重量。

3.dp数组如何初始化

既然 dp[j]中的j表示容量，那么最大容量（重量）是多少呢，就是所有石头的重量和。

因为提示中给出1 <= stones.length <= 30，1 <= stones[i] <= 1000，所以最大重量就是30 * 1000 。

而我们要求的target其实只是最大重量的一半，所以dp数组开到15000大小就可以了。

当然也可以把石头遍历一遍，计算出石头总重量 然后除2，得到dp数组的大小。

我这里就直接用15000了。

接下来就是如何初始化dp[j]呢，因为重量都不会是负数，所以dp[j]都初始化为0就可以了，这样在递归公式dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);中dp[j]才不会初始值所覆盖。

代码为：
```c++
vector<int> dp(15001, 0);
```
4.确定遍历顺序

在[动态规划：关于01背包问题，你该了解这些！（滚动数组）](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/%E5%85%B3%E4%BA%8E01%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%EF%BC%88%E6%BB%9A%E5%8A%A8%E6%95%B0%E7%BB%84%EF%BC%89.md)中就已经说明：如果使用一维dp数组，物品遍历的for循环放在外层，遍历背包的for循环放在内层，且内层for循环倒叙遍历！

代码如下：

```c++
for(int i = 0; i < stones.size(); i++){//遍历物品
    for(int j = target; j >= stones[i]; j--){//遍历背包
        dp[j] = max(dp[j],dp[j - stones[i]] + stones[i]);
    }
}
```
5.举例推导dp数组

输入：[2,4,1,1]，此时target=(2+4+1+1)/2 = 4,dp数组的状态图如下：
![avater](https://camo.githubusercontent.com/66a1997cb20485150923610a041234548ada396071aab195b9d95dc0e7a096f7/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132313131353830353930342e6a7067)

最后dp[target]里容量为targrt的背包所能背的最大重量。

那么分成两堆石头，一堆石头的总重量为dp[target]，另一堆就是sum - dp[target]。

**在计算target的时候，target = sum / 2因为是向下取整，所以sum-dp[target]一定是大于等于dp[target]的。**

那么相撞之后剩下的最小石头重量就是sum - dp[target] - dp[target]

整体c++代码如下：
```c++
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        vector<int> dp(15001, 0);
        int sum = 0;
        for(int i = 0; i < stones.size(); i++){
            sum += stones[i];
        }
        int target = sum / 2;
        for(int i = 0; i < stones.size(); i++){
            for(int j = target; j >= stones[i]; j--){
                dp[j] = max(dp[j],dp[j - stones[i]] + stones[i]);
            }
        }
        //分成两堆石头，第一堆石头的重量为dp[target]，另一堆为sum - dp[target]，
        //剩下的石头就是sum - 2 * dp[target]
        return sum - dp[target] - dp[target];
    }
};
```