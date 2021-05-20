## 翻转二叉树
翻转一棵二叉树。

示例：
```
输入：

     4
   /   \
  2     7
 / \   / \
1   3 6   9
```
输出：
```
     4
   /   \
  7     2
 / \   / \
9   6 3   1
```
备注:
这个问题是受到 Max Howell 的 原问题 启发的 ：

谷歌：我们90％的工程师使用您编写的软件(Homebrew)，但是您却无法在面试时在白板上写出翻转二叉树这道题，这太糟糕了。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/invert-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

翻转操作可以用二叉树的指针交换完成（核心部分）。
</br><span style="color:green">**需要注意的问题是,本题在翻转子树的时候只能采用前序和后序遍历**</span>

采用中序遍历会出现的问题：
到根节点为2的情况
```
     4                
   /   \            
  2     7   ->  
 / \   / \
1   3 6   9
```
```
     4
   /   \
  2     7   ->
 / \   / \
3   1 6   9
```
```
     4
   /   \
  7     2   ->
 / \   / \
6   9 3   1
```
```
     4
   /   \
  7     2
 / \   / \
6   9 1   3
```
<span style="color:red">**最终结果子树的完全没有翻转！**</span>

以前序遍历为例，代码如下：

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
    public TreeNode invertTree(TreeNode root) {
        preOrderInvertTree(root);
        return root;
    }
    
    public void preOrderInvertTree(TreeNode root){
        if(root==null){
            return;
        }
        swapTreeNode(root);             //前序
        preOrderInvertTree(root.left);
        preOrderInvertTree(root.right);
    }
    
    void swapTreeNode(TreeNode root){       //交换索引
        TreeNode tmp=root.left;
        root.left=root.right;
        root.right=tmp;
    } 
}
```