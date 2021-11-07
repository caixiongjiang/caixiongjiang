## 编号2061:统计字符串中的元音子字符串(AC)

子字符串 是字符串中的一个连续（非空）的字符序列。

元音子字符串 是 仅 由元音（'a'、'e'、'i'、'o' 和 'u'）组成的一个子字符串，且必须包含 全部五种 元音。

给你一个字符串 word ，统计并返回 word 中 元音子字符串的数目 。

 

示例 1：
```
输入：word = "aeiouu"
输出：2
解释：下面列出 word 中的元音子字符串（斜体加粗部分）：
- "aeiouu"
- "aeiouu"
```
示例 2：
```
输入：word = "unicornarihan"
输出：0
解释：word 中不含 5 种元音，所以也不会存在元音子字符串。
```
示例 3：
```
输入：word = "cuaieuouac"
输出：7
解释：下面列出 word 中的元音子字符串（斜体加粗部分）：
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
```
示例 4：
```
输入：word = "bbaeixoubb"
输出：0
解释：所有包含全部五种元音的子字符串都含有辅音，所以不存在元音子字符串。 
```
提示：

* 1 <= word.length <= 100
* word 仅由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-vowel-substrings-of-a-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

不用多想，这道题上来我就用三个for循环暴力解决（双指针）

上代码：
```c++
class Solution {
public:
    int countVowelSubstrings(string word) { 
        unordered_map<char,int> m;
        if(word.size() < 5) return 0;
        int num = 0;
        string s;
        for(int end = 4; end < word.size(); end++){       
            for(int start = 0; start <= end; start++){
                m = unordered_map<char, int>();              
                s = word.substr(start, end - start + 1);
                int flag=0; //标记是否为元音子串
                for(char c: s){
                    if(c!='a' && c!='e' && c!='i' && c!='o'&& c!='u'){
                        flag=1;
                        break;
                    }
                    m[c]++;
                }                
                if(m['a'] == 0|| m['e'] == 0 || m['i'] == 0 ||m['o'] == 0 || m['u'] == 0) flag=1;
                if(flag == 0) num++;
            }
        }
        return num;  
    }
};
```