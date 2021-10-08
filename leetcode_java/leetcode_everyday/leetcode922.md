## 编号922：按奇偶排序树组Ⅱ

给定一个非负整数数组 A， A 中一半整数是奇数，一半整数是偶数。

对数组进行排序，以便当 A[i] 为奇数时，i 也是奇数；当 A[i] 为偶数时， i 也是偶数。

你可以返回任何满足上述条件的数组作为答案。

 

示例：
```
输入：[4,2,5,7]
输出：[4,5,2,7]
解释：[4,7,2,5]，[2,5,4,7]，[2,7,4,5] 也会被接受。
``` 

提示：

* 2 <= A.length <= 20000
* A.length % 2 == 0
* 0 <= A[i] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-array-by-parity-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

可以用比较朴实的方法，就是遍历数组将其分成奇数组和偶数组，再将其按照顺序合并成一个数组！

时间复杂度就是O(n),c++代码如下：
```c++
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        vector<int> even(nums.size() / 2);//初始化就确定数组的大小
        vector<int> odd(nums.size() / 2);
        vector<int> result(nums.size());
        int evenIndex = 0;
        int oddIndex = 0;
        int resultIndex = 0;
        //将nums数组放进偶数数组 和 奇数数组
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] % 2 == 0) even[evenIndex++] = nums[i];
            else odd[oddIndex++] = nums[i];
        }
        //把偶数数组，奇数数组分别放进result数组中
        for(int i = 0; i < evenIndex; i++){
            result[resultIndex++] = even[i];
            result[resultIndex++] = odd[i];
        }
        return result;
    }
};
```