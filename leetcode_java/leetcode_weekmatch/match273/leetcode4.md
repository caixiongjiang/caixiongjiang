## 编号：还原原数组(🍵)

Alice 有一个下标从 0 开始的数组 arr ，由 n 个正整数组成。她会选择一个任意的 正整数 k 并按下述方式创建两个下标从 0 开始的新整数数组 lower 和 higher ：

* 1.对每个满足 0 <= i < n 的下标 i ，lower[i] = arr[i] - k
* 2.对每个满足 0 <= i < n 的下标 i ，higher[i] = arr[i] + k
不幸地是，Alice 丢失了全部三个数组。但是，她记住了在数组 lower 和 higher 中出现的整数，但不知道每个整数属于哪个数组。请你帮助 Alice 还原原数组。

给你一个由 2n 个整数组成的整数数组 nums ，其中 恰好 n 个整数出现在 lower ，剩下的出现在 higher ，还原并返回 原数组 arr 。如果出现答案不唯一的情况，返回 任一 有效数组。

注意：生成的测试用例保证存在 至少一个 有效数组 arr 。

 

示例 1：
```
输入：nums = [2,10,6,4,8,12]
输出：[3,7,11]
解释：
如果 arr = [3,7,11] 且 k = 1 ，那么 lower = [2,6,10] 且 higher = [4,8,12] 。
组合 lower 和 higher 得到 [2,6,10,4,8,12] ，这是 nums 的一个排列。
另一个有效的数组是 arr = [5,7,9] 且 k = 3 。在这种情况下，lower = [2,4,6] 且 higher = [8,10,12] 。
```
示例 2：
```
输入：nums = [1,1,3,3]
输出：[2,2]
解释：
如果 arr = [2,2] 且 k = 1 ，那么 lower = [1,1] 且 higher = [3,3] 。
组合 lower 和 higher 得到 [1,1,3,3] ，这是 nums 的一个排列。
注意，数组不能是 [1,3] ，因为在这种情况下，获得 [1,1,3,3] 唯一可行的方案是 k = 0 。
这种方案是无效的，k 必须是一个正整数。
```
示例 3：
```
输入：nums = [5,435]
输出：[220]
解释：
唯一可行的组合是 arr = [220] 且 k = 215 。在这种情况下，lower = [5] 且 higher = [435] 。
```
提示：

* 2 * n == nums.length
* 1 <= n <= 1000
* 1 <= nums[i] <= 10^9
* 生成的测试用例保证存在 至少一个 有效数组 arr

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/recover-the-original-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

1.对数组nums进行排序, nums[0]即为lower[0]最小的;

2.枚举[1,n-1]的元素, 先计算k值;

3.然后l = 1, r =i+1, 双指针寻找满足nums[r] - nums[l] == 2k的元素, 将结果存入ans中;

4.如果所有元素都可以匹配, 返回ans;


代码如下：
```c++
class Solution {
public:
    vector<int> recoverArray(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for(int i = 1; i < n; i++){
            int d = nums[i] - nums[0];
            //2k大于0,且不为奇数
            if(d == 0 || d % 2 == 1) continue;
            vector<bool> vis(n);//使用vis标记元素是否被使用
            vector<int> ans;
            ans.push_back(nums[0] + d / 2);
            vis[i] = true;
            int l = 1;
            int r = i + 1;
            //寻找满足条件的l,r,nums[r] - nums[l] == 2k
            while(r < n){
                while(l < n && vis[l]){
                    l++;//左指针右移
                }
                while(r < n && nums[r] - nums[l] < d){
                    r++;//右指针右移
                }
                //如果差值大于2k跳出循环
                if(r < n && nums[r] - nums[l] > d) break;
                //匹配成功则标记已经访问
                vis[l] = true;
                vis[r] = true;
                ans.push_back((nums[l] + nums[r]) >> 1);
                //指针右移
                l++;
                r++;
            }
            if(ans.size() == n / 2) return ans;
        }
        return {};
    }
};
```