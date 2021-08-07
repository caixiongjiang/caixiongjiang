## 编号40：组合总和Ⅱ
给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

注意：解集不能包含重复的组合。 

 

示例 1:
```
输入: candidates = [10,1,2,7,6,1,5], target = 8,
输出:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
```
示例 2:
```
输入: candidates = [2,5,2,1,2], target = 5,
输出:
[
[1,2,2],
[5]
] 
```
提示:

* 1 <= candidates.length <= 100
* 1 <= candidates[i] <= 50
* 1 <= target <= 30

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combination-sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
这道题与[39.组合总和（二）](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode39.md)只相差两个条件：
</br>1.就是要求每个数字在每个组合中只能使用一次
</br>2.数组candidates的元素是有重复的，而[39题](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode39.md)
</br>**本题的核心在于集合（数组candidates）有重复元素，但还不能有重复的组合。**
所以要在搜索的过程中就去掉重复组合。


这个去重为什么很难理解呢，所谓去重，**其实就是使用过的元素不能重复选取。**

都知道组合问题可以抽象为树形结构，那么“使用过”在这个树形结构上是有两个维度的，一个维度是同一树枝上使用过，一个维度是同一树层上使用过。**没有理解这两个层面上的“使用过” 是造成没有彻底理解去重的根本原因。**

回看一下题目，元素在同一个组合内是可以重复的，怎么重复都没事，但两个组合不能相同。

所以我们要去重的是同一树层上的“使用过”，同一树枝上的都是一个组合里的元素，不用去重。

为了理解去重,举一个例子，candidates = [1, 1, 2], target = 3，（方便起见candidates已经排序了）

<span style="color:green">强调一下，树层去重的话，需要对数组排序！</span>

选择过程树形结构如图所示：
![avater](https://camo.githubusercontent.com/3e488c39460e69b34dc80f13189fb69b4c2dfeca214a4570f6eacc19e374b1e6/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333230323733363338342e706e67)
可以看到在本体中多加了一个used数组。

## 回溯三部曲
* 递归函数参数
</br>这道题还需要增加一个bool型的数组used，用来记录同一树枝上的元素是否使用果。
</br>代码如下：
```java
List<List<Integer>> result;
LinkedList<Integer> path;
public void backTracking(int[] candidates, int target, int sum, int startIndex)
```
* 递归终止条件
与[39题](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode39.md)相同，不再赘述。

* 单层搜索的逻辑
要去重的是“同一树层上的使用过”，如果判断同一树层上元素（相同的元素）是否使用过了呢。

如果candidates[i] == candidates[i - 1] 并且 used[i - 1] == false，就说明：前一个树枝，使用了candidates[i - 1]，也就是说同一树层使用过candidates[i - 1]。

此时for循环里就应该做continue的操作。

这块比较抽象，如图：
![avater](https://camo.githubusercontent.com/01a9f11f54f6742f343d6bd2ad528891610a70242361d3169e3684c90e72fe92/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333230323831373937332e706e67)

在图中将used的变化用橘黄色标注上，可以看出在candidates[i] == candidates[i - 1]相同的情况下：

* used[i - 1] == true，说明同一树支candidates[i - 1]使用过
* used[i - 1] == false，说明同一树层candidates[i - 1]使用过
</br>**这块去重的逻辑很抽象，需要仔细思考**
</br>所以当层代码逻辑如下：

```java
for(int i = startIndex; i < candidates.length && sum + candidates[i] <= target; i++){
	//used[i - 1] == true,说明同一树支candiates[i - 1]使用过
	//used[i - 1] == false,说明同一树层candiates[i - 1]使用过
	//要对同一树层使用过的元素进行跳过
	if(i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false){
		continue;
	}
	sum += candidates[i];
	path.add(candidates[i]);
	used[i] = true;
	backTracking(candidates, target, sum, i + 1, used);
	used[i] = false;
	sum -= candidates[i];       
	path.removeLast();
}
```
注意sum + candidates[i] <= target为剪枝操作。

整体代码如下：
```java
class Solution {
    List<List<Integer>> result = new ArrayList<>();
    LinkedList<Integer> path = new LinkedList<>();
    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        //为了将重复的数字都放在一起，所以先进行排序
        Arrays.sort(candidates);
        boolean[] used = new boolean[candidates.length];
        backTracking(candidates, target, 0, 0, used);
        return result;
    }

    public void backTracking(int[] candidates, int target, int sum, int startIndex, boolean[] used){
        if(sum > target) return;
        if(sum == target){
            result.add(new ArrayList<>(path));
            return;
        } 
        for(int i = startIndex; i < candidates.length && candidates[i] + sum <= target; i++){
            // used[i - 1] == true，说明同一树支candidates[i - 1]使用过
            // used[i - 1] == false，说明同一树层candidates[i - 1]使用过
            // 要对同一树层使用过的元素进行跳过
            if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false) {
                continue;
            }
            sum += candidates[i];
            path.add(candidates[i]);
            used[i] = true;
            backTracking(candidates, target, sum, i + 1, used); // 和39.组合总和的区别1：这里是i+1，每个数字在每个组合中只能使用一次
            used[i] = false;
            sum -= candidates[i];
            path.removeLast(); 
        }
    }
}
```