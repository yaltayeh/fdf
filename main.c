// #include <libft.h>
// #include "matrix/point.h"
#include <mlx.h>
#include "fdf.h"
#include <math.h>
#include <stdlib.h>

char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);


int render_frame(t_fdf_data *data)
{
	int		r;
	static void	*img;
	int		bpp;
	int 	size_line;
	int 	endian;
	int  *buffer;


	r = data->w < data->h ? data->w: data->h;
	img = mlx_new_image(data->mlx_ptr, r, r);
	buffer = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	if (!img)
		return (0);
	for (int y = 1; y < r; y++)
		for (int x = 1; x < r; x++)
		{
			float _x, _y;
			_x = x * data->test;
			_y = y * data->test;
			//float v = tan(_x * _x + _y * _y) * cos(_x + _y) - cos(_x * _x + _y * _y);
			//float v = (sin(2 * _y) - 2 * sin(pow(_x, 8)) - _y) / _y;
			//float v = (_x * _x + _y * _y) / (90 * cos(4 * _x));
			float v = sin(_x) + sin(pow(_y, 5));
			if (v < cos(data->test2))
				buffer[y * r + x] = 0xff0000;
		}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, 0, 0);
	return (1);
}

t_fdf_data	*start_window()
{
	t_fdf_data	*data;

	data = malloc(sizeof(t_fdf_data));
	if (!data)
		return (NULL);
	data->test = 1;
	data->test2 = 1;
	data->w = W ;
	data->h = H;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (NULL);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->w, data->h, "TEST");
	if (!data->win_ptr)
		return (NULL);
	events_config(data);
	return (data);
}


int main()
{
	t_fdf_data	*data;

	data = start_window();
	if (!data)
		return (1);
	mlx_loop_hook(data->mlx_ptr, render_frame, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}