## 编号1365：有多少小于当前数字的数字

给你一个数组 nums，对于其中每个元素 nums[i]，请你统计数组中比它小的所有数字的数目。

换而言之，对于每个 nums[i] 你必须计算出有效的 j 的数量，其中 j 满足 j != i 且 nums[j] < nums[i] 。

以数组形式返回答案。

 

示例 1：
```
输入：nums = [8,1,2,2,3]
输出：[4,0,1,1,3]
解释： 
对于 nums[0]=8 存在四个比它小的数字：（1，2，2 和 3）。 
对于 nums[1]=1 不存在比它小的数字。
对于 nums[2]=2 存在一个比它小的数字：（1）。 
对于 nums[3]=2 存在一个比它小的数字：（1）。 
对于 nums[4]=3 存在三个比它小的数字：（1，2 和 2）。
```

示例 2：
```
输入：nums = [6,5,4,8]
输出：[2,1,0,3]
```

示例 3：
```
输入：nums = [7,7,7,7]
输出：[0,0,0,0] 
```
提示：

* 2 <= nums.length <= 500
* 0 <= nums[i] <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/how-many-numbers-are-smaller-than-the-current-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
两层for循环暴力查找，时间复杂度明显为O(n^2)

可以重新定义一个新数组，将数组排个序

**排序之后，其实每一个数值的下标就代表这前面有几个比它小的了。**

代码如下：
```c++
vector<int> vec = nums;
sort(vec.begin(), vec.end()); // 从小到大排序之后，元素下标就是小于当前数字的数字
```

用一个哈希表hash（本题可以就用一个数组）来做数值和下标的映射。这样就可以通过数值快速知道下标（也就是前面有几个比它小的）。

此时有一个情况，就是数值相同怎么办？

例如，数组：1 2 3 4 4 4 ，第一个数值4的下标是3，第二个数值4的下标是4了。

这里就需要一个技巧了，**在构造数组hash的时候，从后向前遍历，这样hash里存放的就是相同元素最左面的数值和下标了。** 代码如下：
```c++
int hash[101];
for (int i = vec.size() - 1; i >= 0; i--) { // 从后向前，记录 vec[i] 对应的下标
    hash[vec[i]] = i;
}
```
最后在遍历原数组nums，用hash快速找到每一个数值 对应的 小于这个数值的个数。存放在将结果存放在另一个数组中。

代码如下：
```c++
// 此时hash里保存的每一个元素数值 对应的 小于这个数值的个数
for (int i = 0; i < nums.size(); i++) {
    vec[i] = hash[nums[i]];
}
```
流程如图：

![avater](https://camo.githubusercontent.com/c42f0afce225e30ab355c28fbbe6b4343162288be28dc683e81293a3815fb615/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f313336352ee69c89e5a49ae5b091e5b08fe4ba8ee5bd93e5898de695b0e5ad97e79a84e695b0e5ad972e706e67)


整体代码如下：
```c++
class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<int> vec = nums;
        sort(vec.begin(), vec.end());//从小到大排序之后，元素下标就是小于当前数字的数字
        int hash[101];
        for(int i = vec.size() - 1; i >= 0; i--){
            hash[vec[i]] = i;
        }
        //此时哈希表里保存的每一个元素数值对应的小于这个数数值的个数
        for(int i = 0; i < nums.size(); i++){
            vec[i] = hash[nums[i]];
        }
        return vec;
    }
};
```