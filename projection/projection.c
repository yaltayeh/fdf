#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

/*
 * To find the equation of a plane given three points in 3D space, follow these steps:
 *
 * Step 1: Define the Points
 * Let the three points be:
 *   P1(x1, y1, z1)
 *   P2(x2, y2, z2)
 *   P3(x3, y3, z3)
 *
 * Step 2: Find Two Vectors in the Plane
 * You can create two vectors in the plane using the points:
 *   v1 = P2 - P1 = (x2 - x1, y2 - y1, z2 - z1)
 *   v2 = P3 - P1 = (x3 - x1, y3 - y1, z3 - z1)
 *
 * Step 3: Compute the Normal Vector
 * The normal vector n to the plane can be found using the cross product of the two vectors:
 *   n = v1 × v2
 *
 * If v1 = (a, b, c) and v2 = (d, e, f), then the cross product is given by:
 *   n = (b*f - c*e, c*d - a*f, a*e - b*d)
 *
 * Step 4: Write the Equation of the Plane
 * The equation of the plane can be expressed in the form:
 *   n_x * (x - x1) + n_y * (y - y1) + n_z * (z - z1) = 0
 * where (n_x, n_y, n_z) are the components of the normal vector n.
 *
 * Rearranging gives us:
 *   n_x * x + n_y * y + n_z * z = d
 * where d is calculated as:
 *   d = n_x * x1 + n_y * y1 + n_z * z1
*/

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

t_point sub_point(t_point p1, t_point p2)
{
	t_point	ret;

	ret.x = p1.x - p2.x;
	ret.y = p1.y - p2.y;
	ret.z = p1.z - p2.z;
	return (ret);
}

t_point add_point(t_point p1, t_point p2)
{
	t_point	ret;

	ret.x = p1.x + p2.x;
	ret.y = p1.y + p2.y;
	ret.z = p1.z + p2.z;
	return (ret);
}

t_point div_vector(t_point p1, t_point p2)
{
	t_point	ret;

	bzero(&ret, sizeof(ret));
	if (p2.x != 0)
		ret.x = p1.x / p2.x;
	if (p2.y != 0)
	ret.y = p1.y / p2.y;
	if (p2.z != 0)
		ret.z = p1.z / p2.z;
	return (ret);
}

t_point	multi_point(t_point p, float v)
{
	t_point	ret;

	ret.x = p.x * v;
	ret.y = p.y * v;
	ret.z = p.z * v;
	return (ret);
}

t_point multi_points(t_point p1, t_point p2)
{
	t_point	ret;

	ret.x = p1.x * p2.x;
	ret.y = p1.y * p2.y;
	ret.z = p1.z * p2.z;
	return (ret);
}

t_point cross_vectors(t_point v1, t_point v2)
{
	t_point	ret;
	// If v1 = (a, b, c) and v2 = (d, e, f), then the cross product is given by:
	//	*   n = (a*e - b*d)
	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

t_point abs_point(t_point p)
{
	if (p.x < 0)
		p.x = -p.x;
	if (p.y < 0)
		p.y = -p.y;
	if (p.z < 0)
		p.z = -p.z;
	return p;
}



int sum_point(t_point p)
{
	return (p.x + p.y + p.z);
}


void plane_equation(t_point p[3], float eq[4])
{
	t_point	v1;
	t_point	v2;
	t_point	n;

	//  * Step 2: Find Two Vectors in the Plane
	//  * You can create two vectors in the plane using the points:
	//  *   v1 = P2 - P1 = (x2 - x1, y2 - y1, z2 - z1)
	//  *   v2 = P3 - P1 = (x3 - x1, y3 - y1, z3 - z1)
	v1 = sub_point(p[1], p[0]);
	v2 = sub_point(p[2], p[0]);

	//	* Step 3: Compute the Normal Vector
	//	* The normal vector n to the plane can be found using the cross product of the two vectors:
	//	*   n = v1 × v2
	//	*
	//	* If v1 = (a, b, c) and v2 = (d, e, f), then the cross product is given by:
	//	*   n = (b*f - c*e, c*d - a*f, a*e - b*d)
	n = cross_vectors(v1, v2);

	// * Step 4: Write the Equation of the Plane
	// * The equation of the plane can be expressed in the form:
	// *   n_x * (x - x1) + n_y * (y - y1) + n_z * (z - z1) = 0
	// * where (n_x, n_y, n_z) are the components of the normal vector n.
	eq[0] = n.x;
	eq[1] = n.y;
	eq[2] = n.z;
	eq[3] = -sum_point(multi_points(n, p[0]));
	// return is (ax + by + cz + d = 0)
}

void	line_equation(t_point p1, t_point p2, t_point eq[2])
{
	t_point direction_ratios;

	direction_ratios = sub_point(p2, p1);
	eq[0] = p1;
	eq[1] = direction_ratios;
}



/*

Let a line in three dimensions be specified by two points x_1=(x_1,y_1,z_1) and x_2=(x_2,y_2,z_2) lying on it, so a vector along the line is given by

 v=[x_1+(x_2-x_1)t; y_1+(y_2-y_1)t; z_1+(z_2-z_1)t]. 	
(1)
The squared distance between a point on the line with parameter t and a point x_0=(x_0,y_0,z_0) is therefore

 d^2=[(x_1-x_0)+(x_2-x_1)t]^2+[(y_1-y_0)+(y_2-y_1)t]^2+[(z_1-z_0)+(z_2-z_1)t]^2.  	
(2)
To minimize the distance, set d(d^2)/dt=0 and solve for t to obtain

 t=-((x_1-x_0)·(x_2-x_1))/(|x_2-x_1|^2), 	
(3)
where · denotes the dot product. The minimum distance can then be found by plugging t back into (2) to obtain

d^2=(x_1-x_0)^2+(y_1-y_0)^2+(z_1-z_0)^2+2t[(x_2-x_1)(x_1-x_0)+(y_2-y_1)(y_1-y_0)+(z_2-z_1)(z_1-z_0)]+t^2[(x_2-x_1)^2+(y_2-y_1)^2+(z_2-z_1)^2] 	
(4)
=|x_1-x_0|^2-2([(x_1-x_0)·(x_2-x_1)]^2)/(|x_2-x_1|^2)+([(x_1-x_0)·(x_2-x_1)]^2)/(|x_2-x_1|^2) 	
(5)
=(|x_1-x_0|^2|x_2-x_1|^2-[(x_1-x_0)·(x_2-x_1)]^2)/(|x_2-x_1|^2). 	
(6)
Using the vector quadruple product

 (AxB)^2=A^2B^2-(A·B)^2 	
(7)
where x denotes the cross product then gives

 d^2=(|(x_2-x_1)x(x_1-x_0)|^2)/(|x_2-x_1|^2), 	
(8)
and taking the square root results in the beautiful formula

d	=	(|(x_2-x_1)x(x_1-x_0)|)/(|x_2-x_1|)	
(9)
	=	(|(x_0-x_1)x(x_0-x_2)|)/(|x_2-x_1|)	
(10)
.			
(11)
Here, the numerator is simply twice the area of the triangle formed by points x_0, x_1, and x_2,
 and the denominator is the length of one of the bases of the triangle, which follows since, 
 from the usual triangle area formula, Delta=bd/2.
*/
t_point distance_line_and_point(t_point line_points[2], t_point point)
{
	float t;
	t_point lp, v;
	
	v = sub_point(line_points[1], line_points[0]);
	lp = sub_point(line_points[0], point);
	multi_point(v, t);
}

int main()
{
	float eq[4];
	t_point line_eq[2];
	t_point plane_p[3] = {
		{-5, 0, -5},
		{5, 0, 0},
		{0, 0, 5}
	};
	plane_equation(plane_p, eq);
	printf("plane_equation:\n");
	printf("   %.2fx + %.2fy + %.2fz + %.2f = 0\n", eq[0], eq[1], eq[2], eq[3]);

	t_point line_p[2] = {
		{0, 5, 0},
		{0, 0, 0}
	};
	printf("-------------------\nline_equation:\n");
	line_equation(line_p[0], line_p[1], line_eq);
	printf("    x = %.2f + %.2ft\n", line_eq[0].x, line_eq[1].x);
	printf("    y = %.2f + %.2ft\n", line_eq[0].y, line_eq[1].y);
	printf("    z = %.2f + %.2ft\n", line_eq[0].z, line_eq[1].z);


	float t;



	t = -(eq[0] * line_eq[0].x + eq[1] * line_eq[0].y + eq[2] * line_eq[0].z + eq[3]) / 
			(eq[0] * line_eq[1].x + eq[1] * line_eq[1].y + eq[2] * line_eq[1].z);

	printf("t = %.2f\n", t);
	t_point p;

	p.x = line_eq[0].x + t * line_eq[1].x;
	p.y = line_eq[0].y + t * line_eq[1].y;
	p.z = line_eq[0].z + t * line_eq[1].z;


	printf("point: (%.2f, %.2f, %.2f)\n", p.x, p.y, p.z);
	return (0);
}