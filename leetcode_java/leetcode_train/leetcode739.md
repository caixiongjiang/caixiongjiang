## 编号739：每日温度

请根据每日 气温 列表 temperatures ，请计算在每一天需要等几天才会有更高的温度。如果气温在这之后都不会升高，请在该位置用 0 来代替。

示例 1:
```
输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]
```
示例 2:
```
输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]
```
示例 3:
```
输入: temperatures = [30,60,90]
输出: [1,1,0] 
```
提示：

* 1 <= temperatures.length <= 105
* 30 <= temperatures[i] <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/daily-temperatures
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

首先用暴力解法写,代码如下：

```c++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size());
        for(int i = 0; i < temperatures.size(); i++){
            if(temperatures[i] < 100){
                for(int j = i + 1; j < temperatures.size(); j++){
                    if(temperatures[j] > temperatures[i]){
                        result[i] = j - i;
                        break;
                    }
                }
            }
        }
        return result;
    }
};
```

当然它超时了！！！

## 单调栈
什么时候用单调栈？单调栈是什么？

**通常是一维数组，要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置，此时我们就用单调栈。**

单调栈的原理是什么呢？为什么时间复杂度是O(n)就可以找到每一个元素的右边第一个比它大的元素位置呢？

单调栈的本质是空间换时间，因为在遍历的过程中需要用一个栈来记录右边第一个比当前元素的元素，优点是只需要遍历一次。

在使用单调栈的时候首先要明确如下几点：

1.单调栈里存放的元素是什么？

单调栈里只需要存放元素的下标i就可以了，如果需要使用对应的元素，直接T[i]就可以获取。

2.单调栈里元素是递增呢？ 还是递减呢？

注意一下顺序为**从栈头到栈底的顺序**，因为单纯的说从左到右或者从前到后，不说栈头朝哪个方向的话，大家一定会越看越懵。

这里我们要使用递增循序（再强调一下是指从栈头到栈底的顺序），因为只有递增的时候，加入一个元素i，才知道栈顶元素在数组中右面第一个比栈顶元素大的元素是i。

文字描述理解起来有点费劲，画了一系列的图，来讲解单调栈的工作过程。

使用单调栈主要有三个判断条件。

* 当前遍历的元素T[i]小于栈顶元素T[st.top()]的情况
* 当前遍历的元素T[i]等于栈顶元素T[st.top()]的情况
* 当前遍历的元素T[i]大于栈顶元素T[st.top()]的情况
把这三种情况分析清楚了，也就理解透彻了。

我们用temperatures = [73, 74, 75, 71, 71, 72, 76, 73]为例来逐步分析，输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。

首先先将第一个遍历元素加入单调栈
![avater](https://camo.githubusercontent.com/5f43eb9646eb60a7298bf0c554ae77b897563996aef5fd218e2bd47504a9764a/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303231393132343433343137322e6a7067)

加入T[1] = 74，因为T[1] > T[0]（当前遍历的元素T[i]大于栈顶元素T[st.top()]的情况），而我们要保持一个递增单调栈（从栈头到栈底），所以将T[0]弹出，T[1]加入，此时result数组可以记录了，result[0] = 1，即T[0]右面第一个比T[0]大的元素是T[1]。
![avater](https://camo.githubusercontent.com/94d2c3c6780cfeb463b92d9e71425fc182824bfdc98944472770be442d25747b/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303231393132343530343239392e6a7067)

加入T[2]，同理，T[1]弹出
![avater](https://camo.githubusercontent.com/cd5b2d6961b70250d9c5358e1447b4f623436f89c5d841cee78b1284d618aaf8/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303231393132343532373336312e6a7067)

加入T[3]，T[3] < T[2] （当前遍历的元素T[i]小于栈顶元素T[st.top()]的情况），加T[3]加入单调栈。

![avater](https://camo.githubusercontent.com/5cbb0b6b809012385909edbe55b41c3dc5bf98a1e7cb898726274b91874d692a/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303231393132343631303736312e6a7067)

加入T[4]，T[4] == T[3] （当前遍历的元素T[i]等于栈顶元素T[st.top()]的情况），此时依然要加入栈，不用计算距离，因为我们要求的是右面第一个大于本元素的位置，而不是大于等于！
![avater](https://camo.githubusercontent.com/0dad1466acfb03d2da9e2ad68bfb51f9031532a9e0e4246d33d24f6b01a1fcc7/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303231393132343633333434342e6a7067)

加入T[5]，T[5] > T[4] （当前遍历的元素T[i]大于栈顶元素T[st.top()]的情况），将T[4]弹出，同时计算距离，更新result
![avater](https://camo.githubusercontent.com/af5d726963cdf485a8083f338d90f09ab6ac038d233a4268f00907eafc3712a9/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303231393132343730303536372e6a7067)

T[4]弹出之后， T[5] > T[3] （当前遍历的元素T[i]大于栈顶元素T[st.top()]的情况），将T[3]继续弹出，同时计算距离，更新result
![avater](https://camo.githubusercontent.com/ac31b173adf9893ed6d750fa1ed1a47b2f94fafdb5bd8162197f781ec93cd5e4/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303231393132343732363631332e6a7067)

直到发现T[5]小于T[st.top()]，终止弹出，将T[5]加入单调栈
![avater](https://camo.githubusercontent.com/abcc123e7b6d99d22cddb0e5498f6b1d4806dff6cf6a672720852d2d620da878/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303231393132343830373731352e6a7067)

加入T[6]，同理，需要将栈里的T[5]，T[2]弹出
![avater](https://camo.githubusercontent.com/42f8f8f5240c8014ee234b3992c7d3ed438617ce1264c7f7c93f0f099550a9af/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032313032313931323438333337342e6a7067)

同理，继续弹出
![avater](https://camo.githubusercontent.com/06a62393bd5b1fb6644faf41ceab74e35ef51394233ed9370ba0a73b8bba708f/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f323032313032313931323439303039382e6a7067)

此时栈里只剩下了T[6]
![avater](https://camo.githubusercontent.com/76566b036646563068ac84d15d0975552f61e6db3ab4bddda22e522fa2ecfaa7/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303231393132343933303135362e6a7067)

加入T[7]， T[7] < T[6] 直接入栈，这就是最后的情况，result数组也更新完了。
![avater](https://camo.githubusercontent.com/cc1a965cbb4eca7bf4ecab130c86d025def816b79420d6669e2a1b189b8790c2/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303231303231393132343935373231362e6a7067)

此时有同学可能就疑惑了，那result[6] , result[7]怎么没更新啊，元素也一直在栈里。

其实定义result数组的时候，就应该直接初始化为0，如果result没有更新，说明这个元素右面没有更大的了，也就是为0。

以上在图解的时候，已经把，这三种情况都做了详细的分析。

* 情况一：当前遍历的元素T[i]小于栈顶元素T[st.top()]的情况
* 情况二：当前遍历的元素T[i]等于栈顶元素T[st.top()]的情况
* 情况三：当前遍历的元素T[i]大于栈顶元素T[st.top()]的情况

整体代码如下：
```c++
//单调栈
class Solution{
public:
    vector<int> dailyTemperatures(vector<int>& temperatures){
        //递减栈
        stack<int> st;//存放数组的下标
        vector<int> result(temperatures.size(), 0);
        st.push(0);
        for(int i = 1; i < temperatures.size(); i++){
            if(temperatures[i] < temperatures[st.top()]){//情况一
                st.push(i);
            }else if(temperatures[i] == temperatures[st.top()]){//情况二
                st.push(i);
            }else{
                while(!st.empty() && temperatures[i] > temperatures[st.top()]){//情况三
                    result[st.top()] = i - st.top();
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }
};
```

精简代码如下：
```c++
// 版本二
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        stack<int> st; // 递减栈
        vector<int> result(T.size(), 0);
        st.push(0);
        for (int i = 1; i < T.size(); i++) {
            while (!st.empty() && T[i] > T[st.top()]) { // 注意栈不能为空
                result[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        return result;
    }
};
```