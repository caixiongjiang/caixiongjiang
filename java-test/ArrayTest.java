public class ArrayTest{
    public static void main(String args[]){
        //1.一维数组的声明和初始化
        int[] ids;//声明
        //1.1静态初始化:数组的初始化和数组元素的赋值操作同时进行
        ids=new int[]{1001,1002,1003};
        //1.2动态初始化：数组的初始化和数组元素的赋值操作分开进行
        String[] names=new String[5];
        //数组一旦初始化完成,其长度就确定了

        //2.调用数组的指定位置的元素：通过角标的方式调用。
        //数组的索引从0开始，到数组的长度-1结束
        names[0]="王明";
        names[1]="张学良";
        names[2]="毛润之";
        names[3]="陈仲甫";
        names[4]="蔡孑民";


        //3.获取数组的长度
        //属性：length
        System.out.println(ids.length);
        System.out.println(names.length);

        //4.遍历数组元素
        for(int i=0;i<names.length;i++){
            System.out.println(names[i]);
        }
    }
}