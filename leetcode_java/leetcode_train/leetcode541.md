## 编号541：反转字符串Ⅱ

给定一个字符串 s 和一个整数 k，你需要对从字符串开头算起的每隔 2k 个字符的前 k 个字符进行反转。

如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。

示例:

```
输入: s = "abcdefg", k = 2
输出: "bacdfeg"
```

提示：

该字符串只包含小写英文字母。
给定字符串的长度和 k 在 [1, 10000] 范围内。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-string-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
在遍历字符串的过程中，只要让 i += (2 * k)，i 每次移动 2 * k 就可以了，然后判断是否需要有反转的区间。

因为要找的也就是每2 * k 区间的起点，这样写，程序会高效很多。

<span style="color:green">所以当需要固定规律一段一段去处理字符串的时候，要想想在在for循环的表达式上做做文章。</span>


```java
class Solution {
    public void reverse(char[] s,int start,int end){
        char tmp=0;
        for(int i=start,j=end;i<j;i++,j--){
            tmp=s[i]; 
            s[i]=s[j]; 
            s[j]=tmp;
        }
    }
    public String reverseStr(String s, int k) {
        char[] ch = s.toCharArray();//将字符串写入char型数组
        for(int i=0;i<ch.length;i+=(k*2)){   
            // 1. 每隔 2k 个字符的前 k 个字符进行反转
            // 2. 剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符
        if(i+k<=ch.length){
            reverse(ch,i,i+k-1);
            continue;
        }
        //剩余字符少于k个，则将剩余字符全部反转
        reverse(ch,i,ch.length-1);
        }    
        String res= new String(ch);
        return res;
    }
}
```