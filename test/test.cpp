#include<iostream>
#include<string>

using namespace std;

class Building;
class GoodGay
{
public:
	GoodGay();

	void visit();//让visit函数可以访问Building中私有的成员
	void visit2();//让visit2函数不可以访问Building中私有的成员
private:
	Building *  building;
};

class Building {
	//告诉编译器 GoodGay下的成员函数作为本类的好朋友，可以访问私有的成员 
	friend void GoodGay::visit();
public:
	Building();
public:
	string m_SittingRoom;//客厅
private:
	string m_BedRoom;//卧室

};

//类外实现他们的函数
Building::Building() {
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

GoodGay::GoodGay() {
	building = new Building;
}

void GoodGay::visit()
{
	cout << "visit函数正在访问：" << building->m_SittingRoom << endl;

	cout << "vist函数正在访问：" << building->m_BedRoom << endl;
}
void GoodGay::visit2()
{
	cout << "vist2函数正在访问：" << building->m_SittingRoom<< endl;

	//cout << "visit2函数正在访问：" << building->m_BedRoom << endl;
}

void test01() {
	GoodGay gg;
	gg.visit();
	gg.visit2();
}

int main() {
	test01();
	system("pause");
	return 0;
}