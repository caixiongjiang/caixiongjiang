## 编号677：键值映射

实现一个 MapSum 类，支持两个方法，insert 和 sum：

* MapSum() 初始化 MapSum 对象
* void insert(String key, int val) 插入 key-val 键值对，字符串表示键 key ，整数表示值 val 。如果键 key 已经存在，那么原来的键值对将被替代成新的键值对。
* int sum(string prefix) 返回所有以该前缀 prefix 开头的键 key 的值的总和。
 

示例：
```
输入：
["MapSum", "insert", "sum", "insert", "sum"]
[[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
输出：
[null, null, 3, null, 5]

解释：
MapSum mapSum = new MapSum();
mapSum.insert("apple", 3);  
mapSum.sum("ap");           // return 3 (apple = 3)
mapSum.insert("app", 2);    
mapSum.sum("ap");           // return 5 (apple + app = 3 + 2 = 5)
``` 

提示：

* 1 <= key.length, prefix.length <= 50
* key 和 prefix 仅由小写英文字母组成
* 1 <= val <= 1000
* 最多调用 50 次 insert 和 sum

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/map-sum-pairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 暴力求解
我们将所有的key-val 键值进行存储，每次需要搜索给定的前缀prefix时，我们依次搜索所有的键值。如果键值包含给定的前缀，则我们将其val进行相加，返回所有符合要求的val的和。

整体代码如下：
```c++
class MapSum {
public:
    MapSum() {
        
    }
    
    void insert(string key, int val) {
        cnt[key] = val;
    }
    
    int sum(string prefix) {
        int res = 0;
        for(auto & [key,val] : cnt){
            if(key.substr(0, prefix.size()) == prefix){
                res += val;
            }
        }
        return res;
    }
private:
    unordered_map<string, int> cnt;
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
```

### 前缀哈希映射

我们可以用哈希表存储所有可能前缀的值。当我们得到一个新的key-val 键值，我们将key 的每个前缀prefix[i] 都在哈希表中进行存储，我们需要更新每个前缀prefix[i] 对应的值。我们计算出它对应的值的增加为 \textit{delta}delta，计算方式如下：

* 如果键key不存在，则此时delta等于val。
* 如果键key存在，则此时键key 对应得前缀的值都增加val−map[key]，其中map[key] 表示键key当前对应的值。
* 我们在完成前缀的值改写后，同时要更新键key对应的值为val。

求sum时,我们直接利用哈希表查找给定的前缀对应的值即可。

整体代码如下：
```c++
class MapSum {
public:
    MapSum() {

    }
    
    void insert(string key, int val) {
        int delta = val;
        if (map.count(key)) {
            delta -= map[key];
        }
        map[key] = val;
        for (int i = 1; i <= key.size(); ++i) {
            prefixmap[key.substr(0, i)] += delta;
        }
    }
    
    int sum(string prefix) {
        return prefixmap[prefix];
    }
private:
    unordered_map<string, int> map;
    unordered_map<string, int> prefixmap;
};
```

### 字典树

由于我们要处理前缀，自然而然联想到可以用Trie（前缀树）来处理此问题。处理方法跟方法二的原理一样，我们直接在前缀对应的Trie的每个节点存储该前缀对应的值。

* insert操作：原理与方法二一样，我们首先求出前缀对应的值的改变delta，我们直接在Trie 节点上更新键key 的每个前缀对应的值。
* sum 操作: 我们直接在前缀树上搜索该给定的前缀对应的值即可，如果给定的前缀不在前缀树中，则返回0。

当然在实际中我们也可以在Trie的节点只存储键key对应的val, 每次求sum 时利用DFS 或者BFS遍历前缀树的子树即可。

整体代码如下：
```c++
struct TrieNode {
    int val;
    TrieNode * next[26];
    TrieNode() {
        this->val = 0;
        for (int i = 0; i < 26; ++i) {
            this->next[i] = nullptr;
        }
    }
};

class MapSum {
public:
    MapSum() {
        this->root = new TrieNode();
    }
    
    void insert(string key, int val) {
        int delta = val;
        if (cnt.count(key)) {
            delta -= cnt[key];
        }
        cnt[key] = val;
        TrieNode * node = root;
        for (auto c : key) {
            if (node->next[c - 'a'] == nullptr) {
                node->next[c - 'a'] = new TrieNode();
            }
            node = node->next[c - 'a'];
            node->val += delta;
        }
    }
    
    int sum(string prefix) {
        TrieNode * node = root;
        for (auto c : prefix) {
            if (node->next[c - 'a'] == nullptr) {
                return 0;
            } else {
                node = node->next[c - 'a'];
            }
        }
        return node->val;
    }
private:
    TrieNode * root;
    unordered_map<string, int> cnt;
};
```







