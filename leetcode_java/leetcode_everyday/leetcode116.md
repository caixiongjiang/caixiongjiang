## 编号116：填充每个节点的下一个右侧节点指针

给定一个 完美二叉树 ，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：
```c++
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

初始状态下，所有 next 指针都被设置为 NULL。

 

进阶：

* 你只能使用常量级额外空间。
* 使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。
 

示例：

![avater](https://assets.leetcode.com/uploads/2019/02/14/116_sample.png)

```
输入：root = [1,2,3,4,5,6,7]
输出：[1,#,2,3,#,4,5,6,7,#]
解释：给定二叉树如图 A 所示，你的函数应该填充它的每个 next 指针，以指向其下一个右侧节点，如图 B 所示。序列化的输出按层序遍历排列，同一层节点由 next 指针连接，'#' 标志着每一层的结束。 
```
提示：

* 树中节点的数量少于 4096
* -1000 <= node.val <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 递归

整体代码如下：
```c++

```

## 迭代（层序遍历）

整体代码如下：
```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        queue<Node*> que;
        if (root != NULL) que.push(root);
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            Node* nodePre;
            Node* node;
            for (int i = 0; i < size; i++) { // 开始每一层的遍历
                if (i == 0) {
                    nodePre = que.front(); // 记录一层的头结点
                    que.pop();
                    node = nodePre;
                } else {
                    node = que.front();
                    que.pop();
                    nodePre->next = node; // 本层前一个节点next指向本节点
                    nodePre = nodePre->next;
                }
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            nodePre->next = NULL; // 本层最后一个节点指向NULL
        }
        return root;
    }
};
```


```c++
//写法二
class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return root;
        }
        
        // 初始化队列同时将第一层节点加入队列中，即根节点
        queue<Node*> Q;
        Q.push(root);
        
        // 外层的 while 循环迭代的是层数
        while (!Q.empty()) {
            
            // 记录当前队列大小
            int size = Q.size();
            
            // 遍历这一层的所有节点
            for(int i = 0; i < size; i++) {
                
                // 从队首取出元素
                Node* node = Q.front();
                Q.pop();
                
                // 连接
                if (i < size - 1) {
                    node->next = Q.front();
                }
                
                // 拓展下一层节点
                if (node->left != nullptr) {
                    Q.push(node->left);
                }
                if (node->right != nullptr) {
                    Q.push(node->right);
                }
            }
        }
        
        // 返回根节点
        return root;
    }
};
```