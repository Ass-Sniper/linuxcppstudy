/* more2.c
 * version 0.2
 * read and print 24 lines then pause for a few special commands
 * feature of version 0.2: reads from /dev/tty for commands 
 */

#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more(FILE *);

int main(int argc, char const *argv[])
{
	FILE *fp;
	if (argc == 1) {
		do_more(stdin);
	} else {
		while(--argc) {
			if ((fp = fopen(*++argv, "r")) != NULL) {
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
	FILE *fp_tty;

	/* File "/dev/tty" represents keyboard and screen device decription file
	   Reading from this file equals to retrieve user input from stardand input device keyboard;
	   Writing to this file equals to output relevant content to stardand ouput device screen*/
	fp_tty = fopen("/dev/tty", "r"); 
	if (fp_tty == NULL) {
		exit(1);
	}
	while(fgets(buffer, LINELEN, fp)) {
		if (num_of_lines == PAGELEN) {
			reply = see_more(fp_tty);
			if (reply == 0) {
				break;
			}
			num_of_lines -= reply;
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
int see_more(FILE *cmd)
{
	int c;
	printf("\033[7m more?\033[m"); /*output effect's format control:"\033[7m" reverse display;"\033[1m": set brightness*/
	while((c = getc(cmd)) != EOF) {/*reads from tty*/
	    if (c == 'q') {			/*quit*/
	    	return 0;
	    } else if (c == ' ')	/*next page*/
	    {
	    	return PAGELEN;
	    } else if (c == '\n')	/*next line*/
	    {
	    	return 1;
	    }
	}

	return 0;
}