public class LogicTest {
    public static void main(String args[]){
        //区分&与&&
        boolean b1 = false;
        int num1 = 10;
        if(b1 & (num1++ > 0)){
            System.out.println("我现在在北京");
        }else{
            System.out.println("我现在在南京");//✔
        }
        System.out.println("num1 = " + num1);//11

        boolean b2 = false;
        int num2 = 10;
        if(b2 && (num2++ > 0)){ //此时的&&：因为b2为false，整个结果为false
                                //且此时不会去执行后半部分的语句就可以判断整个语句是true还是false了
            System.out.println("我现在在北京");
        }else{
            System.out.println("我现在在南京");//✔
        }
        System.out.println("num2 = " + num2);//10


        //区分 |与||
        boolean b3 = true;
        int num3 = 10;
        if(b3 | (num3++ > 0)){
            System.out.println("我现在在北京");//✔
        }else{
            System.out.println("我现在在南京");
        }
        System.out.println("num3 = " + num3);//11


        boolean b4 = true;
        int num4 = 10;
        if(b4 || (num4++ > 0)){  //此时的||：因为b4为true，整个结果为true
            //且此时不会去执行后半部分的语句就可以判断整个语句是true还是false了
            System.out.println("我现在在北京");//✔
        }else{
            System.out.println("我现在在南京");
        }
        System.out.println("num4 = " + num4);//10

    }
}
