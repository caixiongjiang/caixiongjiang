## 编号105：前序遍历和后续遍历构造二叉树

给定一棵树的前序遍历 preorder 与中序遍历  inorder。请构造二叉树并返回其根节点。

 

示例 1:

![avater](https://assets.leetcode.com/uploads/2021/02/19/tree.jpg)
```
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
```
示例 2:
```
Input: preorder = [-1], inorder = [-1]
Output: [-1]
```
提示:

* 1 <= preorder.length <= 3000
* inorder.length == preorder.length
* -3000 <= preorder[i], inorder[i] <= 3000
* preorder 和 inorder 均无重复元素
* inorder 均出现在 preorder
* preorder 保证为二叉树的前序遍历序列
* inorder 保证为二叉树的中序遍历序列

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路


以前序数组的第一个元素为切割点，先切中序数组，根据中序数组，反过来在切前序数组。一层一层切下去，每次后序数组最后一个元素就是节点元素。
</br>思路和 后序数组+中序数组 -->得到一棵树 基本一致

一共分为六步：


* 第一步：如果数组大小为零的话，说明是空节点了。

* 第二步：如果不为空，那么取前序数组的第一个元素作为节点元素。

* 第三步：找到后序数组最后一个元素在中序数组的位置，作为切割点

* 第四步：切割中序数组，切成中序左数组和中序右数组 （顺序别搞反了，一定是先切中序数组）

* 第五步：切割前序数组，切成前序左数组和前序右数组

* 第六步：递归处理左区间和右区间


代码如下：

```java
class Solution {
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        return helpBuildTree(preorder, 0, preorder.length, inorder, 0, inorder.length);
    }
    /**
    由于设计递归的子区间的划分，这里统一使用左闭右开的原则：
    preLeft,preRight分别代表前序序列的边界
    inLeft,inRight分别代表中序序列的边界
     */
    public TreeNode helpBuildTree(int[] preorder, int preLeft, int preRight, int[] inorder, int inLeft, int inRight){                                  
        //递归终止条件
        if(inRight - inLeft < 1) return null;
        if(inRight - inLeft == 1){
            return new TreeNode(inorder[inLeft]);
        }
        
        //rootVal 为前序遍历的第一个节点的值，也就是根节点的值
        //rootIndex 为根节点在中序序列中的位置
        int rootVal = preorder[preLeft];
        TreeNode root = new TreeNode(rootVal);
        
        
        // 根据根结点的值找到该值在中序数组inorder里的位置
        int rootIndex = 0;
        for(int i = inLeft; i < inRight; i++){
            if(inorder[i] == rootVal){
                rootIndex = i;
                break;
            }
        }
        //划分左右子树,此处子区间边界的确定需要画一个例子更加容易明白
        root.left = helpBuildTree(preorder, preLeft + 1, preLeft + (rootIndex - inLeft) + 1, inorder, inLeft, rootIndex);
        root.right = helpBuildTree(preorder, preLeft + (rootIndex - inLeft) + 1, preRight, inorder, rootIndex + 1, inRight);
        return root;
    }
}
```