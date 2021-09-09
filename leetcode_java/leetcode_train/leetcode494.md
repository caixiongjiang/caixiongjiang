## 编号494：目标和

给你一个整数数组 nums 和一个整数 target 。

向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 **表达式** ：

例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
返回可以通过上述方法构造的、运算结果等于 target 的不同 **表达式** 的数目。

 

示例 1：
```
输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有 5 种方法让最终目标和为 3 。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
```
示例 2：
```
输入：nums = [1], target = 1
输出：1
```
提示：

* 1 <= nums.length <= 20
* 0 <= nums[i] <= 1000
* 0 <= sum(nums[i]) <= 1000
* -1000 <= target <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/target-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
第一眼看去又是回溯的问题，此时可以套组合总和的回溯法代码。

当然它超时了！！

不过为了复习，先把回溯法先写一遍：

```c++
class Solution{
    private:
        vector<vector<int>> result;
        vector<int> path;
        void backTracking(vector<int>& candidates, int target, int sum, int startIndex){
            if(sum == target){
                result.push_back(path);
            }
            //如果sum + candidates[i] > target 就终止遍历
            for(int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++){
                sum += candidates[i];
                path.push_back(candidates[i]);
                backTracking(candidates, target, sum, i + 1);
                sum -= candidats[i];//回溯
                path.pop_back();//回溯
            }
        }
    public:
        int findTargetSumWays(vector<int>& nums, int S){
            int sum = 0;
            for(int i = 0; i < nums.size(); i++) sum += nums[i];
            if(S > sum) return 0;//此时没有方案
            if((S + sum) % 2) return 0;//此时没有方案，两个int相加的时候要各位小心数值溢出的问题
            int bigSize = (S + sum) / 2;//转变为组合总和问题，bigsize就是要求的和

            //回溯法代码
            result.clear();
            path.clear();
            sort(nums.begin(), nums.end());//需要排序
            backTracking(nums, bagSize, 0, 0);
            return result.size();
        }
};
```

## 动态规划
