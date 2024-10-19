#include <stdio.h>
#include "matrix.h"

t_matrix	matrix_add(t_matrix matrix1, t_matrix matrix2)
{
	t_matrix	result;
	size_t		i;

	i = 0;
	while (i < MATRIX_SIZE)
	{
		result.data[i] = matrix1.data[i] + matrix2.data[i];
		i++;
	}
	return (result);
}

t_matrix	matrix_sub(t_matrix matrix1, t_matrix matrix2)
{
	t_matrix	result;
	size_t		i;

	i = 0;
	while (i < MATRIX_SIZE)
	{
		result.data[i] = matrix1.data[i] - matrix2.data[i];
		i++;
	}
	return (result);
}

t_matrix	matrix_scalar(t_matrix matrix, float value)
{
	t_matrix	result;
	size_t		i;

	i = 0;
	while (i < MATRIX_SIZE)
	{
		result.data[i] = matrix.data[i] * value;
		i++;
	}
	return (result);
}

float	dot_product(t_matrix matrix1, t_matrix matrix2)
{
	float	result;
	size_t	i;

	i = 0;
	result = 0;
	while (i < MATRIX_SIZE)
	{
		result += matrix1.data[i] * matrix2.data[i];
		i++;
	}
	return (result);
}

t_matrix	cross_product3(t_matrix matrix1, t_matrix matrix2)
{
	t_matrix	result;

	result.data[0] = matrix1.data[1] * matrix2.data[2] \
					- matrix1.data[2] * matrix2.data[1];
	result.data[1] = matrix1.data[0] * matrix2.data[2] \
					- matrix1.data[2] * matrix2.data[0];
	result.data[2] = matrix1.data[0] * matrix2.data[1] \
					- matrix1.data[1] * matrix2.data[0];
	return (result);
}
