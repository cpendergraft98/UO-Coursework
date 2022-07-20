/* 
CIS 314 Project 4, Part 4
Author: Cole Pendergraft

Credit to Liam Bhakta for helping me greatly with this part, I was
very confused by it and wouldn't have been able to figure it out without
his assistance.
*/

#include <stdio.h>
#include <stdlib.h>

/* 
Optimized x86-64 inner loop code:

.L10:
	movq (%rax), %rcx		# %rcx = *(%rax)
											# In terms of original: long t1 = a[i][j]
											# Stores value pointed to by %rax in %rcx
											# %rax stores p2
											# %rcx now stores value pointed to by p2
											
	movq (%rdx), %rsi		# %rsi = *(%rdx)
											# In terms of original: long t2 = a[i][j]
											# In terms of optimized code: temp = *p1
											# store value pointed to by %rdx in %rsi
											# tells me I need at least 1 pointers and a temp variable
											# %rsi stores tem
											# (%rdx) stores p1

	movq %rsi, (%rax)		# *(%rax) = %rsi
											# In terms of original: a[i][j] = t2
											# In terms of optimized code: *p2 = temp
											# set value %rax points to to value stored in %rsi
											# value stored in %rsi is the value pointed to by %rdx
											# tells me I need at least 2 pointers and a temp variable
											# %rsi stores temp
											# (%rax) stores p2

	movq %rcx, (%rdx)		# *(%rdx) = %rcx 
											# In terms of original: a[j][i] = t1
											# In terms of optimized code: *p1 = *p2
											# set value %rdx points to to value stored in %rcx
											# value stored in %rcx is the value pointed to by %rax
											# which is the value pointed to by p2.

	// At this point, the values stored in our two original pointers have been swapped

	addq $8, %rax				# Shifts to the next row element
											# %rax += 8
											# In terms of original code: a[i][++j] (Incremented row position)
											# In terms of optimized code: p1 += 1

	addq $32, %rdx			# Shifts to the next column element
											# %rdx += 32
											# In terms of original code: a[++i][j] (Incremented column position)
											# In terms of optimized code: p2 += N

	cmpq %r9, %rax			# Checks that j < i
	jne .L10
*/

#define N 4
typedef long array_t[N][N];

void transpose(array_t a){
	// Transposing an array swaps rows with columns

	long *p1, *p2; // Determined we need 2 pointers from x86-64 code

	for(long i = 0; i < N; ++i){
		p1 = &a[i][0];
		p2 = &a[0][i];
		for(long j = 0; j < i; ++j){
			long temp;  // Initialize temp variable
			temp = *p1;	// Store value pointed to by p1 in temp (  movq (%rdx), %rsi )
			*p1 = *p2;		// Store value pointed to by p2 in p1 ( movq %rcx, (%rdx) )
			*p2 = temp;		// Set value stored in p2 to the value stored in temp ( movq %rsi, (%rax) )
			p1 += 1;			// Increment to the next row position ( addq $8, %rax )
			p2 += N;			// Increment to the next column position ( addq $32, %rdx )
		}
	}
}

int main(){
	printf("=Test 1=\n");
	printf("Input array: {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}\n");
	array_t a = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	transpose(a);

	for(long i = 0; i< N; i++){	// I wasn't particularly concerned with making a really nice
												// function to print terms of the array in some formatted way,  
												// that seems secondary compared to the rest of the work, so I
												// just made a very simple print loop so I could check that my
												// outputs match the expect.
		for(long j = 0; j < N; j++){
			printf("%ld\n", a[i][j]);
		}
	}
	return 0;
}
