/*
            1060 Are They Equal (25 分)
If a machine can save only 3 significant digits, the float numbers 12300 and 12358.9 are considered 
equal since they are both saved as 0.123×10^5 with simple chopping. Now given the number of 
significant digits on a machine and two float numbers, you are supposed to tell if they are treated 
equal in that machine.

Input Specification:
Each input file contains one test case which gives three numbers N, A and B, where N (<100) is the
 number of significant digits, and A and B are the two float numbers to be compared. Each float 
 number is non-negative, no greater than 10^100, and that its total digit number is less than 100.

Output Specification:
For each test case, print in a line YES if the two numbers are treated equal, and then the number 
in the standard form 0.d[1]...d[N]*10^k (d[1]>0 unless the number is 0); or NO if they are not 
treated equal, and then the two numbers in their standard form. All the terms must be separated 
by a space, with no extra space at the end of a line.

Note: Simple chopping is assumed without rounding.

Sample Input 1:
3 12300 12358.9

Sample Output 1:
YES 0.123*10^5

Sample Input 2:
3 120 128

Sample Output 2:
NO 0.120*10^3 0.128*10^3

*/

//此题部分正确，得21分

#include <iostream>
#include <string>
using namespace std;

int N;//有效位数

string deal(string s, int& e){
    int index = 0;//下标位置
    while(s.length() > 0 && s[0] == '0'){
        s.erase(s.begin());//去掉s的前导0
        --e;//每去掉一个0，指数e减1
    }
    if(s[0] == '.'){//若去掉前导零后是小数点，则说明s是小于1的小数
        s.erase(s.begin());
        while(s.length() > 0 && s[0] == '0'){
            s.erase(s.begin());//去掉小数点后非零位前的所有零
            --e;//每去掉一个0，指数e减1
        }
    }else{//若去掉前导零后不是小数点，则找到后面的小数点进行删除
        while(index < s.length() && s[index] != '.'){
            ++index, ++e;//只要不遇到小数点，就让指数e++
        }
        if(index < s.length()){
            s.erase(s.begin() + index);//把小数点删除
        }
    }
    if(s.length() == 0) e = 0;
    int num = 0;//代表res的位数
    index = 0;
    string res;
    while(num < N){//只要精度没有到N
        if(index < s.length()) res += s[index++];//只要还有数字，就加到res末尾
        else res += '0';//否则res末尾添加0
        ++num;
    }
    return res;
}

int main(){
    //输入
    string s1, s2, s3, s4;
    cin >> N >> s1 >> s2;
    int e1 = 0, e2 = 0;//e1和e2为s1和s2的指数
    //处理逻辑
    s3 = deal(s1, e1);
    s4 = deal(s2, e2);
    //输出
    if(s3 == s4 && e1 == e2){
        cout << "YES 0." << s3 << "*10^" << e1 << endl;
    }else{
        cout << "NO 0." << s3 << "*10^" << e1 << " 0." << s4 << "*10^" << e2 << endl;
    }
    return 0;
}