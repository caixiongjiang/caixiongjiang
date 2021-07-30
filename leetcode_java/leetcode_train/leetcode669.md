## 编号669：修剪二叉搜索树

给你二叉搜索树的根节点 root ，同时给定最小边界low 和最大边界 high。通过修剪二叉搜索树，使得所有节点的值在[low, high]中。修剪树不应该改变保留在树中的元素的相对结构（即，***如果没有被移除，原有的父代子代关系都应当保留***）。 可以证明，存在唯一的答案。

所以结果应当返回修剪好的二叉搜索树的新的根节点。注意，根节点可能会根据给定的边界发生改变。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2020/09/09/trim1.jpg)
```
输入：root = [1,0,2], low = 1, high = 2
输出：[1,null,2]
```
示例 2：
![avater](https://assets.leetcode.com/uploads/2020/09/09/trim2.jpg)
```
输入：root = [3,0,4,null,2,null,null,1], low = 1, high = 3
输出：[3,2,null,1]
```
示例 3：
```
输入：root = [1], low = 1, high = 2
输出：[1]
```
示例 4：
```
输入：root = [1,null,2], low = 1, high = 3
输出：[1,null,2]
```
示例 5：
```
输入：root = [1,null,2], low = 2, high = 4
输出：[2] 
```
提示：

* 树中节点数在范围 [1, 104] 内
* 0 <= Node.val <= 104
* 树中每个节点的值都是唯一的
* 题目数据保证输入是一棵有效的二叉搜索树
* 0 <= low <= high <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/trim-a-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

直接想法就是：递归处理，然后遇到 root.val < low || root.val > high 的时候直接return NULL，一波修改，赶紧利落。


但其实并不是这样，当这个节点不在区间时，还要看他还有没孩子。如图：
![avater](https://camo.githubusercontent.com/78c968364d75716a9fd4aaef8c4874878c2fbac0f548ac801b4ff4da22988d47/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303230343135353330323735312e706e67)

从图中可以看出需要重构二叉树，想想是不是本题就有点复杂了。

其实不用重构那么复杂。

在上图中我们发现节点0并不符合区间要求，那么将节点0的右孩子 节点2 直接赋给 节点3的左孩子就可以了（就是把节点0从二叉树中移除），如图：
![avater](https://camo.githubusercontent.com/20aa1164ff2a4ded0e14d55e906f87a1d2f49c47af97f51c3dedb7fd6b6e81fa/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303230343135353332373230332e706e67)

<span style="color:green">当元素的值小于low，则应递归右子树，若大于high，则应递归左子树</span>

代码如下：
```java
class Solution {
    public TreeNode trimBST(TreeNode root, int low, int high) {
        if(root == null) return null;
        if(root.val < low){
            return trimBST(root.right, low, high);
        }
        if(root.val > high){
            return trimBST(root.left, low ,high);
        }
        //root在low和high之间
        root.left = trimBST(root.left, low, high);
        root.right = trimBST(root.right, low, high);
        return root;
    }
}
```




