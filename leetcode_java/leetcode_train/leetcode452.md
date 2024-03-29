## 编号452：用最少数量的箭引爆气球
在二维空间中有许多球形的气球。对于每个气球，提供的输入是水平方向上，气球直径的开始和结束坐标。由于它是水平的，所以纵坐标并不重要，因此只要知道开始和结束的横坐标就足够了。开始坐标总是小于结束坐标。

一支弓箭可以沿着 x 轴从不同点完全垂直地射出。在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被引爆。可以射出的弓箭的数量没有限制。 弓箭一旦被射出之后，可以无限地前进。我们想找到使得所有气球全部被引爆，所需的弓箭的最小数量。

给你一个数组 points ，其中 points [i] = [xstart,xend] ，返回引爆所有气球所必须射出的最小弓箭数。

 
示例 1：
```
输入：points = [[10,16],[2,8],[1,6],[7,12]]
输出：2
解释：对于该样例，x = 6 可以射爆 [2,8],[1,6] 两个气球，以及 x = 11 射爆另外两个气球
```
示例 2：
```
输入：points = [[1,2],[3,4],[5,6],[7,8]]
输出：4
```
示例 3：
```
输入：points = [[1,2],[2,3],[3,4],[4,5]]
输出：2
```
示例 4：
```
输入：points = [[1,2]]
输出：1
```
示例 5：
```
输入：points = [[2,3],[2,3]]
输出：1 
```
提示：

* 1 <= points.length <= 104
* points[i].length == 2
* -231 <= xstart < xend <= 231 - 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-number-of-arrows-to-burst-balloons
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
如何使用最少的弓箭呢？

只射重叠最多的气球，用的弓箭一定最少。

那么就试一试贪心吧！**局部最优：当气球出现重叠，一起射，所用弓箭最少。全局最优：把所有气球射爆所用弓箭最少。**

如何模拟气球射爆的过程？是在数组中移除元素还是做标记呢？

如果真实的模拟射气球的过程，应该射一个，气球数组就remove一个元素，这样最直观，毕竟气球被射了。

如果把气球排序之后，从前到后遍历气球，被射过的气球仅仅跳过就行了，没有必要让气球数组remove气球，只要记录一下箭的数量就可以了。

为了让气球尽可能的重叠，需要对数组进行排序。我们习惯从前往后遍历，所以采用起始位置排序。


如果气球重叠了，重叠气球中右边边界的最小值 之前的区间一定需要一个弓箭。

以题目示例： [[10,16],[2,8],[1,6],[7,12]]为例，如图：（方便起见，已经排序）
![avater](https://camo.githubusercontent.com/6b977b77c443779e3aa70800cfc1417abd8f2e6b17bc9aebba1e50004e57bcf9/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333130313932393739312e706e67)


整体代码如下：
```java
class Solution {
    public int findMinArrowShots(int[][] points) {
        if(points.length == 0) return 0;
        Arrays.sort(points, (o1, o2) -> Integer.compare(o1[0], o2[0]));//对原数组进行排序

        int count = 1;//有气球最少需要一只箭射爆
        for(int i = 1; i < points.length; i++){
            if(points[i][0] > points[i - 1][1]){//两个气球没有重叠的情况
                count++;
            }else{
                points[i][1] = Math.min(points[i][1],points[i-1][1]);//将右边界统一起来，为下一次判断作准备
            }
        }
        return count;
    }
}
```

