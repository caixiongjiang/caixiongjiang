## 编号1221：分割平衡字符串

在一个 平衡字符串 中，'L' 和 'R' 字符的数量是相同的。

给你一个平衡字符串 s，请你将它分割成尽可能多的平衡字符串。

**注意**：分割得到的每个字符串都必须是平衡字符串，且分割得到的平衡字符串是原平衡字符串的连续子串。

返回可以通过分割得到的平衡字符串的**最大数量**。

 

示例 1：
```
输入：s = "RLRRLLRLRL"
输出：4
解释：s 可以分割为 "RL"、"RRLL"、"RL"、"RL" ，每个子字符串中都包含相同数量的 'L' 和 'R' 。
```
示例 2：
```
输入：s = "RLLLLRRRLR"
输出：3
解释：s 可以分割为 "RL"、"LLLRRR"、"LR" ，每个子字符串中都包含相同数量的 'L' 和 'R' 。
```
示例 3：
```
输入：s = "LLLLRRRR"
输出：1
解释：s 只能保持原样 "LLLLRRRR".
```
示例 4：
```
输入：s = "RLRRRLLRLL"
输出：2
解释：s 可以分割为 "RL"、"RRRLLRLL" ，每个子字符串中都包含相同数量的 'L' 和 'R' 。 
```
提示：

* 1 <= s.length <= 1000
* s[i] = 'L' 或 'R'
* s 是一个**平衡**字符串

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/split-a-string-in-balanced-strings
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

这道题目看起来好像很复杂，其实是非常简单的贪心.

从前向后遍历，只要遇到平衡子串，计数就+1，遍历一遍即可。

**局部最优：从前向后遍历，只要遇到平衡子串就统计**

全局最优：统计了最多的平衡子串。

局部最优可以推出全局最优，举不出反例，那么就试试贪心。

例如，LRLR 这本身就是平衡子串 , 但要遇到LR就可以分割。

C++代码如下：
```c++
class Solution {
public:
    int balancedStringSplit(string s) {
        int result = 0;
        int count = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'R') count++;
            else count--;
            if (count == 0) result++;
        }
        return result;
    }
};
```