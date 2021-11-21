## 编号559：N叉树的最大高度

给定一个 N 叉树，找到其最大深度。

最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。

N 叉树输入按层序遍历序列化表示，每组子节点由空值分隔（请参见示例）。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2018/10/12/narytreeexample.png)

```
输入：root = [1,null,3,2,4,null,5,6]
输出：3
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2019/11/08/sample_4_964.png)

```
输入：root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
输出：5
```
 

提示：

* 树的深度不会超过 1000 。
* 树的节点数目位于 [0, 104] 之间。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-depth-of-n-ary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 深度优先搜索

如果根节点有 N 个子节点，则这 NN 个子节点对应 N 个子树。记 N 个子树的最大深度中的最大值为 maxChildDepth，则该 NN 叉树的最大深度为maxChildDepth+1。

每个子树的最大深度又可以以同样的方式进行计算。因此我们可以用「深度优先搜索」的方法计算 N 叉树的最大深度。具体而言，在计算当前 N 叉树的最大深度时，可以先递归计算出其每个子树的最大深度，然后在 O(1) 的时间内计算出当前 N 叉树的最大深度。递归在访问到空节点时退出。


代码如下：
```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    int maxDepth(Node* root) {
        if(root == nullptr){
            return 0;
        }      
        int maxChildDepth = 0;
        //深度优先搜索 每个vector都包含着一条子路径的所有节点
        vector<Node *> children = root->children;
        for(auto child : children){
            int childDepth = maxDepth(child);
            maxChildDepth = max(maxChildDepth, childDepth);
        }
        return maxChildDepth + 1;
    }
};
```

### 广度优先搜索

我们也可以用「广度优先搜索」的方法来解决这道题目，但我们需要对其进行一些修改，此时我们广度优先搜索的队列里存放的是「当前层的所有节点」。每次拓展下一层的时候，不同于广度优先搜索的每次只从队列里拿出一个节点，我们需要将队列里的所有节点都拿出来进行拓展，这样能保证每次拓展完的时候队列里存放的是当前层的所有节点，即我们是一层一层地进行拓展。最后我们用一个变量ans来维护拓展的次数，该 N叉树的最大深度即为ans。

代码如下：
```c++
class Solution {
public:
    int maxDepth(Node* root) {
        if (root == nullptr) {
            return 0;
        }
        queue<Node *> qu;
        qu.push(root);
        int ans = 0;
        while (!qu.empty()) {
            int size = qu.size();
            while (size > 0) {
                Node * node = qu.front();
                qu.pop();
                vector<Node *> children = node->children;
                for (auto child : children) {
                    qu.push(child);
                }
                size--;
            }
            ans++;
        }
        return ans;
    }
};
```
