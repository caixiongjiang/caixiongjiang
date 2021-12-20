## 编号475:供暖器

冬季已经来临。 你的任务是设计一个有固定加热半径的供暖器向所有房屋供暖。

在加热器的加热半径范围内的每个房屋都可以获得供暖。

现在，给出位于一条水平线上的房屋 houses 和供暖器 heaters 的位置，请你找出并返回可以覆盖所有房屋的最小加热半径。

说明：所有供暖器都遵循你的半径标准，加热的半径也一样。

 

示例 1:
```
输入: houses = [1,2,3], heaters = [2]
输出: 1
解释: 仅在位置2上有一个供暖器。如果我们将加热半径设为1，那么所有房屋就都能得到供暖。
```
示例 2:
```
输入: houses = [1,2,3,4], heaters = [1,4]
输出: 1
解释: 在位置1, 4上有两个供暖器。我们需要将加热半径设为1，这样所有房屋就都能得到供暖。
```
示例 3：
```
输入：houses = [1,5], heaters = [2]
输出：3 
```
提示：

* 1 <= houses.length, heaters.length <= 3 * 10^4
* 1 <= houses[i], heaters[i] <= 10^9

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/heaters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 排序+二分查找

为了使供暖器可以覆盖所有房屋且供暖器的加热半径最小，对于每个房屋，应该选择离该房屋最近的供暖器覆盖该房屋，最近的供暖器和房屋的距离即为该房屋需要的供暖器的最小加热半径。所有房屋需要的供暖器的最小加热半径中的最大值即为可以覆盖所有房屋的最小加热半径。

为了得到距离每个房屋最近的供暖器，可以将供暖器数组 heaters 排序，然后通过二分查找得到距离最近的供暖器。

具体步骤：

1.对heaters数组排序

2.对每个house进行统计需要的半径：具体做法为找到house右边的供暖器和左边的供暖器离house的距离的最小值，就求出了每个house需要的最小半径。

3.ans就为每个house需要最小半径的最大值。

代码如下：
```c++
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int ans = 0;
        sort(heaters.begin(), heaters.end());
        for(int house : houses){
            /*
            i为每个house左边的供暖器，j为每个house右边的供暖器
            */
            //在heaters数组中查找第一个大于house的数字，并返回下标
            int j = upper_bound(heaters.begin(), heaters.end(), house) - heaters.begin();
            int i = j - 1;
            int rightDistant = j >= heaters.size() ? INT_MAX : heaters[j] - house;
            int leftDistant = i < 0 ? INT_MAX : house - heaters[i];
            int curDistant = min(rightDistant, leftDistant);
            ans = max(ans, curDistant);
        }
        return ans;
    }
};
```

### 排序+双指针

总体思路和第一种方法一样，只是使用的方法不同，上述为二分查找，这里使用双指针的方法。


代码如下：
```c++
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        
        //插入两个数是为了防止cur指针溢出，并且不影响每个house最近供暖器距离的判断！
        heaters.insert(heaters.begin(), INT_MIN);
        heaters.emplace_back(INT_MAX);  

        long long r = 0;
        int n = heaters.size();
        int cur = 0;
        //i为houses上的指针，cur是heaters上的指针
        for(int i = 0; i < houses.size(); i++){
            while(cur < n + 2){
                //寻找第一个在houses[i]右边的供暖器的位置（下标）
                if(heaters[cur] >= houses[i]) break;
                cur++;
            }
            //使用cur代表房子右边的供暖器的指针，cur - 1代表房子左边的供暖器的指针
            r = max(r, min((long long)heaters[cur] - houses[i], (long long)houses[i] - heaters[cur - 1]));
        }
        return r;
    }
};
```