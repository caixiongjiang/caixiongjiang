## 编号139：单词拆分

给定一个非空字符串 s 和一个包含非空单词的列表 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

说明：

* 拆分时可以重复使用字典中的单词。
* 你可以假设字典中没有重复的单词。
示例 1：
```
输入: s = "leetcode", wordDict = ["leet", "code"]
输出: true
解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。
```
示例 2：
```
输入: s = "applepenapple", wordDict = ["apple", "pen"]
输出: true
解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
     注意你可以重复使用字典中的单词。
```
示例 3：
```
输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
输出: false
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-break
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

本道是枚举分割所有字符串，判断是否在字典里出现过。很明显可以使用回溯法进行分割。

先给出回溯法C++代码：
```c++
class Solution {
private:
    bool backtracking (const string& s, const unordered_set<string>& wordSet, int startIndex) {
        if (startIndex >= s.size()) {
            return true;
        }
        for (int i = startIndex; i < s.size(); i++) {
            string word = s.substr(startIndex, i - startIndex + 1);
            if (wordSet.find(word) != wordSet.end() && backtracking(s, wordSet, i + 1)) {
                return true;
            }
        }
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        return backtracking(s, wordSet, 0);
    }
};
```
但显然这是超时的代码！！

递归的过程有很多计算，可以使用数组保存一下递归过程中运算的结果。

c++代码如下：
```c++
class Solution {
private:
    bool backtracking (const string& s,
            const unordered_set<string>& wordSet,
            vector<int>& memory,
            int startIndex) {
        if (startIndex >= s.size()) {
            return true;
        }
        // 如果memory[startIndex]不是初始值了，直接使用memory[startIndex]的结果
        if (memory[startIndex] != -1) return memory[startIndex];
        for (int i = startIndex; i < s.size(); i++) {
            string word = s.substr(startIndex, i - startIndex + 1);
            if (wordSet.find(word) != wordSet.end() && backtracking(s, wordSet, memory, i + 1)) {
                memory[startIndex] = 1; // 记录以startIndex开始的子串是可以被拆分的
                return true;
            }
        }
        memory[startIndex] = 0; // 记录以startIndex开始的子串是不可以被拆分的
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<int> memory(s.size(), -1); // -1 表示初始化状态
        return backtracking(s, wordSet, memory, 0);
    }
};
```

这份代码可以AC了，但是效率并不是很高，下面用背包来做一做！

## 背包问题

动态规划五部曲

单词就是物品，字符串s就是背包，单词能否组成字符串s，就是问物品能不能把背包装满。

拆分时可以重复使用字典中的单词，说明就是一个完全背包！

动规五部曲分析如下：

1.确定dp数组以及下标的含义

**dp[i] : 字符串长度为i的话，dp[i]为true，表示可以拆分为一个或多个在字典中出现的单词。**

2.确定递推公式

**如果确定dp[j] 是true，且 [j, i] 这个区间的子串出现在字典里，那么dp[i]一定是true。（j < i ）。**

<span style="color:green">**所以递推公式是 if([j, i] 这个区间的子串出现在字典里 && dp[j]是true) 那么 dp[i] = true。**</span>

3.dp数组如何初始化

从递归公式中可以看出，dp[i] 的状态依靠 dp[j]是否为true，那么dp[0]就是递归的根基，dp[0]一定要为true，否则递归下去后面都都是false了。

那么dp[0]有没有意义呢？

dp[0]表示如果字符串为空的话，说明出现在字典里。

**但题目中说了“给定一个非空字符串 s” 所以测试数据中不会出现i为0的情况**，那么dp[0]初始为true完全就是为了推导公式。

下标非0的dp[i]初始化为false，只要没有被覆盖说明都是不可拆分为一个或多个在字典中出现的单词。

4.确定遍历顺序

题目中说是拆分为一个或多个在字典中出现的单词，所以这是完全背包。

还要讨论两层for循环的前后循序。

如果求组合数就是外层for循环遍历物品，内层for遍历背包。

如果求排列数就是外层for遍历背包，内层for循环遍历物品。

**本题最终要求的是是否都出现过，所以对出现单词集合里的元素是组合还是排列，并不在意！**

那么本题使用求排列的方式，还是求组合的方式都可以。

即：外层for循环遍历物品，内层for遍历背包 或者 外层for遍历背包，内层for循环遍历物品 都是可以的。

但本题还有特殊性，**因为是要求子串，最好是遍历背包放在外循环，将遍历物品放在内循环。**

如果要是外层for循环遍历物品，内层for遍历背包，就需要把所有的子串都预先放在一个容器里。（如果不理解的话，可以自己尝试这么写一写就理解了）

所以最终我选择的遍历顺序为：遍历背包放在外循环，将遍历物品放在内循环。内循环从前到后。

举例推导dp[i]
以输入: s = "leetcode", wordDict = ["leet", "code"]为例，dp状态如图：

![avater](https://camo.githubusercontent.com/93e08e1542aa16c13cf1cb226e36b66d13b8463f21843b40365f310ff9afb039/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303230323136323635323732372e6a7067)

dp[s.size()]就是所求结果。

整体代码如下：
```c++
class Solution{
public:
    bool wordBreak(string s, vector<string>& wordDict){
        vector<bool> dp(s.size() + 1, false);
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        dp[0] = true;//为后序的动态规划推导使用
        for(int i = 1; i <= s.size(); i++){//遍历背包
            for(int j = 0; j <= i; j++){//遍历物品
                string word = s.substr(j, i - j);
                if(wordSet.find(word) != wordSet.end() && dp[j]){
                    dp[i] = true;
                }
            }
        }
        return dp[s.size()];
    }
};
```
