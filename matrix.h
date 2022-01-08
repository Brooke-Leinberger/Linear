#ifndef MAT
#define MAT
#include "vector.h"


typedef struct dmatrix
{
	int rows, cols; //size
	double** row_arr; //ptrs
} dmatrix;

extern dmatrix* create_matrix(int rows, int cols, dmatrix* dest);
extern int free_matrix(dmatrix* mat);
extern dmatrix* identity_matrix(int rows, int cols, dmatrix* dest);
extern int compare_matricies(dmatrix* a, dmatrix* b);
extern double* read_location(dmatrix* mat, int row, int col);
extern int edit_location(dmatrix* mat, int row, int col, double val);
extern vector* read_row(dmatrix* mat, int row, vector* dest);
extern vector* read_col(dmatrix* mat, int col, vector* dest);
extern int write_row(dmatrix* mat, int row, vector* dest);
extern int write_col(dmatrix* mat, int col, vector* dest);
extern dmatrix* scale_matrix(dmatrix* mat, double val, dmatrix* dest);
extern dmatrix* multiply_matricies(dmatrix* a, dmatrix* b, dmatrix* dest);
#endif /* h1.h */
