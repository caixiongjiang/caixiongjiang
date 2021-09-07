#include<iostream>
#include<string>
using namespace std;


//1.设计英雄结构体
struct Hero {
	string name;
	int age;
	string sex;
};
//打印排序后的数组中的信息
void printHero(struct Hero heroArray[], int len) {
	for (int i = 0; i < len; i++) {
		cout << "姓名： " << heroArray[i].name << "年龄: " << heroArray[i].age
			<< "性别： " << heroArray[i].sex << endl;
	}
}

//冒泡排序实现年龄的升序排列
void bubbleSort(struct Hero heroArray[], int len) {
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			if (heroArray[j].age > heroArray[j + 1].age) {
				struct Hero temp = heroArray[j];
				heroArray[j] = heroArray[j + 1];
				heroArray[j + 1] = temp;
			}
		}
	}
}


int main() {
	//2.创建数组存放5名英雄
	Hero heroArray[5] = {
		{"刘备", 23, "男"},
		{"张飞", 22, "男"},
		{"关羽", 20, "男"},
		{"赵云", 19, "男"},
		{"貂蝉", 21, "女"}
	};

	int len = sizeof(heroArray) / sizeof(heroArray[0]);
	
	//3.对数组进行排序，按照年龄进行升序排列
	bubbleSort(heroArray, len);
	//4.将排序后结果打印输出
	printHero(heroArray, len);

	system("pause");
	return 0;
}