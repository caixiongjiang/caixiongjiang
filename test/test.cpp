#include<iostream>
#include<string>

using namespace std;

//建筑物类
class Building 
{
	//goodGay全局函数是 Building好朋友，可以访问Building中私有的成员
	friend void goodGay(Building* building);
public:
	Building()
	{
		m_sittingRoom = "客厅";
		m_BedRoom = "卧室";
	}

public:
	string m_sittingRoom; // 客厅

private:
	string m_BedRoom; //卧室
};

//全局函数
void goodGay(Building* building)
{
	cout << "好基友全局函数 正在访问：" << building->m_sittingRoom << endl;

	cout << "好基友全局函数 正在访问：" << building->m_BedRoom << endl;
}

void test01()
{
	Building building;
	goodGay(&building);
}


int main() {

	test01();
	system("pause");
	return 0;
}