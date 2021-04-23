#include <stdio.h>
//c语言中用“指针”来表示内存的地址，而如果这个内存地址恰好是某个变量的地址，那么又称“这个指针指向该变量”。
//如果定义为int a的整型变量，&a就表示它的地址
//指针实际上是一个整数，确切的说是一个unsigned类型的整数

using namespace std;
//交换值的函数
void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
int main(){
    int a[10];
    for(int i=0;i<10;i++){
        scanf("%d",a+i);
    }
    for(int i=0;i<10;i++){
        printf("%d",*(a+i));
    }
//指针变量可以使用自增操作
    int a1[10]={1,2,3,4,5,6,7,8,9,10};  //数组名可以作为数组中第一个元素的地址
    for(int *p=a1;p<a1+10;p++){
        printf("%d",*p);
    }

//指针的减法
    int a2[10]={1,4,9,16,25,36,49};
    int *p=a;
    int *q=&a[5];
    printf("q=%d\n",q);     //q为数组a[0]元素的地址
    printf("p=%d\n",p);     //p为数组a[5]元素的地址
    printf("q-p=%d\n",q-p); //两个地址相差5个int，输出的结果为5

//使用指针变量作为函数参数
    int a3=1,b3=2;
    int *p1=&a3,*p2=&b3;
    swap(p1,p2);
    printf("a=%d,b=%d\n",*p1,*p2);

    return 0;
}

