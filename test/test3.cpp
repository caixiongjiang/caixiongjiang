#include<iostream>

using namespace std;

//深拷贝与浅拷贝

class Person {
public:
	Person() {
		cout << "Person 的默认构造函数调用" << endl;
	}
	
	Person(int age, int height) {
		m_Age = age;
		m_Height = new int(height);
		cout << "Person 的有参构造函数调用" << endl;
	}

	//自己实现一个拷贝构造函数来解决浅拷贝带来的问题
	Person(const Person& p) {
		cout << "拷贝构造函数的调用" << endl;
		m_Age = p.m_Age;
		//m_Height = p.m_Height;  编译器默认实现就是这行代码
		m_Height = new int(*p.m_Height);//使用深拷贝：在堆区重新寻找一块地址存放信息
	}

	~Person() {
		//析构代码：将堆区开辟的数据做一个释放操作
		if (m_Height != NULL) {
			delete m_Height;
			m_Height = NULL;
		}	
		cout << "Person 的析构构造函数调用" << endl;
	}
	int m_Age;//年龄
	int* m_Height;//身高
};

void test01() {
	Person p1(23, 180);
	cout << "p1的年龄为：" << p1.m_Age << "       身高为："<< *p1.m_Height << endl;
	Person p2(p1);
	cout << "p2的年龄为：" << p2.m_Age << "       身高为："<< *p2.m_Height << endl;
}

int main() {

	test01();
	system("pause");
	return 0;
}