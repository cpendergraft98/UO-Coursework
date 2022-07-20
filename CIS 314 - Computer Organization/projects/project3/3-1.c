// CIS 314 Project 3, Part 1
// Author: Cole Pendergraft
//
// SOURCE CITATIONS:
//
// Used to help me better understand struct:
// tutorialspoint.com/cprogramming/c_structures.htm
// 
// Refresher on pointers:
// tutorialspoint.com/cprogramming/c_pointers.htm
//
// Understanding strtol:
// tutorialspoint.com/cprogramming/c_function_strtol.htm
//
// Understanding Bubblesort:
// geeksforgeeks.org/bubble-sort/
//

#include <stdio.h>
#include <stdlib.h>

struct IntArray{
	int length;
	int *dataPtr;
};

struct IntArray* mallocIntArray(int length){
	int *vals = NULL;

	// Here we create and initialize a pointer to our IntArray instance,
	// and allocate a memory amount equivalent to the size of the 
	// IntArray structure.
	struct IntArray* initArray = (struct IntArray *)malloc(sizeof(struct IntArray));

	// This is us creating our pointer to the int array, we want to allocate a memory
	// amount equivalent to the how many ints we have in our array, so we take
	// the size of a single int and multiply it by the number of ints we have in the
	// array
	vals = (int *)malloc(sizeof(int) * length);

	// We want to store our int array values in the dataPtr
	initArray -> dataPtr = vals;
	// And keep track of the expected array length
	initArray -> length = length;

	// Now we have created our IntArray instanc, set the associated dataPtr
	// to look at the vals in the array, and established the length of said 
	// array, so we return our new IntArray instance that I have called 
	// initArray.
	return initArray;
}

void freeIntArray(struct IntArray *array){
	// First we free the dataPtr associated with our IntArray object, because
	// once we've freed the IntArray pointer we can no longer access this
	// data pointer
	free(array -> dataPtr);

	// Now we can free our actual instance
	free(array);
}

void readIntArray(struct IntArray *array){
	// We use char buf[BUFSIZ] so we have a variable buffer size.
	char buf[BUFSIZ];
	char *endptr = NULL;
	int val = 0;

	for(int i = 1; i <= array->length; i++){

		start:
		printf("Enter a value:");
		// Here we use fgets to grab the user input from stdin
		fgets(buf, sizeof buf, stdin);

		// We take that user input and convert it into a value that
		// we can store, strtol will make it a long int, but that's
		// fine because we can just cast to a regular int later. From what I 
		// understand about strtol, I believe it is able to differentiate 
		// numeric values and non numeric values, and non numeric 
		// characters are converted to 0, hence why the project spec 
		// details that we can only populate our array with 
		// values >0. If i'm not mistaken it also stores the non-numeric characters
		// in endptr as well.
		val = strtol(buf, &endptr, 10);

		// We need to make sure that our integers in the array
		// are nonnegative
		if(val <= 0){
			printf("Invalid input, only positive integers >0.\n");

			// If one is negative, we need to reissue the request to enter a value
			// without incrementing i or adding it to the array
			goto start;
		}

		// Populate the array with the integer values
		array->dataPtr[i] = val;
	}
}

void swap(int *xp, int *yp){
	// Temporary pointer to store the value of xp
	// by using *xp we are accessing the value stored
	// in xp
	int hold = *xp;

	// Swap values of xp with yp
	*xp = *yp;

	// Set yp = stored value.
	*yp = hold;
}

void sortIntArray(struct IntArray *array){
	int i, j;
	// We need to use a nested for loop here because we want
	// to compare every individual value to the rest
	for(i = 1; i < (array->length); i++){
		// The internal four loop checks if the value at position j is greater
		// than the value next to it. If it is, then those two values are swapped
		// If a swap occurs, the loop then iterates and effectively checks that
		// same value again against the one next to it. If j is not greater than j+1
		// then no swap occurs, and that value is left where it is. This is why we need
		// a nested loop, because we can only compare a value to the one immediately
		// next to it. For me, it's easiest to understand by looking at an example:
		// Assume we have [4, 2 , 5, 3]
		// On first iteration we check if 4 < 2, it is, so we swap
		// We now have [2, 4, 5, 3]
		// On second iteration we check if 4 > 5, it isn't so nothing happens
		// Third and final iteration we check if 5 > 3, it is so we swap
		// We now have [2, 4, 3, 5]
		// And now we see why we need the external for loop, if we were to
		// stop here the ordering would be wrong, because 4 > 3,
		// so we need to iterate through the array again to check if the values in
		// new positions have a neighbor to the right that is smaller.
		for(j = 1; j < (array->length); j++){
			if((array->dataPtr[j]) > (array->dataPtr[j+1])){
				swap(&(array->dataPtr[j]), &(array->dataPtr[j+1]));
			}
		}
	}
}

void printIntArray(struct IntArray *array){
	printf("[");
	for(int i = 1; i <= array->length; i++){

		// The only reason this if statement exists is to
		// make sure that the last element printed 
		// doesn't have a comma after it. It was very 
		// important to me that there was no comma
		// after the last element :)
		if(i != (array->length)){
			printf("%d,", array->dataPtr[i]);
		}else{
			printf("%d", array->dataPtr[i]);
		}
	}
	printf("]\n");
}

int main(){
	char buf[BUFSIZ];
	long length = 0;
	char *endptr = NULL;

	start:
	printf("Enter the desired array size:");
	// The logic here is the pretty close to the same as in readIntArray.
	// We prompt the user and grab the input from stdin
	fgets(buf, sizeof buf, stdin);

	// Convert that input to an integer value and store it in the 
	// length variable
	length = strtol(buf, &endptr, 10);

	// Test to make sure that the value we passed is positive and
	// nonzero
	if(length <= 0){
		printf("Invalid input, only positive intergers >0\n");

		// If the value is negative/zero, we want to notify the user
		// go to the top, prompt them again, and retest the value.
		goto start;
	}

	struct IntArray* array = mallocIntArray(length);
	readIntArray(array);
	sortIntArray(array);
	printIntArray(array);
	freeIntArray(array);
	return 0;
}
