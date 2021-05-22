## 编号111：二叉树的最小深度

给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

说明：叶子节点是指没有子节点的节点。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2020/10/12/ex_depth.jpg)
```
输入：root = [3,9,20,null,null,15,7]
输出：2
```
示例 2：
```
输入：root = [2,null,3,null,4,null,5,null,6]
输出：5
```
提示：

* 树中节点数的范围在 [0, 105] 内
* -1000 <= Node.val <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-depth-of-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
遍历顺序上依然是后序遍历（因为要比较递归返回之后的结果），但在处理中间节点的逻辑上，最大深度很容易理解，最小深度可有一个误区，如图：

![avater](https://camo.githubusercontent.com/93b85ef3d6e7a070f3281f4cf8949ec7affb07261311f989848ce2e7167ef5b6/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303230333135353830303530332e706e67)

题目中说的是：**最小深度是从根节点到最近叶子节点的最短路径上的节点数量。**注意是叶子节点。

什么是叶子节点，左右孩子都为空的节点才是叶子节点！

## 递归法

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
    public int minDepth(TreeNode root) {
        return getDepth(root);
    }
    private int getDepth(TreeNode node){
        if(node==null){
            return 0;   //表示当前节点的高度为0
        }
        int leftDepth=getDepth(node.left);//左
        int rightDepth=getDepth(node.right);//右
        //左子树为空，右子树不空
        if(node.left==null && node.right!=null){
            return 1+rightDepth;
        }
        //右子树为空，左子树不空
        if(node.left!=null && node.right==null){
            return 1+leftDepth;
        }
        int res=1+Math.min(leftDepth,rightDepth);
        return res;
    }
}
```

## 迭代法

```java
class Solution{
    public int minDepth(TreeNode root){
        if(root==null){
            return 0;
        }
        int minDepth=0;
        Queue<TreeNode> queue=new LinkedList<TreeNode>();
        queue.offer(root);
        while(!queue.isEmpty()){
            int levelSize=queue.size();
            minDepth++;
            for(int i=0;i<levelSize;i++){
                TreeNode node=queue.poll();
                if(node.left==null && node.right==null){
                    //是叶子节点则直接返回深度
                    return minDepth;
                }
                if(node.left!=null){
                    queue.offer(node.left);
                }
                if(node.right!=null){
                    queue.offer(node.right);
                }
            }
        }
        return minDepth;
    }
}
```
