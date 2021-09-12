#include<iostream>

using namespace std;

//函数重载
//可以让函数名字相同，提高复用性

//函数重载的满足条件：
//在同一个作用域下
//函数名称相同
//函数参数类型不同，或者个数不同，或者顺序不同
void func() {
	cout << "func的调用? " << endl;
}

void func(int a) {
	cout << "func的调用! " << endl;
}

void func(double a) {
	cout << "func的调用* " << endl;
}

void func(int a, double b) {
	cout << "func的调用@cxj " << endl;
}

void func(double a, int b) {
	cout << "func的调用@nau_cxj" << endl;
}

//注意事项
//函数的返回值不可以作为函数重载的条件
//int func(double a, int b) {
//	cout << "func的调用@nau_cxj" << endl;
//}

int main() {
	func();
	func(10);
	func(3.14);
	func(2, 6.27);
	func(3.14, 10);

	system("pause");
	return 0;
}