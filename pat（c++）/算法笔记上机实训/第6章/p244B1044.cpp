/*
                        1044 火星数字 (20 分)
火星人是以 13 进制计数的：

地球人的 0 被火星人称为 tret。
地球人数字 1 到 12 的火星文分别为：jan, feb, mar, apr, may, jun, jly, aug, sep, oct, nov, dec。
火星人将进位以后的 12 个高位数字分别称为：tam, hel, maa, huh, tou, kes, hei, elo, syy, lok, mer, jou。
例如地球人的数字 29 翻译成火星文就是 hel mar；而火星文 elo nov 对应地球数字 115。为了方便交流，请你编写
程序实现地球和火星数字之间的互译。

输入格式：
输入第一行给出一个正整数 N（<100），随后 N 行，每行给出一个 [0, 169) 区间内的数字 —— 或者是地球文，
或者是火星文。

输出格式：
对应输入的每一行，在一行中输出翻译后的另一种语言的数字。

输入样例：
4
29
5
elo nov
tam

输出样例：
hel mar
may
115
13

*/

//此题使用打表实现

#include <cstdio>
#include <iostream>
#include <string>
#include <map>
using namespace std;

//[0,12]的火星文
string unitDigit[13] = {"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", 
                        "sep", "oct", "nov", "dec"};
//13的[0,12]的火星文
string tenDigit[13] = {"tret", "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", 
                       "syy", "lok", "mer", "jou"};
string numToStr[170];//数字->火星文
map<string, int> strToNum;//火星文->数字

void init(){
    //建立数字和火星文的相互映射
    for(int i = 0; i < 13; ++i){
        numToStr[i] = unitDigit[i];//个位为[0, 12]，十位为0
        strToNum[unitDigit[i]] = i;
        numToStr[i * 13] = tenDigit[i];//十位为[0, 12]，个位为0
        strToNum[tenDigit[i]] = i * 13;
    }
    //枚举
    for(int i = 1; i < 13; ++i){//十位
        for(int j = 1; j < 13; ++j){//个位
            string str = tenDigit[i] + " " + unitDigit[j];//火星文
            numToStr[i * 13 + j] = str;//数字->火星文
            strToNum[str] = i * 13 + j;//火星文->数字
        }
    }
}

int main(){
    init();//打表
    int N;
    scanf("%d%*c", &N);
    while(N--){
        string temp;
        getline(cin, temp);
        if(temp[0] >= '0' && temp[0] <= '9'){//输入为数字
            int num = 0;
            for(int i = 0; i < temp.size(); ++i){
                num = num * 10 + (temp[i] - '0');//字符转数字公式的精髓
            }
            cout << numToStr[num] << endl;//查表
        }else{//输入为火星文
            cout << strToNum[temp] << endl;//查表
        }
    }
    return 0;
}