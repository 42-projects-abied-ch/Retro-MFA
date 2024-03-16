#include "retro.h"

int	init_window(t_surf *surf, t_imgdata *data)
{
	surf->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	surf->win = mlx_new_window(surf->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "retro-MFA");
	if (!surf->win)
		return (1);
	data->img = mlx_new_image(surf->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->img)
		return (1);
	data->addr = mlx_get_data_addr(data->img, \
				&data->bits_per_pixel, &data->lines_length, &data->endian);
	surf->img = data;
	return (0);
}