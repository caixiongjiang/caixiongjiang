## 编号1207：独一无二出现的次数

给你一个整数数组 arr，请你帮忙统计数组中每个数的出现次数。

如果每个数的出现次数都是独一无二的，就返回 true；否则返回 false。

 

示例 1：
```
输入：arr = [1,2,2,1,1,3]
输出：true
解释：在该数组中，1 出现了 3 次，2 出现了 2 次，3 只出现了 1 次。没有两个数的出现次数相同。
```
示例 2：
```
输入：arr = [1,2]
输出：false
```
示例 3：
```
输入：arr = [-3,0,1,-3,1,1,1,-3,10,0]
输出：true 
```
提示：

* 1 <= arr.length <= 1000
* -1000 <= arr[i] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-number-of-occurrences
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

本题强调了-1000 <= arr[i] <= 1000，那么就可以用数组来做哈希，arr[i]作为哈希表（数组）的下标，那么arr[i]可以是负数，怎么办？负数不能做数组下标。

此时可以定义一个2000大小的数组，例如int count[2002];，统计的时候，将arr[i]统一加1000，这样就可以统计arr[i]的出现频率了。

题目中要求的是是否有相同的频率出现，那么需要再定义一个哈希表（数组）用来记录频率是否重复出现过，bool fre[1002]; 定义布尔类型的就可以了，**因为题目中强调1 <= arr.length <= 1000，所以哈希表大小为1000就可以了。**

如图所示：
![avater](https://camo.githubusercontent.com/a88e85abc1e5334eaac06bc00fd8790bf1aca3c466d0e5c5191cc8541174d56a/68747470733a2f2f636f64652d7468696e6b696e672e63646e2e626365626f732e636f6d2f706963732f313230372ee78bace4b880e697a0e4ba8ce79a84e587bae78eb0e6aca1e695b02e706e67)

c++代码如下：
```c++
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        int count[2002] = {0};//统计数字出现的频率
        for(int i = 0; i < arr.size(); i++){
            count[arr[i] + 1000]++;//数的范围是-1000~1000，将数值加上1000作为下标
        }
        bool fre[1002] = {false};//看相同频率是否重复出现
        for(int i = 0; i <= 2000; i++){
            if(count[i]){ //count[i]大于0
                if(count[i]){
                    //若次数为count[i]出现过，就返回false，若没出现过就迭代bool数组fre的值 
                    if(fre[count[i]] == false) fre[count[i]] = true;
                    else return false;
                }
            }
        }
        return true;
    }
};
```