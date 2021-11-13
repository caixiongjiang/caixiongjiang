## 编号520：检测大写字母

我们定义，在以下情况时，单词的大写用法是正确的：

* 全部字母都是大写，比如 "USA" 。
* 单词中所有字母都不是大写，比如 "leetcode" 。
* 如果单词不只含有一个字母，只有首字母大写， 比如 "Google" 。
给你一个字符串 word 。如果大写用法正确，返回 true ；否则，返回 false 。

 

示例 1：
```
输入：word = "USA"
输出：true
```
示例 2：
```
输入：word = "FlaG"
输出：false 
```
提示：

* 1 <= word.length <= 100
* word 由小写和大写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/detect-capital
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

比较简单的分情况判断题

我的思路是根据前两个字母的情况分类讨论：

如果第一个字母是大写，则有两种情况：
* 1.第二个字母是大写，则所有字母都是大写
* 2.第二个字母是小写，则后面所有字母都是小写

如果第一个字母是小写：
* 则后面所有字母都是小写。

代码如下：
```c++
class Solution {
public:
    bool detectCapitalUse(string word) {
        int i = 0;
        if(word[i] >= 65 && word[i] <= 90){
            i++;
            if(word[i] >= 65 && word[i] <= 90){
                i++;
                for(; i < word.size(); i++){
                    if(word[i] >= 97 && word[i] <= 122) return false;
                }
                return true;
            }else{
                i++;
                for(; i < word.size(); i++){
                    if(word[i] >= 65 && word[i] <= 90) return false;
                }
                return true;
            }
        }else{
            i++;
            for(; i < word.size(); i++){
                if(word[i] >= 65 && word[i] <= 90) return false;
            }
            return true;
        }
    }
};
```