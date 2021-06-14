## 编号110：平衡二叉树

给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：

*一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1 。*

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2020/10/06/balance_1.jpg)

```
输入：root = [3,9,20,null,null,15,7]
输出：true
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2020/10/06/balance_2.jpg)

```
输入：root = [1,2,2,3,3,null,null,4,4]
输出：false
```
示例 3：
```
输入：root = []
输出：true
```
提示：

* 树中的节点数在范围 [0, 5000] 内
* -104 <= Node.val <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/balanced-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 递归

```java
class Solution {
    public boolean isBalanced(TreeNode root) {
        return getHeight(root) != -1;
    }
    private int getHeight(TreeNode root){
        if(root == null){
            return 0;
        }
        int leftHeight = getHeight(root.left);
        if(leftHeight == -1) return -1;
        int rightHeight = getHeight(root.right);
        if(rightHeight == -1) return -1;
        //左右子树好高度差大于1，return -1表示不是平衡树了。
        if(Math.abs(leftHeight-rightHeight) > 1){
            return -1;
        }
        return Math.max(leftHeight,rightHeight) + 1;
    }
}
```

## 迭代

```java
class Solution {
    public boolean isBalanced(TreeNode root) {
        if(root == null){
            return true;
        }
        Stack<TreeNode> stack = new Stack<>();
        TreeNode pre = null;
        while(root != null || !stack.isEmpty()){
            while(root != null){
                stack.push(root);
                root = root.left;
            }
            TreeNode node = stack.peek();
            //右结点为null或者已经遍历过
            if(node.right == null || node.right == pre){
                //输出
                if(Math.abs(getHeight(node.left) - getHeight(node.right)) > 1){
                    return false;
                }
                stack.pop();
                pre = node;
                root = null;//当前结点下，没有要遍历的结点了
            } else{
                root = node.right;
            }
        }
        return true;
    }
    /*
    求结点的高度 
    */
    public int getHeight(TreeNode root){
        if(root == null){
            return 0;
        }
        int leftHeight = root.left != null ? root.left.val :0;
        int rightHeight =root.right != null ? root.right.val :0;
        int height = Math.max(leftHeight,rightHeight) + 1;
        root.val = height;//用TreeNode.val来保存当前结点的高度
        return height;
    }
}
```