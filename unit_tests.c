#include "vector.h"
#include "matrix.h"
#include "quaternion.h"
#include <math.h>
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


int approx(double a, double b, int precision)
{
    return abs(a-b) < pow(10, precision) ? 1 : 0;
}


int test_vectors()
{
	int pass_count = 0, fail_count = 0;

	printf("\nTesting Vectors.............\n");
	//Vectors

	//assert expected behavior creating vectors
	vector* w = create_vector(3, NULL, NULL);
    assert(w != NULL, "Expected w to not be NULL because a vector was created") ? pass_count++ : fail_count++;
    assert(w->elements[0] == 0, "Expected X component (0th element) to equal 0") ? pass_count++ : fail_count++;
    assert(w->elements[1] == 0, "Expected Y component (1st element) to equal 0") ? pass_count++ : fail_count++;
    assert(w->elements[2] == 0, "Expected Z component (2nd element) to equal 0") ? pass_count++ : fail_count++;

    vector* comp = create_vector(3, NULL, NULL);
	vector* x = create_vector(3, NULL, NULL);
	x->elements[0] = 1;
	vector* y = create_vector(3, NULL, NULL);
	y->elements[1] = 1;
	vector* z = create_vector(3, NULL, NULL);
	z->elements[2] = 1;


    //set comp to x vector
    create_vector(3, NULL, comp);
	comp->elements[0] = 1;

    //test compare_vectors function behavior
	assert(compare_vectors(x, comp) == 1, "Expected x to equal comp") ? pass_count++ : fail_count++;
	assert(compare_vectors(x, y) == 0, "Expected x to not equal y") ? pass_count++ : fail_count++;
	assert(compare_vectors(x, x) == -1, "Expected address of x to equal address of x") ? pass_count++ : fail_count++;

    //set comp to y vector
	create_vector(3, NULL, comp); //test overwriting a vector
	comp->elements[1] = 1;

	assert(compare_vectors(y, comp) == 1, "Expected y to equal comp") ? pass_count++ : fail_count++;
	assert(compare_vectors(y, x) == 0, "Expected y to not equal x") ? pass_count++ : fail_count++;
	assert(compare_vectors(y, y) == -1, "Expected address of y to equal address of y") ? pass_count++ : fail_count++;

    //set comp to z vector
    create_vector(3, NULL, comp); //test overwriting a vector
	comp->elements[2] = 1;

    //test dot_product function behavior
	assert(dot_product(x,y) == 0, "Expected dot product of x and y to be 0, since they are perpendicular") ? pass_count++ : fail_count++;
	assert(dot_product(x,x) == 1, "Expected dot product of x and x to be 1, since 1 = 1^2") ? pass_count++ : fail_count++;

    //test dot_product function behavior
    create_vector(3, NULL, z); //Overwrite z
	cross_product(x, y, z); //cross product of x and y should be z

	assert(z != NULL, "Expected z to not be NULL because a vector was created") ? pass_count++ : fail_count++;
	assert(compare_vectors(z, comp) == 1, "Expected z to equal comp") ? pass_count++ : fail_count++; //assert the cross product of x and y is z
    //NOTE: comp is still set to z

    create_vector(3, NULL, comp);

	comp->elements[0] = 1;
	comp->elements[1] = 2;
	comp->elements[2] = 3;

    //test read_vector
	double* coord = read_vector(comp, NULL);
    assert(coord[0] == 1, "Expected X component (0th element) to equal 1") ? pass_count++ : fail_count++;
    assert(coord[1] == 2, "Expected Y component (1st element) to equal 2") ? pass_count++ : fail_count++;
    assert(coord[2] == 3, "Expected Z component (2nd element) to equal 3") ? pass_count++ : fail_count++;


    //test create_vector with non-NULL elements, and non-NULL dest
	vector* v = create_vector(3, coord, w);

	assert(v != NULL, "Expected z to not be NULL because a vector was created") ? pass_count++ : fail_count++;
	assert(v == w, "Expected w to equal v because w was set as the dest argument") ? pass_count++ : fail_count++;
	assert(v->elements[0] == 1, "Expected X component (0th element) to equal 1") ? pass_count++ : fail_count++;
	assert(v->elements[1] == 2, "Expected Y component (1st element) to equal 1") ? pass_count++ : fail_count++;
	assert(v->elements[2] == 3, "Expected Z component (2nd element) to equal 1") ? pass_count++ : fail_count++;
	assert(compare_vectors(v, comp) ==  1, "Expected v to equal comp") ? pass_count++ : fail_count++;
	assert(compare_vectors(v, y)    ==  0, "Expected v to not equal y") ? pass_count++ : fail_count++;
	assert(compare_vectors(v, w)    == -1, "Expected address of v to equal address of w") ? pass_count++ : fail_count++;

	//idiot-proofing

	coord[0] = 1;
	coord[1] = 0;
	coord[2] = 0;

	vector* i;

	i = create_vector(0, coord, NULL);
	assert(i == NULL, "Expected i to be NULL because count was 0 (count<1)") ? pass_count++ : fail_count++;

	i = create_vector(-2, coord, NULL);
	assert(i == NULL, "Expected i to be NULL because count was -2 (count<1)") ? pass_count++ : fail_count++;

	assert(free_vector(NULL) == 0, "Expected free_vector to return zero because its input was NULL") ? pass_count++ : fail_count++;

    assert(!dot_product(NULL, comp), "Expected dot_product(NULL, comp) to return 0.0 since one of the arguments is NULL") ? pass_count++ : fail_count++;
    assert(!dot_product(comp, NULL), "Expected dot_product(comp, NULL) to return 0.0 since one of the arguments is NULL") ? pass_count++ : fail_count++;
    assert(!dot_product(NULL, NULL), "Expected dot_product(NULL, NULL) to return 0.0 since one of the arguments is NULL") ? pass_count++ : fail_count++;

    assert(!cross_product(NULL, comp, NULL), "Expected cross_product(NULL, comp) to return 0.0 since one of the arguments is NULL") ? pass_count++ : fail_count++;
    assert(!cross_product(comp, NULL, NULL), "Expected cross_product(comp, NULL) to return 0.0 since one of the arguments is NULL") ? pass_count++ : fail_count++;
    assert(!cross_product(NULL, NULL, NULL), "Expected cross_product(NULL, NULL) to return 0.0 since one of the arguments is NULL") ? pass_count++ : fail_count++;

    assert(magnitude_vector(NULL) == -1, "Expected magnitude_vector(NULL) to return NULL") ? pass_count++ : fail_count++;
    assert(!normalize_vector(NULL, NULL), "Expected normalize_vector(NULL, NULL) to return NULL") ? pass_count++ : fail_count++;
    assert(!normalize_vector(NULL, comp), "Expected normalize_vector(NULL, comp) to return NULL") ? pass_count++ : fail_count++;

	//freeing
	free_vector(comp);
	free_vector(w);
	free_vector(x);
	free_vector(y);
	free_vector(z);
	free(coord);

	printf("%d passed\n%d failed\n", pass_count, fail_count);
	return 1;
}

int test_matrices ()
{
	int pass_count = 0, fail_count = 0;
	printf("Testing matrices...\n");

	matrix* identity = identity_matrix(3, 3, NULL);
	matrix* three_by_three = create_matrix(3, 3, NULL);

	assert( compare_matrices(three_by_three, identity) == 0, "Expected matrices to not be equal" ) ? pass_count++ : fail_count++;

	edit_location(three_by_three, 0, 0, 1.0);
	edit_location(three_by_three, 1, 1, 1.0);
	edit_location(three_by_three, 2, 2, 1.0);

	assert( compare_matrices(three_by_three, identity) == 1, "Expected matrices to be equal" ) ? pass_count++ : fail_count++;
	assert( compare_matrices(identity, identity) == -1, "Expected matrices to be equal references" ) ? pass_count++ : fail_count++;

	scale_matrix(identity, 2, identity); //scale identity matrix by 2, and store it in the same matrix
	edit_location(three_by_three, 0, 0, 2.0);
	edit_location(three_by_three, 1, 1, 2.0);
	edit_location(three_by_three, 2, 2, 2.0);
	assert( compare_matrices(three_by_three, identity) == 1, "Expected matrices to be equal" ) ? pass_count++ : fail_count++;


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
	assert( compare_vectors(actual, expected) == 1, "Expected first row to contain <1,2,3>" ) ? pass_count++ : fail_count++;

	expected->elements[0] = 1;
	expected->elements[1] = 4;
	expected->elements[2] = 7;
	read_col(three_by_three, 0, actual);
	assert( compare_vectors(actual, expected) == 1, "Expected first column to contain <1,4,7>" ) ? pass_count++ : fail_count++;

	//Freeing
	free_vector(actual);
	free_vector(expected);
	free_matrix(three_by_three);

	matrix* two_by_three = create_matrix(2, 3, NULL);
	matrix* three_by_two = create_matrix(3, 2, NULL);

	for(int i = 0; i < 6; i++)
	{
		edit_location(two_by_three, i/3, i%3, i+1);
		edit_location(three_by_two, i/2, i%2, i+7);
	}

	matrix* result = multiply_matrices(two_by_three, three_by_two, NULL);

	assert( result->rows == 2, "Expected result to have 2 rows" ) ? pass_count++ : fail_count++;
	assert( result->cols == 2, "Expected result to have 2 columns" ) ? pass_count++ : fail_count++;
	expected = create_vector(2, NULL, NULL);
	actual = create_vector(2, NULL, NULL);
	expected->elements[0] = 58;
	expected->elements[1] = 64;
	read_row(result, 0, actual);
	assert( compare_vectors(actual, expected) == 1, "Expected first row to contain <58, 64>" ) ? pass_count++ : fail_count++;
	expected->elements[0] = 139;
	expected->elements[1] = 154;
	read_row(result, 1, actual);
	assert( compare_vectors(actual, expected) == 1, "Expected first row to contain <139, 154>" ) ? pass_count++ : fail_count++;

	//Freeing
	free_vector(actual);
	free_vector(expected);
	free_matrix(two_by_three);
	free_matrix(three_by_two);
	free_matrix(result);

	printf("%d passed\n%d failed\n", pass_count, fail_count);
	return 1;
}



#define x elements[0]
#define y elements[1]
#define z elements[2]
#define w elements[3]

int test_quaternions () {
    int pass_count = 0, fail_count = 0;
    printf("Testing quaternions...\n");

    printf("----------  test blank_quaternion  ----------\n");
    vector *quat = blank_quaternion(NULL);
    assert(quat->count == 4, "Expected quat to not be NULL") ? pass_count++ : fail_count++;
    assert(quat != NULL, "Expected quat to not be NULL") ? pass_count++ : fail_count++;
    assert(quat->w == 1, "Expected the real component to equal 1") ? pass_count++ : fail_count++;
    assert(quat->x == 0, "Expected the x component to equal 0") ? pass_count++ : fail_count++;
    assert(quat->y == 0, "Expected the y component to equal 0") ? pass_count++ : fail_count++;
    assert(quat->z == 0, "Expected the z component to equal 0") ? pass_count++ : fail_count++;

    //test blank vector with dest
    printf("----------  test blank_quaternion with dest  ----------\n");
    quat->w = 42;
    vector *neo = blank_quaternion(quat);
    assert(quat == neo, "Expected quat to not be NULL") ? pass_count++ : fail_count++;
    assert(quat->w == 1, "Expected the real component to equal 1") ? pass_count++ : fail_count++;
    assert(quat->x == 0, "Expected the x component to equal 0") ? pass_count++ : fail_count++;
    assert(quat->y == 0, "Expected the y component to equal 0") ? pass_count++ : fail_count++;
    assert(quat->z == 0, "Expected the z component to equal 0") ? pass_count++ : fail_count++;

    neo = NULL;

    //test create_quaternion_components
    printf("----------  test create_quaternion_components  ----------\n");
    create_quaternion_components(-1, 0, 1, 2, quat);
    assert(quat->w == -1, "Expected the real component to equal -1") ? pass_count++ : fail_count++;
    assert(quat->x ==  0, "Expected the x component to equal 0") ? pass_count++ : fail_count++;
    assert(quat->y ==  1, "Expected the y component to equal 1") ? pass_count++ : fail_count++;
    assert(quat->z ==  2, "Expected the z component to equal 2") ? pass_count++ : fail_count++;

    //test compare_quaternions
    printf("----------  test compare_components  ----------\n");
    vector *comp = blank_quaternion(NULL);
    blank_quaternion(quat);

    assert(comp != quat, "Expected that quat and comp are distinct quaternions") ? pass_count++ : fail_count++;
    assert(compare_vectors(comp, quat) ==  1, "Expected that quat and comp are equal and distinct") ? pass_count++ : fail_count++;
    assert(compare_vectors(comp, comp) == -1, "Expected that comp being compared with itself would return -1") ? pass_count++ : fail_count++;

    create_quaternion_components(-1, 0, 1, 2, quat);
    create_quaternion_components(-1, 0, 1, 2, comp);

    assert(compare_vectors(comp, quat) ==  1, "Expected that quat and comp are equal and distinct") ? pass_count++ : fail_count++;
    assert(compare_vectors(comp, comp) == -1, "Expected that comp being compared with itself would return -1") ? pass_count++ : fail_count++;

    create_quaternion_components(1, 2, 3, 4, comp);

    assert(compare_vectors(comp, quat) ==  0, "Expected that quat and comp are unequal and distinct") ? pass_count++ : fail_count++;

    assert(compare_vectors(NULL, quat) ==  0, "Expected that a NULL comparison would fail") ? pass_count++ : fail_count++;
    assert(compare_vectors(comp, NULL) ==  0, "Expected that a NULL comparison would fail") ? pass_count++ : fail_count++;
    assert(compare_vectors(NULL, NULL) ==  0, "Expected that a NULL comparison would fail") ? pass_count++ : fail_count++;


    //test clone_quaternion
    printf("----------  test clone_components  ----------\n");
    blank_quaternion(comp);
    assert(compare_vectors(quat, comp) == 0, "Expected quaternions to be distinct and unequal") ? pass_count++ : fail_count++;
    clone_vector(quat, comp); //clone quat into comp
    assert(compare_vectors(quat, comp) == 1, "Expected quaternions to be distinct and equal") ? pass_count++ : fail_count++;
    assert(!neo, "Expected neo to be NULL") ? pass_count++ : fail_count++;
    assert(compare_vectors(quat, neo) == 0, "Expected that a NULL comparison would fail") ? pass_count++ : fail_count++;
    neo = clone_vector(quat, neo);
    assert(compare_vectors(quat, neo) == 1, "Expected quaternions to be distinct and equal") ? pass_count++ : fail_count++;

    printf("----------  test magnitude_components  ----------\n");
    create_quaternion_components(3, 4, 0, 0, quat);
    assert(magnitude_vector(quat) == 5, "Expected magnitude to equal 5") ? pass_count++ : fail_count++;
    create_quaternion_components(1, 1, 1, 1, quat);
    assert(magnitude_vector(quat) == 2, "Expected magnitude to equal 5") ? pass_count++ : fail_count++;
    create_quaternion_components(2, 2, 2, 2, quat);
    assert(magnitude_vector(quat) == 4, "Expected magnitude to equal 5") ? pass_count++ : fail_count++;
    create_quaternion_components(1, 2, 3, 4, quat);
    assert(magnitude_vector(quat) == sqrt(30), "Expected magnitude to equal 5") ? pass_count++ : fail_count++;


    printf("----------  test normalize_components  ----------\n");
    create_quaternion_components(3, 4, 0, 0, quat); //should create a magnitude 5 quaternion, as previously tested
    normalize_vector(quat, comp); //copy a normalized version of quat into comp

    assert(magnitude_vector(quat) == 5, "Expected quat to have a magnitude of 5") ? pass_count++ : fail_count++;
    assert(magnitude_vector(comp) == 1, "Expected comp to have a magnitude of 1") ? pass_count++ : fail_count++;
    assert(dot_product(comp, quat) == 5, "Expected dot_product of comp and quat to equal 5") ? pass_count++ : fail_count++; //relies on dot_product working
    assert(approx(comp->x * 0.75, comp->w, -10), "Expected the ratio of components to be preserved") ? pass_count++ : fail_count++;


    printf("----------  test quaternion_to_vector  ----------\n");
    create_quaternion_components(0, -1, 0, 1, quat);
    vector *vec = quaternion_to_vector(quat, NULL);
    assert(quat->x == vec->x, "Expected the x components to be equal") ? pass_count++ : fail_count++;
    assert(quat->y == vec->y, "Expected the y components to be equal") ? pass_count++ : fail_count++;
    assert(quat->z == vec->z, "Expected the z components to be equal") ? pass_count++ : fail_count++;
    assert(!quaternion_to_vector(quat, comp), "Expected a return value of NULL for non-4D vector destination") ? pass_count++ : fail_count++;


    printf("----------  test quaternion_to_vector  ----------\n");
    vec->x = 3;
    vec->y = 4;
    vec->z = 5;
    vector_to_quaternion(vec, quat);
    create_quaternion_components(0, 3, 4, 5, comp);
    assert(compare_vectors(quat, comp) == 1, "Expected quat and comp to be equal and distinct") ? pass_count++ : fail_count++;
    assert(!vector_to_quaternion(quat, vec), "Expected a return value of NULL for non-3D vector destination") ? pass_count++ : fail_count++;


    //printf("----------  test create_quaternion_angle_vector  ----------\n");
    //printf("----------  test quaternion_to_matrix  ----------\n");
    //printf("----------  test inverse_quaternion  ----------\n");
    //printf("----------  test multiply_quaternions  ----------\n");


    free_vector(comp);
    free_vector(neo);
    free_vector(quat);
    free_vector(vec);

    printf("%d passed\n%d failed\n", pass_count, fail_count);
    return 1;
}