## 编号283：移动零

给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:
```
输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
```
说明:

* 必须在原数组上操作，不能拷贝额外的数组。
* 尽量减少操作次数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/move-zeroes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

**对整个数组移除元素0，然后slowIndex之后都是移除元素0的冗余元素，把这些元素都赋值为0就可以了。**

如动画所示：
![avater](https://camo.githubusercontent.com/7b62ae10084227149e190a11a0c24753cdf8dfea90de434b9760537cb6e98912/68747470733a2f2f747661312e73696e61696d672e636e2f6c617267652f65366339643234656c7931676f6a646c72767171696732306a633064616b6a6e2e676966)

c++代码如下：
```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slowIndex = 0;
        for(int fastIndex = 0; fastIndex < nums.size(); fastIndex++){
            if(nums[fastIndex] != 0){
                nums[slowIndex++] = nums[fastIndex]; 
            }
        }
        //将slowIndex之后的荣誉元素赋值为0
        for(int i = slowIndex; i < nums.size(); i++){
            nums[i] = 0;
        }
    }
};
```