## 编号968：监控二叉树
给定一个二叉树，我们在树的节点上安装摄像头。

节点上的每个摄影头都可以监视其父对象、自身及其直接子对象。

计算监控树的所有节点所需的最小摄像头数量。

 

示例 1：
![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/29/bst_cameras_01.png)

```
输入：[0,0,null,0,0]
输出：1
解释：如图所示，一台摄像头足以监控所有节点。
```
示例 2：
![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/29/bst_cameras_02.png)

```
输入：[0,0,null,0,null,0,null,null,0]
输出：2
解释：需要至少两个摄像头来监视树的所有节点。 上图显示了摄像头放置的有效位置之一。
```
提示：

1.给定树的节点数的范围是 [1, 1000]。
</br>2.每个节点的值都是 0。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-cameras
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
本题思考的问题就是如何才能让摄像头的数量最少？从题目中的示例可以看出**摄像头都没有放在叶子节点上！** 
</br>为什么不从头结点开始看起呢，为啥要从叶子节点看呢？

因为头结点放不放摄像头也就省下一个摄像头， 叶子节点放不放摄像头省下了的摄像头数量是指数阶别的。

**所以我们要从下往上看，局部最优：让叶子节点的父节点安摄像头，所用摄像头最少，整体最优：全部摄像头数量所用最少！**

这道题目有两个难点：

* 二叉树的遍历
* 如何隔两个节点放一个摄像头

## 确定遍历顺序
可以使用后序遍历也就是左右中的顺序，这样就可以在回溯的过程中从下到上进行推导了
</br>后续遍历模板如下：

```java
    public int traversal(TreeNode cur) {

        // 空节点，该节点有覆盖
        if (终止条件) return ;

        int left = traversal(cur.left);    // 左
        int right = traversal(cur.right);  // 右

        逻辑处理                            // 中
        return ;
    }
```
**注意在以上代码中我们取了左孩子的返回值，右孩子的返回值，即left 和 right， 以后推导中间节点的状态**

## 如何隔两个节点放一个摄像头
每个节点可能有几种状态：

有如下三种：

* 该节点无覆盖
* 本节点有摄像头
* 本节点有覆盖
我们分别有三个数字来表示：

* 0：该节点无覆盖
* 1：本节点有摄像头
* 2：本节点有覆盖

</br><span style="color:red">在遍历树的过程中，就会遇到空节点，那么问题来了，空节点究竟是哪一种状态呢？ 空节点表示无覆盖？ 表示有摄像头？还是有覆盖呢？</span>
回归本质，为了让摄像头数量最少，我们要尽量让叶子节点的父节点安装摄像头，这样才能摄像头的数量最少。

那么空节点不能是无覆盖的状态，这样叶子节点就要放摄像头了，空节点也不能是有摄像头的状态，这样叶子节点的父节点就没有必要放摄像头了，而是可以把摄像头放在叶子节点的爷爷节点上。

**所以空节点的状态只能是有覆盖，这样就可以在叶子节点的父节点放摄像头了**

接下来就是递推关系。

那么递归的终止条件应该是遇到了空节点，此时应该返回2（有覆盖），原因上面已经解释过了。

</br>代码如下：
```java
//空节点，该节点右覆盖
if(cur == null) return 2;
```


递归的函数，以及终止条件已经确定了，再来看单层逻辑处理。

主要有如下四类情况：
* 情况1：左右节点都有覆盖
</br>左孩子有覆盖，右孩子有覆盖，那么此时中间节点应该就是无覆盖的状态了。

如图：

![avater](https://camo.githubusercontent.com/79ff2c1a6ad7495309e21769b7a724df6ac02014b96896eaa03bc38c614cbd4f/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313232393230333731303732392e706e67)

代码如下：
```java
// 左右节点都有覆盖
if (left == 2 && right == 2) return 0;
```

* 情况2：左右节点至少有一个无覆盖的情况
如果是以下情况，则中间节点（父节点）应该放摄像头：

left == 0 && right == 0 左右节点无覆盖 left == 1 && right == 0 左节点有摄像头，右节点无覆盖 left == 0 && right == 1 左节点有无覆盖，右节点摄像头 left == 0 && right == 2 左节点无覆盖，右节点覆盖 left == 2 && right == 0 左节点覆盖，右节点无覆盖

这个不难理解，毕竟有一个孩子没有覆盖，父节点就应该放摄像头。

此时摄像头的数量要加一，并且return 1，代表中间节点放摄像头。

代码如下：
```java
if(left == 0 || right == 0){
    result++;
    return 1;
}
```

* 情况3：左右节点至少有一个有摄像头
</br>如果是以下情况，其实就是 左右孩子节点有一个有摄像头了，那么其父节点就应该是2（覆盖的状态）

left == 1 && right == 2 左节点有摄像头，右节点有覆盖 left == 2 && right == 1 左节点有覆盖，右节点有摄像头 left == 1 && right == 1 左右节点都有摄像头

代码如下：
```java
if(left == 1 || right == 1) return 2;
```

**从这个代码中，可以看出，如果left == 1，right == 0怎么办？其实这种条件在情况2中已经判断过了**，如图：
![avater](https://camo.githubusercontent.com/02a99f06434d9828a9c0b1f0e6e14a3d413f4d29ead3e5a1abdec30f947d8536/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032303132323932303336323335352e706e67)

* 情况4：头结点没有覆盖
以上都处理完了，递归结束之后，可能头结点 还有一个无覆盖的情况，如图：
![avater](https://camo.githubusercontent.com/d7687fbaab8c727b61350a9771ff17a800a652c6c31da7bdf51146fa218b7aa7/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313232393230333734323434362e706e67)\

所以递归结束之后，还要判断根节点，如果没有覆盖，result++，代码如下：
```java
int minCameraCover(TreeNode root) {
    result = 0;
    if (traversal(root) == 0) { // root 无覆盖
        result++;
    }
    return result;
}
```
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
    private int count = 0;
    public int minCameraCover(TreeNode root) {
        if (trval(root) == 0) count++;
        return count;
    }

    private int trval(TreeNode root) {
        if (root == null) return -1;

        int left = trval(root.left);
        int right = trval(root.right);

        if (left == 0 || right == 0) {
            count++;
            return 2;
        }

        if (left == 2 || right == 2) {
            return 1;
        }

        return 0;
    }
}
```