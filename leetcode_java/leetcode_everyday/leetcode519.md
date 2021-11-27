## 编号519：随机翻转矩阵

给你一个 m x n 的二元矩阵 matrix ，且所有值被初始化为 0 。请你设计一个算法，随机选取一个满足 matrix[i][j] == 0 的下标 (i, j) ，并将它的值变为 1 。所有满足 matrix[i][j] == 0 的下标 (i, j) 被选取的概率应当均等。

尽量最少调用内置的随机函数，并且优化时间和空间复杂度。

实现 Solution 类：

* Solution(int m, int n) 使用二元矩阵的大小 m 和 n 初始化该对象
* int[] flip() 返回一个满足 matrix[i][j] == 0 的随机下标 [i, j] ，并将其对应格子中的值变为 1
* void reset() 将矩阵中所有的值重置为 0
 

示例：
```
输入
["Solution", "flip", "flip", "flip", "reset", "flip"]
[[3, 1], [], [], [], [], []]
输出
[null, [1, 0], [2, 0], [0, 0], null, [2, 0]]

解释
Solution solution = new Solution(3, 1);
solution.flip();  // 返回 [1, 0]，此时返回 [0,0]、[1,0] 和 [2,0] 的概率应当相同
solution.flip();  // 返回 [2, 0]，因为 [1,0] 已经返回过了，此时返回 [2,0] 和 [0,0] 的概率应当相同
solution.flip();  // 返回 [0, 0]，根据前面已经返回过的下标，此时只能返回 [0,0]
solution.reset(); // 所有值都重置为 0 ，并可以再次选择下标返回
solution.flip();  // 返回 [2, 0]，此时返回 [0,0]、[1,0] 和 [2,0] 的概率应当相同 
```
提示：

* 1 <= m, n <= 104
* 每次调用flip 时，矩阵中至少存在一个值为 0 的格子。
* 最多调用 1000 次 flip 和 reset 方法。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/random-flip-matrix
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 数组映射
代码如下：

```c++
class Solution {
public:
    Solution(int m, int n) {
        this->m = m;
        this->n = n;
        this->total = m * n;
        srand(time(nullptr));
    }
    
    vector<int> flip() {
        int x = rand() % total;
        vector<int> ans;
        total--;   
        // 查找位置 x 对应的映射
        if (map.count(x)) {
            ans = {map[x] / n, map[x] % n};
        } else {
            ans = {x / n, x % n};
        }
        // 将位置 x 对应的映射设置为位置 total 对应的映射
        if (map.count(total)) {
            map[x] = map[total];
        } else {
            map[x] = total;
        }
        return ans;
    }
    
    void reset() {
        total = m * n;
        map.clear();
    }
private:
    int m;
    int n;
    int total;
    unordered_map<int, int> map;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(m, n);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */
```

### 分块

代码如下：
```c++
class Solution {
public:
    Solution(int m, int n) {
        this->m = m;
        this->n = n;
        total = m * n;
        bucketSize = sqrt(m * n);
        for (int i = 0; i < total; i += bucketSize) {
            buckets.push_back({});
        }
        srand(time(nullptr));
    }

    vector<int> flip() {
        int x = rand() % total;
        int sumZero = 0;
        int curr = 0;
        total--;

        for (auto & bucket : buckets) {
            if (sumZero + bucketSize - bucket.size() > x) {
                for (int i = 0; i < bucketSize; ++i) {
                    if (!bucket.count(curr + i)) {
                        if (sumZero == x) {
                            bucket.emplace(curr + i);
                            return {(curr + i) / n, (curr + i) % n};
                        } 
                        sumZero++;
                    }
                }
            }
            curr += bucketSize;
            sumZero += bucketSize - bucket.size();
        }
        
        return {};
    }

    void reset() {
        for (auto & bucket : buckets) {
            bucket.clear();
        }
        total = m * n;
    }
private:
    int m;
    int n;
    int bucketSize;
    int total;
    vector<unordered_set<int>> buckets;
};
```