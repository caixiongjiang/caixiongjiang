#include<iostream>
#include<string>

using namespace std;

//const使用场景
struct student {
	string name;
	int age;
	int score;
};
//将函数中的形参改为指针，可以节省内存空间，而且不会赋值一个新的副本出来
void printStudent(const student * s) {
	//s->age = 10; //加入const之后，一旦有修改的操作就会报错，可以防止我们的误操作。
	cout << "姓名： " << s->name << "年龄： "
	<< s->age << "分数： " << s->score << endl;
}

int main() {
	//创建结构体变量
	student s = { "张三", 15, 83 };

	//通过函数来打印结构体变量信息

	printStudent(&s);

	system("pause");
	return 0;
}