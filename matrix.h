#ifndef MAT
#define MAT
#include "vector.h"


typedef struct matrix
{
	int rows, cols; //size
	double** row_arr; //pointers
} matrix;

extern matrix* create_matrix(int rows, int cols, matrix* dest);
extern int free_matrix(matrix* mat);
extern matrix* identity_matrix(int rows, int cols, matrix* dest);
extern int compare_matrices(matrix* a, matrix* b);
extern double* read_location(matrix* mat, int row, int col);
extern int edit_location(matrix* mat, int row, int col, double val);
extern vector* read_row(matrix* mat, int row, vector* dest);
extern vector* read_col(matrix* mat, int col, vector* dest);
extern int write_row(matrix* mat, int row, vector* source);
extern int write_col(matrix* mat, int col, vector* source);
extern matrix* scale_matrix(matrix* mat, double val, matrix* dest);
extern matrix* multiply_matrices(matrix* a, matrix* b, matrix* dest);
#endif /* MAT */
