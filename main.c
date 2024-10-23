// #include <libft.h>
// #include "matrix/point.h"
#include <mlx.h>
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdio.h>
#include <libft.h>

char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);


int render_frame(t_fdf_data *data)
{
	int		r;
	static void	*img;
	int		bpp;
	int 	size_line;
	int 	endian;
	int  *buffer;
	struct input_event ev;
	ssize_t bytes;

	(void)bytes;
	if (data->controller_fd != 0)
	{
		ft_bzero(&ev, sizeof(ev));
		//printf("ev: %u\n", ev.code);
	//  	// bytes = read(data->controller_fd, &ev, sizeof(struct input_event));
	// 	// if (bytes <= 0)
	// 	// 	return (0);
	// // 	if (bytes < (ssize_t)sizeof(struct input_event)) 
	// // 	{
	// // 		close(data->controller_fd);
	// // 		data->controller_fd = 0;
	// // 	}
	// // 	if (ev.type == EV_ABS) {
	// // 		if (ev.code == 1) 
	// // 			data->cy = (ev.value - 128) + 750 * 0.25f;
	// // 		if (ev.code == 0) 
	// // 			data->cx = (ev.value - 128) + 750 * 0.25f;
	// // 	}
	//  //	usleep(10000);
	}


	//mlx_clear_window(data->mlx_ptr, data->win_ptr);
	if (img == NULL)
	{
		r = data->w < data->h ? data->w: data->h;
		img = mlx_new_image(data->mlx_ptr, r, r);
		if (!img)
			return (1);
	}
	buffer = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	for (int y = 0; y < r; y++)
		for (int x = 0; x < r; x++)
		{
			float v = x * x + y * y - 100 * 100;
			if (v <= 0)
				buffer[y * r + x] = 0xff0000;
		}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, data->cx, data->cy);
	return (1);
}

t_fdf_data	*start_window()
{
	t_fdf_data	*data;

	data = malloc(sizeof(t_fdf_data));
	if (!data)
		return (NULL);
	data->cx = 0;
	data->cy = 0;
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
    int fd;
	t_fdf_data	*data;

	data = start_window();
	if (!data)
		return (1);

    // Open the input device (replace 'eventX' with the correct event number)
    fd = open("/dev/input/event18", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return EXIT_FAILURE;
    }
	data->controller_fd = fd;
	mlx_loop_hook(data->mlx_ptr, render_frame, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}