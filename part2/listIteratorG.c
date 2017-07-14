/*
  listIteratorG.c ... Generic List Iterator implementation
  Written by Daniel Brockwell, z5116823
  Date: 07/04/17
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorG.h"

#define SPACESIZE 1 

#define CAN_SETDEL 1 // this determines whether findnext, findpref, *next or *prev has been called directly before
#define CANNOT_SETDEL 0

#define SUCCESS 1
#define NO_SUCCESS 0

#define NOT_FOUND 0
#define FOUND 1

#define THE_MARK_YOU_SHOULD_GIVE_ME 10

typedef struct Node {
	void *val;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct IteratorGRep {
	int nitems;  
	Node *first;
	Node *last;
    Node *prev;
    Node *next;
    Node *setdel;
    ElmFreeFp free;
    ElmCopyFp copy;
    ElmCompareFp cmp;

} IteratorGRep;

// int printVals (IteratorG it);




// HOLY SHIT I STARTED THIS AT 8:30PM BLESS UP FAM
IteratorG IteratorGNew(ElmCompareFp cmp, ElmCopyFp copy, ElmFreeFp free){ // Wait Stephen, what's a cursor
    IteratorG it = malloc(sizeof(IteratorGRep));
    assert(it != NULL);
    it->first = NULL;
    it->last = NULL;
    it->prev = NULL;
    it->next = NULL;
    it->setdel = NULL;
    it->nitems = 0;
    it->free = free;
    it->copy = copy;
    it->cmp = cmp;
    return it;
}

void reset(IteratorG it){
    it->prev = NULL; // set cursor to be here: --> ^ <-- Element 0 _ Element1 _ Element2... (before first element)
    it->next = it->first;
}


int add(IteratorG it, void *vp){
    
    struct Node *newnode = malloc(sizeof(Node));
    assert(newnode != NULL);

    int successcheck = NO_SUCCESS; // 0 means unsuccessful, becomes 1 when function works
    it->setdel = NULL;

    newnode->val = it->copy(vp);

 
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


int hasNext(IteratorG it){
    it->setdel = NULL;
  if (it->next == NULL){ // if there's no node after the current node
  	return 0;
  } else {
  	return 1;
  } 
}


// CHANGE 

int hasPrevious(IteratorG it){
    it->setdel = NULL;
   if (it->prev == NULL){ // if there's no node after the current node 
  	return 0;
  } else {
  	return 1;
  } 
}


void *next(IteratorG it){
    if (it->next == NULL) {
        return NULL;
    } else {
  	// Cursor shifted right by the first two
        it->prev = it->next;
        it->next = it->next->next;
        it->setdel = it->prev; // because the 'curr' is to the left of the cursor 
        return it->prev->val;
  }
}

void *previous(IteratorG it){
    if (it->prev == NULL) {
  	    return NULL;
    } else {
  	    it->next = it->prev;
        it->prev = it->prev->prev; // Cursor shifted left by these two commands
        it->setdel = it->next; // because the 'curr' is  to the left of the cursor
        return it->next->val; // return the pointer to the new current value
    }	
}


int delete(IteratorG it){
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
        it->free(it->setdel->val);
        free(it->setdel);
        it->setdel = NULL;
        return 1;

    }

}



int set(IteratorG it, void *vp){

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
        it->free(it->setdel->val);
        it->setdel->val = it->copy(vp);
        return 1;

    }
}

void *findNext(IteratorG it, void *vp){
    it->setdel = NULL;
    int found = NOT_FOUND;
    Node *ntemp = it->next;
    while (found != FOUND && ntemp->next != NULL) {


        if (it->cmp(ntemp->val, vp)){
            found = FOUND;
           }
        ntemp = ntemp->next;

    }

    if (found == FOUND) {
        it->setdel = ntemp;
        it->prev = ntemp;
        it->next = ntemp->next;
        return it->prev->val; // given prev has been shifted one along, 
        // the cursor sits to the right of the next value
        // and hence the prev from the cursor is what was 'next' beforehand
    } else {
        return NULL;;
    }
}

void *findPrevious(IteratorG it, void *vp){
    int found = NOT_FOUND;
    Node *ptemp = it->prev;
    while (found != FOUND && ptemp->prev != NULL) {

        if (it->cmp(ptemp->val, vp)) {
            found = FOUND;
           }
        ptemp = ptemp->prev;
    }

    if (found == FOUND) {
        it->setdel = ptemp;
        it->prev = ptemp->prev;
        it->next = ptemp;
        return it->next->val; // given prev has been shifted one along, 
        // the cursor sits to the right of the next value
        // and hence the prev from the cursor is what was 'next' beforehand
    } else {
        return NULL;;
    }
}

/*

int printVals(IteratorG it) {

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
/
    return 0;

}

*/
