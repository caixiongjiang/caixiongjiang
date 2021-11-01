## 编号2055：蜡烛之间的盘子(AC)

1.求出并记录每个‘|’前有多少个有效的‘*’；

2.每次query时，求出两个‘|’的位置（二分）；

3.两个‘|’的差就是结果

要注意的细节
* 最前和最后的*要省略
* it2的位置要分类讨论

代码如下：
```c++
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        map<int, int> m;//记录每个‘|’之前有多少个有效的‘*’
        map<int, int>::iterator it1, it2;//这个方法可以提取出map容器中的数据
        int cnt = 0;
        int n = s.size();
        int start = 0, end = n - 1;
        vector<int> ans;
        
        //找到正确的计数区间【start, end】
        while(start < n && s[start] == '*'){
            start++;
        }
        while(end >= 0 && s[end] == '*'){
            end--;
        }

        for(int i = start; i <= end; i++){
            if(s[i] == '|'){
                m[i] = cnt;
            }else{
                cnt++;
            }
        }
        //it1->first 代表存入的数据 it2->second 代表存入数据的个数
        for(auto& q : queries){
            //返回m中第一个大于或等于两个边界的迭代器指针
            it1 = m.lower_bound(q[0]);      
            it2 = m.lower_bound(q[1]);
            //vector::emplace_back：作用类似于push_back
            //区别：如果是尾插临时对象的话，push_back()需要先构造临时对象，再将这个对象拷贝到容器的末尾，而emplace_back()则直接在容器的末尾构造对象，这样就省去了拷贝的过程。
            if(it2 == m.end()){
                ans.emplace_back(cnt - it1->second);
            }else if(it2->second == 0){
                ans.emplace_back(0);
            }else if(s[q[1]] == '*'){
                if(prev(it2)->second >= it1->second){
                    ans.emplace_back(prev(it2)->second - it1->second);
                }else{
                    ans.emplace_back(0);
                }
            }else{
                ans.emplace_back(it2->second - it1->second);
            }
        }
        return ans;
    }
};
```