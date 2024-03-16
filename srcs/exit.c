#include "retro.h"

void	cleanup_display(t_surf* data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

int		exit_success(t_surf* data)
{
	cleanup_display(data);
	exit(EXIT_SUCCESS);
}

void	exit_failure(t_surf* data, char* msg)
{
	cleanup_display(data);
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}