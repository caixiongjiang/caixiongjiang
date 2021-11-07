## 编号2062:所有子字符串中的元音(AC)

给你一个字符串 word ，返回 word 的所有子字符串中 元音的总数 ，元音是指 'a'、'e'、'i'、'o' 和 'u' 。

子字符串 是字符串中一个连续（非空）的字符序列。

注意：由于对 word 长度的限制比较宽松，答案可能超过有符号 32 位整数的范围。计算时需当心。

 

示例 1：
```
输入：word = "aba"
输出：6
解释：
所有子字符串是："a"、"ab"、"aba"、"b"、"ba" 和 "a" 。
- "b" 中有 0 个元音
- "a"、"ab"、"ba" 和 "a" 每个都有 1 个元音
- "aba" 中有 2 个元音
因此，元音总数 = 0 + 1 + 1 + 1 + 1 + 2 = 6 。
```
示例 2：
```
输入：word = "abc"
输出：3
解释：
所有子字符串是："a"、"ab"、"abc"、"b"、"bc" 和 "c" 。
- "a"、"ab" 和 "abc" 每个都有 1 个元音
- "b"、"bc" 和 "c" 每个都有 0 个元音
因此，元音总数 = 1 + 1 + 1 + 0 + 0 + 0 = 3 。
```
示例 3：
```
输入：word = "ltcd"
输出：0
解释："ltcd" 的子字符串均不含元音。
```
示例 4：
```
输入：word = "noosabasboosa"
输出：237
解释：所有子字符串中共有 237 个元音。 
```
提示：

* 1 <= word.length <= 105
* word 由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/vowels-of-all-substrings
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

上来一看和前面的题目好像，上来就用暴力（双指针）的方法，结果就是超出时间限制！

下面粘上我暴力的代码：
```c++
class Solution {
public:
    long long countVowels(string word) {
        int res = 0;
        for(int end = 0; end < word.size(); end++){
            for(int start = 0; start <= end; start++){
                string s = word.substr(start, end - start + 1);
                for(char c : s){
                    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') res++;
                }
            }
        }
        return res;
    }
};
```

想想也是，第二题怎么会比第一题简单！！笑死！！

## 动态规划

对于以字符wrd[idx]为末尾字符的字符串，可看做由以wrd[idx-1]为末尾字符的字符串，添加字符wrd[idx]得来。

那么所求答案就是上一个字符串的结果，加上“新添加字符的影响”。

在添加新字符时，原有字符所能组成的子串会增加（即原有字符到新字符组成的串）。此时，新增的字符有两种可能：

1.是元音字符。

对于这种情况，增加了一个元音字符，其自身作为子串使得总答案+1；也使得前面每个字符的“最大长度子串（即该字符到末尾字符组成的字符串）”的元音字符数量+1。我们可以用一个变量prevNum保存之前子串中元音字符的个数。

2.不是元音字符。

此时，前面每个字符的“最大长度子串”的元音字符数量不变。直接加入这个数量即可（因为新加入字符使得这些子串，作为新串的一部分被遍历到了）。


动态规划代码：
```c++
class Solution {
public:
    long long countVowels(string word) 
    {
        long long wrdSize = word.size();
        long long ans = 0;
                
        long long prevValidCharNum = 0;
        //赋初值
        if(isValidChar(word[0])) { 
            ans = 1; 
            prevValidCharNum = 1;  
        }
        
        for(long long i = 1; i < wrdSize ; i++)
        {
            if(isValidChar(word[i])){
                ans += 1;
                ans += (prevValidCharNum + i);
                prevValidCharNum = prevValidCharNum + i + 1; // 不要忘记更新元音字符数量，+1是其自身对应的字符数量
            }
            else{
                ans += prevValidCharNum;
            }
        }        
        return ans;
    }
    
    bool isValidChar(char c){
        vector<char> dict({'a','e','i','o','u'});
        for(auto v:dict){
            if( c == v) return true;
        }
        return false;
    }
};
```