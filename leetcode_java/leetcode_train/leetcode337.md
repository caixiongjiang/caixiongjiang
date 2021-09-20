## 编号337：打家劫舍Ⅲ

在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为“根”。 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。

计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。

示例 1:
```
输入: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \ 
     3   1

输出: 7 
解释: 小偷一晚能够盗取的最高金额 = 3 + 3 + 1 = 7.
```
示例 2:
```
输入: [3,4,5,1,3,null,1]

     3
    / \
   4   5
  / \   \ 
 1   3   1
输出: 9
解释: 小偷一晚能够盗取的最高金额 = 4 + 5 = 9.
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/house-robber-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
这道题目和 [198.打家劫舍](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode198.md)，[213.打家劫舍II](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode213.md)也是如出一辙，只不过这个换成了树。

如果对树的遍历不够熟悉的话，那本题就有难度了。

对于树的话，首先就要想到遍历方式，前中后序（深度优先搜索）还是层序遍历（广度优先搜索）。

**本题一定是要后序遍历，因为通过递归函数的返回值来做下一步计算。**

与198.打家劫舍，213.打家劫舍II一样，关键是要讨论当前节点抢还是不抢。

**如果抢了当前节点，两个孩子就不能动，如果没抢当前节点，就可以考虑抢左右孩子**（注意这里说的是“考虑”）

## 暴力递归
代码如下：
```c++
class Solution {
public:
    int rob(TreeNode* root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return root->val;
        // 偷父节点
        int val1 = root->val;
        if (root->left) val1 += rob(root->left->left) + rob(root->left->right); // 跳过root->left，相当于不考虑左孩子了
        if (root->right) val1 += rob(root->right->left) + rob(root->right->right); // 跳过root->right，相当于不考虑右孩子了
        // 不偷父节点
        int val2 = rob(root->left) + rob(root->right); // 考虑root的左右孩子
        return max(val1, val2);
    }
};
```

以上代码超时了，这个递归过程有重复计算。

我们计算了root的四个孙子（左右孩子的孩子）为头结点的子树的情况，又计算了root的左右孩子为头结点的子树的情况，计算左右孩子的时候其实又把孙子计算了一遍。
## 记忆化递推

所以可以使用一个map把计算过的结果保存一下，这样如果计算过孙子了，那么计算孩子的时候可以复用孙子节点的结果。

代码如下：
```c++
class Solution {
public:
    unordered_map<TreeNode* , int> umap; // 记录计算过的结果
    int rob(TreeNode* root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return root->val;
        if (umap[root]) return umap[root]; // 如果umap里已经有记录则直接返回
        // 偷父节点
        int val1 = root->val;
        if (root->left) val1 += rob(root->left->left) + rob(root->left->right); // 跳过root->left
        if (root->right) val1 += rob(root->right->left) + rob(root->right->right); // 跳过root->right
        // 不偷父节点
        int val2 = rob(root->left) + rob(root->right); // 考虑root的左右孩子
        umap[root] = max(val1, val2); // umap记录一下结果
        return max(val1, val2);
    }
};
```

* 时间复杂度：O(n)
* 空间复杂度：O(logn) 算上递推系统栈的空间

## 动态规划

在上面两种方法，其实对一个节点 偷与不偷得到的最大金钱都没有做记录，而是需要实时计算。

**而动态规划其实就是使用状态转移容器来记录状态的变化，这里可以使用一个长度为2的数组，记录当前节点偷与不偷所得到的的最大金钱。**

1.确定递归函数的参数和返回值

这里我们要求一个节点 偷与不偷的两个状态所得到的金钱，那么返回值就是一个长度为2的数组。

参数为当前节点，代码如下：
```c++
vector<int> robTree(TreeNode* cur) {
```
其实这里的返回数组就是dp数组。

<span style="color:red">所以dp数组（dp table）以及下标的含义：下标为0记录不偷该节点所得到的的最大金钱，下标为1记录偷该节点所得到的的最大金钱。</span>

所以本题dp数组就是一个长度为2的数组！

那么有同学可能疑惑，长度为2的数组怎么标记树中每个节点的状态呢？

别忘了在递归的过程中，系统栈会保存每一层递归的参数。

如果还不理解的话，就接着往下看，看到代码就理解了哈。

2.确定终止条件

在遍历的过程中，如果遇到空节点的话，很明显，无论偷还是不偷都是0，所以就返回
```c++
if (cur == NULL) return vector<int>{0, 0};
```
这也相当于dp数组的初始化

3.确定遍历顺序

首先明确的是使用后序遍历。 因为通过递归函数的返回值来做下一步计算。

**通过递归左节点，得到左节点偷与不偷的金钱。**

**通过递归右节点，得到右节点偷与不偷的金钱。**

代码如下：
```c++
// 下标0：不偷，下标1：偷
vector<int> left = robTree(cur->left); // 左
vector<int> right = robTree(cur->right); // 右
// 中
```
4.确定单层递归的逻辑

如果是偷当前节点，那么左右孩子就不能偷，val1 = cur->val + left[0] + right[0]; （**如果对下标含义不理解就在回顾一下dp数组的含义**）

如果不偷当前节点，那么左右孩子就可以偷，至于到底偷不偷一定是选一个最大的，所以：val2 = max(left[0], left[1]) + max(right[0], right[1]);

最后当前节点的状态就是{val2, val1}; 即：{不偷当前节点得到的最大金钱，偷当前节点得到的最大金钱}

代码如下：
```c++
vector<int> left = robTree(cur->left); // 左
vector<int> right = robTree(cur->right); // 右

// 偷cur
int val1 = cur->val + left[0] + right[0];
// 不偷cur
int val2 = max(left[0], left[1]) + max(right[0], right[1]);
return {val2, val1};
```
5.举例推导dp数组

以示例1为例，dp数组状态如下：（注意用后序遍历的方式推导）
![avater](https://camo.githubusercontent.com/6fc9f73094a48e54f24ec2c95f77bda078d2ffc116e2b242bbb0cdb38a3bdef0/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3333372e2545362538392539332545352541452542362545352538412541422545382538382538444949492e6a7067)
最后头结点就是 取下标0 和 下标1的最大值就是偷得的最大金钱。

整体代码如下：
```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int rob(TreeNode* root) {
        vector<int> result = robTree(root);
        return max(result[0], result[1]);
    }
    //长度为2的数组，0：不偷， 1：偷
    vector<int> robTree(TreeNode* cur){
        if(cur == NULL) return vector<int>{0,0};
        vector<int> left = robTree(cur->left);
        vector<int> right = robTree(cur->right);
        //偷cur
        int val1 = cur->val + left[0] + right[0];
        //不偷cur
        int val2 = max(left[0], left[1]) + max(right[0], right[1]);
        return {val2,val1};
    }
};
```