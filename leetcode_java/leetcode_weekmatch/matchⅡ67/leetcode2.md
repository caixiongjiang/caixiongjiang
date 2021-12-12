## 编号：适合打劫银行的日子（×）

你和一群强盗准备打劫银行。给你一个下标从 0 开始的整数数组 security ，其中 security[i] 是第 i 天执勤警卫的数量。日子从 0 开始编号。同时给你一个整数 time 。

如果第 i 天满足以下所有条件，我们称它为一个适合打劫银行的日子：

第 i 天前和后都分别至少有 time 天。
第 i 天前连续 time 天警卫数目都是非递增的。
第 i 天后连续 time 天警卫数目都是非递减的。
更正式的，第 i 天是一个合适打劫银行的日子当且仅当：security[i - time] >= security[i - time + 1] >= ... >= security[i] <= ... <= security[i + time - 1] <= security[i + time].

请你返回一个数组，包含 所有 适合打劫银行的日子（下标从 0 开始）。返回的日子可以 任意 顺序排列。

 

示例 1：
```
输入：security = [5,3,3,3,5,6,2], time = 2
输出：[2,3]
解释：
第 2 天，我们有 security[0] >= security[1] >= security[2] <= security[3] <= security[4] 。
第 3 天，我们有 security[1] >= security[2] >= security[3] <= security[4] <= security[5] 。
没有其他日子符合这个条件，所以日子 2 和 3 是适合打劫银行的日子。
```
示例 2：
```
输入：security = [1,1,1,1,1], time = 0
输出：[0,1,2,3,4]
解释：
因为 time 等于 0 ，所以每一天都是适合打劫银行的日子，所以返回每一天。
```
示例 3：
```
输入：security = [1,2,3,4,5,6], time = 2
输出：[]
解释：
没有任何一天的前 2 天警卫数目是非递增的。
所以没有适合打劫银行的日子，返回空数组。
```
示例 4：
```
输入：security = [1], time = 5
输出：[]
解释：
没有日子前面和后面有 5 天时间。
所以没有适合打劫银行的日子，返回空数组。 
```
提示：

* 1 <= security.length <= 105
* 0 <= security[i], time <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-good-days-to-rob-the-bank
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

维护两个滑动的窗口，窗口的大小都为time:

* 初始化两个窗口，第一个为【1，time】，第二个为【time + 1，2 * time】，中间重叠的点为p。
* 初始化o1和o2的值，分别代表前一个窗口递增的数量和第二个窗口递减的数量。
* 随着p的遍历，滑动窗口，分别维护两个窗口o1和o2的值。
* 将所有o1和o2值都为0的下标都记录下来计入结果数组。

代码如下：
```c++
class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n = security.size();
        vector<int> ret;
        //剪枝1
        if(2 * time + 1 > n) return ret;
        //剪枝2
        if(time == 0){
            for(int i = 0; i < n; i++){
                ret.emplace_back(i);
            }
            return ret;
        }
        int o1 = 0, o2 = 0;//前面递增和后面递减的个数
        //初始化o1 和o2
        for(int i = 1; i <= time; i++){
            if(security[i] > security[i - 1]) o1++;
        }
        for(int i = time + 1; i <= 2 * time; i++){
            if(security[i] < security[i - 1]) o2++;
        }
        for(int p = time, i = 0, j = 2 * time;; p++){
            //如果左窗口递减数量和右窗口递增数量都为0时，此时适合打劫银行
            if(!o1 && !o2) ret.emplace_back(p);
            if(j + 1 == n) break;//防止指针溢出
            //维护左边窗口的递减数量的情况
            if(security[i] < security[i + 1]) o1--;
            if(security[p] < security[p + 1]) o1++;
            //维护右边窗口的递增数量的情况
            if(security[p] > security[p + 1]) o2--;
            if(security[j] > security[j + 1]) o2++;
            i++;
            j++;
        }
        return ret;
    }
};

````