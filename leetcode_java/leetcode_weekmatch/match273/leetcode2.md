## 编号：执行所有的后缀指令（AC）

现有一个 n x n 大小的网格，左上角单元格坐标 (0, 0) ，右下角单元格坐标 (n - 1, n - 1) 。给你整数 n 和一个整数数组 startPos ，其中 startPos = [startrow, startcol] 表示机器人最开始在坐标为 (startrow, startcol) 的单元格上。

另给你一个长度为 m 、下标从 0 开始的字符串 s ，其中 s[i] 是对机器人的第 i 条指令：'L'（向左移动），'R'（向右移动），'U'（向上移动）和 'D'（向下移动）。

机器人可以从 s 中的任一第 i 条指令开始执行。它将会逐条执行指令直到 s 的末尾，但在满足下述条件之一时，机器人将会停止：

下一条指令将会导致机器人移动到网格外。
没有指令可以执行。
返回一个长度为 m 的数组 answer ，其中 answer[i] 是机器人从第 i 条指令 开始 ，可以执行的 指令数目 。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/12/09/1.png)

```
输入：n = 3, startPos = [0,1], s = "RRDDLU"
输出：[1,5,4,3,1,0]
解释：机器人从 startPos 出发，并从第 i 条指令开始执行：
- 0: "RRDDLU" 在移动到网格外之前，只能执行一条 "R" 指令。
- 1:  "RDDLU" 可以执行全部五条指令，机器人仍在网格内，最终到达 (0, 0) 。
- 2:   "DDLU" 可以执行全部四条指令，机器人仍在网格内，最终到达 (0, 0) 。
- 3:    "DLU" 可以执行全部三条指令，机器人仍在网格内，最终到达 (0, 0) 。
- 4:     "LU" 在移动到网格外之前，只能执行一条 "L" 指令。
- 5:      "U" 如果向上移动，将会移动到网格外。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/12/09/2.png)

```
输入：n = 2, startPos = [1,1], s = "LURD"
输出：[4,1,0,0]
解释：
- 0: "LURD"
- 1:  "URD"
- 2:   "RD"
- 3:    "D"
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2021/12/09/3.png)

```
输入：n = 1, startPos = [0,0], s = "LRUD"
输出：[0,0,0,0]
解释：无论机器人从哪条指令开始执行，都会移动到网格外。
```
提示：

* m == s.length
* 1 <= n, m <= 500
* startPos.length == 2
* 0 <= startrow, startcol < n
* s 由 'L'、'R'、'U' 和 'D' 组成


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/execution-of-all-suffix-instructions-staying-in-a-grid
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 按照题意模拟（我的做法）

代码有点长，效率也不如别人！

代码如下：
```c++
class Solution {
public:
    vector<int> executeInstructions(int n, vector<int>& startPos, string s) {
        int m = s.size();
        int index = 0;
        vector<int> ret;
        vector<int> temp(2);
        temp = startPos;
        while(index < m){
            int cnt = 0;
            for(int i = index; i < m; i++){
                if(s[i] == 'R'){
                    if(startPos[1] + 1 == n) break;
                    else{
                        startPos[1] += 1;
                        cnt++;
                    }
                }
                if(s[i] == 'L'){
                    if(startPos[1] - 1 == -1) break;
                    else{
                        startPos[1] -= 1;
                        cnt++;
                    }
                }
                if(s[i] == 'U'){
                    if(startPos[0] - 1 == -1) break;
                    else{
                        startPos[0] -= 1;
                        cnt++;
                    }
                }
                if(s[i] == 'D'){
                    if(startPos[0] + 1 == n) break;
                    else{
                        startPos[0] += 1;
                        cnt++;
                    }
                }
            }
            ret.push_back(cnt);
            startPos = temp;
            index++;
        }
        return ret;
    }
};
```

### 大佬的代码

可以将起始的坐标抽象成两个整数，再将走出表格的判断逻辑整合在一起，这样代码简短很多，唯一的原则就是执行次数+1放在判断出界逻辑之后。

```c++
class Solution {
public:
    vector<int> executeInstructions(int n, vector<int>& startPos, string s) {
        vector<int> ans;
        for (int i = 0; i < s.size(); i += 1) {
            int k = 0;
            int x = startPos[0], y = startPos[1];
            for (int j = i; j < s.size(); j += 1) {
                if (s[j] == 'L') y -= 1;
                if (s[j] == 'R') y += 1;
                if (s[j] == 'U') x -= 1;
                if (s[j] == 'D') x += 1;
                if (x < 0 or x >= n or y < 0 or y >= n) break;
                k += 1;
            }
            ans.push_back(k);
        }
        return ans;
    }
};
```