## 编号1382：将二叉树搜索树变平衡

你一棵二叉搜索树，请你返回一棵 平衡后 的二叉搜索树，新生成的树应该与原来的树有着相同的节点值。

如果一棵二叉搜索树中，每个节点的两棵子树高度差不超过 1 ，我们就称这棵二叉搜索树是 平衡的 。

如果有多种构造方法，请你返回任意一种。

 

示例：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/03/15/1515_ex1_out.png)

```
输入：root = [1,null,2,null,3,null,4,null,null]
输出：[2,1,3,null,null,null,4]
解释：这不是唯一的正确答案，[3,1,4,null,2,null,null] 也是一个可行的构造方案。 
```
提示：

* 树节点的数目在 1 到 10^4 之间。
* 树节点的值互不相同，且在 1 到 10^5 之间。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/balance-a-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

这道题目，可以中序遍历把二叉树转变为有序数组，然后在根据有序数组构造平衡二叉搜索树。

建议做这道题之前，先看如下两篇题解：

* [98.验证二叉搜索树](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode98.md) 学习二叉搜索树的特性
* [108.将有序数组转换为二叉搜索树](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode108.md) 学习如何通过有序数组构造二叉搜索树
这两道题目做过之后，本题分分钟就可以做出来了。

代码如下：
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

//左闭右闭版本

class Solution {
private:
    vector<int> vec;
    //有序树转为有序数组
    void traversal(TreeNode* cur){
        if(cur == nullptr){
            return;
        }
        traversal(cur->left);
        vec.push_back(cur->val);
        traversal(cur->right);
    }
    //有序数组转平衡二叉树
    TreeNode* getTree(vector<int>& nums, int left, int right){
        if(left > right) return nullptr;
        int mid = left + ((right - left) >> 1);
        TreeNode* root = new TreeNode(nums[mid]);
        //左闭右闭
        root->left = getTree(nums, left, mid - 1);
        root->right = getTree(nums, mid + 1, right);
        return root;
    }
public:
    TreeNode* balanceBST(TreeNode* root) {
        traversal(root);
        //左闭右闭
        return getTree(vec, 0, vec.size() - 1);
    }
};
```


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

//左闭右开版本

class Solution {
private:
    vector<int> vec;
    //有序树转为有序数组
    void traversal(TreeNode* cur){
        if(cur == nullptr){
            return;
        }
        traversal(cur->left);
        vec.push_back(cur->val);
        traversal(cur->right);
    }
    //有序数组转平衡二叉树
    TreeNode* getTree(vector<int>& nums, int left, int right){
        if(left >= right) return nullptr;
        int mid = left + ((right - left) >> 1);
        TreeNode* root = new TreeNode(nums[mid]);
        //左闭右开
        root->left = getTree(nums, left, mid);
        root->right = getTree(nums, mid + 1, right);
        return root;
    }
public:
    TreeNode* balanceBST(TreeNode* root) {
        traversal(root);
        //左闭右开
        return getTree(vec, 0, vec.size());
    }
};
```