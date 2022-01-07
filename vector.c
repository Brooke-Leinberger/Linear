#include "vector.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

//helper function
static double square(double num)
{
	return num * num;
}

/*
creates a vector of size count, using elements as values.
if dest is not null, the vector dest will be overwritten, if it is the same size, and is the value returned
if count is less than one, NULL is returned
if elements is null, the vector is populated with zeros
if dest is null, a new vector is allocated
*/
vector* create_vector( int count, double* elements, vector* dest )
{
	if( count < 1 )
		return NULL;

	vector* vec;

	if( !dest )
		vec = malloc(sizeof(vector));
	else
	{
		if(dest->count != count)
			return NULL;
		vec = dest;
	}

	vec->count = count;
	vec->elements = malloc(count * sizeof(double));

	if( elements )
		for( int i = 0; i < count; i++ )
			vec->elements[i] = elements[i];

	else
		memset(vec->elements, 0, count * sizeof(double));

	return vec;
}

/*Frees a given vector vec
  Returns a 1 if completed successfully
  Returns a 0 if vec is NULL*/
int free_vector( vector* vec )
{
	if ( !vec )
		return 0;

	free(vec->elements);
	free(vec);
	return 1;
}

/*
returns a pointer to a copy of the elements of a given vector
returns NULL pointer if vec is a NULL pointer
*/
double* read_vector( vector*  vec )
{
	if( !vec )
		return NULL;

	double* arr = malloc(vec->count * sizeof(double));
	for( int i = 0; i < vec->count; i++ )
		arr[i] = vec->elements[i];

	return arr;
}

/*Returns a pointer to a copy of a given vector
  if dest is NULL, a new vector is allocated
  if dest is not NULL, and is the same size as
  src, it is overwritten and returned
  if dest is not NULL and not the same size as
  src, NULL is returned
  if src is NULL, NULL is returned*/
vector* clone_vector( vector* src, vector* dest )
{
	if (!src)
		return NULL;

	return create_vector(src->count, src->elements, dest);
}

/*Scales the vector vec by scale and writes the result back on vec
  Returns NULL if vec is null, or if vec and dest are not the same size
  If dest is null, a new vector is allocated and returned
  If dest is not null, it is overwritten and returned*/
vector* scale_vector( double scale, vector* vec, vector* dest )
{
	if ( !vec )
		return NULL;

	if( !dest )
		dest = create_vector(vec->count, NULL, NULL);

	else if( dest->count != vec->count )
			return NULL;

	for( int i = 0; i < vec->count; i++ )
		dest->elements[i] = vec->elements[i] * scale;

	return dest;
}

/*Returns the magnitude / "length" of the vector vec
  Returns non-negative number on success
  Returns negative number (-1.0) on failure (vec is NULL).*/
double magnitude_vector( vector* vec )
{
	if (!vec)
		return -1.0;

	double sum = 0.0;
	for(int i = 0; i < vec->count; i++)
		sum += square(vec->elements[i]);

	return sqrt(sum);
}

/*Divides (scales) a vector vec by its magnitude
  Returns 0 if vec is NULL */
vector* normalize_vector( vector* vec, vector* dest )
{
	//NULL and compatatability checks are done in scale_vector
	double mag = magnitude_vector(vec);
	return scale_vector(1.0 / mag, vec, dest);
}

/*Returns the dot product of two vectors
  If either of the input vectors are NULL, 0.0 is returned
  0.0 is a valid output (the two vectors are perpendicular),
  but it can signal something may potentially be wrong*/
double dot_product( vector* left, vector* right )
{
	if ( !left || !right || left->count != right->count )
		return 0.0; //this is still a valid output, but can act as a flag

	double sum = 0.0;
	for( int i = 0; i < left->count; i++ )
		sum += left->elements[i] * right->elements[i];

	return sum;
}

/*Returns the cross product of two 3D vectors
  Allocates a new vector for the result if dest is NULL
  Returns NULL if either vector input is NULL
  Returns NULL if either vector input is not 3D
  Returns NULL if dest is not NULL and not 3D*/
vector* cross_product( vector* left, vector* right, vector* dest )
{
	if ( !left || !right )
		return NULL;
	if ( left->count != 3 || right->count != 3 )
		return NULL;

	if( !dest )
		dest = create_vector(3, NULL, NULL);

	else if( dest->count != 3 )
			return NULL;

	dest->elements[0] = left->elements[1] * right->elements[2] - left->elements[2] * right->elements[1];
	dest->elements[1] = left->elements[2] * right->elements[0] - left->elements[0] * right->elements[2];
	dest->elements[2] = left->elements[0] * right->elements[1] - left->elements[1] * right->elements[0];

	return dest;
}
