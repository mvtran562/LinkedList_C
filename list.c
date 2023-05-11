// Matthew Tran
// An Amazing Sort of Assignment
// Week 1

// All of the included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

// creating a structure for nodes
typedef struct node{
    void *data;
    struct node *prev;
    struct node *next;
}NODE;

// creating a structure for lists that will point to a dummy node
typedef struct list{
    int count;
    NODE *head;
    int (*compare)();
}LIST;

// create list function will initialize the list and dummy node
// O(1)
LIST *createList(int(*compare)())
{
    LIST *lp;
    lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    NODE *dummyNode;
    dummyNode = malloc(sizeof(NODE));
    assert(dummyNode != NULL);
    lp->head = dummyNode;
    lp->compare = compare;

    dummyNode->prev = dummyNode;
    dummyNode->next = dummyNode;
    return lp;
}

// search function
// given the list and the item you are looking for
// this will find the node that it is in and return the node
// while also changing the value of found accordingly
// O(n)
static NODE *search (LIST *lp, void *item,bool *found )
{
    
    assert(lp != NULL);
    assert(lp->compare != NULL);
    *found = false;
    NODE *currNode;
    currNode = lp->head->next;
    int i;
    for(i =0; i<lp->count;i++)
    {
        

        if( (*lp->compare)(currNode->data,item) == 0)
        {
            *found = true;
            return currNode;
        }
        currNode = currNode->next;
    }

    return NULL;
}

// the destroy list function will free the nodes in the list 
// until the count is 0 before freeing other elements
// O(n)
void destroyList(LIST *lp)
{
    assert(lp != NULL);
    
    while(lp->count>0)
    {
        removeFirst(lp);

    }
    free(lp->head);
    free(lp);

}

// The num items function will return the count, which shows
// how many items are in the list
// O(1)
int numItems(LIST *lp)
{
    assert(lp != NULL);
    return lp->count;
}

// The add first function will add the item at the front of the list by
// moving around pointers
// O(1)
void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL);
    NODE *newNode;
    newNode = malloc(sizeof(NODE));
    assert(newNode != NULL);
    newNode->data = item;

    
    newNode->prev = lp->head;
    
    newNode->next = lp->head->next;
    newNode->next->prev = newNode;

    lp->head->next = newNode;
    lp->count++;
}

// The add last function will add the item to the back of the list by moving
// around the pointers
// O(1)
void addLast(LIST *lp, void *item)
{
    assert(lp != NULL);
    NODE *newNode;
    newNode = malloc(sizeof(NODE));
    assert(newNode != NULL);
    newNode->data = item;

    
    newNode->prev = lp->head->prev;
    
    newNode->next = lp->head;

    newNode->prev->next = newNode;
    lp->head->prev = newNode;
    lp->count++;
}

// This will remove the first element in a list by moving around pointers then freeing
// O(1)
void *removeFirst(LIST *lp)
{
    assert(lp->count >0);
    NODE *tempNode;
    tempNode = malloc(sizeof(NODE));
    assert(tempNode != NULL);
    assert(lp->head->next != NULL);
    tempNode = lp->head->next;

    lp->head->next = tempNode->next;
    
    tempNode->next->prev = lp->head;

    void *returnVal = tempNode->data;

    free(tempNode);
    lp->count--;
    return returnVal;
    
}
// This will remove the last element in a list by moving around pointers then freeing
// O(1)
void *removeLast(LIST *lp)
{
    assert(lp->count >0);
    NODE *tempNode;
    tempNode = malloc(sizeof(NODE));
    assert(tempNode != NULL);
    
    tempNode = lp->head->prev;

    tempNode->prev->next = lp->head;
    lp->head->prev = tempNode->prev;

    void *returnVal = tempNode->data;

    free(tempNode);
    lp->count--;
    return returnVal;
    
}

// This will return the data of the first element in the list after the 
// dummy node
// O(1)
void *getFirst(LIST *lp)
{
    assert(lp != NULL);
    return lp->head->next->data;
}

// This will return the data of the last element in the list before the 
// dummy node
// O(1)
void *getLast(LIST *lp)
{
    assert(lp != NULL);
    return lp->head->prev->data;
}

// This will remove the specified item by searching for it and 
// freeing it while also moving pointers around
// O(n)
void removeItem(LIST *lp, void *item)
{
    assert(lp != NULL);
    NODE *tempNode;
    bool found;
    tempNode = search(lp,item,&found);
    if (found)
    {
        tempNode->prev->next = tempNode->next;
        tempNode->next->prev = tempNode->prev;
        free(tempNode);
        lp->count--;
    }

}

// This will find the node with the item 
// in the parameter in the list and return the item in it
// O(n)
void *findItem(LIST *lp, void *item)
{
    assert(lp != NULL);
    NODE *tempNode;
    bool found;
    tempNode = search(lp,item,&found);
    if (found)
    {
        return tempNode->data;
    }
    return NULL;
}

// This will get the items from the linked list and put them all
// into an array that is returned
// O(n)
void *getItems(LIST *lp)
{
    assert(lp != NULL);
    void **cpy;
    cpy = malloc(sizeof(void*) * lp->count);
    assert(cpy != NULL);
    NODE *tempNode;
    tempNode = lp->head->next;
    int i;
    for (i=0; i<lp->count;i++)
    {
        cpy[i]=tempNode->data;
        tempNode = tempNode->next;
    }
    return cpy;
}
