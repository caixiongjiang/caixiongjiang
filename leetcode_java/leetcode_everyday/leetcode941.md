## 编号941：有效的山脉数组

给定一个整数数组 arr，如果它是有效的山脉数组就返回 true，否则返回 false。

让我们回顾一下，如果 A 满足下述条件，那么它是一个山脉数组：

* arr.length >= 3
* 在 0 < i < arr.length - 1 条件下，存在 i 使得：
</br>&emsp;arr[0] < arr[1] < ... arr[i-1] < arr[i]
</br>&emsp;arr[i] > arr[i+1] > ... > arr[arr.length - 1]
 

![avater](https://assets.leetcode.com/uploads/2019/10/20/hint_valid_mountain_array.png)


 

示例 1：
```
输入：arr = [2,1]
输出：false
```

示例 2：
```
输入：arr = [3,5,5]
输出：false
```

示例 3：
```
输入：arr = [0,3,2,1]
输出：true 
```
提示：

* 1 <= arr.length <= 104
* 0 <= arr[i] <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-mountain-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

判断是山峰，主要就是要严格的保存左边到中间，和右边到中间是递增的。

这样可以使用两个指针，left和right，让其按照如下规则移动，如图：

![avater](https://camo.githubusercontent.com/b71d86d1575a8cdcb4795f8c5df05aa637a8b9f4353551bab4b1c42ab3154e68/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3934312ee69c89e69588e79a84e5b1b1e88489e695b0e7bb842e706e67)

注意这里还是有一些细节，例如如下两点：

* 因为left和right是数组下表，移动的过程中注意不要数组越界
* 如果left或者right没有移动，说明是一个单调递增或者递减的数组，依然不是山峰

C++代码如下：
```c++

```