#include <stdio.h>
int f(int x){
    if(x<=0){
        return 1;
    }
    return x*f(x-1);
}
int main(int argc, char **argv)
{
	printf("%d\n", f(5));
	return 0;
}
