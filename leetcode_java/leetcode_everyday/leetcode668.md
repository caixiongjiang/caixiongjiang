## 编号668：乘法表中第k小的数

几乎每一个人都用 乘法表。但是你能在乘法表中快速找到第k小的数字吗？

给定高度m 、宽度n 的一张 m * n的乘法表，以及正整数k，你需要返回表中第k 小的数字。

例 1：
```
输入: m = 3, n = 3, k = 5
输出: 3
解释: 
乘法表:
1	2	3
2	4	6
3	6	9

第5小的数字是 3 (1, 2, 2, 3, 3).
```
例 2：
```
输入: m = 2, n = 3, k = 6
输出: 6
解释: 
乘法表:
1	2	3
2	4	6

第6小的数字是 6 (1, 2, 2, 3, 4, 6).
```
注意：

* m 和 n 的范围在 [1, 30000] 之间。
* k 的范围在 [1, m * n] 之间。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/kth-smallest-number-in-multiplication-table
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 二分搜索（值作为边界）

针对乘法表中的值做二分搜索

* 1.值取值范围为[1, mn]，因此left = 1, right = mn
* 2.每次判断（left + right）/2 是乘法表中第几小元素，来舍弃当前候选集的一半

代码如下：
```c++
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        //值的取值范围是【1，mn】,采用左闭右闭的写法
        int left = 1, right = m * n;
        while(left < right){
            int mid = left + ((right - left) >> 1);
            if(kThCount(m, n, mid) >= k){
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        return left;
    }
    //找到mid在乘法表中的位置
    //思路：列从m开始，行从1开始，即取每行的最大值和mid比较
    //若小于mid，result就加一行的数量，行加1继续比较
    //若大于mid，列减1继续进行比较
    int kThCount(int m, int n, int mid){
        int result = 0, row = 1, col = m;
        while(col > 0 && row <= n){
            if(col * row <= mid){
                result += col;
                row++;
            }else{
                col--;
            }
        }
        return result;
    }
};
```

