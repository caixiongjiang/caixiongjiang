## 编号700：二叉搜索树中的搜索

给定二叉搜索树（BST）的根节点和一个值。 你需要在BST中找到节点值等于给定值的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 NULL。

例如，

```
给定二叉搜索树:

        4
       / \
      2   7
     / \
    1   3

和值: 2
```
你应该返回如下子树:
```
      2     
     / \   
    1   3
```
在上述示例中，如果要找的值是 5，但因为没有节点值为 5，我们应该返回 NULL。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/search-in-a-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

二叉搜索树是一个有序树：

* 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
* 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
* 它的左、右子树也分别为二叉搜索树
这就决定了，二叉搜索树，递归遍历和迭代遍历和普通二叉树都不一样。

本题，其实就是在二叉搜索树中搜索一个节点。那么我们来看看应该如何遍历。

## 递归

这里可能会疑惑，在递归遍历的时候，什么时候直接return 递归函数的返回值，什么时候不用加这个 return呢。

我们在二叉树：递归函数究竟什么时候需要返回值，什么时候不要返回值？中讲了，如果要搜索一条边，递归函数就要加返回值，这里也是一样的道理。

<span style="color:green">***因为搜索到目标节点了，就要立即return了，这样才是找到节点就返回（搜索某一条边），如果不加return，就是遍历整棵树了。***</span>

代码如下：

```java
class Solution {
    public TreeNode searchBST(TreeNode root, int val) {
        if(root == null) return null;
        if(root.val == val) return root;
        if(root.val > val){
           return searchBST(root.left, val);//这里必须加return
        }else if(root.val < val){
           return searchBST(root.right, val);//这里必须加return
        }
        return null;
    }
}
```

## 迭代
一提到二叉树遍历的迭代法，可能立刻想起使用栈来模拟深度遍历，使用队列来模拟广度遍历。

对于二叉搜索树可就不一样了，因为二叉搜索树的特殊性，也就是节点的有序性，可以不使用辅助栈或者队列就可以写出迭代法。

对于一般二叉树，递归过程中还有回溯的过程，例如走一个左方向的分支走到头了，那么要调头，在走右分支。

**而对于二叉搜索树，不需要回溯的过程，因为节点的有序性就帮我们确定了搜索的方向。**

例如要搜索元素为3的节点，**我们不需要搜索其他节点，也不需要做回溯，查找的路径已经规划好了。**

中间节点如果大于3就向左走，如果小于3就向右走，如图：

![avater](https://camo.githubusercontent.com/19b0a6612a0d6427d36473e666a5d541b4221900549b67c7015f4284247b71d5/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230303831323139303231333238302e706e67)

代码如下：

```java
class Solution {
    // 迭代，利用二叉搜索树特点，优化，可以不需要栈
    public TreeNode searchBST(TreeNode root, int val) {
        while (root != null)
            if (val < root.val) root = root.left;
            else if (val > root.val) root = root.right;
            else return root;
        return root;
    }
}
```