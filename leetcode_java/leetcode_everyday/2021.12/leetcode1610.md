## 编号1610:可见点的最大数目

给你一个点数组 points 和一个表示角度的整数 angle ，你的位置是 location ，其中 location = [posx, posy] 且 points[i] = [xi, yi] 都表示 X-Y 平面上的整数坐标。

最开始，你面向东方进行观测。你 不能 进行移动改变位置，但可以通过 自转 调整观测角度。换句话说，posx 和 posy 不能改变。你的视野范围的角度用 angle 表示， 这决定了你观测任意方向时可以多宽。设 d 为你逆时针自转旋转的度数，那么你的视野就是角度范围 [d - angle/2, d + angle/2] 所指示的那片区域。

对于每个点，如果由该点、你的位置以及从你的位置直接向东的方向形成的角度 位于你的视野中 ，那么你就可以看到它。

同一个坐标上可以有多个点。你所在的位置也可能存在一些点，但不管你的怎么旋转，总是可以看到这些点。同时，点不会阻碍你看到其他点。

返回你能看到的点的最大数目。

 

示例 1：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/04/89a07e9b-00ab-4967-976a-c723b2aa8656.png)

```
输入：points = [[2,1],[2,2],[3,3]], angle = 90, location = [1,1]
输出：3
解释：阴影区域代表你的视野。在你的视野中，所有的点都清晰可见，尽管 [2,2] 和 [3,3]在同一条直线上，你仍然可以看到 [3,3] 。
```
示例 2：
```
输入：points = [[2,1],[2,2],[3,4],[1,1]], angle = 90, location = [1,1]
输出：4
解释：在你的视野中，所有的点都清晰可见，包括你所在位置的那个点。
```
示例 3：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/04/5010bfd3-86e6-465f-ac64-e9df941d2e49.png)

```
输入：points = [[1,0],[2,1]], angle = 13, location = [1,1]
输出：1
解释：如图所示，你只能看到两点之一。 
```
提示：

* 1 <= points.length <= 105
* points[i].length == 2
* location.length == 2
* 0 <= angle < 360
* 0 <= posx, posy, xi, yi <= 100


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-number-of-visible-points
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

首先明确 :

* Angle 是 角度制 的 , 而反三角函数求解出来的角度是 弧度制 的

弧度 与 角度 的关系 :
```
1) 角度转换为弧度公式： 弧度 = 角度÷180×π
2) 弧度转换为角度公式： 角度 = 弧度×180÷π
```
因为涉及角度的问题 , 为了统一
那么我们可以把**观察点的水平东方向**作为**xy轴坐标的x轴**来把**每一个点与观察点的角度**表示出来

![avater](https://pic.leetcode-cn.com/1638759814-YhHAna-image.png)

**此时需要注意 第三第四象限的情况需要对 θ 做相应的处理**
```c++
// x1,y1 为观察点
double CalAngle(int& x1,int& y1,int& x2,int& y2) {
    // 计算 v = (x1 - x2,y1 - y2) 与水平线的角度
    double dx = x2 - x1 , dy = y2 - y1;
    double theta = acos(dx / sqrt(dx * dx + dy * dy));
    theta = theta / PI * Base;
    if(dy < 0) {
        // 此时说明在 3,4 象限
        theta = 2 * Base - theta;
    }
    return theta;
}
```

然后对每一个点的对应角度进行排序

用一个 大小为**Angle**的窗口 来计算窗口中的最大点数即可

**题目好像卡了下 double 的精度问题**特别是**Angle == 0**的情况 需要加入**EPS**来解决

此时也要注意**窗口同时包含第一象限和第四象限**的情况
```c++
// 然后判断包含第一象限 和 第四象限 的情况
r = 0;// 右边界重新回到第一个点
h[r] += 360;// 又转了一圈 需要 + 360° 
while(l < n && r < l) {
    if(h[r] - h[l] > angle + EPS) {
        res = max(res,r + n - l);
        while(l < n && h[r] - h[l] > angle) l ++;
    } else {
        r ++; 
        if(r < n) h[r] += 360;
    } 
}
if(l == r) res = h.size();// 说明把全部点都包含了
```

整体代码如下：
```c++
const double PI = 3.1415926535;
const double Base = 180;// 一个 PI 表示的角度
const double EPS = 1e-6;
class Solution {
public:
    unordered_map<int,double> point2Angle;// 每一个点 和 观看位置的水平位置的连线的角度
    double CalAngle(int& x1,int& y1,int& x2,int& y2) {
        // 计算 v = (x1 - x2,y1 - y2) 与水平线的角度
        double dx = x2 - x1 , dy = y2 - y1;
        double theta = acos(dx / sqrt(dx * dx + dy * dy));
        theta = theta / PI * Base;
        if(dy < 0) {
            // 此时说明在 3,4 象限
            theta = 2 * Base - theta;
        }
        return theta;
    }
    int visiblePoints(vector<vector<int>>& ps, int angle, vector<int>& pos) {
        // 用反三角函数即可 
        // v1 * v2 = cos<v1,v2> * |v1| * |v2|
        // acos<v1,v2> = v1 * v2 / |v1| / |v2|
        int res = 0;
        int add = 0;// 和观看点重合的点
        vector<double> h;
        for(auto& i : ps) {
            if(i[0] == pos[0] && i[1] == pos[1]) add ++;
            else {
                h.push_back(CalAngle(pos[0],pos[1],i[0],i[1]));
            }
        }
        if(h.empty()) return add;
        sort(h.begin(),h.end());// 排序
        if(h.back() - h[0] <= angle + EPS) return h.size() + add;// 小剪枝
        // 滑动窗口解决
        // 首先 1,4 象限的分开讨论 
        int l = 0;
        int r = 0;
        int n = h.size();
        while(r < n) {
            if(h[r] - h[l] > angle + EPS) {
                res = max(res,r - l);
                while(h[r] - h[l] >= angle + EPS) l ++;
            } else r ++;
        }
        res = max(res,r - l);
        // 然后判断包含第一象限 和 第四象限 的情况
        r = 0;// 右边界重新回到第一个点
        h[r] += 360;// 又转了一圈 需要 + 360° 
        while(l < n && r < l) {
            if(h[r] - h[l] > angle + EPS) {
                res = max(res,r + n - l);
                while(l < n && h[r] - h[l] > angle) l ++;
            } else {
                r ++; 
                if(r < n) h[r] += 360;
            } 
        }
        if(l == r) res = h.size();// 说明把全部点都包含了
        return res + add;
    }
};
```