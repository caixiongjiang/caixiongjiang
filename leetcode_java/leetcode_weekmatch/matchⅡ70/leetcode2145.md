## 编号2145：统计隐藏数组数目（×）

给你一个下标从 0 开始且长度为 n 的整数数组 differences ，它表示一个长度为 n + 1 的 隐藏 数组 相邻 元素之间的 差值 。更正式的表述为：我们将隐藏数组记作 hidden ，那么 differences[i] = hidden[i + 1] - hidden[i] 。

同时给你两个整数 lower 和 upper ，它们表示隐藏数组中所有数字的值都在 闭 区间 [lower, upper] 之间。

* 比方说，differences = [1, -3, 4] ，lower = 1 ，upper = 6 ，那么隐藏数组是一个长度为 4 且所有值都在 1 和 6 （包含两者）之间的数组。
    * [3, 4, 1, 5] 和 [4, 5, 2, 6] 都是符合要求的隐藏数组。
    * [5, 6, 3, 7] 不符合要求，因为它包含大于 6 的元素。
    * [1, 2, 3, 4] 不符合要求，因为相邻元素的差值不符合给定数据。
请你返回 符合 要求的隐藏数组的数目。如果没有符合要求的隐藏数组，请返回 0 。

 

示例 1：
```
输入：differences = [1,-3,4], lower = 1, upper = 6
输出：2
解释：符合要求的隐藏数组为：
- [3, 4, 1, 5]
- [4, 5, 2, 6]
所以返回 2 。
```
示例 2：
```
输入：differences = [3,-4,5,1,-2], lower = -4, upper = 5
输出：4
解释：符合要求的隐藏数组为：
- [-3, 0, -4, 1, 2, 0]
- [-2, 1, -3, 2, 3, 1]
- [-1, 2, -2, 3, 4, 2]
- [0, 3, -1, 4, 5, 3]
所以返回 4 。
```
示例 3：
```
输入：differences = [4,-7,2], lower = 3, upper = 6
输出：0
解释：没有符合要求的隐藏数组，所以返回 0 。
```
提示：

* n == differences.length
* 1 <= n <= 105
* -10^5 <= differences[i] <= 10^5
* -10^5 <= lower <= upper <= 10^5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-the-hidden-sequences
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

首先，我们需要知道隐藏数组是否在[lower, upper]内，可以用一个初始值来模拟，每次加上dif数组的值，是否超出范围。不过会超时。

代码如下：
```c++
class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        int sum = 0;
        int res = 0;
        for(int i = lower; i <= upper; i++){
            sum += i;
            bool flag = true;
            for(auto& dif : differences){
                sum += dif;
                //cout << sum << " ";
                if(sum > upper || sum < lower){
                    flag = false;
                    break;
                }
            }
            if(flag) res++;
            sum = 0;
        }
        return res;
    }
};
```

所以要想一个O(n)的办法。

我们可以只用一个数（随便哪个都行）来模拟，然后看看边界差值相差多少来确定。

**相当于我们把界限比作一根铅笔，给定的界限为铅笔1，由你模拟出来的上下界为铅笔2。题目的要求为让你移动铅笔2，使得铅笔1要包含铅笔2**

判断逻辑：
* 如果铅笔2长于铅笔1，无论怎么移，都不行。（也就是说无论你取什么数，都无法落在给定的界限里）
* 否则，可以移动的距离就是所求答案（可以取长度之差 + 1个数，使得落在界限内）

代码如下：
```c++
class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        long long minval = 0, maxval = 0, sum = 0;
        for (auto x : differences) {
            sum += x;
            minval = min(minval, sum);//记录上界
            maxval = max(maxval, sum);//记录下界
        }
        //上下界之差如果大于要求的界限，一定会超出范围
        if (maxval - minval > upper - lower) return 0;
        //两个界限的长度之差即为数组的个数，注意边界问题
        return (upper - lower) - (maxval - minval) + 1;
    }
};
```