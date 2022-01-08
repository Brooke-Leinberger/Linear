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


int test_vectors()
{
	int passcount = 0, failcount = 0;

	printf("\nVector Testing.............\n");
	//Vectors

	//expected behavior
	vector* comp = create_vector(3, NULL, NULL);
	vector* w = create_vector(3, NULL, NULL);
	vector* x = create_vector(3, NULL, NULL);
	x->elements[0] = 1;
	vector* y = create_vector(3, NULL, NULL);
	y->elements[1] = 1;
	vector* z = create_vector(3, NULL, NULL);
	z->elements[2] = 1;

	comp->elements[0] = 1;

	assert(x != NULL, "Expected x to not be NULL because a vector was created") ? passcount++ : failcount++;
	assert(x->elements[0] == 1, "Expected X component (0th element) to equal 1") ? passcount++ : failcount++;
	assert(x->elements[1] == 0, "Expected Y component (1st element) to equal 0") ? passcount++ : failcount++;
	assert(x->elements[2] == 0, "Expected Z component (2nd element) to equal 0") ? passcount++ : failcount++;
	assert(compare_vectors(x, comp) == 1, "Expected x to equal comp") ? passcount++ : failcount++;
	assert(compare_vectors(x, y) == 0, "Expected x to not equal y") ? passcount++ : failcount++;
	assert(compare_vectors(x, x) == -1, "Expected address of x to equal address of x") ? passcount++ : failcount++;

	comp->elements[0] = 0;
	comp->elements[1] = 1;

	assert(y != NULL, "Expected y to not be NULL because a vector was created") ? passcount++ : failcount++;
	assert(y->elements[0] == 0, "Expected X component (0th element) to equal 0") ? passcount++ : failcount++;
	assert(y->elements[1] == 1, "Expected Y component (1st element) to equal 1") ? passcount++ : failcount++;
	assert(y->elements[2] == 0, "Expected Z component (2nd element) to equal 0") ? passcount++ : failcount++;
	assert(compare_vectors(y, comp) == 1, "Expected y to equal comp") ? passcount++ : failcount++;
	assert(compare_vectors(y, x) == 0, "Expected y to not equal x") ? passcount++ : failcount++;
	assert(compare_vectors(y, y) == -1, "Expected address of y to equal address of y") ? passcount++ : failcount++;

	comp->elements[1] = 0;
	comp->elements[2] = 1;

	assert(dot_product(x,y) == 0, "Expected dot product of x and y to be 0, since they are perpendicular") ? passcount++ : failcount++;
	assert(dot_product(x,x) == 1, "Expected dot product of x and x to be 1, since 1 = 1^2") ? passcount++ : failcount++;

	cross_product(x, y, z);

	assert(z != NULL, "Expected z to not be NULL because a vector was created") ? passcount++ : failcount++;
	assert(z->elements[0] == 0, "Expected X component (0th element) to equal 0") ? passcount++ : failcount++;
	assert(z->elements[1] == 0, "Expected Y component (1st element) to equal 0") ? passcount++ : failcount++;
	assert(z->elements[2] == 1, "Expected Z component (2nd element) to equal 1") ? passcount++ : failcount++;
	assert(compare_vectors(z, comp) == 1, "Expected z to equal comp") ? passcount++ : failcount++;
	assert(compare_vectors(z, x) == 0, "Expected z to not equal x") ? passcount++ : failcount++;
	assert(compare_vectors(z, z) == -1, "Expected address of z to equal address of z") ? passcount++ : failcount++;

	comp->elements[2] = 0;

	assert(w != NULL, "Expected z to not be NULL because a vector was created") ? passcount++ : failcount++;
	assert(w->elements[0] == 0, "Expected X component (0th element) to equal 0") ? passcount++ : failcount++;
	assert(w->elements[1] == 0, "Expected Y component (1st element) to equal 0") ? passcount++ : failcount++;
	assert(w->elements[2] == 0, "Expected Z component (2nd element) to equal 0") ? passcount++ : failcount++;
	assert(compare_vectors(w, comp) == 1, "Expected w to equal comp") ? passcount++ : failcount++;
	assert(compare_vectors(w, y) == 0, "Expected w to not equal y") ? passcount++ : failcount++;
	assert(compare_vectors(w, w) == -1, "Expected address of w to equal address of w") ? passcount++ : failcount++;

	comp->elements[0] = 1;
	comp->elements[1] = 1;
	comp->elements[2] = 1;

	double* coord = read_vector(comp);
	vector* v = create_vector(3, coord, w);

	assert(v != NULL, "Expected z to not be NULL because a vector was created") ? passcount++ : failcount++;
	assert(v == w, "Expected w to equal v because w was set as the dest argument") ? passcount++ : failcount++;
	assert(v->elements[0] == 1, "Expected X component (0th element) to equal 1") ? passcount++ : failcount++;
	assert(v->elements[1] == 1, "Expected Y component (1st element) to equal 1") ? passcount++ : failcount++;
	assert(v->elements[2] == 1, "Expected Z component (2nd element) to equal 1") ? passcount++ : failcount++;
	assert(compare_vectors(v, comp) == 1, "Expected v to equal comp") ? passcount++ : failcount++;
	assert(compare_vectors(v, y) == 0, "Expected v to not equal y") ? passcount++ : failcount++;
	assert(compare_vectors(v, w) == -1, "Expected address of v to equal address of w") ? passcount++ : failcount++;

	//idiot-proofing

	coord[0] = 1;
	coord[1] = 0;
	coord[2] = 0;

	vector* i;

	i = create_vector(0, coord, NULL);
	assert(i == NULL, "Expected i to be NULL because count was 0 (count<1)") ? passcount++ : failcount++;

	i = create_vector(-2, coord, NULL);
	assert(i == NULL, "Expected i to be NULL because count was -2 (count<1)") ? passcount++ : failcount++;

	assert(free_vector(NULL) == 0, "Expected free_vector to return zero because its input was NULL") ? passcount++ : failcount++;

	//freeing
	free_vector(comp);
	free_vector(w);
	free_vector(x);
	free_vector(y);
	free_vector(z);
	free(coord);

	printf("%d passed\n%d failed\n", passcount, failcount);
	return 1;
}

int test_matricies()
{
	int passcount = 0, failcount = 0;
	printf("Testing Matricies...\n");

	dmatrix* identity = identity_matrix(3, 3, NULL);
	dmatrix* three_by_three = create_matrix(3, 3, NULL);

	assert( compare_matricies(three_by_three, identity) == 0, "Expected matricies to not be equal" ) ? passcount++ : failcount++;

	edit_location(three_by_three, 0, 0, 1.0);
	edit_location(three_by_three, 1, 1, 1.0);
	edit_location(three_by_three, 2, 2, 1.0);

	assert( compare_matricies(three_by_three, identity) == 1, "Expected matricies to be equal" ) ? passcount++ : failcount++;
	assert( compare_matricies(identity, identity) == -1, "Expected matricies to be equal references" ) ? passcount++ : failcount++;

	free_matrix(identity);



	vector *expected = NULL, *actual = NULL;
	create_matrix(3, 3, three_by_three);
	expected = create_vector(3, NULL, NULL);

	for(int i = 0; i < 9; i++)
		edit_location(three_by_three, i/3, i%3, i+1);

	expected->elements[0] = 1;
	expected->elements[1] = 2;
	expected->elements[2] = 3;
	actual = read_row(three_by_three, 0, NULL);
	assert( compare_vectors(actual, expected) == 1, "Expected first row to contain <1,2,3>" ) ? passcount++ : failcount++;

	expected->elements[0] = 1;
	expected->elements[1] = 4;
	expected->elements[2] = 7;
	read_col(three_by_three, 0, actual);
	assert( compare_vectors(actual, expected) == 1, "Expected first column to contain <1,4,7>" ) ? passcount++ : failcount++;

	//Freeing
	free_vector(actual);
	free_vector(expected);
	free_matrix(three_by_three);

	dmatrix* two_by_three = create_matrix(2, 3, NULL);
	dmatrix* three_by_two = create_matrix(3, 2, NULL);

	for(int i = 0; i < 6; i++)
	{
		edit_location(two_by_three, i/3, i%3, i+1);
		edit_location(three_by_two, i/2, i%2, i+7);
	}

	dmatrix* result = multiply_matricies(two_by_three, three_by_two, NULL);

	assert( result->rows == 2, "Expected result to have 2 rows" ) ? passcount++ : failcount++;
	assert( result->cols == 2, "Expected result to have 2 columns" ) ? passcount++ : failcount++;
	expected = create_vector(2, NULL, NULL);
	actual = create_vector(2, NULL, NULL);
	expected->elements[0] = 58;
	expected->elements[1] = 64;
	read_row(result, 0, actual);
	assert( compare_vectors(actual, expected) == 1, "Expected first row to contain <58, 64>" ) ? passcount++ : failcount++;
	expected->elements[0] = 139;
	expected->elements[1] = 154;
	read_row(result, 1, actual);
	assert( compare_vectors(actual, expected) == 1, "Expected first row to contain <139, 154>" ) ? passcount++ : failcount++;

	//Freeing
	free_vector(actual);
	free_vector(expected);
	free_matrix(two_by_three);
	free_matrix(three_by_two);
	free_matrix(result);



	printf("%d passed\n%d failed\n", passcount, failcount);
	return 1;
}
