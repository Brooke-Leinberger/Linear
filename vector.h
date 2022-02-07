#ifndef VEC
#define VEC

typedef struct vector 
{
	int count;
	double* elements;
} vector;

extern vector *create_vector(int count, const double *elements, vector *dest);
extern vector *blank_vector (int count, vector *dest);
extern int free_vector(struct vector* vec);
extern double *read_vector(vector* vec, double *dest);
extern int compare_vectors(vector *a, vector *b);
extern vector *clone_vector(vector *vec, vector *dest);
extern vector *scale_vector(double scale, vector *vec, vector *dest);
extern double magnitude_vector(vector *vec);
extern vector *normalize_vector(vector *vec, vector *dest);
extern double dot_product(vector *left, vector *right);
extern vector *cross_product(vector *left, vector *right, vector *dest);
#endif /* VEC */
