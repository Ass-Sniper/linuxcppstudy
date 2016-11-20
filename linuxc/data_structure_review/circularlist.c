/**
 *	Circular Singly Linked List
 *	Copyright (c) 2016-2018 Ass-Sniper
 *	All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h> // for using UINT_MAX
#include <assert.h>
#include <stdint.h> // for using uint32_t

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

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

int destroyList(lnode **head_ref)
{
/*	uint cnt = 0;
	lnode *curr = NULL, *temp = NULL;
	curr = head_ref->pnext; //Let curr points to head's next node so that we can release the memory of head node 
	free(head_ref);
	cnt++;
	while(curr != head_ref) {
		temp = curr->pnext;
		free(curr);
		cnt++;
		curr = temp;
	}
    printf("---[%d] node%s that %s head node had been released---\n", cnt, (cnt<=1)?"":"s", (cnt<=1)?"is":"contain");
    return cnt;*/
	uint cnt = 0;
	lnode *curr = NULL, *temp = NULL;
	if (NULL == *head_ref)
	{
		printf("Cannot delete list ! list is empty\n");
		return 0;
	}
	// delete first node standalone
	curr = (*head_ref)->pnext;
	free(*head_ref);
	cnt++;
	// delete remaining nodes of list
	while(curr != *head_ref) {
		temp = curr->pnext;
		free(curr);
		cnt++;
		curr = temp;
	}
	*head_ref = NULL;
    // printf("---[%d] node%s that %s head node had successfully been released---\n", cnt, (cnt<=1)?"":"s", (cnt<=1)?"is":"contain");
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

bool IsEmpty(lnode const *head_ptr) 
{
	if((NULL == head_ptr) || (head_ptr->pnext == head_ptr)) {
		return true;
	}
	return false;	
}

void printDetails(lnode const *head_ptr)
{
	lnode *worker = NULL;
	lnode *temp = NULL;
	uint i = 1;	
	if (IsEmpty(head_ptr) == true)
	{
		printf("Cannot print ! list is empty\n");
		return;
	}
	worker = head_ptr->pnext;
	// printf("list head at: %p\n", head_ptr);
	while(worker != head_ptr) {
		temp = worker->pnext;
		printf("element[%d] at [%p]---[data]: %d\t---[pnext]: %p\n", i, worker, worker->data, worker->pnext);
		i++;
		worker = temp;
	}
}

void printBrief(lnode const *head_ptr)
{
	lnode *worker = NULL;
	uint i = 1;
	if(IsEmpty(head_ptr) == true)
	{
		printf("list is empty\n");
		return;
	}
	worker = head_ptr->pnext;
	// printf("[head:%d;%p]->", head_ptr->data, head_ptr->pnext);
	printf("[head:%d]->", head_ptr->data);	
	while(worker != head_ptr) {
		// printf("[node:%d;%p]", worker->data, worker->pnext);
		printf("[node:%d]->", worker->data);
		i++;
		worker = worker->pnext;
		if(i%6 == 0) {
			printf("\n");
		}
	}
	printf("[head:%d]\n", head_ptr->data);
}

lnode* getTail(lnode *head_ptr)
{
	lnode *worker = head_ptr;
	while(head_ptr != worker->pnext) {
		worker = worker->pnext;
	}
	return worker;
}

lnode* getPrev(lnode *head_ptr, lnode *node)
{
	lnode *worker = head_ptr;
	while(head_ptr != worker->pnext) {
		if(worker->pnext == node)
			break;
		worker = worker->pnext;
	}
	return worker;
}

// Search first match node and return that node
// @head_ptr list is to be searched
// @vlaue value is to be found
lnode* locate(lnode const *head_ptr, int const value, uint *index)
{
	lnode *worker = NULL;
	uint i = 2;
	if(NULL == head_ptr)
	{
		printf("list is empty\n");
		return worker;
	}
	worker = head_ptr->pnext;
	while(worker != head_ptr) {
		if(worker->data == value) {
			*index = i;
			break;			
		}
		worker = worker->pnext;
		i++;
	}
	return ((i >= 2) ? worker: NULL);
}

// Find first match node which data equals to oldvalue and change its data to newvalue
void setElement(lnode const *head_ref, int const oldvalue, int const newvalue)
{
	lnode *target = NULL;
	uint index = 2;
	target = locate(head_ref, oldvalue, &index);
	if (target) {
		target->data = newvalue;
	} else {
		printf("---cannot find %d---\n", oldvalue);
	}

}

// Append new element 'new_data' at list's tail
bool append(lnode *head_ptr, int const new_data)
{
	bool flag = false;
	lnode *last = NULL;
	if(NULL == head_ptr) {
		// printf("---list doesn't be created---\n");
		return flag;
	}
	lnode *newnode = newNode(new_data);
	last = getTail(head_ptr);
	newnode->pnext = last->pnext; // At this time, last has pointed to head node, so last->node == head_ptr
	last->pnext = newnode;
	head_ptr->data++; // change list's count
	return flag;
}

// Delete first match node which data field equals to value
bool removeElement(lnode *head_ptr, int const value)
{
	if (NULL == head_ptr) {
		return false;
	}
	lnode *worker = head_ptr;
	/* Go to the node for which the node next to it has to be deleted */
	while(worker->pnext != head_ptr && ((worker->pnext)->data != value)) {
		worker = worker->pnext;
	}
	if(worker->pnext == head_ptr || (worker->pnext)->data != value) {
		printf("Element %d is not present in the list\n",value);
		return false;
	}
	/* Now head_ptr points to a node and the node next to it has to be removeElementd */
	lnode *temp = NULL;
	temp = worker->pnext;
	/*temp points to the node which has to be removeElementd*/
	worker->pnext = temp->pnext;
	/*We remove the node which is next to the head_ptr (which is also temp) */
	free(temp);
	/* Beacuse we deleted the node, we no longer require the memory used for it . 
	free() will deallocate the memory.
	*/		
	return true;
}

int find(lnode *head_ptr, int key)
{
	int index = 0;
	lnode *start = head_ptr;
	lnode *worker = NULL;	
	worker = start->pnext; //First node is dummy node.
	/* Iterate through the entire linked list and search for the key. */
	while(worker != start) {
		if(worker->data == key) { //key is found.
			return index;
		}
		worker = worker->pnext;//Search in the next node.
		index++;
	}
	/*Key is not found */
	return -1;
}

int main(int argc, char const *argv[])
{
	lnode *circularlist = NULL;
	circularlist = createcircularlinkedlist();
	printBrief(circularlist);
	// printDetails(circularlist);
	append(circularlist, 111);
	append(circularlist, 66);
	append(circularlist, 888);
	setElement(circularlist, 66, 666);
	printBrief(circularlist);
    removeElement(circularlist, 888);
    if(find(circularlist, 109) < 0)
    	printf("Not found !\n");
    removeElement(circularlist, 109);
	printBrief(circularlist);
	// printDetails(circularlist);
	destroyList(&circularlist);
	printBrief(circularlist);
	// printDetails(circularlist);
	return 0;
}


