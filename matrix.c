#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "vector.h"

dmatrix* create_matrix(int rows, int cols, dmatrix* dest)
{
	dmatrix* mat;

	if(!dest)
		mat = malloc(sizeof(dmatrix));
	else
	{
		if(dest->rows != rows || dest->cols != cols)
			return NULL;
		mat = dest;
	}

	mat->rows = rows;
	mat->cols = cols;

	mat->row_arr = malloc(rows * sizeof(double));

	for(int i = 0; i < rows; i++)
	{
		mat->row_arr[i] = malloc(cols * sizeof(double));
		memset(mat->row_arr[i], 0, cols * sizeof(double));
	}

	return mat;
}

int free_matrix(dmatrix* mat)
{
	if(!mat)
		return 0;

	for(int i = 0; i < mat->rows; i++)
		free(mat->row_arr[i]);

	free(mat->row_arr);
	free(mat);
	return 1;
}

double* read_location(dmatrix* mat, int row, int col)
{
	if(!mat) //mat is not null
		return NULL;
	if(row >= mat->rows || row < 0) //rows in bound
		return NULL;
	if(col >= mat->cols || col < 0) //cols in bound
		return NULL;

	return &((mat->row_arr[row])[col]);
}

int edit_location(dmatrix* mat, int row, int col, double val)
{
	double* val_ptr;
	if( !mat || !(val_ptr = read_location(mat, row, col)) )
		return 0;

	*val_ptr = val;
	return 1;
}

vector* read_row(dmatrix* mat, int row, vector* dest)
{
	if(!mat) //mat is not null
		return NULL;
	if(row >= mat->rows || row < 0) //rows in bound
		return NULL;

	return create_vector(mat->cols, mat->row_arr[row], dest);
}

vector* read_col(dmatrix* mat, int col, vector* dest)
{
	if(!mat) //mat is not null
		return NULL;
	if(col >= mat->cols || col < 0) //cols in bound
		return NULL;

	double* column = malloc(mat->rows * sizeof(double));

	for(int i = 0; i < mat->rows; i++)
		column[i] = (mat->row_arr[i])[col];

	vector* vec = create_vector(mat->rows, column, dest);
	free(column);
	return vec;
}

int write_row( dmatrix* mat, int row, vector* arr )
{
	if(!mat || !arr) //mat is not null
		return 0;
	if(row >= mat->rows || row < 0) //rows in bound
		return 0;
	if(arr->count != mat->cols) //vector is right size
		return 0;

	for(int i = 0; i < mat->cols; i++)
		mat->row_arr[row][i] = arr->elements[i];
	return 1;
}

int write_col( dmatrix* mat, int col, vector* arr )
{
	if(!mat || !arr) //mat is not null
		return 0;
	if(col >= mat->cols || col < 0) //cols in bound
		return 0;
	if(arr->count != mat->rows) //vector is right size
		return 0;

	for(int i = 0; i < mat->rows; i++)
		mat->row_arr[i][col] = arr->elements[i];

	return 1;

}

dmatrix* scale_matrix(dmatrix* mat, double scale, dmatrix* dest)
{
	if(!mat)
		return NULL;

	dmatrix* output = create_matrix(mat->rows, mat->cols, dest);

	for(int row = 0; row < mat->rows; row++)
		for(int col = 0; col < mat->cols; col++)
			output->row_arr[row][col] = mat->row_arr[row][col] * scale;

	return output;
}
dmatrix* multiply_matricies(dmatrix* a, dmatrix* b, dmatrix* dest)
{
	if(!a || !b)
		return NULL;

	dmatrix* mat = create_matrix(a->rows, b->cols, dest);
	vector* row  = create_vector(a->rows, NULL, NULL);
	vector* col  = create_vector(b->cols, NULL, NULL);

	for(int row_index = 0; row_index < a->rows; row_index++)
	{
		for(int col_index = 0; col_index < b->cols; col_index++)
		{
			read_row(a, row_index, row);
			read_col(b, col_index, col);
			mat->row_arr[row_index][col_index] = dot_product(row, col);
		}
	}

	return mat;
}
