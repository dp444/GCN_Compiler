#include <stdio.h>

int add(int a,int b){return a+b;}
int sub(int a,int b){return a-b;}
int mul(int a,int b){return a*b;}

int main() {
    int (*ops[3])(int,int) = {add,sub,mul};
    int a=7,b=5;
    for (int i=0;i<3;++i)
        printf("%d\n", ops[i](a,b));
    return 0;
}