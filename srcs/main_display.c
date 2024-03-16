#include "retro.h"
#include <mlx.h>

int main()
{
	t_surf	data;

	memset(&data, 0, sizeof(t_surf));
	init_mlx(&data);
	init_window_arthur(&data);
	display_full_screen(&data);
	mlx_hook(data.win, 17, 0, exit_success, &data);
	mlx_hook(data.win, 2, 1L, key_press_handler, &data);
	mlx_loop(data.mlx);
	cleanup_display(&data);
}