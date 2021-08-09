## 编号46：全排列
给定一个不含重复数字的数组 nums ，返回其 **所有可能的全排列** 。你可以 **按任意顺序** 返回答案。

 

示例 1：
```
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```
示例 2：
```
输入：nums = [0,1]
输出：[[0,1],[1,0]]
```
示例 3：
```
输入：nums = [1]
输出：[[1]] 
```
提示：

* 1 <= nums.length <= 6
* -10 <= nums[i] <= 10
* nums 中的所有整数 互不相同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/permutations
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

我以[1,2,3]为例，抽象成树形结构如下：
![avater](https://camo.githubusercontent.com/e98da84da1c29c70e57d0a0f5f2aac727c0f2662c49f7ea78ff295dabdd70aa5/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313230393137343232353134352e706e67)

## 回溯三部曲
* 递归函数参数
<span style="color:green">首先排列是有序的，也就是说[1,2] 和[2,1] 是两个集合，这和之前分析的子集以及组合所不同的地方。</span>

可以看出元素1在[1,2]中已经使用过了，但是在[2,1]中还要在使用一次1，所以处理排列问题就不用使用startIndex了。

但排列问题需要一个used数组，标记已经选择的元素，如图橘黄色部分所示:
![avater](https://camo.githubusercontent.com/e98da84da1c29c70e57d0a0f5f2aac727c0f2662c49f7ea78ff295dabdd70aa5/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313230393137343232353134352e706e67)
代码如下：
```java
List<List<Integer>> result;
LinkedList<Integer> path;
public void backTracking(int[] nums)
```
* 递归终止条件
可以看出叶子节点，就是收割结果的地方。

那么什么时候，算是到达叶子节点呢？

当收集元素的数组path的大小达到和nums数组一样大的时候，说明找到了一个全排列，也表示到达了叶子节点。

代码如下：
```java
// 此时说明找到了一组
if (path.size() == nums.length) {
    result.add(new ArrayList<>(path));
    return;
}
```

* 单层搜索的逻辑
这里和[77.组合问题](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode77.md)、[131.切割问题](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode131.md)和[78.子集问题](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode78.md)最大的不同就是for循环里不用startIndex了。

因为排列问题，每次都要从头开始搜索，例如元素1在[1,2]中已经使用过了，但是在[2,1]中还要再使用一次1。

**而used数组，其实就是记录此时path里都有哪些元素使用了，一个排列里一个元素只能使用一次。**

代码如下：
```java
for(int i = 0; i < nums.length; i++){
    if(used[i]) continue;
    used[i] = true;
    path.add(nums[i]);
    backTracking(nums);
    path.removeLast();
    used[i] = false;
}
```



整体代码如下：
```java
class Solution {
    List<List<Integer>> result = new ArrayList<>();
    LinkedList<Integer> path = new LinkedList<>();
    boolean[] used;
    public List<List<Integer>> permute(int[] nums) {
        if(nums.length == 0) return result;
        used = new boolean[nums.length];
        backTracking(nums);
        return result;
    }

    public void backTracking(int[] nums){
        if(path.size() == nums.length){
            result.add(new ArrayList<>(path));
            return;
        }
        for(int i = 0; i < nums.length; i++){
            if(used[i]) continue;
            used[i] = true;
            path.add(nums[i]);
            backTracking(nums);
            path.removeLast();
            used[i] = false;
        }
    }
}
```