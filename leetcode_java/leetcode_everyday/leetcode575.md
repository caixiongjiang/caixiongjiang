## 编号575：分糖果

Alice 有 n 枚糖，其中第 i 枚糖的类型为 candyType[i] 。Alice 注意到她的体重正在增长，所以前去拜访了一位医生。

医生建议 Alice 要少摄入糖分，只吃掉她所有糖的 n / 2 即可（n 是一个偶数）。Alice 非常喜欢这些糖，她想要在遵循医生建议的情况下，尽可能吃到最多不同种类的糖。

给你一个长度为 n 的整数数组 candyType ，返回： Alice 在仅吃掉 n / 2 枚糖的情况下，可以吃到糖的最多种类数。

 

示例 1：
```
输入：candyType = [1,1,2,2,3,3]
输出：3
解释：Alice 只能吃 6 / 2 = 3 枚糖，由于只有 3 种糖，她可以每种吃一枚。
```
示例 2：
```
输入：candyType = [1,1,2,3]
输出：2
解释：Alice 只能吃 4 / 2 = 2 枚糖，不管她选择吃的种类是 [1,2]、[1,3] 还是 [2,3]，她只能吃到两种不同类的糖。
```
示例 3：
```
输入：candyType = [6,6,6,6]
输出：1
解释：Alice 只能吃 4 / 2 = 2 枚糖，尽管她能吃 2 枚，但只能吃到 1 种糖。 
```
提示：

* n == candyType.length
* 2 <= n <= 104
* n 是一个偶数
* -105 <= candyType[i] <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/distribute-candies
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

我的思路是使用哈希数组存放每种糖果的数量，然后取糖果数量和一半糖果数量的最小值（贪心）

我的代码如下：
```c++
class Solution {
public:
    int distributeCandies(vector<int>& candyType) {
        int n = candyType.size();
        int res = 0;
        unordered_map<int, int> amout;//{糖果种类号，对应糖果数量}
        for(int i = 0; i < n; i++){
            amout[candyType[i]]++;
        }
        int x = amout.size();
        res = min(x, n / 2);
        return res;
    }
};
```


官方给出答案中也使用到了贪心。

一方面，设糖果数量为 nn，由于妹妹只能分到一半的糖果，所以答案不会超过n/2；另一方面，设这些糖果一共有m种，答案也不会超过m。

若m ≤ n/2，则可以每种糖果至少分一颗给妹妹，此时答案为 mm；若m > n/2，则妹妹只能分到n/2种糖果，每种糖果分一颗，此时答案为n/2。

综上所述，答案为min(m, n/2)。

官方精简代码：
```c++
class Solution {
public:
    int distributeCandies(vector<int> &candyType) {
        return min(unordered_set<int>(candyType.begin(), candyType.end()).size(), candyType.size() / 2);
    }
};
```