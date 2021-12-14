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

### 贪心+优先队列

#### 解题思路
大家赶DDL的时候怎么排序的呢？ 肯定是优先赶最紧急的吧；这就是这道题的核心思路。

首先我们可以对所有课程按照ddl升序排列，那我们就可以通过遍历尝试优先修读最早截止的课程。

但每门课修读所需要的时长又是不一样的，所以在肯定有课已经要超过ddl的时候，那我们就会选择修读时间更短的课程优先修读；这样我们修读下一门课的时候就会有更多的时间了。

#### 举个栗子
假设duration数组是这样的 大学物理 [2, 4] 高等数学 [5, 7] 线性代数 [3, 3]

那么，按照策略，我们会先尝试修读线性代数。 然后尝试修读大学物理，这个时候我们发现竟然修了线性代数之后就修不了大学物理了；只能放弃；转而修高等数学发现也没有足够的时间了。

那合理的做法是什么呢？ 就是我们这个时候需要放弃线性代数，因为线性代数和大学物理的权重是没有区别的，既然两者只能修一门，我们应该让当前累计花费的时间更少。

大学物理虽然ddl比线性代数更晚，但它修读的时间也更短，如果已经要放弃一门课了，我们会放弃修读时间更长的。

#### 总结

所以整体思路就是： 
* 优先修读dll近的 放弃的时候则放弃修读时间长的 给之后的课程留更多的时间。
* 可以用优先队列模拟这个过程；堆顶放修读时间最长的课程；按照ddl升序排列依次修读。
    * 如果可以修读，更新总修读时间。
    * 如果不可修读，看花费最长时间的课程是哪门，我们把它替换掉即可。

代码如下：
```c++
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(), [](const auto& a, const auto& b) { return a[1] < b [1];});

        priority_queue<int> q;
        int day = 0;
        for (auto c: courses) {
            if (day + c[0] <= c[1]) {
                day += c[0];
                q.push(c[0]);
                continue;
            }
            if (!q.empty() && q.top() > c[0]) {
                day -= q.top();
                day += c[0];
                q.pop();
                q.push(c[0]);
            } 
            
        }

        return q.size();
    }
};
```

