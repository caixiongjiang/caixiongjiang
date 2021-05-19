## 编号654：最大二叉树
给定一个不含重复元素的整数数组 nums 。一个以此数组直接递归构建的 最大二叉树 定义如下：

二叉树的根是数组 nums 中的最大元素。
左子树是通过数组中 最大值左边部分 递归构造出的最大二叉树。
右子树是通过数组中 最大值右边部分 递归构造出的最大二叉树。
返回有给定数组 nums 构建的 最大二叉树 。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2020/12/24/tree1.jpg)
```
输入：nums = [3,2,1,6,0,5]
输出：[6,3,5,null,2,0,null,null,1]
解释：递归调用如下所示：
- [3,2,1,6,0,5] 中的最大值是 6 ，左边部分是 [3,2,1] ，右边部分是 [0,5] 。
    - [3,2,1] 中的最大值是 3 ，左边部分是 [] ，右边部分是 [2,1] 。
        - 空数组，无子节点。
        - [2,1] 中的最大值是 2 ，左边部分是 [] ，右边部分是 [1] 。
            - 空数组，无子节点。
            - 只有一个元素，所以子节点是一个值为 1 的节点。
    - [0,5] 中的最大值是 5 ，左边部分是 [0] ，右边部分是 [] 。
        - 只有一个元素，所以子节点是一个值为 0 的节点。
        - 空数组，无子节点。
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2020/12/24/tree2.jpg)
```
输入：nums = [3,2,1]
输出：[3,null,2,null,1]
```

提示：

* 1 <= nums.length <= 1000
* 0 <= nums[i] <= 1000
* nums 中的所有整数 互不相同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
最大二叉树的构建过程如下：

![avater](https://camo.githubusercontent.com/6613e2180acd1cd85438e1bd899d96ef181321e6e58abe8d1f7a1973113362f8/68747470733a2f2f747661312e73696e61696d672e636e2f6c617267652f30303865476d5a456c7931676e626a7576696f657a673330647730393231636b2e676966)

</br>构造树一般采用的是前序遍历，因为先构造中间节点，然后递归构造左子树和右子树。
* 确定递归函数的参数和返回值
```java
TreeNode constructMaxTree(int[] nums,int left,int right)
```
* 确定终止条件

</br><span style="color:green">题目中说了输入的数组大小一定是大于等于1的，所以我们不用考虑小于1的情况，**那么当递归遍历的时候，如果传入的数组大小为1，说明遍历到了叶子节点了。**</span>

那么应该定义一个新的节点，并把这个数组的数值赋给新的节点，然后返回这个节点。 这表示一个数组大小是1的时候，构造了一个新的节点，并返回。
```java
if(right-left < 1){     //指针之差小于1，说明没有元素了
    return null;
}
if(right-left==1){      //子树为叶子节点的情况
    return new TreeNode(nums[left]);
}
```
* 确定单层递归的逻辑
</br>1.先要找到数组中最大的值和对应的下表， 最大的值构造根节点，下表用来下一步分割数组

```java
int maxIndex=left;//最大值所在的位置
        int maxValue=nums[maxIndex];//最大值
        for(int i=left+1;i < right;i++){    //  左闭右开原则
            if(nums[i]>maxValue){
                maxIndex=i;
                maxValue=nums[i];
            }
        }
        TreeNode root=new TreeNode(maxValue);
```
</br>2.最大值所在的下表左区间 构造左子树
</br>3.最大值所在的下表右区间 构造右子树

整体代码如下：
```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public TreeNode constructMaximumBinaryTree(int[] nums) {
        return constructMaxTree(nums,0,nums.length);
    }
    
    public TreeNode constructMaxTree(int[] nums,int left,int right){
        if(right-left < 1){     //指针之差小于1，说明没有元素了
            return null;
        }
        if(right-left==1){      //子树为叶子节点的情况
            return new TreeNode(nums[left]);
        }
        int maxIndex=left;//最大值所在的位置
        int maxValue=nums[maxIndex];//最大值
        for(int i=left+1;i < right;i++){    //  左闭右开原则
            if(nums[i]>maxValue){
                maxIndex=i;
                maxValue=nums[i];
            }
        }
        TreeNode root=new TreeNode(maxValue);
        //根据maxValue划分子树
        root.left=constructMaxTree(nums,left,maxIndex);//此处（）的left是上一次递归得到的left
        root.right=constructMaxTree(nums,maxIndex+1,right);//此处（）的right是上一次递归得到的right
        return root;
    }
}
```