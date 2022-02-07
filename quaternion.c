
#include "quaternion.h"
#include <stdlib.h>
#include <math.h>
#include "vector.h"

#define x elements[0]
#define y elements[1]
#define z elements[2]
#define w elements[3]

static double square(double n)
{
    return n * n;
}

/*
 * Creates a blank quaternion
 * If dest is NULL, a new quaternion is allocated
 * If dest is not NULL, dest is overwritten
 */
vector *blank_quaternion(vector *dest)
{
    dest = create_vector(4, NULL, dest);
    dest->w = 1;
    return dest;
}


/*
 * Creates a quaternion with the given components
 * If dest is NULL, a new quaternion is allocated
 * If dest is not NULL, dest is overwritten
 */
vector *create_quaternion_components ( double w_comp, double x_comp, double y_comp, double z_comp, vector *dest )
{
    dest = blank_quaternion(dest);

	dest->w = w_comp;
	dest->x = x_comp;
	dest->y = y_comp;
	dest->z = z_comp;

	return dest;
}


/*
 * Creates a new quaternion corresponding to an angle-axis transformation
 * If dest is NULL, a new quaternion is allocated
 * If dest is not NULL, dest is overwritten
 */
vector *create_quaternion_angle_axis ( double angle, vector *axis, vector *dest)
{
	if( !axis )
		return NULL;

	dest = vector_to_quaternion(axis, dest);
    normalize_vector(dest, dest);

	double sine = sin(angle/2);

    for(int i = 0; i < 3; i++)
        dest->elements[i] = sine * dest->elements[i];

	dest->w = cos(angle/2);

	return dest;
}


//Frees the quaternion
int free_quaternion (vector *quat)
{
    free_vector(quat);
}


/*
 * Returns the given quaternion with the imaginary components negated
 * Returns NULL if quat is NULL
 * Returns a freshly allocated quaternion if dest is NULL
 * If dest is not NULL, dest is overwritten
 */
vector *inverse_quaternion(vector *quat, vector *dest)
{
    if( !quat )
        return NULL;

	dest = clone_vector(quat, dest);

    for(int i = 0; i < 3; i++)
        dest->elements[i] *= -1;

	return dest;
}

/*
 * Creates a quaternion with no real component and imaginary components corresponding to the vector
 * If dest is NULL, a new quaternion is allocated
 * If dest is not NULL, dest is overwritten
 */
vector *vector_to_quaternion (vector *vec, vector *dest)
{
	if( !vec )
		return NULL;

	dest = create_quaternion_components(0, vec->elements[0], vec->elements[1], vec->elements[2], dest);
	return dest;
}

vector *quaternion_to_vector (vector *quat, vector *dest)
{
	if( !quat )
		return NULL;

    dest = create_vector(3, NULL, dest);

    for(int i = 0; i < 3; i++)
        dest->elements[i] = quat->elements[i];

    return dest;
}

/*
 * Returns the result of two
 */
vector *multiply_quaternions (vector* left, vector* right, vector* dest)
{
	if( !left || !right )
		return NULL;

	dest = blank_quaternion(dest);

	dest->w = left->w * right->w - left->x * right->x - left->y * right->y - left->z * right->z;
	dest->x = left->w * right->x + left->x * right->w + left->y * right->z - left->z * right->y;
	dest->y = left->w * right->y + left->y * right->w + left->z * right->x - left->x * right->z;
	dest->z = left->w * right->z + left->z * right->w + left->x * right->y - left->y * right->x;

    return dest;
}

vector *rotate_vector (vector *quat, vector *vec, vector *dest)
{
    //quat * vec * inv_quat
    if( !quat || !vec )
        return NULL;

	vector *inverse = inverse_quaternion(quat, inverse); //assign inverse
	vector *vec_quat = vector_to_quaternion(vec, NULL); //create quaternion from vec
    normalize_vector(vec_quat, vec_quat); //normalize

	vector *inter  = multiply_quaternions(quat, vec_quat, NULL); //perform first multiplication
	vector *result = multiply_quaternions(inter, inverse, NULL); //perform second multiplication
	dest = quaternion_to_vector(result, dest); //isolate vector

    //Free intermediate variables
	free_quaternion(inter);
	free_quaternion(inverse);
	free_quaternion(vec_quat);
	free_quaternion(result);

	return dest;
}

matrix *quaternion_to_matrix(vector *quat, matrix *dest)
{
	if( !quat )
		return NULL;

	if( !dest )
		dest = create_matrix(3, 3, NULL);

	else if( dest->rows != 3 || dest->cols != 3)
		return NULL;

	vector *vec = create_vector(3, NULL, NULL);

	vec->elements[0] = square(quat->w) + square(quat->x) - square(quat->y) - square(quat->z);
    vec->elements[1] = 2 * (quat->x * quat->y + quat->w * quat->z);
    vec->elements[2] = 2 * (quat->x * quat->z - quat->w * quat->y);
	write_row(dest, 0, vec);

    vec->elements[0] = 2 * (quat->x * quat->y - quat->w * quat->z);
    vec->elements[1] = square(quat->w) - square(quat->x) + square(quat->y) - square(quat->z);
    vec->elements[2] = 2 * (quat->x * quat->y + quat->w * quat->z);
	write_row(dest, 0, vec);

    vec->elements[0] = 2 * (quat->x * quat->z + quat->w * quat->y);
    vec->elements[1] = 2 * (quat->y * quat->z - quat->w * quat->x);
    vec->elements[2] = square(quat->w) - square(quat->x) - square(quat->y) + square(quat->z);
	write_row(dest, 0, vec);

	free(vec->elements);

	return dest;
}
