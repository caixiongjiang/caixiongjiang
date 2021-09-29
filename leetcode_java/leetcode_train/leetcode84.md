## 编号84：柱状图中最大的矩形

给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

 

示例 1:

![avater](https://assets.leetcode.com/uploads/2021/01/04/histogram.jpg)

```
输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/01/04/histogram-1.jpg)

```
输入： heights = [2,4]
输出： 4 
```
提示：

* 1 <= heights.length <=105
* 0 <= heights[i] <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/largest-rectangle-in-histogram
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

本题的思路和[42.接雨水](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode42.md)很相似。

## 双指针法

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int sum = 0;
        for(int i = 0; i < heights.size(); i++){
            int left = i;
            int right = i;
            //柱子左边如果更低就跳出，无法再加宽
            for(; left >= 0; left--){
                if(heights[left] < heights[i]) break;
            }
            //柱子右边如果更低就跳出，无法再加宽
            for(; right < heights.size(); right++){
                if(heights[right] < heights[i]) break;
            }
            int w = right - left - 1;
            int h = heights[i];
            sum = max(sum, w * h);
        }
        return sum;
    }
};
```

同样是超出时间限制。

## 动态规划

**本题要记录每个柱子左边第一个小于该柱子的下标，而不是左边第一个小于该柱子的高度。**

所以需要循环查找。

代码如下：
```c++
class Solution{
public:
    int largestRectangleArea(vector<int>& heights){
        vector<int> minLeftIndex(heights.size());
        vector<int> minRightIndex(heights.size());
        int size = heights.size();

        //记录每个柱子的左边第一个小于该柱子的下标
        minLeftIndex[0] = -1;//初始化，防止下面死循环
        for(int i = 1; i < size; i++){
            int t = i - 1;
            //这里不是用if，是不断向左寻找的过程
            while(t >= 0 && heights[t] >= heights[i]) t = minLeftIndex[t];
            minLeftIndex[i] = t;
        }
        //记录每个柱子的右边第一个小于该柱子的下标
        minRightIndex[size - 1] = size;//注意这里初始化，防止下面while死循环
        for(int i = size - 2; i >= 0; i--){
            int t = i + 1;
            //这里不是用if,而是不断向右寻找的过程
            while(t < size && heights[t] >= heights[i]) t = minRightIndex[t];
            minRightIndex[i] = t;
        }
        //求和
        int result = 0;
        for(int i = 0; i < size; i++){
            int sum = heights[i] * (minRightIndex[i] - minLeftIndex[i] - 1);
            result = max(sum, result);
        }
        return result;
    }
};
```

## 单调栈

本地单调栈的解法和接雨水的题目是遥相呼应的。

为什么这么说呢，**[42. 接雨水](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode42.md)是找每个柱子左右两边第一个大于该柱子高度的柱子，而本题是找每个柱子左右两边第一个小于该柱子的柱子。**

**这里就涉及到了单调栈很重要的性质，就是单调栈里的顺序，是从小到大还是从大到小。**

在[题解42. 接雨水](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode42.md)中接雨水的单调栈从栈头（元素从栈头弹出）到栈底的顺序应该是从小到大的顺序。

那么因为本题是要找每个柱子左右两边第一个小于该柱子的柱子，**所以从栈头（元素从栈头弹出）到栈底的顺序应该是从大到小的顺序！**

我来举一个例子，如图：
![avater](https://camo.githubusercontent.com/982732321ae13eb943dbbd0f06b994dce1a46e706c9be9d6693b181c19ff5666/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303232333135353330333937312e6a7067)

只有栈里从大到小的顺序，才能保证栈顶元素找到左右两边第一个小于栈顶元素的柱子。

所以本题单调栈的顺序正好与接雨水反过来。

此时大家应该可以发现其实就是**栈顶和栈顶的下一个元素以及要入栈的三个元素组成了我们要求最大面积的高度和宽度**

理解这一点，对单调栈就掌握的比较到位了。

剩下就是分析清楚如下三种情况：
* 情况一：当前遍历的元素heights[i]小于栈顶元素heights[st.top()]的情况
* 情况二：当前遍历的元素heights[i]等于栈顶元素heights[st.top()]的情况
* 情况三：当前遍历的元素heights[i]大于栈顶元素heights[st.top()]的情况

c++整体代码如下：
```c++
// 版本一
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        heights.insert(heights.begin(), 0); // 数组头部加入元素0
        heights.push_back(0); // 数组尾部加入元素0
        st.push(0);
        int result = 0;
        // 第一个元素已经入栈，从下表1开始
        for (int i = 1; i < heights.size(); i++) {
            // 注意heights[i] 是和heights[st.top()] 比较 ，st.top()是下表
            if (heights[i] > heights[st.top()]) {
                st.push(i);
            } else if (heights[i] == heights[st.top()]) {
                st.pop(); // 这个可以加，可以不加，效果一样，思路不同
                st.push(i);
            } else {
                while (heights[i] < heights[st.top()]) { // 注意是while
                    int mid = st.top();
                    st.pop();
                    int left = st.top();
                    int right = i;
                    int w = right - left - 1;
                    int h = heights[mid];
                    result = max(result, w * h);
                }
                st.push(i);
            }
        }
        return result;
    }
};
```

精简代码如下：
```c++
// 版本二
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        heights.insert(heights.begin(), 0); // 数组头部加入元素0
        heights.push_back(0); // 数组尾部加入元素0
        st.push(0);
        int result = 0;
        for (int i = 1; i < heights.size(); i++) {
            while (heights[i] < heights[st.top()]) {
                int mid = st.top();
                st.pop();
                int w = i - st.top() - 1;
                int h = heights[mid];
                result = max(result, w * h);
            }
            st.push(i);
        }
        return result;
    }
};
```