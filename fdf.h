#ifndef FDF_H
# define FDF_H

# include <mlx.h>

# define ON_KEYDOWN		2	// int (*f)(int keycode, void *param)
# define ON_KEYUP		3	// int (*f)(int keycode, void *param)
# define ON_MOUSEDOWN	4	// int (*f)(int button, int x, int y, void *param)
# define ON_MOUSEUP		5	// int (*f)(int button, int x, int y, void *param)
# define ON_MOUSEMOVE	6	// int (*f)(int x, int y, void *param)
# define ON_EXPOSE		12	// int (*f)(void *param)
# define ON_DESTROY		17	// int (*f)(void *param)

#define W 1200
#define H 750

typedef struct s_fdf_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		controller_fd;
	int		w;
	int		h;
	float	cx;
	float	cy;
	float	cx2;
	float	cy2;
	int mask;
} t_fdf_data;

int	destroy_event(t_fdf_data *data);

int events_config(t_fdf_data *data);

#endif