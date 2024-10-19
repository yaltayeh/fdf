#include <math.h>
#include "coordinates.h"

t_cartesian spherical_2_cartesian(t_spherical sp)
{
	t_cartesian	car;

	car.x = sp.radius * sin(sp.inclination) * cos(sp.azimuth);
	car.y = sp.radius * sin(sp.inclination) * sin(sp.azimuth);
	car.z = sp.radius * cos(sp.inclination);
	return (car);
}

t_spherical cartesian_2_spherical(t_cartesian car)
{
	t_spherical sp;
	double		xy;
	double		xyz;

	xy = car.x * car.x + car.y * car.y;
	xyz = xy + car.z * car.z;
	sp.radius = sqrt(xyz);
	// if (xyz == 0)
	// 	exit(1);	
	sp.inclination = acos(car.z / sqrt(xyz));
	sp.azimuth = 0;

	return (sp);
}


t_cartesian cylindrical_2_cartesian(t_cylindrical cy)
{
	t_cartesian	car;

	car.x = cy.radial * cos(cy.azimuth);
	car.y = cy.radial * sin(cy.azimuth);
	car.z = cy.z;
	return (car);
}

t_cylindrical cartesian_2_cylindrical(t_cartesian car)
{
	t_cylindrical	cy;

	cy.radial = sqrt(car.x * car.x + car.y * car.y);
	cy.z = car.z;
	// if (car.x == 0 && car.y == 0)
	// 	exit(1);

	if (car.x >= 0)
		cy.azimuth = asin(car.y / cy.radial);
	else 
		cy.azimuth = -asin(car.y / cy.radial) + M_PI;
	return (cy);
}

