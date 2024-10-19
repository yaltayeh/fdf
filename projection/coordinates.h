#include <math.h>

typedef struct s_cartesian
{
	double	x;
	double	y;
	double	z;
} t_cartesian;

// https://en.wikipedia.org/wiki/Spherical_coordinate_system
typedef struct s_spherical
{
	double	radius;
	double	inclination;
	double	azimuth;
} t_spherical;

// https://en.wikipedia.org/wiki/Cylindrical_coordinate_system
typedef struct s_cylindrical
{
	double	radial;
	double	azimuth;
	double	z;
}	t_cylindrical;

t_cartesian spherical_2_cartesian(t_spherical sp);

t_spherical cartesian_2_spherical(t_cartesian car);

t_cartesian cylindrical_2_cartesian(t_cylindrical cy);

t_cylindrical cartesian_2_cylindrical(t_cartesian car);
