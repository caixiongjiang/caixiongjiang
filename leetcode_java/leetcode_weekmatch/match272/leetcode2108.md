## 编号2108:向字符串添加空格（AC）

给你一个下标从 0 开始的字符串 s ，以及一个下标从 0 开始的整数数组 spaces 。

数组 spaces 描述原字符串中需要添加空格的下标。每个空格都应该插入到给定索引处的字符值 之前 。

例如，s = "EnjoyYourCoffee" 且 spaces = [5, 9] ，那么我们需要在 'Y' 和 'C' 之前添加空格，这两个字符分别位于下标 5 和下标 9 。因此，最终得到 "Enjoy Your Coffee" 。
请你添加空格，并返回修改后的字符串。

 

示例 1：
```
输入：s = "LeetcodeHelpsMeLearn", spaces = [8,13,15]
输出："Leetcode Helps Me Learn"
解释：
下标 8、13 和 15 对应 "LeetcodeHelpsMeLearn" 中加粗斜体字符。
接着在这些字符前添加空格。
```
示例 2：
```
输入：s = "icodeinpython", spaces = [1,5,7,9]
输出："i code in py thon"
解释：
下标 1、5、7 和 9 对应 "icodeinpython" 中加粗斜体字符。
接着在这些字符前添加空格。
```
示例 3：
```
输入：s = "spacing", spaces = [0,1,2,3,4,5,6]
输出：" s p a c i n g"
解释：
字符串的第一个字符前可以添加空格。 
```
提示：

* 1 <= s.length <= 3 * 10^5
* s 仅由大小写英文字母组成
* 1 <= spaces.length <= 3 * 10^5
* 0 <= spaces[i] <= s.length - 1
* spaces 中的所有值 严格递增

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/adding-spaces-to-a-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

我第一次想到的是使用c++中string容器的insert方法，每次找到要插入的位置，就插一个空格，但要注意的是下一次插空格的时候需要往后多加一个位置。

代码如下：
```c++
class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        int n = spaces.size();
        for(int i = 0; i < n; i++){
            s.insert(spaces[i] + i, " ");
        }
        return s;
    }
};
```

代码很简单，每次插入都多加i个位置。但是结果是有2个示例通不过，超时了！（62/64）

**原因很简单，如果字符串过长的话，insert方法的底层需要对后面每个字符进行更改，时间复杂度过高！**

### 队列暂存

所以想到了队列来暂存的机制，这样不需要修改后面所有位置上的字符。

代码如下：
```c++
class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        int n = spaces.size();
        int m = s.size();
        queue<char> que;
        string ret;
        int tmp = 0;
        for(int i = 0; i < n; i++){
            int temp = spaces[i];
            for(int j = tmp; j < temp; j++){
                que.emplace(s[j]);
            }
            while(!que.empty()){
                char x = que.front();
                que.pop();
                ret += x;
            }
            ret += " ";
            tmp = temp;//更新下次要入队的位置
        }
        //这里要注意的是，spaces[i]的位置没有到字符串的末尾，所以最后一次tmp到字符串末尾的位置需要重新加入到结果字符串中。
        for(int i = tmp; i < m; i++){
            ret += s[i];
        }
        return ret;
    }
};
```

<span style="color:red">执行用时：160 ms, 在所有 C++ 提交中击败了
100.00%的用户</span>

<span style="color:red">内存消耗：81.4 MB, 在所有 C++ 提交中击败了100.00%的用户</span>

<span style="color:red">通过测试用例：
66 / 66</span>

### 利用数组标记位置

copy了一份第一名的代码！

代码如下：
```c++
class Solution {
public:
    string addSpaces(string s, vector<int>& a) {
        string ret;
        int n = s.size();
        vector<int> c(n);
        for(int i : a) c[i] = 1;
        for(int i = 0; i < s.size(); ++i) {
            if(c[i]) ret += " ";
            ret += s[i];
        }
        return ret;
    }
};
```

**大体思路就是设定一个与字符串长度相同的数组用来标记需要加入空格的位置，再定义一个string字符串复制s字符串，遇到需要加空格的位置，就加空格！**

**利用空间换时间就能通过本题的设定时间限制，结果字符串使用尾插防止修改需要的高时间！**

<span style ="color:red">执行用时：108 ms, 在所有 C++ 提交中击败了100.00%的用户</span>

<span style ="color:red">内存消耗：86.4 MB, 在所有 C++ 提交中击败了100.00%的用户</span>

<span style ="color:red">通过测试用例：
66 / 66
</span>
