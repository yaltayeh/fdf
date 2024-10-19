#ifndef MATRIX_H
# define MATRIX_H

# define MATRIX_SIZE 4

typedef struct s_matrix
{
	float	data[MATRIX_SIZE];
}	t_matrix;

t_matrix	matrix_add(t_matrix matrix1, t_matrix matrix2);
t_matrix	matrix_sub(t_matrix matrix1, t_matrix matrix2);
t_matrix	matrix_scalar(t_matrix matrix, float v);
float		dot_product(t_matrix matrix1, t_matrix matrix2);
t_matrix	cross_product3(t_matrix matrix1, t_matrix matrix2);

#endif