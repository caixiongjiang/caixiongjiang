## 编号491：递增子序列、
给你一个整数数组 nums ，找出并返回所有该数组中不同的递增子序列，递增子序列中 **至少有两个元素** 。你可以按 **任意顺序** 返回答案。

数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。

 

示例 1：
```
输入：nums = [4,6,7,7]
输出：[[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
```
示例 2：
```
输入：nums = [4,4,3,2,1]
输出：[[4,4]]
```
提示：

* 1 <= nums.length <= 15
* -100 <= nums[i] <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/increasing-subsequences
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
这个递增子序列比较像是取有序的子集。而且本题也要求不能有相同的递增子序列。

这又是子集，又是去重。在回溯算法：求[子集问题（二）](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode90.md)中我们是通过排序，再加一个标记数组来达到去重的目的。
本题求自增子序列，是不能对原数组经行排序的，排完序的数组都是自增子序列了。

**所以不能使用之前的去重逻辑！**
本题给出的示例，还是一个有序数组 [4, 6, 7, 7]，这更容易误导大家按照排序的思路去做了。

为了有鲜明的对比，我用[4, 7, 6, 7]这个数组来举例，抽象为树形结构如图：
![avater](https://camo.githubusercontent.com/b7284140cb1fc0fb3975b57b315035795c29f13f48fd1a1cd28c6bfad89ded68/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132343230303232393832342e706e67)
## 回溯三部曲

* 递归函数参数
代码如下：
```java
List<List<Integer>> result;
List<Integer> path;
public void backTracking(int[] nums, int startIndex)
```

* 终止条件
本题与求子集问题类似，也是要遍历树形结构找到每一个节点，所以可以不加终止条件，startIndex每次都会加1，并不会无限递归。
</br>但本题收集结果有所不同，题目要求递增子序列大小至少为2，所以代码如下：

```java
if (path.size() > 1) {
    result.add(path);
    // 注意这里不要加return，因为要取树上的所有节点
}
```

* 单层搜索逻辑
![avater](https://camo.githubusercontent.com/b7284140cb1fc0fb3975b57b315035795c29f13f48fd1a1cd28c6bfad89ded68/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132343230303232393832342e706e67)
在图中可以看出，同一父节点下的同层上使用过的元素就不能在使用了

那么单层搜索代码如下：

```java
int[] used = new int[201];
for(int i = startIndex; i < nums.length; i++){
    //这里使用nums[i] + 100是为了防止nums[i]的值在-100到0之间。
    if(!path.isEmpty() && nums[i] < path.get(path.size() - 1) || (used[nums[i] + 100] == 1)){
        continue;
    }
    used[nums[i] + 100] = 1;//记录这个元素在本层用过了，本层后面不能再用了
    path.add(nums[i]);
    backTracking(nums, i + 1);
    path.remove(path.size() - 1);
} 
```
</br><span style="color:green">整体代码如下：</span>

```java
class Solution {
    List<List<Integer>> result = new ArrayList<>();
    List<Integer> path = new ArrayList<>();

    public List<List<Integer>> findSubsequences(int[] nums) {
        backTracking(nums, 0);
        return result;
    }

    public void backTracking(int[] nums, int startIndex){
        if(path.size() > 1){
            result.add(new ArrayList<>(path));
            //注意这里不要return,因为要取树上的所有节点
        }

        int[] used = new int[201];
        for(int i = startIndex; i < nums.length; i++){
            //这里使用nums[i] + 100是为了防止nums[i]的值在-100到0之间。
            if(!path.isEmpty() && nums[i] < path.get(path.size() - 1) || (used[nums[i] + 100] == 1)){
                continue;
            }
            used[nums[i] + 100] = 1;//记录这个元素在本层用过了，本层后面不能再用了
            path.add(nums[i]);
            backTracking(nums, i + 1);
            path.remove(path.size() - 1);
        } 
    }
}
```