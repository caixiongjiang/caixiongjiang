## 编号530：二叉搜索树的最小绝对差

给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两节点的差的绝对值的最小值。

 

示例：
```
输入：

   1
    \
     3
    /
   2

输出：
1

解释：
最小绝对差为 1，其中 2 和 1 的差的绝对值为 1（或者 2 和 3）。 
```
提示：

* 树中至少有 2 个节点。
* 本题与 783 https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes/ 相同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

题目中要求在二叉搜索树上任意两节点的差的绝对值的最小值。

注意是二叉搜索树，二叉搜索树可是有序的。

遇到在二叉搜索树上求什么最值啊，差值之类的，***就把它想成在一个有序数组上求最值，求差值***，这样就简单多了。

## 递归
按照当前思路一般是先将二叉搜索树转化为衣蛾有序数组，再遍历一遍数组，再统计最小的差值

</br>但其实只需要在中序遍历的过程中就可以进行比较了，不过需要用一个pre节点来记录cur(当前节点)的前一个节点，在比较的时候使用。

如图：

![avater](https://camo.githubusercontent.com/931af534c98dc189f90dc5bf4de923540e7b3f287c90cba33cad854f5653f815/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303230343135333234373435382e706e67)

代码如下：

```java
class Solution {
    TreeNode pre;//用来记录当前节点的前一个节点
    int result = Integer.MAX_VALUE;//全局变量，用来记录结果
    public int getMinimumDifference(TreeNode root) {
        if(root == null) return 0;
        traversal(root);
        return result;
    }

    public void traversal(TreeNode root){//中序遍历
        if(root == null) return;
        traversal(root.left);//左，进行递归
        if(pre != null){     //中，进行操作
            if((root.val - pre.val) < result){
                result = root.val - pre.val;
            }
        }
        pre = root;
        traversal(root.right);//右
    }
}
```

或者只用一个方法进行实现，代码如下：

```java
class Solution {
    TreeNode pre;// 记录上一个遍历的结点
    int result = Integer.MAX_VALUE;
    public int getMinimumDifference(TreeNode root) {
        if (root == null) {
            return result;
        }
        // 左
        int left = getMinimumDifference(root.left);
        
        // 中
        if (pre != null) {
            result = Math.min(left, root.val - pre.val);
        }
        pre = root;
        // 右
        int right = getMinimumDifference(root.right);
        result = Math.min(right, result);
        return result;
    }
}
```