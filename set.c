// Matthew Tran
// Project 4 Week 2
// Utilizing Hash Tables, but generic

//Included libraries 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

// Setting up structure set. Calling it SET
typedef struct set{
    int length;
    int count;
    LIST **data;

    int (*compare)();
    unsigned(*hash)();
}SET;




// Creates the set and initializes the values
// Allocates memory for the size of LIST for the size alpha
// initializes the new functions that we are given
// O(n)
SET *createSet (int maxElts, int (*compare)(), unsigned(*hash)())
{
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp!= NULL);
    sp->length = maxElts/20;
    sp->count = 0;
    sp->data = malloc(sizeof(LIST*)*sp->length);
    assert(sp->data != NULL);

    assert(compare!= NULL);
    assert(hash!= NULL);

    sp->compare = compare;
    sp->hash = hash;

    int i;
    for(i=0; i<sp->length; i++)
    {
        sp->data[i] = createList(sp->compare);
    }

    return sp;
}

// Function to destroy the set
// Utilizes the destroyList function to free the lists in the array
// Then, frees the array and the set itself
// O(n^2) 
void destroySet(SET *sp)
{
    
    assert(sp!=NULL);
    assert(sp->data != NULL);
    
    
    int i;
    for(i=0; i<sp->length; i++)
    {
        destroyList(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}


// Returns the number of words in the data
// This is kept track of with count
// O(1)
int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}

// Add element function
// This will use the hash function to figure out which slot in
// the array to go, then put it in the linked list that is in that slot
// O(n)  
void addElement(SET *sp, void *elt) 
{
 
    assert(sp!=NULL);
    assert(elt!=NULL);

    int locn = (*sp->hash)(elt) % sp->length;

    if (findItem(sp->data[locn],elt) != NULL)
    {
        return;
    }
    addFirst(sp->data[locn], elt);
    sp->count++;
}

// Remove element function
// This will remove the elt in the parameter by looking at where it was hashed to,
// then looking for elt in the linked list. It removes it if it finds it
// O(n)
void removeElement(SET *sp, void *elt)
{
    assert(elt != NULL);
    assert(sp!=NULL);
    assert(sp->data != NULL);
    assert(sp->count > 0);

    int locn = (*sp->hash)(elt) % sp->length;
    

    if(findItem(sp->data[locn],elt)!= NULL)
    {  
        removeItem(sp->data[locn], elt);
        sp->count--;
    }
}

// Finds the element and returns it
// Uses search function to get the location of the element 
// If it is found, then it will return the string, but return NULL if not
// O(n)
void *findElement(SET *sp, void *elt)
{
    assert(elt != NULL);
    assert(sp!=NULL);
    assert(sp->data != NULL);
    
    int locn = (*sp->hash)(elt) % sp->length;

    
    return findItem(sp->data[locn], elt);
}


// Will getElements from each of the lists and put them into a 
// new array with all of the elts together using memcpy
// It will retturn the array with all of the elements
// O(n) according to Atkinson
void *getElements(SET *sp)
{
    assert(sp!=NULL);
    assert(sp->data != NULL);
    


   
    void **elts = malloc(sizeof(void*)*sp->count);
    assert(elts != NULL);
    
    int i =0;
    int j=0;
    while(j < sp->count && i<sp->length)
    {

        memcpy(elts+j,getItems(sp->data[i]),sizeof(void*)*numItems(sp->data[i]));
        j+= numItems(sp->data[i]);
        i++;
    }

    /*
    int i;
    int j;
    j=0;
    for(i=0;i<sp->length && j< sp->count;i++)
    {
         void *item = getItems(sp->data[i]);
         memcpy(elts+j,item,sizeof(void*)*numItems(sp->data[i]));
         j+= numItems(sp->data[i]);
    }
    */


    
    /*
    
    int i;
    for(i=0;i<sp->length;i++)
    {
        void **currElts;
        currElts = getItems(sp->data[i]);
        int size;
        size = numItems(sp->data[i]);
        int j;
        for(j =0; j< size;j++)
        {
            elts = currElts[(size*i)+j];
        }
    }
    return elts;
    */

    return elts;
}
