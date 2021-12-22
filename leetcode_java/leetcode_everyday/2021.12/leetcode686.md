## 编号686:重复叠加字符串匹配

给定两个字符串 a 和 b，寻找重复叠加字符串 a 的最小次数，使得字符串 b 成为叠加后的字符串 a 的子串，如果不存在则返回 -1。

注意：字符串 "abc" 重复叠加 0 次是 ""，重复叠加 1 次是 "abc"，重复叠加 2 次是 "abcabc"。

 

示例 1：
```
输入：a = "abcd", b = "cdabcdab"
输出：3
解释：a 重复叠加三遍后为 "abcdabcdabcd", 此时 b 是其子串。
```
示例 2：
```
输入：a = "a", b = "aa"
输出：2
```
示例 3：
```
输入：a = "a", b = "a"
输出：1
```
示例 4：
```
输入：a = "abc", b = "wxyz"
输出：-1 
```
提示：

* 1 <= a.length <= 104
* 1 <= b.length <= 104
* a 和 b 由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/repeated-string-match
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

真是艰难的过程啊！！

写了一个半小时，终于过了！！

### 字符串匹配(自己的思路)

整体步骤：

1.先做剪枝的操作，如果字符串b中的字符在a中完全没有则无法完成匹配，返回-1；

2.第二步在字符串a中找到等于字符串b中的首字母的下标并放入index数组

3.设b字符串的长度为n，用字符串的substr函数取从下标开始的n个字符与b字符串判断是否相等

4.如果当前字符串a不符合这个条件就将字符串a增加一倍，直到找到相匹配的字符串为止。

起始代码：
```c++
class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        string clone;
        clone = a;
        int n = b.size();
        int res = 1;
        vector<int> cnt1(26);
        vector<int> cnt2(26);
        vector<int> index;
        //剪枝
        for(char c : a){
            cnt1[c - 'a']++;
        }
        for(char c : b){
            cnt2[c - 'a']++;
        }
        for(int i = 0; i < 26; i++){
            if(cnt1[i] == 0 && cnt2[i] != 0) return -1;
        }
        //寻找匹配字符串
        while(true){
            for(int i = 0; i < a.size(); i++){
                if(a[i] == b[0]){
                    index.push_back(i);
                }
            }
            for(int i = 0; i < index.size(); i++){
                if(index[i] + n > a.size()){
                    //这里要加clone数组而不是加其本身，防止指数级增加
                    a += clone;
                    res++;
                }
                if(a.substr(index[i], n) == b){
                    return res;
                }
            }
        }
    }
};
```

很可惜，这个代码超时了！

是因为这个示例：
```
"abcabcabcabc"
"abac"
```

分析原因就是a的字符串无论扩大多少倍都找不到b这个子串，所以a无限增加陷入死循环。

所以需要加入条件跳出循环：设置没有自增前字符串a的长度为temp，也就是如果index数组的在字符串a中位置大于temp并且此时a的长度大于index[i]+n时，是永远不可能匹配成功的！

改进后的代码如下：
```c++
class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        string clone;
        clone = a;
        int n = b.size();
        int res = 1;
        vector<int> cnt1(26);
        vector<int> cnt2(26);
        vector<int> index;
        for(char c : a){
            cnt1[c - 'a']++;
        }
        for(char c : b){
            cnt2[c - 'a']++;
        }
        for(int i = 0; i < 26; i++){
            if(cnt1[i] == 0 && cnt2[i] != 0) return -1;
        }

        int temp = 0;
        while(true){
            for(int i = 0; i < a.size(); i++){
                if(a[i] == b[0]){
                    index.push_back(i);
                }
            }
            if(res == 1) temp = index.size();
            for(int i = 0; i < index.size(); i++){
                if(index[i] > temp && index[i] + n < a.size()) return -1;
                if(index[i] + n > a.size()){
                    a += clone;
                    res++;
                }
                if(a.substr(index[i], n) == b){
                    return res;
                }
            }
        }
    }
};
```

发现还是有3个示例没过，其中一个如下：
```
"baaabbbaba"
"baaabbbababaaabbbababaaabbbababaaabbbababaaabbbababaaabbbababaaabbbababaaabbbababaaabbbababaaabbbaba"

输出：
11
预期结果：
10
```

分析之后发现相差一次的原因是，在同一个index[i]的情况下需要优先加字符串a的倍数，而不是往后找下一个index[i]进行匹配

修改代码如下：
```c++
class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        string clone;
        clone = a;
        int n = b.size();
        int res = 1;
        vector<int> cnt1(26);
        vector<int> cnt2(26);
        vector<int> index;
        //剪枝
        for(char c : a){
            cnt1[c - 'a']++;
        }
        for(char c : b){
            cnt2[c - 'a']++;
        }
        for(int i = 0; i < 26; i++){
            if(cnt1[i] == 0 && cnt2[i] != 0) return -1;
        }
        //寻找匹配字符串
        int temp = 0;
        while(true){
            for(int i = 0; i < a.size(); i++){
                if(a[i] == b[0]){
                    index.push_back(i);
                }
            }
            if(res == 1) temp = index.size();
            for(int i = 0; i < index.size(); i++){
                if(index[i] > temp && index[i] + n < a.size()) return -1;
                //这里从if改成了while
                while(index[i] + n > a.size()){
                    a += clone;
                    res++;
                }
                if(a.substr(index[i], n) == b){
                    return res;
                }
            }
        }
    }
};
```

终于通过了！！时间为0ms

### 暴力匹配（网上看的题解）

代码思路很简单，用了c++的STL标准库

就是不断叠加a字符串，每叠加一次就寻找它包不包含b字符串。
那么问题来了，何以为界？
我姑且无脑的的从叠加0次开始匹配🤣，然后到a字符串叠加到长度刚好大于等于b字符串的长度时，再多匹配一次为止。

代码如下：
```c++
class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        string t = "";
        int n1 = a.size(), n2 = b.size();
        int x = n2 / n1;
        for(int i = 0; i <= x + 2; i++){
            if(t.find(b) != -1){
                return i;
            }else{
                t += a;
            }
        }
        return -1;
    }
};
```
当然效率很低， 通过时间为4ms

### KMP算法

1.字符串a长度为m, 字符串b长度为n

2.n = k * m + c, (0 <= c < m), 则字符串a最多需要k + 2次重复叠加就能满足所有匹配情况

3.k = n / m

4.求出新的主串sstr， b为模式串

5.KMP求出第一次完全匹配的位置i， 则(i - 1) / m + 1就是重复次数

6.如果不能匹配成功则返回-1

```c++
class Solution {
public:
    int repeatedStringMatch(string a, string b) 
    {
        int m = a.size(), n = b.size();
        int mul = n / m + 1;//最多需要额外的重复叠加次数
        string sstr = a;
        while (mul -- ) sstr += a; //主串

        b = '*' + b;
        sstr = '*' + sstr;//下标从1开始
        vector<int> ne(n + 1, 0);
        for (int i = 2, j = 0; i <= n; i ++ )//模式串
        {
            while (j && b[i] != b[j + 1]) j = ne[j];
            if (b[i] == b[j + 1]) j ++ ;
            ne[i] = j;
        }

        for (int i = 1, j = 0; i <= sstr.size(); i ++ )//KMP
        {
            while (j && sstr[i] != b[j + 1]) j = ne[j];
            if (sstr[i] == b[j + 1]) j ++ ;
            if (j == n)
            {
                return (i - 1) / m + 1; //第一次匹配成功
            }
        }

        return -1;
    }
};
```


