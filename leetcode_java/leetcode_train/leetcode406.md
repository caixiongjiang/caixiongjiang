## 编号406：根据身高重建队列
假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。每个 people[i] = [hi, ki] 表示第 i 个人的身高为 hi ，前面 **正好** 有 ki 个身高大于或等于 hi 的人。

请你重新构造并返回输入数组 people 所表示的队列。返回的队列应该格式化为数组 queue ，其中 queue[j] = [hj, kj] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。

 

示例 1：
```
输入：people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
输出：[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
解释：
编号为 0 的人身高为 5 ，没有身高更高或者相同的人排在他前面。
编号为 1 的人身高为 7 ，没有身高更高或者相同的人排在他前面。
编号为 2 的人身高为 5 ，有 2 个身高更高或者相同的人排在他前面，即编号为 0 和 1 的人。
编号为 3 的人身高为 6 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
编号为 4 的人身高为 4 ，有 4 个身高更高或者相同的人排在他前面，即编号为 0、1、2、3 的人。
编号为 5 的人身高为 7 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
因此 [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] 是重新构造后的队列。
```
示例 2：
```
输入：people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
输出：[[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]] 
```
提示：

* 1 <= people.length <= 2000
* 0 <= hi <= 106
* 0 <= ki < people.length
* 题目数据确保队列可以被重建

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/queue-reconstruction-by-height
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
根据题意，就是给你一堆身高不同的信息和一些位置的信息，让你按照人群的顺序进行输出给定二维数组。

**如果两个维度一起考虑一定会顾此失彼。**

对于本题相信大家困惑的点是先确定k还是先确定h呢，也就是究竟先按h排序呢，还先按照k排序呢？

按照身高h来排序呢，身高一定是从大到小排（**身高相同的话则k小的站前面**），让高个子在前面。

<span style="color:green">可以确定一个维度了，就是身高，前面的节点一定都比本节点高！</span>
那么只需要按照k为下标重新插入队列就可以了，为什么呢？

以图中{5,2} 为例：
![avater](https://camo.githubusercontent.com/3d39c063c5c641dbbde31225b7f3986eadf7c7eb24c720dfc97085c0eb151285/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313231363230313835313938322e706e67)
按照身高排序之后，优先按身高高的people的k来插入，后序插入节点也不会影响前面已经插入的节点，最终按照k的规则完成了队列。

所以在按照身高从大到小排序后：

局部最优：优先按身高高的people的k来插入。插入操作过后的people满足队列属性

全局最优：最后都做完插入操作，整个队列满足题目队列属性
整个插入过程如下：

排序完的people： [[7,0], [7,1], [6,1], [5,0], [5,2]，[4,4]]

插入的过程： 插入[7,0]：[[7,0]] 插入[7,1]：[[7,0],[7,1]] 插入[6,1]：[[7,0],[6,1],[7,1]] 插入[5,0]：[[5,0],[7,0],[6,1],[7,1]] 插入[5,2]：[[5,0],[7,0],[5,2],[6,1],[7,1]] 插入[4,4]：[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]

此时就按照题目的要求完成了重新排列。

整体代码如下：
```java
class Solution {
    public int[][] reconstructQueue(int[][] people) {
        //1、前面有ki个人比他高，先对数组按身高由高到低排序，Ki由低到高排序（默认）
        //排序前：[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]
        //排序后：[7,0],[7,1],[6,1],[5,0],[5,2],[4,4]
        //2、直接插入排序，让元素归位
        // [7,0]      在0位置插入
        // [7,0],[7,1]   在1位置插入
        // [7,0],[6,1],[7,1]      在1位置插入,后面自动后移
        // [5,0],[7,0],[6,1],[7,1]  在0位置插入,后面自动后移
        // [5,0],[7,0],[5,2],[6,1],[7,1]    在2位置插入,后面自动后移
        // [5,0],[7,0],[5,2],[6,1],[4,4],[7,1]   在4位置插入,后面自动后移
        //【列表在制定位置插入元素后，元素会自动后移】

        //o1,o2分别表示people的一个实例

        //Arrays.sort(people,(o1,o2) -> (o1[0] == o2[0]? o1[1]-o2[1]: o2[0]-o1[0]));
        Arrays.sort(people,(x,y) -> (x[0] == y[0]? x[1]-y[1]: y[0]-x[0]));

        ArrayList<int[]> queue = new ArrayList<>();
        for(int[] p : people){
            queue.add(p[1],p);
        }

        //将列表转化为二维数组
        return queue.toArray(new int[people.length][2]);        
    }
}
```