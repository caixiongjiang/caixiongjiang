## 编号2129：将标题首字母大写(AC)

给你一个字符串 title ，它由单个空格连接一个或多个单词组成，每个单词都只包含英文字母。请你按以下规则将每个单词的首字母 大写 ：

如果单词的长度为 1 或者 2 ，所有字母变成小写。
否则，将单词首字母大写，剩余字母变成小写。
请你返回 大写后 的 title 。

 

示例 1：
```
输入：title = "capiTalIze tHe titLe"
输出："Capitalize The Title"
解释：
由于所有单词的长度都至少为 3 ，将每个单词首字母大写，剩余字母变为小写。
```
示例 2：
```
输入：title = "First leTTeR of EACH Word"
输出："First Letter of Each Word"
解释：
单词 "of" 长度为 2 ，所以它保持完全小写。
其他单词长度都至少为 3 ，所以其他单词首字母大写，剩余字母小写。
```
示例 3：
```
输入：title = "i lOve leetcode"
输出："i Love Leetcode"
解释：
单词 "i" 长度为 1 ，所以它保留小写。
其他单词长度都至少为 3 ，所以其他单词首字母大写，剩余字母小写。 
```
提示：

* 1 <= title.length <= 100
* title 由单个空格隔开的单词组成，且不含有任何前导或后缀空格。
* 每个单词由大写和小写英文字母组成，且都是 非空 的。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/capitalize-the-title
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

思路就是将整个字符串按照空格进行分割，然后按照题目的要求进行字符大小写的处理。

### 字符串分割

代码如下：
```c++
class Solution {
public:
    string capitalizeTitle(string title) {
        string temp;
        vector<string> v;
        string res;
        //分割字符串
        for(auto &ch : title){
            if(ch == ' '){
                v.push_back(temp); 
                temp.clear();
            }else{
                temp += ch;
            }
        }
        v.push_back(temp);//加入最后一个字符串
        
        //对字符串进行处理
        for(auto &s : v){
            if(s.size() < 3){
                for(auto &ch : s){
                    if(ch >= 65 && ch <= 90) ch += 32;
                }
                res += s + " ";
            }else{
                for(int i = 0; i < s.size(); i++){
                    if(i == 0){
                        if(s[i] >= 97 && s[i] <= 122) s[i] -= 32;
                    }
                    else if(s[i] >= 65 && s[i] <= 90){
                        s[i] += 32;
                    }
                }
                res += s + " ";
            } 
        }
        res.erase(res.end() - 1);//去掉最后一个空格
        return res;
    }
};
```

照例，还是要copy一下大佬的代码学习学习！

### [何逊](https://leetcode-cn.com/u/heltion/)的做法

代码如下：
```c++
class Solution {
public:
    string capitalizeTitle(string t) {
        for (int i = 0, j = 0; i < t.size(); i = j += 1) {
            while (j < t.size() and t[j] != ' ') j += 1;
            for (int k = i; k < j; k += 1){ 
                if (t[k] >= 'A' and t[k] <= 'Z') t[k] += 'a' - 'A';
            }
            if (j - i > 2) t[i] = t[i] - 'a' + 'A';
        }
        return t;
    }
};
```

大佬的做法是将字符串分割这部给省略了，直接暴力进行判断，代码简短一点，但效率并不高，不过比赛可以这样。