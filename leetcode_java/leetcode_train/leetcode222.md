## 编号222：完全二叉树的节点个数

给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。

完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层，则该层包含 1~ 2h 个节点。

 

示例 1：
![avater](https://assets.leetcode.com/uploads/2021/01/14/complete.jpg)

```
输入：root = [1,2,3,4,5,6]
输出：6
```
示例 2：
```
输入：root = []
输出：0
```
示例 3：
```
输入：root = [1]
输出：1 
```
提示：

* 树中节点的数目范围是[0, 5 * 104]
* 0 <= Node.val <= 5 * 104
* 题目数据保证输入的树是 完全二叉树
 

**进阶**：遍历树来统计节点是一种时间复杂度为 O(n) 的简单解决方案。你可以设计一个更快的算法吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-complete-tree-nodes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
1.普通二叉树的写法
</br>2.完全二叉树的写法

### 普通二叉树
#### 递归写法
```java
class Solution {
    public int countNodes(TreeNode root) {
        if(root == null){
            return 0;
        }
        return countNodes(root.left) + countNodes(root.right) + 1;
    }
}
```
#### 迭代写法(层序遍历)
```java
class Solution {
    public int countNodes(TreeNode root) {
        if(root==null){
            return 0;
        }
        Queue<TreeNode> queue=new LinkedList<TreeNode>();
        queue.offer(root);
        int result = 0;
        while(!queue.isEmpty()){
            int levelSize = queue.size();
            for(int i = 0;i<levelSize;i++){
                TreeNode node = queue.poll();
                result++;
                if(node.left !=null){
                    queue.offer(node.left);
                }
                if(node.right !=null){
                    queue.offer(node.right);
                }
            }
        }
        return result;
    }
}
```
### 完全二叉树
完全二叉树只有两种情况，情况一：就是满二叉树，情况二：最后一层叶子节点没有满。

对于情况一，可以直接用 2^树深度 - 1 来计算，注意这里根节点深度为1。

对于情况二，分别递归左孩子，和右孩子，递归到某一深度一定会有左孩子或者右孩子为满二叉树，然后依然可以按照情况1来计算。
</br>图一：

![avater](https://camo.githubusercontent.com/5d85c9f8df419ce8db22f668ff22f7a3ae55660b8e9bead3b98e2d8cdd69ac9c/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132343039323534333636322e706e67)

</br>图二：

![avater](https://camo.githubusercontent.com/9dda2135e7216b78bcd3d71377dfa37ae7dc8b262add58376383c58db9e3c97a/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132343039323633343133382e706e67)
可以看出如果整个树不是满二叉树，就递归其左右孩子，直到遇到满二叉树为止，用公式计算这个子树（满二叉树）的节点数量。
</br>**写法一：**

```java
class Solution {
    public int countNodes(TreeNode root) {
        if(root == null){
            return 0;
        }
        TreeNode left = root.left;
        TreeNode right= root.right;
        int leftHeight = 0,rightHeight = 0;
        while(left != null){
            left=left.left;
            leftHeight++;
        }
        while(right != null){
            right=right.right;
            rightHeight++;
        }
        if(leftHeight == rightHeight){
            return (2<<leftHeight)-1;
        }
        return countNodes(root.left)+countNodes(root.right)+1; 
    }
}
```
</br>**写法二：**

```java
class Solution {
    public int countNodes(TreeNode root) {
        if(root == null){
           return 0;
        } 
        int left = countLevel(root.left);
        int right = countLevel(root.right);
        if(left == right){
            return countNodes(root.right) + (1<<left);
        }else{
            return countNodes(root.left) + (1<<right);
        }
    }
    private int countLevel(TreeNode root){
        int level = 0;
        while(root != null){
            level++;
            root = root.left;
        }
        return level;
    }
}
```