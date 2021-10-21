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
## 思路

注意题目提示内容，：

* 你只能使用常量级额外空间。
* 使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。

基本上就是要求使用递归了，迭代的方式一定会用到栈或者队列。

## 递归

一想用递归怎么做呢，虽然层序遍历是最直观的，但是递归的方式确实不好想。

如图，假如当前操作的节点是cur：
![avater](https://camo.githubusercontent.com/3b60f368fe9d0d491e635976ea10aa5f1820c6a625f4e18c7518b1a26dd89c5d/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f3131362ee5a1abe58585e6af8fe4b8aae88a82e782b9e79a84e4b88be4b880e4b8aae58fb3e4bea7e88a82e782b9e68c87e99288312e706e67)

图中cur节点为元素4，那么搭线的逻辑代码：(**注意注释中操作1和操作2和图中的对应关系**）
```c++
if (cur->left) cur->left->next = cur->right; // 操作1
if (cur->right) {
    if (cur->next) cur->right->next = cur->next->left; // 操作2
    else cur->right->next = NULL;
}
```

使用前序遍历，整体代码如下：

```c++
class Solution {
private:
    void traversal(Node* cur) {
        if (cur == NULL) return;
                                // 中
        if (cur->left) cur->left->next = cur->right; // 操作1
        if (cur->right) {
            if (cur->next) cur->right->next = cur->next->left; // 操作2
            else cur->right->next = NULL;
        }
        traversal(cur->left);   // 左
        traversal(cur->right);  // 右
    }
public:
    Node* connect(Node* root) {
        traversal(root);
        return root;
    }
};
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