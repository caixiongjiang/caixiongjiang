## 编号450：删除二叉搜索树中的节点 

给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。

一般来说，删除节点可分为两个步骤：

1.首先找到需要删除的节点；
2.如果找到了，删除它。
说明： 要求算法时间复杂度为 O(h)，h 为树的高度。

示例:
```
root = [5,3,6,2,4,null,7]
key = 3

    5
   / \
  3   6
 / \   \
2   4   7

给定需要删除的节点值是 3，所以我们首先找到 3 这个节点，然后删除它。

一个正确的答案是 [5,4,6,2,null,null,7], 如下图所示。

    5
   / \
  4   6
 /     \
2       7

另一个正确答案是 [5,2,6,null,4,null,7]。

    5
   / \
  2   6
   \   \
    4   7
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/delete-node-in-a-bst
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---

## 思路

搜索树节点删除比节点插入要复杂很多，有很多情况需要考虑。

二叉搜索树同时也是一颗平衡二叉树，平衡二叉树删除节点的情况：
* 第一种情况：没找到删除的节点，遍历到空节点直接返回了
* 找到删除的节点：
</br>1.第二种情况：左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
</br>2.第三种情况：删除节点的左孩子为空，右孩子不为空，删除节点，右孩子补位，返回右孩子为根节点
</br>3.第四种情况：删除节点的右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为根节点
</br>4.第五种情况：左右孩子节点都不为空，则将删除节点的左子树头结点（左孩子）放到删除节点的右子树的最左面节点的左孩子上，返回删除节点右孩子为新的根节点。

第五种情况的情景如下所示：
![avater](https://camo.githubusercontent.com/4a6ff55863bf30ec834ec9fb9d7bde209f4ecc33b71869ba7d55de4cd14ab970/68747470733a2f2f747661312e73696e61696d672e636e2f6c617267652f30303865476d5a456c7931676e626a336b3539366d673330647130616967797a2e676966)


代码如下：
```java
class Solution {
    public TreeNode deleteNode(TreeNode root, int key) {
        if(root == null) return null;//第一种情况：没找到删除的节点
        if(root.val == key){
            //第二种情况:左右孩子都为空（叶子节点），直接删除节点，返回null为根节点
            //第三种情况：其左孩子为空，右孩子不为空，删除节点，右孩子补位，返回右孩子为新的根节点
            //注意这里没有写第二种情况的判断语句是因为对第三种情况的判断已经包含了第二种情况
            if(root.left == null) return root.right;
            //第四种情况：其右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为新的根节点
            else if(root.right == null) return root.left;
            //第五种情况：左右孩子节点都不为空，则将删除节点的左子树头结点（左孩子）放到删除节点的右子树的最左面节点的左孩子上，返回删除节点右孩子为新的根节点。
            else{
                TreeNode cur = root.right;
                while(cur.left != null){
                    cur = cur.left;//找到了右子树最左边的节点
                }
                cur.left = root.left;//把要删除的节点（root）左子树放在cur的左孩子的位置
                root = root.right;//进行删除，返回旧root的右孩子作为新的root
                return root;
            }
        }
        if(root.val > key){
            root.left = deleteNode(root.left, key);//递归向左调用
        }
        if(root.val < key){
            root.right = deleteNode(root.right, key);//递归向右调用
        }
        return root;
    }
}
```