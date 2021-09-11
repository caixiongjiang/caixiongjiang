#include<iostream>

using namespace std;

//引用做函数的返回值
//1.不要返回局部变量的引用
int& test01() {
	int a = 10;//局部变量存放在4区中的栈区	
	return a;
}

//2.函数的调用可以作为左值
int& test02() {
	static int a = 10;//静态变量存放在全局区，数据在程序结束后由系统释放
	return a;
}

int main() {

	int& ref = test01();
	cout << "ref = " << ref << endl;//第一次结果正确为10是因为编译器做了保留
	cout << "ref = " << ref << endl;//第二次结果错误，因为a的内存已被释放。

	int& res = test02();
	cout << "res = " << res << endl;//10
	test02() = 1000;//如果函数的返回值是引用，函数的返回值可以作为左值
	cout << "res = " << res << endl;//1000

	system("pause");
	return 0;
}