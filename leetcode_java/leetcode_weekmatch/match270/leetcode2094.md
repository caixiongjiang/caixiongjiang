## 编号2094：找出 3 位偶数(AC)

给你一个整数数组 digits ，其中每个元素是一个数字（0 - 9）。数组中可能存在重复元素。

你需要找出 所有 满足下述条件且 互不相同 的整数：

* 该整数由 digits 中的三个元素按 任意 顺序 依次连接 组成。
* 该整数不含 前导零
* 该整数是一个 偶数
例如，给定的 digits 是 [1, 2, 3] ，整数 132 和 312 满足上面列出的全部条件。

将找出的所有互不相同的整数按 递增顺序 排列，并以数组形式返回。

 

示例 1：
```
输入：digits = [2,1,3,0]
输出：[102,120,130,132,210,230,302,310,312,320]
解释：
所有满足题目条件的整数都在输出数组中列出。 
注意，答案数组中不含有 奇数 或带 前导零 的整数。
```
示例 2：
```
输入：digits = [2,2,8,8,2]
输出：[222,228,282,288,822,828,882]
解释：
同样的数字（0 - 9）在构造整数时可以重复多次，重复次数最多与其在 digits 中出现的次数一样。 
在这个例子中，数字 8 在构造 288、828 和 882 时都重复了两次。 
```
示例 3：
```
输入：digits = [3,7,5]
输出：[]
解释：
使用给定的 digits 无法构造偶数。
```
示例 4：
```
输入：digits = [0,2,0,0]
输出：[200]
解释：
唯一一个不含 前导零 且满足全部条件的整数是 200 。
```
示例 5：
```
输入：digits = [0,0,0]
输出：[]
解释：
构造的所有整数都会有 前导零 。因此，不存在满足题目条件的整数。 
```
提示：

* 3 <= digits.length <= 100
* 0 <= digits[i] <= 9

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/finding-3-digit-even-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 暴力枚举
初步想法就是暴力枚举，具体做法：
* 1.根据每位数字的特性，将所有能组成数字都列举出来
* 2.将数字的大小作为下标，将它标记为已经访问过的数字，vis数组的值变为1
* 3.从小到大遍历vis数组，每次遇到不为0的值时，都将下标存入结果数组中（这样从小到大遍历就保证了得到的结果也是从小到大排序的）。


代码如下：
```c++
class Solution {
public:
    vector<int> findEvenNumbers(vector<int>& v){
        int n = v.size();
        vector<int> vis(1000);//标记当前组成的数字是否已经访问过
        for(int i = 0; i < n; i++){ 
            if(v[i])
            for(int j = 0; j < n; j++){ 
                if(j != i)
                for(int k = 0; k < n; k++){ 
                    if(j != k and k != i and v[k] % 2 == 0){
                        vis[v[i] * 100 + v[j] * 10 + v[k]] = 1;
                    }
                }
            }
        }
        vector<int> res;
        for (int i = 0; i < 1000; i++){
            if (vis[i]) res.push_back(i);
        }
        return res;
    }
};
```


### 哈希表

先将所有的digits中的数字遍历并存入哈希表中。

求的是三位数，并不多，那就将所有**三位数的偶数**遍历一遍，将他们的每位数都求出来，存入哈希表中，再将哈希表中的对应数字的哈希值减1。

如果对应三个数字上的哈希值都还大于0，说明digits数组可以组成这个三位数。

注意：判断完就将三个数字的哈希值复原，进行下一轮的判断（digits数组可以重复使用）


代码如下：
```c++
class Solution {
    int cnt[10];

public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        for (int x : digits) cnt[x]++;
        vector<int> ans;
        for (int i = 100; i < 999; i += 2) {
            int a = i % 10, b = i / 10 % 10, c = i / 100;
            cnt[a]--; cnt[b]--; cnt[c]--;
            if (cnt[a] >= 0 && cnt[b] >= 0 && cnt[c] >= 0) ans.push_back(i);
            cnt[a]++; cnt[b]++; cnt[c]++;
        }
        return ans;
    }
};
```