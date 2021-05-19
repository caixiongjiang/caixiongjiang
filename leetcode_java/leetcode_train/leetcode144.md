## 二叉树的前序遍历
给你二叉树的根节点 root ，返回它节点值的 前序 遍历。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2020/09/15/inorder_1.jpg)
```
输入：root = [1,null,2,3]
输出：[1,2,3]
```
示例 2：
```
输入：root = []
输出：[]
```
示例 3：
```
输入：root = [1]
输出：[1]
```
示例 4：

![avater](https://assets.leetcode.com/uploads/2020/09/15/inorder_5.jpg)
```
输入：root = [1,2]
输出：[1,2]
```
示例 5：

![avater](https://assets.leetcode.com/uploads/2020/09/15/inorder_4.jpg)
```
输入：root = [1,null,2]
输出：[1,2]
```

提示：

树中节点数目在范围 [0, 100] 内
-100 <= Node.val <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-preorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 递归做法

代码如下：
```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public ArrayList<Integer> preorderTraversal(TreeNode root) {
        ArrayList<Integer> result=new ArrayList<Integer>();
        preOrder(root,result);
        return result;
    }
    public void preOrder(TreeNode root,ArrayList<Integer> result){
        if(root==null){
            return; //只返回函数调用
        }
        result.add(root.val);//数组添加值
        preOrder(root.left,result);
        preOrder(root.right,result);
    }
}
```

## 迭代做法
