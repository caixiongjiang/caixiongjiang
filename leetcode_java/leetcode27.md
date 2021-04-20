## 移除元素
给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

 

说明:

为什么返回数值是整数，但输出的答案是数组呢?

请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:
```java
// nums 是以“引用”方式传递的。也就是说，不对实参作任何拷贝
int len = removeElement(nums, val);

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
``` 

示例 1：
```java
输入：nums = [3,2,2,3], val = 3
输出：2, nums = [2,2]
解释：函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。你不需要考虑数组中超出新长度后面的元素。例如，函数返回的新长度为 2 ，而 nums = [2,2,3,3] 或 nums = [2,2,0,0]，也会被视作正确答案。
```
示例 2：
```java 
输入：nums = [0,1,2,2,3,0,4,2], val = 2
输出：5, nums = [0,1,4,0,3]
解释：函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。注意这五个元素可为任意顺序。你不需要考虑数组中超出新长度后面的元素。
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-element
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---

## 思路
有的同学可能说了，多余的元素，删掉不就得了。

<span style="color:pink">*要知道数组的元素在内存地址中是连续的，不能单独删除数组中的某个元素，只能覆盖。*</span>

---
## 暴力解法

![avatar](https://mmbiz.qpic.cn/mmbiz_gif/ciaqDnJprwv4rN7Lc7cH7s9Xs5Gfgibnf7TXGEicwHiav5ChqT6UqgicWib6XRp7TxJva0A6ibrCA6Jx2jAibibWr811pOA/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1)

```java
// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
class Solution {
    public int removeElement(int[] nums, int val) {
        int length=nums.length;
        for(int i=0;i<length;i++){
            if(nums[i]==val){
                for(int j=i+1;j<length;j++){
                    nums[j-1]=nums[j];
                }
                i--;// 因为下表i以后的数值都向前移动了一位，所以i也向前移动一位
                length--;// 此时数组的大小-1
            } 
        }
        return length;
    }
}
```

---
## 双指针法

双指针法（快慢指针法）：「通过一个快指针和慢指针在一个for循环下完成两个for循环的工作。」

删除过程如下：

![avatar](https://mmbiz.qpic.cn/mmbiz_gif/ciaqDnJprwv4rN7Lc7cH7s9Xs5Gfgibnf7kT8a6hE8xVSviaeZHuIqUAx3HRef0dDvg5roSXCIulV2XcjOnxKwYVA/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1)

<span style="color:green">*双指针法（快慢指针法）在数组和链表的操作中是非常常见的，很多考察数组和链表操作的面试题，都使用双指针法。*</span>

我们来回顾一下，之前已经讲过有四道题目使用了双指针法。

双指针法将时间复杂度O(n^2)的解法优化为 O(n)的解法。也就是降一个数量级，题目如下：

</br>15.三数之和
</br>18.四数之和
</br>双指针来记录前后指针实现链表反转：

206.反转链表
</br>使用双指针来确定有环：

142题.环形链表II

```java
// 时间复杂度：O(n)
// 空间复杂度：O(1)
class Solution {
    public int removeElement(int[] nums, int val) {
        int slowIndex = 0; //慢指针
        for (int fastIndex = 0; fastIndex < nums.length; fastIndex++) {   //快指针  
            if (val != nums[fastIndex]) { //不相等就留下，相等时会被后续覆盖
                nums[slowIndex++] = nums[fastIndex]; 
            }
        }
        return slowIndex;
    }
}
```