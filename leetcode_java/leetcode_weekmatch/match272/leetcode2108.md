## 编号2108:找出数组中的第一个回文字符串（AC）

给你一个字符串数组 words ，找出并返回数组中的 第一个回文字符串 。如果不存在满足要求的字符串，返回一个 空字符串 "" 。

回文字符串 的定义为：如果一个字符串正着读和反着读一样，那么该字符串就是一个 回文字符串 。

 

示例 1：
```
输入：words = ["abc","car","ada","racecar","cool"]
输出："ada"
解释：第一个回文字符串是 "ada" 。
注意，"racecar" 也是回文字符串，但它不是第一个。
```
示例 2：
```
输入：words = ["notapalindrome","racecar"]
输出："racecar"
解释：第一个也是唯一一个回文字符串是 "racecar" 。
```
示例 3：
```
输入：words = ["def","ghi"]
输出：""
解释：不存在回文字符串，所以返回一个空字符串。 
```
提示：

* 1 <= words.length <= 100
* 1 <= words[i].length <= 100
* words[i] 仅由小写英文字母组成


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-first-palindromic-string-in-the-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

另外写一个判断是否为回文子串的函数，挨个判断就行了！

代码如下：
```c++
class Solution {
public:
    bool isTrue(string s){
        int n = s.size();
        for(int i = 0, j = n - 1; i <= j; i++, j--){
            if(s[i] != s[j]) return false;
        }
        return true;
    }
    
    string firstPalindrome(vector<string>& words) {
        int m = words.size();
        for(auto &s : words){
            if(isTrue(s)) return s;
            
        }
        return "";
    } 
};
```