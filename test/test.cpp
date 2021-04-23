#include<stdio.h> 
int main()
{
int i, j, m, n; 
scanf("%d", &n);
m = n/2;
for (i = 1; i <= m+1; i++){
  for(j=1;j<=m+1-i;j++) 
{
    printf (" ");
  }     
  for(j=1;j<=2*i-1;j+=2)
{
    printf ("*");
  }     
  printf ("\n");
}
for (i = m; i >= 1; i--){
  for (j=1;j<i;j++)
{
    printf (" ");
  }     
  for(j=2*i-1;j>0;j--) 
{
    printf ("*");
  }     
  printf ("\n");
}
}