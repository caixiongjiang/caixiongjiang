#include<iostream>

using namespace std;

//重载递减运算符

//自定义整型
class Myinteger {
	friend ostream& operator<<(ostream& cout, Myinteger myint);
public:
	Myinteger() {
		m_Num = 3;
	}
	//重载前置--运算符  返回引用为了一直对一个数据进行递减操作
	Myinteger& operator--() {
		//先进行--的运算，再将自身做返回
		m_Num--;
		return *this;
	}
	//重载前置--运算符  返回值
	Myinteger operator--(int) {
		//先记录当时的结果
		Myinteger temp = *this;
		//后递增
		m_Num--;
		//最后将记录结果返回
		return temp;
	}
private:
	int m_Num;
};

ostream& operator<<(ostream& cout, Myinteger myint) {
	cout << myint.m_Num;
	return cout;
}

void test01() {
	Myinteger myint;
	cout << --(--myint) << endl;
	cout << myint << endl;
}

void test02() {
	Myinteger myint;
	cout << myint-- << endl;
	cout << myint << endl;
}

int main() {
	test01();
	test02();
	system("pause");
	return 0;
}