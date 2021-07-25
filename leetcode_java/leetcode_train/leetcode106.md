## 编号106：中序和后序遍历序列构造二叉树

根据一棵树的中序遍历与后序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出
```
中序遍历 inorder = [9,3,15,20,7]
后序遍历 postorder = [9,15,7,20,3]
```
返回如下的二叉树：

```
    3
   / \
  9  20
    /  \
   15   7
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

以后序数组的最后一个元素为切割点，先切中序数组，根据中序数组，反过来在切后序数组。一层一层切下去，每次后序数组最后一个元素就是节点元素。

如果让我们肉眼看两个序列，画一颗二叉树的话，应该分分钟都可以画出来。

流程如图：

![avater](https://camo.githubusercontent.com/4ed69d4938c961bfb8b4b53cfafff5a5b3671fc663f120009e4724940974207c/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303230333135343234393836302e706e67)\

说到一层一层切割，就应该想到了递归。

来看一下一共分几步：

* 第一步：如果数组大小为零的话，说明是空节点了。

* 第二步：如果不为空，那么取后序数组最后一个元素作为节点元素。

* 第三步：找到后序数组最后一个元素在中序数组的位置，作为切割点

* 第四步：切割中序数组，切成中序左数组和中序右数组 （顺序别搞反了，一定是先切中序数组）

* 第五步：切割后序数组，切成后序左数组和后序右数组

* 第六步：递归处理左区间和右区间


代码如下：

```java
class Solution {
    public TreeNode buildTree(int[] inorder, int[] postorder) {
        return buildTree1(inorder, 0, inorder.length, postorder, 0, postorder.length);
    }
    /** 
    inLeft和inRight为中序遍历的边界
    postLeft和postRight为后序遍历的边界
    这里使用左闭右开的写法
    */
    
    public TreeNode buildTree1(int[] inorder, int inLeft, int inRight, 
                               int[] postorder, int postLeft, int postRight){
        //没有元素了
        if(inRight - inLeft < 1){
            return null;
        }
        //只有一个元素了
        if(inRight - inLeft == 1){
            return new TreeNode(inorder[inLeft]);
        }
        //后序数组postorder里的最后一个节点就是根节点
        int rootVal = postorder[postRight - 1];
        TreeNode root = new TreeNode();
        root.val = rootVal;
        
        //根据根节点的值找到该值在中序数组inorder里的位置
        int rootIndex = 0;
        for(int i = inLeft; i < inRight; i++){
            if(inorder[i] == rootVal){
                rootIndex = i;
            }
        }
        //根据rootIndex划分左右子树
        root.left = buildTree1(inorder, inLeft, rootIndex, 
                               postorder, postLeft, postLeft + (rootIndex - inLeft));
        root.right = buildTree1(inorder, rootIndex + 1, inRight, 
                                postorder, postLeft + (rootIndex - inLeft), postRight - 1);
        return root; 
    }
}
```