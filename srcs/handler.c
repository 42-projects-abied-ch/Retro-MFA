#include "retro.h"

int	key_press_handler(int keycode, t_surf *surf)
{
	if (keycode == KEY_ESC)
	{
		mlx_loop_end(surf->mlx);
		return (0);
	}
	return (0);
}

int	key_release_handler(int keycode, t_surf *surf)
{
	(void)keycode;
	(void)surf;
	return (0);
}