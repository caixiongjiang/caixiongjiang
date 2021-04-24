/*
String类型变量的使用
1.String属于引用数据类型
2.声明String类型变量时，使用一对""
3.String可以和8种基本数据类型做运算，且运算只能是连接运算：+
4.运算的记过仍然是String类型
*/
public class StringTest {
    public static void main(String[] args){
        String s1 ="Hello World!";

        System.out.println(s1);

        String s2 = "a";
        String s3 = "";
        //char c = ''; 编译不通过

        int number = 1001;
        String numberStr = "学号: ";
        String info = numberStr + number;
        boolean b1 = true;
        String info1=info+b1;//连接运算
        System.out.println(info1);

        //练习1
        char c = 'a';
        int num = 10;
        String str = "hello";
        System.out.println(c + num + str);//107hello  answer:107hello
        System.out.println(c + str + num);//ahello10  answer:ahello10
        System.out.println(c + (num + str));//a10hello  answer:a10hello
        System.out.println((c + num) + str);//107hello  answer:107hello
        System.out.println(str + num + c);//hello10a  answer:hello10a

        //练习2
        //''(char)  ""(String)
        //* *
        System.out.println("*   *");//answer:*   *
        System.out.println('*'+'\t'+'*');//answer:93
        System.out.println('*'+"\t"+'*');//answer:*        *
        System.out.println('*'+'\t'+"*");//answer:51*
        System.out.println('*'+('\t'+"*"));//answer:*      *
    }
}
