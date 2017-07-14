/*
  listIteratorInt.c ... list Iterator ADT implementation
  Written by Daniel Brockwell, z5116823
  Date: 07/04/17
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorInt.h"

#define SPACESIZE 1 

#define CAN_SETDEL 1 // this determines whether findnext, findpref, *next or *prev has been called directly before
#define CANNOT_SETDEL 0

#define SUCCESS 1
#define NO_SUCCESS 0

#define NOT_FOUND 0
#define FOUND 1

#define THE_MARK_YOU_SHOULD_GIVE_ME 10

typedef struct Node {
	int val;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct IteratorIntRep {
	int nitems;  
	Node *first;
	Node *last;
    Node *prev;
    Node *next;
    Node *setdel;
} IteratorIntRep;

int printNums(IteratorInt it);


IteratorInt IteratorIntNew(){ // Wait Stephen, what's a cursor

    IteratorInt it = malloc(sizeof(IteratorIntRep));
    assert(it != NULL);
    it->first = NULL;
    it->last = NULL;
    it->prev = NULL;
    it->next = NULL;
    it->setdel = NULL;
    it->nitems = 0;
    return it;
}

void reset(IteratorInt it){

    if (it == NULL) {
        printf("The it node is null.\n");
    } else if (it->nitems == 0){
        printf("No items in list.\n");
    } else if (it->prev == it->first) {
        printf("Already first.\n");
    } else {
        it->prev = NULL; // set cursor to be here: --> ^ <-- Element 0 _ Element1 _ Element2... (before first element)
        it->next = it->first;
    }
}


int add(IteratorInt it, int v){
    
    struct Node *newnode = malloc(sizeof(Node));
    assert(newnode != NULL);

    int successcheck = NO_SUCCESS; // 0 means unsuccessful, becomes 1 when function works
    it->setdel = NULL;

    newnode->val = v;
 
    if (it->nitems == 0) // No other nodes 
    {
        it->first = newnode;
  	    it->last = newnode;
        it->next = NULL;
        it->prev = newnode;
  	    newnode->next = NULL;
  	    newnode->prev = NULL;
    } 
    else if (it->prev == NULL) // Insert at beginning
    {
        newnode->next = it->next;
        it->first->prev = newnode;
        newnode->prev = NULL;
        it->first = newnode;
        it->next = newnode->next;
        it->prev = newnode;

    } 
    else if (it->next == NULL) // Insert at end
    {
        newnode->prev = it->last;  // prev from newnode is the current last node
        it->last->next = newnode;
        newnode->next = NULL;
        it->last = newnode;
        it->next = newnode->next;
        it->prev = newnode;

    } else { // Insert somewhere in middle
        newnode->prev = it->prev;
        newnode->next = it->next;
        it->prev = newnode;
        it->next = newnode->next;
    }   
    successcheck = SUCCESS; // node has been added
    it->nitems++;
    return successcheck;
}


int hasNext(IteratorInt it){
    it->setdel = NULL;
  if (it->next == NULL){ // if there's no node after the current node
  	return 0;
  } else {
  	return 1;
  } 
}


// CHANGE 

int hasPrevious(IteratorInt it){
    it->setdel = NULL;
   if (it->prev == NULL){ // if there's no node after the current node 
  	return 0;
  } else {
  	return 1;
  } 
}


int *next(IteratorInt it){
    if (it->next == NULL) {
        return NULL;
    } else {
  	// Cursor shifted right by the first two
        it->prev = it->next;
        it->next = it->next->next;
        it->setdel = it->prev; // because the 'curr' is to the left of the cursor 
        return &(it->prev->val);
  }
}

int *previous(IteratorInt it){
    if (it->prev == NULL) {
  	    return NULL;
    } else {
  	    it->next = it->prev;
        it->prev = it->prev->prev; // Cursor shifted left by these two commands
        it->setdel = it->next; // because the 'curr' is  to the left of the cursor
        return &(it->next->val); // return the pointer to the new current value
    }	
}


int delete(IteratorInt it){
    if (it->setdel == NULL || it->nitems == 0) 
    // If there hasn't been a prev/next/findprev/findnext call immediately before this OR
    // If there aren't any items in the list OR
    // If no node has been selected for the deletion
    { 
        if (it->setdel  == NULL) {
            printf("Can't call delete.\n");
        } else {
            printf("No items in list to delete.\n");
        }
        return 0;
    } 
    else 
    { 
        if (it->nitems == 1)
        {
            it->first = NULL;
            it->last = NULL;
            it->next = NULL;
            it->prev = NULL;
        } 
        else if (it->setdel == it->first)
        {
            it->first = it->first->next;
            it->first->prev = NULL;

            it->next = it->first;
            it->prev = NULL; // These two adjust the cursor
        } 
        else if (it->setdel == it->last) 
        {
            it->last = it->last->prev;
            it->last->next = NULL;

            it->next = NULL;
            it->prev = it->last; // These two adjust the cursor

        } else if (it->setdel == it->next){
            it->setdel->next->prev = it->setdel->prev;
            it->setdel->prev->next = it->setdel->next;

            it->next = it->next->next;// Adjust cursor 

        } else if (it->setdel == it->prev) {

            it->setdel->next->prev = it->setdel->prev;
            it->setdel->prev->next = it->setdel->next;

            it->prev = it->prev->prev; // Adjust cursor

        }

          
        it->nitems--;
        free(it->setdel);
        it->setdel = NULL;
        return 1;

    }

}



int set(IteratorInt it, int v){

    if (it->setdel == NULL || it->nitems == 0) 
    // If there hasn't been a prev/next/findprev/findnext call immediately before this OR
    // If there aren't any items in the list OR
    // If no node has been selected for the deletion
    { 
        if (it->setdel == NULL) {
            printf("Can't call set.\n");
        } else if (it->nitems == 0) {
            printf("No items in list to delete.\n");
        } else {
            printf("Setdel node is null.\n");
        }
        return 0;
    } 
else 
    { 
        it->setdel->val = v;
        return 1;

    }
}

int *findNext(IteratorInt it, int v){
    it->setdel = NULL;
    int found = NOT_FOUND;
    Node *ntemp = it->next;
    while (found != FOUND && ntemp->next != NULL) {

        if (ntemp->val == v) {
            found = FOUND;
           }
        ntemp = ntemp->next;

    }

    if (found == FOUND) {
        it->setdel = ntemp;
        it->prev = ntemp;
        it->next = ntemp->next;
        return &(it->prev->val); // given prev has been shifted one along, 
        // the cursor sits to the right of the next value
        // and hence the prev from the cursor is what was 'next' beforehand
    } else {
        return NULL;;
    }
}

int *findPrevious(IteratorInt it, int v){
    int found = NOT_FOUND;
    Node *ptemp = it->prev;
    while (found != FOUND && ptemp->prev != NULL) {

        if (ptemp->val == v) {
            found = FOUND;
           }
        ptemp = ptemp->prev;
    }

    if (found == FOUND) {
        it->setdel = ptemp;
        it->prev = ptemp->prev;
        it->next = ptemp;
        printf("%d is the return value.\n", it->next->val);
        return &(it->next->val); // given prev has been shifted one along, 
        // the cursor sits to the right of the next value
        // and hence the prev from the cursor is what was 'next' beforehand
    } else {
        return NULL;;
    }
}



int printNums(IteratorInt it) {

    if (it->prev != NULL) {
        printf("Previous is %d\n", it->prev->val);
    } else {
        printf("Prev is null\n");
    }

    if (it->next != NULL) {
    printf("Next is %d\n", it->next->val);
    } else {
        printf("Next is null\n");
    }

    if (it->setdel != NULL) {
        printf("Setdel is %d\n", it->setdel->val);
    } else {
        printf("Setdel is null\n");
    }
    printf("X <-");
    Node *cur;
    for (cur = it->first; cur != NULL; cur = cur->next) {
        printf(" %d ",cur->val);
        if (cur->next == it->next) printf("<^>");
        else printf("<->");
    }
    printf("X\n");

    return 0;

}
