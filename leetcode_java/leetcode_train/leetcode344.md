## 编号344：反转字符串
编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 char[] 的形式给出。

不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用 O(1) 的额外空间解决这一问题。

你可以假设数组中的所有字符都是 ASCII 码表中的可打印字符。

示例 1：
```
输入：["h","e","l","l","o"]
输出：["o","l","l","e","h"]
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
对于字符串，我们定义两个指针（也可以说是索引下表），一个从字符串前面，一个从字符串后面，两个指针同时向中间移动，并交换元素。

以字符串hello为例，过程如下：

![avater](https://camo.githubusercontent.com/e9fba18d2e6bc2a78cf62e0cd1273d56935babbd9a71dad3ae24055a8f56da20/68747470733a2f2f747661312e73696e61696d672e636e2f6c617267652f30303865476d5a456c793167703066766939317066673330646530616b776e712e676966)

```java
class Solution {
    public void reverseString(char[] s) {
        char tmp=0;
        for(int i=0,j=s.length-1;i<s.length/2;i++,j--){
            tmp=s[i];
            s[i]=s[j];
            s[j]=tmp;
        }
    }
}
```