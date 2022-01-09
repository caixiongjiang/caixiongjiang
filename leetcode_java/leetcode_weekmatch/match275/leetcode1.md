## 编号：检查是否每一行每一列都包含全部整数（AC）

对一个大小为 n x n 的矩阵而言，如果其每一行和每一列都包含从 1 到 n 的 全部 整数（含 1 和 n），则认为该矩阵是一个 有效 矩阵。

给你一个大小为 n x n 的整数矩阵 matrix ，请你判断矩阵是否为一个有效矩阵：如果是，返回 true ；否则，返回 false 。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/12/21/example1drawio.png)

```
输入：matrix = [[1,2,3],[3,1,2],[2,3,1]]
输出：true
解释：在此例中，n = 3 ，每一行和每一列都包含数字 1、2、3 。
因此，返回 true 。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/12/21/example2drawio.png)

```
输入：matrix = [[1,1,1],[1,2,3],[1,2,3]]
输出：false
解释：在此例中，n = 3 ，但第一行和第一列不包含数字 2 和 3 。
因此，返回 false 。
```
提示：

* n == matrix.length == matrix[i].length
* 1 <= n <= 100
* 1 <= matrix[i][j] <= n

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/check-if-every-row-and-column-contains-all-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

题目要求在n✖️n的矩阵中，每一行中只会出现1到n的数，所以只要先按行判断，再按列判断，暴力模拟即可

### 我的解答（暴力）

代码如下：
```c++
class Solution {
public:
    bool checkValid(vector<vector<int>>& matrix) {
        int n = matrix.size();
        //按行判断
        for(int i = 0; i < n; i++){
            vector<int> cnt(n);
            for(int j = 0; j < n; j++){
                cnt[matrix[i][j] - 1]++;
            }
            for(int k = 0; k < n; k++){
                if(cnt[k] == 0) return false;
            }
        }
        //按列判断
        for(int j = 0; j < n; j++){
            vector<int> cnt(n);
            for(int i = 0; i < n; i++){
                cnt[matrix[i][j] - 1]++;
            }
            for(int k = 0; k < n; k++){
                if(cnt[k] == 0) return false;
            }
        }
        return true;
    }
};
```

### [何逊](https://leetcode-cn.com/u/heltion/)的解答

代码基本一致，就是要将哈希数组的长度多设一位（下标和实际数值相差1）

代码如下：
```c++
class Solution {
public:
    bool checkValid(vector<vector<int>>& m) {
        int n = m.size();
        for (int i = 0; i < n; i += 1) {
            vector<int> v(n + 1);
            for (int j = 0; j < n; j += 1) {
                if (v[m[i][j]]) return false;
                v[m[i][j]] = 1;
            }
        }
        for (int i = 0; i < n; i += 1) {
            vector<int> v(n + 1);
            for (int j = 0; j < n; j += 1) {
                if (v[m[j][i]]) return false;
                v[m[j][i]] = 1;
            }
        }
        return true;
    }
};
```
