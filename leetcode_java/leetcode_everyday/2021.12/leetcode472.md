## 编号472:连接词

给你一个 不含重复 单词的字符串数组 words ，请你找出并返回 words 中的所有 连接词 。

连接词 定义为：一个完全由给定数组中的至少两个较短单词组成的字符串。

 

示例 1：
```
输入：words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
输出：["catsdogcats","dogcatsdog","ratcatdogcat"]
解释："catsdogcats" 由 "cats", "dog" 和 "cats" 组成; 
     "dogcatsdog" 由 "dog", "cats" 和 "dog" 组成; 
     "ratcatdogcat" 由 "rat", "cat", "dog" 和 "cat" 组成。
```
示例 2：
```
输入：words = ["cat","dog","catdog"]
输出：["catdog"] 
```
提示：

* 1 <= words.length <= 104
* 0 <= words[i].length <= 1000
* words[i] 仅由小写字母组成
* 0 <= sum(words[i].length) <= 105


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/concatenated-words
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 字典🌲+dfs

判断一个单词是不是连接词，需要判断这个单词是否完全由至少两个给定数组中的更短的非空单词（可以重复）组成。判断更短的单词是否在给定数组中，可以使用字典树实现。

为了方便处理，首先将数组words**按照字符串的长度递增的顺序排序**，排序后可以确保当遍历到任意单词时，比该单词短的单词一定都已经遍历过，因此可以根据已经遍历过的全部单词判断当前单词是不是连接词。

在将数组words排序之后，遍历数组，跳过空字符串，对于每个非空单词，判断该单词是不是连接词，如果是连接词则将该单词加入结果数组，如果不是连接词则将该单词加入字典树。

判断一个单词是不是连接词的做法是在字典树中深度优先搜索。从该单词的第一个字符（即下标 0 处的字符）开始，在字典树中依次搜索每个字符对应的结点，可能有以下几种情况：

* 如果一个字符对应的结点是单词的结尾，则找到了一个更短的单词，从该字符的后一个字符开始搜索下一个更短的单词；

* 如果一个字符对应的结点在字典树中不存在，则当前的搜索结果失败，回到上一个单词的结尾继续搜索。

* 如果找到一个更短的单词且这个更短的单词的最后一个字符是当前单词的最后一个字符，则当前单词是连接词。由于数组words中没有重复的单词，因此在判断一个单词是不是连接词时，该单词一定没有加入字典树，由此可以确保判断连接词的条件成立。

由于一个连接词由多个更短的非空单词组成，**如果存在一个较长的连接词的组成部分之一是一个较短的连接词，则一定可以将这个较短的连接词换成多个更短的非空单词，因此不需要将连接词加入字典树。**

大佬的字典🌲模版（效率是最高的）：

代码如下：
```c++
constexpr int MN = 8E4, M = 26, ML = 1000 + 1;
int len, top, tree[MN][M];
bool isEnd[MN], vis[ML];

int getNext() {
    isEnd[++top] = 0;
    memset(tree[top], 0, sizeof tree[top]);
    return top;
}

void insert(const string& s) {
    int rt = 1;
    for (char c : s) {
        c -= 'a';
        if (tree[rt][c]) rt = tree[rt][c];
        else rt = tree[rt][c] = getNext();
    }
    isEnd[rt] = 1;
}

class Solution {
    bool dfs(const string& s, int pos) {
        if (pos == len) return true;
        if (vis[pos]) return false;
        int rt = 1;
        for (int i = pos; i < len && rt; ++i) {
            rt = tree[rt][s[i] - 'a'];
            if (isEnd[rt] && dfs(s, i + 1)) return true;
        }
        return false;
    }
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        top = 0; getNext();
        //按照字符串的长度递增的顺序
        sort(words.begin(), words.end(), [](auto&& a, auto&& b) {return a.size() < b.size();});
        vector<string> ans;
        for (auto&& s : words) {            
            if (!(len = s.size())) continue;
            memset(vis, 0, len);
            if (!dfs(s, 0)) insert(s);
            else ans.emplace_back(move(s));
        }
        return ans;
    }
};
```

官方题解（）

代码如下：
```c++
//字典🌲的结构体
struct Trie {
    bool isEnd;
    vector<Trie *> children;
    Trie() {
        this->children = vector<Trie *>(26, nullptr);
        this->isEnd = false;
    }
};

class Solution {
public:
    Trie * trie = new Trie();

    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> ans;
        //按照字符串的长度递增的方式排序
        sort(words.begin(), words.end(), [&](const string & a, const string & b){
            return a.size() < b.size(); 
        });
        for (int i = 0; i < words.size(); i++) {
            string word = words[i];
            //如果为空字符串就跳过
            if (word.size() == 0) {
                continue;
            }
            //如果dfs搜索成功就加入结果数组
            if (dfs(word, 0)) {
                ans.emplace_back(word);
            } else {//如果不成功就加入字典🌲
                insert(word);
            }
        }
        return ans;
    }

    bool dfs(const string & word, int start) {
        //如果字符串的长度等于开始的字符位置就表示匹配成功，成功找到
        if (word.size() == start) {
            return true;
        }
        Trie * node = trie;
        for (int i = start; i < word.size(); i++) {
            char ch = word[i];
            int index = ch - 'a';
            node = node->children[index];
            if (node == nullptr) {
                return false;
            }
            //没有遍历到结尾
            if (node->isEnd) {
                //递归
                if (dfs(word, i + 1)) {
                    return true;
                }
            }
        }
        return false;
    }

    void insert(const string & word) {
        Trie * node = trie;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new Trie();
            }
            node = node->children[index];
        }
        node->isEnd = true;
    }
};

```