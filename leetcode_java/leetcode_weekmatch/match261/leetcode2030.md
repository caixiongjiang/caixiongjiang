## 编号2030：含特定字母的最小子序列

给你一个字符串 s ，一个整数 k ，一个字母 letter 以及另一个整数 repetition 。

返回 s 中长度为 k 且 字典序最小 的子序列，该子序列同时应满足字母 letter 出现 至少 repetition 次。生成的测试用例满足 letter 在 s 中出现 至少 repetition 次。

子序列 是由原字符串删除一些（或不删除）字符且不改变剩余字符顺序得到的剩余字符串。

字符串 a 字典序比字符串 b 小的定义为：在 a 和 b 出现不同字符的第一个位置上，字符串 a 的字符在字母表中的顺序早于字符串 b 的字符。

 

示例 1：
```
输入：s = "leet", k = 3, letter = "e", repetition = 1
输出："eet"
解释：存在 4 个长度为 3 ，且满足字母 'e' 出现至少 1 次的子序列：
- "lee"（"leet"）
- "let"（"leet"）
- "let"（"leet"）
- "eet"（"leet"）
其中字典序最小的子序列是 "eet" 。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/09/13/smallest-k-length-subsequence.png)
```
输入：s = "leetcode", k = 4, letter = "e", repetition = 2
输出："ecde"
解释："ecde" 是长度为 4 且满足字母 "e" 出现至少 2 次的字典序最小的子序列。
```
示例 3：
```
输入：s = "bb", k = 2, letter = "b", repetition = 2
输出："bb"
解释："bb" 是唯一一个长度为 2 且满足字母 "b" 出现至少 2 次的子序列。 
```
提示：

* 1 <= repetition <= k <= s.length <= 5 * 104
* s 由小写英文字母组成
* letter 是一个小写英文字母，在 s 中至少出现 repetition 次

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 方法一：单调栈

首先：这题是要求一个子序列res，以下是这个res需要满足的条件：

1.从原序列中删去n-k个元素，之后得到res
</br>2.res中有至少repetition 个letter
</br>3.res是满足上面两点要求的集合中字典序最小的。

如果是只满足1,3就是一个单调栈的基本做法。从前往后扫描（枚举），只要s[i]< res.back()，且还能删(pop),就继续res.pop_back().

然后再来看看2怎么满足，我们是从前往后枚举的，**因此不能删除到后面letter不够的情况**，因此用cnt来维护后面还剩下多少个letter，**不够就不能删**，这样就会出现我们最后删除的个数< n - k ,**但是字典序还是最小的**，因此我们可以将最后的res长度删减为k，并补上letter在末尾。

整体代码如下：
```c++
class Solution {
public:
    string smallestSubsequence(string s, int k, char letter, int repetition ) {
        int  n = s.size();
        int cnt = 0;  // 后面还未扫描到的 letter的数量
        for(int i = 0 ; i < n; ++ i)  //统计letter出现的数量
            if(s[i] == letter) cnt++ ; 
        int toErase = n - k;   // 要删去n - k 个元素
        string res;         // 答案
        int p = 0;          // 目前为止letter已扫描了的次数
        for(int i = 0 ;i < n; ++ i)
        {
            while(toErase && res.size() && s[i] < res.back()){  // 删去逆序的字母
                if(res.back() == letter){
                    if(repetition  > p - 1 + cnt)  // 后面的letter 不够凑成repetition 个letter
                        break;
                    p -- ;      // 可以删除
                }
                res.pop_back();
                toErase -- ;  //删去一个
            }
            if(s[i]== letter) p ++ , cnt -- ;  // 前面增加，后面减少
            res += s[i];
        }
        
        while(res.size() > k){      // 是因为逆序字母可能不够的原因 会漏删一些 元素，现在检查补上
            if(res.back() == letter) p -- ;
            res.pop_back();
        }
        for(int i = k - 1;i >= 0; -- i){ // 因为前面的元素可能比letter更小，所以要检查一下补上letter
            if(p < repetition  && res[i] != letter) {//(这是为了保证letter个数足够，但letter不够小，所以得从后往前补，保证最小)
                res[i] = letter;
                ++ p;
            }   
        }
        return res;
    }
};
```

## 方法二：
