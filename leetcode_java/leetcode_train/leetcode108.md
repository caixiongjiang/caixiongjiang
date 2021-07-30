## 编号108：将有序数组转换为二叉搜索树

给你一个整数数组 nums ，其中元素已经按**升序**排列，请你将其转换为一棵 高度平衡 二叉搜索树。

**高度平衡**二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/02/18/btree1.jpg)

```
输入：nums = [-10,-3,0,5,9]
输出：[0,-3,9,-10,null,5]
解释：[0,-10,5,null,-3,null,9] 也将被视为正确答案：
```
![avater](https://assets.leetcode.com/uploads/2021/02/18/btree2.jpg)

示例 2：
![avater](https://assets.leetcode.com/uploads/2021/02/18/btree.jpg)
```
输入：nums = [1,3]
输出：[3,1]
解释：[1,3] 和 [3,1] 都是高度平衡二叉搜索树。
```

提示：

* 1 <= nums.length <= 104
* -104 <= nums[i] <= 104
* nums 按**严格递增**顺序排列

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

题目中说要转换为一棵高度平衡二叉搜索树。这和转换为一棵普通二叉搜索树有什么差别呢？

其实这里不用强调平衡二叉搜索树，数组构造二叉树，构成平衡树是自然而然的事情，因为大家默认都是从数组中间位置取值作为节点元素，一般不会随机取，**所以想构成不平衡的二叉树是自找麻烦。**
</br>有序数组构造二叉搜索树，寻找分割点就比较容易了。

分割点就是数组中间位置的节点。
那么为问题来了，如果数组长度为偶数，中间节点有两个，取哪一个？

取哪一个都可以，只不过构成了不同的平衡二叉搜索树。

例如：输入：[-10,-3,0,5,9]

如下两棵树，都是这个数组的平衡二叉搜索树：
![avater](https://camo.githubusercontent.com/23a9861831a55d31b96d85f0ad2afa9be7929ba412d115a5176216f26ccd1e3b/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3130382e2545352542302538362545362539432538392545352542412538462545362539352542302545372542422538342545382542442541432545362538442541322545342542382542412545342542412538432545352538462538392545362539302539432545372542342541322545362541302539312e706e67)
如果要分割的数组长度为偶数的时候，中间元素为两个，是取左边元素 就是树1，取右边元素就是树2。

代码如下：(这里还是左闭右开的版本)
```java
class Solution {
    public TreeNode sortedArrayToBST(int[] nums) {
        return mySortedArrayToBST(nums, 0, nums.length);
    }

    public TreeNode mySortedArrayToBST(int[] nums, int left, int right){
        if(right - left < 1) return null;
        if(right - left == 1) return new TreeNode(nums[left]);
        int mid = left + (right - left)/2;
        TreeNode root = new TreeNode(nums[mid]);
        root.left = mySortedArrayToBST(nums, left, mid);
        root.right = mySortedArrayToBST(nums, mid + 1, right);
        return root;
    }
}
```

