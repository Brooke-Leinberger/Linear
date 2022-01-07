#include "vector.h"
#include "matrix.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// Simple boolean assert function for unit testing (Taken from Larry Kiser's SWEN 250 class in Fall 2021)
int assert( int test_result, char error_format[], ... ) {
         va_list arguments ;
         static int test_number = 1 ;
         int result = 1 ;        // return 1 for test passed or 0 if failed

         if ( ! test_result ) {
                 va_start( arguments, error_format ) ;
                 printf( "Test # %d failed: ", test_number ) ;
                 vprintf( error_format, arguments ) ;
                 printf( "\n" ) ;
                 result = 0 ;
         }
         test_number++ ;
         return result ;
}


int test()
{
	int passcount = 0, failcount = 0;

	printf("\nVector Testing.............\n");
	//Vectors

	//expected behavior
	double* coord = malloc(3 * sizeof(double));
	vector* x = NULL;
	vector* y = NULL;
	vector* z = NULL;

	coord[0] = 1;
	coord[1] = 0;
	coord[2] = 0;

	x = create_vector(3, coord, NULL);

	assert(x != NULL, "Expected x to not be NULL because a vector was created") ? passcount++ : failcount++;
	assert(x->elements[0] == 1, "Expected X component (0th element) to equal 1") ? passcount++ : failcount++;
	assert(x->elements[1] == 0, "Expected Y component (1st element) to equal 0") ? passcount++ : failcount++;
	assert(x->elements[2] == 0, "Expected Z component (2nd element) to equal 0") ? passcount++ : failcount++;

	coord[0] = 0;
	coord[1] = 1;
	coord[2] = 0;

	y = create_vector(3, coord, NULL);

	assert(y != NULL, "Expected y to not be NULL because a vector was created") ? passcount++ : failcount++;
	assert(y->elements[0] == 0, "Expected X component (0th element) to equal 0") ? passcount++ : failcount++;
	assert(y->elements[1] == 1, "Expected Y component (1st element) to equal 1") ? passcount++ : failcount++;
	assert(y->elements[2] == 0, "Expected Z component (2nd element) to equal 0") ? passcount++ : failcount++;

	assert(dot_product(x,y) == 0, "Expected dot product of x and y to be 0, since they are perpendicular") ? passcount++ : failcount++;
	assert(dot_product(x,x) == 1, "Expected dot product of x and x to be 1, since 1 = 1^2") ? passcount++ : failcount++;

	z = cross_product(x,y,NULL);

	assert(z != NULL, "Expected z to not be NULL because a vector was created") ? passcount++ : failcount++;
	assert(z->elements[0] == 0, "Expected X component (0th element) to equal 0") ? passcount++ : failcount++;
	assert(z->elements[1] == 0, "Expected Y component (1st element) to equal 0") ? passcount++ : failcount++;
	assert(z->elements[2] == 1, "Expected Z component (2nd element) to equal 1") ? passcount++ : failcount++;

	vector* w = create_vector(3, NULL, NULL);
	assert(w != NULL, "Expected z to not be NULL because a vector was created") ? passcount++ : failcount++;
	assert(w->elements[0] == 0, "Expected X component (0th element) to equal 0") ? passcount++ : failcount++;
	assert(w->elements[1] == 0, "Expected Y component (1st element) to equal 0") ? passcount++ : failcount++;
	assert(w->elements[2] == 0, "Expected Z component (2nd element) to equal 0") ? passcount++ : failcount++;

	coord[0] = 1;
	coord[1] = 1;
	coord[2] = 1;

	vector* v = create_vector(3, coord, w);
	assert(v != NULL, "Expected z to not be NULL because a vector was created") ? passcount++ : failcount++;
	assert(w == v, "Expected w to equal v because w was set as the dest argument") ? passcount++ : failcount++;
	assert(w->elements[0] == 1, "Expected X component (0th element) to equal 1") ? passcount++ : failcount++;
	assert(w->elements[1] == 1, "Expected Y component (1st element) to equal 1") ? passcount++ : failcount++;
	assert(w->elements[2] == 1, "Expected Z component (2nd element) to equal 1") ? passcount++ : failcount++;

	//idiot-proofing

	coord[0] = 1;
	coord[1] = 0;
	coord[2] = 0;

	x = create_vector(0, coord, NULL);
	assert(x == NULL, "Expected x to be NULL because count was 0 (count<1)") ? passcount++ : failcount++;

	x = create_vector(-2, coord, NULL);
	assert(x == NULL, "Expected x to be NULL because count was -2 (count<1)") ? passcount++ : failcount++;

	assert(free_vector(NULL) == 0, "Expected free_vector to return zero because its input was NULL") ? passcount++ : failcount++;

	//freeing
	free_vector(w);
	free_vector(x);
	free_vector(y);
	free_vector(z);
	free(coord);

	printf("%d passed\n%d failed\n", passcount, failcount);

	return 1;
}
