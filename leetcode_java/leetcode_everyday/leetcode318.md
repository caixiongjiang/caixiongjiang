## 编号318：最大单词长度乘积

给定一个字符串数组 words，找到 length(word[i]) * length(word[j]) 的最大值，并且这两个单词不含有公共字母。你可以认为每个单词只包含小写字母。如果不存在这样的两个单词，返回 0。

 

示例 1:
```
输入: ["abcw","baz","foo","bar","xtfn","abcdef"]
输出: 16 
解释: 这两个单词为 "abcw", "xtfn"。
```
示例 2:
```
输入: ["a","ab","abc","d","cd","bcd","abcd"]
输出: 4 
解释: 这两个单词为 "ab", "cd"。
```
示例 3:
```
输入: ["a","aa","aaa","aaaa"]
输出: 0 
解释: 不存在这样的两个单词。 
```
提示：

* 2 <= words.length <= 1000
* 1 <= words[i].length <= 1000
* words[i] 仅包含小写字母

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-product-of-word-lengths
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

为了得到最大单词长度乘积，朴素的做法是，遍历字符串数组words中的每一对单词，判断这一对单词是否有公共字母，如果没有公共字母，则用这一对单词的长度乘积更新最大单词长度乘积。

用n表示数组words的长度，用li表示单词words[i]的长度，其中0≤ i< n，则上述做法需要遍历字符串数组words中的每一对单词，对于下标为i和j的单词，其中i < j，需要 $O(l_i \times l_j) $的时间判断是否有公共字母和计算长度乘积。因此上述做法的时间复杂度是 $O(\sum_{0 \le i < j < n} l_i \times l_j)$，该时间复杂度高于 O(n^2)。

如果可以将判断两个单词是否有公共字母的时间复杂度降低到 O(1)，则可以将总时间复杂度降低到 O(n^2)。可以使用位运算预处理每个单词，通过位运算操作判断两个单词是否有公共字母。由于单词只包含小写字母，共有26 个小写字母，因此可以使用位掩码的最低 26 位分别表示每个字母是否在这个单词中出现。将 a 到 z 分别记为第0个字母到第25个字母，则位掩码的从低到高的第i位是1当且仅当第i个字母在这个单词中，其中0≤ i ≤25。

用数组masks记录每个单词的位掩码表示。计算数组 masks 之后，判断第i个单词和第j个单词是否有公共字母可以通过判断masks[i] & masks[j] 是否等于 0实现，当且仅当masks[i] & masks[j]=0 时第i个单词和第 j 个单词没有公共字母，此时使用这两个单词的长度乘积更新最大单词长度乘积。

整体代码如下：
```c++
class Solution {
public:
    int maxProduct(vector<string>& words) {
        int length = words.size();
        vector<int> masks(length);
        for(int i = 0; i < length; i++){
            string word = words[i];
            int wordLength = words[i].size();
            for(int j = 0; j < wordLength; j++){
                masks[i] |= 1 << (word[j] - 'a');
            }
        }
        int maxProd = 0;//表示最大乘积
        for(int i = 0; i < length; i++){
            for(int j = i + 1; j < length; j++){
                if((masks[i] & masks[j]) == 0){
                    maxProd = max(maxProd, int(words[i].size() * words[j].size()));
                }
            }
        }
        return maxProd;
    }
};
```