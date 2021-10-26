## 编号2047：句子中的有效单词数(×)

句子仅由小写字母（'a' 到 'z'）、数字（'0' 到 '9'）、连字符（'-'）、标点符号（'!'、'.' 和 ','）以及空格（' '）组成。每个句子可以根据空格分解成 一个或者多个 token ，这些 token 之间由一个或者多个空格 ' ' 分隔。

如果一个 token 同时满足下述条件，则认为这个 token 是一个有效单词：

仅由小写字母、连字符和/或标点（不含数字）。
至多一个 连字符 '-' 。如果存在，连字符两侧应当都存在小写字母（"a-b" 是一个有效单词，但 "-ab" 和 "ab-" 不是有效单词）。
至多一个 标点符号。如果存在，标点符号应当位于 token 的 末尾 。
这里给出几个有效单词的例子："a-b."、"afad"、"ba-c"、"a!" 和 "!" 。

给你一个字符串 sentence ，请你找出并返回 sentence 中 有效单词的数目 。

 

示例 1：
```
输入：sentence = "cat and  dog"
输出：3
解释：句子中的有效单词是 "cat"、"and" 和 "dog"
```
示例 2：
```
输入：sentence = "!this  1-s b8d!"
输出：0
解释：句子中没有有效单词
"!this" 不是有效单词，因为它以一个标点开头
"1-s" 和 "b8d" 也不是有效单词，因为它们都包含数字
```
示例 3：
```
输入：sentence = "alice and  bob are playing stone-game10"
输出：5
解释：句子中的有效单词是 "alice"、"and"、"bob"、"are" 和 "playing"
"stone-game10" 不是有效单词，因为它含有数字
```
示例 4：
```
输入：sentence = "he bought 2 pencils, 3 erasers, and 1  pencil-sharpener."
输出：6
解释：句子中的有效单词是 "he"、"bought"、"pencils,"、"erasers,"、"and" 和 "pencil-sharpener." 
```
提示：

* 1 <= sentence.length <= 1000
* sentence 由小写英文字母、数字（0-9）、以及字符（' '、'-'、'!'、'.' 和 ','）组成
* 句子中至少有 1 个 token

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-valid-words-in-a-sentence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

这道题恶心坏了，看了大佬直接用正则，果然小丑竟是我自己，判断半天一堆BUG，目前先不研究正则表达式。

所以我没有AC这道题目，用c++模拟一堆错误。

这里写了一个比较好的c++版本，代码逻辑详看代码的注释：
```c++
class Solution {
public:
    bool ok(char ch){   //判定是否为a~z字母
        if(ch >= 'a' && ch <= 'z') return true;
        return false;
    }

    bool check(string s){   //判断是否为题目给定的token
        int n = s.size();
        bool flag = false;  //标记是否为题目要求的token
        for(int i = 0; i < n; i++){
            if(ok(s[i])) continue;  //遇到字母就继续遍历，跳过后面的判断
            if(isdigit(s[i])) return false; //isdigit()用于判断字符串是否含有数字
            if(s[i] == '-'){
                if(flag) return false;
                if(i == 0 || i == n - 1) return false;  //若‘-’号在单词的开头或者结尾它就不是题目要求的token
                if(!ok(s[i - 1]) || !ok(s[i + 1])) return false;    //‘-’号前后必须都是是字母
                flag = true;
            }
            else if(i != n - 1) return false;   //标点符号必须在单词的最后
        }
        return true;
    }

    int countValidWords(string sentence) {
        stringstream sin(sentence); //stringstream是字符串流。
        string s;
        int res = 0;
        //流的话输出的时候会根据 >> 后面的变量类型进行输出
        //类似于 sin >> x  输入的数据会根据x的类型进行输出，不像scanf("%d", &x);
        while(sin >> s){    //可以理解为cin >> ,以空格或者回车作为结束的标准
            if(check(s)) res++;
        }
        return res;
    }
};
```