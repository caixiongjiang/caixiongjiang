## 编号：连接两字母单词得到的最长回文串（🍵）

给你一个字符串数组 words 。words 中每个元素都是一个包含 两个 小写英文字母的单词。

请你从 words 中选择一些元素并按 任意顺序 连接它们，并得到一个 尽可能长的回文串 。每个元素 至多 只能使用一次。

请你返回你能得到的最长回文串的 长度 。如果没办法得到任何一个回文串，请你返回 0 。

回文串 指的是从前往后和从后往前读一样的字符串。

 

示例 1：
```
输入：words = ["lc","cl","gg"]
输出：6
解释：一个最长的回文串为 "lc" + "gg" + "cl" = "lcggcl" ，长度为 6 。
"clgglc" 是另一个可以得到的最长回文串。
```
示例 2：
```
输入：words = ["ab","ty","yt","lc","cl","ab"]
输出：8
解释：最长回文串是 "ty" + "lc" + "cl" + "yt" = "tylcclyt" ，长度为 8 。
"lcyttycl" 是另一个可以得到的最长回文串。
```
示例 3：
```
输入：words = ["cc","ll","xx"]
输出：2
解释：最长回文串是 "cc" ，长度为 2 。
"ll" 是另一个可以得到的最长回文串。"xx" 也是。 
```
提示：

* 1 <= words.length <= 105
* words[i].length == 2
* words[i] 仅包含小写英文字母。


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-palindrome-by-concatenating-two-letter-words
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

对于前后相同的字符串可以放在中间构成回文子串。

对于前后不相同的字符串可以放在一头一尾组成回文子串。但是只有偶数个反向字符串能组成！

### 两次遍历

思路转自python题解[flix](https://leetcode-cn.com/problems/longest-palindrome-by-concatenating-two-letter-words/solution/ha-xi-biao-liang-ci-bian-li-qing-song-yi-5t0j/),写了一个c++版本！

两次遍历的思路：

1.第一次遍历原字符串数组，将反转后相同的字符串（包括字符串本身前后相同和本身不同的如“aa”和“aa”以及“cl”和“lc”）进行匹配。

2.由于都是偶数个匹配的逻辑，剩余的奇数个字符串（包括字符串本身前后相同和本身不同的）只有前后相同的字符串能放在中间作为回文子串的一部分。

看个例子：

words = ["ab", "lc", "ba", "cl", "ab", "gg", "bb", "gg", "gg", "cd", "ef"] 为例，展示了以上流程：

* 首先，匹配 word 及其对称表示 rword （如图 灰色箭头所示）。每匹配到一对，最长回文串 +4。注意，对于形如'gg'类型的word，也优先进行以上匹配。
* 其次，若存在未被匹配的形如'bb'、'gg'类型的word（如图 红色字体所示），最长回文串 +2，并返回。

![avater](https://pic.leetcode-cn.com/1641664283-bgtNog-LeetCode-5962-trans.svg)

代码如下：
```c++
class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        map<string, int> mp;//<字符串，个数>
        int res = 0;

        //匹配偶数个字符串
        for(auto &word : words){
            string rword; //反向字符串
            rword += word[1]; 
            rword += word[0];
            if(mp[rword] >= 1){
                mp[rword] -= 1;//保持已有字符串的个数永远保持为1
                res += 4;
            }else{
                mp[word]++;//把前后相同的字符串和前后不同的字符串都放入哈希表中
            }
        }

        //剩余的奇数个前后字符相同的字符串统计【最多只能加一个】
        for(auto &[x, y] : mp){
            if(x[0] == x[1] && y >= 1){
                res += 2;
                break;
            }
        }

        return res;
    }
};
```

### 