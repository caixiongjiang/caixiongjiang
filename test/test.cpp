#include<iostream>
#include<string>

using namespace std;

//类做友元
class Building {
	//GoodGay是本类的好朋友，可以访问本类中私有的成员
	friend class GoodGay;
public:
	Building();

public:
	string m_sittingRoom; // 客厅

private:
	string m_BedRoom; //卧室
};

//类外写成员函数
Building::Building(){
	m_sittingRoom = "客厅";
	m_BedRoom = "卧室";
}

class GoodGay {
public:

	GoodGay();

	void visit(); //参观函数访问Building中的属性

	Building* building;

};

GoodGay::GoodGay()
{
	//创建建筑物对象
	building = new Building;
}

void GoodGay::visit() {
	cout << "好基友类正在访问：" << building->m_sittingRoom << endl;

	cout << "好基友类正在访问：" << building->m_BedRoom << endl;
}

void test01() {
	GoodGay gg;
	gg.visit();
}

int main() {
	test01();
	system("pause");
	return 0;
}