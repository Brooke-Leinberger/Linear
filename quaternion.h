#ifndef QUAT
#define QUAT
#include "vector.h"
#include "matrix.h"

typedef struct quaternion
{
	double w, x, y, z;
} quaternion;

extern quaternion* create_quaternion_components   ( double w, double x, double y, double z, quaternion *dest); //tested
extern quaternion* create_quaternion_angle_vector ( double angle, vector* axis, quaternion *dest );
extern quaternion* blank_quaternion (quaternion *dest); //tested
extern int         free_quaternion ( quaternion *quat ); //tested
extern int         compare_quaternions ( quaternion *a, quaternion *b ); //tested
extern quaternion* clone_quaternion( quaternion *quat, quaternion *dest); //tested
extern double      magnitude_quaternion(quaternion *quat); //tested
extern quaternion* normalize_quaternion(quaternion *quat, quaternion *dest); //
extern quaternion* vector_to_quaternion(vector *vec,   quaternion *dest);
extern vector*     quaternion_to_vector(quaternion* quat,  vector *dest);
extern matrix*    quaternion_to_matrix(quaternion* quat, matrix *dest);
extern quaternion* inverse_quaternion (quaternion* quat, quaternion* dest);
extern quaternion* multiply_quaternions (quaternion* left, quaternion* right, quaternion *dest);

#endif
