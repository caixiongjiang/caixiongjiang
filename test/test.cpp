#include<iostream>

using namespace std;

//关系运算符重载
class Person {
public:
	Person(string name, int age) {
		m_Name = name;
		m_Age = age;
	}
	//重载关系运算符 == 号
	bool operator==(Person& p) {
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age) {
			return true;
		}
		else {
			return false;
		}
	}
	//重载关系运算符 !=号
	bool operator!=(Person& p) {
		if (this->m_Name != p.m_Name || this->m_Age != p.m_Age) {
			return true;
		}
		else {
			return false;
		}
	}
	
	string m_Name;
	int m_Age;

};

void test01(){
	Person p1("Tom", 18);
	Person p2("Jerry", 18);
	
	if (p1 == p2) {
		cout << "p1和p2是相等的" << endl;
	}
	else {
		cout << "p1和p2是不相等的" << endl;
	}

	if (p1 != p2) {
		cout << "p1和p2是不相等的" << endl;
	}
	else {
		cout << "p1和p2是相等的" << endl;
	}
}

int main() {
	test01();
	system("pause");
	return 0;
}