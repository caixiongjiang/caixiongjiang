## 编号563：二叉树的坡度

一个树的 节点的坡度 定义即为，该节点左子树的节点之和和右子树节点之和的 差的绝对值 。如果没有左子树的话，左子树的节点之和为 0 ；没有右子树的话也是一样。空结点的坡度是 0 。

整个树 的坡度就是其所有节点的坡度之和。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2020/10/20/tilt1.jpg)

```
输入：root = [1,2,3]
输出：1
解释：
节点 2 的坡度：|0-0| = 0（没有子节点）
节点 3 的坡度：|0-0| = 0（没有子节点）
节点 1 的坡度：|2-3| = 1（左子树就是左子节点，所以和是 2 ；右子树就是右子节点，所以和是 3 ）
坡度总和：0 + 0 + 1 = 1
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2020/10/20/tilt2.jpg)

```
输入：root = [4,2,9,3,5,null,7]
输出：15
解释：
节点 3 的坡度：|0-0| = 0（没有子节点）
节点 5 的坡度：|0-0| = 0（没有子节点）
节点 7 的坡度：|0-0| = 0（没有子节点）
节点 2 的坡度：|3-5| = 2（左子树就是左子节点，所以和是 3 ；右子树就是右子节点，所以和是 5 ）
节点 9 的坡度：|0-7| = 7（没有左子树，所以和是 0 ；右子树正好是右子节点，所以和是 7 ）
节点 4 的坡度：|(3+5+2)-(9+7)| = |10-16| = 6（左子树值为 3、5 和 2 ，和是 10 ；右子树值为 9 和 7 ，和是 16 ）
坡度总和：0 + 0 + 0 + 2 + 7 + 6 = 15
```
示例 3：

![avater](https://assets.leetcode.com/uploads/2020/10/20/tilt3.jpg)

```
输入：root = [21,7,14,1,1,2,2,3,3]
输出：9 
```
提示：

* 树中节点数目的范围在 [0, 104] 内
* -1000 <= Node.val <= 1000
* 通过次数47,175提交次数73,520

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-tilt
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

根据题意，我们需要累计二叉树中所有结点的左子树结点之和与右子树结点之和的差的绝对值。因此，我们可以使用深度优先搜索，在遍历每个结点时，累加其左子树结点之和与右子树结点之和的差的绝对值，并返回以其为根结点的树的结点之和。

具体地，我们实现算法如下：

* 从根结点开始遍历，设当前遍历的结点为node；
* 遍历node的左子结点，得到左子树结点之和sum_left；遍历node的右子结点，得到右子树结点之和sum_right；
* 将左子树结点之和与右子树结点之和的差的绝对值累加到结果变量ans；
返回以node作为根结点的树的结点之和sum_left+sum_right+node.val。

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
    int ans = 0;

    int findTilt(TreeNode root) {
        dfs(root);
        return ans;
    }

    int dfs(TreeNode node) {
        if (node == null) {
            // 空节点返回0
            return 0;
        }

        // 左子树之和
        int left = dfs(node.left);
        // 右子树之和
        int right = dfs(node.right);

        // 总坡度存储在全局变量 ans 中
        ans += Math.abs(left - right);

        // 返回值是子树之和
        return left + right + node.val;
    }
};
```
