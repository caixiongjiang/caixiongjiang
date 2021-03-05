#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <math.h>
#include <string.h>

using namespace std;

int main(){

//一维数组的定义格式 数据类型 数组名[数组大小]
    int a[10];
    double db[2333];
    char str[100000];
    bool HashTable[1000000];
//一维数组的初始化
    int b[10]={5,3,2,6,8,4};                //前面6个数赋值后，后面没有赋值的部分默认赋为0
    int c[10]={0};                          //将整个数组都赋值为0，也可以用int c[10]={};
//可以根据一些条件，可以让后一位的结果由前一位或若干位计算而来。
    scanf("%d",&a[0]);
    for(int i=1;i<10;i++){
        a[i]=a[i-1]*2;
    }
    for(int i=0;i<10;i++){
        printf("a[%d]=%d\n",i,a[i]);
    }
//冒泡排序
    int a2[10]={3,1,4,5,2};
    for(int i=1;i<=4;i++){                  //要进行n-1趟排序
        for(int j=0;j<5-i;j++){             //进行一轮排序
            if(a2[j]>a2[j+1]){
                int temp=a2[j];
                a2[j]=a2[j+1];
                a2[j+1]=temp;
            }
        }
    }
    for(int i=0;i<5;i++){
        printf("%d",a2[i]);
    }

//二维数组 格式：数组名[第一维大小][第二维大小]
    int a3[5][6];
    double db3[10][10];
    char c3[256][256];
    bool vis[1000][1000];

    int a4[3][3],b4[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&a4[i][j]);          //输入二维数组a4的元素
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&b4[i][j]);          //输入二位数组b4的元素
        }
    }
    int c4[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            c4[i][j]=a4[i][j]+b4[i][j];     //对应位置元素相加并放到二位数组c4中
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%d ",c4[i][j]);         //输出二维数组c4的元素
        }
        printf("\n");                       //每三个换行
    }
//使用memset函数和fill函数给数组中的每个值都赋相同的值
//格式:memset(数组名,值,sezeof(数组名));(此处头文件使用string.h)
    int a[5]={1,2,3,4,5};
    memset(a,0,sizeof(a));
    for(int i=0;i<5;i++){
        printf("%d",a[i]);
    }
//字符数组的初始化
    char str[15]={'G','o','d','s'};
    for(int i=0;i<4;i++){
        printf("%c",str[i]);
    }

//getchar输入,putchar输出单个字符
//gets输入一行字符串(识别\n作为输入结束)puts进行输出
//%c格式能识别空格跟换行并将其输入，%s通过空格和换行来识别一个字符串的结束。

//string.h可以使用strlen(),strcmp(),strcmp(),strcpy(),strcat()。
//strlen函数可以得到字符数组第一个\0前的字符的个数

//strcmp函数返回两个字符串大小的比较结果，格式为strcmp(字符数组1，字符数组2)
//若字符数组1大于字符数组2，则返回大于0的整数，若相等，则返回0，小于则返回小于0的整数

//strcpy函数可以把一个字符串复制给另一个字符串，格式为strcpy(字符数组1,字符数组2)
//注意：把字符数组2复制给字符数组2

//strcat()函数可以把一个字符串接到另一个字符串的后面，格式为strcat(字符数组1,字符数组2)
//注意：是把字符数组2接到字符数组1的后面
    getchar();
    system("pause");        
    return 0;                            
}
