/*
100000以内的质数的输出:
从2开始，到这个数-1结束为止，都不能被这个数本身整除
*/
public class PrimeNumberTest {
    public static void main(String args[]){
        boolean flag=true;//标识是否为素数
        long start=System.currentTimeMillis();//获取当前时间距离1970—01-01 0点0分0秒的毫秒数
        for(int i=2;i<=100000;i++){
            for(int j=2;j<=Math.sqrt(i);j++){
                if(i%j==0){
                    flag=false;
                    break;//若已经不是素数则跳出循环(只对非质数的自然数有作用)
                }
            }
            if(flag==true){
                System.out.println(i);
            }
            //重置flag
            flag=true;
        }
        long end=System.currentTimeMillis();//获取当前时间距离1970—01-01 0点0分0秒的毫秒数
        System.out.println("所花费的时间："+(end-start));//18.72s  优化1：加了break之后为2.5s
                                                        //优化2：j<Math.sqrt(i) 1.01s
    }
}
