// Author: Cole Pendergraft

#include <stdio.h>
#include <stdlib.h>

int main(){
	char line[20];
	char *result = NULL;

	printf("Enter a number:");
	result = fgets(line, 20,  stdin);
	if(result == NULL) {
		printf("Invalid Input\n");
		return 0;
	}

	char *endptr = NULL;
	long count = 0;

	count = strtol(line, &endptr, 10);
	if(endptr == line){
		printf("Invalid Input\n");
		return 0;
	}
	int *numbers = NULL;
	numbers = (int *)malloc(sizeof(int) * count);

	int i = 0;
	for( ; i < count; i++){
		numbers[i] = i + 1;
		// Could also do *(numbers + i) = i + 1
	}

	for(i = 0; i < count; i++){
		printf("%d ", numbers[i]);
	}
	printf("\n");

	free(numbers);

	return 0;
}