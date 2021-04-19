## 编号35：搜索插入位置
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

你可以假设数组中无重复元素。

示例 1:
输入: [1,3,5,6], 5
输出: 2

示例 2:
输入: [1,3,5,6], 2
输出: 1

示例 3:
输入: [1,3,5,6], 7
输出: 4

示例 4:
输入: [1,3,5,6], 0
输出: 0
暴力算法(线性查找)：
```java
    class Solution {
    public int searchInsert(int[] nums, int target) { 
        int i=0;
       for(;i<nums.length;i++){
           if(nums[i]>=target) break;
       }
       return i;
    }
}
```
既然暴力解法的时间复杂度是O(n)，就要尝试一下使用二分查找法。

大家注意这道题目的前提是数组是有序数组，这也是使用二分查找的基础条件。

以后大家*只要看到面试题里给出的数组是有序数组，都可以想一想是否可以使用二分法。*

### 二分算法(写法1)：
```java
class Solution {
    public int searchInsert(int[] nums, int target) { 
        int n=nums.length;
        int left=0;
        int right=n-1;//定义target在左闭右闭的区间里，【left，right】
        while(left<=right){
            int middle=left+((right-left)/2);//防止溢出，等同于(left+right)/2
            if(nums[middle]>target){
                right=middle-1;//target在左区间，所以在【left,middle-1】
            }else if(nums[middle]<target){
                left=middle+1;//target在右区间，所有【middle+1,right】
            }else{//nums[middle]==target
                return middle;
            }
        }
        // 分别处理如下四种情况
        // 目标值在数组所有元素之前  [0, -1]
        // 目标值等于数组中某一个元素  return middle;
        // 目标值插入数组中的位置 [left, right]，return  right + 1
        // 目标值在数组所有元素之后的情况 [left, right]， return right + 1
        return right + 1;
    }
}
```
### 二分算法(写法2)
```java
class Solution {
    public int searchInsert(int[] nums, int target) {
        int n = nums.length;
        int left = 0;
        int right = n; // 定义target在左闭右开的区间里，[left, right)  target
        while (left < right) { // 因为left == right的时候，在[left, right)是无效的空间
            int middle = left + ((right - left)/2);
            if (nums[middle] > target) {
                right = middle; // target 在左区间，在[left, middle)中
            } else if (nums[middle] < target) {
                left = middle + 1; // target 在右区间，在 [middle+1, right)中
            } else { // nums[middle] == target
                return middle; // 数组中找到目标值的情况，直接返回下标
            }
        }
        // 分别处理如下四种情况
        // 目标值在数组所有元素之前 [0,0)
        // 目标值等于数组中某一个元素 return middle
        // 目标值插入数组中的位置 [left, right) ，return right 即可
        // 目标值在数组所有元素之后的情况 [left, right)，return right 即可
        return right;
    }
}
```