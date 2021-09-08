//封装函数显示菜单界面，如 void showMenu（）
//在main函数中调用封装好的函数
#include<iostream>
#include<string>
#define MAX 1000

using namespace std;

//1.菜单界面
void showMenu() {
	cout << "****************************" << endl;
	cout << "*****   1.添加联系人   *****" << endl;
	cout << "*****   2.显示联系人   *****" << endl;
	cout << "*****   3.删除联系人   *****" << endl;
	cout << "*****   4.查找联系人   *****" << endl;
	cout << "*****   5.修改联系人   *****" << endl;
	cout << "*****   6.清空联系人   *****" << endl;
	cout << "*****   0.退出通讯录   *****" << endl;
	cout << "****************************" << endl;
}
//设计联系人的结构体
struct Person {
	string m_Name;
	int m_Sex;//性别：1代表男，2代表女
	int m_Age;
	string m_Phone;
	string m_Addr;
};

//设计通讯录的结构体
struct addressBooks {
	//通讯中保存的联系人数组
	struct Person personArray[MAX];
	//通讯录中当前记录联系人的个数
	int m_Size;
};

//1.添加联系人
void addPerson(addressBooks * abs) {
	//判断通讯录是否已满，如果满了就不要添加
	if (abs->m_Size == MAX) {
		cout << "通讯录已满，无法添加！" << endl;
	}
	else {
		//添加联系人

		//姓名
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;
	
		//性别
		cout << "请输入性别：" << endl;
		cout << "1 --- 男" << endl;
		cout << "2 --- 女" << endl;
		int sex = 0;
		while (true)
		{
			//如果输入的是1或者2可以退出循环，因为输入的是正确的值
			//如果输入有误，重新输入
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}
		
		//年龄
		cout << "请输入年龄： " << endl;
		int age = 0;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;

		//电话
		cout << "请输入联系电话： " << endl;
		string phone;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//住址
		cout << "请输入家庭住址：" << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		//更新通讯录的人数
		abs->m_Size++;

		cout << "添加成功" << endl;
		system("pause"); //请按任意键继续
		system("cls");//清屏操作
	}
}

//2.显示联系人
void showPerson(addressBooks* abs) {
	//判断通讯录中人数是否为0，如果为0，提示记录为空
	if (abs->m_Size == 0) {
		cout << "当前的记录为空： " << endl;
	}
	else {
		for (int i = 0; i < abs->m_Size; i++) {
			cout << "姓名： " << abs->personArray[i].m_Name << "\t";
			cout << "性别： " << (abs->personArray[i].m_Sex == 1 ? "男" : "女")<< "\t";
			cout << "年龄： " << abs->personArray[i].m_Age << "\t";
			cout << "电话： " << abs->personArray[i].m_Phone << "\t";
			cout << "住址： " << abs->personArray[i].m_Addr << endl;
			
			system("pause"); //请按任意键继续
			system("cls");//清屏操作
		}
	}
}


//3.1检测联系人是否存在，如果存在，返回联系人所在数组的具体位置，不存在返回-1
//参数1： 通讯录  参数二：对比姓名
int isExist(addressBooks * abs, string name) {
	for (int i = 0; i < abs->m_Size; i++) {
		//找到用户输入的姓名了
		if (abs->personArray[i].m_Name == name) {
			return i;//返回这个人在数组中的下标编号
		}
	}
	//如果遍历结束都没有找到，就返回-1
	return -1;
}

//3.2删除联系人
void deletePerson(addressBooks* abs) {
	cout << "请输入您要删除的联系人" << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);
	if (ret != -1) {
		//进行删除操作:例如要删除李四，就将李四的数据从后往前移，并且让通讯录中记录的人员做一个-1的操作
		for (int i = ret; i < abs->m_Size; i++) {
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--;//更新通讯录中的人员数
		cout << "删除成功" << endl;
	}
	else {
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

//4.查找联系人
void findPerson(addressBooks* abs) {
	cout << "请输入您要查找的联系人" << endl;
	string name;
	cin >> name;

	//判断指定的联系人是否存在
	int ret = isExist(abs, name);

	if (ret != -1) {
		cout << "姓名：" << abs->personArray[ret].m_Name << "\t";
		cout << "性别：" << abs->personArray[ret].m_Sex << "\t";
		cout << "年龄：" << abs->personArray[ret].m_Age << "\t";
		cout << "电话：" << abs->personArray[ret].m_Phone<< "\t";
		cout << "地址：" << abs->personArray[ret].m_Addr<< endl;
	}
	else {
		cout << "查无此人" << endl;
	}

	system("pause");
	system("cls");
}

//5.修改指定的联系人信息
void modifyPerson(addressBooks* abs) {
	cout << "请输入您要修改的联系人" << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);
	if (ret != -1) {//找到指定的联系人
		//姓名
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personArray[ret].m_Name = name;
		//性别
		int sex = 0;
		cout << "请输入性别" << endl;
		cout << "1 --- 男" << endl;
		cout << "2 --- 女" << endl;
		
		while (true) {
			cin >> sex;
			if (sex == 1 || sex == 2) {
				//输入正确 退出循环输入
				abs->personArray[ret].m_Sex = sex;
				break;
			}
				cout << "输入有误，请重新输入" << endl;
		}
			//年龄
			cout << "请输入年龄：" << endl;
			int age = 0;
			cin >> age;
			abs->personArray[ret].m_Age = age;
 			//电话
			cout << "请输入联系电话：" << endl;
			string phone;
			cin >> phone;
			abs->personArray[ret].m_Phone = phone;
			//住址
			cout << "请输入家庭住址： " << endl;
			string address;
			cin >> address;
			abs->personArray[ret].m_Addr = address;

			cout << "修改成功" << endl;
	}	
	else {//未找到联系人
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

//6.清空所有联系人
	//实现思路，将通讯录所有联系人信息清除掉，只要将通讯录记录的联系人数量置为0，做逻辑清空
void clearPerson(addressBooks * abs){
	abs->m_Size = 0;
	cout << "通讯录已清空" << endl;
	system("pause");
	system("cls");
}

int main(){
	//创建通讯录结构体变量
	addressBooks abs;
	//初始化通讯录中当前人员的个数
	abs.m_Size = 0;

	int select = 0;//创建一个用户选择输入的变量

	while (true) {
		showMenu();

		cin >> select;

		switch (select)
		{
		case 1:                    //1.添加联系人
			addPerson(&abs);//利用地址传递可以修饰实参
			break;
		case 2:					   //2.显示联系人
			showPerson(&abs);
			break;
		case 3:                    //3.删除联系人
			deletePerson(&abs);
			break;
		case 4:                    //4.查找联系人 
			findPerson(&abs);
			break;
		case 5:                    //5.修改联系人
			modifyPerson(&abs);
			break;
		case 6:                    //6.清空联系人  
			clearPerson(&abs);
			break;
		case 0:                    //0.退出通讯录 
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}
	 }
	system("pause");
	return 0;
}