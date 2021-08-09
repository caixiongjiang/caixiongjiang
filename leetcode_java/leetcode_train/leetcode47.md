## 编号47：全排列Ⅱ
给定一个**可包含重复数字**的序列 nums ，**按任意顺序**返回所有不重复的全排列。

 

示例 1：
```
输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]
```
示例 2：
```
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]] 
```
提示：

1 <= nums.length <= 8
-10 <= nums[i] <= 10

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/permutations-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
排列问题其实也是一样的套路。

**还要强调的是去重一定要对元素经行排序，这样我们才方便通过相邻的节点来判断是否重复使用了。**

我以示例中的 [1,1,2]为例 （为了方便举例，已经排序）抽象为一棵树，去重过程如图：
![avater](https://camo.githubusercontent.com/fcfd646bdc26aaa94c6e07b84a1011405b84e8445d744360f871e76e2daf54ac/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132343230313333313232332e706e67)

图中我们对同一树层，前一位（也就是nums[i-1]）如果使用过，那么就进行去重。

一般来说：**组合问题和排列问题是在树形结构的叶子节点上收集结果，而子集问题就是取树上所有节点的结果。**

整体代码如下：
```java
class Solution {
    //存放结果
    List<List<Integer>> result = new ArrayList<>();
    //暂存结果
    LinkedList<Integer> path = new LinkedList<>();

    public List<List<Integer>> permuteUnique(int[] nums) {
        boolean[] used = new boolean[nums.length];
        Arrays.fill(used, false);
        Arrays.sort(nums);
        backTracking(nums, used);
        return result;
    }

    public void backTracking(int[] nums, boolean[] used){
        if(path.size() == nums.length){
            result.add(new ArrayList<>(path));
            return;
        }
        for(int i = 0; i < nums.length; i++){
            // used[i - 1] == true，说明同⼀树⽀nums[i - 1]使⽤过
            // used[i - 1] == false，说明同⼀树层nums[i - 1]使⽤过
            // 如果同⼀树层nums[i - 1]使⽤过则直接跳过
            if(i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false){
                continue;
            }
            //如果同一树枝nums[i]没使用过开始处理
            if(!used[i]){
                used[i] = true;
                path.add(nums[i]);//标记同一树枝nums[i]使用过，防止同一树枝重复使用
                backTracking(nums, used);
                path.removeLast();//回溯，说明同一树层nums[i]使用过，防止下一树层重复
                used[i] = false;//回溯
            }
        }
    }
}
```