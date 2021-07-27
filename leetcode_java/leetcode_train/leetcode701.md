## 编号701：二叉搜索树中的插入操作

给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 输入数据 保证 ，新值和原始二叉搜索树中的任意节点值都不同。

注意，可能存在多种有效的插入方式，只要树在插入后仍保持为二叉搜索树即可。 你可以**返回 任意有效的结果**。

 

示例 1：
![avater](https://assets.leetcode.com/uploads/2020/10/05/insertbst.jpg)

```
输入：root = [4,2,7,1,3], val = 5
输出：[4,2,7,1,3,5]
```
解释：另一个满足题目要求可以通过的树是：

![avater](https://assets.leetcode.com/uploads/2020/10/05/bst.jpg)

示例 2：
```
输入：root = [40,20,60,10,30,50,70], val = 25
输出：[40,20,60,10,30,50,70,null,null,25]
```
示例 3：
```
输入：root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
输出：[4,2,7,1,3,5]
```
提示：

* 给定的树上的节点数介于 0 和 10^4 之间
* 每个节点都有一个唯一整数值，取值范围从 0 到 10^8
* -10^8 <= val <= 10^8
* 新值和原始二叉搜索树中的任意节点值都不同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/insert-into-a-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

由于是二叉搜索树：
</br>1.根节点左边的节点值一定小于右边的节点，所以只需要与根节点的值进行比较，比它大就往右遍历，比它小就往左遍历，直到找到需要插入的位置。
</br>2.插入之前必须保存前一个节点的位置，否则无法插入，而且还需要知道在左边插入还是在右边插入

## 迭代
按照上述两个步骤，写出代码：

```java
class Solution {
    public TreeNode insertIntoBST(TreeNode root, int val) {
        if(root == null){
            return new TreeNode(val);
        }
        TreeNode newRoot = root;//记录当前节点
        TreeNode pre = root;//记录当前节点的前一个节点
        while(root != null){
            pre = root;
            if(root.val < val){
                root = root.right;
            }else{
                root = root.left;
            }
        }
	//判断是从左插入还是从右边插入
        if(pre.val > val){
            pre.left = new TreeNode(val);
        }else{
            pre.right = new TreeNode(val);
        }
        return newRoot;
    }
}
```

## 递归

代码如下：

递归思路和迭代相差不大，代码如下：

```java
class Solution{
    public TreeNode insertIntoBST(TreeNode root, int val){
        return buildTree(root, val);
    }
    public TreeNode buildTree(TreeNode root, int val){
        if(root == null) return new TreeNode(val);// 如果当前节点为空，也就意味着val找到了合适的位置，此时创建节点直接返回。
        if(root.val < val){
            root.right = buildTree(root.right, val);//递归创建右子树
        }else{
            root.left = buildTree(root.left, val);//递归创建右子树
        }
        return root;
    }
}
```
