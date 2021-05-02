public class ArrayTest3 {
    public static void main(String args[]){
        int[] arr=new int[]{1,2,3};
        String[] arr1=new String[4];
        arr1[0]="刘德华";
        arr1[1]="张学友";
        arr1=new String[3];
    }
}
/*
局部变量放在栈中
new出来的结构都放在堆中
*/