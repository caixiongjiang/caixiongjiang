## 编号2034：股票价格波动(×)

给你一支股票价格的数据流。数据流中每一条记录包含一个 时间戳 和该时间点股票对应的 价格 。

不巧的是，由于股票市场内在的波动性，股票价格记录可能不是按时间顺序到来的。某些情况下，有的记录可能是错的。如果两个有相同时间戳的记录出现在数据流中，前一条记录视为错误记录，后出现的记录 更正 前一条错误的记录。

请你设计一个算法，实现：

* **更新**股票在某一时间戳的股票价格，如果有之前同一时间戳的价格，这一操作将 更正 之前的错误价格。
* 找到当前记录里**最新股票价格**。**最新股票价格**定义为时间戳最晚的股票价格。
* 找到当前记录里股票的**最高价格**。
* 找到当前记录里股票的**最低价格**。
请你实现 StockPrice 类：

* StockPrice() 初始化对象，当前无股票价格记录。
* void update(int timestamp, int price) 在时间点 timestamp 更新股票价格为 price 。
* int current() 返回股票**最新价格**。
* int maximum() 返回股票**最高价格**。
* int minimum() 返回股票**最低价格**。
 

示例 1：
```
输入：
["StockPrice", "update", "update", "current", "maximum", "update", "maximum", "update", "minimum"]
[[], [1, 10], [2, 5], [], [], [1, 3], [], [4, 2], []]
输出：
[null, null, null, 5, 10, null, 5, null, 2]

解释：
StockPrice stockPrice = new StockPrice();
stockPrice.update(1, 10); // 时间戳为 [1] ，对应的股票价格为 [10] 。
stockPrice.update(2, 5);  // 时间戳为 [1,2] ，对应的股票价格为 [10,5] 。
stockPrice.current();     // 返回 5 ，最新时间戳为 2 ，对应价格为 5 。
stockPrice.maximum();     // 返回 10 ，最高价格的时间戳为 1 ，价格为 10 。
stockPrice.update(1, 3);  // 之前时间戳为 1 的价格错误，价格更新为 3 。
                          // 时间戳为 [1,2] ，对应股票价格为 [3,5] 。
stockPrice.maximum();     // 返回 5 ，更正后最高价格为 5 。
stockPrice.update(4, 2);  // 时间戳为 [1,2,4] ，对应价格为 [3,5,2] 。
stockPrice.minimum();     // 返回 2 ，最低价格时间戳为 4 ，价格为 2 。 
```
提示：

* 1 <= timestamp, price <= 109
* update，current，maximum 和 minimum 总 调用次数不超过 105 。
* current，maximum 和 minimum 被调用时，update 操作 至少 已经被调用过 一次 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/stock-price-fluctuation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

一道比较基础的数据结构题。我们需要观察题目的条件，来选择合适的数据结构存储信息。

我们需要的信息有：

* 每个时间戳对应的价格
* 当前的最晚时间戳
* 当前的最低价格
* 当前的最高价格
**记录时间戳对应的价格，自然想到用一个map或unordered_map，同时因为要求最晚时间，所以考虑使用有序数据结构map。**

**记录最低和最高价格，考虑使用有序数据结构set，但这里可能出现重复的价格，所以使用multiset。**当然，也可以使用map来维护每个价格出现的次数。

* 各操作时间复杂度均为O(logN)。
* 空间复杂度O(N)。

整体代码如下：
```c++
class StockPrice {
    multiset<int> prices;
    map<int, int> history;
    
public:
    StockPrice() {}
    
    void update(int timestamp, int price) {
        if (history.count(timestamp))//此函数对具有特定键的元素进行计数，如果包含键的元素存在，则返回1，如果容器中不存在具有键的元素，则返回0。
            prices.erase(prices.find(history[timestamp]));//erase方法用来从一个map中删除掉指定的节点
        history[timestamp] = price;
        prices.insert(price);
    }
    
    int current() {
        return history.rbegin()->second;//rbegin()返回一个指向map尾部的逆向迭代器
    }
    
    int maximum() {
        return *prices.rbegin();
    }
    
    int minimum() {
        return *prices.begin();//指向map头部
    }
};



/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */
```