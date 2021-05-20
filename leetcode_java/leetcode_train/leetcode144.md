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
```java
/**
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
    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> res=new ArrayList<Integer>();             //保存结果的数组
        if(root==null){
            return res;
        }

        Deque<TreeNode> stack=new LinkedList<TreeNode>();       //双端队列实现二叉树节点为元素的栈结构（链表结构）
        TreeNode node=root;
        while(!stack.isEmpty() || node!=null){
            while(node!=null){        //按照栈中的顺序来进行:中间节点先入栈，再右孩子，在左孩子；此时出栈顺序为中左右
                res.add(node.val);
                stack.push(node);
                node=node.left;
            }
            node=stack.pop();
            node=node.right;
        }
        return res;
    }
}
```
