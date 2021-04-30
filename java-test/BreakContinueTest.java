/*
break和continue关键字的使用
              使用范围                  循环中使用的作用
break：      switch-case                 结束当前循环
             循环结构中
continue:    循环结构中                   结束当次循环

*/

public class BreakContinueTest {
    public static void main(String args[]){
        for(int i=1;i<=10;i++){
            if(i%4==0){
                break;
            }
            System.out.println(i);
        }
    }
}
