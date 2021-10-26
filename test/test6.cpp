#include<iostream>

using namespace std;

//多继承语法
class Base1
{
public:
	Base1()
	{
		m_A = 100;
	}
	int m_A;
};

class Base2
{
public:
	Base2()
	{
		m_A = 200;
	}
	int m_A;
};

//子类 需要继承Base1和Base2
//语法 ：class 子类： 继承方式   父类1，继承方式   父类2... 
class Son :public Base1, public Base2
{
public:
	Son() 
	{
		m_C = 300;
		m_D = 400;
	}
	int m_C;
	int m_D;
};

void test01()
{
	Son s;
	cout << "size of Son = " << sizeof(s) << endl;// 结果为16
	//当父类中出现同名成员，需要加作用域区分
	cout << "Base1下的m_A = " << s.Base1::m_A << endl;
	cout << "Base2下的m_A = " << s.Base2::m_A << endl;
}

int main() {
	test01();
	system("pause");
	return 0;
}