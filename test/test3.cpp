#include <iostream>
using namespace std;

//实现通用 对数组进行排序的函数
//规则 从大到小
//算法 选择排序
//测试 char数组 ，int数组

//交换函数模板
template<typename T>
void mySwap(T &a, T &b)
{
        T temp = a;
        a = b;
        b = temp;
}

//排序算法(简单选择排序)
template<typename  T>
void mySort(T arr[], int length)
{
    for(int i = 0; i < length; i++)
    {
        int max = i; //认定最大值的下标
        for(int j = i + 1; j < length; j++)
        {
            if(arr[max]  < arr[j])
            {
                max = j;
            }
        }
        if(max != i)
        {
            //交换max和i元素
            mySwap(arr[max], arr[i]);
        }
    }
}

//提供打印数组模板
template<typename T>
void printArray(T arr[], int length)
{
    for(int i = 0; i < length; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void test01()
{
    //测试char数组
    char charArr[] = "badcfe";
    int len = sizeof (charArr) / sizeof (char);
    mySort(charArr, len);
    printArray(charArr, len);
}

void test02()
{
    //测试int数组
    int intArr[] = {7,5,1,9,3,2,4,8};
    int len = sizeof (intArr) / sizeof (int);
    mySort(intArr, len);
    printArray(intArr, len);
}

int main()
{
    test01();
    test02();
    return 0;
}