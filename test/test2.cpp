#include<iostream>

using namespace std;

//构造函数的分类和调用
//1.分类
//按照参数分类 无参构造  (默认构造)和有参构造
//按照类型分类 普通构造  拷贝构造
class Person {
public:
	//构造函数
	Person()
	{
		cout << "Person 的无参构造函数调用" << endl;
	}
	
	Person(int a)
	{
		age = a;
		cout << "Person 的有参构造函数调用" << endl;
	}
	//拷贝构造函数
	Person(const Person &p) {
		//将传入的人身上的所有属性拷贝到我身上
		age = p.age;
		cout << "Person 的拷贝构造函数调用" << endl;
	}

	//析构函数
	~Person() {
		cout << "Person 的析构函数调用" << endl;
	}

	int age;
};

//2.调用
void test01() {
	//1.括号法
	Person p1;//默认构造函数的调用
	Person p2(10);//调用有参构造函数
	Person p3(p2);//拷贝构造函数
	
	//注意事项
	//调用默认构造函数时候，不要加()	
	//因为下面这一行代码，编译器会认为是一个函数的声明,不会认为在创建对象
	//Person p1();



	cout << "p2的年龄为：" << p2.age << endl;
	cout << "p3的年龄为：" << p3.age << endl;
	//2.显示法
	Person p4;
	Person p5 = Person(10);//有参构造
	Person p6 = Person(p5);//拷贝构造

	Person(10);//匿名对象 特点：当前行执行结束后，系统就立即回收掉匿名对象	
	
	//注意事项2
	//不要利用拷贝构造函数来初始化匿名对象 编译器会认为Person(p3) 等价于 Person p3;

	//3.隐式转化法
	Person p7 = 10; //相当于写了Person p4 = Person(10);
	Person p8 = p7;//拷贝构造
}

int main() {

	test01();

	system("pause");
	return 0;
}