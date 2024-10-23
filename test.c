#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <mlx.h>
#include "fdf.h"
#include <string.h>

#define EVENT_DEVICE "/dev/input/event18" // Change to your event device

int fd; // File descriptor for input device
int button_pressed = 0; // Variable to track button state

int close_window(t_fdf_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data);
	exit(0);
}

int read_events(t_fdf_data *data) {
    struct input_event ev;
    ssize_t bytes = read(fd, &ev, sizeof(ev));
    if (bytes < (ssize_t)sizeof(ev)) {
        return 0; // No event read
    }

    if (ev.type == EV_KEY)
    {
        if (ev.code == 304 && ev.value)
            data->mask = (data->mask + 1) % 24;
        else if (ev.code == 305 && ev.value)
            close_window(data);
    }
   if (ev.type == EV_ABS) 
   {
        if (ev.code == 0) 
            data->cx = (ev.value - 128) + data->w * 0.25f;
        if (ev.code == 1) 
            data->cy = (ev.value - 128) + data->h * 0.25f;

        if (ev.code == 3) 
            data->cx2 = (ev.value - 128) + data->w * 0.25f;
        if (ev.code == 4) 
            data->cy2 = (ev.value - 128) + data->h * 0.25f;
	}
    return 1; // Event read successfully
}

int update_window(t_fdf_data *data) {
    int		r;
	static void	*img;
	static void	*img2;
	int		bpp;
	int 	size_line;
	int 	endian;
	int  *buffer;

    // This will be called once per loop iteration
    read_events(data); // Read input events
    // You can update the window here based on button_pressed if needed
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
	r = data->w < data->h ? data->w: data->h;
	if (!img)
	{
		img = mlx_new_image(data->mlx_ptr, r, r);
		if (!img)
			return (1);
	}
    if (!img2)
	{
		img2 = mlx_new_image(data->mlx_ptr, r, r);
		if (!img2)
			return (1);
	}
	buffer = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	for (int y = 0; y < r; y++)
		for (int x = 0; x < r; x++)
		{
			float v = (x - 100) * (x - 100) + (y - 100) * (y - 100);
            
			if (v <= 100 * 100)
				buffer[y * r + x] = (int)(255 * (v)) << (data->mask * 1);
		}
    buffer = (int *)mlx_get_data_addr(img2, &bpp, &size_line, &endian);
	for (int y = 0; y < r; y++)
		for (int x = 0; x < r; x++)
		{
			float v = (x - 100) * (x - 100) + (y - 100) * (y - 100);
            
			if (v <= 100 * 100)
				buffer[y * r + x] = (int)(255 * (v)) << (data->mask * 1);
		}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, data->cx - 100, data->cy);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img2, data->cx2 + 400, data->cy2);
    return 1; // Return 0 to keep the loop running
}

int main() {
    t_fdf_data data;
    fd = open(EVENT_DEVICE, O_RDONLY);
    // if (fd < 0) {
    //     perror("Failed to open device");
    //     return EXIT_FAILURE;
    // }
    memset(&data, 0, sizeof(data));
    data.mlx_ptr = mlx_init();
    data.w = 1000;
    data.h = 600;
    data.win_ptr = mlx_new_window(data.mlx_ptr, data.w, data.h, "PS5 Controller Input");
    data.mask = 21;

    mlx_loop_hook(data.mlx_ptr, update_window, &data); // Hook the update function
    mlx_loop(data.mlx_ptr); // Start the loop

    close(fd);
    return EXIT_SUCCESS;
}
