## 编号：银行中的激光束数量（AC）

银行内部的防盗安全装置已经激活。给你一个下标从 0 开始的二进制字符串数组 bank ，表示银行的平面图，这是一个大小为 m x n 的二维矩阵。 bank[i] 表示第 i 行的设备分布，由若干 '0' 和若干 '1' 组成。'0' 表示单元格是空的，而 '1' 表示单元格有一个安全设备。

对任意两个安全设备而言，如果同时 满足下面两个条件，则二者之间存在 一个 激光束：

两个设备位于两个 不同行 ：r1 和 r2 ，其中 r1 < r2 。
满足r1 < i < r2的 所有行i，都没有安全设备 。
激光束是独立的，也就是说，一个激光束既不会干扰另一个激光束，也不会与另一个激光束合并成一束。

返回银行中激光束的总数量。


示例 1：

![avater](https://assets.leetcode.com/uploads/2021/12/24/laser1.jpg)

```
输入：bank = ["011001","000000","010100","001000"]
输出：8
解释：在下面每组设备对之间，存在一条激光束。总共是 8 条激光束：
 * bank[0][1] -- bank[2][1]
 * bank[0][1] -- bank[2][3]
 * bank[0][2] -- bank[2][1]
 * bank[0][2] -- bank[2][3]
 * bank[0][5] -- bank[2][1]
 * bank[0][5] -- bank[2][3]
 * bank[2][1] -- bank[3][2]
 * bank[2][3] -- bank[3][2]
注意，第 0 行和第 3 行上的设备之间不存在激光束。
这是因为第 2 行存在安全设备，这不满足第 2 个条件。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/12/24/laser2.jpg)

```
输入：bank = ["000","111","000"]
输出：0
解释：不存在两个位于不同行的设备
```

提示：

* m == bank.length
* n == bank[i].length
* 1 <= m, n <= 500
* bank[i][j] 为 '0' 或 '1'

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-laser-beams-in-a-bank
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

1.遍历，将每一行的个数输出来存到nums数组中

2.将nums中不为0的加入queue

3.将每一个pop出来的数与pre（前一个pop出来的数）相乘，结果加上那个数

```c++
class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int m = bank.size();
        int n = bank[0].size();
        int res = 0;
        vector<int> nums(m);
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(bank[i][j] != '0') nums[i]++; 
            }
        }
        // for(int i = 0; i < m; i++){
        //     cout << nums[i] << endl;
        // }
        queue<int> que;
        for(int i = 0; i < m; i++){
            if(nums[i] != 0) que.push(nums[i]);
        }
        int pre = que.front();
        int cur = 0;
        while(!que.empty()){
            que.pop();
            if(!que.empty()) cur = que.front();
            else cur = 0;
            //cout << cur << endl;
            res += pre * cur;
            //cout << res << endl;
            pre = cur;
        }
        return res;
    }
};
```


### 优化

突然发现，从vector到queue多了一步，优化一下代码：

```c++
class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int m = bank.size();
        int n = bank[0].size();
        int res = 0;
        queue<int> que;
        for(int i = 0; i < m; i++){
            int temp = 0;
            for(int j = 0; j < n; j++){
                if(bank[i][j] != '0') temp++; 
            }
            if(temp) que.push(temp);
        }
        int pre = que.front();
        int cur = 0;
        while(!que.empty()){
            que.pop();
            if(!que.empty()) cur = que.front();
            else cur = 0;
            //cout << cur << endl;
            res += pre * cur;
            //cout << res << endl;
            pre = cur;
        }
        return res;
    }
};
```


### 大佬写的代码(使用的stl库)

思路一致，用了stl库

代码如下：
```c++
class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int r = 0, p = 0;
        for (auto& s : bank) {
            int o = count(s.begin(), s.end(), '1');
            if (not o) continue;
            r += p * o;
            p = o;
        }
        return r;
    }
};
```