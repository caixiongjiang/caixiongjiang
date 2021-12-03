#include <iostream>
using namespace std;

//普通函数与函数模板的调用规则
//1.如果函数模版和普通函数都可以调用，优先调用普通函数
//2.可以通过空模板的参数列表 强制调用函数模版
//3.函数模板可以发生函数重载
//4.如果函数模版可以产生更好的匹配，优先调用函数模版

void myPrint(int a, int b)
{
    cout << "调用的普通函数" << endl;
}

template <typename T>
void myPrint(T a, T b)
{
    cout << "调用函数模版" << endl;
}

template <typename T>
void myPrint(T a, T b, T c)
{
    cout << "重载的函数模版" << endl;
}

void test01()
{
    int a = 10;
    int b = 20;

    myPrint(a, b);               //调用的普通函数
    //通过空模版的参数列表，强制调用函数模版
    myPrint<>(a, b);            //调用函数模版
    myPrint(a, b, 100);  //重载的函数模版

    //如果函数模版产生更好的匹配，优先调用函数模版
    char c1 = 'a';
    char c2 = 'b';
    myPrint(c1, c2);  //调用函数模版
}

int main()
{
    test01();
    return 0;
}
