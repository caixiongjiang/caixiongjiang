#include <stdio.h>

int main()
{
	int x;
	scanf("%d", &x);
	int digit;
	int ret = 0;

	while ( x> 0 ) {
		digit = x%10;
		printf("%d", digit);		
		ret = ret*10 + digit;
		// printf("x=%d,digit=%d,ret=%d\n", x, digit, ret);
		x /= 10;
	}
	printf(" ret = %d", ret);				//输入700,结果为007，ret的值为7
	
	return 0;
}