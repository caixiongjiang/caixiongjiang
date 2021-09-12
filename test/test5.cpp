#include<iostream>

using namespace std;

//打印数据的函数
void showValue(const int& val) {
	//val = 1000;
	cout << "val = " << val << endl;
}


int main() {

	//常量引用
	//使用场景：用来修饰形参，防止误操作
	int a = 10;
	//int &ref = 10; 引用本身需要一个合法的内存空间，因此这行错误
	//加上const之后，编译器将代码修改为 int  temp = 10；const int & ref = temp;
 	const int& ref = 10;
	//ref = 20;//加入const之后变为只读，不可以修改

	int b = 100;
	showValue(b);

	system("pause");
	return 0;
}