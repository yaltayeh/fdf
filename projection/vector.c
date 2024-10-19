typedef struct s_vector
{
	float	a;
	float	b;
	float	c;
}	t_vector;

t_vector vector_addition(t_vector v1, t_vector v2)
{
	t_vector ret;

	ret.a = v1.a + v2.a;
	ret.b = v1.b + v2.b;
	ret.c = v1.c + v2.c;
	return (ret);
}

t_vector vector_subtraction(t_vector v1, t_vector v2)
{
	t_vector ret;

	ret.a = v1.a - v2.a;
	ret.b = v1.b - v2.b;
	ret.c = v1.c - v2.c;
	return (ret);
}

t_vector vector_scalar(float value, t_vector v)
{
	v.a *= value;
	v.b *= value;
	v.c *= value;
	return (v);
}

float dot_product(t_vector v1, t_vector v2)
{
	return (v1.a * v2.a + v1.b * v2.b + v1.c * v2.c);
}

t_vector cross_product(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.a = v1.b * v2.c - v1.c * v2.b;
	ret.b = v1.c * v2.a - v1.a * v2.c;
	ret.c = v1.a * v2.b - v1.b * v2.a;
	return (ret);
}
