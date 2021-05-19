## 编号242：有效的字母异位词

给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

示例 1:
```
输入: s = "anagram", t = "nagaram"
输出: true
```
示例 2:
```
输入: s = "rat", t = "car"
输出: false
```
说明:
你可以假设字符串只包含小写字母。

进阶:
如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-anagram
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
先看暴力的解法，两层for循环，同时还要记录字符是否重复出现，很明显时间复杂度是 O(n^2)。

暴力的方法这里就不做介绍了，直接看一下有没有更优的方式。

***数组其实就是一个简单哈希表***，而且这道题目中字符串只有小写字符，那么就可以定义一个数组，来记录字符串s里字符出现的次数。

如果对哈希表的理论基础关于数组，set，map不了解的话可以看这篇：关于哈希表，你该了解这些！

需要定义一个多大的数组呢，定一个数组叫做record，大小为26 就可以了，初始化为0，<span style="color:green">因为字符a到字符z的ASCII也是26个连续的数值。</span>

为了方便举例，判断一下字符串s= "aee", t = "eae"。

操作动画如下：

![avater](https://camo.githubusercontent.com/5deaafe2bcad9a8ce089ac7fb82ce40d190b0f4249acaef4be7bf78516bc93aa/68747470733a2f2f747661312e73696e61696d672e636e2f6c617267652f30303865476d5a456c7931676f767879673833626e673330647330396f6232392e676966)

定义一个数组叫做record用来上记录字符串s里字符出现的次数。

需要把字符映射到数组也就是哈希表的索引下表上，***因为字符a到字符z的ASCII是26个连续的数值，所以字符a映射为下表0，相应的字符z映射为下表25***。

再遍历 字符串s的时候，***只需要将 s[i] - ‘a’ 所在的元素做+1 操作即可，并不需要记住字符a的ASCII，只要求出一个相对数值就可以了***。 这样就将字符串s中字符出现的次数，统计出来了。

那看一下如何检查字符串t中是否出现了这些字符，同样在遍历字符串t的时候，对t中出现的字符映射哈希表索引上的数值再做-1的操作。

那么最后检查一下，***record数组如果有的元素不为零0，说明字符串s和t一定是谁多了字符或者谁少了字符，return false。***

最后如果record数组所有元素都为零0，说明字符串s和t是字母异位词，return true。

时间复杂度为O(n)，空间上因为定义是的一个常量大小的辅助数组，所以空间复杂度为O(1)。

看完这篇哈希表总结：哈希表：总结篇！（每逢总结必经典），详细就可以哈希表的各种用法非常清晰了。

代码如下：
```java
class Solution {
    public boolean isAnagram(String s, String t) {
        int[] record=new int[26];//从a到z26个字母的数组作为一个哈希表来存储
        for(char c:s.toCharArray()){
            record[c-'a']+=1;
        }
        for(char c:t.toCharArray()){
            record[c-'a']-=1;
        }
        for(int i:record){
            if(i!=0){
                return false;
            }
        }
        return true;
    }
}
```