## 编号1035：不相交的线

在两条独立的水平线上按给定的顺序写下 nums1 和 nums2 中的整数。

现在，可以绘制一些连接两个数字 nums1[i] 和 nums2[j] 的直线，这些直线需要同时满足满足：

 nums1[i] == nums2[j]
且绘制的直线不与任何其他连线（非水平线）相交。
**请注意，连线即使在端点也不能相交：每个数字只能属于一条连线。**

以这种方法绘制线条，并返回可以绘制的最大连线数。

 

示例 1：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/04/28/142.png)
```
输入：nums1 = [1,4,2], nums2 = [1,2,4]
输出：2
解释：可以画出两条不交叉的线，如上图所示。 
但无法画出第三条不相交的直线，因为从 nums1[1]=4 到 nums2[2]=4 的直线将与从 nums1[2]=2 到 nums2[1]=2 的直线相交。
```
示例 2：
```
输入：nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
输出：3
```
示例 3：
```
输入：nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
输出：2 
```
提示：

* 1 <= nums1.length <= 500
* 1 <= nums2.length <= 500
* 1 <= nums1[i], nums2[i] <= 2000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/uncrossed-lines
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

绘制一些连接两个数字 A[i] 和 B[j] 的直线，只要 A[i] == B[j]，且直线不能相交！

直线不能相交，这就是说明在字符串A中 找到一个与字符串B相同的子序列，且这个子序列不能改变相对顺序，只要相对顺序不改变，链接相同数字的直线就不会相交。

拿示例一A = [1,4,2], B = [1,2,4]为例，相交情况如图：

![avater](https://camo.githubusercontent.com/45bec9ccb3bcc6aa54c7170708935ecd9902383721dfe492d22a4eb953fde598/68747470733a2f2f636f64652d7468696e6b696e672d313235333835353039332e66696c652e6d7971636c6f75642e636f6d2f706963732f32303231303931343134353135382e706e67)

<span style="color:green">其实也就是说A和B的最长公共子序列是[1,4]，长度为2。</span> 这个公共子序列指的是相对顺序不变（即数字4在字符串A中数字1的后面，那么数字4也应该在字符串B数字1的后面）

这么分析完之后,可以发现：**本题说是求绘制的最大连线数，其实就是求两个字符串的最长公共子序列的长度！**

那么本题就和我们刚刚讲过的这道题目[动态规划：1143.最长公共子序列](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode1143.md)就是一样一样的了。

一样到什么程度呢？ 把字符串名字改一下，其他代码都不用改，直接copy过来就行了。

本题代码如下：
```c++
class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        vector<vector<int>> dp(A.size() + 1, vector<int>(B.size() + 1, 0));
        for (int i = 1; i <= A.size(); i++) {
            for (int j = 1; j <= B.size(); j++) {
                if (A[i - 1] == B[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[A.size()][B.size()];
    }
};
```