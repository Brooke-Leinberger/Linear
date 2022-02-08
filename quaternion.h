#ifndef QUAT
#define QUAT
#include "vector.h"
#include "matrix.h"

extern vector* create_quaternion_components   ( double w, double x, double y, double z, vector *dest); //tested
extern vector* create_quaternion_angle_vector ( double angle, vector* axis, vector *dest );
extern vector* blank_quaternion (vector *dest); //tested
extern int     free_quaternion ( vector *quat ); //tested
extern vector* vector_to_quaternion (vector *vec,  vector *dest); //tested
extern vector* quaternion_to_vector (vector* quat, vector *dest); //tested
extern matrix* quaternion_to_matrix (vector* quat, matrix *dest);
extern vector* inverse_quaternion   (vector* quat, vector* dest);
extern vector* multiply_quaternions (vector* left, vector* right, vector *dest);

#endif
