#include<iostream>

using namespace std;

//抽象不同零件类
//抽象CPU类
class CPU
{
public:
	//抽象的计算函数
	virtual void calculator() = 0;
};

//抽象显卡类
class GPU
{
public:
	//抽象的显示函数
	virtual void display() = 0;
};

//抽象内存条类
class Memory
{
public:
	//抽象的存储函数
	virtual void storage() = 0;
};

//电脑类
class Computer
{
public:
	Computer(CPU* cpu, GPU* gpu, Memory* mem)
	{
		m_cpu = cpu;
		m_gpu = gpu;
		m_mem = mem;
	}

	//提供工作的函数
	void work()
	{
		//让零件工作起来，调用接口
		m_cpu->calculator();

		m_gpu->display();

		m_mem->storage();
	}
	//提供析构函数 释放3个电脑零件
	~Computer()
	{
		//释放cpu零件
		if (m_cpu != NULL) 
		{
			delete m_cpu;
			m_cpu = NULL;
		}
		//释放显卡零件
		if (m_gpu != NULL)
		{
			delete m_gpu;
			m_gpu = NULL;
		}
		//释放内存条零件
		if (m_mem != NULL)
		{
			delete m_mem;
			m_mem = NULL;
		}
	}
private:
	CPU * m_cpu;//cpu的零件指针
	GPU * m_gpu;//显卡零件指针
	Memory * m_mem;//内存条的零件指针
};

//具体厂商
//Intel厂商
class IntelCPU : public CPU
{
public:
	virtual void calculator()
	{
		cout << "Intel的CPU开始计算了!" << endl;
	}
};

class IntelGPU : public GPU
{
public:
	virtual void display()
	{
		cout << "Intel的显卡开始显示了!" << endl;
	}
};

class IntelMemory : public Memory
{
public:
	virtual void storage()
	{
		cout << "Intel的内存条开始存储了!" << endl;
	}
};

//Lenovo厂商
class LenovoCPU : public CPU
{
public:
	virtual void calculator()
	{
		cout << "Lenovo的CPU开始计算了!" << endl;
	}
};

class LenovoGPU : public GPU
{
public:
	virtual void display()
	{
		cout << "Lenovo的显卡开始显示了!" << endl;
	}
};

class LenovoMemory : public Memory
{
public:
	virtual void storage()
	{
		cout << "Lenovo的内存条开始存储了!" << endl;
	}
};

void test01()
{
	//第一台电脑零件
	CPU* IntelCpu = new IntelCPU;
	GPU* IntelGpu = new IntelGPU;
	Memory* IntelMem = new IntelMemory;

	cout << "第一台电脑开始工作：" << endl;
	//创建第一台电脑
	Computer* computer1 = new Computer(IntelCpu, IntelGpu, IntelMem);
	computer1->work();
	delete computer1;
	
	cout << "-----------------------" << endl;
	cout << "第二台电脑开始工作：" << endl;
	//第二台电脑组装
	Computer* computer2 = new Computer(new LenovoCPU, new LenovoGPU, new LenovoMemory);
	computer2->work();
	delete computer2;
}

int main()
{
	test01();
	system("pause");
	return 0;
}