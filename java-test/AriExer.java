/*随意给出一个整数，打印显示它的个位数，十位数，百位数的值。
格式如下：
数字xxx的情况如下：
个位数：
十位数：
百位数：

*/
class AriExer {
    public static void main(String args[]){
        int num = 187;
        
        int bai = num / 100;
        int shi = num % 100 / 10;
        int ge = num % 10;

        System.out.println("百位为：" + bai);
        System.out.println("十位为：" + shi);
        System.out.println("个位为：" + ge);
    }
}