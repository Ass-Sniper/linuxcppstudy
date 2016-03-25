/*c source file : cMain.c, for testing c call c++ style function */
/*This will lead to a compile error: #include "cppEg.h"*/
extern int add(int x, int y);

int main(int argc, char* argv[])
{
	add(2,3);
	return 0;
}

