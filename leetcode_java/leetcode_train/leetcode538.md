## 把二叉树搜索树转换为累加树

给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

提醒一下，二叉搜索树满足下列约束条件：

节点的左子树仅包含键 小于 节点键的节点。
节点的右子树仅包含键 大于 节点键的节点。
左右子树也必须是二叉搜索树。
注意：本题和 [1038](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode1038.md) 相同

 

示例 1：
![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/05/03/tree.png)

```
输入：[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
输出：[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
```
示例 2：
```
输入：root = [0,null,1]
输出：[1,null,1]
```
示例 3：
```
输入：root = [1,0,2]
输出：[3,3,2]
```
示例 4：
```
输入：root = [3,2,4,1]
输出：[7,9,4,10] 
```
提示：

* 树中的节点数介于 0 和 104 之间。
* 每个节点的值介于 -104 和 104 之间。
* 树中的所有值 互不相同 。
* 给定的树为二叉搜索树。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/convert-bst-to-greater-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---

## 思路

**换一个角度来看，这就是一个有序数组[2, 5, 13]，求从后到前的累加数组，也就是[20, 18, 13]，是不是感觉这就简单了。**

为什么变成数组就是感觉简单了呢？

因为数组大家都知道怎么遍历啊，从后向前，挨个累加就完事了，这换成了二叉搜索树，看起来就别扭了一些是不是。

那么知道如何遍历这个二叉树，也就迎刃而解了，从树中可以看出累加的顺序是右中左，所以我们需要反中序遍历这个二叉树，然后顺序累加就可以了。

## 递归
遍历顺序如图所示：
![avater](https://camo.githubusercontent.com/10bf49200c0f9d2574ebc7eb2c27e2fd64fd2e86c3caf79c5631cdf7c73b842b/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303230343135333434303636362e706e67)
本题依然需要一个pre指针记录当前遍历节点cur的前一个节点，这样才方便做累加。

代码如下：

```java
class Solution {
    int sum;
    public TreeNode convertBST(TreeNode root) {
        sum = 0;
        myConvertBST(root);
        return root;
    }
    //按右中左的顺序遍历，进行累加即可
    public void myConvertBST(TreeNode root){
        if(root == null){
            return;
        }
        myConvertBST(root.right);
        sum += root.val;
        root.val = sum;
        myConvertBST(root.left);
    }
}
```