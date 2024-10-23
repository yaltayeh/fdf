#include <stdio.h>
#include "fdf.h"
#include <stdlib.h>

#define INFO(fmt, ...) printf("%s: "fmt"\n", __func__, ##__VA_ARGS__); (void)data;

int	destroy_event(t_fdf_data *data);

int key_down_event(int keycode, t_fdf_data *data)
{
	INFO("key=%d", keycode);
	if (keycode == 126)
		data->test += 0.1f;
	if (keycode == 125)
		data->test -= 0.1f;
	if (keycode == 123)
		data->test2 -= 0.1f;
	if (keycode == 124)
		data->test2 += 0.1f;
	if (keycode == 53)
		destroy_event(data);
	return (0);
}

int key_up_event(int keycode, t_fdf_data *data)
{
	INFO("key=%d", keycode);
	return (0);
}

int mouse_down_event(int button, int x, int y, t_fdf_data *data)
{
	INFO("button=%d, x=%d, y=%d", button, x, y);
	return (0);
}

int mouse_up_event(int button, int x, int y, t_fdf_data *data)
{

	INFO("button=%d, x=%d, y=%d", button, x, y);
	return (0);
}

int mouse_move_event(int x, int y, t_fdf_data *data)
{
	INFO("x=%d, y=%d", x, y);
	return (0);
}

int	expose_event(t_fdf_data *data)
{
	INFO();
	return (0);
}

int	destroy_event(t_fdf_data *data)
{
	INFO();
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data);
	exit(0);
}

int events_config(t_fdf_data *data)
{
	mlx_hook(data->win_ptr, ON_KEYDOWN,   0, key_down_event,    data);
	mlx_hook(data->win_ptr, ON_KEYUP,     0, key_up_event,      data);
	mlx_hook(data->win_ptr, ON_MOUSEDOWN, 0, mouse_down_event,  data);
	mlx_hook(data->win_ptr, ON_MOUSEUP,   0, mouse_up_event,    data);
//	mlx_hook(data->win_ptr, ON_MOUSEMOVE, 0, mouse_move_event,  data);
	mlx_hook(data->win_ptr, ON_EXPOSE,    0, expose_event,      data);
	mlx_hook(data->win_ptr, ON_DESTROY,   0, destroy_event,     data);
	return (0);
}