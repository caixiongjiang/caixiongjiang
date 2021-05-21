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
### 递归方法
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

### 迭代法（其实就是用栈或者队列的结构来代替递归）
#### 层序遍历的方法（队列）
```java
class Solution {
	public TreeNode invertTree(TreeNode root) {
		if(root==null) {
			return null;
		}
		//将二叉树中的节点逐层放入队列中，再迭代处理队列中的元素
		Queue<TreeNode> queue = new LinkedList<TreeNode>();
		queue.add(root);
		while(!queue.isEmpty()) {
			//每次都从队列中拿一个节点，并交换这个节点的左右子树
			TreeNode tmp = queue.poll();
			TreeNode left = tmp.left;
			tmp.left = tmp.right;
			tmp.right = left;
			//如果当前节点的左子树不为空，则放入队列等待后续处理
			if(tmp.left!=null) {
				queue.add(tmp.left);
			}
			//如果当前节点的右子树不为空，则放入队列等待后续处理
			if(tmp.right!=null) {
				queue.add(tmp.right);
			}
			
		}
		//返回处理完的根节点
		return root;
	}
}
```
#### 深度优先搜索（前序）
```java
class Solution{
    public TreeNode invertTree(TreeNode root) {
        if (root == null)
            return root;
        Stack<TreeNode> stack = new Stack<>();
        stack.add(root);
        while (!stack.empty()) {
            TreeNode node = stack.pop();//中
            //先交换子节点
            TreeNode left = node.left;
            node.left = node.right;
            node.right = left;
            if (node.right != null) {//入栈的顺序为右左，出栈则为左右
                stack.push(node.right);
            }
            if (node.left != null) {
                stack.push(node.left);
            }
        }
        return root;
    }
}
```