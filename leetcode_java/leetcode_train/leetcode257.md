## 编号257：二叉树的所有路径

给定一个二叉树，返回所有从根节点到叶子节点的路径。

说明: 叶子节点是指没有子节点的节点。

示例:
```
输入:

   1
 /   \
2     3
 \
  5

输出: ["1->2->5", "1->3"]

解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3
```
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-paths
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
<span style="color:green">**这道题目要求从根节点到叶子的路径，所以需要前序遍历，这样才方便让父节点指向孩子节点，找到对应的路径。**</span>

在这道题目中将第一次涉及到回溯，因为我们要把路径记录下来，需要回溯来回退一一个路径在进入另一个路径。

前序遍历以及回溯的过程如图：

![avater](https://camo.githubusercontent.com/874f41d965adfe0ef03e0ba9ad81dbed1b074eea229ab8c301ee7b7583639d8a/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303230343135313730323434332e706e67)
我们先使用递归的方式，来做前序遍历。***要知道递归和回溯就是一家的，本题也需要回溯。***

## 递归
1.递归函数函数参数以及返回值
要传入根节点，记录每一条路径的path，和存放结果集的result，这里递归不需要返回值，代码如下：
```java
public void traversal(TreeNode cur, vector<int> path,vector<string> result)
```
2.确定递归终止条件
再写递归的时候都习惯了这么写：
```java
if (cur == NULL) {
    终止处理逻辑
}
```
但是本题的终止条件这样写会很麻烦，因为本题要找到叶子节点，就开始结束的处理逻辑了（把路径放进result里）。

那么什么时候算是找到了叶子节点？ <span style="color:red">**是当 cur不为空，其左右孩子都为空的时候，就找到叶子节点。**</span>

所以本题的终止条件是：
```java
if (cur.left == null && cur.right == null) {
    终止处理逻辑
}
```
为什么没有判断cur是否为空呢，因为下面的逻辑可以控制空节点不入循环。

再来看一下终止处理的逻辑。

这里使用vector 结构path来记录路径，所以要把vector 结构的path转为string格式，在把这个string 放进 result里。

那么为什么使用了vector 结构来记录路径呢？ ***因为在下面处理单层递归逻辑的时候，要做回溯，使用vector方便来做回溯。***

可能有的同学问了，我看有些人的代码也没有回溯啊。

其实是有回溯的，只不过隐藏在函数调用时的参数赋值里，下文我还会提到。

这里我们先使用vector结构的path容器来记录路径，那么终止处理逻辑(c++)如下：
```c++
if (cur->left == NULL && cur->right == NULL) { // 遇到叶子节点
    string sPath;
    for (int i = 0; i < path.size() - 1; i++) { // 将path里记录的路径转为string格式
        sPath += to_string(path[i]);
        sPath += "->";
    }
    sPath += to_string(path[path.size() - 1]); // 记录最后一个节点（叶子节点）
    result.push_back(sPath); // 收集一个路径
    return;
}
```
3.确定单层递归逻辑
因为是前序遍历，需要先处理中间节点，中间节点就是我们要记录路径上的节点，先放进path中。

path.push_back(cur->val);

然后是递归和回溯的过程，上面说过没有判断cur是否为空，那么在这里递归的时候，如果为空就不进行下一层递归了。

所以递归前要加上判断语句，下面要递归的节点是否为空，如下(c++)
```c++
if (cur->left) {
    traversal(cur->left, path, result);
}
if (cur->right) {
    traversal(cur->right, path, result);
}
```
此时还没完，递归完，要做回溯啊，因为path 不能一直加入节点，它还要删节点，然后才能加入新的节点。

<span style="color:green">**回溯和递归是一一对应的，有一个递归，就要有一个回溯.**</span>

那么代码应该这么写：(c++)
```c++
if (cur->left) {
    traversal(cur->left, path, result);
    path.pop_back(); // 回溯
}
if (cur->right) {
    traversal(cur->right, path, result);
    path.pop_back(); // 回溯
}
```

### java中的StringBuilder类

**注**：如果程序对附加字符串的需求很频繁，不建议使用+来进行字符串的串联。可以考虑使用java.lang.StringBuilder 类，使用这个类所产生的对象默认会有16个字符的长度，可以自行指定初始长度。***如果附加的字符超出可容纳的长度，则StringBuilder 对象会自动增加长度以容纳被附加的字符***。如果有频繁作字符串附加的需求，使用StringBuilder 类能使效率大大提高。

(1)Append 方法可用来将文本或对象的字符串表示形式添加到由当前 StringBuilder对象表示的字符串的结尾处。以下示例将一个 StringBuilder对象初始化为“Hello World”，然后将一些文本追加到该对象的结尾处。将根据需要自动分配空间。
```java
StringBuilderMyStringBuilder = new StringBuilder("Hello World!");
MyStringBuilder.Append(" What a beautiful day.");
Console.WriteLine(MyStringBuilder);
```
此示例将 Hello World! What abeautiful day.显示到控制台。

(2)AppendFormat 方法将文本添加到 StringBuilder的结尾处，而且实现了 IFormattable接口，因此可接受格式化部分中描述的标准格式字符串。可以使用此方法来自定义变量的格式并将这些值追加到 StringBuilder的后面。以下示例使用 AppendFormat方法将一个设置为货币值格式的整数值放置到 StringBuilder的结尾。
```java
int MyInt= 25;
StringBuilder MyStringBuilder = new StringBuilder("Your total is ");
MyStringBuilder.AppendFormat("{0:C} ", MyInt);
Console.WriteLine(MyStringBuilder);
```
此示例将 Your total is $25.00显示到控制台。

(3)Insert 方法将字符串或对象添加到当前 StringBuilder中的指定位置。以下示例使用此方法将一个单词插入到 StringBuilder的第六个位置。
```java
StringBuilderMyStringBuilder = new StringBuilder("Hello World!");
MyStringBuilder.Insert(6,"Beautiful ");
Console.WriteLine(MyStringBuilder);
```
此示例将 Hello BeautifulWorld!显示到控制台。

(4)可以使用 Remove方法从当前 StringBuilder中移除指定数量的字符，移除过程从指定的从零开始的索引处开始。以下示例使用 Remove方法缩短 StringBuilder。
```java
StringBuilderMyStringBuilder = new StringBuilder("Hello World!");
MyStringBuilder.Remove(5,7);
Console.WriteLine(MyStringBuilder);
```
此示例将 Hello显示到控制台。

(5)使用 Replace方法，可以用另一个指定的字符来替换 StringBuilder对象内的字符。以下示例使用 Replace方法来搜索 StringBuilder对象，查找所有的感叹号字符 (!)，并用问号字符 (?)来替换它们。
```java
StringBuilderMyStringBuilder = new StringBuilder("Hello World!");
MyStringBuilder.Replace('!', '?');
Console.WriteLine(MyStringBuilder);
```

</br></br></br></br>
整体代码如下（java）：

```java
class Solution {
    /**
     * 递归回溯法
     */
    public List<String> binaryTreePaths(TreeNode root) {
        List<String> res = new ArrayList<>();
        if(root == null){
            return res;
        }
        List<Integer> paths =new ArrayList<>();
        traversal(root, paths, res);
        return res;
    }

    private void traversal(TreeNode root, List<Integer> paths, List<String> res){
        paths.add(root.val);
        //叶子节点
        if(root.left == null && root.right == null){
            //输出
            StringBuilder sb = new StringBuilder();
            for(int i = 0; i < paths.size() - 1; i++){
                sb.append(paths.get(i)).append("->");
            }
            sb.append(paths.get(paths.size() - 1));
            res.add(sb.toString());
            return;
        }
        if(root.left != null){
            traversal(root.left, paths, res);
            paths.remove(paths.size() -1);//回溯
        }
        if(root.right != null){
            traversal(root.right, paths, res);
            paths.remove(paths.size() - 1);//回溯
        }
    }
}


//解法二（常规前序遍历，不用回溯），更容易理解
class Solution {
    public List<String> binaryTreePaths(TreeNode root) {
        List<String> res = new ArrayList<>();
        helper(root, new StringBuilder(), res);
        return res;
    }

    public void helper(TreeNode root, StringBuilder sb, List<String> res) {
        if (root == null) {return;}
      	// 遇到叶子结点就放入当前路径到res集合中
        if (root.left == null && root.right ==null) {
            sb.append(root.val);
            res.add(sb.toString());
          	// 记得结束当前方法
            return;
        }
        helper(root.left,new StringBuilder(sb).append(root.val + "->"),res);
        helper(root.right,new StringBuilder(sb).append(root.val + "->"),res);
    }
}
```
