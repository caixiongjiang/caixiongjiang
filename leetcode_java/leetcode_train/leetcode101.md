## 编号101：对称二叉树

给定一个二叉树，检查它是否是镜像对称的。

 

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。
```
    1
   / \
  2   2
 / \ / \
3  4 4  3
```
但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:
```
    1
   / \
  2   2
   \   \
   3    3
```  



进阶：

你可以运用递归和迭代两种方法解决这个问题吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/symmetric-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

**首先想清楚，判断对称二叉树要比较的是哪两个节点，要比较的可不是左右节点！**

对于二叉树是否对称，要比较的是根节点的左子树与右子树是不是相互翻转的，理解这一点就知道了<span style="color:green">**其实我们要比较的是两个树（这两个树是根节点的左右子树）**</span>，所以在递归遍历的过程中，也是要同时遍历两棵树。

那么如果比较呢？

比较的是两个子树的里侧和外侧的元素是否相等。如图所示：

![avater](https://camo.githubusercontent.com/c6b7e44d2d4a15a2ab7bf066addab1380aab6e9ce15491a4aaca04388abebc7b/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303230333134343632343431342e706e67)

本题遍历只能是“后序遍历”，因为我们要<span style="color:pink">通过递归函数的返回值来判断两个子树的内侧节点和外侧节点是否相等。</span>

正是因为要遍历两棵树而且要比较内侧和外侧节点，所以准确的来说是一个树的遍历顺序是左右中，一个树的遍历顺序是右左中。

但都可以理解算是后序遍历，尽管已经不是严格上在一个树上进行遍历的后序遍历了。

## 递归法

1.确定递归函数的参数和返回值
</br>因为我们要比较的是根节点的两个子树是否是相互翻转的，进而判断这个树是不是对称树，所以要比较的是两个树，参数自然也是左子树节点和右子树节点。

返回值自然是bool类型。

```java
boolean compare(TreeNode left,TreeNode right)
```
2.确定终止条件
要比较两个节点数值相不相同，首先要把两个节点为空的情况弄清楚！否则后面比较数值的时候就会操作空指针了。

节点为空的情况有：（注意我们比较的其实不是左孩子和右孩子，所以如下我称之为左节点右节点）
* 左节点为空，右节点不为空，不对称，return false
* 左不为空，右为空，不对称 return false
* 左右都为空，对称，返回true
</br>此时已经排除掉了节点为空的情况，那么剩下的就是左右节点不为空：
* 左右都不为空，比较节点数值，不相同就return false

```java
if (left == null && right != null) return false;
else if (left != null && right == null) return false;
else if (left == null && right == null) return true;
else if (left.val != right.val) return false; // 注意这里我没有使用else
```
3.确定单层递归的逻辑
单层递归的逻辑就是处理 右节点都不为空，且数值相同的情况。
* 比较二叉树外侧是否对称：传入的是左节点的左孩子，右节点的右孩子。
* 比较内测是否对称，传入左节点的右孩子，右节点的左孩子。
* 如果左右都对称就返回true ，有一侧不对称就返回false 。

```java
boolean outside = compare(left->left, right->right);   // 左子树：左、 右子树：右
boolean inside = compare(left->right, right->left);    // 左子树：右、 右子树：左
boolean isSame = outside && inside;                    // 左子树：中、 右子树：中（逻辑处理）
return isSame;
```

java代码如下：

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
    public boolean isSymmetric(TreeNode root) {
        return comapare(root.left,root.right);
    }
    
    private boolean comapare(TreeNode left,TreeNode right){
        if(left==null && right!=null){
            return false;
        }
        if(left!=null && right==null){
            return false;
        }
        if(left==null && right==null){
            return true;
        }
        if(left.val!=right.val){     //不能写left.val和right.val相等，return true。因为还要往下比较
            return false;
        }
        //比较外侧
        boolean compareOutside=comapare(left.left,right.right);
        //比较内侧
        boolean compareInside=comapare(left.right,right.left);
        return compareInside && compareOutside; //若内侧和外侧全部相同才能返回true
    }
}
```

## 迭代法

将两边的节点放入队列一一比较。
</br>1.使用队列

```java
class Solution {
    public boolean isSymmetric(TreeNode root) {
        return check(root, root);
    }

    public boolean check(TreeNode u, TreeNode v) {
        Queue<TreeNode> q = new LinkedList<TreeNode>();
        q.offer(u);
        q.offer(v);
        while (!q.isEmpty()) {
            u = q.poll();
            v = q.poll();
            if (u == null && v == null) {
                continue;
            }
            if ((u == null || v == null) || (u.val != v.val)) {
                return false;
            }
            //外侧节点入队
            q.offer(u.left);
            q.offer(v.right);
            //内侧节点入队
            q.offer(u.right);
            q.offer(v.left);
        }
        return true;
    }
}
```
</br>2.使用双端队列，从两端插入

```java
/**
     * 迭代法
     * 使用双端队列，相当于两个栈
     */
class Solution{
    public boolean isSymmetric(TreeNode root){
        Deque<TreeNode> deque = new LinkedList<>();
        deque.offerFirst(root.left);
        deque.offerLast(root.right);
        while (!deque.isEmpty()) {
            TreeNode leftNode = deque.pollFirst();
            TreeNode rightNode = deque.pollLast();
            if (leftNode == null && rightNode == null) {
                continue;
            }
            if (leftNode == null || rightNode == null || leftNode.val != rightNode.val) {
                return false;
            }
            deque.offerFirst(leftNode.left);
            deque.offerFirst(leftNode.right);
            deque.offerLast(rightNode.right);
            deque.offerLast(rightNode.left);
        }
        return true;
    }
    public boolean res(TreeNode root){
        return isSymmetric(root);
    }
}
```