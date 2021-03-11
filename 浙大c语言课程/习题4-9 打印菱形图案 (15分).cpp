//输入样例 7,输出：
//      * 
//    * * * 
//  * * * * * 
//* * * * * * * 
//  * * * * * 
//    * * * 
//      * 



#include <stdio.h>
int main(){
	int n;
	scanf("%d",&n);
	if(n%2!=0){
		for(int i=1;i<=n/2+1;i++){  //上半部分 n/2+1行 
			for(int j=1;j<=(n+1)/2-i;j++){
			    printf("  ");
		    }
			for(int m=1;m<=2*i-1;m++){
				printf("* ");
			}
			printf("\n");  
		}
		
		for(int l=1;l<=n/2;l++){    //下半部分 n/2行 
			for(int z=1;z<=l;z++){
				printf("  ");
			}
			for(int k=1;k<=n-2*l;k++){
				printf("* ");
			}
			printf("\n");
		} 
	}
	return 0;
} 