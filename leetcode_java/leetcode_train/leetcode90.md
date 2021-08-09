## 编号90：子集Ⅱ
给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。返回的解集中，子集可以按 **任意顺序** 排列。

 

示例 1：
```
输入：nums = [1,2,2]
输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
```
示例 2：
```
输入：nums = [0]
输出：[[],[0]] 
```
提示：

* 1 <= nums.length <= 10
* -10 <= nums[i] <= 10

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/subsets-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
集合里有重复元素了，而且求取的子集要去重。

那么关于回溯算法中的去重问题，**在[40.组合总和II](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode40.md)中已经详细讲解过了，和本题是一个套路。**

**排列问题里去重也是这个套路，所以理解“树层去重”和“树枝去重”非常重要。**

用示例中的[1, 2, 2] 来举例，如图所示： （**注意去重需要先对集合排序**）
![avater](https://camo.githubusercontent.com/fcac8430a14f54a39935fbc43df3bf6561ed754f2b883076d97a7da250513383/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132343139353431313937372e706e67)

从图中可以看出，同一树层上重复取2 就要过滤掉，同一树枝上就可以重复取2，因为同一树枝上元素的集合才是唯一子集！

直接给出代码：
```java
class Solution {
    List<List<Integer>> result = new ArrayList<>();
    LinkedList<Integer> path = new LinkedList<>();
    boolean[] used;

    public List<List<Integer>> subsetsWithDup(int[] nums) {
        if(nums.length == 0){
            result.add(path);
            return result;
        }
        Arrays.sort(nums);
        used = new boolean[nums.length];
        backTracking(nums, 0);
        return result;
    }

    public void backTracking(int[] nums, int startIndex){
        result.add(new ArrayList<>(path));
        if(startIndex >= nums.length) return;
        for(int i = startIndex; i < nums.length; i++){
            //此处的操作是为了去重，在同一个for循环中去除相同的元素
            if(i > 0 && nums[i] == nums[i-1] && used[i - 1] == false){
                continue;
            }
            path.add(nums[i]);
            used[i] = true;
            backTracking(nums, i + 1);
            path.removeLast();
            used[i] = false;
        }
    }
}
```