## 编号2103：环和杆(AC)

总计有 n 个环，环的颜色可以是红、绿、蓝中的一种。这些环分布穿在 10 根编号为 0 到 9 的杆上。

给你一个长度为 2n 的字符串 rings ，表示这 n 个环在杆上的分布。rings 中每两个字符形成一个 颜色位置对 ，用于描述每个环：

第 i 对中的 第一个 字符表示第 i 个环的 颜色（'R'、'G'、'B'）。
第 i 对中的 第二个 字符表示第 i 个环的 位置，也就是位于哪根杆上（'0' 到 '9'）。
例如，"R3G2B1" 表示：共有 n == 3 个环，红色的环在编号为 3 的杆上，绿色的环在编号为 2 的杆上，蓝色的环在编号为 1 的杆上。

找出所有集齐 全部三种颜色 环的杆，并返回这种杆的数量。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/11/23/ex1final.png)

```
输入：rings = "B0B6G0R6R0R6G9"
输出：1
解释：
- 编号 0 的杆上有 3 个环，集齐全部颜色：红、绿、蓝。
- 编号 6 的杆上有 3 个环，但只有红、蓝两种颜色。
- 编号 9 的杆上只有 1 个绿色环。
因此，集齐全部三种颜色环的杆的数目为 1 。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/11/23/ex2final.png)

```
输入：rings = "B0R0G0R9R0B0G0"
输出：1
解释：
- 编号 0 的杆上有 6 个环，集齐全部颜色：红、绿、蓝。
- 编号 9 的杆上只有 1 个红色环。
因此，集齐全部三种颜色环的杆的数目为 1 。
```
示例 3：
```
输入：rings = "G4"
输出：0
解释：
只给了一个环，因此，不存在集齐全部三种颜色环的杆。
```
提示：

* rings.length == 2 * n
* 1 <= n <= 100
* 如 i 是 偶数 ，则 rings[i] 的值可以取 'R'、'G' 或 'B'（下标从 0 开始计数）
* 如 i 是 奇数 ，则 rings[i] 的值可以取 '0' 到 '9' 中的一个数字（下标从 0 开始计数）

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rings-and-rods
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路


简单的哈希题，直接上代码。

需要注意的是：题目中给的数字为字符型，需要转换为int

代码如下：
```c++
class Solution {
public:
    int countPoints(string rings) {
        vector<int> cntR(10);
        vector<int> cntG(10);     
        vector<int> cntB(10);
        int n = rings.size();
        int ans = 0;
        for(int i = 0; i < n; i += 2){
            if(rings[i] == 'R') cntR[rings[i + 1] - '0']++;
            if(rings[i] == 'G') cntG[rings[i + 1] - '0']++;
            if(rings[i] == 'B') cntB[rings[i + 1] - '0']++;
        }
        for(int i = 0; i < 10; i++){
            if(cntR[i] && cntG[i] && cntB[i]) ans++;
        }
        return ans;
    }
};
```


附上一个大佬写的版本，非常的巧妙：
```c++
class Solution {
public:
    int countPoints(string s) {
        map<char, int> A;
        A['R'] = 0;
        A['G'] = 1;
        A['B'] = 2;
        vector<int> cnt(10);
        for (int i = 0; i < (int)s.size(); i += 2) {
            int x = A[s[i]];
            int y = s[i + 1] - '0';
            cnt[y] |= 1 << x;
        }
        int ret = 0;
        for (int k = 0; k < 10; ++k) {
            if (cnt[k] == 7) ++ret;
        }
        return ret;
    }
};
```