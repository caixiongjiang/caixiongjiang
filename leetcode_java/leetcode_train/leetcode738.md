## 编号738：单调递增的数字

给定一个非负整数 N，找出小于或等于 N 的最大的整数，同时这个整数需要满足其各个位数上的数字是单调递增。

（当且仅当每个相邻位数上的数字 x 和 y 满足 x <= y 时，我们称这个整数是单调递增的。）

示例 1:
```
输入: N = 10
输出: 9
```
示例 2:
```
输入: N = 1234
输出: 1234
```
示例 3:
```
输入: N = 332
输出: 299
说明: N 是在 [0, 10^9] 范围内的一个整数。
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/monotone-increasing-digits
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
题意很简单，最先想到的一定是暴力解法，先来暴力一波，结果就是**超时！**

</br>代码如下：

```java
class Solution{
    private boolean checkNum(int num){
        int max = 10;
        while(num) {
            int t = num % 10;
            if(max >= t) max = t;
            else return false;
            num = num / 10;
        }
        return true;
    }
    public int monotoneIncreasingDigits(int N){
        for(int i = N; i > 0; i--){
            if(checkNum(i)) return i;
        }
        return 0;
    }
}
```
* 时间复杂度：O(n * m) m为n的数字长度
* 空间复杂度：O(1)

## 贪心算法
题目要求小于等于N的最大单调递增的整数，那么拿一个两位的数字来举例。

例如：98，一旦出现strNum[i - 1] > strNum[i]的情况（非单调递增），首先想让strNum[i - 1]--，然后strNum[i]给为9，这样这个整数就是89，即小于98的最大的单调递增整数。

这一点如果想清楚了，这道题就好办了。

**局部最优：遇到strNum[i - 1] > strNum[i]的情况，让strNum[i - 1]--，然后strNum[i]给为9，可以保证这两位变成最大单调递增整数。**

**全局最优：得到小于等于N的最大单调递增的整数。**

**但这里局部最优推出全局最优，还需要其他条件，即遍历顺序，和标记从哪一位开始统一改成9。**
此时是从前向后遍历还是从后向前遍历呢？

从前向后遍历的话，遇到strNum[i - 1] > strNum[i]的情况，让strNum[i - 1]减一，但此时如果strNum[i - 1]减一了，可能又小于strNum[i - 2]。

这么说有点抽象，举个例子，数字：332，从前向后遍历的话，那么就把变成了329，此时2又小于了第一位的3了，真正的结果应该是299。
</br><span style="color:green">**所以从前后向遍历会改变已经遍历过的结果！**</span>

那么从后向前遍历，就可以重复利用上次比较得出的结果了，从后向前遍历332的数值变化为：332 -> 329 -> 299

确定了遍历顺序之后，那么此时局部最优就可以推出全局，找不出反例，试试贪心。

</br>
整体代码如下：

```java
//版本一：
class Solution {
    public int monotoneIncreasingDigits(int n) {
        String[] strings = (n + "").split("");
        int start = strings.length;
        for(int i = strings.length - 1; i > 0; i--){//从后往前遍历
            if(Integer.parseInt(strings[i]) < Integer.parseInt(strings[i - 1])){
                strings[i - 1] = (Integer.parseInt(strings[i - 1]) - 1) + "";
                start = i;
            }
        }
        for(int i = start; i < strings.length; i++){
            strings[i] = "9";
        }
        return Integer.parseInt(String.join("",strings));
    }
}
```

```java
//版本二：(效率较高的版本，但是逻辑较为复杂)
class Solution {
    public int monotoneIncreasingDigits(int n) {
        String num = String.valueOf(n);
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < num.length() - 1; i++) {
            if (num.charAt(i) <= num.charAt(i + 1)) {
                sb.append(num.charAt(i));
            } else {
                for (int j = i - 1; j >= 0; j--) {
                    if (num.charAt(j) < num.charAt(i)) {
                        sb = new StringBuilder();
                        for (int k = 0; k < num.length(); k++) {
                            if (k <= j) {
                                sb.append(num.charAt(k));
                            } else if (k == j + 1) {
                                sb.append((char) (num.charAt(i) - 1));
                            } else {
                                sb.append('9');
                            }
                        }
                        return Integer.parseInt(sb.toString());
                    }
                }
                sb = new StringBuilder();
                if (num.charAt(0) != '1') {
                    sb.append((char) (num.charAt(0) - 1));
                }
                for (int k = 1; k < num.length(); k++) {
                    sb.append('9');
                }
                return Integer.parseInt(sb.toString());
            }
        }
        sb.append(num.charAt(num.length() - 1));
        return Integer.parseInt(sb.toString());
    }
}
```