## 编号202：快乐数

编写一个算法来判断一个数 n 是不是快乐数。

「快乐数」定义为：

对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
如果 可以变为  1，那么这个数就是快乐数。
如果 n 是快乐数就返回 true ；不是，则返回 false 。

 

示例 1：
```
输入：19
输出：true
解释：
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
```
示例 2：
```
输入：n = 2
输出：false 
```
提示：

1 <= n <= 231 - 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/happy-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
这道题目看上去貌似一道数学问题，其实并不是！

题目中说了会 无限循环，那么也就是说***求和的过程中，sum会重复出现，这对解题很重要！***

正如：关于哈希表，你该了解这些！中所说，<span style="color:green">**当我们遇到了要快速判断一个元素是否出现集合里的时候，就要考虑哈希法了。**</span>

***所以这道题目使用哈希法，来判断这个sum是否重复出现，如果重复了就是return false， 否则一直找到sum为1为止。***

判断sum是否重复出现就可以使用unordered_set。

**还有一个难点就是求和的过程，如果对取数值各个位上的单数操作不熟悉的话，做这道题也会比较艰难。**

代码如下：
```java
class Solution {
    public boolean isHappy(int n) {
        Set<Integer> record=new HashSet<>();
        while(n!=1 && !record.contains(n)){
            record.add(n);
            n=getNextNumber(n);     //方法中的res作为下一轮循环的n使用
        }
        return (n==1);
    }
    private int getNextNumber(int n){
        int res=0;
        while(n>0){
            int tmp = n%10; //个位数
            res += tmp*tmp;
            n=n/10;         //十位数
        }
        return res;
    }
}
```