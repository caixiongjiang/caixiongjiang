#include <iostream>
#include <string>
using namespace std;

int main() {
	string user;		//用户的输入
	getline(cin, user);	//读取整行字符
	int len = user.length();//计算字符串的长度
	int k, p = len;
	for (int i = len - 1; i >= 0; i--)//从后往前遍历
	{
		if (user[i] == ' ')
		{
			for (k = i + 1; k <= p - 1; k++)
			{
				cout << user[k];
			}
			cout << " ";
			p = i;//保存当前找到的空格的位置
		}
	}
	//到这里的时候还剩第一个没输出
	for (int i = 0; i < p; i++)
		cout << user[i];
	return 0;
}