#include<iostream>

using namespace std;

//拷贝构造的调用时机

class Person {
public:
	Person() {
		cout << "Person 的默认构造函数调用" << endl;
	}
	Person(int age) {
		m_Age = age;
		cout << "Person 的有参构造函数调用" << endl;
	}

	Person(const Person &p) {
		m_Age = p.m_Age;
		cout << "Person 的拷贝构造函数调用" << endl;
	}

	~Person() {
		cout << "Person 的析构函数调用" << endl;
	}

	int m_Age;
};


//1.使用一个已经创建完毕的对象初始化一个新对象
void test01() {
	Person p1(20);
	Person p2(p1);
	cout << "p2的年龄为：" << p2.m_Age << endl;
}
//2.值传递的方式给函数参数传值
void doWork(Person p) {
	
}

void test02() {
	Person p3;
	doWork(p3);

}
//3.用值的方式返回局部对象
Person doWork2() {
	Person p4;
	cout << (int*)&p4 << endl;
	return p4;
}

void test03() {
	Person p = doWork2();
	cout << (int*)&p << endl;
}
int main() {

	test01();
	test02();
	test03();
	system("pause");
	return 0;
}