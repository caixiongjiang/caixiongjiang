/*
Given two sets of integers, the similarity of the sets is defined to be Nc/Nt × 100%, 
where Nc is the number of distinct common numbers shared by the two sets, and Nt is 
the total number of distinct numbers in the two sets. Your job is to calculate the similarity
 of any given pair of sets.

Input Specification:
Each input file contains one test case. Each case first gives a positive integer N (≤50) 
which is the total number of sets. Then N lines follow, each gives a set with a positive M (≤10^4
 ) and followed by M integers in the range [0,10^9]. After the input of sets, a positive integer 
 K (≤2000) is given, followed by K lines of queries. Each query gives a pair of set numbers (the 
 sets are numbered from 1 to N). All the numbers in a line are separated by a space.

Output Specification:
For each query, print in one line the similarity of the sets, in the percentage form accurate up
 to 1 decimal place.

Sample Input:
3
3 99 87 101
4 87 101 5 87
7 99 101 18 5 135 18 99
2
1 2
1 3

Sample Output:
50.0%
33.3%

*/

#include <iostream>
#include <set>
using namespace std;

const int MAX = 51;
set<int> st[MAX];

void compare(int x, int y){
    int sameNum = 0, totalNum = st[y].size();
    //遍历其中一个集合
    for(set<int>::iterator it = st[x].begin(); it != st[x].end(); it++){
        if(st[y].find(*it) != st[y].end()) ++sameNum;
        else ++totalNum;
    }
    printf("%.1f%%\n", sameNum * 100.0 / totalNum);
}

int main(){
    //输入
    int N, M, V, K, st1, st2;
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> M;
        for(int j = 0; j < M; j++){
            cin >> V;
            st[i + 1].insert(V);
        }
    }
    cin >> K;
    for(int i = 0; i < K; i++){
        cin >> st1 >> st2;
        compare(st1, st2);
    }
    return 0;
}
