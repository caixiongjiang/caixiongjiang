## 编号383：赎金信

为了不在赎金信中暴露字迹，从杂志上搜索各个需要的字母，组成单词来表达意思。

给你一个赎金信 (ransomNote) 字符串和一个杂志(magazine)字符串，判断 ransomNote 能不能由 magazines 里面的字符构成。

如果可以构成，返回 true ；否则返回 false 。

magazine 中的每个字符只能在 ransomNote 中使用一次。

 

示例 1：
```
输入：ransomNote = "a", magazine = "b"
输出：false
```
示例 2：
```
输入：ransomNote = "aa", magazine = "ab"
输出：false
```
示例 3：
```
输入：ransomNote = "aa", magazine = "aab"
输出：true 
```
提示：

* 1 <= ransomNote.length, magazine.length <= 105
* ransomNote 和 magazine 由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ransom-note
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

因为题目所只有小写字母，那可以采用空间换取时间的哈希策略， 用一个长度为26的数组还记录magazine里字母出现的次数。

然后再用ransomNote去验证这个数组是否包含了ransomNote所需要的所有字母。

依然是数组在哈希法中的应用。

一些同学可能想，用数组干啥，都用map完事了，**其实在本题的情况下，使用map的空间消耗要比数组大一些的，因为map要维护红黑树或者哈希表，而且还要做哈希函数，是费时的！数据量大的话就能体现出来差别了。 所以数组更加简单直接有效！**

代码如下：
```c++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int record[26] = {0};
        for(int i = 0; i < magazine.size(); i++){
            //通过record数据记录，magazine里各个字符出现次数
            record[magazine[i] - 'a']++;
        }
        for(int j = 0; j < ransomNote.size(); j++){
            //遍历ransomNote，在record里对应的字符数做--操作
            record[ransomNote[j] - 'a']--;
            //如果小于0说明ransomNote里出现的字符，magazine没有
            if(record[ransomNote[j] - 'a'] < 0){
                return false;
            }
        }
        return true;
    }
};
```

版本二：
```c++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> cnt1(26), cnt2(26);
        for(int i = 0; i < ransomNote.size(); i++){
            cnt1[ransomNote[i] - 'a']++;
        }
        for(int i = 0; i < magazine.size(); i++){
            cnt2[magazine[i] - 'a']++;
        }
        if(cnt1.size() > cnt2.size()) return false;
        for(int i = 0; i < cnt1.size(); i++){
            if(cnt1[i] > cnt2[i]) return false;
        }
        return true;
    }
};
```