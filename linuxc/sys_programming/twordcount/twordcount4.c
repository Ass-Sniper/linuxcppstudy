/* twordcount2.c-threaded word counter for two files. 
 * 				version 4: condition variable allows
 *						function report result early
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

struct arg_set *mailbox;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t flag = PTHREAD_COND_INITIALIZER;

int main(int argc, char const *argv[])
{
	pthread_t t1, t2;
	struct arg_set args1, args2;
	void* count_words(void *);
	int report_in = 0;
	int total_words = 0;

	if (argc < 3){
		printf("useage: %s file1 file2\n", argv[0]);
		exit(1);
	}	
	
	pthread_mutex_lock(&lock); // lock the report mailbox now

	args1.filename = argv[1];
	args2.count = 0;
	pthread_create(&t1, NULL, count_words, (void *)&args1);

	args2.filename = argv[2];
	args2.count = 0;
	pthread_create(&t2, NULL, count_words, (void *)&args2);

	while(report_in < 2) {
		printf("MAIN: waiting for flag to go up\n");
		pthread_cond_wait(&flag, &lock); // wait for notify
		printf("MAIN: flag was raised, I have the lock\n");
		printf("%7d: %s\n", mailbox->count, mailbox->filename);
		total_words += mailbox->count;
		if (mailbox == &args1)
		{
			pthread_join(t1, NULL);
		} 
		if (mailbox == &args2) {
			pthread_join(t2, NULL);
		}
		mailbox = NULL;
		pthread_cond_signal(&flag);
		report_in++;
	}
	printf("%7d: total words\n", total_words);

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

	printf("COUNT: waiting to get lock\n");
	pthread_mutex_lock(&lock); // get the mailbox
	printf("COUNT: have mailbox lock, storing data\n");
	if (mailbox != NULL){
		pthread_cond_wait(&flag, &lock);
	}	
	mailbox = args;	// put ptr args to mailbox
	printf("COUNT: raising falg\n");
	pthread_cond_signal(&flag);
	printf("COUNT: unlocking mailbox\n");
	pthread_mutex_unlock(&lock); // realease the mailbox

	return NULL;
}