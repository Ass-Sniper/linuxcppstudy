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

typedef enum boolean {true, false} bool;

typedef struct linkedListNode {
    int data; // if node is head node, this field represents list's count.
    struct linkedListNode *pnext;
} lnode;

// Create list head node and initlize it's data field to 1.
lnode* createlinkedlist()
{
    lnode *head = NULL;
    head = (lnode *)malloc(sizeof(lnode));
    head->data = 0;
    head->pnext = NULL;
    printf("---singly linked list has been created successfully---\n");   
    return head;	
}

// Release each node in list from head to tail on by one.
// @param head_ref is the target which is to be released.
int deleteList(lnode *head_ref)
{
	uint cnt = 0;
	lnode *currhead, *temp;
	currhead = head_ref;
	while(currhead) {
	    temp = currhead->pnext;
	    free(currhead);
	    cnt++;
	    currhead = temp;
	}
	head_ref = NULL; // head node's memory has been released, but its contents has not been cleared yet.
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


/*
	*a = (*a) * (*b);	*a = *a ^ *b;
	*b = (*a) / (*b);	*b = *a ^ *b;
	*a = (*a) / (*b);	*a = *a ^ *b
*/
void swap(int *left, int *right) 
{
	if(*left == *right)
		return;
	*left  = *left + *right;
	*right = *left - *right; // b = (a+b)-b
	*left  = *left - *right; // a = a-(a-b)
}

void printAllElements(lnode const *head_ref)
{
	lnode const *worker = NULL;
	uint i = 1;
	if((NULL == head_ref) || (NULL == head_ref->pnext))
	{
		printf("list is empty.\n");
		return;
	}
	worker = head_ref->pnext;
	// printf("list head at: %p\n", head_ref);
	while(worker && (i <= UINT_MAX)) {
		printf("element[%d] at [%p]---[data]: %d\t---[pnext]: %p\n", i, worker, worker->data, worker->pnext);
		i++;
		worker = worker->pnext;
	}

}

void printByGraphic(lnode const *head_ref)
{
	lnode const *worker = NULL;
	uint i = 1;
	if((NULL == head_ref) || (NULL == head_ref->pnext))
	{
		printf("list is empty\n");
		return;
	}
	worker = head_ref->pnext;
	// printf("[head:%d;%p]->", head_ref->data, head_ref->pnext);
	printf("[head:%d]->", head_ref->data);	
	while(worker && (i <= UINT_MAX)) {
		// printf("[node:%d;%p]", worker->data, worker->pnext);
		printf("[node:%d]", worker->data);
		if(worker->pnext) {
			printf("->");
		}
		i++;
		worker = worker->pnext;
		if((i%6 == 0) || (!worker)) {
			printf("\n");
		}
	}
}

void sortList(lnode *head_ref)
{
	lnode *left = NULL, *right = NULL;
	left = head_ref->pnext;
	right = left->pnext;
	// printByGraphic(head_ref);
	while(left) {
		while(right) {
				// printf("[currleft]:%d —— [currright]:%d\n", left->data, right->data);
			if(right->data > left->data) {
				// printf("[left]:%d <——> [right]:%d\n", left->data, right->data);
				// swap((int *)&(left->data), (int *)&(right->data));
				swap(&(left->data), &(right->data));
			}
					// printByGraphic(head_ref);
			right = right->pnext;
		}	
	   	right = head_ref->pnext;
	   	left = left->pnext;
	}
}

lnode* getTail(lnode *head_ref)
{
	lnode *worker = head_ref;
	while(NULL != worker->pnext) {
		worker = worker->pnext;
	}
	return worker;
}

lnode* getPrev(lnode *head_ref, lnode *node)
{
	lnode *worker = head_ref;
	while(NULL != worker->pnext) {
		if(worker->pnext == node)
			break;
		worker = worker->pnext;
	}
	return worker;
}

// Copy all nodes in head_from to head_to's tail on by one
void copyList(lnode const *head_from, lnode **head_to)
{
	lnode *worker_from = NULL, *worker_to = NULL, *newnode = NULL;
	if(NULL == head_from) {
		return;
	}
	if(NULL == *head_to) {
		*head_to = createlinkedlist(); // create head node
	}
	worker_from = (lnode *)head_from->pnext;
	worker_to = *head_to;
	while(worker_from) {
		newnode = newNode(worker_from->data);
	    worker_to->pnext = newnode;
	    (*head_to)->data++;
	    worker_from = worker_from->pnext;
	    worker_to = getTail(*head_to);
	}
}

// Concatenate result: head_to->head_from
void concatList(lnode **head_from, lnode **head_to)
{
	if(NULL == *head_from) {
		return;
	}
	if(NULL == (*head_from)->pnext) {
		return;
	}		
	if(NULL == *head_to) {
		*head_to = createlinkedlist(); // create head node
	}
	(*head_to)->pnext = (*head_from)->pnext;
	(*head_to)->data += (*head_from)->data;			
	(*head_from)->pnext = NULL;
	(*head_from)->data = 0;
}

// Search first match node and return that node
// @head_ref list is to be searched
// @vlaue value is to be found
lnode* findElement(lnode const *head_ref, int const value, uint *index)
{
	lnode *worker = NULL;
	uint i = 2;
	if(NULL == head_ref)
	{
		printf("list is empty\n");
		return worker;
	}
	worker = head_ref->pnext;
	while(worker && (i <= UINT_MAX)) {
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
	target = findElement(head_ref, oldvalue, &index);
	if (target) {
		target->data = newvalue;
	} else {
		printf("---cannot find %d---\n", oldvalue);
	}

}

// Append new element 'new_data' at list's tail
bool appendElement(lnode *head_ref, int const new_data)
{
	bool flag = false;
	lnode *worker = NULL;
	if(NULL == head_ref) {
		printf("---list is not created---\n");
		return flag;
	}
	lnode *newnode = newNode(new_data);
	worker = getTail(head_ref);
	worker->pnext = newnode;
	head_ref->data++; // change list's count
	return flag;
}

// prev->newnode->before(target)
bool insertBefore(lnode *head_ref, int const before, int const new_data)
{
	bool flag = false;
	lnode *target = NULL, *prev = NULL, *newnode = NULL;
	uint index = 0;
	target = findElement(head_ref, before, &index);	
	prev = getPrev(head_ref, target);
	newnode = newNode(new_data);
	newnode->pnext = target;
	prev->pnext = newnode;
	head_ref->data++;
	flag = true;
	return flag;
}

// after(target)->newnode->...
bool insertAfter(lnode *head_ref, int const after, int const new_data)
{
	bool flag = false;
	lnode *target = NULL, *newnode = NULL;
	uint index = 0;	
	target = findElement(head_ref, after, &index);
	newnode = newNode(new_data);
	newnode->pnext = target->pnext;
	target->pnext = newnode;
	head_ref->data++;
	flag = true;
	return flag;				
}

// Delete first match node which data field equals to value
bool deleteElement(lnode *head_ref, int const value)
{
	bool flag = false;
	lnode *target = NULL, *prev = NULL,*curr = NULL;
	uint i = 1;
	if(head_ref->data < 2) {
		return flag;
	}
	prev = head_ref;
	curr = prev->pnext;
	while(curr && (i <= UINT_MAX)) {
		if(curr->data == value) {
			target = curr;
			prev->pnext = target->pnext;
			free(target);
			head_ref->data--;
			flag = true;
			i++;		
			break;
		} else {
			if(NULL == curr->pnext) 
				break;
			curr = curr->pnext;
			prev = prev->pnext;
		}
	}		
	return flag;
}

int main(int argc, char const *argv[])
{
    lnode *list = NULL/*, *tail = NULL, *findnode = NULL*/;
    lnode *cplist = NULL;
    // int value_to_delete = 0;
    // uint index = 0;
    // lnode *testnode = NULL;
    list = createlinkedlist();
    // printf("list= %p; &list= %p; *(&list)= %p; sizeof(**(&list))= %d\n", list, &list, *(&list), sizeof(**(&list)));
    // printAllElements(list);
    appendElement(list, 222);
    appendElement(list, 111);
    // insertBefore(list, 111, 110);
    // insertAfter(list, 111, 112);
    appendElement(list, 888);
    appendElement(list, 555);
    appendElement(list, 101);
    setElement(list, 101, 109);
    // setElement(list, 999, 109); // not exist
    // printByGraphic(list);

/*    	printf("cplist before copying:\t");
    printByGraphic(cplist);
    	printf("list before sorting:\t");
    printByGraphic(list);
    copyList(list, &cplist);
    sortList(list);
        printf("cplist after copying:\t");
    printByGraphic(cplist);
    	printf("list after sorting:\t");
    printByGraphic(list);*/

    concatList(&list, &cplist);
        printf("cplist after concating:\t");
    printByGraphic(cplist);
    	printf("list after concating:\t");
    printByGraphic(list);


/*    printf("Please enter the search number: ");
    scanf("%d", &value_to_find);
    findnode = findElement(list, value_to_find, &index);
    if(NULL == findnode)
    {
    	printf("not found.\n");
    } else {
    	printf("search result: element[%d] at [%p]---[data]: %d\t---[pnext]: %p\n", index, findnode, findnode->data, findnode->pnext);
    }*/
/*	printf("Please enter the delete number: ");
    scanf("%d", &value_to_delete);
    if(true == deleteElement(list, value_to_delete)) {
    	printf("delete complete.\n");
    } else {
    	printf("not found.\n");
    }*/
    // testnode = getPrev(list, list->pnext->pnext);
    // printf("[data] = %d\n", testnode->data);
    // printf("(int *)&(list->data)= %p; *((int *)&(list->data))= %d;\n", (int *)&(list->data), *((int *)&(list->data)));
    // printAllElements(list);
    // printByGraphic(list);
    deleteList(list);
    deleteList(cplist);
    return 0;
}
