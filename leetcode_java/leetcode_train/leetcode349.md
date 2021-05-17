## 编号349：两个数组的交集

给定两个数组，编写一个函数来计算它们的交集。

 

示例 1：
```
输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2]
```
示例 2：
```
输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[9,4]
```
说明：

输出结果中的每个元素一定是唯一的。
我们可以不考虑输出结果的顺序。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/intersection-of-two-arrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

这道题目，主要要学会使用一种哈希数据结构：<span style="color:green">unordered_set</span>，这个数据结构可以解决很多类似的问题。

注意题目特意说明：输出结果中的每个元素一定是唯一的，也就是说输出的结果的去重的， 同时可以不考虑输出结果的顺序

这道题用暴力的解法时间复杂度是O(n^2)，那来看看使用哈希法进一步优化。

那么用数组来做哈希表也是不错的选择，例如[242. 有效的字母异位词](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode242.md)

但是要注意，<span style="color:green">**使用数组来做哈希的题目，是因为题目都限制了数值的大小。**</span>

而这道题目没有限制数值的大小，就无法使用数组来做哈希表了。
***而且如果哈希值比较少、特别分散、跨度非常大，使用数组就造成空间的极大浪费。***

此时就要使用另一种结构体了，set ，关于set，C++ 给提供了如下三种可用的数据结构：

* std::set
* std::multiset
* std::unordered_set
* std::set和std::multiset底层实现都是红黑树，std::unordered_set的底层实现是哈希表， 使用unordered_set 读写效率是最高的，并不需要对数据进行排序，而且还不要让数据重复，所以选择unordered_set。

思路如图所示：
![avater](https://camo.githubusercontent.com/e78290f6751749c7afae8055cf0e819a5e50e5c919752b9c111df0ba3aee773a/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032303038303931383537303431372e706e67)

代码如下：
```java
import java.util.HashSet;
import java.util.Set;

class Solution {
    public int[] intersection(int[] nums1, int[] nums2) {
        if(nums1==null||nums1.length==0||nums2==null||nums2.length==0){
            return new int[0];
        }
        Set<Integer> set1=new HashSet<>();
        Set<Integer> resSet=new HashSet<>();
        //遍历数组
        for(int i:nums1){
            set1.add(i);
        }
        //遍历数组2的过程需要判断哈希表set1是否存在该元素
        for(int i:nums2){
            if(set1.contains(i)){
                resSet.add(i);
            }
        }
        int[] resArray=new int[resSet.size()];
        int index=0;
        //将结果集合转换为数组
        for(int i:resSet){
            resArray[index++]=i;
        }
        return resArray;
    }
}
```

