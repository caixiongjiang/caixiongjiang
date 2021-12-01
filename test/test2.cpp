#include <iostream>
using namespace std;
//函数模版注意事项
template<typename T>    //typename可以替换成class
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}
//这里为了区分函数模版和类模版，函数模版用typename，类模版用class。
//1.自动类型推倒，必须要推倒出一致的数据类型T才可以使用
void test01()
{
    int a = 10;
    int b = 20;
    char c = 'c';
    mySwap(a, b);//正确！
    //mySwap(a, c);  //推导不出一致的T数据类型，错误！
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

//2.模版必须要确定出T的数据类型，才可以使用
template<typename T>
void func()
{
    cout << "func 调用" << endl;
}

void test02()
{
    func<int>();
}
int main()
{
    test01();
    test02();
    return 0;
}