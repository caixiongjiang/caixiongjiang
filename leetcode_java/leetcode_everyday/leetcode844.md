## 编号844：比较含退格的字符串

给定 s 和 t 两个字符串，当它们分别被输入到空白的文本编辑器后，请你判断二者是否相等。# 代表退格字符。

如果相等，返回 true ；否则，返回 false 。

注意：如果对空文本输入退格字符，文本继续为空。

 

示例 1：
```
输入：s = "ab#c", t = "ad#c"
输出：true
解释：S 和 T 都会变成 “ac”。
```
示例 2：
```
输入：s = "ab##", t = "c#d#"
输出：true
解释：s 和 t 都会变成 “”。
```
示例 3：
```
输入：s = "a##c", t = "#a#c"
输出：true
解释：s 和 t 都会变成 “c”。
```
示例 4：
```
输入：s = "a#c", t = "b"
输出：false
解释：s 会变成 “c”，但 t 仍然是 “b”。 
```
提示：

* 1 <= s.length, t.length <= 200
* s 和 t 只含有小写字母以及字符 '#'
 

进阶：

* 你可以用 O(N) 的时间复杂度和 O(1) 的空间复杂度解决该问题吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/backspace-string-compare
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
空间复杂度O(n)的栈模拟方法 以及空间复杂度是O(1)的双指针方法。

## 方法一：栈模拟

那么本题，确实可以使用栈的思路，但是没有必要使用栈，因为最后比较的时候还要比较栈里的元素，有点麻烦。

这里直接使用字符串string，来作为栈，末尾添加和弹出，string都有相应的接口，最后比较的时候，只要比较两个字符串就可以了，比比较栈里的元素方便一些。

代码如下：
```c++
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        string s; // 当栈来用
        string t; // 当栈来用
        for (int i = 0; i < S.size(); i++) {
            if (S[i] != '#') s += S[i];
            else if (!s.empty()) {
                s.pop_back();

        }
        for (int i = 0; i < T.size(); i++) {
            if (T[i] != '#') t += T[i];
            else if (!t.empty()) {
                t.pop_back();
            }
        }
        if (s == t) return true; // 直接比较两个字符串是否相等，比用栈来比较方便多了
        return false;
    }
};
```

可以发现有重复的逻辑处理S，处理T，可以把这块公共逻辑抽离出来，代码精简如下：
```c++
class Solution {
private:
string getString(const string& S) {
    string s;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] != '#') s += S[i];
        else if (!s.empty()) {
            s.pop_back();
        }
    }
    return s;
}
public:
    bool backspaceCompare(string S, string T) {
        return getString(S) == getString(T);
    }
};
```

## 优化方法（从后向前双指针）

当然还可以有使用 O(1) 的空间复杂度来解决该问题。

同时从后向前遍历S和T（i初始为S末尾，j初始为T末尾），记录#的数量，模拟消除的操作，如果#用完了，就开始比较S[i]和S[j]。

动画如下：
![avater](https://camo.githubusercontent.com/7e8b6ba5fb7b3c53a9a8e1c882e4f7503b7a2cc303c422dffb4de51920dd9c0e/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f676966732f3834342ee6af94e8be83e590abe98080e6a0bce79a84e5ad97e7aca6e4b8b22e676966)

如果S[i]和S[j]不相同返回false，如果有一个指针（i或者j）先走到的字符串头部位置，也返回false。

代码如下：
```c++
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int sSkipNum = 0; // 记录S的#数量
        int tSkipNum = 0; // 记录T的#数量
        int i = S.size() - 1;
        int j = T.size() - 1;
        while (1) {
            while (i >= 0) { // 从后向前，消除S的#
                if (S[i] == '#') sSkipNum++;
                else {
                    if (sSkipNum > 0) sSkipNum--;
                    else break;
                }
                i--;
            }
            while (j >= 0) { // 从后向前，消除T的#
                if (T[j] == '#') tSkipNum++;
                else {
                    if (tSkipNum > 0) tSkipNum--;
                    else break;
                }
                j--;
            }
            // 后半部分#消除完了，接下来比较S[i] != T[j]
            if (i < 0 || j < 0) break; // S 或者T 遍历到头了
            if (S[i] != T[j]) return false;
            i--;j--;
        }
        // 说明S和T同时遍历完毕
        if (i == -1 && j == -1) return true;
        return false;
    }
};
```