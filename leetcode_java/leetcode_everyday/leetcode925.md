## 编号925：长按键入

你的朋友正在使用键盘输入他的名字 name。偶尔，在键入字符 c 时，按键可能会被长按，而字符可能被输入 1 次或多次。

你将会检查键盘输入的字符 typed。如果它对应的可能是你的朋友的名字（其中一些字符可能被长按），那么就返回 True。

 

示例 1：
```
输入：name = "alex", typed = "aaleex"
输出：true
解释：'alex' 中的 'a' 和 'e' 被长按。
```
示例 2：
```
输入：name = "saeed", typed = "ssaaedd"
输出：false
解释：'e' 一定需要被键入两次，但在 typed 的输出中不是这样。
```
示例 3：
```
输入：name = "leelee", typed = "lleeelee"
输出：true
```
示例 4：
```
输入：name = "laiden", typed = "laiden"
输出：true
解释：长按名字中的字符并不是必要的。 
```
提示：

* name.length <= 1000
* typed.length <= 1000
* name 和 typed 的字符都是小写字母。
 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/long-pressed-name
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

这道题目一看以为是哈希，仔细一看不行，要有顺序。

所以模拟同时遍历两个数组，进行对比就可以了。

对比的时候需要一下几点：

* name[i] 和 typed[j]相同，则i++，j++ （继续向后对比）
* name[i] 和 typed[j]不相同
</br>&emsp;看是不是第一位就不相同了，也就是j如果等于0，那么直接返回false
</br>&emsp;不是第一位不相同，就让j跨越重复项，移动到重复项之后的位置，再次比较name[i] 和typed[j]
</br>&emsp;&emsp;如果 name[i] 和 typed[j]相同，则i++，j++ （继续向后对比）
</br>&emsp;&emsp;不相同，返回false
* 对比完之后有两种情况
</br>&emsp;name没有匹配完，例如name:"pyplrzzzzdsfa" type:"ppyypllr"
</br>&emsp;type没有匹配完，例如name:"alex" type:"alexxrrrrssda"
动画如下：

![avater](https://camo.githubusercontent.com/443ed030b0d1046bc3a1fa2d25a929aa0c259ada607b9d11adfac78f8c0f93aa/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f676966732f3932352ee995bfe68c89e994aee585a52e676966)

整体c++代码如下：
```c++
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int i = 0, j = 0;
        while (i < name.size() && j < typed.size()) {
            if (name[i] == typed[j]) { // 相同则同时向后匹配
                j++; i++;
            } else { // 不相同
                if (j == 0) return false; // 如果是第一位就不相同直接返回false
                // j跨越重复项，向后移动，同时防止j越界
                while(j < typed.size() && typed[j] == typed[j - 1]) j++;
                if (name[i] == typed[j]) { // j跨越重复项之后再次和name[i]匹配
                    j++; i++; // 相同则同时向后匹配
                }
                else return false;
            }
        }
        // 说明name没有匹配完，例如 name:"pyplrzzzzdsfa" type:"ppyypllr"
        if (i < name.size()) return false;

        // 说明type没有匹配完，例如 name:"alex" type:"alexxrrrrssda"
        while (j < typed.size()) {
            if (typed[j] == typed[j - 1]) j++;
            else return false;
        }
        return true;
    }
};
```