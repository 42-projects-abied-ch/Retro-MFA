#include "retro.h"

void	init_mlx(t_surf* data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit_failure(data, "error\nmlx initialization failed");
}

void	init_window_arthur(t_surf* data)
{
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Retro-MFA");
	if (data->win == NULL)
		exit_failure(data, "error\nwindow initialization failed");
}

