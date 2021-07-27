## 编号236：二叉树的最近公共祖先

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)
```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
```

示例 2：

![avater](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)
```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
```
示例 3：
```
输入：root = [1,2], p = 1, q = 2
输出：1
```
提示：

* 树中节点数目在范围 [2, 105] 内。
* -109 <= Node.val <= 109
* 所有 Node.val 互不相同 。
* p != q
* p 和 q 均存在于给定的二叉树中。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

首先这个题目一般会想到从自底向上查找，这样就可以找到公共祖先了。
</br>二叉树如何自底向上查找，这时又会想到回溯，<span style="color:green">后序遍历是天然的回溯过程，最先处理的一定是叶子节点。</span>
</br>如何判断一个节点是否是节点p和节点q的公共祖先
<span style="color:yellow">**如果找到一个节点，发现左子树出现节点p，右子树出现节点q，或者左子树出现节点q，右子树出现节点p，那么该节点就是节点p和q的最近公共祖先。**</span>
</br>使用后序遍历的过程，就是从低向上遍历节点，一旦发现符合这个条件的节点，就是最近公共节点。

## 递归

递归三部曲：

* 确定递归函数返回值以及参数
需要递归函数返回值，来告诉我们是否找到节点q或者p，那么返回值为bool类型就可以了。

<span style="color:green">**但我们还要返回最近公共节点，可以利用上题目中返回值是TreeNode ，那么如果遇到p或者q，就把q或者p返回，返回值不为空，就说明找到了q或者p。**</span>

代码如下：
```java
TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q)
```
* 确定终止条件
</br>如果找到了 节点p或者q，或者遇到空节点，就返回。

代码如下：

```java
if (root == q || root == p || root == null) return root;
```
* 确定单层递归逻辑
</br>**值得注意的是 本题函数有返回值，是因为回溯的过程需要递归函数的返回值做判断，但本题我们依然要遍历树的所有节点。**

 递归函数有返回值就是要遍历某一条边，但有返回值也要看如何处理返回值！

如果递归函数有返回值，如何区分要搜索一条边，还是搜索整个树呢？

搜索一条边的写法：
```java
if (递归函数(root.left)) return ;

if (递归函数(root.right)) return ;
```
搜索整个树写法：
```java
left = 递归函数(root.left);
right = 递归函数(root.right);
left与right的逻辑处理;
```

<span style="color:red">在递归函数有返回值的情况下：如果要搜索一条边，递归函数返回值不为空的时候，立刻返回，如果搜索整个树，直接用一个变量left、right接住返回值，这个left、right后序还有逻辑处理的需要，也就是后序遍历中处理中间节点的逻辑（也是回溯）。</span>

那么为什么要遍历整颗树呢？直观上来看，找到最近公共祖先，直接一路返回就可以了。

如图：

![avater](https://camo.githubusercontent.com/b5196e17f71edf0a27d67274efeb0217f445e9cd2176e1f64924e27e192c1bf5/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032313032303431353130353837322e706e67)
因为在如下代码的后序遍历中，如果想利用left和right做逻辑处理，不能立刻返回，而是要等left与right逻辑处理完之后才能返回。
```java
left = 递归函数(root.left);
right = 递归函数(root.right);
left与right的逻辑处理;
```
所以此时大家要知道我们要遍历整棵树。


整体代码如下：

```java
class Solution {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        return myLowestCommonAncestor(root, p, q);
    }
    public TreeNode myLowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q){
        if(root == null || root == p || root == q){
            return root;//返回自身节点
        }
        //后序遍历
        TreeNode left = myLowestCommonAncestor(root.left, p, q);//左
        TreeNode right = myLowestCommonAncestor(root.right, p, q);//右
        //对根节点进行操作
        if(left != null && right != null){//左右子树都找到了，说明此时的root就是所求的节点
            return root;
        }
        if(left == null) return right;
        return left;
    }
}
```

## 总结
1.求最小公共祖先，需要从底向上遍历，那么二叉树，只能通过后序遍历（即：回溯）实现从低向上的遍历方式。

2.在回溯的过程中，必然要遍历整颗二叉树，即使已经找到结果了，依然要把其他节点遍历完，因为要使用递归函数的返回值（也就是代码中的left和right）做逻辑判断。

3.如果返回值left为空，right不为空为什么要返回right，为什么可以用返回right传给上一层结果。