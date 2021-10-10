## 编号5894：至少在两个数组中出现的值(AC)

给你三个整数数组 nums1、nums2 和 nums3 ，请你构造并返回一个 不同 数组，且由 至少 在 两个 数组中出现的所有值组成。数组中的元素可以按 任意 顺序排列。
 

示例 1：
```
输入：nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3]
输出：[3,2]
解释：至少在两个数组中出现的所有值为：
- 3 ，在全部三个数组中都出现过。
- 2 ，在数组 nums1 和 nums2 中出现过。
```
示例 2：
```
输入：nums1 = [3,1], nums2 = [2,3], nums3 = [1,2]
输出：[2,3,1]
解释：至少在两个数组中出现的所有值为：
- 2 ，在数组 nums2 和 nums3 中出现过。
- 3 ，在数组 nums1 和 nums2 中出现过。
- 1 ，在数组 nums1 和 nums3 中出现过。
```
示例 3：
```
输入：nums1 = [1,2,2], nums2 = [4,3,3], nums3 = [5]
输出：[]
解释：不存在至少在两个数组中出现的值。 
```
提示：

* 1 <= nums1.length, nums2.length, nums3.length <= 100
* 1 <= nums1[i], nums2[j], nums3[k] <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-out-of-three
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 我的题解

```c++
class Solution {
public:
    vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
        int size = 100;
        int j = 0;
        vector<int> ret;
        int hash1[101]{};
        int hash2[101]{};
        int hash3[101]{};
        for(int i = nums1.size() - 1; i >= 0; i--){
            hash1[nums1[i]]++;
        }
        
        for(int i = nums2.size() - 1; i >= 0; i--){
            hash2[nums2[i]]++;
        }
        
        for(int i = nums3.size() - 1; i >= 0; i--){
            hash3[nums3[i]]++;
        }
        
        for(int i = 0; i <= size; i++){
            if((hash1[i] > 0 && hash2[i] > 0) ||(hash1[i] > 0 && hash3[i] > 0) || (hash2[i] > 0 && hash3[i] > 0)){
                ret.push_back(i);
            }
        }
        return ret;
    }
};
```
## 思路

整体思路就是通过哈希数组或者HashMap进行数组的统计，如果满足两个数组同一位置的个数大于等于2就将它压入目标数组。

这里提供一个HashMap的版本：
```c++
class Solution {
    public List<Integer> twoOutOfThree(int[] nums1, int[] nums2, int[] nums3) {
        HashSet <Integer> set1 = new HashSet(), set2 = new HashSet(), set3 = new HashSet();
        for(int i : nums1) set1.add(i);
        for(int i : nums2) set2.add(i);
        for(int i : nums3) set3.add(i);
        HashMap <Integer, Integer> map = new HashMap();
        for(int i : set1) map.put(i, map.getOrDefault(i, 0) + 1);
        for(int i : set2) map.put(i, map.getOrDefault(i, 0) + 1);
        for(int i : set3) map.put(i, map.getOrDefault(i, 0) + 1);
        ArrayList <Integer> res = new ArrayList();
        for(int i : map.keySet()) if(map.get(i) >= 2) res.add(i);
        return res;
    }
}
```