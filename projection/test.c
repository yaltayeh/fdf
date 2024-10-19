#include <math.h>
#include <stdio.h>

#define DEFINE_ADD(type) 			\
	type add_##type(type a, type b)	\
	{								\
		return (a + b);				\
	}

DEFINE_ADD(int);
DEFINE_ADD(double);
DEFINE_ADD(float);

#undef DEFINE_ADD

int main()
{
	// t_cylindrical cy;
	// t_cartesian car = {1, 1, 1};
	// cy = cartesian_2_cylindrical(car);
	// printf("(%.8lf, %.2lf, %.2lf)\n", cy.azimuth, cy.radial, cy.z);
	printf("%.5lf\n", acos(0));
}