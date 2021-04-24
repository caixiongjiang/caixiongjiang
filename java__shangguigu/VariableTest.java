/*
基本数据类型之间的运算规则:

前提：这里讨论的只是7种数据类型变量之间的运算
1.自动类型提升：
    当容量小的数据类型的变量和容量大的数据类型的变量做运算，结果自动提升为容量大的数据类型。
    *此时的容量大小指的是，表示数的范围的大和小*
    byte,char,short->int->long->float->double

    特别的：当byte,char,short三种类型的变量做运算时，结果为int型，包括自身做运算。
    
2.强制类型转换：见VariableTest3.java
*/
class VariableTest{
    public static void main(String[] args){
        byte b1=2;
        int i1=12;
        //编译不通过
        //byte b2=b1+i1;
        int i2=b1 + i1;
        long l1 = b1 + i1;
        System.out.println(i2);

        float f = b1+i1;
        System.out.println(f);

        char c1='a';//97
        int i3=10;
        int i4=c1+i3;
        System.out.println(i4);

        short s2=10;
        //char c2=c1+s2; 编译不通过

        byte b2=10;
        //char c3=c1+b2; 编译不通过
        //short s3=b2+s2; 编译不通过
    }
}