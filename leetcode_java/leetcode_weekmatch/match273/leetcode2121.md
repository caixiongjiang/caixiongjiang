## 编号2121：相同元素的间隔之和（叉）

给你一个下标从 0 开始、由 n 个整数组成的数组 arr 。

arr 中两个元素的 间隔 定义为它们下标之间的 绝对差 。更正式地，arr[i] 和 arr[j] 之间的间隔是 |i - j| 。

返回一个长度为 n 的数组 intervals ，其中 intervals[i] 是 arr[i] 和 arr 中每个相同元素（与 arr[i] 的值相同）的 间隔之和 。

注意：|x| 是 x 的绝对值。

 

示例 1：
```
输入：arr = [2,1,3,1,2,3,3]
输出：[4,2,7,2,4,4,5]
解释：
- 下标 0 ：另一个 2 在下标 4 ，|0 - 4| = 4
- 下标 1 ：另一个 1 在下标 3 ，|1 - 3| = 2
- 下标 2 ：另两个 3 在下标 5 和 6 ，|2 - 5| + |2 - 6| = 7
- 下标 3 ：另一个 1 在下标 1 ，|3 - 1| = 2
- 下标 4 ：另一个 2 在下标 0 ，|4 - 0| = 4
- 下标 5 ：另两个 3 在下标 2 和 6 ，|5 - 2| + |5 - 6| = 4
- 下标 6 ：另两个 3 在下标 2 和 5 ，|6 - 2| + |6 - 5| = 5
```
示例 2：
```
输入：arr = [10,5,10,10]
输出：[5,0,3,4]
解释：
- 下标 0 ：另两个 10 在下标 2 和 3 ，|0 - 2| + |0 - 3| = 5
- 下标 1 ：只有这一个 5 在数组中，所以到相同元素的间隔之和是 0
- 下标 2 ：另两个 10 在下标 0 和 3 ，|2 - 0| + |2 - 3| = 3
- 下标 3 ：另两个 10 在下标 0 和 2 ，|3 - 0| + |3 - 2| = 4 
```
提示：

* n == arr.length
* 1 <= n <= 10^5
* 1 <= arr[i] <= 10^5


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/intervals-between-identical-elements
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### map（我的代码）（超时）

暴力解法：
遍历一遍，将其插入map容器中，再用两个for循环将其相等的两个下标差加入答案中。

```c++
class Solution {
public:
    vector<long long> getDistances(vector<int>& arr) {
        vector<long long> ret;
        map<long long, int> mp;
        long long n = arr.size();
        for(long long i = 0; i < n; i++){
            mp.insert(make_pair(i, arr[i]));   
        }
        for(long long i = 0; i < n; i++){
            long long ans = 0;
            for(long long j = 0; j < n; j++){
                if(mp[j] == arr[i]){
                    ans += abs(j - i);
                }
            }
            ret.push_back(ans);
        }
        return ret;
    }
};
```

这份代码死在一个长度非常非常长的arr数组示例，成功超时！

### map优化

因为map不允许相同的key值的pair对组插入，所以我将可能相同的arr[i]作为value值插入，下标作为key值，事实说明这种做法效率太低。

大佬优化的做法为将arr[i]和等于arr[i]的不同坐标放入一个vector作为value值插入map，这样key值不会因为重复而无法插入，后面的判断逻辑就差不多了。具体看注释！

代码如下：
```c++
class Solution {
    //<数组值，等于该key值的数组下标集合>
    map<int, vector<int>> mp;
public:
    vector<long long> getDistances(vector<int>& arr) {
        int n = arr.size();
        for(int i = 0; i < n; i++) mp[arr[i]].push_back(i);
        vector<long long> ret(n);//结果数组
        //auto这里其实迭代器类型，其实为 map<int, vector<int>>::iterator
        //作用和指针差不多
        for(auto it = mp.begin(); it != mp.end(); it++){
            //将key值对应的数组下标暂存如vec数组中
            vector<int> &vec = it->second;
            int m = vec.size();
            long long ans = 0;
            /*因为插入map时是按照下标递增的顺序进行插入的，
            所以vec的第一个元素一定是插入的第一个数*/
            for(int i = 1; i < m; i++) ans += vec[i] - vec[0];
            //将得到的结果插入ret数组
            for(int i = 0; ; i++){
                ret[vec[i]] = ans;
                if(i + 1 == m) break;//跳出循环条件
                //值相同的下标更新不同的ans
                //此部分需要画图感受!!!!!
                long long d = vec[i + 1] - vec[i];
                //下标左边多加(i + 1)段上一轮循环的vec[i + 1] - vec[i]
                ans += (i + 1) * d;
                //下标右边多减(m - (i + 1))段上一轮循环的vec[i + 1] - vec[i]
                ans -= (m - (i + 1)) * d; 
            }
        }
        return ret;
    }
};
```