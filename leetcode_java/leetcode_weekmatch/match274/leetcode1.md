## 编号：检查是否所有 A 都在 B 之前（×）

给你一个 仅 由字符 'a' 和 'b' 组成的字符串 s 。如果字符串中 每个 'a' 都出现在 每个 'b' 之前，返回 true ；否则，返回 false 。



示例 1：
```
输入：s = "aaabbb"
输出：true
解释：
'a' 位于下标 0、1 和 2 ；而 'b' 位于下标 3、4 和 5 。
因此，每个 'a' 都出现在每个 'b' 之前，所以返回 true 。
```
示例 2：
```
输入：s = "abab"
输出：false
解释：
存在一个 'a' 位于下标 2 ，而一个 'b' 位于下标 1 。
因此，不能满足每个 'a' 都出现在每个 'b' 之前，所以返回 false 。
```
示例 3：
```
输入：s = "bbb"
输出：true
解释：
不存在 'a' ，因此可以视作每个 'a' 都出现在每个 'b' 之前，所以返回 true 。
```
提示：

* 1 <= s.length <= 100
* s[i] 为 'a' 或 'b'

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/check-if-all-as-appears-before-all-bs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

搞了半天就是一个示例没过，比赛的时候还不给我看这示例是啥！！！

错误的代码：
```c++
class Solution {
public:
    bool checkString(string s) {
        int n = s.size();
        if(s == "") return false;
        if(n == 1 && s[0] == 'a') return true;
        if(n == 1 && s[0] == 'b') return false;
        int index1 = -1, index2 = 101;
        for(int i = 0; i < n; i++){
            if(s[i] == 'a') index1 = i;
        }
        for(int i = 0; i < n; i++){
            if(s[i] == 'b'){
                index2 = i;
                break;
            }
        }
        return index1 < index2;
    }
};
```
结束之后再看这个示例是‘b’，果然我语文不好。

```c++
class Solution {
public:
    bool checkString(string s) {
        int n = s.size();
        if(s == "") return false;
        if(n == 1 && s[0] == 'a') return true;
        if(n == 1 && s[0] == 'b') return true;
        int index1 = -1, index2 = 101;
        for(int i = 0; i < n; i++){
            if(s[i] == 'a') index1 = i;
        }
        for(int i = 0; i < n; i++){
            if(s[i] == 'b'){
                index2 = i;
                break;
            }
        }
        return index1 < index2;
    }
};
```

第二种写法就是不出现ba即可


```c++
class Solution {
public:
    bool checkString(string s) {
        for (int i = 1; i < s.size(); i += 1) {
            if (s[i] == 'a' && s[i - 1] == 'b') return false;
        }
        return true;
    }
};
```