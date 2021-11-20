## 编号397：整数替换

给定一个正整数 n ，你可以做如下操作：

1.如果 n 是偶数，则用 n / 2替换 n 。
</br>2.如果 n 是奇数，则可以用 n + 1或n - 1替换 n 。

n 变为 1 所需的最小替换次数是多少？

 

示例 1：
```
输入：n = 8
输出：3
解释：8 -> 4 -> 2 -> 1
```
示例 2：
```
输入：n = 7
输出：4
解释：7 -> 8 -> 4 -> 2 -> 1
或 7 -> 6 -> 3 -> 2 -> 1
```
示例 3：
```
输入：n = 4
输出：2 
```
提示：

* 1 <= n <= 231 - 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/integer-replacement
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 枚举

我们可以使用递归的方法枚举所有将 n 变为 1 的替换序列：

当 n 为偶数时，我们只有唯一的方法将 n 替换为 n/2。

当 n 为奇数时，我们可以选择将 n 增加 1 或减少 1。由于这两种方法都会将 n 变为偶数，那么下一步一定是除以 2，因此这里我们可以看成使用两次操作，将n变为(n+1)/2或(n−1)/2。

代码如下：
```c++
class Solution {
public:
    int integerReplacement(int n) {
        if (n == 1) {
            return 0;
        }
        if (n % 2 == 0) {
            return 1 + integerReplacement(n / 2);
        }
        return 2 + min(integerReplacement(n / 2), integerReplacement(n / 2 + 1));
    }
};
```

### 记忆化搜索

我们给方法一的递归加上记忆化，这样递归树的每一层最多只会计算两个 n 值，时间复杂度降低为O(logn)。

代码如下：
```c++
class Solution {
private:
    unordered_map<int, int> memo;

public:
    int integerReplacement(int n) {
        if (n == 1) {
            return 0;
        }
        if (memo.count(n)) {
            return memo[n];
        }
        if (n % 2 == 0) {
            return memo[n] = 1 + integerReplacement(n / 2);
        }
        return memo[n] = 2 + min(integerReplacement(n / 2), integerReplacement(n / 2 + 1));
    }
};
```

### 贪心

实际上，方法一和方法二中的递归枚举中的「最优解」是固定的：

* 当 n 为偶数时，我们只有唯一的方法将 n 替换为 n/2

* 当 n 为奇数时，n 除以 4 的余数要么为 1，要么为 3。

    * 如果为 1，我们可以断定，应该将 n 变成(n - 1)/2。如果我们必须将 n 变成(n+1)/2才能得到最优解，而(n+1)/2是奇数，那么：

        * 如果下一步进行−1 再除以 2，得到(n-1)/4，那么从(n-1)/2可以除以 2 得到同样的结果；

        * 如果下一步进行+1 再除以 2，得到(n+3)/4，那么从(n-1)/2可以除以 2 再+1得到同样的结果；

因此将n变成(n-1)/2总是不会劣于(n+1)/2。

    * 如果为 3，我们可以断定，应该将 n 变成 (n+1)/2。如果我们必须将n 变成 (n-1)/2才能得到最优解，而(n-1)/2是奇数，那么：

        * 如果下一步进行−1再除以2，得到(n-3)/4，那么从那么从(n+1)/2可以除以 2再-1得到同样的结果；
        * 如果下一步进行+1再除以2，得到(n+1)/4，那么从那么从(n+1)/2可以除以 2得到同样的结果；

因此将 n 变成 (n+1)/2总是不会劣于(n-1)/2
 。但这里还需要考虑一种例外的情况，如果 (n-1)/2已经为 1，即n=3时，后续就无需再进行任何操作，此时将n变成(n-1)/2才是最优的。

因此，我们只需要根据上面的分类讨论，求出将 n 变为 1 的操作次数即可。

代码如下：
```c++
class Solution {
public:
    int integerReplacement(int n) {
        int ans = 0;
        while (n != 1) {
            if (n % 2 == 0) {
                ++ans;
                n /= 2;
            }
            else if (n % 4 == 1) {
                ans += 2;
                n /= 2;
            }
            else {
                if (n == 3) {
                    ans += 2;
                    n = 1;
                }
                else {
                    ans += 2;
                    n = n / 2 + 1;
                }
            }
        }
        return ans;
    }
};
```
