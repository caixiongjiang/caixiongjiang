/*
九九乘法表
1*1=1
2*1=2 2*2=4
···
*/
public class NineNineTable {
    public static void main(String args[]){
        for(int i=1;i<=9;i++){
            for(int j=1 ;j<=9;j++){
                System.out.print(i+"*"+j+"="+(i*j)+"");
            }
            System.out.println(); 
        }
    }
}
