## 编号332：重新安排行程
给你一份航线列表 tickets ，其中 tickets[i] = [fromi, toi] 表示飞机出发和降落的机场地点。请你对该行程进行重新规划排序。

所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 开始。如果存在多种有效的行程，请你按字典排序返回最小的行程组合。

* 例如，行程 ```["JFK", "LGA"]``` 与 ```["JFK", "LGB"]``` 相比就更小，排序更靠前。
假定所有机票至少存在一种合理的行程。且所有的机票 必须都用一次 且 只能用一次。

 

示例 1：

![avater](https://assets.leetcode.com/uploads/2021/03/14/itinerary1-graph.jpg)
```
输入：tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
输出：["JFK","MUC","LHR","SFO","SJC"]
```
示例 2：

![avater](https://assets.leetcode.com/uploads/2021/03/14/itinerary2-graph.jpg)

```
输入：tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
输出：["JFK","ATL","JFK","SFO","ATL","SFO"]
解释：另一种有效的行程是 ["JFK","SFO","ATL","JFK","ATL","SFO"] ，但是它字典排序更大更靠后。 
```
提示：

* 1 <= tickets.length <= 300
* tickets[i].length == 2
* fromi.length == 3
* toi.length == 3
* fromi 和 toi 由大写英文字母组成
* fromi != toi

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reconstruct-itinerary
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
这道题目有几个难点：

* 一个行程中，如果航班处理不好容易变成一个圈，成为死循环
* 有多种解法，字母序靠前排在前面，让很多同学望而退步，如何该记录映射关系呢 ？
* 使用回溯法（也可以说深搜） 的话，那么终止条件是什么呢？
* 搜索的过程中，如何遍历一个机场所对应的所有机场。

## 如何理解死循环

对于死循环，我来举一个有重复机场的例子：
![avater](https://camo.githubusercontent.com/1167df66a930780e3ea31db4e493add98f1d3582ca16037abda577f24189324f/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313131353138303533373836352e706e67)

出发机场和到达机场也会重复，**如果在解题的过程中没有对集合元素处理好，就会死循环。**

## 如何记录映射关系

一个机场映射多个机场，机场之间要靠字母序排列，一个机场映射多个机场，可以使用std::unordered_map，如果让多个机场之间再有顺序的话，就是用std::map 或者std::multimap 或者 std::multiset。

<span style="color:green">**为什么一定要增删元素呢，正如开篇我给出的图中所示，出发机场和到达机场是会重复的，搜索的过程没及时删除目的机场就会死循环。所以搜索的过程中就是要不断的删multiset里的元素**</span>

在遍历targets的过程中**可以使用"航班次数"这个字段的数字做相应的增减，来标记到达机场是否使用过了。**

如果“航班次数”大于零，说明目的地还可以飞，如果如果“航班次数”等于零说明目的地不能飞了，而不用对集合做删除元素或者增加元素的操作。

**相当于说我不删，我就做一个标记！**

## 回溯法

回溯模板如下：
```java
public void backtracking(参数) {
    if (终止条件) {
        存放结果;
        return;
    }

    for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) {
        处理节点;
        backtracking(路径，选择列表); // 递归
        回溯，撤销处理结果
    }
}
```
本题以输入：[["JFK", "KUL"], ["JFK", "NRT"], ["NRT", "JFK"]为例，抽象为树形结构如下：

![avater](https://camo.githubusercontent.com/97fc71990118675e1736bf595445afc0e4593fa13d02ea9a85df16151c8df01f/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032303131313531383036353535352e706e67)

## 回溯三部曲

* 递归函数参数
在讲解映射关系的时候，已经讲过了，使用```Map<String, Map<String, Integer>> map;``` 来记录航班的映射关系，我定义为全局变量。
参数里还需要ticketNum，表示有多少个航班（终止条件会用上）。

代码如下：
```java
private Deque<String> res;
private Map<String, Map<String, Integer>> map;
private boolean backTracking(int ticketNum)
```
**注意这里的返回值为boolean**
</br>一般函数返回值都是void，这次为什么是boolean呢？

因为我们只需要找到一个行程，就是在树形结构中唯一的一条通向叶子节点的路线，如图：
![avater](https://camo.githubusercontent.com/97fc71990118675e1736bf595445afc0e4593fa13d02ea9a85df16151c8df01f/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032303131313531383036353535352e706e67)
所以找到了这个叶子节点了直接返回!

* 递归终止条件
拿题目中的示例为例，输入: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]] ，这是有4个航班，那么只要找出一种行程，行程里的机场个数是5就可以了。

所以终止条件是：**我们回溯遍历的过程中，遇到的机场个数，如果达到了（航班数量+1），那么我们就找到了一个行程，把所有航班串在一起了。**

代码如下：
```java
if (result.size() == ticketNum + 1) {
    return true;
}
```

* 单层搜索的逻辑

遍历过程如下：
```java
if(map.containsKey(last)){//防止出现null
   	for(Map.Entry<String, Integer> target : map.get(last).entrySet()){
		int count = target.getValue();
        if(count > 0){
                res.add(target.getKey());
                target.setValue(count - 1);
                if(backTracking(ticketNum)) return true;
                res.removeLast();
                target.setValue(count);
        }
}
```

## Java中Map的 entrySet() 详解以及用法(四种遍历map的方式)

[Map的 entrySet() 用法](https://blog.csdn.net/q5706503/article/details/85122343)


整体代码如下：
```java
class Solution {
    private Deque<String> res;
    private Map<String, Map<String, Integer>> map;

    private boolean backTracking(int ticketNum){
        if(res.size() == ticketNum + 1){
            return true;
        }
        String last = res.getLast();
        if(map.containsKey(last)){//防止出现null
            for(Map.Entry<String, Integer> target : map.get(last).entrySet()){
                int count = target.getValue();
                if(count > 0){
                    res.add(target.getKey());
                    target.setValue(count - 1);
                    if(backTracking(ticketNum)) return true;
                    res.removeLast();
                    target.setValue(count);
                }
            }
        }
        return false;
    }

    public List<String> findItinerary(List<List<String>> tickets) {
        map = new HashMap<String, Map<String, Integer>>();
        res = new LinkedList<>();
        for(List<String> t : tickets){//这个for循环是为了用map构造邻接表
            Map<String, Integer> temp;
            if(map.containsKey(t.get(0))){
                temp = map.get(t.get(0));
                temp.put(t.get(1), temp.getOrDefault(t.get(1), 0) + 1);
            }else{
                temp = new TreeMap<>();//升序Map
                temp.put(t.get(1), 1);
            }
            map.put(t.get(0), temp);

        }
        res.add("JFK");
        backTracking(tickets.size());
        return new ArrayList<>(res);
    }
}
```















