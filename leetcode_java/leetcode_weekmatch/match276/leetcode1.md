## 编号：将字符串拆分为若干长度为 k 的组

字符串 s 可以按下述步骤划分为若干长度为 k 的组：

第一组由字符串中的前 k 个字符组成，第二组由接下来的 k 个字符串组成，依此类推。每个字符都能够成为 某一个 组的一部分。
对于最后一组，如果字符串剩下的字符 不足 k 个，需使用字符 fill 来补全这一组字符。
注意，在去除最后一个组的填充字符 fill（如果存在的话）并按顺序连接所有的组后，所得到的字符串应该是 s 。

给你一个字符串 s ，以及每组的长度 k 和一个用于填充的字符 fill ，按上述步骤处理之后，返回一个字符串数组，该数组表示 s 分组后 每个组的组成情况 。



示例 1：
```
输入：s = "abcdefghi", k = 3, fill = "x"
输出：["abc","def","ghi"]
解释：
前 3 个字符是 "abc" ，形成第一组。
接下来 3 个字符是 "def" ，形成第二组。
最后 3 个字符是 "ghi" ，形成第三组。
由于所有组都可以由字符串中的字符完全填充，所以不需要使用填充字符。
因此，形成 3 组，分别是 "abc"、"def" 和 "ghi" 。
```
示例 2：
```
输入：s = "abcdefghij", k = 3, fill = "x"
输出：["abc","def","ghi","jxx"]
解释：
与前一个例子类似，形成前三组 "abc"、"def" 和 "ghi" 。
对于最后一组，字符串中仅剩下字符 'j' 可以用。为了补全这一组，使用填充字符 'x' 两次。
因此，形成 4 组，分别是 "abc"、"def"、"ghi" 和 "jxx" 。
```
提示：

* 1 <= s.length <= 100
* s 仅由小写英文字母组成
* 1 <= k <= 100
* fill 是一个小写英文字母

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/divide-a-string-into-groups-of-size-k
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
---
## 思路

此题为字符串分割

解法有两种，先补齐字符串再分割，先分割再将最后的字符串进行处理。这里我采用的是后一种解法。

步骤：

每次字符超过k个就将其放入字符串数组，将最后的字符串加上指定字符再放入字符串数组

代码如下：
```c++
class Solution {
public:
    vector<string> divideString(string s, int k, char fill) {
        vector<string> res;
        string temp;
        int n = s.size(), cur = 1;
        
        for(int i = 0; i < n; ){
            if(cur <= k){
                temp += s[i];
                cur++;
                i++;
            }else{
                res.push_back(temp);
                temp.clear();
                cur = 1;
            }
        }
        //cout << temp << endl;
        //cout << k - temp.size() << endl;
        if(temp.size() == k){
            res.push_back(temp);
        }else{
            temp.append(k - temp.size(), fill);
            res.push_back(temp);
            //cout << temp << endl;
        }
        return res;
    }
};
```