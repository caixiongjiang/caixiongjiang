public class ArrayTest1 {
    public static void main(String args[]){
        /*
        5.数组元素的默认初始化值
            >数组元素是整型：0
            >数组元素是浮点型：0.0
            >数组元素是char类型：0(不是'0''),ASCII码值为0对应的数据。
            >数组元素是布尔型：false

            >数组元素是引用数据类型时：null
        */
        int[] arr=new int[4];
        for(int i=0;i<arr.length;i++){
            System.out.println(arr[i]);//输出4个0
        }
        System.out.println("*****");
        
        short[] arr1=new short[4];
        for(int i=0;i<arr1.length;i++){
            System.out.println(arr1[i]);//输出4个0
        }


        float[] arr2=new float[4];
        for(int i=0;i<arr2.length;i++){
            System.out.println(arr2[i]);
        }

        System.out.println("*****");
        char[] arr3=new char[4];
        for(int i=0;i<arr3.length;i++){
            System.out.println("---"+arr3[i]+"---");
        }
        if(arr3[0]== 0){
            System.out.println("你好！ ");
        }

        System.out.println("*****");
        boolean[] arr4=new boolean[4];
        for(int i=0;i<arr4.length;i++){
            System.out.println(arr4[i]);
        }

        System.out.println("*****");
        String[] arr5=new String[4];
        for(int i=0;i<arr5.length;i++){
            System.out.println(arr5[i]);
        }
    }
}
