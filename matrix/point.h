#ifndef POINT_H
# define POINT_H

# include <libft.h>

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_line
{
	struct s_point p1;
	struct s_point p2;
}	t_line;

t_line *line_init(t_point p1, t_point p2)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	line->p1 = p1;
	line->p2 = p2;
	return (line);
}

t_point point_add(t_point point1, t_point point2) \
		asm("_" "matrix_add");

t_point point_sub(t_point point1, t_point point2) \
		asm("_" "matrix_sub");

t_point point_scalar(t_point point, float v) \
		asm("_" "matrix_scalar");

float dot_product_v3(t_point point1, t_point point2) \
		asm("_" "dot_product");

t_point cross_product_v3(t_point point1, t_point point2) \
		asm("_" "cross_product3");

#endif