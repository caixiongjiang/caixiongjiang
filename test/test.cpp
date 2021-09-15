#include<iostream>

using namespace std;

//1.创建一个立方体的类
//2.设计属性和行为
//3.获取立方体的面积和体积
//4.分别利用全局函数和成员函数判断两个立方体是否相等
class Cube {
public:
	void setL(int l) {
		m_L = l;
	}

	int getL() {
		return m_L;
	}

	void setW(int w) {
		m_W = w;
	}
	
	int getW() {
		return m_W;
	}

	void setH(int h) {
		m_H = h;
	}
	
	int getH() {
		return m_H;
	}
//获取立方体面积
	int calculateS() {
		return 2 * m_L * m_W + 2 * m_W * m_H + 2 * m_L * m_H;
	}
//获取立方体体积
	int calculateV() {
		return m_L * m_W * m_H;
	}
//利用成员函数判断两个立方体是否相等
	bool isSameByClass(Cube &c) {
		if (m_L == c.getL() && m_W == c.getW() && m_H == c.getH()) {
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	
	int m_L;//长
	int m_W;//宽
	int m_H;//高
};

//利用全局函数判断两个立方体是否相等
bool isSame(Cube &c1, Cube &c2) {
	if (c1.getL() == c2.getL() && c1.getW() == c2.getW() && c1.getH() == c2.getH()) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	//创建一个立方体
	Cube c1;
	c1.setL(10);
	c1.setW(20);
	c1.setH(20);

	cout << "c1的面积为：" << c1.calculateS() << endl;
	cout << "c1的体积为：" << c1.calculateV() << endl;

	//创建第二个立方体
	Cube c2;
	c2.setL(11);
	c2.setW(20);
	c2.setH(20);
	
	//利用全局函数判断立方体是否相等
	bool ret = isSame(c1, c2);
	if (ret) {
		cout << "c1和c2是相等的" << endl;
	}
	else
	{
		cout << "c1和c2不相等" << endl;
	}
	//利用成员函数判断立方体是否相等
	bool ret2 = c1.isSameByClass(c2);
	if (ret2) {
		cout << "c1和c2是相等的" << endl;
	}
	else
	{
		cout << "c1和c2不相等" << endl;
	}
	system("pause");
	return 0;
}