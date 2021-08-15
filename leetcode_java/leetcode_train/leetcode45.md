## 跳跃游戏Ⅱ
给你一个非负整数数组 nums ，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用**最少的跳跃次数**到达数组的最后一个位置。

假设你总是可以到达数组的最后一个位置。

 

示例 1:
```
输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
```
示例 2:
```
输入: nums = [2,3,0,1,4]
输出: 2
```
提示:

* 1 <= nums.length <= 104
* 0 <= nums[i] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/jump-game-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
本题相对于[55.跳跃游戏](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode55.md)还是难了不少。

但思路是相似的，还是要看最大覆盖范围。

本题要计算最小步数，那么就要想清楚什么时候步数才一定要加一呢？
贪心的思路，局部最优：当前可移动距离尽可能多走，如果还没到终点，步数再加一。整体最优：一步尽可能多走，从而达到最小步数。

思路虽然是这样，但在写代码的时候还不能真的就能跳多远跳远，那样就不知道下一步最远能跳到哪里了。

**所以真正解题的时候，要从覆盖范围出发，不管怎么跳，覆盖范围内一定是可以跳到的，以最小的步数增加覆盖范围，覆盖范围一旦覆盖了终点，得到的就是最小步数！**

**这里需要统计两个覆盖范围，当前这一步的最大覆盖和下一步最大覆盖。**

如果移动下标达到了当前这一步的最大覆盖最远距离了，还没有到终点的话，那么就必须再走一步来增加覆盖范围，直到覆盖范围覆盖了终点。

如图：
![avater](https://camo.githubusercontent.com/52b0a6a3163808900ca557fe8f794b094caeaf7c2efd2d8094e0a94f04e7a21e/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313230313233323330393130332e706e67)
<span style="color:green">图中覆盖范围的意义在于，只要红色的区域，最多两步一定可以到！（不用管具体怎么跳，反正一定可以跳到）</span>

## 方法一
从图中可以看出来，就是移动下标达到了当前覆盖的最远距离下标时，步数就要加一，来增加覆盖距离。最后的步数就是最少步数。

这里还是有个特殊情况需要考虑，当移动下标达到了当前覆盖的最远距离下标时

* 如果当前覆盖最远距离下标不是是集合终点，步数就加一，还需要继续走。
* 如果当前覆盖最远距离下标就是是集合终点，步数不用加一，因为不能再往后走了。

整体代码如下：
```java
class Solution {
    public int jump(int[] nums) {
        if (nums.length == 1) return 0;
        int curDistance = 0;    // 当前覆盖最远距离下标
        int ans = 0;            // 记录走的最大步数
        int nextDistance = 0;   // 下一步覆盖最远距离下标
        for (int i = 0; i < nums.length; i++) {
            nextDistance = Math.max(nums[i] + i, nextDistance);  // 更新下一步覆盖最远距离下标
            if (i == curDistance) {                         // 遇到当前覆盖最远距离下标
                if (curDistance != nums.length - 1) {       // 如果当前覆盖最远距离下标不是终点
                    ans++;                                  // 需要走下一步
                    curDistance = nextDistance;             // 更新当前覆盖最远距离下标（相当于加油了）
                    if (nextDistance >= nums.length - 1) break; // 下一步的覆盖范围已经可以达到终点，结束循环
                } else break;                               // 当前覆盖最远距离下标是集合终点，不用做ans++操作了，直接结束
            }
        }
        return ans;
    }
}
```

## 方法二
依然是贪心，思路和方法一差不多，代码可以简洁一些。

针对于方法一的特殊情况，可以统一处理，即：移动下标只要遇到当前覆盖最远距离的下标，直接步数加一，不考虑是不是终点的情况。

想要达到这样的效果，只要让移动下标，最大只能移动到nums.size - 2的地方就可以了。

因为当移动下标指向nums.size - 2时：

* 如果移动下标等于当前覆盖最大距离下标， 需要再走一步（即ans++），因为最后一步一定是可以到的终点。（题目假设总是可以到达数组的最后一个位置），如图：
![avater](https://camo.githubusercontent.com/96c8d3ad8223401e1dbe9973b55d6da5578a10264185dff0472c19f3114d8d3b/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313230313233323434353238362e706e67)
* 如果移动下标不等于当前覆盖最大距离下标，说明当前覆盖最远距离就可以直接达到终点了，不需要再走一步。如图：
![avater](https://camo.githubusercontent.com/29fc6ee92bd2a8b3e24fe6b785fcc869ab8c9bd85d8302b9dcb7a4ecd8effc2f/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313230313233323333383639332e706e67)

整体代码如下：
```java
// 版本二
class Solution {
    public int jump(int[] nums) {
        int curDistance = 0;    // 当前覆盖的最远距离下标
        int ans = 0;            // 记录走的最大步数
        int nextDistance = 0;   // 下一步覆盖的最远距离下标
        for (int i = 0; i < nums.length - 1; i++) { // 注意这里是小于nums.length - 1，这是关键所在
            nextDistance = Math.max(nums[i] + i, nextDistance); // 更新下一步覆盖的最远距离下标
            if (i == curDistance) {                 // 遇到当前覆盖的最远距离下标
                curDistance = nextDistance;         // 更新当前覆盖的最远距离下标
                ans++;
            }
        }
        return ans;
    }
}
```