#include <iostream>

using namespace std;

//继承中同名成员处理
class Base
{
public:
	Base() 
	{
		m_A = 100;
	}
	void func()
	{
		cout << "Base-func()函数调用" << endl;
	}
	void func(int a)
	{
		cout << "Base-func(int a)函数调用" << endl;
	}
	int m_A;
};

class Son :public Base
{
public:
	Son()
	{
		m_A = 200;
	}
	void func()
	{
		cout << "Son-func()函数调用" << endl;
	}
	int m_A;
};

void test01()
{
	Son s;
	cout << "Son下的m_A = " << s.m_A << endl;	//输出200
	//如果通过子类对象 访问父类中的同名成员， 需要加一个作用域
	cout << "Base下的m_A = " << s.Base::m_A << endl;	//输出100
}

//同名成员函数的处理方式
void test02() 
{
	Son s;
	s.func();//直接调用 调用的是子类中的同名成员
	//如何调用到父类中的同名成员函数？
	s.Base::func();
	//如果子类中出现和父类同名的成员函数，子类的同名成员会隐藏掉父类的所有同名成员函数
	//s.func(100);   出现报错
	s.Base::func(100);
}

int main() {
	test01();
	test02();
	system("pause");
	return 0;
}