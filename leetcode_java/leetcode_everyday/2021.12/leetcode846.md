## 编号846:一手顺子

Alice 手中有一把牌，她想要重新排列这些牌，分成若干组，使每一组的牌数都是 groupSize ，并且由 groupSize 张连续的牌组成。

给你一个整数数组 hand 其中 hand[i] 是写在第 i 张牌，和一个整数 groupSize 。如果她可能重新排列这些牌，返回 true ；否则，返回 false 。

 

示例 1：
```
输入：hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
输出：true
解释：Alice 手中的牌可以被重新排列为 [1,2,3]，[2,3,4]，[6,7,8]。
```
示例 2：
```
输入：hand = [1,2,3,4,5], groupSize = 4
输出：false
解释：Alice 手中的牌无法被重新排列成几个大小为 4 的组。 
```
提示：

* 1 <= hand.length <= 104
* 0 <= hand[i] <= 109
* 1 <= groupSize <= hand.length

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/hand-of-straights
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

题目要求按照从小到大重新排序，而且每个子数组都要有序增加（组成顺子），所以需要对原数组进行排序。


### 排序+哈希

具体步骤：

1.先对原数组进行排序，再遍历数组加入无序map，map中存放的是元素和元素出现的次数

2.第二次遍历数组，查找他在map中的次数，如果为0则跳过，如果不为0则作为一组顺子的起点

3.对每一个递增的值进行判断是否存在map中，如果不存在就返回false



代码如下：
```c++
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        unordered_map<int, int> cnt;
        sort(hand.begin(), hand.end());
        for (auto &h: hand) {
            cnt[h]++;
        }
        for (int i = 0; i < hand.size(); i++) {
            if (cnt[hand[i]] == 0) continue;
            for (int j = 0; j < groupSize; j++) {
                if (cnt[hand[i]+ j] == 0) return false;
                cnt[hand[i] + j]--;
            }
        }
        return true;
    }
};
```

### 纯哈希

这段代码与上述思路相同，但是使用的是map的自动排序功能，最后遍历的也是map容器，细节要稍微复杂一点（遍历的逻辑不同）。

遍历数组只要一个一个向后推，这里遍历map需要value值为0时，才能往后推迭代器


具体步骤：

1.遍历数组加入map，map中存放的是元素和元素出现的次数

2.遍历map容器，每一次将第一个key值作为一组顺子的起点，寻找完一组顺子后立马在map中找第一个value值不为0的迭代器进行逻辑判断

3.对每一组顺子进行判断是否存在map中，如果不存在就返回false



代码如下：
```c++
class Solution{
public:
    bool isNStraightHand(vector<int> &hand, int groupSize){
        if(hand.size() % groupSize != 0) return false;
        int m = hand.size() / groupSize;
        map<int, int> cnt;
        for(auto &x : hand) cnt[x]++;
        map<int, int>::iterator it = cnt.begin();
        int index = 1;
        while(index <= m){
            int temp = it->first;//每一组顺子的起点
            //cout << temp << endl;
            for(int j = 0; j < groupSize; j++){
                if(cnt[temp + j] == 0) return false;
                cnt[temp + j]--;
            }
            index++;
            while(it->second == 0 && it != cnt.end()) it++;
        }
        return true;
    }
};
```