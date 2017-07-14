/*
  client to test listIteratorInt.
  Written by ....
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorInt.h"

int printNums(IteratorInt it);

int main(int argc, char *argv[])

{
    struct IteratorIntRep *it = IteratorIntNew();
	
    printf("Add 20\n");
    assert(add(it, 20) == 1);
    printNums(it);

	printf("Add 12\n");
    assert(add(it, 12) == 1);
    printNums(it);

    printf("Has next\n");
	assert(hasNext(it) == 0);
    printNums(it);

	printf("Add 33\n");
	assert(add(it, 33) == 1);
    printNums(it);

	printf("Add 25\n");
	assert(add(it, 25) == 1);
    printNums(it); 

    printf("Go previous\n");
	assert(*previous(it) == 25);
    printNums(it); 
    
    printf("Go previous\n");
	assert(*previous(it) == 33);
    printNums(it);

    printf("Go next\n");
	assert(*next(it) == 33);
        printNums(it);

    printf("Delete\n");
	assert(delete(it) == 1);
    printNums(it);


     printf("Go previous\n");
	assert(*previous(it) == 12);
    printNums(it);


    printf("Delete\n");
	assert(delete(it) == 1);
    printNums(it);


	
     printf("Go previous\n");
    assert(*previous(it) == 20);
    printNums(it);
 
  printf("Delete\n");
	assert(delete(it) == 1);
    printNums(it);

         printf("Has previous\n");
	assert(hasPrevious(it) == 0);
       printNums(it);
   
	
     
    printf("Go next\n");
       assert(*next(it) == 25);
   printNums(it);



  printf("Delete\n");

	assert(delete(it) == 1);
   printNums(it);



	assert(add(it, 55) == 1);
   printNums(it);
   
	assert(add(it, 29) == 1);
  printNums(it);


printf("Reset\n");
	reset(it);
  printNums(it);
    
    printf("Go next\n");  
	assert(*next(it) == 55);
   printNums(it);




	assert(add(it, 62) == 1);

    printf("Has previous\n");
	assert(hasPrevious(it) == 1);
   printNums(it);

   printf("Inserting 44\n");
   assert(add(it, 44) == 1);
   printNums(it);


   printf("GGGGGo previous\n");

   assert(*previous(it) == 44);


   printf("Go next\n");
   assert(*next(it) == 44);


   printf("Delete\n");

   assert(delete(it) == 1);


   printf("Go previous\n");

   assert(*previous(it) == 62);



   printf("Go next\n");
   assert(*next(it) == 62);

   printf("Delete\n");

   assert(delete(it) == 1);


   printf("Delete\n");

   assert(delete(it) == 0);



   printf("Go next\n");
   assert(*next(it) == 29);

   printf("Delete\n");

   assert(delete(it) == 1);

   printf("Go previous\n");

   assert(*previous(it) == 55);

   printf("Delete\n");

   assert(delete(it) == 1);

   printf("Has next\n");
   assert(hasNext(it) == 0);


   printf("NICE ONE YA DRONGO\n");

   return EXIT_SUCCESS;

}


