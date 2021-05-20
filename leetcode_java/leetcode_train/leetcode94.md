## 二叉树的递归遍历
给定一个二叉树的根节点 root ，返回它的 中序 遍历。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2020/09/15/inorder_1.jpg)
```
输入：root = [1,null,2,3]
输出：[1,3,2]
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
输出：[2,1]
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
 

进阶: 递归算法很简单，你可以通过迭代算法完成吗

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-inorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 递归做法

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
    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> res=new ArrayList<>();
        inOrder(root,res);
        return res;
    }
    public void inOrder(TreeNode root,List<Integer> list){
        if(root==null){
            return;
        }
        inOrder(root.left,list);
        list.add(root.val);
        inOrder(root.right,list);
    }
}
```

## 迭代做法
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
	public List<Integer> inorderTraversal(TreeNode root) {
		List<Integer> res = new ArrayList<Integer>();
		Deque<TreeNode> stack = new LinkedList<TreeNode>();
		while(!stack.isEmpty() || root!=null) {
			//不断往左子树方向走，每走一次就将当前节点保存到栈中
			//这是模拟递归的调用
			while(root!=null) {
				stack.push(root);
				root = root.left;
			//当前节点为空，说明左边走到头了，从栈中弹出节点并保存
			//然后转向右边节点，继续上面整个过程
			}
			    TreeNode tmp = stack.pop();
			    res.add(tmp.val);   
			    root = tmp.right;
			}
		return res;
	}
}
```