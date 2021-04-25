class VariableTest3{
    public  static void mian(String args[]){
        //1.编码情况1：
        long l = 123213;//int转long，成功
        System.out.println(l);

        //编译失败：过大的整数
        //long l1 = 213242354534;

        //编译失败
        //float f1 = 12.3;   double转float(失败)  
        float f1 = (float)12.3;

        //2.编码情况2：
        //整形常量默认类型为int型
        //浮点型常量默认为double型
        byte b = 12;
        //byte b1 = b + 1; 编译失败

        //float f1 = b + 12.3; 编译失败

    }
}