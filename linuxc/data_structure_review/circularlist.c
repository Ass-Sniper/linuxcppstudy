#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h> // for using UINT_MAX
#include <assert.h>
#include <stdint.h> // for using uint32_t

typedef uint32_t uint;

typedef enum boolean {true=1, false=0} bool;

// Singly linked list node
typedef struct linkedListNode
{
	int data;
	struct linkedListNode *pnext;
} lnode;

lnode* createcircularlinkedlist()
{
	lnode *head = NULL;
	head = (lnode *)malloc(sizeof(lnode));
	head->data = 0;
	head->pnext = head;
	return head;
}

int deleteList(lnode *head_ref)
{
	uint cnt = 0;
	lnode *currhead = NULL, *temp = NULL;
	currhead = head_ref->pnext; //Let currhead points to head's next node so that we can release the memory of head node 
	free(head_ref);
	cnt++;
	while(currhead != head_ref) {
		temp = currhead->pnext;
		free(currhead);
		cnt++;
		currhead = temp;
	}
	head_ref = NULL;
    printf("---[%d] node%s that %s head node had been released---\n", cnt, (cnt<=1)?"":"s", (cnt<=1)?"is":"contain");
    return cnt;
}

lnode* newNode(int const new_data)
{
	lnode *newnode = NULL;
	newnode = (lnode *)malloc(sizeof(lnode));
	newnode->data = new_data;
	newnode->pnext = NULL;
	return newnode;	
}

bool IsEmpty(lnode const *head_ref) 
{
	if((NULL == head_ref) || (head_ref->pnext == head_ref)) {
		printf("list is empty.\n");
		return true;
	}
	return false;	
}

void printAllElements(lnode const *head_ref)
{
	lnode *worker = NULL;
	lnode *temp = NULL;
	uint i = 1;	
	if (IsEmpty(head_ref) == true)
	{
		return;
	}
	worker = head_ref->pnext;
	// printf("list head at: %p\n", head_ref);
	while(worker != head_ref) {
		temp = worker->pnext;
		printf("element[%d] at [%p]---[data]: %d\t---[pnext]: %p\n", i, worker, worker->data, worker->pnext);
		i++;
		worker = temp;
	}
}

void printByGraphic(lnode const *head_ref)
{
	lnode *worker = NULL;
	uint i = 1;
	if((NULL == head_ref) || (head_ref == head_ref->pnext))
	{
		printf("list is empty\n");
		return;
	}
	worker = head_ref->pnext;
	// printf("[head:%d;%p]->", head_ref->data, head_ref->pnext);
	printf("[head:%d]->", head_ref->data);	
	while(worker != head_ref) {
		// printf("[node:%d;%p]", worker->data, worker->pnext);
		printf("[node:%d]->", worker->data);
		i++;
		worker = worker->pnext;
		if(i%6 == 0) {
			printf("\n");
		}
	}
	printf("[head:%d]\n", head_ref->data);
}

lnode* getTail(lnode *head_ref)
{
	lnode *worker = head_ref;
	while(head_ref != worker->pnext) {
		worker = worker->pnext;
	}
	return worker;
}

lnode* getPrev(lnode *head_ref, lnode *node)
{
	lnode *worker = head_ref;
	while(head_ref != worker->pnext) {
		if(worker->pnext == node)
			break;
		worker = worker->pnext;
	}
	return worker;
}

// Append new element 'new_data' at list's tail
bool appendElement(lnode *head_ref, int const new_data)
{
	bool flag = false;
	lnode *last = NULL;
	if(NULL == head_ref) {
		printf("---list is not created---\n");
		return flag;
	}
	lnode *newnode = newNode(new_data);
	last = getTail(head_ref);
	newnode->pnext = last->pnext; // At this time, last has pointed to head node, so last->node == head_ref
	last->pnext = newnode;
	head_ref->data++; // change list's count
	return flag;
}

int main(int argc, char const *argv[])
{
	lnode *circularlist = NULL;
	circularlist = createcircularlinkedlist();
	// printByGraphic(circularlist);
	// printAllElements(circularlist);
	appendElement(circularlist, 111);
	// printByGraphic(circularlist);
	// printAllElements(circularlist);
	deleteList(circularlist);
	// printByGraphic(circularlist);
	printAllElements(circularlist);
	return 0;
}


