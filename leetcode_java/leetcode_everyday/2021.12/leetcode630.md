## 编号630：课程表Ⅲ

这里有 n 门不同的在线课程，按从 1 到 n 编号。给你一个数组 courses ，其中 courses[i] = [durationi, lastDayi] 表示第 i 门课将会 持续 上 durationi 天课，并且必须在不晚于 lastDayi 的时候完成。

你的学期从第 1 天开始。且不能同时修读两门及两门以上的课程。

返回你最多可以修读的课程数目。

示例 1：
```
输入：courses = [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
输出：3
解释：
这里一共有 4 门课程，但是你最多可以修 3 门：
首先，修第 1 门课，耗费 100 天，在第 100 天完成，在第 101 天开始下门课。
第二，修第 3 门课，耗费 1000 天，在第 1100 天完成，在第 1101 天开始下门课程。
第三，修第 2 门课，耗时 200 天，在第 1300 天完成。
第 4 门课现在不能修，因为将会在第 3300 天完成它，这已经超出了关闭日期。
```
示例 2：
```
输入：courses = [[1,2]]
输出：1
```
示例 3：
```
输入：courses = [[3,2],[4,3]]
输出：0
```
提示:

* 1 <= courses.length <= 104
* 1 <= durationi, lastDayi <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/course-schedule-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

首先会想到贪心，将自身不符合课程要求的课程剪枝之后，按照时间顺序对二维数组进行排序，按照时间顺序进行排课（贪心），直接一个for循环进行计数。结果发现只能通过36个示例，说明这种贪心不成立。

错误代码如下：
```c++
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        int time = 0;
        int n = courses.size();
        int cnt = 0;
        sort(courses.begin(), courses.end(), [](const vector<int> &a, const vector<int> &b) { return a[0] < b[0]; });
        for(int i = 0; i < n; i++){
            if(courses[i][0] > courses[i][1]) continue;
            if(time + courses[i][0] <= courses[i][1]){
                time += courses[i][0];
                cnt++;
            }
        }
        return cnt;
    }
};
```

