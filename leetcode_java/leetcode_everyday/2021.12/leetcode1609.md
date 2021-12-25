## 编号1609:奇偶树

如果一棵二叉树满足下述几个条件，则可以称为 奇偶树 ：

二叉树根节点所在层下标为 0 ，根的子节点所在层下标为 1 ，根的孙节点所在层下标为 2 ，依此类推。
偶数下标 层上的所有节点的值都是 奇 整数，从左到右按顺序 严格递增
奇数下标 层上的所有节点的值都是 偶 整数，从左到右按顺序 严格递减
给你二叉树的根节点，如果二叉树为 奇偶树 ，则返回 true ，否则返回 false 。

 

示例 1：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/04/sample_1_1966.png)

```
输入：root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
输出：true
解释：每一层的节点值分别是：
0 层：[1]
1 层：[10,4]
2 层：[3,7,9]
3 层：[12,8,6,2]
由于 0 层和 2 层上的节点值都是奇数且严格递增，而 1 层和 3 层上的节点值都是偶数且严格递减，因此这是一棵奇偶树。
```
示例 2：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/04/sample_2_1966.png)

```
输入：root = [5,4,2,3,3,7]
输出：false
解释：每一层的节点值分别是：
0 层：[5]
1 层：[4,2]
2 层：[3,3,7]
2 层上的节点值不满足严格递增的条件，所以这不是一棵奇偶树。
```
示例 3：

![avater](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/04/sample_1_333_1966.png)

```
输入：root = [5,9,1,3,5,7]
输出：false
解释：1 层上的节点值应为偶数。
```
示例 4：
```
输入：root = [1]
输出：true
```
示例 5：
```
输入：root = [11,8,6,1,3,9,11,30,20,18,16,12,10,4,2,17]
输出：true 
```
提示：

* 树中节点数在范围 [1, 10^5] 内
* 1 <= Node.val <= 10^6

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/even-odd-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

思路很简单，就是层序遍历加一点判断！注意事项我会在代码里注释！

代码如下：
```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        queue<TreeNode*> que;
        if(root != NULL) que.push(root);
        int cnt = 0;
        int temp = 0;
        while(!que.empty()){
            int size = que.size();
            vector<int> vec;
            //注意这里必须使用不变的size而不是que.size()，因为它一直在变
            for(int i = 0; i < size; i++){
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                /*判断逻辑*/
                if(cnt % 2 == 0){
                    if(node->val % 2 == 0) return false;
                    else if(vec.size() > 1 && node->val <= temp) return false;
                }else{
                    if(node->val % 2 == 1) return false;
                    else if(vec.size() > 1 && node->val >= temp) return false;
                }

                //使用temp记录上一个节点的值。
                //因为是在一个节点与其比较，必须放在判断之后
                temp = vec.back();
                //cout << temp << endl;
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
            cnt++;
        }
        return true;
    }
};
```