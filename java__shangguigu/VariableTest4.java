public class VariableTest4 {
    public static void main(String args[]){
        
        //1.编码情况1：
        long l=123213;//属于自动类型提升，从int到long
        System.out.println(l);
        //编译失败：过大的整数
        //long l1=213345345536;

        //编译不通过
        //float f1=12.3; 从double转为float，不被许可
        
        //2.编码情况2：
        //整形常量，默认类型为int型
        //浮点型常量，默认类型为double型
        byte b =12;
        //byte b1=b+1;  1为int，与byte做运算自动转换为int型

        //float f1=b+12.3;  12.3为double型与float做运算自动转换为double
    }
}
