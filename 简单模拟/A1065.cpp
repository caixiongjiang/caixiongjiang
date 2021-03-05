#include <stdio.h>

using namespace std;

int main(){
    int n,tcase=1;
    long long a,b,c;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%lld%lld%lld",&a,&b,&c);
        long long sum=a+b;
        bool flag;
        if(a>0&&b>0&&sum<0) flag=true;          //正溢出为true
        else if(a<0&&b<0&&sum>=0) flag=false;   //负溢出为false
        else if(sum>c) flag=true;               //无溢出,a+b>c为true
        else flag=false;                        //无溢出,a+b<=c为false
        if(flag==true){
            printf("Case #%d: true\n",tcase++);
        }
        else{
            printf("Case #%d: false\n",tcase++);
        }
    }
    return 0;
}