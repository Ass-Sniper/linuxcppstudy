#include <stdlib.h>
#include <stdio.h>
// #include <iostream>

// Suppose int a[3], *p=a; which one cannot represent the address of a[1]?
// A:p+1;B:a+1;C:a++;D:++p


/*void g(int **zptr)
{
	int a = 0; 
	*zptr = &a;
}

void poke(int *z)
{
	int *q = NULL; 
	*z = 0xbad; 
	*q = 42;　//Program will invoke signal SIGSEGV, Segmentation fault.
}
*/

int main(void)
{
/*	int a[3]= {0,1,2};
	int *p = a;

	printf("&a[1] = %p\n", &a[1]);
	printf("p+1   = %p\n", p+1);
	printf("a+1   = %p\n", a+1);
	// printf("a++   = %p\n", a++); //a = a+1, error: lvalue required as increment operand
	printf("++p
	   = %p\n", ++p);*/

	// int a = 5;
	// int *ptr = &a;
	// printf("%p\n", *a);

	// std::cout<< *a <<std::endl;

	// std::cout<< (ptr == a) <<std::endl;

	// std::cout<< (ptr == &a) <<std::endl;

	// std::cout<< **&ptr <<std::endl;

/*	int i = 0; 
	int *z = &i; 
	g(&z); 
	printf("%d\n", sizeof('a'));
	poke(z);*/

/*	printf("sizeof('a')  = %d\n", sizeof('a')); // 32-bit:4
	printf("sizeof(char) = %d\n", sizeof(char));// 32-bit:1
	printf("sizeof(int)  = %d\n", sizeof(int)); // 32-bit:4*/

	return 0;
}
