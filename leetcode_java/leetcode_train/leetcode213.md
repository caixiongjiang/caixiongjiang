## 编号213：打家劫舍Ⅱ

你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都**围成一圈**，这意味着**第一个房屋和最后一个房屋是紧挨着的**。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。

给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。

 

示例 1：
```
输入：nums = [2,3,2]
输出：3
解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
```
示例 2：
```
输入：nums = [1,2,3,1]
输出：4
解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
     偷窃到的最高金额 = 1 + 3 = 4 。
```
示例 3：
```
输入：nums = [0]
输出：0 
```
提示：

* 1 <= nums.length <= 100
* 0 <= nums[i] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/house-robber-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
这道题目和[198.打家劫舍](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode198.md)是差不多的，唯一区别就是成环了。

对于一个数组，成环的话主要有如下三种情况：

* 情况一：考虑不包含首尾元素

![avater](https://camo.githubusercontent.com/cda61fe4326306f85a0bb289439361feca5c8d6f06b034c822243d97651b4895/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132393136303734383634332e6a7067)

* 情况二：考虑包含首元素，不包含尾元素

![avater](https://camo.githubusercontent.com/7ddcbfca80ef22e908531cb5226a76f679fed6740348da9b3de45c1a7fddd848/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132393136303832313337342e6a7067)

* 情况三：考虑尾元素，不包含首元素

![avater](https://camo.githubusercontent.com/c6200435004b9fefd988195266a994ed85d727352104ea2192067ba8eed8942e/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303132393136303834323439312e6a7067)

注意我这里用的是"考虑"，例如情况三，虽然是考虑包含尾元素，但不一定要选尾部元素！ 对于情况三，取nums[1] 和 nums[3]就是最大的。

**而情况二 和 情况三 都包含了情况一了，所以只考虑情况二和情况三就可以了。**

整体代码如下：
```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) return nums[0];
        int result1 = robRange(nums, 0, nums.size() - 2);//情况二：只考虑首，不考虑尾
        int result2 = robRange(nums, 1, nums.size() - 1);//情况三：只考虑尾，不考虑首
        return max(result1, result2);
    }

    //198题打家劫舍的逻辑
    int robRange(vector<int>& nums, int start, int end){
        if(start == end) return nums[start];
        vector<int> dp(nums.size());
        dp[start] = nums[start];
        dp[start + 1] = max(nums[start], nums[start + 1]);
        for(int i = start + 2; i <= end; i++){
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[end];
    }
};
```