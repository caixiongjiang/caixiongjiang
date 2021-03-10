#include<stdio.h>
#include<math.h>

using namespace std;

int main()
{ double eps;
  scanf ("%lf", &eps);
int i = 0;  
int flag = 1; 
int denominator = 1; 
double item = 1.0; 
double s = 0;  
while(fabs(item) >= eps){ 
 item = flag * 1.0 / denominator; 
 s = s + item;  
 i++;  
 flag = -flag; 
 denominator = denominator + 2;  
}
printf ("%.2f\n", s);
printf("%d\n",i);
  return 0;
}
