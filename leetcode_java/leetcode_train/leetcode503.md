## 编号503：下一个更大的元素Ⅱ

给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。数字 x 的下一个更大的元素是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1。

示例 1:
```
输入: [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；
数字 2 找不到下一个更大的数； 
第二个 1 的下一个最大的数需要循环搜索，结果也是 2。
```
**注意**: 输入数组的长度不会超过 10000。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/next-greater-element-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

本篇我侧重与说一说，如何处理循环数组。

相信不少同学看到这道题，就想那我直接把两个数组拼接在一起，然后使用单调栈求下一个最大值不就行了！

确实可以！

讲两个nums数组拼接在一起，使用单调栈计算出每一个元素的下一个最大值，最后再把结果集即result数组resize到原数组大小就可以了。

代码如下：
```c++
// 版本一
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        // 拼接一个新的nums
        vector<int> nums1(nums.begin(), nums.end());
        nums.insert(nums.end(), nums1.begin(), nums1.end());
        // 用新的nums大小来初始化result
        vector<int> result(nums.size(), -1);
        if (nums.size() == 0) return result;

        // 开始单调栈
        stack<int> st;
        for (int i = 0; i < nums.size(); i++) {
            while (!st.empty() && nums[i] > nums[st.top()]) {
                result[st.top()] = nums[i];
                st.pop();
            }
            st.push(i);
        }
        // 最后再把结果集即result数组resize到原数组大小
        result.resize(nums.size() / 2);
        return result;
    }
};
```

这种写法确实比较直观，但做了很多无用操作，例如修改了nums数组，而且最后还要把result数组resize回去。

resize倒是不费时间，是O(1)的操作，但扩充nums数组相当于多了一个O(n)的操作。

**其实也可以不扩充nums，而是在遍历的过程中模拟走了两边nums。**

整体代码如下：
```c++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> result(nums.size(), -1);
        if(nums.size() == 0) return result;
        stack<int> st;
        for(int i = 0; i < nums.size() * 2; i++){
            //模拟遍历两遍nums，注意都用i % nums.size()来操作
            while(!st.empty() && nums[i % nums.size()] > nums[st.top()]){
                result[st.top()] = nums[i % nums.size()];
                st.pop();
            }
            st.push(i % nums.size());
        }
        return result;
    }
};
```

