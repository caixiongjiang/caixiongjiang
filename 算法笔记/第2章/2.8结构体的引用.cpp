#include <stdio.h>

using namespace std;
/*结构体的定义，基本格式：
struct Name{
    一些基本的数据结构或者自定义的数据类型 
}
struct  studentInfo{
    int id;
    char gender;
    char name[20];
    char major[20];
}Alice,Bob,stu[1000];       //Alice和Bob代表两个结构体变量，stu为结构体数组

struct studentInfo1{
    int id1;
    char name1[20];
    studentInfo1*next;      //多一个next指针用来指向下一个学生的地址
}stu,*p;                    //定义普通变量stu和指针变量p

访问stu中的变量的写法如下：stu.id    stu.name   stu.next
访问指针变量p中的元素写法如下：(*p).id   (*p).name  (*p).next 

默认生成的构造函数举例；
struct studentInfo{
    int id;
    char gender;
    studentINfo(){}     //此句对结构体默认初始化
}
*/

struct Point{                               //结构体Point用于存放平面点的坐标x，y
    int x,y;
    Point(){}
    Point(int _x,int _y):x(_x),y(_y){}      //用以提供x和y的初始化

}pt[10];

int main(){
    int num=0;
    for(int i=1;i<=3;i++){
        for(int j=0;j<=3;j++){
            pt[num++]=Point(i,j);           //直接使用构造函数
        }
    }
    for(int i=0;i<num;i++){
        printf("%d,%d\n",pt[i].x,pt[i].y);
    }
    return 0;
}