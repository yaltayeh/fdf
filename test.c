#include <libft.h>
#include "matrix/point.h"
#include <mlx.h>
#include "fdf.h"
#include <math.h>

char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);


int render_frame(t_fdf_data *data)
{
	int		r;
	void	*img;
	int		bpp;
	int 	size_line;
	int 	endian;
	int  *buffer;


	r = data->w < data->h ? data->w: data->h;
	img = mlx_new_image(data->mlx_ptr, r, r);
	r /= 2;
	buffer = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	if (!img)
		return (0);
	for (int y = 0; y < r; y++)
		for (int x = 0; x < r; x++)
		{
			if (x * x + y * y < r * r)
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
	data->w = W;
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