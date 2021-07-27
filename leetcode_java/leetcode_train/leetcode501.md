## 编号501：二叉搜索树中的众数

给定一个有相同值的二叉搜索树（BST），找出 BST 中的所有众数（出现频率最高的元素）。

假定 BST 有如下定义：

* 结点左子树中所含结点的值小于等于当前结点的值
* 结点右子树中所含结点的值大于等于当前结点的值
* 左子树和右子树都是二叉搜索树
例如：

给定 BST [1,null,2,2],
```
   1
    \
     2
    /
   2
```
返回[2].

提示：如果众数超过1个，不需考虑输出顺序

进阶：你可以不使用额外的空间吗？（假设由递归产生的隐式调用栈的开销不被计算在内）

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-mode-in-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 如果不是二叉搜索树

如果这不是一颗二叉搜索树，如果不是二叉搜索树，最直观的方法一定是把这个树都遍历了，用map统计频率，把频率排个序，最后取前面高频的元素的集合。

具体步骤如下：
* 这个树都遍历了，用map统计频率
* 把统计的出来的出现频率（即map中的value）排个序
* 取前面高频的元素

具体代码如下：

```java
class Solution {
	public int[] findMode(FindModeInBinarySearchTree.TreeNode root) {
		Map<Integer, Integer> map = new HashMap<>();
		List<Integer> list = new ArrayList<>();
		if (root == null) return list.stream().mapToInt(Integer::intValue).toArray();
		// 获得频率 Map
		searchBST(root, map);
		List<Map.Entry<Integer, Integer>> mapList = map.entrySet().stream()
				.sorted((c1, c2) -> c2.getValue().compareTo(c1.getValue()))
				.collect(Collectors.toList());
		list.add(mapList.get(0).getKey());
		// 把频率最高的加入 list
		for (int i = 1; i < mapList.size(); i++) {
			if (mapList.get(i).getValue() == mapList.get(i - 1).getValue()) {
				list.add(mapList.get(i).getKey());
			} else {
				break;
			}
		}
		return list.stream().mapToInt(Integer::intValue).toArray();
	}

	void searchBST(FindModeInBinarySearchTree.TreeNode curr, Map<Integer, Integer> map) {
		if (curr == null) return;
		map.put(curr.val, map.getOrDefault(curr.val, 0) + 1);
		searchBST(curr.left, map);
		searchBST(curr.right, map);
	}
}
```

### 按二叉搜索树的特性

注：在此题中左右孩子的节点值可以等于它的父节点
</br>
按照中序遍历二叉搜索树，依旧是一个有序数组，<span style="color:green">可以继续使用cur和pre两个指针去比较有序的前后两个节点的值.</span>
</br>如果相等就让count++，但存在一个问题，题目要求找出所有众数。
</br>如果先遍历一遍数组，找出最大频率，然后再重新遍历一遍数组把出现频率为maxCount的元素放入集合，这种方式遍历两遍数组。
</br>其实只需要遍历一遍数组，可以这样操作：频率count大于maxCount的时候，不仅要更新maxCount，而且要清空结果集(result数组)，因为之前的结果数组都失效了。
代码如下：

```java
if(count > maxCount){
    maxCount = count;//更新最大频率
    result.clear();//清空result集合
    result.add(cur.val);
}
```

整体代码如下：

```java
class Solution {
    ArrayList<Integer> result;
    int maxCount;
    int count;
    TreeNode pre;
    public int[] findMode(TreeNode root) {
        result = new ArrayList<>();
        maxCount = 0;
        count = 0;
        pre = null;
        myFindMode(root);
        //将ArrayList数组转化为int数组
        int[] res = new int[result.size()];
        for(int i = 0; i < result.size(); i++){
            res[i] = result.get(i);
        }
        return res;
    }

    public void myFindMode(TreeNode root){
        if(root == null){
            return;
        }
        myFindMode(root.left);

        int rootVal = root.val;//记录当前节点的值
        //计数
        if(pre == null || rootVal != pre.val){
            count = 1;
        }else{
            count++;
        }
        //更新结果以及maxCount
        if(count > maxCount){
            maxCount = count;
            result.clear();
            result.add(rootVal);
        }else if(count == maxCount){
            result.add(rootVal);
        }
        pre = root;
        myFindMode(root.right);
    }
}
```