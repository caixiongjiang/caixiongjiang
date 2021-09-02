## 编号56：合并区间

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。

 

示例 1：
```
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
```
示例 2：
```
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
```
提示：

* 1 <= intervals.length <= 104
* intervals[i].length == 2
* 0 <= starti <= endi <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-intervals
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---

## 思路
按照左边界排序，排序之后局部最优：每次合并都取最大的右边界，这样就可以合并更多的区间了，整体最优：合并所有重叠的区间。

局部最优可以推出全局最优，找不出反例，试试贪心。
看图：（**注意图中区间都是按照左边界排序之后了**）

![avater](https://camo.githubusercontent.com/6af9b5e7c5b2fe5407fcf8a493bf5144acba941f0e7e62d55468f60e9f7b2b3c/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313232333230303633323739312e706e67)


**知道如何判断重复之后，剩下的就是合并了，如何去模拟合并区间呢？**

**其实就是用合并区间后左边界和右边界，作为一个新的区间，加入到result数组里就可以了。如果没有合并就把原区间加入到result数组。**

整体代码如下：
```java
class Solution {
    public int[][] merge(int[][] intervals) {
        List<int[]> res = new LinkedList<>();
        Arrays.sort(intervals,(o1, o2) -> Integer.compare(o1[0], o2[0]));

        int start =  intervals[0][0];
        for(int i = 1; i < intervals.length; i++){
            if(intervals[i][0] > intervals[i - 1][1]){//没有重复
                res.add(new int[]{start, intervals[i - 1][1]});
                start = intervals[i][0];
            }else{                                    //边界重复
                intervals[i][1] = Math.max(intervals[i][1], intervals[i - 1][1]);//统一边界
            }
        }
        res.add(new int[]{start, intervals[intervals.length - 1][1]});//将最后一段合并的区间加入结果
        return res.toArray(new int[res.size()][]);
    }
}
```
