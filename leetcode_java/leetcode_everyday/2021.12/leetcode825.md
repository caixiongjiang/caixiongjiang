## 编号825：适龄的朋友

在社交媒体网站上有 n 个用户。给你一个整数数组 ages ，其中 ages[i] 是第 i 个用户的年龄。

如果下述任意一个条件为真，那么用户 x 将不会向用户 y（x != y）发送好友请求：

* age[y] <= 0.5 * age[x] + 7
* age[y] > age[x]
* age[y] > 100 && age[x] < 100
否则，x 将会向 y 发送一条好友请求。

注意，如果 x 向 y 发送一条好友请求，y 不必也向 x 发送一条好友请求。另外，用户不会向自己发送好友请求。

返回在该社交媒体网站上产生的好友请求总数。



示例 1：
```
输入：ages = [16,16]
输出：2
解释：2 人互发好友请求。
```
示例 2：
```
输入：ages = [16,17,18]
输出：2
解释：产生的好友请求为 17 -> 16 ，18 -> 17 。
```
示例 3：
```
输入：ages = [20,30,100,110,120]
输出：3
解释：产生的好友请求为 110 -> 100 ，120 -> 110 ，120 -> 100 。
```

提示：

* n == ages.length
* 1 <= n <= 2 * 10^4
* 1 <= ages[i] <= 120

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/friends-of-appropriate-ages
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

1.排序+查找：

从三个不发送好友请求的条件来看，以 y 的角度来说，可总结为：年龄比我小的不考虑（同龄的可以），年龄比我大可以考虑，但是不能超过一定范围则不考虑。

即对于一个确定的 y 而言，会发送好友请求的 x 范围为连续段：

随着 y 的逐渐增大，对应的 xx 连续段的左右边界均逐渐增大（数轴上均往右移动）。

因此，我们可以先对 ages 进行排序，枚举每个 y=ages[k]，同时使用 i 和 j 维护左右区间，[i, j) 代表在 ages 上会往 y=ages[k] 发送请求的 x 连续段，统计每个 y=ages[k] 的 x 有多少个即是答案，同时需要注意在 [i, j) 范围内是包含y = ages[k] 自身，统计区间长度时需要进行 −1 操作。

2.桶排序：

假设对 ages 进行桶排后得到的数组为 nums，其中 cnt = nums[i] 的含义为在 ages 中年龄为 i 的人有 cnt 个。

同时，我们发现在解法一中，我们枚举 y=ages[k]，并使用 i 和 j 两个指针寻找连续的 x 段的过程，x 会始终停留于值与 y=ages[k] 相等的最小下标处，而对于桶排数组而言，当前位置就是最小合法 x 值（与 y 相等），因此我们只需要找到最大合法 x 值的位置即可（对应解法一的 j 位置）。

同样，最大 x 的位置在桶排数组中也是随着 y 的增大（右移）逐渐增大（右移）。

剩下的问题在于，如何统计桶排数组中连续段下标的和为多少（有多少个合法 x 值），这可以直接在桶排数组应用前缀和即可。


### 排序+二分

代码如下：
```c++
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        sort(ages.begin(), ages.end());
        int n = ages.size();
	int ans = 0;
        for(int i = 0; i < n; i++) {
            int low = upper_bound(ages.begin(), ages.end(), ages[i] / 2 + 7) - ages.begin();
            int high = upper_bound(ages.begin(), ages.end(), ages[i]) - ages.begin();
            if(high > low)
                ans += high - low - 1;
        }
        return ans;
    }
};
```

### 排序+双指针

代码如下：
```c++
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        sort(ages.begin(), ages.end());
        int n = ages.size(); 
	int ans = 0;
        int high = 0, low = 0;
        for(int i = 0; i < n; i++) {
            int a = ages[i]/2 + 7;
            while(low < n && ages[low] <= a) low++;
            while(high < n && ages[high] <= ages[i]) high++;
            if(high > low)
                ans += high - low - 1;
        }
        return ans;
    }
};
```

### 桶排序

代码如下：
```c++
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        int cnt[121], pre[121];
        memset(cnt, 0, sizeof(cnt));
        memset(pre, 0, sizeof(pre));
        for(auto &e:ages) cnt[e]++;
        for(int i = 1; i < 121; ++i) pre[i] = pre[i-1] + cnt[i];
        int ans = 0;
        for(int i = 1; i < 121; ++i) {
            if(cnt[i] == 0) continue;
            int low = i/2 + 7;
            if(low < i) 
                ans += cnt[i] * (pre[i] - pre[low] - 1);
        }
        return ans;
    }
};
```