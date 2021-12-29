## 编号1995:统计特殊四元组

给你一个 下标从 0 开始 的整数数组 nums ，返回满足下述条件的 不同 四元组 (a, b, c, d) 的 数目 ：

* nums[a] + nums[b] + nums[c] == nums[d] ，且
* a < b < c < d
 

示例 1：
```
输入：nums = [1,2,3,6]
输出：1
解释：满足要求的唯一一个四元组是 (0, 1, 2, 3) 因为 1 + 2 + 3 == 6 。
```
示例 2：
```
输入：nums = [3,3,6,4,5]
输出：0
解释：[3,3,6,4,5] 中不存在满足要求的四元组。
```
示例 3：
```
输入：nums = [1,1,1,3,5]
输出：4
解释：满足要求的 4 个四元组如下：
- (0, 1, 2, 3): 1 + 1 + 1 == 3
- (0, 1, 3, 4): 1 + 1 + 3 == 5
- (0, 2, 3, 4): 1 + 1 + 3 == 5
- (1, 2, 3, 4): 1 + 1 + 3 == 5 
```
提示：

* 4 <= nums.length <= 50
* 1 <= nums[i] <= 100


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-special-quadruplets
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路


### 暴力求解

代码如下：
```c++
//暴力
class Solution {
public:
    int countQuadruplets(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for (int a = 0; a < n; ++a) {
            for (int b = a + 1; b < n; ++b) {
                for (int c = b + 1; c < n; ++c) {
                    for (int d = c + 1; d < n; ++d) {
                        if (nums[a] + nums[b] + nums[c] == nums[d]) {
                            ++ans;
                        }
                    }
                }
            }
        }
        return ans;
    }
};
```



### 哈希解法(n^3复杂度)

逆序选定c的值，将d值作为c值右边相邻的数加入unordered_map中,再将a和b固定相邻枚举，在哈希表中查找有没有等于abc之和的d值，有就将结果加1.

代码如下：
```c++
//哈希解法
class Solution {
public:
    int countQuadruplets(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        unordered_map<int, int> cnt;
        for (int c = n - 2; c >= 2; --c) {
            ++cnt[nums[c + 1]];
            for (int a = 0; a < c; ++a) {
                for (int b = a + 1; b < c; ++b) {
                    if (int sum = nums[a] + nums[b] + nums[c]; cnt.count(sum)) {
                        ans += cnt[sum];
                    }
                }
            }
        }
        return ans;
    }
};
```

### 哈希解法（优化为n^2复杂度）

a + b + c = d  移项之后为 a + b = d - c

固定b和c为相邻下标，逆序枚举b，将d在c的右边枚举，将nums[d] - nums[c]的值加入哈希表中，再枚举a在b的左边，如果map中有等于num[a] + nums[b]就将结果的次数加到res中

代码如下：
```c++
class Solution{
public:
    int countQuadruplets(vector<int> &nums){
        unordered_map<int, int> mp;
        int n = nums.size();
        int res = 0;
        for(int b = n - 3; b >= 1; b--){
            int c = b + 1;
            for(int d = b + 2; d < n; d++){
                mp[nums[d] - nums[c]]++;
            }
            for(int a = 0; a < b; a++){
                res += mp[nums[a] + nums[b]];
            }
        }
        return res;
    }
};
```

### 集合

因为对于每一个 d , 相当于是要知道前面的数中 三元组 的 组合和 等于 nums[d] 的个数 , 那么我们在遍历的过程中实时更新 新增的每一个三元组的可能和 就好了。计算 当前三元组的所有可能 只需要在当前的全部两元组中加入当前数 即可 , 计算 两元组 同理

而又因为 nums[d]<=100 , 所以大于 100 的二元组和三元组是可以忽略的（剪枝）



代码如下：
```c++
class Solution {
public:
    int n1[105] = {0};// n1[i] = j 表示一元组中 i 大小 的个数为 j
    int n2[105] = {0};// n2[i] = j 表示二元组中 i 大小 的个数为 j
    int n3[105] = {0};// n3[i] = j 表示三元组中 i 大小 的个数为 j
    unordered_set<int> st1;// 1 个数字的组成
    unordered_set<int> st2;// 2 个数字的组成
    int countQuadruplets(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        for(int i = 0;i < n;i ++) {
            res += n3[nums[i]];
            for(auto& v : st2) {
                if(v + nums[i] < 105)// 因为 nums[d] < 105
                    n3[v + nums[i]] += n2[v];
            } 
            for(auto& v : st1) {
                if(v + nums[i] >= 105) continue;
                if(!n2[v + nums[i]]) st2.insert(v + nums[i]);
                n2[v + nums[i]] += n1[v];
            } 
            if(!n1[nums[i]]) st1.insert(nums[i]);
            n1[nums[i]] ++;
        }
        return res;
    }
};
```