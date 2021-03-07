#include <stdio.h>
using namespace std;
double num1[1010] = {}, ans[2010] = {};
int main(){
    int n;
    int cnt = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a;
        double b;
        scanf("%d %lf", &a, &b);
        num1[a] = b;
    }
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a;
        double b;
        scanf("%d %lf", &a, &b);
    for (int j = 0; j < 1010; j++) {
        if (num1[j] != 0) {
            ans[j + a] += b*num1[j];
            }
        }
    }
    for (int i = 2000; i >= 0; i--){
        if (ans[i] != 0.0) cnt++;
    }
    printf("%d ", cnt);
    for (int i = 2009; i >= 0; i--) {
        if (ans[i] != 0) {
        printf("%d %.1f", i, ans[i]);
        cnt--;
        if (cnt != 0) printf(" ");
        }
    }
    return 0;
}