## 编号78：子集
给你一个整数数组 nums ，数组中的元素 **互不相同** 。返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。你可以按**任意顺序**返回解集。

 

示例 1：
```
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```
示例 2：
```
输入：nums = [0]
输出：[[],[0]]
```
提示：

* 1 <= nums.length <= 10
* -10 <= nums[i] <= 10
* nums 中的所有元素 互不相同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/subsets
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
如果把 子集问题、组合问题、分割问题都抽象为一棵树的话，**那么组合问题和分割问题都是收集树的叶子节点，而子集问题是找树的所有节点！**

其实子集也是一种组合问题，因为它的集合是无序的，子集{1,2} 和 子集{2,1}是一样的。

**那么既然是无序，取过的元素不会重复取，写回溯算法的时候，for就要从startIndex开始，而不是从0开始！**
求排列问题的时候，就要从0开始，因为集合是有序的，{1, 2} 和{2, 1}是两个集合，排列问题我们后续的文章就会讲到的。

以示例中nums = [1,2,3]为例把求子集抽象为树型结构，如下：
![avater](https://camo.githubusercontent.com/3f67c171ede9807a17fdeaf91ac87e7813516ad272a3c4ac55ee292514ff2acf/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f3230323031313233323034313334382e706e67)
从图中红线部分，可以看出**遍历这个树的时候，把所有节点都记录下来，就是要求的子集集合。**

## 回溯三部曲

此题整体比较简单，不需要进行剪枝优化和其他操作，直接给出代码。
整体代码如下：
```java
class Solution {
    List<List<Integer>> result = new ArrayList<>();
    LinkedList<Integer> path = new LinkedList<>();
    
    public List<List<Integer>> subsets(int[] nums) {
        if(nums.length == 0){
            result.add(new ArrayList<>());
            return result;
        }
        backTracking(nums, 0);
        return result;
    }

    public void backTracking(int[] nums, int startIndex){
        //将path记录的节点都计入result中
        result.add(new ArrayList<>(path));
        //剩余集合为空的时候
        if(startIndex >= nums.length) return;
        for(int i = startIndex; i < nums.length; i++){
            path.add(nums[i]);
            backTracking(nums, i + 1);
            path.removeLast();
        }
    }
}
```