/* twordcount2.c-threaded word counter for two files. 
 * 				version 3: one counter per file
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h> // for using isalnum() function

struct arg_set
{
	char const *filename;
	int count;
};

int main(int argc, char const *argv[])
{
	pthread_t t1, t2; /*two threads*/
	struct arg_set args1, args2; /*two argsset*/
	void* count_words(void *);

	if (argc < 3){
		printf("useage: %s file1 file2\n", argv[0]);
		exit(1);
	}	

	args1.filename = argv[1];
	args1.count = 0;
	pthread_create(&t1, NULL, count_words, (void *)&args1);

	args2.filename = argv[2];
	args2.count = 0;
	pthread_create(&t2, NULL, count_words, (void *)&args2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("%5d: %s\n", args1.count, argv[1]);
	printf("%5d: %s\n", args2.count, argv[2]);
	printf("%5d: total words\n", args1.count + args2.count);

	return 0;
}

void* count_words(void *arg)
{
	struct arg_set *args = (struct arg_set *)arg;
	FILE *fp;
	int c, prevc = '\0';

	if ((fp = fopen(args->filename, "r")) != NULL){
		while((c = getc(fp)) != EOF) {
			if (!isalnum(c) && isalnum(prevc)){
				args->count++;
			}
			prevc = c;
		}
		fclose(fp);
	} else {
		perror(args->filename);
	}

	return NULL;
}