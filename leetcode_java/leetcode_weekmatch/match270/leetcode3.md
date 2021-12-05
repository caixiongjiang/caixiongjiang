## 编号：从二叉树一个节点到另一个节点每一步的方向(×)

给你一棵 二叉树 的根节点 root ，这棵二叉树总共有 n 个节点。每个节点的值为 1 到 n 中的一个整数，且互不相同。给你一个整数 startValue ，表示起点节点 s 的值，和另一个不同的整数 destValue ，表示终点节点 t 的值。

请找到从节点 s 到节点 t 的 最短路径 ，并以字符串的形式返回每一步的方向。每一步用 大写 字母 'L' ，'R' 和 'U' 分别表示一种方向：

* 'L' 表示从一个节点前往它的 左孩子 节点。
* 'R' 表示从一个节点前往它的 右孩子 节点。
* 'U' 表示从一个节点前往它的 父 节点。

请你返回从 s 到 t 最短路径 每一步的方向。

 
示例 1：

![avater](https://assets.leetcode.com/uploads/2021/11/15/eg1.png)

```
输入：root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
输出："UURL"
解释：最短路径为：3 → 1 → 5 → 2 → 6 。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/11/15/eg2.png)

```
输入：root = [2,1], startValue = 2, destValue = 1
输出："L"
解释：最短路径为：2 → 1 。 
```
提示：

* 树中节点数目为 n 。
* 2 <= n <= 105
* 1 <= Node.val <= n
* 树中所有节点的值 互不相同 。
* 1 <= startValue, destValue <= n
* startValue != destValue

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

* 先通过深搜找到从根节点分别到两个点的路径字符串

* 然后将两字符串的相同前缀同时删去

	* 例如两字符串："LLRR"和"LRL"，将前缀"L"删除，表示从根节点向左走一步，到达两个目标结点的最近父结点
* 最后将起始结点对应字符串所剩下的字符全部改成'U'，再拼接终点结点所对应的字符串就是答案了


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
class Solution {
public:
    bool check(TreeNode* root, int x, string& str){
        if(root->val == x) return true;
        if(root->left){
            str.push_back('L');
            if(check(root->left, x, str)) return true;
            str.pop_back();
        }
        if(root->right){
            str.push_back('R');
            if(check(root->right, x, str)) return true;
            str.pop_back();
        }
        return false;
    }
    string getDirections(TreeNode* root, int startValue, int destValue) {
        string str1, str2;
        check(root, startValue, str1);
        check(root, destValue, str2);
        reverse(str1.begin(), str1.end()); reverse(str2.begin(), str2.end());
        while(str1.size() && str2.size() && str1.back() == str2.back()){
            str1.pop_back();
            str2.pop_back();
        }
        reverse(str1.begin(), str1.end()); reverse(str2.begin(), str2.end());
        string ans = string(str1.size(), 'U') + str2;
        return ans;
        
    }
};
```