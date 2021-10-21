#include<iostream>

using namespace std;

//左移运算符重载

class Person {
	friend ostream& operator<<(ostream& cout, Person& p);
public:
	Person(int a, int b) {
		m_A = a;
		m_B = b;
	}
private:
	//利用成员函数来重载左移运算符 p.operator(cout) 简化版本 p << cout
	//不会利用成员函数重载<< 运算符，因为无法实现cout在左侧
	//void operator << (cout) {
	//
	//}

	int m_A;
	int m_B;
};

//只能利用全局函数来实现重载左移运算符
ostream & operator<<(ostream &cout ,Person &p) {		//本质  operator<<(cout, p)    简化 cout << p
	cout << "m_A =" << p.m_A << "  m_B =" << p.m_B;
	return cout;
}

void test01() {
	Person p(10, 10);
	//p.m_A = 10;
	//p.m_B = 10;

	cout << p <<"  Hello World!" <<endl;
}

int main() {
	test01();

	system("pause");
	return 0;
}