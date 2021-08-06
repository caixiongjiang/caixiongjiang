## 编号216：组合总和Ⅲ

找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。

说明：

* 所有数字都是正整数。
* 解集不能包含重复的组合。 
示例 1:
```
输入: k = 3, n = 7
输出: [[1,2,4]]
```
示例 2:
```
输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combination-sum-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---

## 思路

这道题目的思路和之前的[77.组合](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode77.md)类似。

本题k相当于了树的深度，9（因为整个集合就是9个数）就是树的宽度。

例如 k = 2，n = 4的话，就是在集合[1,2,3,4,5,6,7,8,9]中求 k（个数） = 2, n（和） = 4的组合。

选取过程如图：
![avater](https://camo.githubusercontent.com/a70514625cc45a5497139d8e13afdb279cd7625584092f92112ff252b7b623e1/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333139353731373937352e706e67)

### 回溯三部曲

* 回溯函数模板返回值以及参数
```java
    List<List<Integer>> result = new ArrayList<>(); 
    LinkedList<Integer> path = new LinkedList<>();
```
接下来还需要如下参数：

</br>1.targetSum（int）目标和，也就是题目中的n。
</br>2.k（int）就是题目中要求k个数的集合。
</br>3.sum（int）为已经收集的元素的总和，也就是path里元素的总和。
</br>4.startIndex（int）为下一层for循环搜索的起始位置。
所以代码如下：
```java
public void backTracking(int targetSum, int k, int startIndex, int sum)
```

* 回溯函数终止条件
如果path.size() 和 k相等了，就终止

如果此时path里收集到的元素和（sum） 和targetSum（就是题目描述的n）相同了，就用result收集当前的结果。
* 回溯搜索的遍历过程

集合固定的就是9个数[1,...,9]，所以for循环固定i<=9
如图：
![avater](https://camo.githubusercontent.com/a70514625cc45a5497139d8e13afdb279cd7625584092f92112ff252b7b623e1/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333139353731373937352e706e67)
处理过程就是 path收集每次选取的元素，相当于树型结构里的边，sum来统计path里元素的总和。



整体代码如下：
```java
class Solution {
    List<List<Integer>> result = new ArrayList<>(); 
    LinkedList<Integer> path = new LinkedList<>();

    public List<List<Integer>> combinationSum3(int k, int n) {
        backTracking(n, k, 1, 0);//初始sum = 0
        return result;
    }

    public void backTracking(int targetSum, int k, int startIndex, int sum){
        //剪枝：如果当前值的总和已经大于所给的targetSum，直接返回
        if(sum > targetSum) return;
        if((path.size() == k) && (sum == targetSum)){
            result.add(new ArrayList<>(path));
            return;
        }
        //剪枝 9 - (k - path.size()) + 1;如果当前元素加上所剩元素的个数小于k，就没必要再遍历
        for(int i = startIndex; i <= 9 - (k - path.size()) + 1; i++){
            path.add(i);
            sum += i;
            backTracking(targetSum, k, i + 1, sum);
            //回溯
            path.removeLast();
            sum -= i;
        }
    }
}
```