#include<iostream>
#include<string>

using namespace std;

class Person
{
public:
	//写姓名
	void setName(string name) {
		m_Name = name;
	}
	//获取姓名
	string getName() {
		return m_Name;
	}
	//获取年龄 只读
	int getAge() {
		m_Age = 23;//初始化为0岁
		return m_Age;
	}
	//设置情人 只写
	void setLover(string lover) {
		m_Lover = lover;
	}

private:
	//姓名 可读可写
	string m_Name;
	//年龄 只读
	int m_Age;
	//情人 只写
	string m_Lover;
};

int main() {

	Person p;
	p.setName("张三");
	cout << "姓名为：" << p.getName() << endl;
	cout << "年龄为：" << p.getAge() << endl;
	//设置情人为LISA，但不能获取到这个数据
	p.setLover("LISA");

	system("pause");
	return 0;
}