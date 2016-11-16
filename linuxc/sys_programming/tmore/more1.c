/* more1.c
 * version 0.1
 * read and print 24 lines then pause for a few special commands
 */

#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more();

int main(int argc, char const *argv[])
{
	FILE *fp;
	if (argc == 1) {
		do_more(stdin);
	} else {
		while(--argc) {
			if ((fp = fopen(*++argv, "r")) != NULL){
				do_more(fp);
				fclose(fp);
			} else {
				exit(1);
			}
		}
	}

	return 0;
}

/*
 * read PAGELEN lines, then call see_more() for further instructions
 */
void do_more(FILE *fp) 
{
	char buffer[LINELEN];
	int num_of_lines = 0;
	int reply;

	while(fgets(buffer, LINELEN, fp)) {
		if (num_of_lines == PAGELEN) {
			reply = see_more();
			if (reply == 0) {
				break;
			}
			num_of_lines -= reply; /*reset count*/
		}
		if (fputs(buffer, stdout) == EOF) {
			exit(1);
		}
		num_of_lines++;
	}

}

/*
 * print message, wait for response, return # of lines to advance
 * q means no, space means yes, CR means one line
 */
int see_more()
{
	int c;
	printf("\033[7m more?\033[m"); /*输出特效格式控制：\033[7m 反显;\033[1m 设置高亮度*/
	while((c = getchar()) != EOF) {
	    if (c == 'q') {
	    	return 0;
	    } else if (c == ' ')
	    {
	    	return PAGELEN;
	    } else if (c == '\n')
	    {
	    	return 1;
	    }
	}

	return 0;
}