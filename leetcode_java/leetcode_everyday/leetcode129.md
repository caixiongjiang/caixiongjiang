## 编号129：求根到叶子节点的数字之和

给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
每条从根节点到叶节点的路径都代表一个数字：

* 例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
计算从根节点到叶节点生成的 所有数字之和 。

叶节点 是指没有子节点的节点。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/02/19/num1tree.jpg)

```
输入：root = [1,2,3]
输出：25
解释：
从根到叶子节点路径 1->2 代表数字 12
从根到叶子节点路径 1->3 代表数字 13
因此，数字总和 = 12 + 13 = 25
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/02/19/num2tree.jpg)

```
输入：root = [4,9,0,5,1]
输出：1026
解释：
从根到叶子节点路径 4->9->5 代表数字 495
从根到叶子节点路径 4->9->1 代表数字 491
从根到叶子节点路径 4->0 代表数字 40
因此，数字总和 = 495 + 491 + 40 = 1026
```
提示：

* 树中节点的数目在范围 [1, 1000] 内
* 0 <= Node.val <= 9
* 树的深度不超过 10

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sum-root-to-leaf-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

首先思路很明确，就是要遍历整个树把更节点到叶子节点组成的数字相加。

那么先按递归三部曲来分析：

## 递归三部曲

* 确定递归函数返回值及其参数

这里我们要遍历整个二叉树，且需要要返回值做逻辑处理，所有返回值为void

参数只需要把根节点传入，此时还需要定义两个全局遍历，一个是result，记录最终结果，一个是vector path。

**为什么用vector类型（就是数组）呢？ 因为用vector方便我们做回溯！**

所以代码如下：
```c++
int result;
vector<int> path;
void traversal(TreeNode* cur) 
```

* 确定终止条件

递归什么时候终止呢？

当然是遇到叶子节点，此时要收集结果了，通知返回本层递归，因为单条路径的结果使用vector，我们需要一个函数vectorToInt把vector转成int。

终止条件代码如下：
```c++
if (!cur->left && !cur->right) { // 遇到了叶子节点
    result += vectorToInt(path);
    return;
}
```
这里vectorToInt函数就是把数组转成int，代码如下：
```c++
int vectorToInt(const vector<int>& vec) {
    int sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum = sum * 10 + vec[i];
    }
    return sum;
}
```

* 确定递归单层逻辑

本题其实采用前中后序都不无所谓， 因为也没有中间几点的处理逻辑。

这里主要是当左节点不为空，path收集路径，并递归左孩子，右节点同理。

但别忘了回溯。

如图：

![avater](https://camo.githubusercontent.com/ba7f72207a904c09d84baf4e9caf6633b4438c6a603a7024426b5b6364b62907/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3132392ee6b182e6a0b9e588b0e58fb6e5ad90e88a82e782b9e695b0e5ad97e4b98be5928c2e706e67)

代码如下：
```c++
                 // 中
if (cur->left) { // 左 （空节点不遍历）
    path.push_back(cur->left->val);
    traversal(cur->left);    // 递归
    path.pop_back();         // 回溯
}
if (cur->right) { // 右 （空节点不遍历）
    path.push_back(cur->right->val);
    traversal(cur->right);   // 递归
    path.pop_back();         // 回溯
}
```

## 整体c++代码

```c++
class Solution {
private:
    int result;
    vector<int> path;
    // 把vector转化为int
    int vectorToInt(const vector<int>& vec) {
        int sum = 0;
        for (int i = 0; i < vec.size(); i++) {
            sum = sum * 10 + vec[i];
        }
        return sum;
    }
    void traversal(TreeNode* cur) {
        if (!cur->left && !cur->right) { // 遇到了叶子节点
            result += vectorToInt(path);
            return;
        }

        if (cur->left) { // 左 （空节点不遍历）
            path.push_back(cur->left->val);     // 处理节点
            traversal(cur->left);               // 递归
            path.pop_back();                    // 回溯，撤销
        }
        if (cur->right) { // 右 （空节点不遍历）
            path.push_back(cur->right->val);    // 处理节点
            traversal(cur->right);              // 递归
            path.pop_back();                    // 回溯，撤销
        }
        return ;
    }
public:
    int sumNumbers(TreeNode* root) {
        path.clear();
        if (root == nullptr) return 0;
        path.push_back(root->val);
        traversal(root);
        return result;
    }
};
```