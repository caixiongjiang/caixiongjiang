## 编号1154:一年中的第几天

给你一个字符串 date ，按 YYYY-MM-DD 格式表示一个 现行公元纪年法 日期。请你计算并返回该日期是当年的第几天。

通常情况下，我们认为 1 月 1 日是每年的第 1 天，1 月 2 日是每年的第 2 天，依此类推。每个月的天数与现行公元纪年法（格里高利历）一致。

 

示例 1：
```
输入：date = "2019-01-09"
输出：9
```
示例 2：
```
输入：date = "2019-02-10"
输出：41
```
示例 3：
```
输入：date = "2003-03-01"
输出：60
```
示例 4：
```
输入：date = "2004-03-01"
输出：61 
```
提示：

* date.length == 10
* date[4] == date[7] == '-'，其他的 date[i] 都是数字
* date 表示的范围从 1900 年 1 月 1 日至 2019 年 12 月 31 日

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/day-of-the-year
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

这题主要的考察点有两个：

1.字符串数字转换为int数字

2.闰年的判断

我写的代码比较长，主要是第一步的代码多

代码如下：
```c++
class Solution {
public:
    int dayOfYear(string date) {
        string year, month, day;
        for(int i = 0; i < date.size(); i++){
            if(i <= 3) year += date[i];
            if(i >= 5 && i <= 6) month += date[i];
            if(i >= 8) day += date[i];
        }
        int years = 0, months = 0, days = 0;
        years = (year[0] - '0') * 1000 + (year[1] - '0') * 100 +
         (year[2] - '0') * 10 + (year[3] - '0');
        months = (month[0] - '0') * 10 + (month[1] - '0');
        days = (day[0] - '0') * 10 + (day[1] - '0');
        //cout << years << months << days << endl;
        int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        //如果是闰年就对2月份进行改变
        if(years % 400 == 0 || (years % 4 == 0 && years % 100 != 0)){
            month_days[1]++;
        }
        
        int ans = 0;
        for(int i = 0; i < months - 1; i++){
            ans += month_days[i];
        }
        ans += days;
        return ans;
    }
};
```


官方的代码用了c++的库函数，我不了解，三行代码找出了年月日的int数字。

代码如下：
```c++
class Solution {
public:
    int dayOfYear(string date) {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));

        int amount[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
            ++amount[1];
        }

        int ans = 0;
        for (int i = 0; i < month - 1; ++i) {
            ans += amount[i];
        }
        return ans + day;
    }
};
```

看了一下结果，时间和空间时一模一样的，我怀疑stoi底层代码与我的方法的代码相差不大。哈哈哈！！！