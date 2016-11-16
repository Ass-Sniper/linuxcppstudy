#include <stdio.h>

int fun(int& num, const int& inc)
{
	float div = 2.0;
	double ret = 0;
	num += inc;
	ret = num/div;
	return ret;
}

int main(int argc, char *argv[]){
	int a = 3;
	int b = 5;
	printf("%d\n", sizeof(fun(a,b)));
	printf("%d\n", a);
	return 0;
}
