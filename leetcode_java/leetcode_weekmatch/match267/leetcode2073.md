## 编号：买票需要的时间(AC)

有 n 个人前来排队买票，其中第 0 人站在队伍 最前方 ，第 (n - 1) 人站在队伍 最后方 。

给你一个下标从 0 开始的整数数组 tickets ，数组长度为 n ，其中第 i 人想要购买的票数为 tickets[i] 。

每个人买票都需要用掉 恰好 1 秒 。一个人 一次只能买一张票 ，如果需要购买更多票，他必须走到  队尾 重新排队（瞬间 发生，不计时间）。如果一个人没有剩下需要买的票，那他将会 离开 队伍。

返回位于位置 k（下标从 0 开始）的人完成买票需要的时间（以秒为单位）。

 

示例 1：
```
输入：tickets = [2,3,2], k = 2
输出：6
解释： 
- 第一轮，队伍中的每个人都买到一张票，队伍变为 [1, 2, 1] 。
- 第二轮，队伍中的每个都又都买到一张票，队伍变为 [0, 1, 0] 。
位置 2 的人成功买到 2 张票，用掉 3 + 3 = 6 秒。
```
示例 2：
```
输入：tickets = [5,1,1,1], k = 0
输出：8
解释：
- 第一轮，队伍中的每个人都买到一张票，队伍变为 [4, 0, 0, 0] 。
- 接下来的 4 轮，只有位置 0 的人在买票。
位置 0 的人成功买到 5 张票，用掉 4 + 1 + 1 + 1 + 1 = 8 秒。
```

提示：

* n == tickets.length
* 1 <= n <= 100
* 1 <= tickets[i] <= 100
* 0 <= k < n

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/time-needed-to-buy-tickets
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

整体解法就是进行几轮递减的问题：<span style="color:green">取决于tickets[k]值的大小！</span>

这种解法需要注意的是，**当这一轮的tickets[k]的值已经为0时，在他前面排队的人就不能继续计算时间了，在上一轮结束时计时就结束了！**

代码如下：
```c++
class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int n = tickets[k];
        int time = 0;
        while(n > 0){
            for(int i = 0; i < tickets.size(); i++){
                if(tickets[k] == 0) break;
                if(tickets[i] > 0){
                    tickets[i]--;
                    time++;
                    }
                }
            n--;
        }
        return time;
    }
};
```


附上竞赛前几名大佬的解法（果然时间复杂度低好多）

```c++
class Solution {
    int a[100];
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        copy(tickets.begin(),tickets.end(),a);
        int n=tickets.size(),i,t=0;
        queue<int> q;
        for(i=0;i<n;i++)q.push(i);
        while(!q.empty())
        {
            t++;
            i=q.front();
            q.pop();
            if(--a[i])q.push(i);
            else if(i==k)break;
        }
        return t;
    }
};
```