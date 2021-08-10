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
        for(List<String> t : tickets){
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















