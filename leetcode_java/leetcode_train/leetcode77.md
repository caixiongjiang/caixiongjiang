## 编号77：组合

给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。

你可以按**任何顺序**返回答案。

 

示例 1：
```
输入：n = 4, k = 2
输出：
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```
示例 2：
```
输入：n = 1, k = 1
输出：[[1]]
```
提示：

* 1 <= n <= 20
* 1 <= k <= n

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combinations
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---

## 思路

直接解法就是使用for循环，这样就可以直接输出和示例中一样的结果。
</br>
但如果n = 100，k = 50,那就50层for循环，该如何写？
**回溯法解决的问题都可以抽象为树形结构（N叉树），用树形结构来理解回溯就容易多了。**

那么我把组合问题抽象为如下树形结构：
![avater](https://camo.githubusercontent.com/339ef1f1660cad426b63173d3a4f52c66ce9237fbee51ba245994eb34375400b/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333139353232333934302e706e67)

可以看出这个棵树，一开始集合是 1，2，3，4， 从左向右取数，取过的数，不在重复取。

第一次取1，集合变为2，3，4 ，因为k为2，我们只需要再取一个数就可以了，分别取2，3，4，得到集合[1,2] [1,3] [1,4]，以此类推。

**每次从集合中选取元素，可选择的范围随着选择的进行而收缩，调整可选择的范围。**

图中可以发现n相当于树的宽度，k相当于树的深度。

那么如何在这个树上遍历，然后收集到我们要的结果集呢？

**图中每次搜索到了叶子节点，我们就找到了一个结果。**

相当于只需要把达到叶子节点的结果收集起来，就可以求得 n个数中k个数的组合集合。

## 回溯法三部曲
* 递归函数的返回值以及参数
这里要定义两个全局变量，一个用来存放符合条件单一结果，一个用来存放符合条件结果的集合。
代码如下(c++):
```c++
vector<vector<int>> result; // 存放符合条件结果的集合
vector<int> path; // 用来存放符合条件结果
```

函数里一定有两个参数，既然是集合n里面取k的数，那么n和k是两个int型的参数。

然后还需要一个参数，为int型变量startIndex，这个参数用来记录本层递归的中，集合从哪里开始遍历（集合就是[1,...,n] ）。

每次从集合中选取元素，可选择的范围随着选择的进行而收缩，调整可选择的范围，就是要靠startIndex。

<span style="color:green">**从下图中红线部分可以看出，在集合[1,2,3,4]取1之后，下一层递归，就要在[2,3,4]中取数了，那么下一层递归如何知道从[2,3,4]中取数呢，靠的就是startIndex。**</span>
![avater](https://camo.githubusercontent.com/625a45f9e4f060f5fe958b7563bc2d9738695da2a09d8228844e27ced2541a91/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333139353332383937362e706e67)

* 回溯函数终止条件

path这个数组的大小如果达到k，说明我们找到了一个子集大小为k的组合了，在图中path存的就是根节点到叶子节点的路径。

如图红色部分：

![avater](https://camo.githubusercontent.com/3fc93087e14863740e9e6a2e1273db45f6921af80552a758c2ceb29fbfeb40b8/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333139353430373930372e706e67)

此时用result二维数组，将path保存起来，并终止本层递归，所以终止条件代码如下：
```java
if(path.size() == k){
    result.add(path);
    return;
}
```

* 单层搜索的结果
回溯法的搜索过程就是一个树型结构的遍历过程，在如下图中，可以看出for循环用来横向遍历，递归的过程是纵向遍历。
![avater](https://camo.githubusercontent.com/33d520a983f316935dd6b5bc3401160705c0a5050ce9feaf4e2a1a2d8db40799/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333139353234323839392e706e67)

### 完整代码如下：
```java
class Solution {
    List<List<Integer>> result = new ArrayList<>();
    LinkedList<Integer> path = new LinkedList<>();
    public List<List<Integer>> combine(int n, int k) {
        combineHelper(n, k, 1);
        return result;
    }

    /**
     * 每次从集合中选取元素，可选择的范围随着选择的进行而收缩，调整可选择的范围，就是要靠startIndex
     * @param startIndex 用来记录本层递归的中，集合从哪里开始遍历（集合就是[1,...,n] ）。
     */
    private void combineHelper(int n, int k, int startIndex){
        //终止条件
        if (path.size() == k){
            result.add(new ArrayList<>(path));
            return;
        }
        for (int i = startIndex; i <= n; i++){
            path.add(i);
            combineHelper(n, k, i + 1);
            path.removeLast();
        }
    }
}
```

## 剪枝优化

举一个例子，n = 4，k = 4的话，那么第一层for循环的时候，从元素2开始的遍历都没有意义了。 在第二层for循环，从元素3开始的遍历都没有意义了。

如图所示：
![avater](https://camo.githubusercontent.com/1d9148107548d853ba1f58b0507cb85835dc4aed5be588e21f280458b63b05b3/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303133303139343333353230372e706e67)

图中每一个节点（图中为矩形），就代表本层的一个for循环，那么每一层的for循环从第二个数开始遍历的话，都没有意义，都是无效遍历。

**所以，可以剪枝的地方就在递归中每一层的for循环所选择的起始位置。**

**如果for循环选择的起始位置之后的元素个数 已经不足 我们需要的元素个数了，那么就没有必要搜索了。**

注意代码中i，就是for循环里选择的起始位置。
```java
for(int i = startIndex; i <= n; i++){}
```
看一下优化的过程：
</br>1.已经选择的元素的个数：path.size();
</br>2.还需要的元素个数：k - path.size();
</br>3.在集合n中至多要从该起始位置：n - (k - path.size()) + 1,开始遍历。
</br>为什么要 +1 呢，因为包括起始位置，我们要的是一个左闭的集合
</br>举个例子，n = 4,k = 3,目前已经选取的元素为0(path.size()为0),n-(k-0)+1即为2。
从2开始搜索，组合[2,3,4]。
</br>所以优化后的for循环是：

```java
for(int i = startIndex; i <= n - (k - path.size()) + 1; i++){}
```
剪枝优化后的整体代码如下：
```java
class Solution {
    List<List<Integer>> result = new ArrayList<>();
    LinkedList<Integer> path = new LinkedList<>();
    public List<List<Integer>> combine(int n, int k) {
        combineHelper(n, k, 1);
        return result;
    }

    /**
     * 每次从集合中选取元素，可选择的范围随着选择的进行而收缩，调整可选择的范围，就是要靠startIndex
     * @param startIndex 用来记录本层递归的中，集合从哪里开始遍历（集合就是[1,...,n] ）。
     */
    private void combineHelper(int n, int k, int startIndex){
        //终止条件
        if (path.size() == k){
            result.add(new ArrayList<>(path));
            return;
        }
        for (int i = startIndex; i <= n - (k - path.size()) + 1; i++){
            path.add(i);
            combineHelper(n, k, i + 1);
            path.removeLast();
        }
    }
}

```