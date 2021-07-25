## 编号113：路径总和Ⅱ

给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。

叶子节点 是指没有子节点的节点。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/01/18/pathsumii1.jpg)
```
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：[[5,4,11,2],[5,8,4,5]]
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/01/18/pathsum2.jpg)
```
输入：root = [1,2,3], targetSum = 5
输出：[]
```
示例 3：
```
输入：root = [1,2], targetSum = 0
输出：[]
```
提示：

树中节点总数在范围 [0, 5000] 内
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/path-sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

路径总和II要遍历整个树，找到所有路径，所以递归函数不要返回值！

如图：

![avater](https://camo.githubusercontent.com/4cf59332f4ee49ed732cbb25c9d42c6d9611b67e48af9a2cc3e8ec98a126aded/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303230333136303932323734352e706e67)

代码如下：

```java
class Solution {
    public List<List<Integer>> pathSum(TreeNode root, int targetSum) {
        List<List<Integer>> res = new ArrayList<>();
        if(root == null) return res;

        List<Integer> path = new LinkedList<>();
        preOrderDFS(root, targetSum, res, path);
        return res;
    }

    public void preOrderDFS(TreeNode cur, int targetSum, List<List<Integer>> res,List<Integer> path){
        path.add(cur.val);//将遍历的节点加入path路径
        if(cur.left == null && cur.right == null){
            if(targetSum - cur.val == 0){
                res.add(new ArrayList<>(path));
            }
            return;
        }

        if(cur.left != null){
            preOrderDFS(cur.left, targetSum - cur.val, res, path);
            path.remove(path.size()-1);//回溯
        }

        if(cur.right != null){
            preOrderDFS(cur.right, targetSum - cur.val, res, path);
            path.remove(path.size()-1);//回溯
        }
    }
}
```