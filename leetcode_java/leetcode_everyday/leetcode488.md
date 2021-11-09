## 编号488：祖玛游戏

你正在参与祖玛游戏的一个变种。

在这个祖玛游戏变体中，桌面上有 一排 彩球，每个球的颜色可能是：红色 'R'、黄色 'Y'、蓝色 'B'、绿色 'G' 或白色 'W' 。你的手中也有一些彩球。

你的目标是 清空 桌面上所有的球。每一回合：

从你手上的彩球中选出 任意一颗 ，然后将其插入桌面上那一排球中：两球之间或这一排球的任一端。
接着，如果有出现 三个或者三个以上 且 颜色相同 的球相连的话，就把它们移除掉。
如果这种移除操作同样导致出现三个或者三个以上且颜色相同的球相连，则可以继续移除这些球，直到不再满足移除条件。
如果桌面上所有球都被移除，则认为你赢得本场游戏。
重复这个过程，直到你赢了游戏或者手中没有更多的球。
给你一个字符串 board ，表示桌面上最开始的那排球。另给你一个字符串 hand ，表示手里的彩球。请你按上述操作步骤移除掉桌上所有球，计算并返回所需的 最少 球数。如果不能移除桌上所有的球，返回 -1 。

 

示例 1：
```
输入：board = "WRRBBW", hand = "RB"
输出：-1
解释：无法移除桌面上的所有球。可以得到的最好局面是：
- 插入一个 'R' ，使桌面变为 WRRRBBW 。WRRRBBW -> WBBW
- 插入一个 'B' ，使桌面变为 WBBBW 。WBBBW -> WW
桌面上还剩着球，没有其他球可以插入。
```
示例 2：
```
输入：board = "WWRRBBWW", hand = "WRBRW"
输出：2
解释：要想清空桌面上的球，可以按下述步骤：
- 插入一个 'R' ，使桌面变为 WWRRRBBWW 。WWRRRBBWW -> WWBBWW
- 插入一个 'B' ，使桌面变为 WWBBBWW 。WWBBBWW -> WWWW -> empty
只需从手中出 2 个球就可以清空桌面。
```
示例 3：
```
输入：board = "G", hand = "GGGGG"
输出：2
解释：要想清空桌面上的球，可以按下述步骤：
- 插入一个 'G' ，使桌面变为 GG 。
- 插入一个 'G' ，使桌面变为 GGG 。GGG -> empty
只需从手中出 2 个球就可以清空桌面。
```
示例 4：
```
输入：board = "RBYYBBRRB", hand = "YRBGB"
输出：3
解释：要想清空桌面上的球，可以按下述步骤：
- 插入一个 'Y' ，使桌面变为 RBYYYBBRRB 。RBYYYBBRRB -> RBBBRRB -> RRRB -> B
- 插入一个 'B' ，使桌面变为 BB 。
- 插入一个 'B' ，使桌面变为 BBB 。BBB -> empty
只需从手中出 3 个球就可以清空桌面。 
```
提示：

* 1 <= board.length <= 16
* 1 <= hand.length <= 5
* board 和 hand 由字符 'R'、'Y'、'B'、'G' 和 'W' 组成
* 桌面上一开始的球中，不会有三个及三个以上颜色相同且连着的球

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/zuma-game
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路


c++整体代码如下：
```c++
class Solution {
public:
    int res = INT_MAX;
    set<pair<string, int>> visit;

    void eliminates(string& board)
    {
	    //用于判断插入球后是否能进行消除
	    int fast = 0;
	    int slow = 0;
	    for ( ;fast <= board.size();++fast)
	    {
		    if ( fast<board.size()&&board[fast] == board[slow]) continue;//快指针元素等于慢指针元素，此时移动快指针
		    if (fast - slow >= 3) {
			    //凑齐至少三个元素
			    board.erase(board.begin() + slow, board.begin() + fast);
			    fast = 0;//消除后将fast置为0，从头开始再次判断
		    }
		    slow = fast;
	    }
    }

    void trace(string& board, string& hand,int step)
    {
	    //回溯
	    if (step >= res) return;//当前步数大于最小步数，无需进行后续判断
	    if (visit.count({ board, step })) return;//此情况已经被判断过，返回
	    visit.insert({ board,step });
	    if (board.empty()) {
		    //board已经被全部消除，计算当前结果并返回
		    res = min(res, step);
		    return;
	    }
	    if (hand.empty()) {
		    //手里没有彩球可用
		    return;
	    }

	    for (int i = 0; i < board.size(); ++i){
		    for (int j = 0; j < hand.size(); ++j) {
			    char ch = hand[j];
			    hand.erase(hand.begin() + j);
			    string bd = board;
			    bd.insert(bd.begin() + i, ch);
                //判断board插入后能否被消除
                eliminates(bd);
			    trace(bd, hand, step + 1);
			    hand.insert(hand.begin() + j,ch);
		    }
	    }
    }
    int findMinStep(string board, string hand) {
	    trace(board, hand, 0);
	    return res == INT_MAX ? -1 : res;
    }
};
```