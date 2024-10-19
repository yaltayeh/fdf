#ifndef VECTOR3_H
# define VECTOR3_H

typedef struct s_vector3
{
	float	a;
	float	b;
	float	c;
}	t_vector3;

t_vector3 vector3_add(t_vector3 vector1, t_vector3 vector2) \
		asm("_" "matrix_add");

t_vector3 vector3_sub(t_vector3 vector1, t_vector3 vector2) \
		asm("_" "matrix_sub");

t_vector3 vector3_scalar(t_vector3 vector, float v) \
		asm("_" "matrix_scalar");

float dot_product_v3(t_vector3 vector1, t_vector3 vector2) \
		asm("_" "dot_product");

t_vector3 cross_product_v3(t_vector3 vector1, t_vector3 vector2) \
		asm("_" "cross_product3");

#endif