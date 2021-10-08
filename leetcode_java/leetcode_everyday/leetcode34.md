## 编号34：在排序数组中查找元素的第一个和最后一个位置

给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。

**进阶**：

* 你可以设计并实现时间复杂度为 O(log n) 的算法解决此问题吗？
 

示例 1：
```
输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]
```
示例 2：
```
输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]
```
示例 3：
```
输入：nums = [], target = 0
输出：[-1,-1] 
```
提示：

* 0 <= nums.length <= 105
* -109 <= nums[i] <= 109
* nums 是一个非递减数组
* -109 <= target <= 109

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

寻找target在数组里的左右边界，有如下三种情况：

* 情况一：target 在数组范围的右边或者左边，例如数组{3, 4, 5}，target为2或者数组{3, 4, 5},target为6，此时应该返回{-1, -1}
* 情况二：target 在数组范围中，且数组中不存在target，例如数组{3,6,7},target为5，此时应该返回{-1, -1}
* 情况三：target 在数组范围中，且数组中存在target，例如数组{3,6,7},target为6，此时应该返回{1, 1}
这三种情况都考虑到，说明就想的很清楚了。

接下来，在去寻找左边界，和右边界了。

采用二分法来去寻找左右边界，为了让代码清晰，我分别写两个二分来寻找左边界和右边界。

**刚刚接触二分搜索的同学不建议上来就像如果用一个二分来查找左右边界，很容易把自己绕进去，建议扎扎实实的写两个二分分别找左边界和右边界**

## 处理三种情况

整体代码如下：
```c++
//左闭右闭的版本
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int leftBorder = getLeftBorder(nums, target);
        int rightBorder = getRightBorder(nums, target);
        //情况一
        if(leftBorder == -2 || rightBorder == -2) return {-1, -1};
        //情况三
        if(rightBorder - leftBorder > 1) return {leftBorder + 1, rightBorder - 1};
        //情况二
        return {-1, -1};
    }

private:
    int getRightBorder(vector<int>& nums, int target){
        int left = 0;
        int right = nums.size() - 1;
        int rightBorder = -2; //记录一下rightBorder没有被赋值的情况
        while(left <= right){
            int mid = left + ((right - left) / 2);
            if(nums[mid] > target){
                right = mid - 1;
            }else{  //寻找右边界，nums[mid] == target的时候更新left
                left = mid + 1;
                rightBorder = left;
            } 
        }
        return rightBorder;
    }

    int getLeftBorder(vector<int>& nums, int target){
        int left = 0;
        int right = nums.size() - 1;
        int leftBorder = -2;  //记录一下leftBorder没有被赋值的情况
        while(left <= right){
            int mid = left + ((right - left) / 2);
            if(nums[mid] >= target){ //寻找左边界，nums[mid] == target的时候更新right
                right = mid - 1;
                leftBorder = right;
            }else{
                left = mid + 1;
            }
        }
        return leftBorder;
    }
};
```