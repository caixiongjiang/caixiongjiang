## 编号268：丢失的数字

给定一个包含 [0, n] 中 n 个数的数组 nums ，找出 [0, n] 这个范围内没有出现在数组中的那个数。

 

示例 1：
```
输入：nums = [3,0,1]
输出：2
解释：n = 3，因为有 3 个数字，所以所有的数字都在范围 [0,3] 内。2 是丢失的数字，因为它没有出现在 nums 中。
```
示例 2：
```
输入：nums = [0,1]
输出：2
解释：n = 2，因为有 2 个数字，所以所有的数字都在范围 [0,2] 内。2 是丢失的数字，因为它没有出现在 nums 中。
```
示例 3：
```
输入：nums = [9,6,4,2,3,5,7,0,1]
输出：8
解释：n = 9，因为有 9 个数字，所以所有的数字都在范围 [0,9] 内。8 是丢失的数字，因为它没有出现在 nums 中。
```
示例 4：
```
输入：nums = [0]
输出：1
解释：n = 1，因为有 1 个数字，所以所有的数字都在范围 [0,1] 内。1 是丢失的数字，因为它没有出现在 nums 中。 
```
提示：

* n == nums.length
* 1 <= n <= 104
* 0 <= nums[i] <= n
* nums 中的所有数字都 独一无二

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/missing-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 排序
首先上我自己写的代码

我用的是排序的思路

代码如下：
```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] != i) {
                return i;
            }
        }
        return n;
    }
};
```

### 哈希集合

使用哈希集合，可以将时间复杂度降低到O(n)。

首先遍历数组nums，将数组中的每个元素加入哈希集合，然后依次检查从 0 到 n 的每个整数是否在哈希集合中，不在哈希集合中的数字即为丢失的数字。由于哈希集合的每次添加元素和查找元素的时间复杂度都是O(1)，因此总时间复杂度是O(n)。

代码如下：
```c++
class Solution{
public: 
    int missingNumber(vector<int>& nums){
        unordered_set<int> set;
        int n = nums.size();
        for(int i = 0; i < n; i++){
            set.insert(nums[i]);
        }
        int missing = -1;
        for(int i = 0; i <= n; i++){
            if(!set.count(i)){
                missing = i;
                break;
            }
        }
        return missing;
    }
};
```


### 位运算

数组nums中有n个数，在这n个数的后面添加从0到n的每个整数，则添加了n+1个整数，共有2n+1个整数。

在2n+1个整数中，丢失的数字只在后面n+1个整数中出现一次，其余的数字在前面n个整数中（即数组中）和后面n+1个整数中各出现一次，即其余的数字都出现了两次。

根据出现的次数的奇偶性，可以使用按位异或运算得到丢失的数字。按位异或运算⊕满足交换律和结合律，且对任意整数 x 都满足x⊕x=0和x⊕0=x。

由于上述2n+1个整数中，丢失的数字出现了一次，其余的数字都出现了两次，因此对上述2n+1个整数进行按位异或运算，结果即为丢失的数字。

代码如下：
```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            res ^= nums[i];
        }
        for (int i = 0; i <= n; i++) {
            res ^= i;
        }
        return res;
    }
};
```


### 数学方法

将从 0 到 n 的全部整数之和记为total，根据高斯求和公式，有：

$$total=\sum_{i=0}^n = \frac {n(n+1)}{2}$$

将数组$nums$的元素之和记为$arrSum$，则$arrSum$比$total$少了丢失的一个数字，因此丢失的数字即为$total$与$arrSum$之差。




代码如下：
```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int total = n * (n + 1) / 2;
        int arrSum = 0;
        for (int i = 0; i < n; i++) {
            arrSum += nums[i];
        }
        return total - arrSum;
    }
};
```