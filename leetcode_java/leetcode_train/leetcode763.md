## 编号763：划分字母区间
字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。返回一个表示每个字符串片段的长度的列表。

 

示例：
```
输入：S = "ababcbacadefegdehijhklij"
输出：[9,7,8]
解释：
划分结果为 "ababcbaca", "defegde", "hijhklij"。
每个字母最多出现在一个片段中。
像 "ababcbacadefegde", "hijhklij" 的划分是错误的，因为划分的片段数较少。 
```
提示：

* S的长度在[1, 500]之间。
* S只包含小写字母 'a' 到 'z' 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/partition-labels
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
题目要求同一字母最多出现在一个片段中，那么如何把同一个字母的都圈在同一个区间里呢？


在遍历的过程中相当于是要找每一个字母的边界，如果找到之前遍历过的所有字母的最远边界，说明这个边界就是分割点了。此时前面出现过所有字母，最远也就到这个边界了。

可以分为如下两步：

* 统计每一个字符最后出现的位置
* 从头遍历字符，并更新字符的最远出现下标，如果找到字符最远出现位置下标和当前下标相等了，则找到了分割点
</br>如图：

![avater](https://camo.githubusercontent.com/df42dd4499b985d072029c73d8a1923dca4890265806f9cea3781f7192ea0908/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313232323139313932343431372e706e67)

整体代码如下：
```java
class Solution {
    public List<Integer> partitionLabels(String s) {
        List<Integer> list = new LinkedList<>();
        int[] edge = new int[500];
        char[] chars = s.toCharArray();//字符串转数组
        //统计所有字母的最远区间下标
        for(int i = 0; i < chars.length; i++){
            edge[chars[i] - 0] = i;
        }
        int idx = 0;
        int last = -1;
        for(int i = 0; i < chars.length; i++){
            idx = Math.max(idx, edge[chars[i] - 0]);//不断更新字母最远区间下标
            if(i == idx){//找到边界
                list.add(i - last);
                last = i;
            }
        }
        return list;
    }
}
```
