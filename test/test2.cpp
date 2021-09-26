#include<iostream>

using namespace std;

//常函数
class Person{
public:
	//this指针的本质是指针常量，指针的指向是不可以修改的
	//此处的const表示this指针指向的值也不可以修改
	void showPerson() const {
		//this->m_A = 100; 指针指向的值不可以修改
		//this = NULL; this指针不可以修改指针的指向	
		m_B = 100;
	}
	void func() {
	}
	
	//特殊变量，即在常函数中也可以修改这个值，加上mutable关键字
	mutable int m_B; 
	int m_A;
};

void test01() {
	Person p;
	p.showPerson();
}

//常对象
void test02() {
	const Person p;//在对象前加上const称为常对象
	//p.m_A = 100;
	p.m_B = 1000;//m_B是特殊值，在常对象下也可以修改

	//常对象只能调用常函数
	p.showPerson();
	//p.func(); 
	//常对象不可以调用普通成员函数，因为普通成员函数可以修改属性
	cout << "m_B = " << p.m_B << endl;
}

int main() {
	test01();
	test02();
	system("pause");
	return 0;
}