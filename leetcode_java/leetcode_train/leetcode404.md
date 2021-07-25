## 编号404：左叶子之和

计算给定二叉树的所有左叶子之和。
```
示例：

    3
   / \
  9  20
    /  \
   15   7
```
在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sum-of-left-leaves
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---

## 思路

因为题目中其实没有说清楚左叶子究竟是什么节点，那么我来给出左叶子的明确定义：<span style="color:green">***如果左节点不为空，且左节点没有左右孩子，那么这个节点就是左叶子***</span>

那么判断当前节点是不是左叶子是无法判断的，必须要通过节点的父节点来判断其左孩子是不是左叶子。

如果该节点的左节点不为空，该节点的左节点的左节点为空，该节点的左节点的右节点为空，则找到了一个左叶子，判断代码如下：
```java
if (node.left != null && node.left.left == null && node.left.right == null) {
    左叶子节点处理逻辑
}
```


代码如下：
```java
class Solution {
    public int sumOfLeftLeaves(TreeNode root) {
        if(root == null){
            return 0;
        }
        int leftValue = sumOfLeftLeaves(root.left);//左
        int rightValue = sumOfLeftLeaves(root.right);//右
        int value = 0;
        if(root.left != null && root.left.left == null && root.left.right == null){
            value = root.left.val;
        }
        int sum = value + leftValue + rightValue;
        return sum;
    }
}
```