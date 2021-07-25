## 编号112：路径总和

给你二叉树的根节点 root 和一个表示目标和的整数 targetSum ，判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。

叶子节点 是指没有子节点的节点。

 

示例 1：
![avater](https://assets.leetcode.com/uploads/2021/01/18/pathsum1.jpg)

```
输入：root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
输出：true
```

示例 2：

![avater](https://assets.leetcode.com/uploads/2021/01/18/pathsum2.jpg)
```
输入：root = [1,2,3], targetSum = 5
输出：false
```
示例 3：

```
输入：root = [1,2], targetSum = 0
输出：false
```
提示：

* 树中节点的数目在范围 [0, 5000] 内
* -1000 <= Node.val <= 1000
* -1000 <= targetSum <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/path-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

注意：不要去累加然后判断是否等于目标和，那么代码比较麻烦，可以用递减，让计数器count初始为目标和，然后每次减去遍历路径节点上的数值。

如果最后count == 0，同时到了叶子节点的话，说明找到了目标和。

如果遍历到了叶子节点，count不为0，就是没找到。

![avater](https://camo.githubusercontent.com/218e8b14468c8d1eed6f35ae0300f6d491373b7aced7b6dbe21ef9fc5e76554c/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032313032303331363035313231362e706e67)


代码如下：

```java
class Solution {
    public boolean hasPathSum(TreeNode root, int targetSum) {
        if(root == null) return false;
        return traversal(root, targetSum - root.val);
    }

    private boolean traversal(TreeNode cur, int value){
        if(cur.left == null && cur.right == null && value == 0) return true;
        if(cur.left == null && cur.right == null) return false;

        if(cur.left != null){
            value -= cur.left.val;//递归，处理节点
            if(traversal(cur.left, value) != false) return true;
            value += cur.left.val;//回溯，撤销处理结果
        }
        if(cur.right != null){
            value -= cur.right.val;//递归，处理节点
            if(traversal(cur.right, value) != false) return true;
            value += cur.right.val;//回溯，撤销处理结果
        }
        return false;
    }
}
```