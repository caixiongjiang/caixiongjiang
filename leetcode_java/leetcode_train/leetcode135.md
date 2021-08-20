## 编号135：分发糖果
老师想给孩子们分发糖果，有 N 个孩子站成了一条直线，老师会根据每个孩子的表现，预先给他们评分。

你需要按照以下要求，帮助老师给这些孩子分发糖果：

* 每个孩子至少分配到 1 个糖果。
* 评分更高的孩子必须比他两侧的邻位孩子获得更多的糖果。
</br>那么这样下来，老师至少需要准备多少颗糖果呢？

 

示例 1：
```
输入：[1,0,2]
输出：5
解释：你可以分别给这三个孩子分发 2、1、2 颗糖果。
```
示例 2：
```
输入：[1,2,2]
输出：4
解释：你可以分别给这三个孩子分发 1、2、1 颗糖果。
     第三个孩子只得到 1 颗糖果，这已满足上述两个条件。
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/candy
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
这道题目一定是要确定一边之后，再确定另一边，例如比较每一个孩子的左边，然后再比较右边，如果两边一起考虑一定会顾此失彼。

先确定右边评分大于左边的情况（也就是从前向后遍历）

此时局部最优：**只要右边评分比左边大，右边的孩子就多一个糖果，全局最优：相邻的孩子中，评分高的右孩子获得比左边孩子更多的糖果**

局部最优可以推出全局最优。

如果ratings[i] > ratings[i - 1] 那么[i]的糖 一定要比[i - 1]的糖多一个，所以贪心：candyVec[i] = candyVec[i - 1] + 1

代码如下：
```java
for(int i = 1; i < ratings.length; i++){
    if(ratings[i] > ratings[i - 1]){
        candyVeci] = candyVec[i - 1] + 1;
    }
}
```
如图：
![avater](https://camo.githubusercontent.com/70449883232e5300b4b31c96a324e6b05faa4c53273edd4d246a95668c155935/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313131373131343931363837382e706e67)
再确定左孩子大于右孩子的情况（从后向前遍历）

遍历顺序这里有同学可能会有疑问，为什么不能从前向后遍历呢？

因为如果从前向后遍历，根据 ratings[i + 1] 来确定 ratings[i] 对应的糖果，那么每次都不能利用上前一次的比较结果了。

**所以确定左孩子大于右孩子的情况一定要从后向前遍历！**

如果 ratings[i] > ratings[i + 1]，此时candyVec[i]（第i个小孩的糖果数量）就有两个选择了，一个是candyVec[i + 1] + 1（从右边这个加1得到的糖果数量），一个是candyVec[i]（之前比较右孩子大于左孩子得到的糖果数量）。

那么又要贪心了，**局部最优：取candyVec[i + 1] + 1 和 candyVec[i] 最大的糖果数量，保证第i个小孩的糖果数量即大于左边的也大于右边的。全局最优：相邻的孩子中，评分高的孩子获得更多的糖果。**

局部最优可以推出全局最优。

所以就取candyVec[i + 1] + 1 和 candyVec[i] 最大的糖果数量，**candyVec[i]只有取最大的才能既保持对左边candyVec[i - 1]的糖果多，也比右边candyVec[i + 1]的糖果多。**

如图：
![avater](https://camo.githubusercontent.com/fd569cc320e81cf432c6fc90366c90d9a640edee14ef179f353063b931dd4afd/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313131373131353635383739312e706e67)
所以该过程代码如下：
```java
for(int i = ratings.length - 2; i >= 0; i--){
    if(ratings[i] > ratings[i + 1]){
        candyVec[i] = max(candyVec[i], candyVec[i + 1] + 1);
    }
}
```
整体代码如下：
```java
class Solution {
    public int candy(int[] ratings) {
        int[] candyVec = new int[ratings.length];
        for(int i = 0; i < candyVec.length; i++){
            candyVec[i] = 1;
        }

        for(int i = 1; i < ratings.length; i++){
            if(ratings[i] > ratings[i - 1]){
                candyVec[i] = candyVec[i - 1] + 1;
            }
        }

        for(int i = ratings.length - 2; i >= 0; i--){
            if(ratings[i] > ratings[i + 1]){
                candyVec[i] = Math.max(candyVec[i], candyVec[i + 1] + 1);
            }
        }
        int count = 0;
        for(int i = 0; i < candyVec.length; i++){
            count += candyVec[i];
        }

        return count;
    }
}
```


本题采用了两次贪心的策略：

* 一次是从左到右遍历，只比较右边孩子评分比左边大的情况。
* 一次是从右到左遍历，只比较左边孩子评分比右边大的情况。
这样从局部最优推出了全局最优，即：相邻的孩子中，评分高的孩子获得更多的糖果。

