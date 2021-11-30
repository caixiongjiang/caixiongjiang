## 编号400：第N位数字

给你一个整数 n ，请你在无限的整数序列 [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...] 中找出并返回第 n 位数字。

示例 1：
```
输入：n = 3
输出：3
```
示例 2：
```
输入：n = 11
输出：0
解释：第 11 位数字在序列 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... 里是 0 ，它是 10 的一部分。 
```
提示：

* 1 <= n <= 2^31 - 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/nth-digit
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 

---
## 思路

### 直接计算


已知 x 位数共有9×10^(x−1)个，所有 x 位数的位数之和是9×10^(x−1)。使用 d 和 count 分别表示当前遍历到的位数和当前位数下的所有整数的位数之和，初始时d=1，count=9。每次将 n 减去 d×count，然后将 d 加 1，将count 乘以 10，直到 n ≤ d × count，此时的 d 是目标数字所在整数的位数，n 是所有 d 位数中从第一位到目标数字的位数。

为了方便计算目标数字，使用目标数字在所有 d 位数中的下标进行计算，下标从 0 开始计数。令index=n−1，则index 即为目标数字在所有 d 位数中的下标，index 的最小可能取值是 0。

得到下标index 之后，即可使用方法一的做法得到无限整数序列中的第 n 位数字。


代码如下：
```c++
class Solution {
public:
    int findNthDigit(int n) {
        int d = 1;      //d表示是几位数
        int count = 9;  //count表示d位数的个数
	//计算处于哪个区间
	while (n > (long) d * count) {
            n -= d * count;//n 是所有 d 位数中从第一位到目标数字的位数
            d++;
            count *= 10;
        }
        //这里用n初始为200来模拟，循环之后的n为200 - 9 = 191
        int index = n - 1;                  //index = 190
        int start = (int) pow(10, d - 1);   //start = 10
        int num = start + index / d;        //num = 10 + 190 / 2 = 105 第几个数
        int digitIndex = index % d;         //digitIndex = 190 % 2 = 0  0代表数内第d位，n代表数内第n位
        int digit = (num / (int) (pow(10, d - digitIndex - 1))) % 10;//digit = (105 / 10) % 10 = 0
        return digit;
    }
};
```


### 二分查找

基本的计算逻辑不变

只是在查找数字使用了二分法，效率会更加高一点。

代码如下：
```c++
class Solution {
public:
    int findNthDigit(int n) {
        int low = 1, high = 9;
        while (low < high) {
            int mid = (high - low) / 2 + low;
            if (totalDigits(mid) < n) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        int d = low;
        int prevDigits = totalDigits(d - 1);
        int index = n - prevDigits - 1;
        int start = (int) pow(10, d - 1);
        int num = start + index / d;
        int digitIndex = index % d;
        int digit = (num / (int) (pow(10, d - digitIndex - 1))) % 10;
        return digit;
    }
    //根据长度来判断处在第几个数
    int totalDigits(int length) {
        int digits = 0;
        int curLength = 1, curCount = 9;
        while (curLength <= length) {
            digits += curLength * curCount;
            curLength++;
            curCount *= 10;
        }
        return digits;
    }
};
```