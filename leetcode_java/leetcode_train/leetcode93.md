## 编号93：复原IP地址
给定一个只包含数字的字符串，用以表示一个 IP 地址，返回所有可能从 s 获得的 **有效 IP 地址** 。你可以按任何顺序返回答案。

**有效 IP 地址** 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。

例如："0.1.2.201" 和 "192.168.1.1" 是**有效**IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是**无效**IP 地址。

 

示例 1：

输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]
示例 2：
```
输入：s = "0000"
输出：["0.0.0.0"]
```
示例 3：
```
输入：s = "1111"
输出：["1.1.1.1"]
```
示例 4：
```
输入：s = "010010"
输出：["0.10.0.10","0.100.1.0"]
```
示例 5：
```
输入：s = "101023"
输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"] 
```
提示：

* 0 <= s.length <= 3000
* s 仅由数字组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/restore-ip-addresses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
从题目的类型来看，**这道题属于切割问题，切割问题就可以使用回溯搜索法把所有可能性搜出来。**
切割问题可以抽象为树型结构，如图：
![avater](https://camo.githubusercontent.com/3a33d3becdfd47803cb939aa3067f71f51d3a25d4392f0c98c3c36071db50339/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333230333733353933332e706e67)

## 回溯三部曲
* 递归参数
startIndex一定是需要的，因为不能重复分割，记录下一层递归分割的起始位置。

**本题我们还需要一个变量pointNum，记录添加逗点的数量。**

所以代码如下：
```java
List<String> result;
// startIndex: 搜索的起始位置， pointNum:添加逗点的数量
private void backTrack(String s, int startIndex, int pointNum)
```
* 递归终止条件
终止条件和[回溯算法：分割回文串](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode131.md)情况就不同了，**本题明确要求只会分成4段，所以不能用切割线切到最后作为终止条件，而是分割的段数作为终止条件。**

pointNum表示逗点数量，pointNum为3说明字符串分成了4段了。

然后验证一下第四段是否合法，如果合法就加入到结果集里

代码如下：
```java
if (pointNum == 3) { // 逗点数量为3时，分隔结束
    // 判断第四段子字符串是否合法，如果合法就放进result中
    if (isValid(s, startIndex, s.length() - 1)) {
        result.add(s);
    }
    return;
}
```

* 单层搜索的逻辑
在```for(int i = startIndex; i < s.length(); i++)```循环中 [startIndex, i]这个区间就是截取的子串，需要判断这个子串是否合法。

如果合法就在字符串后面加上符号.表示已经分割。

如果不合法就结束本层循环，如图中剪掉的分支：
![avater](https://camo.githubusercontent.com/3a33d3becdfd47803cb939aa3067f71f51d3a25d4392f0c98c3c36071db50339/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333230333733353933332e706e67)

然后就是递归和回溯的过程：

递归调用时，下一层递归的startIndex要从i+2开始（**因为需要在字符串中加入了分隔符.**），同时记录分割符的数量pointNum 要 +1。

回溯的时候，就将刚刚加入的分隔符. 删掉就可以了，pointNum也要-1。

代码如下：
```java
for (int i = startIndex; i < s.length(); i++) {
    if (isValid(s, startIndex, i)) {
        s = s.substring(0, i + 1) + "." + s.substring(i + 1);    //在str的后⾯插⼊⼀个逗点
        pointNum++;
        backTrack(s, i + 2, pointNum);// 插⼊逗点之后下⼀个⼦串的起始位置为i+2
        pointNum--;// 回溯
        s = s.substring(0, i + 1) + s.substring(i + 2);// 回溯删掉逗点
    } else {
        break;
    }
}
```
## 判断字符串是否合法
最后就是在写一个判断段位是否是有效段位了。

主要考虑到如下三点：

* 段位以0为开头的数字不合法
* 段位里有非正整数字符不合法
* 段位如果大于255了不合法
代码如下：
```java
// 判断字符串s在左闭⼜闭区间[start, end]所组成的数字是否合法
private Boolean isValid(String s, int start, int end) {
    if (start > end) {
        return false;
    }
    if (s.charAt(start) == '0' && start != end) { // 0开头的数字不合法
        return false;
    }
    int num = 0;
    for (int i = start; i <= end; i++) {
        if (s.charAt(i) > '9' || s.charAt(i) < '0') { // 遇到⾮数字字符不合法
            return false;
        }
        num = num * 10 + (s.charAt(i) - '0');
        if (num > 255) { // 如果⼤于255了不合法
            return false;
        }
    }
    return true;
}
```

整体代码如下：
```java
class Solution {
    List<String> result = new ArrayList<>();

    public List<String> restoreIpAddresses(String s) {
        if (s.length() > 12) return result; // 算是剪枝了
        backTrack(s, 0, 0);
        return result;
    }

    // startIndex: 搜索的起始位置， pointNum:添加逗点的数量
    private void backTrack(String s, int startIndex, int pointNum) {
        if (pointNum == 3) {// 逗点数量为3时，分隔结束
            // 判断第四段⼦字符串是否合法，如果合法就放进result中
            if (isValid(s,startIndex,s.length()-1)) {
                result.add(s);
            }
            return;
        }
        for (int i = startIndex; i < s.length(); i++) {
            if (isValid(s, startIndex, i)) {
                s = s.substring(0, i + 1) + "." + s.substring(i + 1);    //在str的后⾯插⼊⼀个逗点
                pointNum++;
                backTrack(s, i + 2, pointNum);// 插⼊逗点之后下⼀个⼦串的起始位置为i+2
                pointNum--;// 回溯
                s = s.substring(0, i + 1) + s.substring(i + 2);// 回溯删掉逗点
            } else {
                break;
            }
        }
    }

    // 判断字符串s在左闭⼜闭区间[start, end]所组成的数字是否合法
    private Boolean isValid(String s, int start, int end) {
        if (start > end) {
            return false;
        }
        if (s.charAt(start) == '0' && start != end) { // 0开头的数字不合法
            return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s.charAt(i) > '9' || s.charAt(i) < '0') { // 遇到⾮数字字符不合法
                return false;
            }
            num = num * 10 + (s.charAt(i) - '0');
            if (num > 255) { // 如果⼤于255了不合法
                return false;
            }
        }
        return true;
    }
}
```