/*c++ call c style function by using extern keyword */
#include <stdio.h>
extern "C"
{
#include "cEg.h"

}

int main(int argc, char* argv[])
{
	printf("In the main function\n");
	add(2,3);
	return 0;
}
