## 编号2116：判断一个括号字符串是否有效（AC）

一个括号字符串是只由 '(' 和 ')' 组成的 非空 字符串。如果一个字符串满足下面 任意 一个条件，那么它就是有效的：

* 字符串为 ().
* 它可以表示为 AB（A 与 B 连接），其中A 和 B 都是有效括号字符串。
* 它可以表示为 (A) ，其中 A 是一个有效括号字符串。

给你一个括号字符串 s 和一个字符串 locked ，两者长度都为 n 。locked 是一个二进制字符串，只包含 '0' 和 '1' 。对于 locked 中 每一个 下标 i ：

* 如果 locked[i] 是 '1' ，你 不能 改变 s[i] 。
* 如果 locked[i] 是 '0' ，你 可以 将 s[i] 变为 '(' 或者 ')' 。
如果你可以将 s 变为有效括号字符串，请你返回 true ，否则返回 false 。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/11/06/eg1.png)

```
输入：s = "))()))", locked = "010100"
输出：true
解释：locked[1] == '1' 和 locked[3] == '1' ，所以我们无法改变 s[1] 或者 s[3] 。
我们可以将 s[0] 和 s[4] 变为 '(' ，不改变 s[2] 和 s[5] ，使 s 变为有效字符串。
```
示例 2：
```
输入：s = "()()", locked = "0000"
输出：true
解释：我们不需要做任何改变，因为 s 已经是有效字符串了。
```
示例 3：
```
输入：s = ")", locked = "0"
输出：false
解释：locked 允许改变 s[0] 。
但无论将 s[0] 变为 '(' 或者 ')' 都无法使 s 变为有效字符串。
```
提示：

* n == s.length == locked.length
* 1 <= n <= 105
* s[i] 要么是 '(' 要么是 ')' 。
* locked[i] 要么是 '0' 要么是 '1' 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/check-if-a-parentheses-string-can-be-valid
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

首先排除掉字符个数为奇数的情况，再从头遍历一次不可修改的右括号，从尾遍历一次不可修改的左括号，看是否能构成有效字符串就行了。

代码如下：
```c++
class Solution {
public:
    bool canBeValid(string s, string locked) {
        int n = s.size(),l = 0, r = 0;
        if(n % 2 == 1) return false;
        //从前往后遍历统计右括号
        for(int i = 0; i < n; i++){
            if(locked[i] == '1' && s[i] == ')'){
                r++;
                /* i+1-r < r： 从左到右访问到第i个字符，是不可更改的右括号，
                这样的右括号出现次数为r，那它的左边[0...i]最多有i+1-r个左括
                号，左括号数量小于右括号的话，return false */
                if(i + 1 - r < r) return false;
            }
        }
        //从后往前遍历统计左括号
        for(int i = n - 1; i >= 0; i--){
            if(locked[i] == '1' && s[i] == '('){
                l++;
                /* n-i-l<l： 从右到左访问到第i个字符，是不可更改的左括号，
                这样的左括号出现次数为l，那它的右边[i...n-1]最多有n-i-l个
                右括号，右括号数量小于左括号的话，return false */
                if(n - i - l < l) return false;
            }
        }
        return true;
    }
};
```