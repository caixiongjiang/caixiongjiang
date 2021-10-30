#include<iostream>

using namespace std;

//纯虚函数和抽象类
class Base
{
public :
	//纯虚函数
	//只要有一个纯虚函数，这个类称为抽象类
	//抽象类特点：
	//1.无法实例化对象
	//2.抽象类的子类必须要重写父类中的纯虚函数，否则也属于抽象类
	virtual void func() = 0;//虚函数的基础上可以直接写等于0变成纯虚函数
};

class Son : public Base
{
public:
	virtual void func() 
	{
		cout << "func函数调用" << endl;
	};
};

void test01()
{
	//抽象类是不能实例化对象的
	//Base b;
	//new Base
	Son s; //子类必须要重写父类中的纯虚函数，否则无法实例化对象
	Base* base = new Son;
	base->func();
}

int main() 
{
	test01();
	system("pause");
	return 0;
}