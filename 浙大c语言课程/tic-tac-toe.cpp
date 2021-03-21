#include <stdio.h> 

int main()

{

	const int size=3;

	int board[size][size];

	int i,j;

	int numofx;

	int numofo;

	int result=-1;   //-1:没人赢，1:x赢，0:0赢； 

	//读入矩阵

	for (i=0;i<size;i++) {                                //00:1  01:0  02:1 

		for(j=0;j<size;j++) {                             //10:1  11:1  12:0

			scanf("%d",&board[i][j]);                     //20:0  21:0  22:1

		}

	}

	

	//检查行和列

	for (i=0;i<size&&result==-1;i++) {

		numofo=numofx=0;

		for(j=0;j<size;j++) {

			if (board[i][j]==1) {

			

				numofx++;

			

			}else {

			numofo++;

		}

			if (board[j][i]==1) {

				

					numofx++;

				

				}else {

				numofo++;

			}

		}

	} 

	if(numofo==size){

		result=0;

	}else if (numofx==size){

		result=1;

	}

	/*/检出列

	if(result==-1) {

		for (j=0;j<size&&result==-1;j++) {

			numofo=numofx=0;

			for(i=0;i<size;i++) {

				 	if(board[i][j]==1){

						numofx++;

			        }else {

				         numofo++;

			        }

			}

			 

		if(numofo==size){

				result=0;

		}else if (numofx==size){

				result=1;

		}

	   }                               

		   

	

	}*/

	//检查对角线

	numofo=numofx=0;

	for(i=0;i<size;i++) {

		if(board[i][i]==1){

			numofx++;

		}else {

			numofo++;

	   }

	}

	if(numofo==size){

			result=0;

	}else if (numofx==size){

				result=1;

	}

	numofo=numofx=0;

	for(i=0;i<size;i++) {

		if(board[i][size-i-1]==1){

			numofx++;

		}else {

			numofo++;

	   }

   }  
   
   //判断 

   if(result==1){

   	printf("x赢了！"); 

   } else if(result==0){

   	printf("O赢了！"); 

   } else if (result==-1){

   	printf("你俩都没赢，平手！");

   }                         

   return 0;