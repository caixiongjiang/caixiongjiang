## 编号454：四数相加Ⅱ

给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n ，请你计算有多少个元组 (i, j, k, l) 能满足：

* 0 <= i, j, k, l < n
* nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
 

示例 1：
```
输入：nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
输出：2
解释：
两个元组如下：
1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0
```
示例 2：
```
输入：nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
输出：1
```
提示：

* n == nums1.length
* n == nums2.length
* n == nums3.length
* n == nums4.length
* 1 <= n <= 200
* -228 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 228

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/4sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路


代码如下：
```c++
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> map;//key:a+b的值，value:a+b数值出现的次数
        //遍历A数组和B数组，统计两个数组元素之和，和出现的次数，放到map中
        for(int a : A){
            for(int b : B){
                map[a + b]++;
            }
        }
        int count = 0;//统计a+b+c+d = 0 出现的次数
        //在遍历C数组和D数组，找到如果0-(c+d)在map中出现过的话，就把map中的key对应的value统计出来
        for(int c : C){
            for(int d : D){
                if(map.find(0 - (c + d)) != map.end()){
                    count += map[0 - (c + d)];
                }
            }
        }
        return count;
    }
};
```