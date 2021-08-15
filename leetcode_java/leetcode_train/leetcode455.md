## 编号455：分发饼干

假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。

对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

 
示例 1:
```
输入: g = [1,2,3], s = [1,1]
输出: 1
解释: 
你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
所以你应该输出1。
```
示例 2:
```
输入: g = [1,2], s = [1,2,3]
输出: 2
解释: 
你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
你拥有的饼干数量和尺寸都足以让所有孩子满足。
所以你应该输出2.
```
提示：

* 1 <= g.length <= 3 * 104
* 0 <= s.length <= 3 * 104
* 1 <= g[i], s[j] <= 231 - 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/assign-cookies
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路
为了了满足更多的小孩，就不要造成饼干尺寸的浪费。

大尺寸的饼干既可以满足胃口大的孩子也可以满足胃口小的孩子，那么就应该优先满足胃口大的。

**这里的局部最优就是大饼干喂给胃口大的，充分利用饼干尺寸喂饱一个，全局最优就是喂饱尽可能多的小孩。**

可以尝试使用贪心策略，先将饼干数组和小孩数组排序。

然后**从后向前遍历小孩数组，用大饼干优先满足胃口大的，并统计满足小孩数量。**

如图：
![avater](https://camo.githubusercontent.com/68df1344894239ff2aa2b72a8fad341d3f2a563a5ff8ad028ba13dc262eefc09/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303230313132333136313830393632342e706e67)
这个例子可以看出饼干9只有喂给胃口为7的小孩，这样才是整体最优解，并想不出反例，那么就可以撸代码了。
整体代码如下：
```java
//大饼干优先满足胃口大的小孩
class Solution {
    public int findContentChildren(int[] g, int[] s) {
        Arrays.sort(g);
        Arrays.sort(s);
        int index = s.length - 1;
        int count = 0;
        for(int i = g.length - 1;i >= 0; i--){
            if(index >=0 && s[index] >= g[i]){
                count++;
                index--;
            }
        }
        return count;
    }
}
```
<span style="color:green">其实也可以换个思路，小饼干先喂饱小胃口</span>


整体代码如下：
```java
class Solution {
    public int findContentChildren(int[] g, int[] s) {
        Arrays.sort(g);
        Arrays.sort(s);
        int start = 0;
        int count = 0;
        for(int i = 0;i < s.length && start < g.length; i++){
            if(s[i] >= g[start]){
                start++;
                count++;
            }
        }
        return count;
    }
}
```