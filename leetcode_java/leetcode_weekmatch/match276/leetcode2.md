## 编号：得到目标值的最少行动次数(AC)

你正在玩一个整数游戏。从整数 1 开始，期望得到整数 target 。

在一次行动中，你可以做下述两种操作之一：

* 递增，将当前整数的值加 1（即， x = x + 1）。
* 加倍，使当前整数的值翻倍（即，x = 2 * x）。
在整个游戏过程中，你可以使用 递增 操作 任意 次数。但是只能使用 加倍 操作 至多 maxDoubles 次。

给你两个整数 target 和 maxDoubles ，返回从 1 开始得到 target 需要的最少行动次数。




示例 1：
```
输入：target = 5, maxDoubles = 0
输出：4
解释：一直递增 1 直到得到 target 。
```
示例 2：
```
输入：target = 19, maxDoubles = 2
输出：7
解释：最初，x = 1 。
递增 3 次，x = 4 。
加倍 1 次，x = 8 。
递增 1 次，x = 9 。
加倍 1 次，x = 18 。
递增 1 次，x = 19 。
```
示例 3：
```
输入：target = 10, maxDoubles = 4
输出：4
解释：
最初，x = 1 。 
递增 1 次，x = 2 。 
加倍 1 次，x = 4 。 
递增 1 次，x = 5 。 
加倍 1 次，x = 10 。 
```
提示：

* 1 <= target <= 10^9
* 0 <= maxDoubles <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-moves-to-reach-target-score
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
---

## 思路

我们需要更好的步数，一定是希望加倍越多越好。

逆向推导：

1.如果是奇数，就-1
2.如果是偶数，就除以2
3.如果减半的次数用完了就只能减1了

第一次超时代码：
```c++
class Solution {
public:
    int minMoves(int target, int maxDoubles) {
        int res = 0;
        if(target == 1) return 0;
        while(target > 1){
            if(target % 2 != 0){
                target--;
                res++;
            }else{
                if(maxDoubles > 0){
                    target /= 2;
                    maxDoubles--;
                    res++;
                }else{
                    target--;
                    res++;
                }
            }   
        }
        return res;
    }
};
```

原因是如果target很大，maxDoubles又为0时，需要不断递减，超时。

可以做一个剪枝

代码如下：
```c++
class Solution {
public:
    int minMoves(int target, int maxDoubles) {
        int res = 0;
        if(target == 1) return 0;
        if(maxDoubles == 0){
            res = target - 1;
        }
        else{
            while(target > 1){
                if(target % 2 != 0){
                    target--;
                    res++;
                }else{
                    if(maxDoubles > 0){
                        target /= 2;
                        maxDoubles--;
                        res++;
                    }else{
                        target--;
                        res++;
                    }
                }   
            }
        }
        return res;
    }
};
```

## 继续优化

发现只优化了循环外的递减操作，可以将循环里面也优化

代码如下：
```c++
class Solution {
public:
    int minMoves(int target, int maxDoubles) {
        int ret = 0;
        while (target != 1) {
            if (maxDoubles == 0) {
                ret += target-1;
                break;
            }
            if (target % 2 == 0) {
                target /= 2;
                ret++;
                maxDoubles--;
            }
            else {
                target /= 2;
                ret += 2;
                maxDoubles--;
            }
        }
        return ret;
    }
};
```
