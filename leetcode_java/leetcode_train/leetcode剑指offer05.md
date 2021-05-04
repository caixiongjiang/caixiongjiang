## 剑指Offer 05.替换空格
请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

示例 1：
```
输入：s = "We are happy."
输出："We%20are%20happy."
```


限制：
0 <= s 的长度 <= 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
#### 方法1：
一般会想到运用额外的数组的空间进行替换，此时空间复杂度为O(n),时间复杂度为O(n)
</br>由于每次替换从 1 个字符变成 3 个字符，使用字符数组可方便地进行替换。建立字符数组地长度为 s 的长度的 3 倍，这样可保证字符数组可以容纳所有替换后的字符。

```java
class Solution {
    public String replaceSpace(String s) {
        int length=s.length();
        char[] array=new char[length*3];
        int size=0;
        for(int i=0;i<length;i++){
            char ch=s.charAt(i);//每次读取一个char字符
            if(ch==' '){
                array[size++]='%';
                array[size++]='2';
                array[size++]='0';
            }else{
                array[size++]=ch; 
            }
    }
    String str=new String(array,0,size);//将数组转化成字符串,因为此处字符串不定长所以要添加参数确定长度
    return str;
    }
}
```
#### 方法2：
如果想把这道题目做到极致，就不要只用额外的辅助空间了！
<span style="color:green">首先扩充数组到每个空格替换成"%20"之后的大小。</span>
<span style="color:green">然后从后向前替换空格，也就是双指针法，</span>过程如下：
</br>i指向新长度的末尾，j指向旧长度的末尾。

![avater](https://camo.githubusercontent.com/ceeb030f60d3cea82997354907abfbf403f7ad2caa29fdcda85a3633185076f1/68747470733a2f2f747661312e73696e61696d672e636e2f6c617267652f65366339643234656c7931676f36716d6576686770673230647530396d3471702e676966)

为什么要从后向前填充，从前向后填充不行么？
</br>
从前向后填充就是O(n^2)的算法了，因为每次添加元素都要将添加元素之后的所有元素向后移动。

<span style="color:green">*数组填充类的问题，都可以先预先给数组扩容带填充后的大小，然后在从后向前进行操作。*</span>

这么做有两个好处：

不用申请新数组。
从后向前填充元素，避免了从前先后填充元素要来的 每次添加元素都要将添加元素之后的所有元素向后移动。
</br>***注：这种空间复杂度为O(1)的方法只能由c++实现***

```c++
class Solution {
public:
    string replaceSpace(string s) {
        int count = 0; // 统计空格的个数
        int sOldSize = s.size();
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                count++;
            }
        }
        // 扩充字符串s的大小，也就是每个空格替换成"%20"之后的大小
        s.resize(s.size() + count * 2);
        int sNewSize = s.size();
        // 从后先前将空格替换为"%20"
        for (int i = sNewSize - 1, j = sOldSize - 1; j < i; i--, j--) {
            if (s[j] != ' ') {
                s[i] = s[j];
            } else {
                s[i] = '0';
                s[i - 1] = '2';
                s[i - 2] = '%';
                i -= 2;
            }
        }
        return s;
    }
};
```