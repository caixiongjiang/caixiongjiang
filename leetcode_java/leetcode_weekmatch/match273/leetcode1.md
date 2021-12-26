## 编号：反转两次的数字(AC)

反转 一个整数意味着倒置它的所有位。

例如，反转 2021 得到 1202 。反转 12300 得到 321 ，不保留前导零 。
给你一个整数 num ，反转 num 得到 reversed1 ，接着反转 reversed1 得到 reversed2 。如果 reversed2 等于 num ，返回 true ；否则，返回 false 。

 

示例 1：
```
输入：num = 526
输出：true
解释：反转 num 得到 625 ，接着反转 625 得到 526 ，等于 num 。
```
示例 2：
```
输入：num = 1800
输出：false
解释：反转 num 得到 81 ，接着反转 81 得到 18 ，不等于 num 。 
```
示例 3：
```
输入：num = 0
输出：true
解释：反转 num 得到 0 ，接着反转 0 得到 0 ，等于 num 。 
```
提示：

* 0 <= num <= 10^6


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/a-number-after-a-double-reversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 转化为字符串（我的做法）

刚开始我想的也是将个位为0排除掉，但是不小心写错了，以为不行。太笨了，后来竟然是将它转化为字符串做。

代码如下：
```c++
class Solution {
public:
    bool isSameAfterReversals(int num) {
        if(num == 0) return true;
        string s = to_string(num);
        //cout << s << endl;
        bool flag = true;
        string temp = s;
        int n = s.size();
        string ret = "";
        int index = -1;
        for(int i = n - 1; i >= 0; i--){
            if(s[i] != '0'){
                index = i;
                break;
            }
        }
        if(index == n - 1) return true;
        ret = s.substr(0,index + 1);
        //cout << ret << endl;
        if(temp != ret) return false;
        return true;
    }
};
```

### 数学

代码如下：
```c++
class Solution {
public:
    bool isSameAfterReversals(int num) {
        if (num == 0) return true;
        if (num % 10 == 0) return false;
        return true;
    }
};
```

个位为0排出掉就好了，除了0要做特殊判断。
