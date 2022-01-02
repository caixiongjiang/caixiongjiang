## 编号2115：从给定原材料中找到所有可以做出的菜（🍵）

你有 n 道不同菜的信息。给你一个字符串数组 recipes 和一个二维字符串数组 ingredients 。第 i 道菜的名字为 recipes[i] ，如果你有它 所有 的原材料 ingredients[i] ，那么你可以 做出 这道菜。一道菜的原材料可能是 另一道 菜，也就是说 ingredients[i] 可能包含 recipes 中另一个字符串。

同时给你一个字符串数组 supplies ，它包含你初始时拥有的所有原材料，每一种原材料你都有无限多。

请你返回你可以做出的所有菜。你可以以 任意顺序 返回它们。

注意两道菜在它们的原材料中可能互相包含。

 

示例 1：
```
输入：recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
输出：["bread"]
解释：
我们可以做出 "bread" ，因为我们有原材料 "yeast" 和 "flour" 。
```
示例 2：
```
输入：recipes = ["bread","sandwich"], ingredients = [["yeast","flour"],["bread","meat"]], supplies = ["yeast","flour","meat"]
输出：["bread","sandwich"]
解释：
我们可以做出 "bread" ，因为我们有原材料 "yeast" 和 "flour" 。
我们可以做出 "sandwich" ，因为我们有原材料 "meat" 且可以做出原材料 "bread" 。
```
示例 3：
```
输入：recipes = ["bread","sandwich","burger"], ingredients = [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]], supplies = ["yeast","flour","meat"]
输出：["bread","sandwich","burger"]
解释：
我们可以做出 "bread" ，因为我们有原材料 "yeast" 和 "flour" 。
我们可以做出 "sandwich" ，因为我们有原材料 "meat" 且可以做出原材料 "bread" 。
我们可以做出 "burger" ，因为我们有原材料 "meat" 且可以做出原材料 "bread" 和 "sandwich" 。
```
示例 4：
```
输入：recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast"]
输出：[]
解释：
我们没法做出任何菜，因为我们只有原材料 "yeast" 。 
```
提示：

* n == recipes.length == ingredients.length
* 1 <= n <= 100
* 1 <= ingredients[i].length, supplies.length <= 100
* 1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <= 10
* recipes[i], ingredients[i][j] 和 supplies[k] 只包含小写英文字母。
* 所有 recipes 和 supplies 中的值互不相同。
* ingredients[i] 中的字符串互不相同。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-all-possible-recipes-from-given-supplies
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

---
## 思路

### 拓扑排序

维护入度值和邻接表，具体看注释！

代码如下：
```c++
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_set<string> sups;//原材料无序集合
        for(auto &s : supplies) sups.insert(s);
        int n = recipes.size();
        vector<int> degreeIn(n);//用于记录每道菜缺少的原材料
        //邻接map <缺少的原材料，缺少该原材料的菜的下标组成的数组>
        unordered_map<string, vector<int>> edges;
        for(int i = 0; i < n; i++){
            for(auto &ingredient : ingredients[i]){
                /* 某个原材料找不到, 说明该recipe依赖此原材料, degreeIn++ */
                //set.find()函数如果找不到就返回set.end()的迭代器
                if(sups.find(ingredient) == sups.end()){
                    degreeIn[i]++;//入度加1
                    edges[ingredient].push_back(i);//加入edges中
                }
            }
        }
        //用队列存储能做出的菜
        queue<int> que;
        for(int i = 0; i < n; i++){
            if(degreeIn[i] == 0){
                que.push(i);
            }
        }
        vector<string> ret;
        while(!que.empty()){
            int x = que.front();
            que.pop();
            ret.push_back(recipes[x]);//将做出来的菜加入结果数组
            //遍历缺少的该原材料的菜的下标，看看能不能做出新的菜
            for(auto v : edges[recipes[x]]){
                degreeIn[v]--;//这道菜做出来了，重新作为原材料，对该菜的依赖都消除
                //若菜v不缺少原材料，则做出这道菜
                if(degreeIn[v] == 0) que.push(v);
            }
        }
        return ret;
    }
};
```

### 暴力法（我的做法）

只是少写一些细节，导致一直通不过！

暴力法，如果能合成新的recipe就不断组合，不能合成新的recipe就停止循环!（三个for循环）

代码如下：
```c++
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        //<原材料,1表示存在;0表示不存在>
        unordered_map<string, int> mp1;
        for (auto s : supplies) {
            ++mp1[s];
        }
        int n = recipes.size();
        while (1) {
            int flag2 = 0;//表示是否有新的菜可以作为原材料
            for (int i = 0; i < n; ++i) {
                if (mp1[recipes[i]] != 0) {
                    continue;
                }
                int flag = 1;//代表该菜能否被出来
                for (auto &ing : ingredients[i]) {
                    if (mp1[ing] == 0) { /* 某个原材料找不到 */
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    ++mp1[recipes[i]]; /* 该菜可以做出来, 加入到新的原材料 */
                    flag2 = 1;
                }
            }
            if (flag2 == 0) { /* 没有新的菜能做出来成为原材料 */
                break;
            }
        }
        vector<string> ans;
        for (auto &r : recipes) {
            if (mp1[r] > 0) {
                ans.push_back(r);
            }
        }
        return ans;
    }
};
```
