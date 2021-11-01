#include<iostream>
#include<string>
using namespace std;

//虚析构和纯虚析构

class Animal
{
public:

	Animal()
	{
		cout << "Animal的构造函数调用" << endl;
	}
	//利用虚析构可以解决父类指针释放子类对象时不干净的问题
	//virtual ~Animal()
	//{
	//	cout << "Animal的析构函数调用" << endl;
	//}
	
	//纯虚析构  需要有声明也需要有实现
	//有了纯虚析构 之后这个类也属于抽象类，无法实例化对象
	virtual ~Animal() = 0;
	
	//纯虚函数
	virtual void speak() = 0;

};

Animal:: ~Animal()
{
	cout << "Animal的纯虚析构函数" << endl;
}

class Cat : public Animal
{	
public:
	Cat(string name) 
	{
		cout << "Cat的构造函数使用" << endl;
		m_Name = new string(name);
	}
	virtual void speak()
	{
		cout << *m_Name << "小猫在说话" << endl;
	}

	~Cat() 
	{
		if (m_Name != NULL) 
		{
			cout << "Cat析构函数调用" << endl;
			delete m_Name;
			m_Name = NULL;
		}
	}
	string *m_Name;
};

void test01()
{
	Animal * animal = new Cat("Tom");
	animal->speak();
	//父类指针在析构时候 不会调用子类中析构函数，
	//导致子类如果有堆区属性，会出现内存的泄露情况
	delete animal;
}

int main()
{
	test01();
	system("pause");
	return 0;
}