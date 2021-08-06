## 编号17：电话号码的字母组合

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按**任意顺序**返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
![avater](https://camo.githubusercontent.com/0a88f57a4edfba769988b2efcbab005bbebdd6b2fdd98a3228499bbd3a7d667a/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032303130323931363432343034332e706e67)



 

示例 1：
```
输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
```
示例 2：
```
输入：digits = ""
输出：[]
```
示例 3：
```
输入：digits = "2"
输出：["a","b","c"] 
```
提示：

* 0 <= digits.length <= 4
* digits[i] 是范围 ['2', '9'] 的一个数字。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
从示例上来说，输入"23"，最直接的想法就是两层for循环遍历了吧，正好把组合的情况都输出了。

如果输入"233"呢，那么就三层for循环，如果"2333"呢，就四层for循环.......

大家应该感觉出和回溯算法：[求组合问题！](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode77.md)遇到的一样的问题，就是这for循环的层数如何写出来，此时又是回溯法登场的时候了。

理解本题后，要解决如下三个问题：

1.数字和字母如何映射
2.两个字母就两个for循环，三个字符我就三个for循环，以此类推，然后发现代码根本写不出来
3.输入1 * #按键等等异常情况
## 数字和字母的映射
```java
String[] numString = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
```

## 回溯法解决n个for循环的问题
例如：输入："23"，抽象为树形结构，如图所示：
![avater](https://camo.githubusercontent.com/e3ea2109e556ee3dec50d10bd777bd8361a198f347f1fd15e633291d51b924e3/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333230303330343436392e706e67)

* 确定回溯函数参数
首先需要一个字符串s来收集叶子节点的结果，然后用一个字符串数组result保存起来，这两个变量我依然定义为全局。

再来看参数，参数指定是有题目中给的string digits，然后还要有一个参数就是int型的index。
这个index是记录遍历第几个数字了，就是用来遍历digits的（题目中给出数字字符串），同时index也表示树的深度。
```java
List<String> result;
String s;
public void backtracking(String digits,String[] numString, int index)
```
* 确定终止条件
例如输入用例"23"，两个数字，那么根节点往下递归两层就可以了，叶子节点就是要收集的结果集。

那么终止条件就是如果index 等于 输入的数字个数（digits.size）了（本来index就是用来遍历digits的）。

然后收集结果，结束本层递归。
* 确定单层遍历逻辑
```java
for(int i = 0; i < str.length(); i++){
	temp.append(str.charAt(i));
        backTracking(digits, numString, num + 1);
        //回溯：剔除末尾的继续尝试
        temp.deleteCharAt(temp.length() - 1);
}
```
注意这里for循环，可不像是在[回溯算法：求组合问题！](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode77.md)和[回溯算法：求组合总和！](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode216.md)中从startIndex开始遍历的。

因为本题每一个数字代表的是不同集合，也就是求不同集合之间的组合，而[77. 组合](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode77.md)和[216.组合总和III](https://github.com/caixiongjiang/caixiongjiang/blob/main/leetcode_java/leetcode_train/leetcode216.md)都是是求同一个集合中的组合！


整体代码如下：
```java
class Solution {
    List<String> result = new ArrayList<>();
    
    public List<String> letterCombinations(String digits) {
        if(digits == null || digits.length() == 0){
            return result;
        }
        //初始对应所有的数字，为了对应2-9，新增了两个无效的字符串""
        String[] numString = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        //迭代处理
        backTracking(digits, numString, 0);
        return result;
    }
    //每次迭代获取一个字符串，所以会设计大量的字符串拼接，所以这里选择更为高效的 StringBuilder
    StringBuilder temp = new StringBuilder();
    //比如digits如果为"23",num 为0，则str表示2对应的 abc
    //num表示numString数组的下标
    public void backTracking(String digits, String[] numString, int num){
        //遍历全部一次记录一次得到的字符串
        if(num == digits.length()){
            result.add(temp.toString());
            return;
        }
        //str表示当前num对应的字符串
        String str = numString[digits.charAt(num) - '0'];
        for(int i = 0; i < str.length(); i++){
            temp.append(str.charAt(i));
            backTracking(digits, numString, num + 1);
            //回溯：剔除末尾的继续尝试
            temp.deleteCharAt(temp.length() - 1);
        }
    }
}
```