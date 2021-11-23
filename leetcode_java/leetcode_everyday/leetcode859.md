## 编号859：亲密字符串

给你两个字符串 s 和 goal ，只要我们可以通过交换 s 中的两个字母得到与 goal 相等的结果，就返回 true ；否则返回 false 。

交换字母的定义是：取两个下标 i 和 j （下标从 0 开始）且满足 i != j ，接着交换 s[i] 和 s[j] 处的字符。

例如，在 "abcd" 中交换下标 0 和下标 2 的元素可以生成 "cbad" 。
 

示例 1：
```
输入：s = "ab", goal = "ba"
输出：true
解释：你可以交换 s[0] = 'a' 和 s[1] = 'b' 生成 "ba"，此时 s 和 goal 相等。
```
示例 2：
```
输入：s = "ab", goal = "ab"
输出：false
解释：你只能交换 s[0] = 'a' 和 s[1] = 'b' 生成 "ba"，此时 s 和 goal 不相等。
```
示例 3：
```
输入：s = "aa", goal = "aa"
输出：true
解释：你可以交换 s[0] = 'a' 和 s[1] = 'a' 生成 "aa"，此时 s 和 goal 相等。
```
示例 4：
```
输入：s = "aaaaaaabc", goal = "aaaaaaacb"
输出：true
```
提示：

* 1 <= s.length, goal.length <= 2 * 104
* s 和 goal 由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/buddy-strings
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

对于一般情况，我们找到单词中不同的位置，不能多于两个；且他们可以互换。

对于特殊情况，两个串一摸一样，但是题目要求你必须换位置，此时合法的情况只能交换两个一样的字母，意味着有字母至少出现两次。

第一种情况：遍历比较两个串，记录下不同的位置，判断这两个位置是不是正好满足互换关系即可。如果有超过两个不同的位置可以直接返回false。

第二种情况：遍历对串的每个字母计数；如果两个串没有不同的地方，必须有字母在串中出现不止一次。


代码如下：
```c++
class Solution {
public:
    bool buddyStrings(string s, string goal) {
        int cnt = 0;
        if (s.size() != goal.size()) return false;

        int diff1 = -1; // 第一次不同的位置
        int diff2 = -1; // 第二次不同的位置
        int chars[26];
        memset(chars, 0, sizeof(chars));
        bool valid_no_diff = false;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] != goal[i]) {
                cnt++;
                if (cnt > 2) return false;
                if (cnt == 1) diff1 = i;
                if (cnt == 2) diff2 = i;
            }
            chars[s[i]-'a']++;
            if (chars[s[i] - 'a'] >= 2) valid_no_diff = true;
        }

        if (cnt == 0 && valid_no_diff) return true; // 两个串一摸一样，需要有两个以上相同字母出现
        if (cnt == 2 && s[diff1] == goal[diff2] && s[diff2] == goal[diff1]) return true; // 两个串有两个位置不同，需要正好可以互换

        return false;
    }
};
```