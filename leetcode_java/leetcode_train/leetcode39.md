## 编号39：组合总和

给定一个无重复元素的正整数数组 candidates 和一个正整数 target ，找出 candidates 中所有可以使数字和为目标数 target 的唯一组合。

candidates 中的数字可以无限制重复被选取。如果至少一个所选数字数量不同，则两种组合是唯一的。 

对于给定的输入，保证和为 target 的唯一组合数少于 150 个。

 

示例 1：
```
输入: candidates = [2,3,6,7], target = 7
输出: [[7],[2,2,3]]
```
示例 2：
```
输入: candidates = [2,3,5], target = 8
输出: [[2,2,2,2],[2,3,3],[3,5]]
```
示例 3：
```
输入: candidates = [2], target = 1
输出: []
```
示例 4：
```
输入: candidates = [1], target = 1
输出: [[1]]
```
示例 5：
```
输入: candidates = [1], target = 2
输出: [[1,1]] 
```
提示：

* 1 <= candidates.length <= 30
* 1 <= candidates[i] <= 200
* candidate 中的每个元素都是独一无二的。
* 1 <= target <= 500

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combination-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。\

---
## 思路
**题目中的无限制重复被选取，吓得我赶紧想想 出现0 可咋办**，然后看到下面提示：1 <= candidates[i] <= 200，我就放心了。
本题和[回溯算法：求组合总和！](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode216.md)区别是：本题没有数量要求，可以无限重复，但是有总和的限制，所以间接的也是有个数的限制。
本题搜索的过程抽象成树形结构如下：
![avater](https://camo.githubusercontent.com/4531ac181c876944fb901e9a5b7e5e291dab33265d8a3e83d61500069ab760c2/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313232333137303733303336372e706e67)
因为本题没有组合数量的要求，仅仅是总和的限制，所以递归没有层数的限制，只要选取的元素总和超过target，就返回。

## 回溯三部曲

* 递归函数参数
</br>变量：依然是两个全局变量，二维数组result存放结果集，数组path存放符合条件的结果
</br>参数：1.题目中的参数，集合candidates和目标值target。
</br>     2.此外还需要一个int型变量来统计单一结果path里的总和，其实也可以用target做相应的减法就可以了，若targrt == 0就说明找到了结果。
</br>     3.本题还需要startIndex来控制for循环的起始位置。

<span style="color:green">对于组合问题，什么时候需要startIndex？</span>
</br><span style="color:red">如果是多个集合取组合，各个集合之间相互不影响，那么就不用startIndex;如果是一个集合来求组合的话，就需要用startIndex。</span>
</br>代码如下:

```java
List<List<Integer>> result;
List<Integer> path;
public void backTracking(int[] candidates, int target,int sum, int startIndex)
```
* 递归终止条件
如下树形结构：
![avater](https://camo.githubusercontent.com/4531ac181c876944fb901e9a5b7e5e291dab33265d8a3e83d61500069ab760c2/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313232333137303733303336372e706e67)
从图中可知：只有两种情况
```java
if(sum > target) return;
if(sum == target){
    result.add(new ArrayList<>(path));
    return;
}
```
* 单层搜索的逻辑
单层for循环依然是从startIndex开始，搜索candidates集合
```java
for (int i = startIndex; i < candidates.length; i++) {
    sum += candidates[i];
    path.add(candidates[i]);
    backtracking(candidates, target, sum, i); // 关键点:不用i+1了，表示可以重复读取当前的数
    sum -= candidates[i];   // 回溯
    path.removeLast();        // 回溯
}
```

整体代码如下：
```java
class Solution {
    List<List<Integer>> result = new ArrayList<>();
    LinkedList<Integer> path = new LinkedList<>(); 
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        backTracking(candidates, target, 0, 0);
        return result;
    }

    public void backTracking(int[] candidates, int target,int sum, int startIndex){
        if(sum > target) return;
        if(sum == target){
            result.add(new ArrayList<>(path));
            return;
        }
        for(int i = startIndex; i < candidates.length; i++){
            sum += candidates[i];
            path.add(candidates[i]);
            backTracking(candidates, target, sum, i);
            sum -= candidates[i];
            path.removeLast();
        }
    }
}
```

## 剪枝优化
**在递归的过程中，如果已经知道下一层的sum会大于target，就没有必要进入下一层递归了。**
那么就可以修改for循环的代码部分。
对总集合排序之后，如果下一层的sum（就是本层的 sum + candidates[i]）已经大于target，就可以结束本轮for循环的遍历。

如图：

![avater](https://camo.githubusercontent.com/1671c386e32647289cf3d957fc1143eacc031bd5f2fdda1af36e9d7d9c6c8784/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313232333137303830393138322e706e67)

***可以看到这种情况只存在于数组中的元素递增的情况，所以剪枝优化首先要对candidates的数组进行排序***
for循环剪枝代码如下：
```java
for(int i = startIndex; i < candidates.length && sum + candidates[i] <= target; i++)
```

优化后的整体代码如下：
```java
class Solution {
    List<List<Integer>> result = new ArrayList<>();
    LinkedList<Integer> path = new LinkedList<>(); 
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        Arrays.sort(candidates);//配合剪枝进行排序
        backTracking(candidates, target, 0, 0);
        return result;
    }

    public void backTracking(int[] candidates, int target,int sum, int startIndex){
        if(sum > target) return;
        if(sum == target){
            result.add(new ArrayList<>(path));
            return;
        }
        //剪枝优化：sum + candidates[i]的结果如果大于target就没有进行下一步了
        for(int i = startIndex; i < candidates.length && sum + candidates[i] <= target; i++){
            sum += candidates[i];
            path.add(candidates[i]);
            backTracking(candidates, target, sum, i);
            sum -= candidates[i];
            path.removeLast();
        }
    }
}
```

优化后超过了99%的用户的性能。
